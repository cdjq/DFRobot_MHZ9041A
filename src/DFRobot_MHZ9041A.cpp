/*!
 * @file DFRobot_MHZ9041A.cpp
 * @brief Define the basic structure of the DFRobot_MHZ9041A class, the implementation of the basic methods
 * @copyright	Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [ZhixinLiu](zhixin.liu@dfrobot.com)
 * @version V0.5.0
 * @date 2025-04-23
 * @url https://github.com/DFRobot/DFRobot_MHZ9041A
 */
#include "DFRobot_MHZ9041A.h"

DFRobot_MHZ9041A::DFRobot_MHZ9041A(void){}
DFRobot_MHZ9041A::~DFRobot_MHZ9041A(void){}

uint32_t DFRobot_MHZ9041A::baudMatch(eModuleBaud_t baud)
{
  if(baud == eBaud9600){
    return 9600;
  }else if(baud == eBaud19200){
    return 19200;
  }else if(baud == eBaud38400){
    return 38400;
  }else if(baud == eBaud57600){
    return 57600;
  }else if(baud == eBaud115200){
    return 115200;
  }else{
    return 115200;
  }
}

void DFRobot_MHZ9041A::setBaud(eModuleBaud_t baud)
{
  uint8_t buffer[2] = {0};
  buffer[0] = (uint8_t)baud;
  writeReg(REG_BAUD_L, buffer, 1);
  return;
}

uint32_t DFRobot_MHZ9041A::getBaud(void)
{
  uint8_t buffer[2] = {0};
  readReg(REG_BAUD_L, buffer, 1);
	return baudMatch((eModuleBaud_t)buffer[0]);
}

void DFRobot_MHZ9041A::setMode(eWorkMode_t mode)
{
  uint8_t buffer[1] = {0};
  buffer[0] = (uint8_t)mode;
  writeReg(REG_MODE, buffer, 1);
  delay(100);
}

String DFRobot_MHZ9041A::getSourceData(void)
{
  String sourceData = "";
  uint8_t buffer[50] = {0};
  readReg(REG_SOURCE_LEN, buffer, 1);
  uint8_t len = buffer[0];
  if(len > 44){
    sourceData = "data error";
  }
  delay(10);
  readReg(REG_SOURCE_DATA, buffer, len);
  for(uint8_t i = 0; i < len; i++){
    sourceData += String((char)buffer[i]);
  }
  delay(10);
  return sourceData;
}


String DFRobot_MHZ9041A::getActiveData(void)
{
  String sourceData = "";
  uint8_t buffer[100] = {0};
  int16_t len = readData(buffer);
  if(len < 0){
    return sourceData;
  }
  for(uint8_t i = 0; i < len; i++){
    sourceData += String((char)buffer[i]);
  }
  return sourceData;

}

float DFRobot_MHZ9041A::getCH4Concentration(void)
{
  uint8_t buffer[2] = {0};
  readReg(REG_LEL_H, buffer, 2);
  uint16_t rawValue = ((uint16_t)buffer[0] << 8) | buffer[1];
  rawValue = (rawValue + 5) / 10 * 10;          // Round to the nearest 10
  float concentration = rawValue / 100.0f;
  delay(5);
  return concentration;
}


float DFRobot_MHZ9041A::getTemperature(void)
{
  uint8_t buffer[2] = {0};
  readReg(REG_TEMP_H, buffer, 2);
  uint16_t rawValue = ((uint16_t)buffer[0] << 8) | buffer[1];
  float temp = rawValue / 100.0f;
  delay(5);
  return temp;
}
eFaultCode_t DFRobot_MHZ9041A::getErrorMsg(void)
{
  uint8_t buffer[1] = {0};
  readReg(REG_ERROR_CODE, buffer, 1);
  delay(5);
  return (eFaultCode_t)buffer[0];
}

void DFRobot_MHZ9041A::reset(void)
{
  uint8_t buffer[1] = {0};
  buffer[0] = 0X01;
  writeReg(REG_RESET, buffer, 1);
  delay(2000);
}

bool DFRobot_MHZ9041A::setDeviceID(uint8_t id)
{
  if(id > 0x7F || id < 0x03){
    return false;
  }
  uint8_t buffer[1] = {0};
  buffer[0] = id;
  writeReg(REG_DEVICE_L, buffer, 1);
  delay(5);
  return true;
}

uint8_t DFRobot_MHZ9041A::getDeviceID(void)
{
  uint8_t buffer[1] = {0};
  readReg(REG_DEVICE_L, buffer, 1);
  delay(5);
  return buffer[0];
}


uint16_t DFRobot_MHZ9041A::crc16(uint8_t *data, uint16_t length)
{
  uint16_t crc = 0xFFFF;
  for (uint16_t i = 0; i < length; ++i) {
      crc ^= data[i];
      for (uint8_t j = 0; j < 8; ++j) {
          if (crc & 0x0001) {
              crc = (crc >> 1) ^ 0xA001;
          } else {
              crc >>= 1;
          }
      }
  }
  return crc;
}

DFRobot_MHZ9041A_I2C::DFRobot_MHZ9041A_I2C(TwoWire *pWire, uint8_t addr)
{
  __pWire = pWire;
  this->__I2C_addr = addr;
}

bool DFRobot_MHZ9041A_I2C::begin()
{
  __pWire->begin();
  //__pWire->setClock(100000);
  __pWire->beginTransmission(__I2C_addr);
  if(__pWire->endTransmission() == 0){
    return true;
  }
  return false;
}

int16_t DFRobot_MHZ9041A_I2C::readData(uint8_t *data)
{
  (void)data;
  return -1;
}

void DFRobot_MHZ9041A_I2C::writeReg(uint8_t reg, uint8_t *data, uint8_t len)
{
  __pWire->beginTransmission(this->__I2C_addr);
  __pWire->write(reg);
  for(uint8_t i = 0; i < len; i++){
    __pWire->write(data[i]);
  }
  __pWire->endTransmission();
}

int16_t DFRobot_MHZ9041A_I2C::readReg(uint8_t reg, uint8_t *data, uint8_t len)
{
  int i = 0;
  uint8_t length = len;
  while(length)
  {
    if(length > 32){
      __pWire->beginTransmission(this->__I2C_addr);
      __pWire->write(reg);
      if(__pWire->endTransmission() != 0){
        return -1;
      }
      __pWire->requestFrom((uint8_t)this->__I2C_addr,(uint8_t)32);
      while (__pWire->available()){
        //if(i < len-1){
          data[i++]=__pWire->read();
        //}
      }
      length -= 32;
    }else{
      __pWire->beginTransmission(this->__I2C_addr);
      __pWire->write(reg+i);
      if(__pWire->endTransmission() != 0){
        return -1;
      }
      __pWire->requestFrom((uint8_t)this->__I2C_addr,(uint8_t)length);
      while (__pWire->available()){
        //if(i < len-1){
          data[i++]=__pWire->read();
        //}
      }
      length = 0;
    }
  }
  return 0;
}


#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  DFRobot_MHZ9041A_UART::DFRobot_MHZ9041A_UART(SoftwareSerial *sSerial, uint32_t Baud)
  {
    this->_serial = sSerial;
    this->__baud = Baud;
    _serial->begin(this->__baud);
  }
#else
  DFRobot_MHZ9041A_UART::DFRobot_MHZ9041A_UART(HardwareSerial *hSerial, uint32_t Baud ,uint8_t rxpin, uint8_t txpin)
  {
    this->_serial = hSerial;
    this->__baud = Baud;
    this->__txpin = txpin;
    this->__rxpin = rxpin;
  }
#endif

bool DFRobot_MHZ9041A_UART::begin()
{
  uint8_t buffer[2] = {0};
  #ifdef ESP32
    _serial->begin(this->__baud, SERIAL_8N1, __txpin, __rxpin);
    delay(100);
  #elif defined(ARDUINO_AVR_UNO) || defined(ESP8266)
    // nothing use software
  #else
    _serial->begin(this->__baud);  // M0 cannot create a begin in a construct
  #endif

  while(_serial->available()){
    _serial->read();
  }

  this->readReg(REG_VID_H, buffer, 2);
  if(buffer[0] == VID_H){
    _serial->flush();
    for(uint8_t i = 0; i < 50; i++){
      _serial->read();
    }
    delay(5);
    return true;
  }else{
    return false;
  }
}

void DFRobot_MHZ9041A_UART::writeReg(uint8_t reg, uint8_t *data, uint8_t len)
{
  uint8_t i = 0;
  uint8_t temp[20] = {0xAA, 0x55, 0x00, 0x00, len};
  temp[3] = reg | 0x80;
  for(i = 0; i < len; i++){
    temp[i+5] = data[i];
  }
  uint16_t crc = crc16(temp+2, len+3);
  uint8_t crc_h = (crc >> 8) & 0xFF;
  uint8_t crc_l = crc & 0xFF;
  temp[i+5] = crc_h;
  temp[i+6] = crc_l;
  temp[i+7] = 0x0D;
  temp[i+8] = 0x0A;
  _serial->write(temp, len+9);
  delay(10);
  uint32_t nowtime = millis();
  while(millis() - nowtime < TIME_OUT){
    while(_serial->available()){
      _serial->read();
      _serial->flush();
    }
  }
}

int16_t DFRobot_MHZ9041A_UART::readData(uint8_t *data)
{
  uint8_t i = 0;
  uint32_t nowtime = millis();
  while(millis() - nowtime < TIME_OUT){
    while(_serial->available()){
      data[i++] = _serial->read();
      if(i-1 > 100) return -1;
    }
  }
  _serial->flush();
  return i;
}

int16_t DFRobot_MHZ9041A_UART::readReg(uint8_t reg, uint8_t *data, uint8_t len)
{
  uint8_t i = 0;
  uint8_t recv[100] = {0};
  uint8_t temp[20] = {0xAA, 0x55, 0x00, 0x00, 0x00};
  temp[3] = reg&0x7F;
  uint16_t crc = crc16(temp+2, 3);
  uint8_t crc_h = (crc >> 8) & 0xFF;
  uint8_t crc_l = crc & 0xFF;
  temp[5] = crc_h;
  temp[6] = crc_l;
  temp[7] = 0x0D;
  temp[8] = 0x0A;
  _serial->write(temp, 9);
  delay(7);
  uint32_t nowtime = millis();
  while(millis() - nowtime < TIME_OUT){
    while(_serial->available()){
      recv[i++] = _serial->read();
      if(i > 100) return -1;
      if(i == len+9) {
        memcpy(data, recv+5, len);
        _serial->flush(); 
        return 0; 
      }
    }
  }
  _serial->flush();
  return -1;
}
