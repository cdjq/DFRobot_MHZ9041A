# DFRobot_MHZ9041A
- [English Version](./README.md)

MH-Z9041A 激光甲烷气体传感器是一个家用型甲烷传感器，基于可调谐激光气体吸收技术（TDLAS）对甲烷气体进行检测，内部采用对射光路结构，具有优异的气体选择性、无氧气依赖性、寿命长等特点；内置了控温算法、温度补偿算法，实现对甲烷气体的精确测量；具有串口输出接口，方便使用。该传感器是将成熟的激光气体吸收检测技术与稳定光路设计和电路设计紧密结合而制作出的高性能传感器。
![正反面svg效果图](../../resources/images/xxx.jpg)


## 产品链接(https://www.dfrobot.com.cn)

    SKU：SEN0654

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)

## 概述

提供一个python库给模块，此库具有以下功能：
  获取 gnss 全部数据
  获取 gnss 解析后的数据

## 库安装
1. 下载库至树莓派，要使用这个库，首先要将库下载到Raspberry Pi，命令下载方法如下:

```
sudo git clone https://github.com/DFRobot/DFRobot_MHZ9041A
```

1. 打开并运行例程，要执行一个例程demo_x.py，请在命令行中输入python demo_x.py。例如，要执行 face_matching.py例程，你需要输入:

```
python  get_active_data.py
或 
python2 get_concentration.py
或 
python3 set_device_ID.py
```

## 方法

```python

  def set_baud(self, baud):
    '''!
      @brief 设置模块波特率
      @param 枚举参数 eBaud_t
    '''
  
  def get_baud(self):
    '''!
      @brief 获取模块波特率
      @return 波特率 [9600, 19200, 38400, 57600, 115200]
    '''

  def set_mode(self, mode):
    '''!
      @brief 设置模块的工作模式
      @param mode 要设置的模式值
    '''

  def get_source_data(self):
    '''!
      @brief 获取原始传感器数据
      @return 字符串形式的原始数据，若数据长度异常返回 "data error"
    '''

  def get_active_data(self):
    '''!
      @brief 获取激活状态下的实时数据
      @return 字符串形式的实时数据，若无数据返回空字符串
    '''

  def get_ch4_concentration(self):
    '''!
      @brief 获取甲烷（CH4）浓度值
      @return 浮点型浓度值（单位：%VOL），读取失败返回0.0
    '''

  def get_temperature(self):
    '''!
      @brief 获取传感器温度值
      @return 浮点型温度值（单位：℃），读取失败返回0.0
    '''

  def get_error_code(self):
    '''!
      @brief 获取设备错误状态码
      @return 错误代码（枚举类型），若无数据返回正常状态码
    '''
  
  def reset(self):
    '''!
      @brief 执行设备软复位操作
    '''
      
  def set_device_id(self, dev_id):
    '''!
      @brief 设置设备I2C地址
      @param dev_id 设备地址（范围：0x03~0x7F）
      @return 设置成功返回True
      @throws ValueError 地址超出范围时抛出异常
    '''

  def get_device_id(self):
    '''!
      @brief 获取当前设备I2C地址
      @return 设备地址值，读取失败返回0
    '''
```

## 兼容性

* RaspberryPi Version

| Board        | 正常运行  | 运行失败   | 未测试    | 备注
| ------------ | :-------: | :--------: | :------: | :-----: |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python版本

| Python  | 正常运行  | 运行失败   | 未测试    | 备注
| ------- | :-------: | :--------: | :------: | :-----: |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## 历史

- 2025/04/23 - V1.0.0 版本

## 创作者

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2025. (Welcome to our website)