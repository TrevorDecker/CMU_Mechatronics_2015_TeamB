//settings.h where all of the settings for the robot will be #defined 
#ifndef _SETTINGS_H__
#define _SETTINGS_H__

//settings of the robot 
#define DEFAULT_WINDOW_HEIGHT 1//meters 
#define DEFAULT_WINDOW_WIDTH  1//meters 
#define DEFAULT_LEFT_GRIPPER_POSITION 0
#define DEFAULT_RIGHT_GRIPPER_POSITION 0
#define MOVE_DOWN_BETWEEN_CLEANS .15 //meters (6in)
 //meters diffrence between left and right gripper to be considered level 
#define LEVEL_THREASHOLD .1

//paramaters of the robot ie the size of the robot 
#define ROBOT_HEIGHT .15 //meters 
#define GRIPPER_THREASHOLD .1 
#define LEFT_GRIPPER_MAX_ANGLE 0
#define LEFT_GRIPPER_MIN_ANGLE 0
#define RIGHT_GRIPPER_MAX_ANGLE 0
#define RIGHT_GRIPPER_MIN_ANGLE 0
#define MAX_EXTENSION 2
#define MIN_EXTENSION 1

#define LEFT_GRIPPER_MOTOR_DIRECTION_A_PIN -1
#define LEFT_GRIPPER_MOTOR_DIRECTION_B_PIN -1
#define LEFT_GRIPPER_MOTOR_PWM_PIN -1

#define RIGHT_GRIPPER_MOTOR_DRIECTION_A_PIN -1
#define RIGHT_GRIPPER_MOTOR_DIRECTION_B_PIN -1
#define RIGHT_GRIPPER_MOTOR_PWM_PIN -1

#define EXTENSION_MOTOR_DIRECTION_A_PIN -1
#define EXTENSION_MOTOR_DIRECTION_B_PIN -1
#define EXTENSION_MOTOR_PWM_PIN -1

//TODO define stepper motors pin 

#endif //_SETTINGS_H__
