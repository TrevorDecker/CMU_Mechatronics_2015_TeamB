---
title: "System Design"
layout: default
---

# System Design #

<img src="../images/cad.PNG" />

To meet the performance specifications, we are designing a mechatronic device that incorporates a microcontroller for system control and mechanisms to grip, pivot and extend to move along the window frame. 

The robot is comprised of three separate units: a gripping unit, an extending unit and a washing unit. The gripping unit is placed on the two ends of the robot to hold the robot onto the sides of the window frame. Since there is a short distance between the top of the frame and the window, these grippers cover a large surface area parallel to the window to apply more pressure. This also more effectively counters moments due to the weight of the robot. A motor with a planetary gearbox is attached to the gripper to create a pivoting motion about the gripper. The extending unit consists of two offset beams attached together with bearings mounted to a block to form a linear slide. The motion of the beams is driven by a motor and lead screw. The cleaning unit moves along the extending unit using a power chain. 

At the beginning of the window washing process, the grippers are attached to both sides of the frame. As the robot shuffles up the frame, releasing the gripping and extending the arm as it climbs, the cleaning unit slides back and forth to clean a section of the window. 

#Design Iterations 

Many design improvements have been made since the start of the project. Firstly, the T-rail has been removed due to size and manufacturing considerations. By using bearing blocks instead, we have been able to reduce the height of our robot by half. As for our gripping unit, we have been able to move from a four-bar linkage to a clamp design which has allowed us to cut down on size and, as result, reduce the distance away from the window pane. This was an  essential in minimizing the torque that causes the robot to fall away from the window. The pivoting unit has seen improvements in material selection. Due to failures that occurred in testing, we are now using metal instead of plastic to transfer loads. The cleaning unit has also undergone many changes in design that have improved our motion along the extending arm as well as our contact with the window surface.

(INSERT CHRONOLOGICAL PHOTOS HEREEEEE)

Overall, due to all the modifications illustrated above, we have been able to decrease the complexity of our subsystems to create a more compact and efficient robot. 
