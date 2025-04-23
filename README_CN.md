# DFRobot_MHZ9041A
- [English Version](./README.md)
MH-Z9041A 激光甲烷气体传感器是一个家用型甲烷传感器，基于可调谐激光气体吸收技术（TDLAS）对甲烷气体进行检测，内部采用对射光路结构，具有优异的气体选择性、无氧气依赖性、寿命长等特点；内置了控温算法、温度补偿算法，实现对甲烷气体的精确测量；具有串口输出接口，方便使用。该传感器是将成熟的激光气体吸收检测技术与稳定光路设计和电路设计紧密结合而制作出的高性能传感器。

![正反面svg效果图](/resources/images/xxx.jpg) 

## 产品链接(https://www.dfrobot.com.cn)

    SKU：SEN0654

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

提供一个Arduino库给ch4模块，此库具有以下功能：
  获取甲烷浓度

## 库安装
这里提供两种使用本库的方法：<br>
1.打开Arduino IDE,在状态栏中的Tools--->Manager Libraries 搜索"DFRobot_MHZ9041A"并安装本库.<br>
2.首先下载库文件,将其粘贴到\Arduino\libraries目录中,然后打开examples文件夹并在该文件夹中运行演示.<br>

## 方法

```C++
/**
 * @enum eFaultCode_t
 * @brief 传感器错误码
 */
typedef enum {
  eSensorNormal = 0x00,                   // 00 传感器工作正常
  eTempControlError = 0x01,               // 01 温控异常
  eAmbientTempError = 0x02,               // 02 环境温度异常
  eAmbientAndTempControlError = 0x03,     // 03 环境温度异常&温控异常
  eLaserSignalWeak = 0x04,                // 04 激光信号弱
  eAmbientAndSignalWeakError = 0x06,      // 06 环境温度异常&激光信号弱
  eLaserSignalError = 0x10,               // 16 激光信号异常
  eAmbientAndSignalError = 0x12,          // 18 环境温度异常&激光信号异常
} eFaultCode_t;

/**
 * @enum eModuleMode_t
 * @brief 工作模式
 */
typedef enum {
  ePassivityMode = 0x00,
  eActiveMode = 0x01,
} eWorkMode_t;

/** 
 * @fn set_mode
 * @brief 设置工作模式
 * @param mode 工作模式
 * @note 0x00:主动模式，0x01:被动模式
 * @return null
 */
void setMode(eWorkMode_t mode); 

/** 
 * @fn getSourceData
 * @brief 获取原始数据
 * @return 原始数据字符串，长度不超过43个字节
 */
String getSourceData(void);

/**
 * @fn getCH4Concentration
 * @brief 获取CH4浓度
 * @return甲烷浓度数值，保留两位小数，小数点后第二位恒为0，单位%LEL
*/
float getCH4Concentration(void);

/**
 * @fn getTemperature
 * @brief 获取环境温度
 * @return 摄氏度
*/
float getTemperature(void);

/**
 * @fn getErrorMsg
 * @brief 获取错误码
 * @return 错误码信息
*/
eFaultCode_t getErrorMsg(void);

/**
 * @fn getActiveData
 * @brief 获取主动上报模式下的原始数据，
 * @return 主动模式下的原始数据字符串
*/
String getActiveData(void);

/**
 * @fn reset
 * @brief 复位板载甲烷传感器，reset引脚低电平2秒后完成复位
 * @return null
 */
void reset(void);

/**
 * @fn setDeviceID
 * @brief 修改模块地址,范围0x03~0x7F
 * @return 修改成功返回1，不成功返回0
 */
bool setDeviceID(uint8_t id);

/**
 * @fn setDeviceID
 * @brief 获取模块地址
 * @return 模块地址
 */
uint8_t getDeviceID(void);
```

## 兼容性

MCU                | Work Well    |   Work Wrong    | Untested    | Remarks
------------------ | :----------: | :-------------: | :---------: | :----:
Arduino Uno        |      √       |                 |             |
Arduino MEGA2560   |      √       |                 |             |
Arduino Leonardo   |      √       |                 |             |
FireBeetle-ESP8266 |      √       |                 |             |
FireBeetle-ESP32   |      √       |                 |             |
FireBeetle-M0      |      √       |                 |             |


## 历史
- 2025/04/23 - V1.0.0 版本

## 创作者

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2025. (Welcome to our website)