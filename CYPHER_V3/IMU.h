#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
Adafruit_BNO055 bno = Adafruit_BNO055();
float Inclination=90;
float InclinationError=0;
float Angle=0;
float AngleError=0;
float Tilt=0;
float TiltError=0;
int Quadrant=3; //1=left 2=right 3=up 4=down

void ReadIMU(){
  delay(10);
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  Inclination = euler.z()-InclinationError;
  Angle = euler.x()-AngleError;
  if(Angle<0){
    Angle+=360;
  }
}

void IMUCalibrate(){
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  Inclination = euler.z();
  InclinationError=Inclination-90;
  Angle = euler.x();
  AngleError = Angle;
}

void IMUInitialize(){
  bno.begin();
  bno.setExtCrystalUse(true);
  IMUCalibrate();
}
