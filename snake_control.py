import serial
import keyboard
import time

ser = serial.Serial('COM6', 9600)
last_key = None

while True:
    if keyboard.is_pressed('up') and last_key != 'up':
        ser.write(b'U')
        last_key = 'up'
    elif keyboard.is_pressed('down') and last_key != 'down':
        ser.write(b'D')
        last_key = 'down'
    elif keyboard.is_pressed('left') and last_key != 'left':
        ser.write(b'L')
        last_key = 'left'
    elif keyboard.is_pressed('right') and last_key != 'right':
        ser.write(b'R')
        last_key = 'right'
    elif not (keyboard.is_pressed('up') or keyboard.is_pressed('down') or
              keyboard.is_pressed('left') or keyboard.is_pressed('right')):
        last_key = None 
    time.sleep(0.05) 

