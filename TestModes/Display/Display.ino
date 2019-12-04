//softwareserial library included in nextion config.h
#include <Nextion.h>
//SoftwareSerial HMISerial(25, A10);
NexPage Map = NexPage(0, 0, "Map");
NexPage heated_victim = NexPage(1, 0, "heated_victim");
NexPage H_victim = NexPage(2, 0, "H_victim");
NexPage S_victim = NexPage(3, 0, "S_victim");
NexPage U_victim = NexPage(4, 0, "U_victim");
NexPage ramp_up = NexPage(5, 0, "ramp_up");
NexPage ramp_down = NexPage(6, 0, "ramp_down");
NexPage Exit = NexPage(7, 0, "Exit");
NexPage checkpoint = NexPage(8, 0, "checkpoint");
NexPage standby = NexPage(9, 0, "standby");
NexPicture arrow = NexPicture(9, 2, "arrow");
NexProgressBar ToF1  = NexProgressBar(9, 3, "ToF1");
NexProgressBar ToF2  = NexProgressBar(9, 4, "ToF2");
NexProgressBar ToF3  = NexProgressBar(9, 5, "ToF3");
NexProgressBar ToF4  = NexProgressBar(9, 6, "ToF4");
NexProgressBar ToF5  = NexProgressBar(9, 7, "ToF5");
NexProgressBar ToF6  = NexProgressBar(9, 8, "ToF6");
NexProgressBar ToF7  = NexProgressBar(9, 9, "ToF7");
NexProgressBar ToF8  = NexProgressBar(9, 10, "ToF8");
NexProgressBar ToF9  = NexProgressBar(9, 11, "ToF9");
NexProgressBar ToF10  = NexProgressBar(9, 12, "ToF10");
NexProgressBar ToF11  = NexProgressBar(9, 13, "ToF11");
NexProgressBar ToF12  = NexProgressBar(9, 14, "ToF12");
NexProgressBar inclination  = NexProgressBar(9, 15, "inclination");
NexProgressBar reflectleft  = NexProgressBar(9, 16, "reflectleft");
NexProgressBar reflectright  = NexProgressBar(9, 17, "reflectright");
NexProgressBar tempL  = NexProgressBar(9, 18, "tempL");
NexProgressBar tempR  = NexProgressBar(9, 19, "tempR");
NexProgressBar angle  = NexProgressBar(9, 20, "angle");


void setup() {
  Serial.begin(9600);
  nexInit();
  checkpoint.show();
  delay(2000);
  standby.show();
}

void loop() {
  delay(50);
  angle.setValue(random(0, 100));
  Serial.println(millis());
}
