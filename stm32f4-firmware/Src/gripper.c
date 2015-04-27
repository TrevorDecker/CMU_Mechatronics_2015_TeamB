//gripper.c
#include "gripper.h"
#include "math.h"

// *******************************************
// **********   Gripper Code *****************
// *******************************************

inline void  gripper_set_x(gripper_state_t *gripper,double newX){
  gripper->x = newX;
}

inline void  gripper_set_y(gripper_state_t *gripper,double newY){
  gripper->y = newY;
} 

inline double gripper_get_x(gripper_state_t *gripper){
  return gripper->x;
}

inline double gripper_get_y(gripper_state_t *gripper){
  return gripper->y;
}

int lockGripper(gripper_state_t *state){
  //todo
  return FALSE;
}
//release the right side gripper 
int unlockGripper(gripper_state_t *state){
  //TODO
  return FALSE;
}

//rotates the gripper the desired amount 
int rotateGripper(gripper_state_t *state,double amountToRotate){
  //TODO 
  return FALSE;
}

int rotateGripperTo(gripper_state_t *state,double angleToRotateTo){
  //TODO
  return FALSE;
}

inline double  isGripperMotionDone(gripper_state_t *state)
{
  return abs(state->curentAngleRobotFrame - state->desiredAngleRobotFrame) < GRIPPER_THREASHOLD;
}

