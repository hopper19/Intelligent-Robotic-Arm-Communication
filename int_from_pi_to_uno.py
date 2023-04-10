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
 
# Set the port name and the baud rate. This baud rate should match the
# baud rate set on the Arduino.
# Timeout parameter makes sure that program doesn't get stuck if data isn't
# being received. After 1 second, the function will return with whatever data
# it has. The readline() function will only wait 1 second for a complete line 
# of input.
ser = serial.Serial('COM9', 115200, timeout=1)
  
# Get rid of garbage/incomplete data
# ser.flush()

# Wait for the Arduino to initialize its serial communication
time.sleep(5)
 
# Infinite loop
while (1):

  send_string = '1'
  # send_string += "\n"

  # Send the string. Make sure you encode it before you send it to the Arduino
  ser.write(send_string.encode('utf-8'))
  print("Just blinked and notified Arduino")

  # Receive data from the Arduino
  # if ser.in_waiting > 0:
  # receive_string = ser.readline().decode('utf-8', 'replace').rstrip()

  # Print the data received from Arduino to the terminal
  # print("Regurgitated by Arduino:")
  # print(receive_string + "\n")

  # Wait for a set amount of time before sending the next integer
  time.sleep(5)


