import sensor, image, time
from pyb import UART

uart = UART(3, 115200)  # 初始化 UART3，波特率 115200

const_value = 0  # 要发送的固定常数

while True:
    const_value=const_value+1
    uart.write(bytearray([const_value]))  # 发送一个字节
    time.sleep_ms(1000)  # 延迟 1000 毫秒，也就是一秒钟
