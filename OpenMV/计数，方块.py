# OpenMV 黑色色块识别计数
import sensor, image, time
from pyb import UART

# 初始化摄像头
sensor.reset()
sensor.set_pixformat(sensor.RGB565) # 彩色图像
sensor.set_framesize(sensor.QVGA)    # 分辨率320x240
sensor.skip_frames(time=2000)        # 给传感器一些时间来稳定
sensor.set_auto_gain(False)          # 关闭自动增益（重要）
sensor.set_auto_whitebal(False)      # 关闭白平衡（重要）

clock = time.clock()

uart = UART(3, 115200)  # 初始化 UART3，波特率 115200
uart.init(115200, bits=8, parity=None, stop=1) # init with given parameters

# 设置黑色识别的色块阈值（根据实际情况可能需要调试）
black_threshold = (0, 40, -40, 40, -40, 40)

# 设定检测区域（例如：图像中心区域）
#roi = (120, 100, 20, 16)# x, y, w, h

# 设定识别色块的最小和最大面积，单位是像素
min_area = 100
max_area = 10000

# 通用短暂休眠时间 (秒)
short_sleep = 0.3

# 达到3或5次后的长休眠时间 (秒)
long_sleep = 1

print("开始识别...")

const_value1= 1  #计数识别，达到个数发1
const_value2= 2  #点位识别，找到发2

Status=1


def usartScan():
    global Status
    if uart.any() == 0:
        return 0
    else:
        Status = int.from_bytes(uart.read(1), 'little')  # 或 decode 后转 int
        print("接收到串口数据：", Status)
        return Status



def detLoop(countMAX, roi):
    black_blob_count=0      # 记录识别到的黑色色块数
    while (black_blob_count <countMAX):
        clock.tick()
        img = sensor.snapshot()  # 持续刷新，防止图像卡住
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

            # 根据识别次数控制休眠
            if black_blob_count == countMAX :
                uart.write(bytearray([const_value1]))  # 发送一个字节
                print("达到特殊计数 {} 次，退出循环".format(black_blob_count))
                time.sleep(long_sleep)
               


            else:
                print("短暂休眠...")
                time.sleep(short_sleep)

        else:
            # 即使没有找到色块，也继续刷新，避免摄像头卡死
            pass
    print("退出计数")

def findblob(roi):
    # 点位识别函数
    print("识别点位")
    black_blob_count = 0
    while (black_blob_count <5):
        clock.tick()
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



while True:
    black_blob_count=0
    usartScan() #更新
    print("当前Status值为 {} ".format(Status))
    if  Status == 1:
        roi = (155, 135, 20, 16)
        detLoop(4, roi)
        Status=0
    elif Status == 2:
        roi = (143, 200, 20, 16)
        findblob(roi)
        Status=0
    elif Status == 3:
        roi = (100, 100, 20, 16)
        detLoop(6, roi)

    else:
        # 无效指令，可略过或等待下次
        img = sensor.snapshot()
        pass



    #uart.write(bytearray([const_value1]))  # 发送一个字节
    #time.sleep_ms(1000)  # 延迟 1000 毫秒，也就是一秒钟
