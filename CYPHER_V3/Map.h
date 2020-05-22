#define SwitchPin 23
#define ImpactSensorLeft 22
#define ImpactSensorRight 24
byte heatmap[2][30][30] = {0};
byte floodfill[2][30][30] = {0};
bool IsForwardAvailable=true;
bool IsRightAvailable=true;
bool IsLeftAvailable=true;
bool IsBackwardsAvailable=true;
int currentfloor=1;
int PositionX = 15;
int PositionY = 15;
int ForwardX=15;
int ForwardY=16;
int LeftX=14;
int LeftY=15;
int RightX=16;
int RightY=15;
int BackwardsX=15;
int BackwardsY=14;
bool Rotating=false;


void PressToStart(){
  DrawForegroundPic(9);
  arrow.setPic(Quadrant);
  pinMode(SwitchPin, INPUT_PULLUP);
  pinMode(ImpactSensorLeft, INPUT_PULLUP);
  pinMode(ImpactSensorRight, INPUT_PULLUP);
	while(digitalRead(SwitchPin) == HIGH){
		ReadIMU();
    n0.setValue(Inclination);
	}
  while(digitalRead(SwitchPin) == LOW){
    ReadIMU();
    n0.setValue(Inclination);
  }
  OnCheckpoint=true;
  EraseForegroundPic();
}


void RelativeXY(){
  if(Quadrant==1){
    LeftX=PositionX;
    LeftY=PositionY-1;
    RightX=PositionX;
    RightY=PositionY+1;
    ForwardX=PositionX-1;
    ForwardY=PositionY;
    BackwardsX=PositionX+1;
    BackwardsY=PositionY;
  } else if(Quadrant==2){
    LeftX=PositionX;
    LeftY=PositionY+1;
    RightX=PositionX;
    RightY=PositionY-1;
    ForwardX=PositionX+1;
    ForwardY=PositionY;
    BackwardsX=PositionX-1;
    BackwardsY=PositionY;
  } else if(Quadrant==3){
    LeftX=PositionX-1;
    LeftY=PositionY;
    RightX=PositionX+1;
    RightY=PositionY;
    ForwardX=PositionX;
    ForwardY=PositionY+1;
    BackwardsX=PositionX;
    BackwardsY=PositionY-1;
  } else if(Quadrant==4){
    LeftX=PositionX+1;
    LeftY=PositionY;
    RightX=PositionX-1;
    RightY=PositionY;
    ForwardX=PositionX;
    ForwardY=PositionY-1;
    BackwardsX=PositionX;
    BackwardsY=PositionY+1;
  }
}

void MapDisplacement(){
    if(Quadrant==1){
      PositionX--;
    } else if(Quadrant==2){
      PositionX++;
    } else if(Quadrant==3){
      PositionY++;
    } else if(Quadrant==4){
      PositionY--;
    }
    RelativeXY();
    if(floodfill[currentfloor][PositionX][PositionY]==0){
      floodfill[currentfloor][PositionX][PositionY]=floodfill[currentfloor][BackwardsX][BackwardsY]+1;
    }
}
