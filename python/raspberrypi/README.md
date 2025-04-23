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
  def begin(self):
    '''!
      @brief Init sensor 
      @return True or False
    '''
    
  def get_data_flush(self):
    '''!
      @brief get_data_flush 
      @return True or False
    '''
    
  def get_date(self):
    '''!
      @brief Get date information, year, month, day 
      @return struct_utc_tim type, represents the returned year, month, day
    '''
    
  def get_utc(self):
    '''!
      @brief Get time information, hour, minute second 
      @return struct_utc_tim type, represents the returned hour, minute, second 
    '''
    
  def get_lat(self):
    '''!
      @brief Get latitude 
      @return struct_lat_lon type, represents the returned latitude 
    '''

  def get_lon(self):
    '''!
      @brief Get longitude 
      @return struct_lat_lon type, represents the returned longitude 
    '''
    
  def get_num_sta_used(self):
    '''!
      @brief Get the number of the used satellite used
      @return uint8_t type, represents the number of the used satellite
    '''

  def get_alt(self):
    '''!
      @brief Altitude information
      @return double type, represents altitude 
    '''
    
  def get_sep(self):
    '''!
      @brief At the height of geoid
      @return Float data(unit: degree)
    '''
    
  def get_hdop(self):
    '''!
      @brief Indicates the horizontal accuracy of positioning
      @return hdop
    '''

  def get_quality(self):
    '''!
      @brief get message Quality 
      @return message Quality
    '''
    
  def get_site_id(self):
    '''!
      @brief get site id
      @return site id  
    '''
  
  def get_dif_time(self):
    '''!
      @brief The number of seconds in which a differential signal was last received
      @return differential time
    '''

  def get_module(self):
    '''!
      @brief Get the Module run mode
      @return mode
    '''
      
  def set_module(self, mode):
    '''!
      @brief Set the Module
      @param mode 4G or lora
    '''
      
  def set_module_baud(self, baud):
    '''!
      @brief Set the Module Baud rate
      @param baud rate
    '''
    
  def get_moudle_baud(self):
    '''!
      @brief Get the Module baud
      @return baud
    '''
    
  def get_gnss_message(self, mode):
    '''!
      @brief Get different types of gps data
      @param mode
      @return char* 
    '''
    

  def get_all_gnss(self):
    '''!
      @brief Get all GNSS data
      @return gnss all data
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

- 2025/08/14 - Version 1.0.0 released.

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2025. (Welcome to our website)
