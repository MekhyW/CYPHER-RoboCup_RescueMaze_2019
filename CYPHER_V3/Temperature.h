#include <Arduino.h>
#include <include/twi.h>
#define ADDR      0x5A
#define ADDR_B    0x50
#define TO_MAX    0x00
#define TO_MIN    0x01
#define PWM_CTRL  0x02
#define RAW_IR_1  0x04
#define RAW_IR_2  0x05
#define TA        0x06
#define TOBJ_1    0x07
#define TOBJ_2    0x08
static const uint32_t TWI_CLOCK = 100000;
static const uint32_t RECV_TIMEOUT = 100000;
static const uint32_t XMIT_TIMEOUT = 100000;
Twi *pTwi = WIRE_INTERFACE;
#define VHeatThreshold 3 
float TemperatureL=0;
float TemperatureR=0;
float AtmosphereL=0;
float AtmosphereR=0;

static void Wire_Init(void) {
  pmc_enable_periph_clk(WIRE_INTERFACE_ID);
  PIO_Configure(
  g_APinDescription[PIN_WIRE_SDA].pPort,
  g_APinDescription[PIN_WIRE_SDA].ulPinType,
  g_APinDescription[PIN_WIRE_SDA].ulPin,
  g_APinDescription[PIN_WIRE_SDA].ulPinConfiguration);
  PIO_Configure(
  g_APinDescription[PIN_WIRE_SCL].pPort,
  g_APinDescription[PIN_WIRE_SCL].ulPinType,
  g_APinDescription[PIN_WIRE_SCL].ulPin,
  g_APinDescription[PIN_WIRE_SCL].ulPinConfiguration);
  NVIC_DisableIRQ(TWI1_IRQn);
  NVIC_ClearPendingIRQ(TWI1_IRQn);
  NVIC_SetPriority(TWI1_IRQn, 0);
  NVIC_EnableIRQ(TWI1_IRQn);
}
 
static void Wire1_Init(void) {
    pmc_enable_periph_clk(WIRE1_INTERFACE_ID);
  PIO_Configure(
      g_APinDescription[PIN_WIRE1_SDA].pPort,
      g_APinDescription[PIN_WIRE1_SDA].ulPinType,
      g_APinDescription[PIN_WIRE1_SDA].ulPin,
      g_APinDescription[PIN_WIRE1_SDA].ulPinConfiguration);
  PIO_Configure(
      g_APinDescription[PIN_WIRE1_SCL].pPort,
      g_APinDescription[PIN_WIRE1_SCL].ulPinType,
      g_APinDescription[PIN_WIRE1_SCL].ulPin,
      g_APinDescription[PIN_WIRE1_SCL].ulPinConfiguration);
  NVIC_DisableIRQ(TWI0_IRQn);
  NVIC_ClearPendingIRQ(TWI0_IRQn);
  NVIC_SetPriority(TWI0_IRQn, 0);
  NVIC_EnableIRQ(TWI0_IRQn);
}

uint8_t readByte() {
  while (!TWI_ByteReceived(pTwi))
    ;
  return TWI_ReadByte(pTwi);
}

static inline bool TWI_FailedAcknowledge(Twi *pTwi) {
  return pTwi->TWI_SR & TWI_SR_NACK;
}

static inline bool TWI_WaitTransferComplete(Twi *_twi, uint32_t _timeout) {
  while (!TWI_TransferComplete(_twi)) {
    if (TWI_FailedAcknowledge(_twi))
      return false;
    if (--_timeout == 0)
      return false;
  }
  return true;
}

static inline bool TWI_WaitByteReceived(Twi *_twi, uint32_t _timeout) {
  while (!TWI_ByteReceived(_twi)) {
    if (TWI_FailedAcknowledge(_twi))
      return false;
    if (--_timeout == 0)
      return false;
  }
  return true;
}



void ReadTemperatureL(){
  uint16_t tempUK;
  float tempK;
  uint8_t hB, lB, pec;
  TWI_StartRead(pTwi, ADDR, TOBJ_1, 1);
  lB = readByte();
  hB = readByte();
  TWI_SendSTOPCondition(pTwi);
  pec = readByte();
  tempUK = (hB << 8) | lB;
  tempK = ((float)tempUK * 2) / 100 ;
  TemperatureL = tempK-273.15;
}

void ReadTemperatureAmbientL(){
  uint16_t tempUK;
  float tempK;
  uint8_t hB, lB, pec;
  TWI_StartRead(pTwi, ADDR, TA, 1);
  lB = readByte();
  hB = readByte();
  TWI_SendSTOPCondition(pTwi);
  pec = readByte();
  tempUK = (hB << 8) | lB;
  tempK = ((float)tempUK * 2) / 100 ;
  AtmosphereL = tempK-273.15;
}

void ReadTemperatureR(){
  uint16_t tempUK;
  float tempK;
  uint8_t hB, lB, pec;
  TWI_StartRead(pTwi, ADDR_B, TOBJ_1, 1);
  lB = readByte();
  hB = readByte();
  TWI_SendSTOPCondition(pTwi);
  pec = readByte();
  tempUK = (hB << 8) | lB;
  tempK = ((float)tempUK * 2) / 100 ;
  TemperatureR = tempK-273.15;
}

void ReadTemperatureAmbientR(){
  uint16_t tempUK;
  float tempK;
  uint8_t hB, lB, pec;
  TWI_StartRead(pTwi, ADDR_B, TA, 1);
  lB = readByte();
  hB = readByte();
  TWI_SendSTOPCondition(pTwi);
  pec = readByte();
  tempUK = (hB << 8) | lB;
  tempK = ((float)tempUK * 2) / 100 ;
  AtmosphereR = tempK-273.15;
}

void ReadTemperature(){
  ReadTemperatureR();
  delay(5);
  ReadTemperatureL();
  delay(5);
  ReadTemperatureAmbientL();
  delay(5);
  ReadTemperatureAmbientR();
}

void TemperatureInitialize(){
  Wire_Init();
  pTwi->TWI_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;
  TWI_ConfigureMaster(pTwi, TWI_CLOCK, VARIANT_MCK);
}
