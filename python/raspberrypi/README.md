# DFRobot_MHZ9041A
- [中文版](./README_CN.md)
The MH-Z9041A Laser Methane Gas Sensor is a household-type methane sensor that utilizes Tunable Diode Laser Absorption Spectroscopy (TDLAS) for methane gas detection. It features a dual-pass optical path structure, offering excellent gas selectivity, no dependence on oxygen, and a long service life.

Equipped with built-in temperature control and compensation algorithms, the sensor achieves accurate methane concentration measurement. It also provides a serial output interface, making it easy to use and integrate.

![效果图](../../resources/images/xxx.jpg)

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

Provides an Arduino library that has the following features:
  Face recognition routine

## Installation
1. Download the library to Raspberry Pi first before use.

```
sudo git clone https://github.com/DFRobot/DFRobot_MHZ9041A
```

1. Open and run the routine. To execute a routine demo_x.py, enter python demo_x.py in the command line. For example, to execute the routine get_gnss.py, you need to enter:

```
python  get_active_data.py
or 
python2 get_concentration.py
or 
python3 set_device_ID.py

```

## Methods

```python
  def set_baud(self, baud):
    '''!
      @brief Set the module baud rate
      @param baud: eBaud_t
    '''

  def get_baud(self):
    '''!
      @brief Get the current baud rate
      @return baud [9600, 19200, 38400, 57600, 115200]
    '''
          
  def set_mode(self, mode):
    '''!
      @brief Set the module operation mode
      @param mode Operation mode value to configure
    '''

  def get_source_data(self):
    '''!
      @brief Retrieve raw sensor data
      @return Raw data as string. Returns "data error" if length exceeds 44 bytes
    '''

  def get_active_data(self):
    '''!
      @brief Get real-time data in active state
      @return Real-time data as string. Empty string if no data
    '''

  def get_ch4_concentration(self):
    '''!
      @brief Measure methane (CH4) concentration
      @return Concentration value in %VOL. Returns 0.0 if read fails
      @note Includes calibration: raw_value = (raw_value + 5) // 10 * 10
    '''

  def get_temperature(self):
    '''!
      @brief Read sensor temperature
      @return Temperature value in ℃. Returns 0.0 if read fails
    '''

  def get_error_code(self):
    '''!
      @brief Retrieve device error status
      @return Error code (enum type). Returns normal status if no data
    '''

  def reset(self):
    '''!
      @brief Perform device soft reset
    '''

  def set_device_id(self, dev_id):
    '''!
      @brief Configure I2C device address
      @param dev_id Target address (0x03~0x7F)
      @return True on success
      @throws ValueError If address is out of valid range
    '''

  def get_device_id(self):
    '''!
      @brief Read current I2C device address
      @return Device address. Returns 0 if read fails
    '''
```

## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |     √     |            |          |         |
| RaspberryPi4 |           |            |    √     |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## History

- 2025/04/23 - Version 1.0.0 released.

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2025. (Welcome to our website)
