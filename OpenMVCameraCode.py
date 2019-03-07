# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time, pyb
from pyb import UART

red_led = pyb.LED(1)
green_led = pyb.LED(2)
blue_led = pyb.LED(3)
ir_leds = pyb.LED(4)

uart = UART(3, 115200, timeout_char=1000)                         # init with given baudrate
uart.init(115200, bits=8, parity=None, stop=1, timeout_char=1000)

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
        red_led.toggle()


