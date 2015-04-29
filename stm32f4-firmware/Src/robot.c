/*
   robot.c 
   class which tracks and controls the robots stat/*
   Author: Trevor Decker
   Last Updated: 4/23/2015
   Version: 0
   ChangeLog: NONE
*/

//TODO add motor control 
//TODO add sensors
//TODO move to freeRTOS
//TODO clean up code
//TODO test  


  // X runs left to right parllel to the floor
  // Y run top to bottom with possitive towards the ground
  // Z run towards the window with possitive towards the window
  
#include "robot.h"
#include <stdio.h>

/*
//TODO use math abs instead once it gets linked in 
double abs(double input){
  if(input > 0){
    return input;
  }else{
    return -input;
  }
}

double min(double a,double b)
{
  if(a < b){
    return a;
  }else{
    return b;
  }
}

double max(double a,double b){
  if(a < b){
    return b;
  }else{
    return a;
  }
}
*/



//TODO move somewhere else 
void error(const char* thisError){
  //TODO report to string 
  printf("ERROR: %s \n",thisError);
}

//max height that the gripper can mvoe in one motion
double gripperMaxHeightOneMotion(gripper_state_t * thisGripper,gripper_state_t* otherGripper)
{
  //TODO
  return 0;
}

//min height that the grippper can move in one motion 
double gripperMinHeightOneMotion(gripper_state_t * thisGripper,gripper_state_t* otherGripper)
{
  //TODO
  return 0;
}

//Robot will end with both grippers locked 
int moveRightGripperToHeight(window_state_t *window,double newHeight){
  //check to see if the newHeight is within the range of the gripper 
  if(newHeight < 0 || newHeight > window->height){
    error("tried to move to a height that is not on the window \n");
    return FALSE;
  }
  
  double dy = newHeight - window->robot.rightGripper.y;
  double dth = atan2(dy,window->width);
  double newTh = window->robot.leftGripper.curentAngleRobotFrame + dth;
  double newExtension = dy/sin(dth);
  if(newExtension > MAX_EXTENSION){
    error("need to be able to extend to a length longer then the arm's max size \n");
    return FALSE;
  }else if(newExtension < MIN_EXTENSION){
    error("need to be able to extend to a length shorter then the arm's min size \n");
    return FALSE;
  }else if(newTh > LEFT_GRIPPER_MAX_ANGLE){
    error("need to be able to rotate past left gripper max angle \n");
    return FALSE;
  }else if(newTh < LEFT_GRIPPER_MIN_ANGLE){
    error("need to be able to rotate past left gripper min angle \n");
    return FALSE;
  }
  lockGripper(&window->robot.leftGripper);
  unlockGripper(&window->robot.rightGripper);

  extendTo(&window->robot.extensionSystem,newExtension);
  rotateGripperTo(&window->robot.leftGripper,newTh);
  //TODO block until all motion is done 
  lockGripper(&window->robot.rightGripper);
  return TRUE;
}

//Robot will end with both grippers locked 
int moveLeftGripperToHeight(window_state_t *window,double newHeight){
  //check to see if the newHeight is within the range of the gripper 
  if(newHeight < 0 || newHeight > window->height){
    error("tried to move to a height that is not on the window \n");
    return FALSE;
  }
  
  double dy = newHeight - window->robot.leftGripper.y;
  double dth = atan2(dy,window->width);
  double newTh = window->robot.rightGripper.curentAngleRobotFrame + dth;
  double newExtension = dy/sin(dth);
  if(newExtension > MAX_EXTENSION){
    error("need to be able to extend to a length longer then the arm's max size \n");
    return FALSE;
  }else if(newExtension < MIN_EXTENSION){
    error("need to be able to extend to a length shorter then the arm's min size \n");
    return FALSE;
  }else if(newTh > RIGHT_GRIPPER_MAX_ANGLE){
    error("need to be able to rotate past left gripper max angle \n");
    return FALSE;
  }else if(newTh < RIGHT_GRIPPER_MIN_ANGLE){
    error("need to be able to rotate past left gripper min angle \n");
    return FALSE;
  }
  lockGripper(&window->robot.rightGripper);
  unlockGripper(&window->robot.leftGripper);

  extendTo(&window->robot.extensionSystem,newExtension);
  rotateGripperTo(&window->robot.rightGripper,newTh);
  //TODO block until all motion is done 
  lockGripper(&window->robot.leftGripper);
  return TRUE;
}

//TODO add other sensors 
void moveToHeight(window_state_t * window,double newHeight)
{
  if(newHeight < 0 || newHeight > window->height){
    error("can not move to a height that is not on the window \n");
  }

  double dLeft = newHeight - window->robot.leftGripper.y;
  double dRight = newHeight - window->robot.rightGripper.y;
 
  while(abs(window->robot.leftGripper.y - newHeight) > LEVEL_THREASHOLD ||   
	abs(window->robot.rightGripper.y - newHeight) > LEVEL_THREASHOLD){
    //not at the desried height so lets move to it
    if(abs(dLeft) > abs(dRight)){
      //left is farther away so lets move it
      if(dLeft > 0){
	//want to move down 
	moveLeftGripperToHeight(window,min(newHeight,gripperMaxHeightOneMotion(&window->robot.leftGripper,&window->robot.rightGripper)));
      }else{
	//want to move up
	moveLeftGripperToHeight(window,max(newHeight,gripperMinHeightOneMotion(&window->robot.leftGripper,&window->robot.rightGripper)));
      }
    }else{
      //right is farther away so lets move it
      if(dRight >0){
	//want to move down 
	moveRightGripperToHeight(window,min(newHeight,gripperMaxHeightOneMotion(&window->robot.rightGripper,&window->robot.leftGripper)));
      }else{
	//want to move up 
	moveRightGripperToHeight(window,max(newHeight,gripperMinHeightOneMotion(&window->robot.rightGripper,&window->robot.leftGripper)));
      }
    }
  }//while 
} //function moveToHeight

//TODO setup all of the motors and sensors 
robot_state_t init_robot(){
  robot_state_t thisRobot;
  rotateGripperTo(&thisRobot.leftGripper,DEFAULT_LEFT_GRIPPER_POSITION);
  rotateGripperTo(&thisRobot.rightGripper,DEFAULT_RIGHT_GRIPPER_POSITION);
  homeCleaner(&thisRobot.cleaner);
  homeExtension(&thisRobot.extensionSystem);
  
  //TODO waits until all processes are done
  //while(1){  
  //   delay(10);
  //   }
  return thisRobot;
}


//walks throught the process of attaching the robot to the window 
//assumes that we are attaching to the top of the window 
window_state_t attach_to_window(){
  //TODO get input width and height from the user using a pot or touch screen
  window_state_t thisWindow;
  thisWindow.height = DEFAULT_WINDOW_HEIGHT;   //meters
  thisWindow.width  = DEFAULT_WINDOW_WIDTH;    //meters
  digital_input_state_t btn_state;
  digitalInputInit(&btn_state,USER_BTN_GPIO,USER_BTN_GPIO_PIN); 

  thisWindow.robot = init_robot();
  extendTo(&thisWindow.robot.extensionSystem,thisWindow.width);
  digitalInputButtonPressed(&btn_state);
  lockGripper(&thisWindow.robot.leftGripper);
  digitalInputButtonPressed(&btn_state);
  lockGripper(&thisWindow.robot.rightGripper);
  digitalInputButtonPressed(&btn_state);
  digitalInputRelease(&btn_state);
  return thisWindow;
}

//assumes that robot has already been attached to the window 
int cleanWindow(window_state_t *window){
  int atBottom = FALSE;
  while(!atBottom){
    cleanThisLevel(&window->robot.cleaner);
    if(window->robot.leftGripper.y+ROBOT_HEIGHT + MOVE_DOWN_BETWEEN_CLEANS < window->height){ 
      moveToHeight(window, window->robot.leftGripper.y + MOVE_DOWN_BETWEEN_CLEANS);
    }else{
      //move to the bottom of the window 
      moveToHeight(window,window->height - ROBOT_HEIGHT);
    }
  }
  cleanThisLevel(&window->robot.cleaner);
  return TRUE;
}

void release_from_window(window_state_t *window){
  digital_input_state_t btn_state;
  digitalInputInit(&btn_state,USER_BTN_GPIO,USER_BTN_GPIO_PIN); 
  digitalInputButtonPressed(&btn_state);
  unlockGripper(&window->robot.leftGripper);
  digitalInputButtonPressed(&btn_state); 
  unlockGripper(&window->robot.rightGripper);
  digitalInputRelease(&btn_state);
}
