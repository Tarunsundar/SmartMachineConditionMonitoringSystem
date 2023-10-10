# SmartMachineConditionMonitoringSystem
This is a C/C++ program written to use Arduino Nicla sense me, microcontroller 
to Monitor the condition of Industrial Machine using it's inbuilt sensors, 
predict machine fault beforehand, alert the supervisor and also record the 
sensor readings for fault prediction.

Required Hardwares:

SD card - to store the predicted machine fault's sensor readings
Stack light &/ fire alarm - to notify the person of the predicted machine fault.
Jumper wires - to connect the microcontroller with hardwares.

The machine condition monitoring system developed takes humidity, temperature and vibration values of the machine 
to predict the fault. the inbuilt sensors provide humidity and temperature values without any extra work,
but the arduino nicla sense me just has an accelerometer(this provides us with the acceleration values in the 3 axis - x, y, z) to get the vibration of machine.
The closest thing without using much of arduino's computational power and processing time was to find the acceleration magnitude.

This program runs to continously monitor the machine's acceleration magnitude, humidity and temperature value and 
if all of the threshold values exceed, it predicts a fault in the machine does the necessary to notify the person incharge
of the fault predicted and parallely keeps on storing the sensor readings in a CSV file, 
which later can be used in troubleshooting the machine fault.



