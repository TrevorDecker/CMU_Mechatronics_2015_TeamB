#include "pid.h"
//PID controller functions 

//creates the pid controler
//spins up a new task  
void pidInit(pid_state_t * pid_state,vnh5019_state_t *motor_state,int output_limited,double max_speed,double set_point,double  error_threshold, double p,double i,double d){
  pid_state->output_limited = output_limited;
  pid_state->max_speed = max_speed;
  pid_state->set_point = set_point;
  pid_state->error_threshold = error_threshold;
  pid_state->p = p;
  pid_state->i = i;
  pid_state->d = d;
  pid_state->motor_state = motor_state;
  //TODO setup task
  //TODO add sensors 
}

//stops the controller from running any more 
void releasePID(pid_state_t *pid_state){
  //TODO
}

inline int pid_is_goal_reached(pid_state_t *pid_state){
  return pid_state->current_error < pid_state->error_threshold;
}

void pid_block_until_goal_reached(pid_state_t*pid_state){
  //causes for this thread to spin until the goal is reached 
  while(!pid_is_goal_reached(pid_state)){
    //delay(20); TODO 
  }
}

inline void pid_set_output_limited(pid_state_t *state,double should_limit){
  state->output_limited = should_limit;
}

inline void pid_set_max_speed(pid_state_t *state,double max_speed){
  state->max_speed = max_speed;
}

inline void pid_set_setpoint(pid_state_t *state,double new_set_point){
  state->set_point = new_set_point;
}

inline void pid_set_p(pid_state_t *state,double new_p){
  state->p = new_p;
}

inline void  pid_set_i(pid_state_t *state,double new_i){
  state->i = new_i;
}

inline void pid_set_d(pid_state_t *state,double new_d){
  state->d = new_d;
}

inline int get_output_limited(pid_state_t *state){
  return state->output_limited;
}

inline double get_max_speed(pid_state_t *state){
  return state->max_speed;
}

inline double get_set_point(pid_state_t *state){
  return state->set_point;
}

inline double pid_get_p(pid_state_t *state){
  return state->p;
}

inline double pid_get_i(pid_state_t *state){
  return state->i;
} 

inline double pid_get_d(pid_state_t *state){
  return state->d;
}

//removes all error, rezeroing the system 
void pid_zero(pid_state_t *state){
  state->p_error = 0;
  state->i_error = 0;
  state->d_error = 0;
}

//gets the current integeration error 
inline double pid_get_p_error(pid_state_t *state){
  return state->p_error;
}

inline double pid_get_i_error(pid_state_t *state){
  return state->i_error;
}

inline double pid_get_d_error(pid_state_t *state){
  return state->d_error;
}

//runs the pid algorithm to calulate what the current output value should be 
void iterate(pid_state_t *state){
  //todo call sensor function 
    //TODO lock comanded_output

    //state->dt = current_time - state->last_run_time;
    //   state->last_run_time = current_time;
  state->current_error = state->current_point - state->set_point;
  state->d_error = (state->current_error - state->last_error)/state->dt;
  state->last_error = state->current_error;
  //will only allow for i_error to grow while the system is enabled 
  state->i_error += state->current_error*state->dt;
  state->comanded_output = state->p*state->p_error + state->i*state->i_error + state->d*state->d_error;
  //making sure that the system stays within limits if it is suppose to 
  if(state->output_limited){
    if(state->comanded_output > state->max_speed){
      state->comanded_output = state->max_speed;
    }else if(state->comanded_output < -1*state->max_speed){
      state->comanded_output = -1*state->max_speed;
    } 
    
  }
  //TODO release lock on comanded_output

  //TODO set motor speeds
}
