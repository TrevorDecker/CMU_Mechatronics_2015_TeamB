---
title: "System Performance"
layout: default
---

# System Performance

## Mechanical

### Frame Gripper

A quick test was run to figure out how much weight our current gripper prototype could support.  A clamp was attached to the gripper and a bag was hung off of the clamp at the distance that we expect the center of mass of the robot to be away from the window.  Weight was added to the bag until failure, which occured at around 5 lbs. Currently, we are leaning towards using the weight of the robot to hold onto the frame. The proposed way to accomplish this is by clasping on with a C-clamp and allowing for the top and bottom of the clamp to apply normal forces to the frame. 

[![]({{site.baseurl}}/images/griptest1.JPG)]({{site.baseurl}}/images/griptest1.JPG)
[![]({{site.baseurl}}/images/griptest2.JPG)]({{site.baseurl}}/images/griptest2.JPG)
[![]({{site.baseurl}}/images/griptest3.JPG)]({{site.baseurl}}/images/griptest3.JPG)

The final iteration, however, consisted of two large pieces of aluminum c-channel with rubber padding.  The c-channel fits over the frame of the window, and when the full weight of the robot is applied to the gripper, the large resulting moment creates a friction lock as the top and bottom of the c-channel bind against the window frame.  The rubber padding increases the coefficient of friction to prevent slipping.  One large advantage to this mechanism is that the weight of the robot actually helps the grippers stick to the window frame by applying more normal force and thus creating more friction.

[![]({{site.baseurl}}/images/griptest4.png)]({{site.baseurl}}/images/griptest4.png)

### Extending Arm
The extension arm has been built and has been tested. The lead screw is able to power the extending arm quickly as long as there is enough current from the power supply. Due to the length of the lead screw, we are concerned about the binding of the lead screw. There are also some concerns regarding the weight of the arm but due to the transfer gearbox but we will attempt to cut down on the weight in a way that would not compromise function.

<iframe width="560" height="315" src="https://www.youtube.com/embed/jR1k3SBtJII" frameborder="0" allowfullscreen></iframe>

### Cleaning Unit
The cleaning unit is currently being built and undergoing testing. We have been testing the fit of various components on the cleaning unit and soon the whole cleaning unit can be printed and tested. One cleaning unit for the extending arm was printed and we successfully got it to slide smoothly on the extension arm. Since the power chain needs to be wound up on both ends, we will need to design a housing to keep the chain compact.

### Pivoting Unit
The pivoting motion is dictated by a gearbox with a worm gear. It has been assembled and is in the process of being tested. From testing the pivoting unit, we understood the importance of material selection and failure modes. At first, we made the spacers out of acrylic which yielded under the stress of the turning gear. The next step is to make new spacers of a larger radius out of delrin or alumnium to withstand the stresses. This improvement will allow us to continue testing.

<iframe width="420" height="315" src="https://www.youtube.com/embed/JQYD1DYoebc" frameborder="0" allowfullscreen></iframe>

## Software Bring-up

We currently have [working firmware](https://github.com/TrevorDecker/CMU_Mechatronics_2015_TeamB/tree/master/stm32f4-firmware) that controls the screen on our development board. To use this, we had to bring up the SPI and GPIO interfaces, and the program uses the system timers to generate data for the screen. We also wrote our own makefile to build the hardware support libraries and our own code. We have been able to connect an external debugger to understand issues with the firmware, which will be very powerful for future development. Our next steps are to write a motor control module.

[![]({{site.baseurl}}/images/software1.jpg)]({{site.baseurl}}/images/software1.jpg)
<br />Our "Hello World" program running with screen support.<br />
