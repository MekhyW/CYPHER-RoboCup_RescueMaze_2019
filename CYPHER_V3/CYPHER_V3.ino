// CYPHER Robot V3
// Escola de Robótica ABC Marcelo Salles
// VERSION: 2.2
#include <Wire.h>
#include "IMU.h"
#include "Temperature.h"
#include "ToF.h"
#include "PID.h"
#include "Encoders.h"
#include "Reflection.h"
#include "Cameras.h"
#include "Display.h"
#include "Motors.h"
#include "Map_ADVANCED.h"
#include "Realsense.h"

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
  WhiteAvgLocal = 0;
  WhiteAvgLocalDenominator = 0;
  TileDistLocal = TileDist/cos(abs(90-Inclination)*0.0174);
  while(EncPulseEB<TileDistLocal || EncPulseDB<TileDistLocal || EncPulseEA<TileDistLocal || EncPulseDA<TileDistLocal){
    UpdateEncoders();
    ReadIMU();
    RelativeXY();
  	CheckBackup();
    ReadToF();
    if(ToFFrontCT<=150 || (ToFFrontA<=150 && ToFFrontB<=150)){
      break;
    }
    while(ToFLeftA<120 && ToFLeftB>120 && ToFFrontB>150 && ToFRightA>120){
    	WobbleLeft();
    	ReadToF();
    }
    while(ToFRightA<120 && ToFRightB>120 && ToFFrontA>150 && ToFLeftA>120){
    	WobbleRight();
    	ReadToF();
    }
    while(ToFFrontA<200 && ToFFrontCT>300 && ToFFrontB>300 && ToFRightA>120){
      WobbleLeft();
      ReadToF();
    }
    while(ToFFrontB<200 && ToFFrontCT>300 && ToFFrontA>300 && ToFLeftA>120){
      WobbleRight();
      ReadToF();
    }
    CheckVictim();
    if(digitalRead(ImpactSensorLeft)==LOW && ToFFrontCT>200 && floodfill[currentfloor][PositionX][PositionY]!=1){
      AvoidLeft();
    } else if(digitalRead(ImpactSensorRight)==LOW && ToFFrontCT>200 && floodfill[currentfloor][PositionX][PositionY]!=1){
      AvoidRight();
    }
    ReadReflection();
    if(ReflectLeft>TrapLimit && ReflectRight>TrapLimit){
      BlackZone();
      break;
    }
    MoveForwardPID(200);
  }
  NextMove();
}





void AlignFrontBack(){
  ResetEncoders();
  ReadToF();
  TargetEncAvg = map(ToFFrontCT - 150, -150, 150, -(TileDist/2), TileDist/2)/2;
  if(ToFFrontCT <= 300 && TargetEncAvg > 0){
    while(EncPulseAvg < TargetEncAvg){
      MoveForward(150);
      UpdateEncoders();
    } 
  } else if(ToFFrontCT <= 300 && TargetEncAvg < 0){
    while(EncPulseAvg < abs(TargetEncAvg)){
      MoveBackwards(150);
      UpdateEncoders();
    } 
  }
  TargetEncAvg = map(ToFFrontCT - 450, -150, 150, -(TileDist/2), TileDist/2)/2;
  if(ToFFrontCT <= 600 && ToFFrontCT>=300 && ToFFrontA <= 600 && ToFFrontA>=300 && ToFFrontB <= 600 && ToFFrontB>=300 && TargetEncAvg > 0){
    while(EncPulseAvg < TargetEncAvg){
      MoveForward(150);
      UpdateEncoders();
    } 
  } else if(ToFFrontCT <= 600 && ToFFrontCT>=300 && ToFFrontA <= 600 && ToFFrontA>=300 && ToFFrontB <= 600 && ToFFrontB>=300 && TargetEncAvg < 0){
    while(EncPulseAvg < abs(TargetEncAvg)){
      MoveBackwards(150);
      UpdateEncoders();
    } 
  }
  ResetEncoders();
  ReadToF();
  TargetEncAvg = map(150 - ToFBackCT, -150, 150, -(TileDist/2), TileDist/2)/2;
  if(ToFBackCT <= 300 && TargetEncAvg > 0){
    while(EncPulseAvg < TargetEncAvg){
      MoveForward(150);
      UpdateEncoders();
    } 
  } else if(ToFBackCT <= 300 && TargetEncAvg < 0){
    while(EncPulseAvg < abs(TargetEncAvg)){
      MoveBackwards(150);
      UpdateEncoders();
    } 
  }
  TargetEncAvg = map(450 - ToFBackCT, -150, 150, -(TileDist/2), TileDist/2)/2;
  if(ToFBackCT <= 600 && ToFBackCT>=300 && ToFBackA <= 600 && ToFBackA>=300 && ToFBackB <= 600 && ToFBackB>=300 && TargetEncAvg > 0){
    while(EncPulseAvg < TargetEncAvg){
      MoveForward(150);
      UpdateEncoders();
    } 
  } else if(ToFBackCT <= 600 && ToFBackCT>=300 && ToFBackA <= 600 && ToFBackA>=300 && ToFBackB <= 600 && ToFBackB>=300 && TargetEncAvg < 0){
    while(EncPulseAvg < abs(TargetEncAvg)){
      MoveBackwards(150);
      UpdateEncoders();
    } 
  }
}

void AlignAngle(){
  ResetEncoders();
  ReadToF();
  if(ToFRightA<300 && ToFRightCT<300 && ToFRightB<300){
  	  TargetEncAvg = map(atan2((ToFRightA-ToFRightB), 160)*57.296, -90, 90, -(TurnDist), TurnDist)/2;
  	  if(TargetEncAvg > 0){
  	  	while(EncPulseAvg < TargetEncAvg){
  	  		RotateRight(150);
  	  		UpdateEncoders();
  	  	}
  	  } else if(TargetEncAvg < 0){
  	  	while(EncPulseAvg < abs(TargetEncAvg)){
  	  		RotateLeft(150);
  	  		UpdateEncoders();
  	  	}
  	  }
  }
  if(ToFLeftA<300 && ToFLeftCT<300 && ToFLeftB<300){
  	  TargetEncAvg = map(atan2((ToFLeftA-ToFLeftB), 160)*57.296, -90, 90, -(TurnDist), TurnDist)/2;
  	  if(TargetEncAvg > 0){
  	  	while(EncPulseAvg < TargetEncAvg){
  	  		RotateLeft(150);
  	  		UpdateEncoders();
  	  	}
  	  } else if(TargetEncAvg < 0){
  	  	while(EncPulseAvg < abs(TargetEncAvg)){
  	  		RotateRight(150);
  	  		UpdateEncoders();
  	  	}
  	  }
  }
  if(ToFFrontA<300 && ToFFrontCT<300 && ToFFrontB<300){
  	  TargetEncAvg = map(atan2((ToFFrontA-ToFFrontB), 160)*57.296, -90, 90, -(TurnDist), TurnDist)/2;
  	  if(TargetEncAvg > 0){
  	  	while(EncPulseAvg < TargetEncAvg){
  	  		RotateRight(150);
  	  		UpdateEncoders();
  	  	}
  	  } else if(TargetEncAvg < 0){
  	  	while(EncPulseAvg < abs(TargetEncAvg)){
  	  		RotateLeft(150);
  	  		UpdateEncoders();
  	  	}
  	  }
  }
  if(ToFBackA<300 && ToFBackCT<300 && ToFBackB<300){
  	  TargetEncAvg = map(atan2((ToFBackA-ToFBackB), 160)*57.296, -90, 90, -(TurnDist), TurnDist)/2;
  	  if(TargetEncAvg > 0){
  	  	while(EncPulseAvg < TargetEncAvg){
  	  		RotateRight(150);
  	  		UpdateEncoders();
  	  	}
  	  } else if(TargetEncAvg < 0){
  	  	while(EncPulseAvg < abs(TargetEncAvg)){
  	  		RotateLeft(150);
  	  		UpdateEncoders();
  	  	}
  	  }
  }
}

void Align(){
  AlignAngle();
  AlignFrontBack();
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
    delay(40);
    MoveBackwards(200);
    delay(40);
    RotateLeft(200);
    delay(56);
    MoveForward(200);
    delay(40);
    UnlockEncoders();
}

void WobbleLeft(){
	LockEncoders();
	RotateLeft(200);
    delay(40);
    MoveBackwards(200);
    delay(40);
    RotateRight(200);
    delay(56);
    MoveForward(200);
    delay(40);
    UnlockEncoders();
}

void Retreat(){
  MotorsStop();
  EB.write(abs(EncPulseEB));
  DB.write(abs(EncPulseDB));
  EA.write(abs(EncPulseEA));
  DA.write(abs(EncPulseDA));
  EncPulseEB=EB.read();
  EncPulseDB=DB.read();
  EncPulseEA=EA.read();
  EncPulseDA=DA.read();
  EncPulseAvg=(EncPulseEB+EncPulseDB+EncPulseEA+EncPulseDA)/4;
  while(EncPulseAvg > 0){
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
        if(MVLeftChar==Decode_H || MVLeftChar==Decode_Red){
          Victim(2, 1);
        }
        if(MVLeftChar==Decode_S || MVLeftChar==Decode_Yellow){
          Victim(3, 1);
        }
        if(MVLeftChar==Decode_U || MVLeftChar==Decode_Green){
          Victim(4, 1);
        }
      } else if((MVRightChar==Decode_H || MVRightChar==Decode_S || MVRightChar==Decode_U) && ToFRightCT<300 && ToFRightA<300 && ToFRightB<300 && ((EncPulseAvg<=TileDist/2&&heatmap[currentfloor][PositionX][PositionY]==0)||(EncPulseAvg>TileDist/2&&heatmap[currentfloor][ForwardX][ForwardY]==0&&Rotating==false)||(Rotating==true&&heatmap[currentfloor][PositionX][PositionY]==0&&(ToFRightA+ToFRightB)/2<(ToFLeftA+ToFLeftB)/2))){
        if(MVRightChar==Decode_H || MVRightChar==Decode_Red){
          Victim(2, 2);
        }
        if(MVRightChar==Decode_S || MVRightChar==Decode_Yellow){
          Victim(3, 2);
        }
        if(MVRightChar==Decode_U || MVRightChar==Decode_Green){
          Victim(4, 2);
        }
      }
}


void Victim(int type, int side){
  MotorsStop();
  delay(100);
  MotorsRelease();
  if(type==1){
    for(int i=0; i<5; i++){
      DrawForegroundPic(1);
      delay(500);
      EraseForegroundPic();
      delay(500); 
    }
  } else if(type==2){
    for(int i=0; i<5; i++){
      DrawForegroundPic(2);
      delay(500);
      EraseForegroundPic();
      delay(500); 
    }
  } else if(type==3){
    for(int i=0; i<5; i++){
      DrawForegroundPic(3);
      delay(500);
      EraseForegroundPic();
      delay(500); 
    }
  } else if(type==4){
    for(int i=0; i<5; i++){
      DrawForegroundPic(4);
      delay(500);
      EraseForegroundPic();
      delay(500); 
    }
  }
  if(EncPulseAvg<=TileDist/2 || Rotating==true){
    heatmap[currentfloor][PositionX][PositionY]=1;
  } else {
    heatmap[currentfloor][ForwardX][ForwardY]=1;
  }
  if(side==1 && type!=4 && KitCounter>0){
    DrawForegroundPic(10);
    DeployKitLeft();
    if(type==2 && KitCounter>0){
      DeployKitLeft();
    }
    DrawForegroundPic(11);
    delay(1000);
  } else if(side==2 && type!=4 && KitCounter>0){
    DrawForegroundPic(12);
    DeployKitRight();
    if(type==2 && KitCounter>0){
      DeployKitRight();
    }
    DrawForegroundPic(13);
    delay(1000);
  }
  EraseForegroundPic();
}


void BlackZone(){
  Retreat();
  floodfill[currentfloor][ForwardX][ForwardY]=100;
}


void NextMove(){
  if(EncPulseAvg>=(TileDist/2)){
    MapDisplacement();
  }
  Align();
  if(OnCheckpoint==true && floodfill[currentfloor][ForwardX][ForwardY]!=100 && (PositionX!=(int)dueFlashStorage.read(0)||PositionY!=(int)dueFlashStorage.read(1)||currentfloor!=(int)dueFlashStorage.read(2))){
      MotorsStop();
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
    DrawForegroundPic(7);
    delay(10000);
    EraseForegroundPic();
  }
  MotorsStop();
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
