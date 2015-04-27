//cleaner.h

//structure defintions 
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

} cleaner_state_t;


//methods 
int cleanLeft();
int cleanRight();
int moveCleanerLeft();
int mvoeCleanerRight();
int cleanerToWindow();
int cleanerOffWindow();
int clenaerClearWindow();
int cleanThisLevel();
void cleanTo(double pointToCleanTo);
void moveCleanerTo(double pointToClenaTo);
int  homeCleaner();
