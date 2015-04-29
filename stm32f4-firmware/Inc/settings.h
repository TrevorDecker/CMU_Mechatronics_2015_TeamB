//settings.h where all of the settings for the robot will be #defined 
#ifndef _SETTINGS_H__
#define _SETTINGS_H__

//////////////////////////////////////////////////
///////////////ROBOT AND WINDOW VALUES ///////////
//////////////////////////////////////////////////
#define DEFAULT_WINDOW_HEIGHT 1//meters 
#define DEFAULT_WINDOW_WIDTH  1//meters 
#define MOVE_DOWN_BETWEEN_CLEANS .15 //meters (6in)
 //meters diffrence between left and right gripper to be considered level 
#define LEVEL_THREASHOLD .1
#define ROBOT_HEIGHT .15 //meters 

#define USER_BTN_GPIO -1
#define USER_BTN_GPIO_PIN -1
//paramaters of the robot ie the size of the robot
///////////////////////////////////////////////////
///////////////  CLEANER VALUES //////////////////
////////////////////////////////////////////////// 
#define CLEANER_SPEED 128
#define CLEANER_LEFT 1
#define CLEANER_RIGHT 0

#define CLEANER_TOWEL_TOTAL_LENGTH 100
#define CLEANER_MIN_POSITION_ALONG_ARM 0
#define CLEANER_MAX_POSITION_ALONG_ARM 2
#define CLEANER_MIN_POSITION_APPROACH 0
#define CLEANER_MAX_POSITION_APPROACH 1

#define CLEANER_ERROR_THRESHOLD 0

#define CLEANER_P 0
#define CLEANER_I 0
#define CLEANER_D 0

////////////////////////////////////////////////
//////////////  EXTENSION SYSTEM //////////////
//////////////////////////////////////////////
#define MAX_EXTENSION 2
#define MIN_EXTENSION 1
//point at which error in extension is considred 0 
#define EXTENSION_THREASHOLD 0.1   

#define EXTENSION_MOTOR_DIRECTION_A_PIN -1
#define EXTENSION_MOTOR_DIRECTION_B_PIN -1
#define EXTENSION_MOTOR_PWM_PIN -1
#define EXTENSION_SPEED 128
#define EXTENSION_INWARD 1
#define EXTENSION_OUTWARD 0 
#define DEFAULT_EXTENSION_ZERO_OFFSET 0

/////////////////////////////////////////////////
///////////  GRIPPER VALUES /////////////////////
////////////////////////////////////////////////
#define GRIPPER_THREASHOLD .1 
#define LEFT_GRIPPER_MAX_ANGLE 0
#define LEFT_GRIPPER_MIN_ANGLE 0
#define RIGHT_GRIPPER_MAX_ANGLE 0
#define RIGHT_GRIPPER_MIN_ANGLE 0

#define GRIPPER_LOCK_SPEED 128
#define GRIPPER_LOCK_DIRECTION 1
#define GRIPPER_CURRENT_SENSE_THREASHOLD 200

#define LEFT_GRIPPER_MOTOR_DIRECTION_A_PIN -1
#define LEFT_GRIPPER_MOTOR_DIRECTION_B_PIN -1
#define LEFT_GRIPPER_MOTOR_PWM_PIN -1

#define RIGHT_GRIPPER_MOTOR_DRIECTION_A_PIN -1
#define RIGHT_GRIPPER_MOTOR_DIRECTION_B_PIN -1
#define RIGHT_GRIPPER_MOTOR_PWM_PIN -1

#define DEFAULT_LEFT_GRIPPER_POSITION 0
#define DEFAULT_RIGHT_GRIPPER_POSITION 0

#define GRIPPER_P 0
#define GRIPPER_I 0
#define GRIPPER_D 0
#define GRIPPER_MAX_SPEED 0

//TODO define stepper motors pin 

#endif //_SETTINGS_H__
