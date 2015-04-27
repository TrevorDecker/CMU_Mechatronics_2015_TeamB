
// ****************************************
// *********   Cleaner Code ***************
// ****************************************

//move the cleaning unit left until left limit is reached with cleaner on the window
int cleanLeft(){
  //TODO
}

//move the cleaning unit right until right limit is reached with cleaner on window
int cleanRight(){
  //TODO
}

//move the cleaning unit left until left limit is reached with cleaner not on the window
int moveCleanerLeft(){
  //TODO

}

//move the cleaning unit right until right limit is reached with cleaner not on the window
int moveCleanerRight(){
  //TODO
}

//moves the cleaning unit onto the window so that it is touching
int cleanerToWindow(){
  //TODO
}

//move the cleaner away from the window so that it is not touching the window
int cleanerOffWindow(){
  //TODO
}

//moves the cleaner away from the window so that the robot can clear the window frame 
int cleanerClearWindow(){
  //TODO
}

//move cleaner left and right a predetermined number of times which should leave the window cleaned 
int cleanThisLevel(){
  moveCleanerLeft();
  for(int pass = 0;pass<3;pass++){
    cleanRight();
    cleanLeft();
  }
}


void  cleanTo(double pointToCLeanTo){
    //TODO
}

int cleanTo_blocking(double pointToCleanTo){
  //TODO
}
  
