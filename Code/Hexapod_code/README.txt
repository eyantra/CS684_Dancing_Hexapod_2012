Instructions for compiling and burning the Hexapod Code
Platform Used: ICCAVR 7.0 ( https://www.imagecraft.com/ )
1) Open the Hexapod Code Project in ICCAVR
   (Project --> Open --> DancingHexapod.prj)

2) Rebuild all the files
   (Project --> Rebuild all)
   This creates a Hex file “DANCINGHEXAPOD.hex”

3) To burn the .hex file on the Hexapod, open the command prompt and go to the Hexapod Code folder. Burn the code using the following command: 
   avrdude -c usbasp -p m2560 -P usb -U flash:w:DANCINGHEXAPOD.hex

4) After the code has been burnt, hold the hexapod in your hands or keep it on a CD box. First, switch on the main power supply of the Hexapod. Next, switch on the servo motors.

5) Once the Hexapod is in its standing position, you can keep it on any plain surface.

6) Connect the Hexapod’s Bluetooth to your Android Phone’s Bluetooth using our android app.
   (Refer to the android documentation for instructions on how to use our android app)

7) Select a song and a dance step in the android app and select Play to enjoy the Hexapod dance. :)

8) To switch off the Hexapod, first switch off the servo motors and then the main power supply switch.
