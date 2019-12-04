#include <Wire.h>
#include "ToF.h"
#include "PID.h"
#include "Motors.h"

void AvoidLeft(){
  //LockEncoders();
  Introduce(1, -1, 250);
  delay(200);
  Introduce(2, -1, 250);
  delay(200);
  Introduce(1, 1, 250);
  delay(500);
  Introduce(2, 1, 250);
  delay(200);
  //UnlockEncoders();
}

void AvoidRight(){
  //LockEncoders();  
  Introduce(2, -1, 250);
  delay(200);
  Introduce(1, -1, 250);
  delay(200);
  Introduce(2, 1, 250);
  delay(200);
  Introduce(1, 1, 250);
  delay(200);
  //UnlockEncoders();
}

void Align(){
  Serial.println("align");
  ResetPID();
  while((ToFFrontCT<150&&ToFFrontA<300&&ToFFrontB<300&&ToFFrontA>(ToFFrontB*1.2)) || (ToFBackCT<300&&ToFBackCT>150&&ToFBackA<300&&ToFBackB<300&&ToFBackA>(ToFBackB*1.2))){
    ReadToF();
    Introduce(2, -1, 150);
  }
  while((ToFFrontCT<150&&ToFFrontA<300&&ToFFrontB<300&&ToFFrontB>(ToFFrontA*1.2)) || (ToFBackCT<300&&ToFBackCT>150&&ToFBackA<300&&ToFBackB<300&&ToFBackB>(ToFBackA*1.2))){
    ReadToF();
    Introduce(1, -1, 150);
  }
  while((ToFFrontCT<300&&ToFFrontCT>150&&ToFFrontA<300&&ToFFrontB<300&&(ToFFrontA*1.2)<ToFFrontB) || (ToFBackCT<150&&ToFBackA<300&&ToFBackB<300&&(ToFBackA*1.2)<ToFBackB)){
    ReadToF();
    Introduce(2, 1, 150);
  }
  while((ToFFrontCT<300&&ToFFrontCT>150&&ToFFrontA<300&&ToFFrontB<300&&(ToFFrontB*1.2)<ToFFrontA) || (ToFBackCT<150&&ToFBackA<300&&ToFBackB<300&&(ToFBackB*1.2)<ToFBackA)){
    ReadToF();
    Introduce(1, 1, 150);
  }
  while((ToFRightCT<300&&ToFRightA<300&&ToFRightB<300&&ToFRightA>(ToFRightB*1.3)) || (ToFLeftCT<300&&ToFLeftA<300&&ToFLeftB<300&&ToFLeftB>(ToFLeftA*1.3))){
      ReadToF();
      Introduce(1, 1, 150);
  }
  while((ToFRightCT<300&&ToFRightA<300&&ToFRightB<300&&(ToFRightA*1.3)<ToFRightB) || (ToFLeftCT<300&&ToFLeftA<300&&ToFLeftB<300&&(ToFLeftB*1.3)<ToFLeftA)){
      ReadToF();
      Introduce(2, 1, 150);
  }
  if(ToFFrontCT<300&&ToFFrontA<300&&ToFFrontB<300&&ToFBackCT<300&&ToFBackA<300&&ToFBackB<300){
    while((ToFFrontCT/1.2)>(ToFFrontCT+ToFBackCT)/2){
      ReadToF();
      MoveForwardPID(150);
    }
    while((ToFBackCT/1.2)>(ToFFrontCT+ToFBackCT)/2){
      ReadToF();
      MoveBackwardsPID(150);
    }
  } else if(ToFFrontCT>300&&ToFFrontCT<600&&ToFFrontA>300&&ToFFrontA<600&&ToFFrontB>300&&ToFFrontB<600&&ToFBackCT>300&&ToFBackCT<600&&ToFBackA>300&&ToFBackA<600&&ToFBackB>300&&ToFBackB<600){
    while((ToFFrontCT/1.1)>(ToFFrontCT+ToFBackCT)/2){
      ReadToF();
      MoveForwardPID(150);
    }
    while((ToFBackCT/1.1)>(ToFFrontCT+ToFBackCT)/2){
      ReadToF();
      MoveBackwardsPID(150);
    }
  } else {
    while((ToFFrontCT<300&&ToFFrontCT>(150*1.2)&&ToFFrontA<300&&ToFFrontB<300) || (ToFFrontCT<600&&ToFFrontCT>(450*1.2)&&ToFFrontA<600&&ToFFrontA>450&&ToFFrontB<600&&ToFFrontB>450&&ToFBackCT>300) || (ToFBackCT<(150/1.4)&&ToFBackA<300&&ToFBackB<300) || (ToFBackCT>300&&ToFBackCT<(450/1.4)&&ToFBackA>300&&ToFBackA<450&&ToFBackB>300&&ToFBackB<450)){
      ReadToF();
      MoveForwardPID(150);
    }
    while((ToFFrontCT<(150/1.4)&&ToFFrontA<300&&ToFFrontB<300) || (ToFFrontCT<(450/1.4)&&ToFFrontCT>300&&ToFFrontA<450&&ToFFrontA>300&&ToFFrontB<450&&ToFFrontB>300) || (ToFBackCT<300&&ToFBackCT>(150*1.2)&&ToFBackA<300&&ToFBackB<300) || (ToFBackCT<600&&ToFBackCT>(450*1.2)&&ToFBackA<600&&ToFBackA>450&&ToFBackB<600&&ToFBackB>450&&ToFFrontCT>300)){
      ReadToF();
      MoveBackwardsPID(150);
    } 
  }
  MotorsStop();
}

void setup() {
  Serial.begin(9600);
  MotorsInitialize();
  Wire.begin();
  ToFInitialize();
  for(int i=0; i<10; i++){
     ReadToF();
  }
  Align();
  //AvoidLeft();
  MotorsStop();
  delay(500);
  MotorsRelease();
}

void loop() {
  //ReadToF();
  //MoveForwardPID(250);
}
