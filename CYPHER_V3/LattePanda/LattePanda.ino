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
int Command=99;
int LastCommand=0;

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
    for(int i=2; i<=13; i++){
      analogWrite(i, 0);
    }
    switch(Command){
      case 0:
        for(int i=2; i<=13; i++){
          analogWrite(i, 150);
        }
        break;
      case 1:
        for(int x=0; x<25; x++){
          analogWrite(LightUR_R, 150);
          analogWrite(LightUL_R, 150);
          analogWrite(LightLR_R, 150);
          analogWrite(LightLL_R, 150);
          delay(100);
          analogWrite(LightUR_R, 0);
          analogWrite(LightUL_R, 0);
          analogWrite(LightLR_R, 0);
          analogWrite(LightLL_R, 0);
          delay(100); 
        }
        break;
      case 2:
        for(int x=0; x<25; x++){
          analogWrite(LightUR_G, 150);
          analogWrite(LightUL_G, 150);
          analogWrite(LightLR_G, 150);
          analogWrite(LightLL_G, 150);
          delay(100);
          analogWrite(LightUR_G, 0);
          analogWrite(LightUL_G, 0);
          analogWrite(LightLR_G, 0);
          analogWrite(LightLL_G, 0);
          delay(100); 
        }
        break;
      case 3:
        for(int x=0; x<25; x++){
          analogWrite(LightUR_B, 150);
          analogWrite(LightUL_B, 150);
          analogWrite(LightLR_B, 150);
          analogWrite(LightLL_B, 150);
          delay(100);
          analogWrite(LightUR_B, 0);
          analogWrite(LightUL_B, 0);
          analogWrite(LightLR_B, 0);
          analogWrite(LightLL_B, 0);
          delay(100); 
        }
        break;
      case 4:
        for(int x=0; x<25; x++){
          for(int i=2; i<=13; i++){
            analogWrite(i, 150);
          }
          delay(200);
          for(int i=2; i<=13; i++){
            analogWrite(i, 0);
          }
          delay(200);
        }
        break;
    }
  }
  LastCommand = Command;
}
