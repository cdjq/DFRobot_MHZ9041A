# -*- coding: utf-8 -*-
'''!
  @file DFRobot_MHZ9041A.py
  @brief Define the Python implementation for DFRobot MHZ9041A methane sensor
  @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license MIT License
  @author [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version V1.0.0
  @date 2025-04-23
  @url https://github.com/DFRobot/DFRobot_MHZ9041A
'''
import sys
import serial
import time
import smbus

class eFaultCode_t:
    SENSOR_NORMAL = 0x00
    TEMP_CONTROL_ERROR = 0x01
    AMBIENT_TEMP_ERROR = 0x02
    AMBIENT_TEMP_CONTROL_ERROR = 0x03
    LASER_SIGNAL_WEAK = 0x04
    AMBIENT_SIGNAL_WEAK_ERROR = 0x06
    LASER_SIGNAL_ERROR = 0x10
    AMBIENT_SIGNAL_ERROR = 0x12

class eWorkMode_t:
    PASSIVITY_MODE = 0x00
    ACTIVE_MODE = 0x01

I2C_MODE = 0
UART_MODE = 1
  
REG_VID_H = 0x02
REG_DEVICE_L = 0x05
REG_LEL_H = 0x0C
REG_TEMP_H = 0x0E
REG_ERROR_CODE = 0x10
REG_MODE = 0x11
REG_RESET = 0x12
REG_SOURCE_LEN = 0x20
REG_SOURCE_DATA = 0x21
VID_H = 0x33
TIME_OUT = 0.2 # seconds

class DFRobot_MHZ9041A(object):
    __uart_i2c     =  0
    ERROR_COUNT     = 0X05
    def __init__(self, bus, Baud):
        if bus != 0:
            self.i2cbus = smbus.SMBus(bus)
            self.__uart_i2c = I2C_MODE
        else:
            self.ser = serial.Serial("/dev/ttyAMA0", baudrate=Baud,stopbits=1, timeout=0.5)
            self.__uart_i2c = UART_MODE
            if self.ser.isOpen == False:
                self.ser.open()
        self._connect = 0

    def set_mode(self, mode):
        '''!
          @brief Set the module operation mode
          @param mode Operation mode value to configure
        '''
        buffer = [mode]
        self.write_reg(REG_MODE, buffer)
        time.sleep(0.1)

    def get_source_data(self):
        '''!
          @brief Retrieve raw sensor data
          @return Raw data as string. Returns "data error" if length exceeds 44 bytes
        '''
        len_buf = self.read_reg(REG_SOURCE_LEN, 1)
        if len_buf is None or len_buf[0] > 44:
            return "data error"
        data = self.read_reg(REG_SOURCE_DATA, len_buf[0])
        return ''.join([chr(b) for b in data])

    def get_active_data(self):
        '''!
          @brief Get real-time data in active state
          @return Real-time data as string. Empty string if no data
        '''
        data = self.read_data()
        return ''.join([chr(b) for b in data]) if data else ""

    def get_ch4_concentration(self):
        '''!
          @brief Measure methane (CH4) concentration
          @return Concentration value in %VOL. Returns 0.0 if read fails
          @note Includes calibration: raw_value = (raw_value + 5) // 10 * 10
        '''
        data = self.read_reg(REG_LEL_H, 2)
        if data is None:
            return 0.0
        raw_value = (data[0] << 8) | data[1]
        raw_value = (raw_value + 5) // 10 * 10  # Calibration
        return raw_value / 100.0

    def get_temperature(self):
        '''!
          @brief Read sensor temperature
          @return Temperature value in ℃. Returns 0.0 if read fails
        '''
        data = self.read_reg(REG_TEMP_H, 2)
        if data is None:
            return 0.0
        raw_value = (data[0] << 8) | data[1]
        return raw_value / 100.0

    def get_error_code(self):
        '''!
          @brief Retrieve device error status
          @return Error code (enum type). Returns normal status if no data
        '''
        data = self.read_reg(REG_ERROR_CODE, 1)
        return data[0] if data else eFaultCode_t.SENSOR_NORMAL

    def reset(self):
        '''!
          @brief Perform device soft reset
        '''
        self.write_reg(REG_RESET, [0x01])
        time.sleep(2)

    def set_device_id(self, dev_id):
        '''!
          @brief Configure I2C device address
          @param dev_id Target address (0x03~0x7F)
          @return True on success
          @throws ValueError If address is out of valid range
        '''
        if not (0x03 <= dev_id <= 0x7F):
            raise ValueError("Device ID must be between 0x03 and 0x7F")
        self.write_reg(REG_DEVICE_L, [dev_id])
        return True

    def get_device_id(self):
        '''!
          @brief Read current I2C device address
          @return Device address. Returns 0 if read fails
        '''
        data = self.read_reg(REG_DEVICE_L, 1)
        return data[0] if data else 0

    def _crc16(self, data):
        crc = 0xFFFF
        for byte in data:
            crc ^= byte
            for _ in range(8):
                if crc & 0x0001:
                    crc = (crc >> 1) ^ 0xA001
                else:
                    crc >>= 1
        return crc

    def _error_handling(self, lens=0):
        result = [0] * lens
        self._connect += 1    
        #print("rtk_lora iic communication faild, please wait")
        time.sleep(0.5)
        return result

class DFRobot_MHZ9041A_I2C(DFRobot_MHZ9041A):
    def __init__(self, bus, addr):
        self.__addr = addr
        super(DFRobot_MHZ9041A_I2C, self).__init__(bus,0)
        
    def begin(self):
        try:
            self.i2cbus.read_i2c_block_data(self.__addr, 0, 1)
            return True
        except:
            return False


    def write_reg(self, reg, data):
        self._connect = 0
        while True:
            try:
                self.i2cbus.write_i2c_block_data(self.__addr, reg, data)
                break
            except:
                self._error_handling()
            if self._connect > self.ERROR_COUNT:
                raise ValueError("Please check the rtk_lora connection or Reconnection sensor!!!")
  
    def read_reg(self, reg, length):
        self._connect = 0
        MAX_LEN = 32
        result = []
        offset = 0
        while offset < length:
            try:
                read_len = min(MAX_LEN, length - offset)
                chunk = self.i2cbus.read_i2c_block_data(self.__addr, reg + offset, read_len)
                result += chunk
                offset += read_len
            except:
                result = self._error_handling(length)
                self._connect += 1
            if self._connect > self.ERROR_COUNT:
                raise ValueError("Please check the rtk_lora connection or Reconnection sensor!!!")
        return result


class DFRobot_MHZ9041A_UART(DFRobot_MHZ9041A):
    def __init__(self, Baud):
        self.__Baud = Baud
        super(DFRobot_MHZ9041A_UART, self).__init__(0, Baud)

    def begin(self):
        self.ser.reset_input_buffer()
        data = self.read_reg(REG_VID_H, 2)
        if data and data[0] == VID_H:
            self.ser.reset_input_buffer()
            return True
        return False

    def write_reg(self, reg, data):
        packet = [0xAA, 0x55, 0x00, reg | 0x80, len(data)]
        packet += data
        crc = self._crc16(packet[2:])
        packet += [crc >> 8, crc & 0xFF, 0x0D, 0x0A]
        test = [0x00,0x11]
        self.ser.write(packet)
        time.sleep(0.05)
        self.ser.reset_input_buffer()

    def read_reg(self, reg, length):
        packet = [0xAA, 0x55, 0x00, reg & 0x7F, 0x00]
        crc = self._crc16(packet[2:])
        packet += [crc >> 8, crc & 0xFF, 0x0D, 0x0A]
        self.ser.write(packet)
        time.sleep(0.01)
        return self._read_response(length)

    def read_data(self):
        start_time = time.time()
        data = []
        while time.time() - start_time < 0.5:
            if self.ser.in_waiting:
                data.append(self.ser.read(1)[0])
                if len(data) > 100:
                    return None
        char_list = [ord(c) for c in data]
        return char_list

    def _read_response(self, length):
        start_time = time.time()
        data = []
        idle_time = 0.05    
        last_recv_time = time.time()
        while time.time() - start_time < TIME_OUT:
            if self.ser.in_waiting:
                chunk = self.ser.read(self.ser.in_waiting)
                data.extend(chunk)
                last_recv_time = time.time()
            else:
                if time.time() - last_recv_time > idle_time:
                    break
            if len(data) >= length + 9:
                break
        if len(data) >= length + 9:
            uint8_list = [ord(c) for c in data]
            return uint8_list[5:5+length]
        else:
            return ""