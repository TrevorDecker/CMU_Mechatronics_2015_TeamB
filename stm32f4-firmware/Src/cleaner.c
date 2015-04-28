#include "cleaner.h"


// ****************************************
// *********   Cleaner Code ***************
// ****************************************

int  initCleaner(cleaner_state_t state,int direction_a_pin,int direction_b_pin,int pwm_pin){
  vnh5019_hw_assign_t hw_asign; //TODO populate
  vnh5019_init(&state.cleanerMotor,&hw_asign);
  
  //TODO 
}

//move the cleaning unit left until left limit is reached with cleaner on the window
//uses constant speed for the motor 
int cleanLeft(cleaner_state_t * state){
  //  while(btn_not_pressed){ TODO 
    vnh5019_set(&state->cleanerMotor,CLEANER_SPEED,CLEANER_LEFT);
    // delay(20); TODO 
    // }
    return TRUE;
}

//move the cleaning unit right until right limit is reached with cleaner on window
//uses constant speed for the motor
int cleanRight(cleaner_state_t * state){
  // while(btn_not_pressed){ TODO 
    vnh5019_set(&state->cleanerMotor,CLEANER_SPEED,CLEANER_RIGHT);
    //  }
    return TRUE;
}

//moves the cleaning unit onto the window so that it is touching
//blocking
int cleanerToWindow(cleaner_state_t* state){
  //TODO
}

//move the cleaner away from the window so that it is not touching the window
//blocking
int cleanerOffWindow(cleaner_state_t* state){
  //TODO
}

//moves the cleaner away from the window so that the robot can clear the window frame 
//blocking
int cleanerClearWindow(cleaner_state_t* state){
  //TODO
}

//move cleaner left and right a predetermined number of times which should leave the window cleaned 
//blocking 
int cleanThisLevel(cleaner_state_t* state){
  moveCleanerLeft(state);
  for(int pass = 0;pass<3;pass++){
    cleanRight(state);
    cleanLeft(state);
  }
}

//uses pid contorler 
//not blocking 
void  cleanTo(cleaner_state_t* state, double pointToCLeanTo){
    //TODO
}

int homeCleaner(cleaner_state_t* state){
  //TODO
}
