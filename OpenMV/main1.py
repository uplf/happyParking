
import sensor, image, time
from pyb import UART

line_threshold   = (0, 110)

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # use RGB565.
sensor.set_framesize(sensor.QQVGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
clock = time.clock() # Tracks FPS.

uart = UART(3, 115200)  # 初始化

while(True):

    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot()#.lens_corr(strength = 1.5, zoom = 1.2)
    blobs = img.find_blobs([line_threshold], pixels_threshold=100,roi=(60, 10, 30, 80))
    if len(blobs) == 1:
        # Draw a rect around the blob.
        b = blobs[0]
        img.draw_rectangle(b[0:4]) # rect
        img.draw_cross(b[5], b[6]) # cx, cy
        dist= b[6]*1.7148+29.407
        #dist= b[6]*1.7148+29.407
        print(dist)
        uart.write(bytearray([int(dist)]))  # 发送一个字节


    #print(clock.fps()) # Note: Your OpenMV Cam runs about half as fast while
    # connected to your computer. The FPS should increase once disconnected.
