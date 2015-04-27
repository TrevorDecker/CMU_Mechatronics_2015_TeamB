//extensionSystem
#ifndef _EXTENSION_SYSTEM_H__
#define _EXTENSION_SYSTEM_H__

#include "logicValues.h"

//structure defintion 
typedef struct extension_state{
  double desiredExtension;
  double currentExtension;
  //minum possible extension for the robot in meters
  double minextension; 
  //maximum possible extension for the robot in meters
  double maxextension;
} extension_state_t;

//methods 
//blocking function 
int home_extension(extension_state_t *state);
void extend_to(extension_state_t *state, double newExtension);
double get_current_extension(extension_state_t *state);
double get_desired_extension(extension_state_t *state);

#endif //_EXTENSION_SYSTEM_H__
