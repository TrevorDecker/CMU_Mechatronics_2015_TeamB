# Written by Trevor Decker 
# reads 100 bytes from a serial port and displays them to the user 

import serial
ser = serial.Serial('/dev/ttyACM0')
line = ser.read(100)
print line
ser.close()
