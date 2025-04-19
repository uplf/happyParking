#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
# Untitled - By: lenovo - Fri Apr 11 2025

import sensor, image, time,pyb,json
from machine import UART
import time
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

clock = time.clock()

# 初始化 UART3，波特率 19200
uart = pyb.UART(3, 115200)

temp=0
state=[]
def Receive_Data(data):

    if data == 1:
        temp=temp+1
        uart.write(str(temp))
    elif data == 2:
        temp=9
        uart.write(str(temp))
    elif data == 3:
        pass
        uart.write(str(temp))

    # 转字符串并发送当前状态
    #注意是！！！字符串！！！damn





while True:
    clock.tick()

    #uart.write(3)  # 发送数据1
# 等待接收到数据
    if uart.any():

        data=uart.read(1)
        print(data)
        #uart.write(str(data))
        uart.write(str(data[0]))
        #data_1=data[0]
        #a=uart.readline().decode().strip()
        #strip删掉回车和换行#readline 传送某一个字符；decode 将某一个字符变成字符串
        #!!!注意是字符串！！！damn
        #print(data)
        #接收反馈，用来判断串口无输出的时候，#究竟是1.后半部分函数的问题，2.还是从机就没有接收到？
        #Receive_Data(data_1)


#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------

