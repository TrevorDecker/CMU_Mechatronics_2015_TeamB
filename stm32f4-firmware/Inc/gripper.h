//gripper.h 

#ifndef _GRIPPER_H__
#define _GRIPPER_H__

#include "logicValues.h"
#include "settings.h"
//structrue defnition
typedef enum gripper_status{
  GRIPPED,
  GRIPPING,
  RELEASED,
  RELEASING,
  ERRORS
} gripper_status_t;

typedef struct gripperSystem{
  gripper_status_t state;
  double curentAngleRobotFrame;
  double desiredAngleRobotFrame;
  double x;
  double y;
} gripper_state_t;

//methods 
void gripper_set_x(gripper_state_t *gripper,double newX);
void gripper_set_y(gripper_state_t *gripper,double newY);
double gripper_get_x(gripper_state_t *gripper);
double gripper_get_y(gripper_state_t *gripper);
int lockGripper(gripper_state_t *state);
int unlockGripper(gripper_state_t *state);
int rotateGripper(gripper_state_t *state,double amountToRotate);
int rotateGripperTo(gripper_state_t *state,double angleToRotateTo);
double isGripperMotionDone(gripper_state_t *state);
#endif //_GRIPPER_H__
