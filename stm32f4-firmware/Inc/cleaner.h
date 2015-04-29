//cleaner.h

#ifndef _CLEANER_H__
#define _CLEANER_H__
//structure defintions 
#include "vnh5019.h"
#include "settings.h"
#include "logicValues.h"
#include "pid.h"
typedef struct cleanerSystem{
  //position of cleaner in arm frame
  double positionAlongArm; //distince along arm of robot
  double positionApproach; //distince cleaner is towards window
  double towelPosition; 
  vnh5019_state_t cleanerMotor;
  
  //what you want the cleaner state to be
  double desiredPositionAlongArm;
  double desiredPositionApproach;
  double desiredTowelPosition;
} cleaner_state_t;


//methods 
int cleanLeft(cleaner_state_t* state);
int cleanRight(cleaner_state_t* state);
int cleanerToWindow(cleaner_state_t*state);
int cleanerOffWindow(cleaner_state_t*state);
int clenaerClearWindow(cleaner_state_t*state);
int cleanThisLevel(cleaner_state_t*state);
void cleanTo(cleaner_state_t* state, double pointToCleanTo);
void moveCleanerTo(cleaner_state_t* state,double pointToClenaTo);
int  homeCleaner(cleaner_state_t* state);
#endif //_CLEANER_H__
