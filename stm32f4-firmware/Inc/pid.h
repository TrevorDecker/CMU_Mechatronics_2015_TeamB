#ifndef _PID_H_
#define _PID_H_

#ifndef _LOGIC_VALUES__
#define _LOGIC_VALUES__
#define TRUE 1;
#define FALSE 0;
#endif //_LOGIC_VALUES__

//TODO consider adding i saturation 


//each pid should be run as a seperate task 
//structure defintions 
typedef struct pid_state{
  int enabled;
  int    output_limited; //if true maxSpeed is used otherwise it is not 
  double max_speed;   //maximum output value for the pid cotnroller, anythign heigher then this will be rounded to this value if outputLimit is enabled 
  double set_point;
  double current_point;
  double current_error;
  double last_error;
  double dt;
  double last_run_time;
  double p;
  double i;
  double d;
  double p_error;
  double i_error;
  double d_error;
  double comanded_output; //the most recent commanded_output
}  pid_state_t;

//Methods
void pid_init(pid_state_t *state,int output_limited,double max_speed,double set_point, double p,double i,double d);
void inline pid_set_enabled(pid_state_t *state,int enabled);
void inline pid_set_output_limited(pid_state_t *state,double should_limit);
void inline pid_set_max_speed(pid_state_t *state,double max_speed);
void inline pid_set_setpoint(pid_state_t *state,double new_set_point);
void inline pid_set_p(pid_state_t *stae,double new_p);
void inline pid_set_i(pid_state_t *state,double new_i);
void inline pid_set_d(pid_state_t *state,double new_d);
int inline pid_is_enabled(pid_state_t *state);
int inline get_output_limited(pid_state_t *state);
double inline get_max_speed(pid_state_t *state);
double inline get_set_point(pid_state_t *state);
double inline pid_get_p(pid_state_t *state);
double inline pid_get_i(pid_state_t *state);
double inline pid_get_d(pid_state_t *state);
//removes all error, rezeroing the system 
void pid_zero(pid_state_t *state);
//gets the current integeration error 
double inline pid_get_p_error(pid_state_t *state);
double inline pid_get_i_error(pid_state_t *state);
double inline pid_get_d_error(pid_state_t *state);
double inline pid_get_comanded_output(pid_state_t *state);


//TODO add motor controllers should be vnh5019 or stepper for now 
//TODO add a way to regester sensors 

#endif // _PID_H_
