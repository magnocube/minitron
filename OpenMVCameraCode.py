# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time
from pyb import UART

uart = UART(3, 9600, timeout_char=1000)                         # init with given baudrate
uart.init(9600, bits=8, parity=None, stop=1, timeout_char=1000)

sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.RGB565) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    #uart.write(clock.fps())
    print(clock.fps())
    uart.write("Hello World!\r\n")
    if(uart.any()):
        data  = uart.readline()
        print(data)

