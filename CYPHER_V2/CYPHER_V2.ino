// CYPHER Robot V2
// Escola de Robótica ABC Marcelo Salles
// VERSION: 6.1
#include <Wire.h>
#include "IMU.h"
#include "Temperature.h"
#include "Reflection.h"
#include "ToF.h"
#include "PID.h"
#include "Encoders.h"
#include "Cameras.h"
#include "Display.h"
#include "Motors.h"
#include "Map_ADVANCED.h"

void setup() {
	Serial.begin(9600);
	Wire.begin();
  Wire.setClock(100000);
  DisplayInitialize();
  ToFInitialize();
  CamsInitialize();
  ReflectionInitialize();
  TemperatureInitialize();
  MotorsInitialize();
  IMUInitialize();
  PressToStart();
  floodfill[currentfloor][PositionX][PositionY]=1;
}


void loop() {
  ResetEncoders();
  ResetPID();
  while(EncPulseEB<TileDist || EncPulseDB<TileDist || EncPulseEA<TileDist || EncPulseDA<TileDist){
    UpdateEncoders();
    ReadIMU();
  	CheckBackup();
    ReadToF();
    if(ToFFrontCT<150 || (ToFFrontA<=150 && ToFFrontB<=150)){
      break;
    }
    while(ToFLeftA<120 && ToFFrontB>150){
    	WobbleLeft();
    	ReadToF();
    }
    while(ToFRightA<120 && ToFFrontA>150){
    	WobbleRight();
    	ReadToF();
    }
    while(ToFFrontA<200&&ToFFrontCT>300&&ToFFrontB>300){
      WobbleLeft();
      ReadToF();
    }
    while(ToFFrontB<200&&ToFFrontCT>300&&ToFFrontA>300){
      WobbleRight();
      ReadToF();
    }
    CheckVictim();
    if(digitalRead(ImpactSensorLeft)==LOW && ToFFrontCT>200 && floodfill[currentfloor][PositionX][PositionY]!=1){
      AvoidLeft();
    } else if(digitalRead(ImpactSensorRight)==LOW && ToFFrontCT>200 && floodfill[currentfloor][PositionX][PositionY]!=1){
      AvoidRight();
    }
    if(floodfill[currentfloor][PositionX][PositionY]==1){
      ReadReflectionPure();
    } else {
      ReadReflection();
    }
    if(ReflectLeft>TrapLimit && ReflectRight>TrapLimit){
      BlackZone();
      break;
    }
    MoveForwardPID(200);
  }
  NextMove();
}





void Align(){
  Serial.println("align");
  MotorsStop();
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


void AvoidLeft(){
  LockEncoders();
  Introduce(1, -1, 200);
  delay(200);
  Introduce(2, -1, 200);
  delay(200);
  Introduce(1, 1, 200);
  delay(200);
  Introduce(2, 1, 200);
  delay(200);
  UnlockEncoders();
}

void AvoidRight(){
  LockEncoders();  
  Introduce(2, -1, 200);
  delay(200);
  Introduce(1, -1, 200);
  delay(200);
  Introduce(2, 1, 200);
  delay(200);
  Introduce(1, 1, 200);
  delay(200);
  UnlockEncoders();
}

void WobbleRight(){
	LockEncoders();
	RotateRight(200);
    delay(50);
    MoveBackwards(200);
    delay(50);
    RotateLeft(200);
    delay(70);
    MoveForward(200);
    delay(50);
    UnlockEncoders();
}

void WobbleLeft(){
	LockEncoders();
	RotateLeft(200);
    delay(50);
    MoveBackwards(200);
    delay(50);
    RotateRight(200);
    delay(70);
    MoveForward(200);
    delay(50);
    UnlockEncoders();
}

void Retreat(){
  MotorsStop();
  EB.write(abs(EncPulseEB));
  DB.write(abs(EncPulseDB));
  EA.write(abs(EncPulseEA));
  DA.write(abs(EncPulseDA));
  while(EncPulseEB>1200 || EncPulseDA>1200 || EncPulseDB>1200 || EncPulseEA>1200){
    ReadToF();
    MoveBackwards(200);
    EncPulseEB=EB.read();
    EncPulseDB=DB.read();
    EncPulseEA=EA.read();
    EncPulseDA=DA.read();
    EncPulseAvg=(EncPulseEB+EncPulseDB+EncPulseEA+EncPulseDA)/4;
    CheckVictim();
  }
}


void TurnLeft(){
  Rotating=true;
  ResetEncoders();
  while(EncPulseEB<TurnDist || EncPulseDB<TurnDist || EncPulseEA<TurnDist || EncPulseDA<TurnDist){
    RotateLeft(200);
    UpdateEncoders();
    ReadToF();
    CheckVictim();
    CheckBackup();
  }
  if(Quadrant==1){
    Quadrant=4;
  } else if(Quadrant==2){
    Quadrant=3;
  } else if(Quadrant==3){
    Quadrant=1;
  } else if(Quadrant==4){
    Quadrant=2;
  }
  RelativeXY();
  Align();
  Rotating=false;
  ResetEncoders();
}


void TurnRight(){	
  Rotating=true;
  ResetEncoders();
  while(EncPulseEB<TurnDist || EncPulseDB<TurnDist || EncPulseEA<TurnDist || EncPulseDA<TurnDist){
    RotateRight(200);
    UpdateEncoders();
    ReadToF();
    CheckVictim();
    CheckBackup();
  }
  if(Quadrant==1){
    Quadrant=3;
  } else if(Quadrant==2){
    Quadrant=4;
  } else if(Quadrant==3){
    Quadrant=2;
  } else if(Quadrant==4){
    Quadrant=1;
  }
  RelativeXY();
  Align();
  Rotating=false;
  ResetEncoders();
}


void TurnBackwards(){
  if(ToFLeftCT>=ToFRightCT){
    TurnLeft();
    TurnLeft();
  } else {
    TurnRight();
    TurnRight();
  }
}


void CheckVictim(){
      ReadTemperature();
      ReadCams();
      if(TemperatureL>=AtmosphereL+VHeatThreshold && ToFLeftCT<300 && ((EncPulseAvg<=TileDist/2&&heatmap[currentfloor][PositionX][PositionY]==0)||(EncPulseAvg>TileDist/2&&heatmap[currentfloor][ForwardX][ForwardY]==0&&Rotating==false)||(Rotating==true&&heatmap[currentfloor][PositionX][PositionY]==0))){
        Victim(1, 1);
      } else if(TemperatureR>=AtmosphereR+VHeatThreshold && ToFRightCT<300 && ((EncPulseAvg<=TileDist/2&&heatmap[currentfloor][PositionX][PositionY]==0)||(EncPulseAvg>TileDist/2&&heatmap[currentfloor][ForwardX][ForwardY]==0&&Rotating==false)||(Rotating==true&&heatmap[currentfloor][PositionX][PositionY]==0))){
        Victim(1, 2);
      } else if((MVLeftChar==Decode_H || MVLeftChar==Decode_S || MVLeftChar==Decode_U) && ToFLeftCT<300 && ToFLeftA<300 && ToFLeftB<300 && ((EncPulseAvg<=TileDist/2&&heatmap[currentfloor][PositionX][PositionY]==0)||(EncPulseAvg>TileDist/2&&heatmap[currentfloor][ForwardX][ForwardY]==0&&Rotating==false)||(Rotating==true&&heatmap[currentfloor][PositionX][PositionY]==0&&(ToFLeftA+ToFLeftB)/2<(ToFRightA+ToFRightB)/2))){
        if(MVLeftChar==Decode_H){
          Victim(2, 1);
        }
        if(MVLeftChar==Decode_S){
          Victim(3, 1);
        }
        if(MVLeftChar==Decode_U){
          Victim(4, 1);
        }
      } else if((MVRightChar==Decode_H || MVRightChar==Decode_S || MVRightChar==Decode_U) && ToFRightCT<300 && ToFRightA<300 && ToFRightB<300 && ((EncPulseAvg<=TileDist/2&&heatmap[currentfloor][PositionX][PositionY]==0)||(EncPulseAvg>TileDist/2&&heatmap[currentfloor][ForwardX][ForwardY]==0&&Rotating==false)||(Rotating==true&&heatmap[currentfloor][PositionX][PositionY]==0&&(ToFRightA+ToFRightB)/2<(ToFLeftA+ToFLeftB)/2))){
        if(MVRightChar==Decode_H){
          Victim(2, 2);
        }
        if(MVRightChar==Decode_S){
          Victim(3, 2);
        }
        if(MVRightChar==Decode_U){
          Victim(4, 2);
        }
      }
}


void Victim(int type, int side){
  MotorsStop();
  delay(100);
  MotorsRelease();
  if(type==1){
    DrawForegroundPic(1);
  } else if(type==2){
    DrawForegroundPic(2);
  } else if(type==3){
    DrawForegroundPic(3);
  } else if(type==4){
    DrawForegroundPic(4);
  }
  if(EncPulseAvg<=TileDist/2 || Rotating==true){
    heatmap[currentfloor][PositionX][PositionY]=1;
  } else {
    heatmap[currentfloor][ForwardX][ForwardY]=1;
  }
  if(side==1 && type!=4 && KitCounter>0){
    DeployKitLeft();
    if(type==2 && KitCounter>0){
      DeployKitLeft();
      delay(3200);
    } else {
      delay(4100);
    }
  } else if(side==2 && type!=4 && KitCounter>0){
    DeployKitRight();
    if(type==2 && KitCounter>0){
      DeployKitRight();
      delay(3200);
    } else {
      delay(4100);
    }
  } else {
  	delay(5000);
  }
  EraseForegroundPic();
}


void BlackZone(){
  Retreat();
  floodfill[currentfloor][ForwardX][ForwardY]=100;
}


void Ramp(){
  OnRamp=true;
  if(Inclination>105){
    DrawForegroundPic(5);
    while(Inclination>95 && ToFFrontCT>150){
      ReadIMU();
      if(Inclination>130){
      	MoveBackwards(200);
      	delay(500);
      }
      ReadToF();
      MoveForwardPID(250);
      CheckVictim();
    }
  } else if(Inclination<75){
    DrawForegroundPic(6);
    while(Inclination<85 && ToFFrontCT>150){
      ReadIMU();
      ReadToF();
      MoveForwardPID(200);
      CheckVictim();
    }
  }
  delay(300);
  MotorsStop();
  delay(100);
  MotorsRelease();
  EraseForegroundPic();
  if(currentfloor==0){
  	currentfloor=1;
  } else if(currentfloor==1){
  	currentfloor=0;
  }
  if(floodfill[currentfloor][BackwardsX][BackwardsY]==0){
  	floodfill[currentfloor][BackwardsX][BackwardsY]=1;
  }
  if(floodfill[currentfloor][PositionX][PositionY]==0){
    floodfill[currentfloor][PositionX][PositionY]=floodfill[currentfloor][BackwardsX][BackwardsY]+1;
  }
  OnRamp=false;
}



void NextMove(){
  Serial.println("next move");
  ReadReflectionPure();
  if(ReflectLeft>TrapLimit && ReflectRight>TrapLimit){
  	BlackZone();
  }
  ReadIMU();
  if(EncPulseAvg>=(TileDist/2)){
    MapDisplacement();
  }
  if(ToFLeftCT<300 && ToFRightCT<300 && ToFLeftA<300 && ToFRightA<300 && ToFFrontCT>300){
    if(Inclination>105 || Inclination<75){
      Ramp();
    }
  }
  Align();
  ReadReflectionPure();
  if(OnCheckpoint==true && (PositionX!=PositionXBackup||PositionY!=PositionYBackup||currentfloor!=currentfloorBackup)){
      MotorsStop();
      //delay(100);
      //MotorsRelease();
      UpdateBackup();
      DrawForegroundPic(8);
      delay(1000);
      EraseForegroundPic();
  }
  IsForwardAvailable=true;
  IsRightAvailable=true;
  IsLeftAvailable=true;
  IsBackwardsAvailable=true;
  if(ToFFrontCT<300 || floodfill[currentfloor][ForwardX][ForwardY]==100){
    IsForwardAvailable=false;
  }
  if(ToFLeftCT<300 || floodfill[currentfloor][LeftX][LeftY]==100){
    IsLeftAvailable=false;
  }
  if(ToFRightCT<300 || floodfill[currentfloor][RightX][RightY]==100){
    IsRightAvailable=false;
  }
  if(ToFBackCT<300 || floodfill[currentfloor][BackwardsX][BackwardsY]==100){
    IsBackwardsAvailable=false;
  }
  if(PositionX==15 && PositionY==15 && currentfloor==1 && (floodfill[currentfloor][ForwardX][ForwardY]>0||IsForwardAvailable==false) && (floodfill[currentfloor][RightX][RightY]>0||IsRightAvailable==false) && (floodfill[currentfloor][LeftX][LeftY]>0||IsLeftAvailable==false) && (floodfill[currentfloor][BackwardsX][BackwardsY]>0||IsBackwardsAvailable==false)){
    MotorsStop();
    //delay(100);
    //MotorsRelease();
    DrawForegroundPic(7);
    delay(10000);
    EraseForegroundPic();
  }
  MarkAccess();
  ProcessAccessKey();
  if(IsRightAvailable==true && floodfill[currentfloor][RightX][RightY]==0){
  	TurnRight();
  } else if(IsForwardAvailable==true && floodfill[currentfloor][ForwardX][ForwardY]==0){
  	//fwd
  } else if(IsLeftAvailable==true && floodfill[currentfloor][LeftX][LeftY]==0){
  	TurnLeft();
  } else if(IsRightAvailable==true && (IsForwardAvailable==false||abs(floodfill[currentfloor][RightX][RightY]-AccessKey)<=abs(floodfill[currentfloor][ForwardX][ForwardY]-AccessKey)) && (IsLeftAvailable==false||abs(floodfill[currentfloor][RightX][RightY]-AccessKey)<=abs(floodfill[currentfloor][LeftX][LeftY]-AccessKey)) && (IsBackwardsAvailable==false||abs(floodfill[currentfloor][RightX][RightY]-AccessKey)<=abs(floodfill[currentfloor][BackwardsX][BackwardsY]-AccessKey))){
    TurnRight();
  } else if(IsForwardAvailable==true && (IsLeftAvailable==false||abs(floodfill[currentfloor][ForwardX][ForwardY]-AccessKey)<=abs(floodfill[currentfloor][LeftX][LeftY]-AccessKey)) && (IsBackwardsAvailable==false||abs(floodfill[currentfloor][ForwardX][ForwardY]-AccessKey)<=abs(floodfill[currentfloor][BackwardsX][BackwardsY]-AccessKey))){
    //fwd
  } else if(IsLeftAvailable==true && (IsBackwardsAvailable==false||abs(floodfill[currentfloor][LeftX][LeftY]-AccessKey)<=abs(floodfill[currentfloor][BackwardsX][BackwardsY]-AccessKey))){
    TurnLeft();
  } else {
    TurnBackwards();
  }
}
