# -*- coding:utf-8 -*-
""" 
  @file get_alcohol_data.py
  @brief Reading alcohol concentration, A concentration of one part per billion (PPB).
  @n step: we must first determine the iic device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
  @n       Then configure the mode of active and passive acquisition, Finally, alcohol data can be read.
  @n note: it takes time to stable oxygen concentration, about 3 minutes.
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author      [ZhixinLiu](zhixin.liu@dfrobot.com)
  version  V1.0
  date  2020-5-27
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_Ozone
"""
import sys
import time
sys.path.append("../..")
from DFRobot_Alcohol import *

COLLECT_NUMBER   = 1              # collect number, the collection range is 1-100
IIC_MODE         = 0x01            # default use IIC1
'''
   # The first  parameter is to select iic0 or iic1
   # The second parameter is the iic device address
   # The default address for iic is ADDRESS_3
   # ADDRESS_0                 = 0x72
   # ADDRESS_1                 = 0x73
   # ADDRESS_2                 = 0x74
   # ADDRESS_3                 = 0x75
'''
#alcohol = DFRobot_Alcohol_IIC (IIC_MODE ,ADDRESS_3)
alcohol = DFRobot_Alcohol_UART(9600)
'''
   # The module is configured in automatic mode or passive
   # MEASURE_MODE_AUTOMATIC    = 0x00           # active  mode
   # MEASURE_MODE_PASSIVE      = 0x01           # passive mode
''' 
alcohol.set_mode(MEASURE_MODE_AUTOMATIC)
time.sleep(1)
while(1):
  ''' Smooth data collection £¬the collection range is 1-100 '''
  alcohol_concentration = alcohol.get_alcohol_data(COLLECT_NUMBER);
  if alcohol_concentration == ERROR:
    print("Please check the connection !")
  else:
    print("alcohol concentration is %d PPB."%alcohol_concentration)
  time.sleep(1)