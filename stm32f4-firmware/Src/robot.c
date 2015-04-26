/*
   robot.c 
   class which tracks and controls the robots stat/*
   Author: Trevor Decker
   Last Updated: 4/23/2015
   Version: 0
   ChangeLog: NONE
*/



  // X runs left to right parllel to the floor
  // Y run top to bottom with possitive towards the ground
  // Z run towards the window with possitive towards the window
  
#include "robot.h"
#include <stdio.h>

//TODO move somewhre else 
void error(const char* this_error){
  //TODO report to string 
  printf("ERROR: %s \n",this_error);
}



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
  
void  moveCleanerTo(double pointToCleanTo){
    //TODO
  }

int moveCleanerTo_blcoking(double pointToCleanTo){
  //TODO
}

int   homeCleaner(){
    //TODO
  }

// *******************************************
// ********    Extension Arm Code   **********
// *******************************************

  //TODO
int homeExtensionArm()
{
    //stopGripping on a side 
} 

void extendTo(double newExtension){
  //TODO
}

//extend/contract the arm by delta meters
void extendBy(double extensionDelta){
  //TODO
}

int extendTo_blocking(double newExtension){
  //TODO
}

double getCurrentExtension()
{
  //TODO
}

double getDesiredExtension()
{
  //TODO 
}

// *******************************************
// **********   Gripper Code *****************
// *******************************************
int lockRightGripper(){
  //todo
}

int lockLeftGripper(){
  //TODO
}

//release the right side gripper 
int unlockRightGripper(){
  if(leftGripper.state != RELEASED){
    error("Tried to let go of both sides of the window");
    return -1;
  }
  //TODO 
  return TRUE;
}

//releases the left side gripper
int unlockLeftGripper(){
  if(rightGripper.state != RELEASED){
    error("Tried to let go of both sides of the window");
    return -1;
  }
  //TODO 
  return TRUE;
}

//rotates the left gripper a desired amount
int rotateLeftGripper(double amountToRotate)
{
  //TODO
  return FALSE;
}

//rotates the right gripper a desired amount
int roateRightGripper(double amountToRoate)
{
  //TODO
  return FALSE;
}

//rotates the left gripper to a desried posistion
int roateLeftGripperTo(double angleToRotateTo)
{
  //TODO
  return FALSE;
}

//roates the right gripper to a desried position
int rotateRightGripperTo(double angleToRotateTo)
{
  //TODO
  return FALSE;
}

//gets the gripper angle in world frame
double getLeftGripperAngleWorld()
{
  //TODO
  return -1;
}

double getRightGripperAngleWorld()
{
  //TODO
  return -1;
}


// ******************************************
// *********** Multi subsystem code *********
// *****************************************


//Robot will end with both grippers locked 
int moveRightGripperToHeight(double newHeight){
  //TODO check to see if right gripper is within range of robot's current posistion, if it is not return an error 
  lockLeftGripper();
  unlockRightGripper();

  while(FALSE)       //TODO fix, should be not at the correct height 
    {
      roateRightGripper(0);  //TODO set rotation amount for each step
      extendBy(0);           //TODO set amount to extend by for each step 
    }
  lockRightGripper();
  return TRUE;
}

//Robot will end with both grippers lcoked
int moveLeftGripperToHeight(double newHeight){
  //TODO check to see if left gripper is within range of the robot's current position, if it is not return an error
  lockRightGripper();
  unlockLeftGripper();
  while(FALSE) //TODO fix, should be not at the correct hegiht
    {
      rotateLeftGripper(0); //TODO set rotation amount for each step 
      extendBy(0);          //TODO set amount to extend by for each step
    }
  lockLeftGripper();
  return TRUE;
}


//TODO
void moveToHeight()
{
  
}

//TODO
int moveToHeight_blocking()
{

  return FALSE;  
}

