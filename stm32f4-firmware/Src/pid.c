#include "pid.h"

//PID controller functions 

//creates the pid controler 
void pid_init(pid_state_t *state,int output_limited,double max_speed,double set_point, double p,double i,double d){
  state->enabled = TRUE;
  state->output_limited = output_limited;
  state->max_speed = max_speed;
  state->set_point = set_point;
  //  state->last_run_time = current_time; //to avoid a timming error when the system is disabled 
  state->p = p;
  state->i = i;
  state->d = d;
  //todo setup task 
  
}


void inline pid_set_enabled(pid_state_t *state,int enabled){
  state->enabled = enabled;
}

void inline pid_set_output_limited(pid_state_t *state,double should_limit){
  state->output_limited = should_limit;
}

void inline pid_set_max_speed(pid_state_t *state,double max_speed){
  state->max_speed = max_speed;
}

void inline pid_set_setpoint(pid_state_t *state,double new_set_point){
  state->set_point = new_set_point;
}

void inline pid_set_p(pid_state_t *state,double new_p){
  state->p = new_p;
}

void inline pid_set_i(pid_state_t *state,double new_i){
  state->i = new_i;
}

void inline pid_set_d(pid_state_t *state,double new_d){
  state->d = new_d;
}

int inline pid_is_enabled(pid_state_t *state){
  return state->enabled;
}

int inline get_output_limited(pid_state_t *state){
  return state->output_limited;
}

double inline get_max_speed(pid_state_t *state){
  return state->max_speed;
}

double inline get_set_point(pid_state_t *state){
  return state->set_point;
}

double inline pid_get_p(pid_state_t *state){
  return state->p;
}

double inline pid_get_i(pid_state_t *state){
  return state->i;
} 

double inline pid_get_d(pid_state_t *state){
  return state->d;
}

//removes all error, rezeroing the system 
void pid_zero(pid_state_t *state){
  state->p_error = 0;
  state->i_error = 0;
  state->d_error = 0;
}

//gets the current integeration error 
double inline pid_get_p_error(pid_state_t *state){
  return state->p_error;
}

double inline pid_get_i_error(pid_state_t *state){
  return state->i_error;
}

double inline pid_get_d_error(pid_state_t *state){
  return state->d_error;
}

double inline pid_get_comanded_output(pid_state_t *state){
  return state->comanded_output;
}

//runs the pid algorithm to calulate what the current output value should be 
void iterate(pid_state_t *state){
  //todo call sensor function 
    //TODO lock comanded_output

  //set speed 0 if the system is not enabled otherwise set the calulated value 
  if(state->enabled){
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
  }else{
    //TODO this might cause a problem for position controllers 
    state->comanded_output = 0;
    // state->last_run_time = current_time; //to avoid a timming error when the system is disabled 
  }
  //TODO release lock on comanded_output

  //TODO set motor speeds
}


