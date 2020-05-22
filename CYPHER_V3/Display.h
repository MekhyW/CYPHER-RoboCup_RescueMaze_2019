#include <Nextion.h>
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
NexPage dropping_left = NexPage(10, 0, "dropping_left");
NexPage dropped_left = NexPage(11, 0, "dropped_left");
NexPage dropping_right = NexPage(12, 0, "dropping_right");
NexPage dropped_right = NexPage(13, 0, "dropped_right");
NexPicture arrow = NexPicture(9, 2, "arrow");
NexNumber n0 = NexNumber(9, 3, "n0");
NexNumber n1 = NexNumber(9, 4, "n1");


void DrawForegroundPic(int id){
    if(id==1){
      heated_victim.show();
    } else if(id==2){
      H_victim.show();
    } else if(id==3){
      S_victim.show();
    } else if(id==4){
      U_victim.show();
    } else if(id==5){
      ramp_up.show();
    } else if(id==6){
      ramp_down.show();
    } else if(id==7){
      Exit.show();
    } else if(id==8){
      checkpoint.show();
    } else if(id==9){
      standby.show();
    } else if(id==10){
      dropping_left.show();
    } else if(id==11){
      dropped_left.show();
    } else if(id==12){
      dropping_right.show();
    } else if(id==13){
      dropped_right.show();
    }
}


void EraseForegroundPic(){
  Map.show();
}

void DisplayInitialize(){
  nexInit();
}
