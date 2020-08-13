#include "PID.h"
#include <iostream>
#include <math.h>
/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {
  Kp = 0;
  Kd = 0;
  Ki = 0;
  p_error = 0;
  d_error = 0;
  i_error = 0;
  best_err = 999999999999;
  index = 0;
  dp_p = 1;
  dp_i = 1;
  dp_d = 1;
  tol = 0.001;
  err = 0;
  state = 0;
}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;  
}

void PID::Twiddle(double cte) {
  // TODO: twiddle logic here
  if ((dp_p + dp_i + dp_d) > tol){
    // check p
    switch (index) {
      case 0: {
        switch (state) {
          case 0: {
            Kp += dp_p;
            state = 1;
            err = TotalError();
            break;
          }
          case 1: {
            if (fabs(err) < fabs(best_err)){
              best_err = err;
              dp_p *= 1.1;
              state = 3;
            }
            else {
              Kp -= 2 * dp_p;
              state = 2;
              err = TotalError();
            }
            break;
          }
          case 2: {
            if (fabs(err) < fabs(best_err)){
              best_err = err;
              dp_p *= 1.1;
            }
            else {
              Kp += dp_p;
              dp_p *= 0.9;
            }
            state = 3;
            break;
          }
          case 3: {
            index = (index + 1) % 3;
            state = 0;
            break;
          }
        }
        break;
      }
    // check d
      case 1: {
        switch (state) {
          case 0: {
            Kd += dp_d;
            state = 1;
            err = TotalError();
            break;
          }
          case 1: {
            if (fabs(err) < fabs(best_err)){
              best_err = err;
              dp_d *= 1.1;
              state = 3;
            }
            else {
              Kd -= 2 * dp_d;
              err = TotalError();
              state = 2;
            }
            break;
          }
          case 2: {
            if (fabs(err) < fabs(best_err)){
              best_err = err;
              dp_d *= 1.1;
            }
            else {
              Kd += dp_d;
              dp_d *= 0.9;
            }
            state = 3;
            break;
          }
          case 3: {
            index = (index + 1) % 3;
            state = 0;
            break;
          }
        }
        break;
      }
    // check i
      case 2: {
        switch (state) {
          case 0: {
            Ki += dp_i;
            state = 1;
            err = TotalError();
            break;
          }
          case 1: {
            if (fabs(err) < fabs(best_err)){
              best_err = err;
              dp_i *= 1.1;
              state = 3;
            }
            else {
              Ki -= 2 * dp_i;
              err = TotalError();
              state = 2;
            }
            break;
          }
          case 2: {
            if (fabs(err) < fabs(best_err)){
              best_err = err;
              dp_i *= 1.1;
            }
            else {
              Ki += dp_i;
              dp_i *= 0.9;
            }
            state = 3;
            break;
          }
          case 3: {
            index = (index + 1) % 3;
            state = 0;
            break;
          }
        }
        break;
      }
    }
  }
  std::cout<<"Best Error:"<<best_err<<":Kp:"<<Kp<<":Ki:"<<Ki<<":Kd:"<<Kd<<"\n";
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return ( -Kp * p_error - Kd * d_error - Ki * i_error);  // TODO: Add your total error calc here!
}