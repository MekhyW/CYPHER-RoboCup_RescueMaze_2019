#define Decode_H 72
#define Decode_S 83
#define Decode_U 85
#define Decode_Red 82
#define Decode_Yellow 89
#define Decode_Green 71
#define Decode_n 110
int MVLeftChar=0;
int MVRightChar=0;

void CamsInitialize(){
  Serial1.begin(9600);
  Serial3.begin(9600);
}

void ReadCams(){
  while(Serial1.available()){
    MVLeftChar = Serial1.read(); 
  }
  while(Serial3.available()){
    MVRightChar = Serial3.read(); 
  }
}
