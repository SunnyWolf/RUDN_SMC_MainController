SMC_RUDN_MainController firmware
================================

This project contains firmware for a main controller of RUDN University ebike.

--------------

Components of the controller
----------------------------

 - STM32F103C8T6 microcontroller
 - MPU6050 accelerometer and hyroscope
 - GPS module
 - 24C04 eeprom
 - HC06 bluetooth <-> uart adapter

Compilation
---------------
You need installed "arm-none-eabi" package to compile this project. 
Just change current directory to directory with project **cd 
RUDN_SMC_MainController** and run **Make**.
Compiled files will be placed in **/build** directory as **.hex**, 
**.bin**, **.elf** files.
