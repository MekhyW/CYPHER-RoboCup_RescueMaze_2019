int MVLeftChar=0;
int MVLeftCharPrevious=0;
int MVRightChar=0;
int MVRightCharPrevious=0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial3.begin(9600);
}

void loop() {
  while(Serial1.available()){
    MVLeftChar = Serial1.read();
  }
  Serial.print(MVLeftChar);
  Serial.print("   ");
  while(Serial3.available()){
    MVRightChar = Serial3.read();
  }
  Serial.println(MVRightChar);
  delay(100);
}
