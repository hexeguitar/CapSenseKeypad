**CapSense Keypad**
-------------------
![CapSenseKeypad](https://raw.githubusercontent.com/hexeguitar/CapSenseKeypad/master/pics/CapSenseKeypad2.jpg)
16 button keypad using capacitive touch sensors, designed as a compact alternative for mechanic keypads.
Circuit is built around Cypress [CY8CMBR3116](http://www.cypress.com/file/46236/download) controller and communicates with the outer world via I2C bus. Additional active low "Host Interrupt" line informs the host controller about any change in the touch sensor matrix. 

The 16 buttons are divided into 0-9 digits, decimal point, left, right, up and down navigation buttons and one "Setup" button used to enter setup mode in the controlled device. The main use for it are DIY test gear, bench tool projects, where such a keypad will offer a quick and convenient way to  input numerical values, navigate through menus etc.

The CY8CMBR3116 chip is configured using the [EZ-Click](http://www.cypress.com/documentation/software-and-drivers/ez-click-20) software to scan 16 buttons, avoid triggering adjacent ones and generate an active low interrupt pulse whenever any of the buttons is pressed or released.

Keypad works with supplies in range from 1.7 to 5.5V and supports high speed 400kHz I2C clock.

PCB material thickness: **1mm**
![CapSenseKeypad](https://raw.githubusercontent.com/hexeguitar/CapSenseKeypad/master/pics/CSkeypad_btm.jpg)

----------

**Example project**
uses PSoC4 Pioneer board and is created with PSoC Creator 3.3.
![PSoC Creator project](https://raw.githubusercontent.com/hexeguitar/CapSenseKeypad/master/ExampleProject_PSoC4/CapSenseKeypad_PSoCcreator.png)
MCU waits for the keypad interrupt event, reads out the button status registers and uses them to control and navigate within a typical V100 terminal (i.e. PuTTY). 

Connections:

 - SCL -> P4[0]
 - SDA -> P4[1]
 - HT -> P1[7]
 - P3[0] RX <- PSoC5LP P12[7] TX
 - P3[1] TX -> PSoC5LP P12[6] RX

Video:
<a href="http://www.youtube.com/watch?feature=player_embedded&v=4fJzSCEbiiY
" target="_blank"><img src="http://img.youtube.com/vi/4fJzSCEbiiY/0.jpg" 
alt="Keypad in action - YT video" width="240" height="180" border="10" /></a>
 
----------
(c) 06.2016 by Piotr Zapart 
www.hexeguitar.com

License:
Creative Commons - Attribution - ShareAlike 3.0 
[http://creativecommons.org/licenses/by-sa/3.0/](http://creativecommons.org/licenses/by-sa/3.0/)


