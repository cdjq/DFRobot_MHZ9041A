 /*!
  * @file  setDeviceID.ino
  * @brief set device ID
  * @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license The MIT License (MIT)
  * @author ZhixinLiu(zhixin.liu@dfrobot.com)
  * @version V1.0.0
  * @date 2025-04-24
  * @url https://github.com/DFRobot/DFRobot_MHZ9041A
  */

#include "DFRobot_MHZ9041A.h"

#define I2C_COMMUNICATION  //use I2C for communication, but use the serial port for communication if the line of codes were masked

#ifdef  I2C_COMMUNICATION
  DFRobot_MHZ9041A_I2C ch4(&Wire ,0x34);
#else
/* -----------------------------------------------------------------------------------------------------
  * |  Sensor  | Connect line | Leonardo/Mega2560/M0 |    UNO    | ESP8266 | ESP32 |  microbit  |   m0  |
  * |   VCC    |=============>|        VCC           |    VCC    |   VCC   |  VCC  |     X      |  vcc  |
  * |   GND    |=============>|        GND           |    GND    |   GND   |  GND  |     X      |  gnd  |
  * |   RX     |=============>|     Serial1 TX1      |     5     |   5/D6  |  D2   |     X      |  tx1  |
  * |   TX     |=============>|     Serial1 RX1      |     4     |   4/D7  |  D3   |     X      |  rx1  |
  * ----------------------------------------------------------------------------------------------------*/
/* Baud rate cannot be changed */
  #if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
    SoftwareSerial mySerial(4, 5);
    DFRobot_MHZ9041A_UART ch4(&mySerial, 115200);
  #elif defined(ESP32)
    DFRobot_MHZ9041A_UART ch4(&Serial1, 115200 ,/*rx*/D2 ,/*tx*/D3);
  #else
    DFRobot_MHZ9041A_UART ch4(&Serial1, 115200);
  #endif
#endif
  
  void setup()
  {
    Serial.begin(115200);
    while(!ch4.begin()){
      Serial.println("NO Deivces !");
      delay(1000);
    } Serial.println("Device connected !");
    ch4.setMode(ePassivityMode);               // set Passivity mode
    bool result = ch4.setDeviceID(0x05);
    if(result){
      Serial.println("Set device ID success!");
    }else{
      Serial.println("Set device ID failed!");
    }
  }
  
  void loop()
  {
    uint8_t addr = ch4.getDeviceID();
    Serial.print("Device ID: ");
    Serial.println(addr, HEX); // print device ID
    Serial.println("Set device ID success, It takes effect after power failure!");
    delay(1000);
  }