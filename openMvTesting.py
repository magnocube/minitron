
import sensor, image, time

threshold_index = 0 # 0 for red, 1 for green, 2 for blue

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green/blue things. You may wish to tune them...
thresholds = [(29, 87, 40, 127, -36, 103), # generic_red_thresholds
              (30, 100, -64, -8, -32, 32), # generic_green_thresholds
              (0, 30, 0, 64, -128, 0),      #generic_blue_thresholds
              (63, 100, -128, 127, 20, 127)] # generic_Yellow_thresholds

resX = 320
resY = 240

largestX = 0
largestY = 0
largestXWidth = 0
largestYHeigth = 0
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(True) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()

# Only blobs that with more pixels than "pixel_threshold" and more area than "area_threshold" are
# returned by "find_blobs" below. Change "pixels_threshold" and "area_threshold" if you change the
# camera resolution. "merge=True" merges all overlapping blobs in the image.

while(True):
    clock.tick()
    img = sensor.snapshot()

    largestX = 0
    largestY = 0
    largestXWidth = 0
    largestYHeigth = 0
    for blob in img.find_blobs([thresholds[threshold_index]], pixels_threshold=30, area_threshold=30, merge=True):
        if blob.w() <= (blob.h() * 1.2):
            if blob.w() >= (blob.h() * 0.8):
                img.draw_rectangle(blob.rect())
                img.draw_cross(blob.cx(), blob.cy())
                age = 10
                quote = "X:" + str(blob.cx()/resX*100) + "Y:" + str(blob.cy()/resY*100)
                print(quote)


    print(clock.fps())
