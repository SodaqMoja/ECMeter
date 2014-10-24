ECMeter
=======

This repository includes all open source files related to the EC-Meter that I have developed for _M2M4ALL_, the company I work for.
This circuit board includes an analog frontend to measure the electrical conductivity and temperature of water. The board will have to be cast in resin with the probes sticking out in order to submerge the board for long durations.


_Please note that this project is still in development_

This is the Arduino library required to use the EC Meter easily. 
Please note that this library requires the SoftI2CMaster library found here: https://github.com/felias-fogg/SoftI2CMaster


###Examples
=====
**readTemperature**
*- Reads the onboard temperature sensor and prints the value every second*

