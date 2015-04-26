/* robot.h */
#ifndef __ROBOT_H
#define __ROBOT_H

//convince defintion of lgoic values 
#define TRUE 1
#define FALSE 0


typedef enum gripperState{
  GRIPPED,
  GRIPPING,
  RELEASED,
  RELEASING,
  ERRORS
} gripperState_t;

typedef struct gripperSystem{
  gripperState_t state;
  double anngleRobotFrame;

  //system variables
  double maxAngle; //in robot frame
  double minAngle; //in robot frame
} gripperSystem_t;

typedef struct cleanerSystem{
  double positionAlongArm; //distince along arm of robot
  double positionApproach; //distince cleaner is towards window
  double towelPosition; 

  //what you want the cleaner state to be
  double desiredPositionAlongArm;
  double desiredPositionApproach;
  double desiredTowelPosition;
  
  //final variables which depend on the window that we are cleanning and towel length that is loaded
  double towelTotalLength;
  double minPositionAlongArm;
  double maxPositionAlongArm;
  double minPositionApproach;
  double maxPositionApproach;

  //position of cleaner in arm frame
  double positionX; //distince along arm of robot in robot frame
  double positionZ; //distince towards the window in robot frame
  
  //position of cleaner in window frame
  double positionX_w;
  double positionY_w;
  double positionZ_w;

} cleanerSystem_t;

typedef struct extensionSystem{
  double desiredExtensionAmount;
  double currentExtensionAmount;
  //minum possible extension for the robot in meters
  double minextension; 
  //maximum possible extension for the robot in meters
  double maxextension;
} extensionSystem_t;


gripperSystem_t leftGripper;
gripperSystem_t rightGripper;
cleanerSystem_t theCleaner;
extensionSystem_t theExtensionSystem;

#endif /*__ROBOT_H */
