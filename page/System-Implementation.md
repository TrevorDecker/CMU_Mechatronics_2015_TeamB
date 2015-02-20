---
title: "System Implementation"
layout: default
---

# System Implementation #

###Frame Gripper###
A gripper is used to hold the robot to the window frame made of 80/20 aluminum. The gripper needs to be able to support the whole weight of the robot and as a result, it needs to be long to cover enough surface area. Also, in order to accomplish the swinging motion, the gripper needs to retract away from the frame so it does not interfere. 

###Extending Arm###
A core feature of our design requires moving a cleaning unit horizontally on the window. To do this, we plan to build an extending unit that the cleaning unit can move on. This slide may be powered by timing belt or a winch solution. To adjust for different size windows, we need the slide to be built on an extending arm that can adjust between the 3 and 5 foot bounds of window size. Stepper motors with limit switches can be used to control movement on the arm with good speed and accuracy, and zeroing position after the arm has changed length is not an issue. The arm will be made of 2in x 2in, thin-walled aluminum to help maintain stiffness. 

###Cleaning Unit###
The actual cleaning unit that will translate from side to side on the telescoping arm comprises of a large sponge and two separate squeegee edges.  The entire cleaning unit can be raised and lowered from the window surface using a lead screw and a small motor.  At rest, the two squeegees extend past the sponge surface, supported by springs.  As the unit is driven further towards the window, the sponge will come into contact as well.  With the sponge in contact with the glass surface, the unit will move across the window in order to clean it.  After moving across the window using the power change, the sponge will retract, and the squeegees will remove leftover water before the entire unit moves down and cleans the next lower “layer” of the window. The sponge will be kept moist with water and cleaning fluid using two separate storage tanks located on the top and bottom of the unit.  Two separate tanks are needed for when the robot flips upside down.  The tanks will have small holes facing the sponge, and the fluid will be gravity fed into the sponge.  The unit will be guided along the telescoping arm using small motorized wheels and limit switches to maintain knowledge of cleaning unit position. 

###Pivoting Unit###
In order to achieve one of the coolness factors we have identified -- cleaning a grid of windows with dividers -- we need to be able to swing from one window frame to another. We believe the most effective solution is a 180º joint where each gripper meets the extending arm. The joint allows movement in the plane parallel to the window. This allows us to move the main cleaning and location assembly up, down, left, or right on a grid of windows with frames. To reduce the side of motor required to move the arm, especially when it is nearly horizontal to the ground, the arm should retract completely. This movement will be realized through the implimentation of a planetary gearbox with a shaft and worm gear that will allow us to pivot both units at the same time with one motor.
