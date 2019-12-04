#define ImpactSensorLeft 22
#define ImpactSensorRight 24

void setup() {
  Serial.begin(9600);
  pinMode(ImpactSensorLeft, INPUT_PULLUP);
  pinMode(ImpactSensorRight, INPUT_PULLUP);
}

void loop() {
  Serial.print(digitalRead(ImpactSensorLeft));
  Serial.print("     ");
  Serial.println(digitalRead(ImpactSensorRight));
  delay(100);
}
