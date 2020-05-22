#define ReflectionAPin A6
#define ReflectionBPin A7
#define TrapLimit 600
bool OnCheckpoint=true;
float WhiteAvgGlobal=0;
int WhiteAvgGlobalDenominator=0;
float WhiteAvgLocal=0;
int WhiteAvgLocalDenominator=0;
float ReflectLeft=100;
float ReflectRight=100;

void ReflectionInitialize(){
	pinMode(ReflectionAPin, INPUT);
	pinMode(ReflectionBPin, INPUT);
}

void ReadReflection(){
  ReflectLeft = (analogRead(ReflectionAPin)*0.7)+(ReflectRight*0.3);
  ReflectRight = (analogRead(ReflectionBPin)*0.7)+(ReflectLeft*0.3);
  if(ReflectLeft<=(TrapLimit/4) && ReflectRight<=(TrapLimit/4)){
    WhiteAvgGlobalDenominator++;
    WhiteAvgGlobal = ((WhiteAvgGlobal*(WhiteAvgGlobalDenominator-1))+((ReflectLeft+ReflectRight)/2))/WhiteAvgGlobalDenominator; 
  }
  if(EncPulseAvg >= TileDist/2){
    WhiteAvgLocalDenominator++;
    WhiteAvgLocal = ((WhiteAvgLocal*(WhiteAvgLocalDenominator-1))+((ReflectLeft+ReflectRight)/2))/WhiteAvgLocalDenominator; 
  }
  OnCheckpoint=false;
  if(WhiteAvgLocal < (WhiteAvgGlobal*0.8)){
    OnCheckpoint=true;
  }
}
