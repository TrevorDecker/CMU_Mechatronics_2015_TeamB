//extensionSystem
#ifndef _EXTENSION_SYSTEM_H__
#define _EXTENSION_SYSTEM_H__

#include "logicValues.h"
#include "vnh5019.h"
#include "settings.h"
//structure defintion 
typedef struct extension_state{
  //TODO extension_sensor 
  double zero_offset;
  double desiredExtension;
  double currentExtension;
  //minum possible extension for the robot in meters
  double minextension; 
  //maximum possible extension for the robot in meters
  double maxextension;
  vnh5019_state_t extensionMotor;
} extension_state_t;

//methods 
//blocking function
void extensionInit(extension_state_t *state);
int homeExtension(extension_state_t *state);
void extendTo(extension_state_t *state, double newExtension);
double getCurrentExtension(extension_state_t *state);
double getDesiredExtension(extension_state_t *state);
void setZeroOffset(extension_state_t *state,double newOffset);
double getZeroOffset(extension_state_t *state);

#endif //_EXTENSION_SYSTEM_H__
