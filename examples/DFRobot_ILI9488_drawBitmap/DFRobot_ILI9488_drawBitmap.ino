/*
 * file : DFRobot_ILI9488_drawBasicGraphics.ino
 *
 * To accomplish the test, you need a fireBeetle Covers-3.5 TFT LCD module to plug fireBeetle esp8266, esp32 or Bluno2. 
 * Then complile and download the example.
 *
 * Once operates right, ways in the loop can display bmp iamges in the SD card(bmp format:24 bit bitmap )
 *
 * Copyright   [DFRobot](http://www.dfrobot.com), 2016
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.0
 * date  2017-11-13
 */


#include "DFRobot_ILI9488_SPI.h"

#if((defined __ets__) || (defined ESP_PLATFORM))
#include "SD_SPI.h"
uint8_t pin_cs = 0, pin_cd = D4, pin_SD_cs = D3;
#else
#include "SD.h"
uint8_t pin_cs = 2, pin_cd = 4, pin_SD_cs = 3;
#endif

DFRobot_ILI9488_SPI tft(pin_cs, pin_cd);


void setup(void)
{
  delay(500);
  Serial.begin(115200);
  tft.begin();
  //tft.supportChineseFont();

  while(!SD.begin(pin_SD_cs)) {
    Serial.print("\n  SD begin faild");
    delay(2000);
  }
  Serial.print("\n  SD begin successful");
}


void loop(void)
{
  tft.fillScreen(DISPLAY_RED);
  delay(500);
  tft.setOrign(0,0);
  tft.fillScreen(0);
  File f = SD.open("Image.bmp", FILE_READ);
  tft.drawBmp(&f,80, 160);
  f.close();
  delay(1000);
}
