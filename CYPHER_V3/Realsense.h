int incomingByte = 0;
byte realsensearray[10];
int NewPositionX = 15;
int NewPositionY = 15;

void ReadRealsense(){
	Serial.flush();
  	if (Serial.available() > 0){
    	Serial.readBytesUntil('\n', realsensearray, sizeof(realsensearray));
    	while (Serial.available() > 0){
      		incomingByte = Serial.read();
    	}
    	NewPositionX = realsensearray[0]-48;
    	if(realsensearray[1] != 45){
      		NewPositionX *= 10;
      		NewPositionX += realsensearray[1]-48;
      		NewPositionY = realsensearray[3]-48;
      		if(realsensearray[4] != 0){
        		NewPositionY *= 10;
        		NewPositionY += realsensearray[4]-48;
      		}
    	} else if(realsensearray[1] == 45){
      		NewPositionY = realsensearray[2]-48;
      		if(realsensearray[3] != 0){
        		NewPositionY *= 10;
        		NewPositionY += realsensearray[3]-48;
      		}
    	}
    	for (int x = 0; x < sizeof(realsensearray) / sizeof(realsensearray[0]); x++){
      		realsensearray[x] = 0;
    	}
    	if(NewPositionX >= 0){
      		PositionX = NewPositionX;
    	}
    	if(NewPositionY >= 0){
      		PositionY = NewPositionY;
    	}
	}
}