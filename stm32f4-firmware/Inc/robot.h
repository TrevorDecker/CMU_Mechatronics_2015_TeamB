/* robot.h */
#ifndef __ROBOT_H
#define __ROBOT_H

#include "logicValues.h"
#include "settings.h" 
#include "gripper.h"
#include "cleaner.h"
#include "extension.h"
#include "vnh5019.h"

//robots position is defined to be left gripper posistion 
typedef struct robot{
  gripper_state_t leftGripper;
  gripper_state_t rightGripper;
  cleaner_state_t cleaner;
  extension_state_t extensionSystem;
} robot_state_t;

typedef struct window{
  double height;
  double width;
  robot_state_t robot;
} window_state_t;

//methods 
void error(const char* thisError);
int moveRightGripperToHeight(window_state_t *window,double newHeight);
int moveLeftGripperToHeight(window_state_t *window,double newHeight);
robot_state_t init_robot();
double gripper_max_height_one_motion(gripper_state_t * thisGripper,gripper_state_t* otherGripper);
double gripper_minHeight_one_motion(gripper_state_t * thisGripper,gripper_state_t* otherGripper);

//high level methods 
window_state_t attach_to_window();
int cleanWindow(window_state_t* window);
void release_from_window(window_state_t *window);


#endif /*__ROBOT_H */
