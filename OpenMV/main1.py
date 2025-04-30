# Measure the distance
#
# This example shows off how to measure the distance through the size in imgage
# This example in particular looks for yellow pingpong ball.

import sensor, image, time
from pyb import UART
# For color tracking to work really well you should ideally be in a very, very,
# very, controlled enviroment where the lighting is constant...
line_threshold   = (0, 110)
# You may need to tweak the above settings for tracking green things...
# Select an area in the Framebuffer to copy the color settings.

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # use RGB565.
sensor.set_framesize(sensor.QQVGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
clock = time.clock() # Tracks FPS.

K=210#the value should be measured

red_threshold = (30, 100, 15, 127, 15, 127)
uart = UART(3, 115200)  # 初始化

while(True):

    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot()#.lens_corr(strength = 1.5, zoom = 1.2)
    #img = sensor.snapshot() # Take a picture and return the image.
    #img.draw_rectangle(60, 10, 30,60, color=(255,0,0), thickness=2)
    blobs = img.find_blobs([line_threshold], pixels_threshold=100,roi=(60, 10, 30, 80))
    if len(blobs) == 1:
        # Draw a rect around the blob.
        b = blobs[0]
        img.draw_rectangle(b[0:4]) # rect
        img.draw_cross(b[5], b[6]) # cx, cy
        Lm = (b[2]+b[3])/2
        length = K/Lm
        length_int=int(length)
        dist= b[6]*1.7148+29.407
        print(dist)
        #print(length)
        #print(length_int)
        uart.write(bytearray([int(dist)]))  # 发送一个字节


    #print(clock.fps()) # Note: Your OpenMV Cam runs about half as fast while
    # connected to your computer. The FPS should increase once disconnected.
