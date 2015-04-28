//extensionSystem.c

#include "extension.h"

// *******************************************
// ********    Extension Arm Code   **********
// *******************************************
void extensionInit(extension_state_t* state){
  vnh5019_hw_assign_t hw_asign; //TODO populate
  vnh5019_init(&state->extensionMotor,&hw_asign);
  setZeroOffset(state,DEFAULT_EXTENSION_ZERO_OFFSET);
  //TODO 
}

inline void setZeroOffset(extension_state_t *state,double newOffset){
  state->zero_offset = newOffset;
}

inline double getZeroOffset(extension_state_t *state){
  return state->zero_offset;
}
  
//TODO move to using the extension sensor as feedback 
//blocking function 
//assumes that only hooked on one side 
int homeExtension(extension_state_t *state)
{
  //extension is homed by moving the arm in, this is a design choice
  // and the arm could be homed by extending otwardard. We chose to 
  // extend inward as it produces a smaller moement on the gripper 
  //  while(btn_not_pressed){ TODO
    vnh5019_set(&state->extensionMotor,EXTENSION_SPEED,EXTENSION_INWARD);
    // }
  
  //TODO add zeroing peice  setZeroOffset(state,current_sensorReading)
  
 return FALSE;
} 

//uses pid 
//not blocking 
//assumes that only hooked on one side 
void extendTo(extension_state_t *state,double newExtension){
  //TODO
}

inline double getCurrentExtension(extension_state_t *state)
{
  return state->currentExtension;
}

inline double getDesiredExtension(extension_state_t *state)
{
  return state->desiredExtension;
}

