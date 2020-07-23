#include <Servo.h>
#define DeployerPin 26
Servo Deployer;
#define motorUR 12
#define motorURdirA 11
#define motorURdirB 10
#define motorLR 6
#define motorLRdirA 4
#define motorLRdirB 5
#define motorUL 9
#define motorULdirA 8
#define motorULdirB 7
#define motorLL 3
#define motorLLdirA 2
#define motorLLdirB 28
int KitCounter=12;

void MotorsRelease(){
  digitalWrite(motorULdirA, LOW);
  digitalWrite(motorULdirB, LOW);
  digitalWrite(motorURdirA, LOW);
  digitalWrite(motorURdirB, LOW);
  digitalWrite(motorLLdirA, LOW);
  digitalWrite(motorLLdirB, LOW);
  digitalWrite(motorLRdirA, LOW);
  digitalWrite(motorLRdirB, LOW);
}

void MotorsStop(){
  digitalWrite(motorULdirA, HIGH);
  digitalWrite(motorULdirB, HIGH);
  digitalWrite(motorURdirA, HIGH);
  digitalWrite(motorURdirB, HIGH);
  digitalWrite(motorLLdirA, HIGH);
  digitalWrite(motorLLdirB, HIGH);
  digitalWrite(motorLRdirA, HIGH);
  digitalWrite(motorLRdirB, HIGH);
}

void MotorsInitialize(){
  Deployer.attach(DeployerPin);
  Deployer.write(75);
  pinMode(motorUL, OUTPUT);
  pinMode(motorULdirA, OUTPUT);
  pinMode(motorULdirB, OUTPUT);
  pinMode(motorLL, OUTPUT);
  pinMode(motorLLdirA, OUTPUT);
  pinMode(motorLLdirB, OUTPUT);
  pinMode(motorUR, OUTPUT);
  pinMode(motorURdirA, OUTPUT);
  pinMode(motorURdirB, OUTPUT);
  pinMode(motorLR, OUTPUT);
  pinMode(motorLRdirA, OUTPUT);
  pinMode(motorLRdirB, OUTPUT);
  MotorsStop();
}

void URForward(){
  digitalWrite(motorURdirA, HIGH);
  digitalWrite(motorURdirB, LOW);
}

void URBackwards(){
  digitalWrite(motorURdirA, LOW);
  digitalWrite(motorURdirB, HIGH);
}

void ULForward(){
  digitalWrite(motorULdirA, HIGH);
  digitalWrite(motorULdirB, LOW);
}

void ULBackwards(){
  digitalWrite(motorULdirA, LOW);
  digitalWrite(motorULdirB, HIGH);
}

void LRForward(){
  digitalWrite(motorLRdirA, HIGH);
  digitalWrite(motorLRdirB, LOW);
}

void LRBackwards(){
  digitalWrite(motorLRdirA, LOW);
  digitalWrite(motorLRdirB, HIGH);
}

void LLForward(){
  digitalWrite(motorLLdirA, HIGH);
  digitalWrite(motorLLdirB, LOW);
}

void LLBackwards(){
  digitalWrite(motorLLdirA, LOW);
  digitalWrite(motorLLdirB, HIGH);
}


void MoveForward(int speed){
  ULForward();
  LLForward();
  URForward();
  LRForward();
  analogWrite(motorUL, speed);
  analogWrite(motorLL, speed);
  analogWrite(motorUR, speed);
  analogWrite(motorLR, speed);
}

void MoveForwardPID(int speed){
  ULForward();
  LLForward();
  URForward();
  LRForward();
  CalculatePID();
  if(ConservativePID==false){
    analogWrite(motorUL, constrain(speed-PID_value, 0, 250));
    analogWrite(motorLL, constrain(speed-PID_value, 0, 250));
    analogWrite(motorUR, constrain(speed+PID_value, 0, 250));
    analogWrite(motorLR, constrain(speed+PID_value, 0, 250));
  } else if(ConservativePID==true){
    analogWrite(motorUL, constrain(speed-PID_value, 130, 250));
    analogWrite(motorLL, constrain(speed-PID_value, 130, 250));
    analogWrite(motorUR, constrain(speed+PID_value, 130, 250));
    analogWrite(motorLR, constrain(speed+PID_value, 130, 250));
  }
}


void MoveBackwards(int speed){
  ULBackwards();
  LLBackwards();
  URBackwards();
  LRBackwards();
  analogWrite(motorUL, speed);
  analogWrite(motorLL, speed);
  analogWrite(motorUR, speed);
  analogWrite(motorLR, speed);
}

void MoveBackwardsPID(int speed){
  ULBackwards();
  LLBackwards();
  URBackwards();
  LRBackwards();
  CalculatePID();
  if(ConservativePID==false){
    analogWrite(motorUL, constrain(speed+PID_value, 0, 250));
    analogWrite(motorLL, constrain(speed+PID_value, 0, 250));
    analogWrite(motorUR, constrain(speed-PID_value, 0, 250));
    analogWrite(motorLR, constrain(speed-PID_value, 0, 250));
  } else if(ConservativePID==true){
    analogWrite(motorUL, constrain(speed+PID_value, 120, 250));
    analogWrite(motorLL, constrain(speed+PID_value, 120, 250));
    analogWrite(motorUR, constrain(speed-PID_value, 120, 250));
    analogWrite(motorLR, constrain(speed-PID_value, 120, 250));
  }
}


void RotateLeft(int speed){
  ULBackwards();
  LLBackwards();
  URForward();
  LRForward();
  analogWrite(motorUL, constrain(speed, 130, 250));
  analogWrite(motorLL, constrain(speed, 130, 250));
  analogWrite(motorUR, constrain(speed, 130, 250));
  analogWrite(motorLR, constrain(speed, 130, 250));
}


void RotateRight(int speed){
  ULForward();
  LLForward();
  URBackwards();
  LRBackwards();
  analogWrite(motorUL, constrain(speed, 130, 250));
  analogWrite(motorLL, constrain(speed, 130, 250));
  analogWrite(motorUR, constrain(speed, 130, 250));
  analogWrite(motorLR, constrain(speed, 130, 250));
}


void Introduce(int side, int dir, int speed){
  if(side==1 && dir==1){
    ULForward();
    LLForward();
    analogWrite(motorUL, speed);
    analogWrite(motorLL, speed);
    analogWrite(motorUR, 0);
    analogWrite(motorLR, 0);
  } else if(side==2 && dir==1){
    URForward();
    LRForward();
    analogWrite(motorUL, 0);
    analogWrite(motorLL, 0);
    analogWrite(motorUR, speed);
    analogWrite(motorLR, speed);
  } else if(side==1 && dir==(-1)){
    ULBackwards();
    LLBackwards();
    analogWrite(motorUL, speed);
    analogWrite(motorLL, speed);
    analogWrite(motorUR, 0);
    analogWrite(motorLR, 0);
  } else if(side==2 && dir==(-1)){
    URBackwards();
    LRBackwards();
    analogWrite(motorUL, 0);
    analogWrite(motorLL, 0);
    analogWrite(motorUR, speed);
    analogWrite(motorLR, speed);
  }
}


void DeployKitRight(){
  Deployer.write(145);
  delay(400);
  Deployer.write(60);
  delay(300);
  Deployer.write(75);
  delay(300);
  KitCounter--;
}

void DeployKitLeft(){
  Deployer.write(5);
  delay(400);
  Deployer.write(90);
  delay(300);
  Deployer.write(75);
  delay(300);
  KitCounter--;
}

void BackForth(){
  MoveForward(250);
  delay(1000);
  MoveBackwards(250);
  delay(1000);
  MotorsStop();
  delay(100);
  MotorsRelease();
  DrawForegroundPic(7);
  delay(10000);
  EraseForegroundPic();
}
