#define LightUR_R 0
#define LightUR_G 0
#define LightUR_B 0
#define LightUL_R 0
#define LightUL_G 0
#define LightUL_B 0
#define LightLR_R 0
#define LightLR_G 0
#define LightLR_B 0
#define LightLL_R 0
#define LightLL_G 0
#define LightLL_B 0
int Command=0;
int LastCommand=0;
int Brightness=150;

void Flash(int color, int side){
  if(color==4){
    
  } else if(side==1){
    if(color==1){
      
    } else if(color==2){
      
    } else if(color==3){
      
    }
  } else if(side==2){
    if(color==1){
      
    } else if(color==2){
      
    } else if(color==3){
      
    }
  }
}

void setup() {
  Serial.begin(9600);
  for(int i=2; i<=13; i++){
    pinMode(i, OUTPUT);
    analogWrite(i, 0);
  }
}

void loop() {
  while(Serial.available()){
    Command = Serial.read() - 48;  
    Serial.println(Serial.read());
  }
  if(Command != LastCommand){
    switch(Command){
      case 0:
        for(int i=2; i<=13; i++){
          analogWrite(i, Brightness);
        }
        break;
      case 1:
        Flash(1, 1);
        break;
      case 2:
        Flash(2, 1);
        break;
      case 3:
        Flash(3, 1);
        break;
      case 4:
        Flash(1, 2);
        break;
      case 5:
        Flash(2, 2);
        break;
      case 6:
        Flash(3, 2);
        break;
      case 7:
        Flash(4, 1); //ExitBonus
        break;
    }  
  }
  LastCommand = Command;
}
