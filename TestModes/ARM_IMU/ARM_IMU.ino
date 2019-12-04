#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
Adafruit_BNO055 bno = Adafruit_BNO055();
float Inclination=90;
float InclinationError=0;
float Angle=0;
float AngleError=0;
float AngularSpeed=0;
float Tilt=0;
float TiltError=0;
int Quadrant=3; //1=left 2=right 3=up 4=down

void ReadIMU(){
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Inclination = euler.z()-InclinationError;
    Angle = euler.x()-AngleError;
    if(Angle<0){
      Angle+=360;
    }
    Tilt = euler.y()-TiltError;
    if(Tilt<0){
      Tilt+=360;
    }
    sensors_event_t angVelocityData;
    bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    AngularSpeed = angVelocityData.gyro.z*57.3;
}

void IMUCalibrate(){
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  Inclination = euler.z();
  InclinationError=Inclination-90;
  Angle = euler.x();
  AngleError = Angle;
  Tilt = euler.y();
  TiltError = Tilt;
}

void IMUInitialize(){
  bno.begin();
  bno.setExtCrystalUse(true);
  IMUCalibrate();
}


void setup() {
  Serial.begin(9600);
  Serial.println("initialize");
  IMUInitialize();
  delay(1000);
}

void loop() {
  ReadIMU();
  Serial.print(Inclination);
  Serial.print("     ");
  Serial.print(Angle);
  Serial.print("     ");
  Serial.print(Tilt);
  Serial.print("     ");
  Serial.println(AngularSpeed);
  delay(100);
}
