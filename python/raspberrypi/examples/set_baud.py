# -*- coding: utf-8 -*
'''!
  @file set_baud.py
  @brief set moude and baud rate
  @copyright  Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license    The MIT License (MIT)
  @author     [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version    V1.0
  @date       2025-05-14
  @url https://github.com/DFRobot/DFRobot_MHZ9041A
'''
from __future__ import print_function
import sys
import os
sys.path.append("../")
import time
from DFRobot_MHZ9041A import *

# only support I2C mode
I2C_1 = 0x01
ch4 = DFRobot_MHZ9041A_I2C (I2C_1, 0x34)
    
def setup():
  while(ch4.begin() == False):
    print("Sensor initialize failed!!")
    time.sleep(1)
  print("Sensor initialize success!!")
  #ch4.reset()
  old_baud = ch4.get_baud()
  print("Current baud rate:", old_baud)
  # set new baud rate
  ch4.set_baud(eBaud_t.BAUD_115200)
  print("Baud rate set command sent!")
  time.sleep(1)
  new_baud = ch4.get_baud()
  print("Updated baud rate:", new_baud)
  print("Note: The new baud rate takes effect after power cycling the device.")
  
def loop():
  exit()
  
if __name__ == "__main__":
  setup()
  while True:
    loop()
