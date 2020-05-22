#include <DueFlashStorage.h>
DueFlashStorage dueFlashStorage;
#include "Map.h"
byte accessmap[2][30][30] = {0};
byte wallmap[2][30][30] = {0};
int AccessKey=0;

void EraseAccessMap(){
	for(int r=0; r<30; r++){
		for(int c=0; c<30; c++){
			accessmap[currentfloor][c][r] = 0;
		}
	}
}

void UpdateBackup(){
  dueFlashStorage.write(0, PositionX);
  dueFlashStorage.write(1, PositionY);
  dueFlashStorage.write(2, currentfloor);
}

void CheckBackup(){
  if(digitalRead(SwitchPin) == LOW){
    PositionX = (int)dueFlashStorage.read(0);
    PositionY = (int)dueFlashStorage.read(1);
    currentfloor = (int)dueFlashStorage.read(2);
    EraseAccessMap();
    MotorsStop();
    MotorsRelease();
    ResetEncoders();
    PressToStart();
    //BackForth();
  }
}

void MarkAccess(){
  if(IsForwardAvailable==true && floodfill[currentfloor][ForwardX][ForwardY]==0){
    accessmap[currentfloor][ForwardX][ForwardY] = floodfill[currentfloor][PositionX][PositionY];
  }
  if(IsRightAvailable==true && floodfill[currentfloor][RightX][RightY]==0){
    accessmap[currentfloor][RightX][RightY] = floodfill[currentfloor][PositionX][PositionY];
  }
  if(IsLeftAvailable==true && floodfill[currentfloor][LeftX][LeftY]==0){
    accessmap[currentfloor][LeftX][LeftY] = floodfill[currentfloor][PositionX][PositionY];
  }
  int wallmapTemp = 1;
  if(IsForwardAvailable==true){
    if(Quadrant==1){
      wallmapTemp *= 2;
    } else if(Quadrant==2){
      wallmapTemp *= 3;
    } else if(Quadrant==3){
      wallmapTemp *= 5;
    } else if(Quadrant==4){
      wallmapTemp *= 7;
    }
  }
  if(IsRightAvailable==true){
    if(Quadrant==1){
      wallmapTemp *= 5;
    } else if(Quadrant==2){
      wallmapTemp *= 7;
    } else if(Quadrant==3){
      wallmapTemp *= 3;
    } else if(Quadrant==4){
      wallmapTemp *= 2;
    }
  }
  if(IsLeftAvailable==true){
    if(Quadrant==1){
      wallmapTemp *= 7;
    } else if(Quadrant==2){
      wallmapTemp *= 5;
    } else if(Quadrant==3){
      wallmapTemp *= 2;
    } else if(Quadrant==4){
      wallmapTemp *= 3;
    }
  }
  if(IsBackwardsAvailable==true){
    if(Quadrant==1){
      wallmapTemp *= 3;
    } else if(Quadrant==2){
      wallmapTemp *= 2;
    } else if(Quadrant==3){
      wallmapTemp *= 7;
    } else if(Quadrant==4){
      wallmapTemp *= 5;
    }
  }
  if(wallmap[currentfloor][PositionX][PositionY]==0){
  	wallmap[currentfloor][PositionX][PositionY] = wallmapTemp;
  } else if(wallmap[currentfloor][PositionX][PositionY]!=wallmapTemp){
  	EraseAccessMap();
  }
  int addressTemp = 3;
  addressTemp = 3+(900*currentfloor)+(30*PositionX)+(PositionY);
  dueFlashStorage.write(addressTemp, floodfill[currentfloor][PositionX][PositionY]);
  dueFlashStorage.write(addressTemp+2000, heatmap[currentfloor][PositionX][PositionY]);
  addressTemp = 3+(900*currentfloor)+(30*ForwardX)+(ForwardY);
  if(dueFlashStorage.read(addressTemp) != 255){
    floodfill[currentfloor][ForwardX][ForwardY] = dueFlashStorage.read(addressTemp);
  }
  if(dueFlashStorage.read(addressTemp+2000) != 255){
    heatmap[currentfloor][ForwardX][ForwardY] = dueFlashStorage.read(addressTemp+2000);
  }
  addressTemp = 3+(900*currentfloor)+(30*RightX)+(RightY);
  if(dueFlashStorage.read(addressTemp) != 255){
    floodfill[currentfloor][RightX][RightY] = dueFlashStorage.read(addressTemp);
  }
  if(dueFlashStorage.read(addressTemp+2000) != 255){
    heatmap[currentfloor][RightX][RightY] = dueFlashStorage.read(addressTemp+2000);
  }
  addressTemp = 3+(900*currentfloor)+(30*LeftX)+(LeftY);
  if(dueFlashStorage.read(addressTemp) != 255){
    floodfill[currentfloor][LeftX][LeftY] = dueFlashStorage.read(addressTemp);
  }
  if(dueFlashStorage.read(addressTemp+2000) != 255){
    heatmap[currentfloor][LeftX][LeftY] = dueFlashStorage.read(addressTemp+2000);
  }
  addressTemp = 3+(900*currentfloor)+(30*BackwardsX)+(BackwardsY);
  if(dueFlashStorage.read(addressTemp) != 255){
    floodfill[currentfloor][BackwardsX][BackwardsY] = dueFlashStorage.read(addressTemp);
  }
  if(dueFlashStorage.read(addressTemp+2000) != 255){
    heatmap[currentfloor][BackwardsX][BackwardsY] = dueFlashStorage.read(addressTemp+2000);
  }
}


void ProcessAccessKey(){
  AccessKey = 0;
  if((IsForwardAvailable==false||floodfill[currentfloor][ForwardX][ForwardY]>0)&&(IsRightAvailable==false||floodfill[currentfloor][RightX][RightY]>0)&&(IsLeftAvailable==false||floodfill[currentfloor][LeftX][LeftY]>0)&&(IsBackwardsAvailable==false||floodfill[currentfloor][BackwardsX][BackwardsY]>0)){
    for(int r=0; r<30; r++){
      for(int c=0; c<30; c++){
        if(floodfill[currentfloor][c][r]==0 && accessmap[currentfloor][c][r]>0 && abs(accessmap[currentfloor][c][r]-floodfill[currentfloor][PositionX][PositionY])<=abs(AccessKey-floodfill[currentfloor][PositionX][PositionY])){
          AccessKey = accessmap[currentfloor][c][r];
        }
      }
    }
  }
}
