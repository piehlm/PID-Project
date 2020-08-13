# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

Introduction
The project's purpose is to build a PID controller with tuned hyperparameters and run it against a simulator. The lessons learned in the courses provide a baseline to implement the algorithms of PID controller in python.  Implementing in C++ is a major portion of this challenge.

PID Components' Effects Description
To demonstrate the effect of each type of controller, I tested several configurations of the hyperparameters manually at initialization step of each controller workflow applyed to steering value and throttle one.

P Controller :
To enable only the P component, the hyperparams = {0.15,0,0} configuration is used. The effect is a wide back and forth motion, rapidly swerving from extreme to extreme (typically, the car could not stay on the road long unless it was set to a very low throttle).

PD Controller :
To enable only the P and D components, the hyperparams = {0.15,0.0003,0} configuration is used. The behavior is similar, slightly more controlled. A fine tuned parameter makes the car steer stablely along the central line.

PDI Controller :
To enable it, the hyperparams = {0.15,0.0003,6.75} configuration is used. The result is the car behaves as expected. As speeds increase, the steering becomes more erratic, but if you maintain 0.3 throttle or less, the results are relatively smooth.

Hyperparameters Tuning :
INitially, All parameters were tuned manually. I started with some recommendations from the formums, which gave me a stable starting point of [0.2, .00003, 3].  Additionally, I implemented twiddle.  It provided some minor improvements, but in general, I struggled to get the car to stay on the road while Twiddle stabilized.  I had to reduce throttle, but that didn't lead to the best results, as the car behaves much easier at slow speeds.  
Eventually, I was able to tweak the parameters to run at 0.33 throttle.  Anything greater than that, and the car became too erratic.
I did attempt to do Twiddle on the throttle, but I was unsuccessful in getting hyper parameters that would keep the car on the road.  

As a fun side note, I was able to accidentally drive the car in reverse around the entire track :)