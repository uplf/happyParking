import sensor, image, time
from pyb import UART

# 为了让颜色追踪效果很好，理想情况下你应该处在一个非常非常非常受控的环境中，
# 即光照是恒定不变的……

line_threshold = (0, 110)

sensor.reset() # 初始化摄像头传感器。
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA) # 使用 QQVGA 分辨率以提高速度。
sensor.skip_frames(10) # 跳过一些帧，使新设置生效。
sensor.set_auto_whitebal(False) # 关闭自动白平衡。
clock = time.clock() # 用于跟踪每秒帧数。

K = 210  # 此值需通过测量获得
uart = UART(3, 115200)  # 初始化串口

# 模式标志
mode = 2  # 初始为模式1

# 通用短暂休眠时间 (秒)
short_sleep = 0.3

# 达到3或5次后的长休眠时间 (秒)
long_sleep = 1


def linefollow():
    sensor.set_pixformat(sensor.GRAYSCALE)# 使用灰度图像
    img = sensor.snapshot() # 拍照并返回图像
    red_threshold = (30, 100, 15, 127, 15, 127)
    print("模式1 - 识别目标并发送距离")
    blobs = img.find_blobs([line_threshold], pixels_threshold=100, roi=(60, 10, 30, 80))
    if len(blobs) == 1:
        # 在目标区域画一个矩形
        b = blobs[0]
        img.draw_rectangle(b[0:4]) # 绘制矩形框
        img.draw_cross(b[5], b[6]) # 绘制中心十字
        Lm = (b[2]+b[3])/2  # 计算目标尺寸（平均宽高）
        length = K / Lm     # 根据比例系数计算距离
        length_int = int(length)
        dist = b[6] * 1.7148 + 29.407  # 通过 y 坐标拟合计算距离
        print(dist)
        #print(length)
        #print(length_int)
        uart.write(bytearray([int(dist)]))  # 发送一个字节数据


def findblob(roi):
    # 点位识别函数
    print("识别点位")
    min_area = 100
    max_area = 10000
    const_value2= 2
    img = sensor.snapshot() # 拍照并返回图像
    black_blob_count = 0
    black_threshold = (0, 40, -40, 40, -40, 40)
    while (black_blob_count <5):
        img = sensor.snapshot()
        img.draw_rectangle(roi, color=(255, 0, 0))  # 在屏幕上画出ROI区域，便于调试观察

        # 只在ROI区域内寻找色块
        blobs = img.find_blobs([black_threshold], roi=roi, area_threshold=min_area, pixels_threshold=min_area, merge=True)

        # 过滤符合大小要求的色块
        valid_blobs = [b for b in blobs if min_area <= b.pixels() <= max_area]

        if valid_blobs:
            black_blob_count += 1
            print("检测到黑色色块，总计：", black_blob_count)

            # 在图像上画出识别到的色块
            for blob in valid_blobs:
                img.draw_rectangle(blob.rect(), color=(0,255,0))
                img.draw_cross(blob.cx(), blob.cy(), color=(0,255,0))

            if black_blob_count == 1 :
                uart.write(bytearray([const_value2]))  # 发送一个字节
                print("达到特殊计数 {} 次，长时间休眠中...".format(black_blob_count))
                time.sleep(long_sleep)

            else:
                print("短暂休眠...")
                time.sleep(short_sleep)
    print("退出识别点位")


mode=2

while(True):

    clock.tick() # 跟踪每次快照之间的时间。

    # 检查串口是否有数据
    if uart.any():
        cmd = uart.read(1)  # 读取1个字节
        if cmd == b'1':
            mode = 1  # 模式1
            print("进入模式1")
        elif cmd == b'2':
            mode = 2  # 切换为模式2
            print("进入模式2")


    # 模式1：识别目标并发送距离
    if mode == 1:
        linefollow()

    elif mode==2:
        # 模式2：查找点位
        sensor.set_pixformat(sensor.RGB565)
        roi = (60, 80, 20, 16)
        findblob(roi)

    else:
        # 无效指令，可略过或等待下次
        img = sensor.snapshot()
        pass

















