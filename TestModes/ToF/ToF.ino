#include <VL53L0X.h>
#include <Wire.h>
#include <Nextion.h>
NexNumber n0 = NexNumber(0, 2, "n0");
#define L0XFrontCTxshut 39
#define L0XFrontAxshut 38
#define L0XFrontBxshut 49
#define L0XRightCTxshut 51
#define L0XRightAxshut 47
#define L0XRightBxshut 48
#define L0XLeftCTxshut 41
#define L0XLeftAxshut 40
#define L0XLeftBxshut 45
#define L0XBackCTxshut 46
#define L0XBackAxshut 50
#define L0XBackBxshut 43
VL53L0X FrontCT;
VL53L0X FrontA;
VL53L0X FrontB;
VL53L0X RightCT;
VL53L0X RightA;
VL53L0X RightB;
VL53L0X LeftCT;
VL53L0X LeftA;
VL53L0X LeftB;
VL53L0X BackCT;
VL53L0X BackA;
VL53L0X BackB;
int ToFFrontCT=9999;
int ToFFrontA=9999;
int ToFFrontB=9999;
int ToFRightCT=9999;
int ToFRightA=9999;
int ToFRightB=9999;
int ToFLeftCT=9999;
int ToFLeftA=9999;
int ToFLeftB=9999;
int ToFBackCT=9999;
int ToFBackA=9999;
int ToFBackB=9999;
#include "Motors.h"
#include "PID.h"


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(100000);
  ToFInitialize();
  nexInit();
  MotorsInitialize();
  MoveForward(150);
}

void ToFInitialize(){
  Serial.println("initializing");
  pinMode(L0XFrontCTxshut, OUTPUT);
  pinMode(L0XFrontAxshut, OUTPUT);
  pinMode(L0XFrontBxshut, OUTPUT);
  pinMode(L0XRightCTxshut, OUTPUT);
  pinMode(L0XRightAxshut, OUTPUT);
  pinMode(L0XRightBxshut, OUTPUT);
  pinMode(L0XLeftCTxshut, OUTPUT);
  pinMode(L0XLeftAxshut, OUTPUT);
  pinMode(L0XLeftBxshut, OUTPUT);
  pinMode(L0XBackCTxshut, OUTPUT);
  pinMode(L0XBackAxshut, OUTPUT);
  pinMode(L0XBackBxshut, OUTPUT);
  delay(10);
  pinMode(L0XFrontBxshut, INPUT);
  delay(10);
  FrontB.setAddress(53);
  pinMode(L0XFrontAxshut, INPUT);
  delay(10);
  FrontA.setAddress(42);
  pinMode(L0XFrontCTxshut, INPUT);
  delay(10);
  FrontCT.setAddress(43);
  pinMode(L0XRightCTxshut, INPUT);
  delay(10);
  RightCT.setAddress(44);
  pinMode(L0XRightAxshut, INPUT);
  delay(10);
  RightA.setAddress(45);
  pinMode(L0XRightBxshut, INPUT);
  delay(10);
  RightB.setAddress(46);
  pinMode(L0XLeftCTxshut, INPUT);
  delay(10);
  LeftCT.setAddress(47);
  pinMode(L0XLeftAxshut, INPUT);
  delay(10);
  LeftA.setAddress(48);
  pinMode(L0XLeftBxshut, INPUT);
  delay(10);
  LeftB.setAddress(49);
  pinMode(L0XBackCTxshut, INPUT);
  delay(10);
  BackCT.setAddress(50);
  pinMode(L0XBackAxshut, INPUT);
  delay(10);
  BackA.setAddress(51);
  pinMode(L0XBackBxshut, INPUT);
  delay(10);
  BackB.setAddress(52);
  FrontA.init();
  FrontA.setTimeout(100);
  FrontA.startContinuous();
  FrontCT.init();
  FrontCT.setTimeout(100);
  FrontCT.startContinuous();
  FrontB.init();
  FrontB.setTimeout(100);
  FrontB.startContinuous();
  RightA.init();
  RightA.setTimeout(100);
  RightA.startContinuous();
  RightCT.init();
  RightCT.setTimeout(100);
  RightCT.startContinuous();
  RightB.init();
  RightB.setTimeout(100);
  RightB.startContinuous();
  LeftA.init();
  LeftA.setTimeout(100);
  LeftA.startContinuous();
  LeftCT.init();
  LeftCT.setTimeout(100);
  LeftCT.startContinuous();
  LeftB.init();
  LeftB.setTimeout(100);
  LeftB.startContinuous();
  BackCT.init();
  BackCT.setTimeout(100);
  BackCT.startContinuous();
  BackA.init();
  BackA.setTimeout(100);
  BackA.startContinuous();
  BackB.init();
  BackB.setTimeout(100);
  BackB.startContinuous();
  FrontA.setMeasurementTimingBudget(70000);
  FrontB.setMeasurementTimingBudget(70000);
  FrontCT.setMeasurementTimingBudget(70000);
  RightA.setMeasurementTimingBudget(70000);
  RightB.setMeasurementTimingBudget(70000);
  RightCT.setMeasurementTimingBudget(70000);
  LeftA.setMeasurementTimingBudget(70000);
  LeftB.setMeasurementTimingBudget(70000);
  LeftCT.setMeasurementTimingBudget(70000);
  BackA.setMeasurementTimingBudget(70000);
  BackB.setMeasurementTimingBudget(70000);
  BackCT.setMeasurementTimingBudget(70000);
}

void ReadToF(){
  ToFFrontCT = FrontCT.readRangeContinuousMillimeters()+60;
  ToFFrontA = FrontA.readRangeContinuousMillimeters()+60;
  ToFFrontB = FrontB.readRangeContinuousMillimeters()+60;
  ToFRightCT = RightCT.readRangeContinuousMillimeters()+60;
  ToFRightA = RightA.readRangeContinuousMillimeters()+60;
  ToFRightB = RightB.readRangeContinuousMillimeters()+60;
  ToFLeftCT = LeftCT.readRangeContinuousMillimeters()+60;
  ToFLeftA = LeftA.readRangeContinuousMillimeters()+60;
  ToFLeftB = LeftB.readRangeContinuousMillimeters()+60;
  ToFBackCT = BackCT.readRangeContinuousMillimeters()+60;
  ToFBackA = BackA.readRangeContinuousMillimeters()+60;
  ToFBackB = BackB.readRangeContinuousMillimeters()+60;
}

void loop() {
  ReadToF();
  //delay(50);
  //Serial.print(abs(((ToFRightA+ToFRightB)/2)-ToFRightCT));
  Serial.print(ToFFrontA);
  Serial.print("    ");
  Serial.print(ToFFrontCT);
  Serial.print("    ");
  Serial.print(ToFFrontB);
  Serial.print("    ");
  Serial.print(ToFRightA);
  Serial.print("    ");
  Serial.print(ToFRightCT);
  Serial.print("    ");
  Serial.print(ToFRightB);
  Serial.print("    ");
  Serial.print(ToFLeftA);
  Serial.print("    ");
  Serial.print(ToFLeftCT);
  Serial.print("    ");
  Serial.print(ToFLeftB);
  Serial.print("    ");
  Serial.print(ToFBackA);
  Serial.print("    ");
  Serial.print(ToFBackCT);
  Serial.print("    ");
  Serial.println(ToFBackB);
}
