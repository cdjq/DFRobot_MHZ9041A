# -*- coding: utf-8 -*
'''!
  @file get_active_data.py
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

# only uart mode
ch4 = DFRobot_MHZ9041A_UART(115200)
        
def setup():
  while(ch4.begin() == False):
    print("Sensor initialize failed!!")
    time.sleep(1)
  print("Sensor initialize success!!")
  ch4.set_mode(eWorkMode_t.ACTIVE_MODE)
  
def loop():
  data = ch4.get_active_data()
  if data != "":
    print("Active data: ", data)
  time.sleep(0.5)

if __name__ == "__main__":
  setup()
  while True:
    loop()
