#!/usr/bin/env python3
 
###############################################################################
# Program: Send a number one integer to an Arduino over UART Serial
# File: int_from_pi_to_uno.py
# Description: This program runs on a laptop. It sends a single integer '1'
# over UART serial to an Arduino.
# Author: Cuong Nguyen
# Date: April 5, 2023
###############################################################################
 
import serial # Module needed for serial communication
import time # Module needed to add delays in the code
 
# Set the port name and the baud rate. This baud rate should match the baud rate set on the Arduino.
ser = serial.Serial('COM9', 115200, timeout=1)
file = open("Cuong-Frontal-Blink-2.txt", "r")
send_string = '1'
  
# Get rid of garbage/incomplete data
ser.flush()

line = file.readline()
while line:
  if line[0].isdigit():
    break
  line = file.readline()
print("Reading data file...")

# Read until there is data left in the file
while line:
  if "#" in line:
    idx = line.find('#')
    time_stamp = line[idx+2:].strip()
    # Send the string. Make sure you encode it before you send it to the Arduino
    ser.write(send_string.encode('utf-8'))
    print("Blinked at", time_stamp,  "and notified Arduino")

  # Wait for a set amount of time before sending the next integer
  time.sleep(0.001)
  line = file.readline()

# Close the serial port
ser.close()



