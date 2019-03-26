
import sensor, image, time, pyb
from pyb import UART


threshold_index = 1 # 0 for red, 1 for green, 2 for blue

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green/blue things. You may wish to tune them...
thresholds = [(44, 78, 35, 89, -25, 39), # generic_red_thresholds
              (25, 89, -128, -31, -44, 39), # generic_green_thresholds
              (0, 30, 0, 64, -128, 0),      #generic_blue_thresholds
              (63, 100, -128, 127, 20, 127)] # generic_Yellow_thresholds





uart = UART(3, 115200, timeout_char=1000)                         # init with given baudrate
uart.init(115200, bits=8, parity=None, stop=1, timeout_char=1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.CIF)
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

    for blob in img.find_blobs([thresholds[threshold_index]], pixels_threshold=50, area_threshold=50, merge=True):
          if blob.w() <= (blob.h() * 1.5):
              if blob.w() >= (blob.h() * 0.5):
                  img.draw_rectangle(blob.rect())
                  img.draw_cross(blob.cx(), blob.cy())
                  age = 10
                  quote = "X:" + str(round(blob.cx()/resX*100)) + "Y:" + str(round(blob.cy()/resY*100)) + "\n"
                  print(quote)
                  uart.write(quote)
                  break

























