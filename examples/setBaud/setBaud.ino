/*!
 * @file  setBaud.ino
 * @brief Set UART baud rate and print before/after values
 * @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V1.0.0
 * @date 2025-05-13
 * @url https://github.com/DFRobot/DFRobot_MHZ9041A
 */

#include "DFRobot_MHZ9041A.h"

// Only for I2C communication
DFRobot_MHZ9041A_I2C ch4(&Wire, 0x34);

void setup()
{
  Serial.begin(115200);
  while(!Serial);
  while (!ch4.begin()) {
    Serial.println("No devices found!");
    delay(1000);
  }
  Serial.println("Device connected!");

  // Get and print current baud rate
  uint32_t oldBaud = ch4.getBaud();
  Serial.print("Current baud rate: ");
  Serial.println(oldBaud);

  // Set new baud rate
  ch4.setBaud(eBaud57600);
  Serial.println("Baud rate set command sent!");

  // Get and print new baud rate
  uint32_t newBaud = ch4.getBaud();
  Serial.print("Updated baud rate: ");
  Serial.println(newBaud);

  Serial.println("Note: The new baud rate takes effect after power cycling the device.");
}

void loop()
{
  delay(2000); // Optional: Reduce serial flooding
}
