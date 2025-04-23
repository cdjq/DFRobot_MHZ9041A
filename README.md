# DFRobot_MHZ9041A
- [中文版](./README_CN.md)
The MH-Z9041A Laser Methane Gas Sensor is a household-type methane sensor that utilizes Tunable Diode Laser Absorption Spectroscopy (TDLAS) for methane gas detection. It features a dual-pass optical path structure, offering excellent gas selectivity, no dependence on oxygen, and a long service life.

Equipped with built-in temperature control and compensation algorithms, the sensor achieves accurate methane concentration measurement. It also provides a serial output interface, making it easy to use and integrate.

This sensor combines mature laser gas absorption detection technology with a stable optical design and precise circuit engineering, resulting in a high-performance gas sensor.
![效果图](resources/images/xxx.jpg)

## Product Link(https://www.dfrobot.com)

    SKU：SEN0654

## Table of Contents

* [Summary](#Summary)
* [Installation](#Installation)
* [Methods](#Methods)
* [Compatibility](#Compatibility)
* [History](#History)
* [Credits](#Credits)

## Summary

Provide an Arduino library for the ch4 module with the following features:
Obtain the methane concentration

## Installation
There are two methods for using this library:<br>
1. Open Arduino IDE, search for "DFRobot_MHZ9041A" on the status bar in Tools ->Manager Libraries and install the library.<br>
2. Download the library file before use, paste it into \Arduino\libraries directory, then open the examples folder and run the demo in the folder.<br>

## Methods

```C++
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
 * @brief Set the module address,range 0x03~0x7F
 * @return Returns 1 if successful, otherwise returns 0
 */
bool setDeviceID(uint8_t id);

/**
 * @fn getDeviceID
 * @brief Get the module address
 * @return Module address
 */
uint8_t getDeviceID(void);
```

## Compatibility

MCU                | Work Well    |   Work Wrong    | Untested    | Remarks
------------------ | :----------: | :-------------: | :---------: | :----:
Arduino Uno        |      √       |                 |             |
Arduino MEGA2560   |      √       |                 |             |
Arduino Leonardo   |      √       |                 |             |
FireBeetle-ESP8266 |      √       |                 |             |
FireBeetle-ESP32   |      √       |                 |             |
FireBeetle-M0      |      √       |                 |             |
Micro:bit          |      √       | nonsupport uart |             |


## History

- 2025/03/26 - Version V0.1.0 released.

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2025. (Welcome to our website)
