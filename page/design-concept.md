---
title: "Design Concept"
layout: default
---

# Design Concept #

<img width="500px" height="375px" src="{{site.baseurl}}/images/design_physical_architecture.jpg">

Physical Architecture


<img width="500px" height="330px" src="{{site.baseurl}}/images/design_cyberphysical_architecture.png">

Cyber-Physical Architecture

To meet the performance specifications, we are designing a mechatronic device that incorporates a microcontroller for system control and mechanisms to grip, pivot and extend to move along the window frame.

The robot is comprised of three separate units: a gripping unit, an extending unit and a washing unit. The gripping unit is placed on the two ends of the robot to hold the robot onto the sides of the window frame. Since there is a short distance between the top of the frame and the window, these grippers cover a large surface area parallel to the window to apply more pressure. This also more effectively counters moments due to the weight of the robot. A motor with a planetary gearbox is attached to the gripper to create a pivoting motion about the gripper. The extending unit consists of two offset beams attached together with bearings mounted on a block, forming a linear slide. The motion of the beams is driven by a belt rotated about a pulley for extension and contraction. The cleaning unit moves along the extending unit using a power chain. 

At the beginning of the window washing process, the robot starts with both its grippers mounted onto the frame. Then, the cleaning unit slides back and forth to clean the area along the extending unit. To move up the frame, the robot releases and extends in a diagonal motion and uses encoders to determine position. 


