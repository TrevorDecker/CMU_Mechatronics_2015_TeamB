#ifndef _PID_H_
#define _PID_H_

#ifndef _LOGIC_VALUES__
#define _LOGIC_VALUES__
#define TRUE 1;
#define FALSE 0;
#endif //_LOGIC_VALUES__

#include "vnh5019.h"

//TODO consider adding i saturation 


//each pid should be run as a seperate task 
//structure defintions 
typedef struct pid_state{
  int    output_limited; //if true maxSpeed is used otherwise it is not 
  double max_speed;   //maximum output value for the pid cotnroller, anythign heigher then this will be rounded to this value if outputLimit is enabled 
  double set_point;
  double current_point;
  double current_error;
  double error_threshold;
  double last_error;
  double dt;
  double last_run_time;
  double p;
  double i;
  double d;
  double p_error;
  double i_error;
  double d_error;
  double comanded_output;
  vnh5019_state_t *motor_state;
}  pid_state_t;

//Methods
void pidInit(pid_state_t * pid_state,vnh5019_state_t *motor_state,int output_limited,double max_speed,double set_point,double  error_threshold, double p,double i,double d);
void pid_set_output_limited(pid_state_t *state,double should_limit);
void pid_set_max_speed(pid_state_t *state,double max_speed);
void pid_set_setpoint(pid_state_t *state,double new_set_point);
void pid_set_p(pid_state_t *stae,double new_p);
void pid_set_i(pid_state_t *state,double new_i);
void pid_set_d(pid_state_t *state,double new_d);
int pid_is_enabled(pid_state_t *state);
int get_output_limited(pid_state_t *state);
double get_max_speed(pid_state_t *state);
double get_set_point(pid_state_t *state);
double pid_get_p(pid_state_t *state);
double pid_get_i(pid_state_t *state);
double pid_get_d(pid_state_t *state);
//removes all error, rezeroing the system 
void pid_zero(pid_state_t *state);
//gets the current integeration error 
double pid_get_p_error(pid_state_t *state);
double pid_get_i_error(pid_state_t *state);
double pid_get_d_error(pid_state_t *state);
double pid_get_comanded_output(pid_state_t *state);
void pid_block_until_goal_reached(pid_state_t*pid_state);
void releasePID(pid_state_t *pid_state);
//TODO add motor controllers should be vnh5019 or stepper for now 
//TODO add a way to regester sensors 

#endif // _PID_H_
