#include <VL53L0X.h>
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
int ToFFrontCT=999;
int ToFFrontA=999;
int ToFFrontB=999;
int ToFRightCT=999;
int ToFRightA=999;
int ToFRightB=999;
int ToFLeftCT=999;
int ToFLeftA=999;
int ToFLeftB=999;
int ToFBackCT=999;
int ToFBackA=999;
int ToFBackB=999;



void ToFInitialize(){
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
  ToFFrontCT = ((FrontCT.readRangeContinuousMillimeters()+60)*1)+(ToFFrontCT*0);
  ToFFrontA = ((FrontA.readRangeContinuousMillimeters()+60)*1)+(ToFFrontA*0);
  ToFFrontB = ((FrontB.readRangeContinuousMillimeters()+60)*1)+(ToFFrontB*0);
  ToFRightCT = ((RightCT.readRangeContinuousMillimeters()+60)*1)+(ToFRightCT*0);
  ToFRightA = ((RightA.readRangeContinuousMillimeters()+60)*1)+(ToFRightA*0);
  ToFRightB = ((RightB.readRangeContinuousMillimeters()+60)*1)+(ToFRightB*0);
  ToFLeftCT = ((LeftCT.readRangeContinuousMillimeters()+60)*1)+(ToFLeftCT*0);
  ToFLeftA = ((LeftA.readRangeContinuousMillimeters()+60)*1)+(ToFLeftA*0);
  ToFLeftB = ((LeftB.readRangeContinuousMillimeters()+60)*1)+(ToFLeftB*0);
  ToFBackCT = ((BackCT.readRangeContinuousMillimeters()+60)*1)+(ToFBackCT*0);
  ToFBackA = ((BackA.readRangeContinuousMillimeters()+60)*1)+(ToFBackA*0);
  ToFBackB = ((BackB.readRangeContinuousMillimeters()+60)*1)+(ToFBackB*0);
}
