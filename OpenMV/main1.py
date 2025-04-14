import sensor, image, time,pyb,json
from machine import UART
import time
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
clock = time.clock()
uart = pyb.UART(3, 115200)
state=[]



def uart_scan():
	if uart.any():
		uart_rec=uart.readline().decode().strip()
		return uart_rec
	else :
		return 0

def usart_test():
	for i in range(16):
		uart.write(i)
		if(uart_scan()==2):
			return
	return

def Receive_Data(data):
	if data == "1":
		state.append("a")
	elif data == "2":
		state.append("b")
	elif data == "3":
		state.append("c")
	uart.write(str(state) + '\n')
while True:
	clock.tick()
	if uart.any():
		a=uart.readline().decode().strip()
		print(a)
		Receive_Data(a)