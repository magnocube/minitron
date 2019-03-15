<<<<<<< HEAD
# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time, pyb
from pyb import UART


threshold_index = 0 # 0 for red, 1 for green, 2 for blue

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green/blue things. You may wish to tune them...
thresholds = [(36, 88, 37, 127, -17, 27), # generic_red_thresholds
              (30, 100, -64, -8, -32, 32), # generic_green_thresholds
              (0, 30, 0, 64, -128, 0),      #generic_blue_thresholds
              (63, 100, -128, 127, 20, 127)] # generic_Yellow_thresholds





uart = UART(3, 115200, timeout_char=1000)                         # init with given baudrate
uart.init(115200, bits=8, parity=None, stop=1, timeout_char=1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
#sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()



red_led = pyb.LED(1)
green_led = pyb.LED(2)
blue_led = pyb.LED(3)
ir_leds = pyb.LED(4)
resX = sensor.width()
resY = sensor.height()



while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.

    print(clock.fps())

    if(uart.any()):
        data  = uart.readline()
        print(data)
        red_led.toggle()

    for blob in img.find_blobs([thresholds[threshold_index]], pixels_threshold=30, area_threshold=30, merge=True):
          if blob.w() <= (blob.h() * 1.2):
              if blob.w() >= (blob.h() * 0.8):
                  img.draw_rectangle(blob.rect())
                  img.draw_cross(blob.cx(), blob.cy())
                  age = 10
                  quote = "X:" + str(blob.cx()/resX*100) + "Y:" + str(blob.cy()/resY*100) + "\n"
                  print(quote)
                  uart.write(quote)
























=======
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


>>>>>>> origin/develop
