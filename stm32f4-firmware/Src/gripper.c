//gripper.c
#include "gripper.h"
#include "math.h"
// *******************************************
// **********   Gripper Code *****************
// *******************************************
//@param gripper_state_t * gripper 
void gripper_init(gripper_state_t *gripper){
  vnh5019_hw_assign_t hw_assign;  //TODO set values
  vnh5019_init(&gripper->gripperMotor,&hw_assign);
  }

// @param gripper_state_t *gripper
// @param double newX
// @return void 
inline void  gripper_set_x(gripper_state_t *gripper,double newX){
  gripper->x = newX;
}

// @param gripper_state_t *gripper
// @param double newY
// @return void
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
  //STRETCH GOAL ADD time out 
  while(vnh5019_get_cs_value(&state->gripperMotor) < GRIPPER_CURRENT_SENSE_THREASHOLD)
    {
         //continue turning the gripper
      vnh5019_set(&state->gripperMotor,GRIPPER_LOCK_SPEED,GRIPPER_LOCK_DIRECTION);
    }
  return TRUE;
}
//release the right side gripper 
int unlockGripper(gripper_state_t *state){
  //STRETCH ADD time out
  while(vnh5019_get_cs_value(&state->gripperMotor) > GRIPPER_CURRENT_SENSE_THREASHOLD){
      //continue turning the gripper
    vnh5019_set(&state->gripperMotor,GRIPPER_LOCK_SPEED,!GRIPPER_LOCK_DIRECTION);
  }
  return TRUE;
}

//rotates the gripper the desired amount 
//blocks 
int rotateGripper(gripper_state_t *state,double amountToRotate){
  pid_state_t pid_state;
  pidInit(&pid_state,&state->gripperMotor,TRUE,GRIPPER_MAX_SPEED,amountToRotate,GRIPPER_THREASHOLD,GRIPPER_P,GRIPPER_I,GRIPPER_D);
  pid_block_until_goal_reached(&pid_state);
  releasePID(&pid_state);
  return TRUE;
}

//blocks
int rotateGripperTo(gripper_state_t *state,double angleToRotateTo){
  return rotateGripper(state,angleToRotateTo-state->curentAngleRobotFrame);
}

inline double  isGripperMotionDone(gripper_state_t *state)
{
  return abs(state->curentAngleRobotFrame - state->desiredAngleRobotFrame) < GRIPPER_THREASHOLD;
}
