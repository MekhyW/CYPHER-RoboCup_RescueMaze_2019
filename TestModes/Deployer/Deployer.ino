#include <Servo.h>
#define DeployerPin 26
Servo Deployer;

void setup() {
  Serial.begin(9600);
  Deployer.attach(DeployerPin);
  Deployer.write(75);
  delay(1000);
}

void DeployKitRight(){
  Deployer.write(145);
  delay(400);
  Deployer.write(60);
  delay(300);
  Deployer.write(75);
  delay(300);
}

void DeployKitLeft(){
  Deployer.write(5);
  delay(400);
  Deployer.write(90);
  delay(300);
  Deployer.write(75);
  delay(300);
}


void loop() {
  Serial.println("here");
  DeployKitLeft();
  delay(2000);
  DeployKitRight();
  delay(2000);
}
