/*!
 * @file DFRobot_MHZ9041A.h
 * @brief Define the basic structure of the DFRobot_MHZ9041A class, the implementation of the basic methods
 * @copyright	Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [ZhixinLiu](zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 202-03-07
 * @url https://github.com/DFRobot/DFRobot_MHZ9041A
 */
#ifndef __DFRobot_GNSS_H__
#define __DFRobot_GNSS_H__

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
#include "SoftwareSerial.h"
#else
#include "HardwareSerial.h"
#endif


/**
 * @enum eFaultCode_t
 * @brief Types of sensor fault codes
 */
typedef enum {
  eSensorNormal = 0x00,                   // 00 Sensor operating normally
  eTempControlError = 0x01,               // 01 Temperature control error
  eAmbientTempError = 0x02,               // 02 Ambient temperature error
  eAmbientAndTempControlError = 0x03,     // 03 Ambient temperature error & temperature control error
  eLaserSignalWeak = 0x04,                // 04 Weak laser signal
  eAmbientAndSignalWeakError = 0x06,      // 06 Ambient temperature error & weak laser signal
  eLaserSignalError = 0x10,               // 16 Laser signal error
  eAmbientAndSignalError = 0x12,          // 18 Ambient temperature error & laser signal error
} eFaultCode_t;

/**
 * @enum eModuleMode_t
 * @brief sensor work mode
 */
typedef enum {
  ePassivityMode = 0x00,
  eActiveMode = 0x01,
} eWorkMode_t;

#define VID_H 0X33
#define TIME_OUT 200
#define REG_VID_H 0X02
#define REG_DEVICE_L 0X05
#define REG_VESION_H 0X0A
#define REG_LEL_H 0x0C
#define REG_TEMP_H 0x0E
#define REG_ERROR_CODE 0x10
#define REG_MODE 0x11
#define REG_RESET 0x12
#define REG_SOURCE_LEN 0x20
#define REG_SOURCE_DATA 0x21


class DFRobot_MHZ9041A{
public:
DFRobot_MHZ9041A();
~DFRobot_MHZ9041A();

/**
 * @fn setMode
 * @brief Set the working mode
 * @param mode Working mode
 * @note 0x00: Active mode, 0x01: Passive mode
 * @return null
 */
void setMode(eWorkMode_t mode);

/**
 * @fn getSourceData
 * @brief Get raw sensor data
 * @return Raw data string, up to 43 bytes in length
 */
String getSourceData(void);

/**
 * @fn getCH4Concentration
 * @brief Get methane (CH4) concentration
 * @return CH4 concentration value, two decimal places, the second digit is always 0, unit: %LEL
 */
float getCH4Concentration(void);

/**
 * @fn getTemperature
 * @brief Get ambient temperature
 * @return Temperature in degrees Celsius
 */
float getTemperature(void);

/**
 * @fn getErrorMsg
 * @brief Get error code information
 * @return Error code
 */
eFaultCode_t getErrorMsg(void);

/**
 * @fn getActiveData
 * @brief Get raw data in active reporting mode
 * @return Raw data string in active mode
 */
String getActiveData(void);

/**
 * @fn reset
 * @brief Reset the onboard methane sensor; hold the reset pin low for 2 seconds to complete the reset
 * @return null
 */
void reset(void);

/**
 * @fn setDeviceID
 * @brief Set the module address 0x03~0x7F
 * @return Returns 1 if successful, otherwise returns 0
 */
bool setDeviceID(uint8_t id);

/**
 * @fn getDeviceID
 * @brief Get the module address
 * @return Module address
 */
uint8_t getDeviceID(void);

protected:
  uint16_t crc16(uint8_t *data, uint16_t length);
private:
  uint8_t  __addr;
  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len) = 0;
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len) = 0;
  virtual int16_t readData(uint8_t *data);
  
};

class DFRobot_MHZ9041A_I2C:public DFRobot_MHZ9041A{
public:
  DFRobot_MHZ9041A_I2C(TwoWire *pWire=&Wire, uint8_t addr = 0x75);
  bool begin(void);
protected:
  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len);
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len);
  int16_t readData(uint8_t* data) override {
    return -1;  // 占位用
  }
private:
  TwoWire *__pWire;
  uint8_t __I2C_addr;
};

class DFRobot_MHZ9041A_UART:public DFRobot_MHZ9041A{
public:
#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  DFRobot_MHZ9041A_UART(SoftwareSerial *sSerial, uint32_t Baud);
#else
  DFRobot_MHZ9041A_UART(HardwareSerial *hSerial, uint32_t Baud ,uint8_t rxpin = 0, uint8_t txpin = 0);
#endif

  bool begin(void);
  int16_t readData(uint8_t *data);
protected:
  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len);
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len);
private:

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  SoftwareSerial *_serial;
#else
  HardwareSerial *_serial;
#endif
  uint32_t __baud;
  uint8_t __rxpin;
  uint8_t __txpin;
};
#endif
