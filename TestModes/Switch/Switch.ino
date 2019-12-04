#define SwitchPin 23

void setup() {
  Serial.begin(9600);
  pinMode(SwitchPin, INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(SwitchPin));
}
