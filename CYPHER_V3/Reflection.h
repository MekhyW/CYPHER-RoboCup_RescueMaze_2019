#define ReflectionAPin A6
#define ReflectionBPin A7
#define TrapLimit 600
bool OnCheckpoint=true;
float WhiteAvg=0;
int WhiteAvgDenominator=0;
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
    WhiteAvgDenominator++;
    WhiteAvg = ((WhiteAvg*(WhiteAvgDenominator-1))+((ReflectLeft+ReflectRight)/2))/WhiteAvgDenominator; 
  }
}

void ReadReflectionPure(){
  ReflectLeft = analogRead(ReflectionAPin);
  ReflectRight = analogRead(ReflectionBPin);
  OnCheckpoint=false;
  if((ReflectLeft+ReflectRight)/2 <= (WhiteAvg*0.9)){
  	OnCheckpoint=true;
  }
}
