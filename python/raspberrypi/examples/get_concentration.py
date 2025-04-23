# -*- coding: utf-8 -*
'''!
  @file get_concentration.py
  @brief get ch4 concentration and temperature
  @copyright  Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license    The MIT License (MIT)
  @author     [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version    V1.0
  @date       2025-04-23
  @url https://github.com/DFRobot/DFRobot_MHZ9041A
'''
from __future__ import print_function
import sys
import os
sys.path.append("../")
import time
from DFRobot_MHZ9041A import *

'''
  Select to use i2c or UART
  I2C_MODE
  UART_MODE
'''
ctype = I2C_MODE

if ctype == I2C_MODE:
  I2C_1 = 0x01
  ch4 = DFRobot_MHZ9041A_I2C (I2C_1, 0x34)
elif ctype == UART_MODE:
  ch4 = DFRobot_MHZ9041A_UART(115200)
    
def setup():
  while(ch4.begin() == False):
    print("Sensor initialize failed!!")
    time.sleep(1)
  print("Sensor initialize success!!")
  ch4.set_mode(eWorkMode_t.PASSIVITY_MODE)
  #ch4.reset()
  
def loop():
  data = ch4.get_ch4_concentration()
  print("CH4 concentration: ", data, "LEL")
  temp = ch4.get_temperature()
  print("Temperature: ", temp, "C")
  error_code = ch4.get_error_code()
  print("Error code: ", error_code)
  source = ch4.get_source_data()
  print("Source data: ", source)
  print("--------------------------------------------------")
  time.sleep(1)
  
if __name__ == "__main__":
  setup()
  while True:
    loop()
