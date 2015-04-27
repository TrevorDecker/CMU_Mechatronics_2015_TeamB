//extensionSystem.c

#include "extension.h"

// *******************************************
// ********    Extension Arm Code   **********
// *******************************************

  //TODO
//blocking function 
int home_extension(extension_state_t *state)
{
  //stopGripping on a side 
  return FALSE;
} 

void extendTo(extension_state_t *state,double newExtension){
  //TODO
}

inline double getCurrentExtension(extension_state_t *state)
{
  return state->currentExtension;
}

inline double getDesiredExtension(extension_state_t *state)
{
  return state->desiredExtension;
}

