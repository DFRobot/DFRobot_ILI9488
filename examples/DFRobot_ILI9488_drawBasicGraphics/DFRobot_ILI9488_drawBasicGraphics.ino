/*
 * file : DFRobot_ILI9488_drawBasicGraphics.ino
 *
 * To accomplish the test, you need a fireBeetle Covers-3.5 TFT LCD module to plug fireBeetle esp8266, esp32 or Bluno2. 
 * Then complile and download the example.
 *
 * Once operates right, the module shows different kinds of figures and printed texts.
 *
 * Copyright   [DFRobot](http://www.dfrobot.com), 2016
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.0
 * date  2017-11-13
 */

 
#include "DFRobot_ILI9488_SPI.h"

#if((defined __ets__) || (defined ESP_PLATFORM))
uint8_t pin_cs = 0, pin_cd = D4, pin_SD_cs = D3;
#else
uint8_t pin_cs = 2, pin_cd = 4, pin_SD_cs = 3;
#endif

DFRobot_ILI9488_SPI tft(pin_cs, pin_cd);


void setup(void)
{
  delay(500);
  Serial.begin(115200);
  _DEBUG_PRINT("\n  ILI9488 DISPLAY TEST !");
  tft.begin();
  //tft.supportChineseFont();
}


#define drawAxis()        tft.fillScreen(0); \
                          tft.drawVLine(0, -240, 480, DISPLAY_WHITE); \
                          tft.drawHLine(-160, 0, 320, DISPLAY_WHITE)

void loop(void)
{
  tft.fillScreen(DISPLAY_RED); delay(500);

  tft.setOrign(160, 240);
  drawAxis();
  tft.setTextColor(DISPLAY_YELLOW);
  tft.setTextSize(4);
  tft.setCursor(0, 0);
#if((defined __ets__) || (defined ESP_PLATFORM))
  tft.printf("fire\nBeetle oh\tye");
  tft.setCursor(0, 240);
  tft.printf("1 + 1 = %d  ", 2);
#else
  tft.print("fire\nBeetle oh\tye");
  tft.setCursor(0, 240);
  tft.println("1 + 1 = 2");
  tft.println("2 + 2 = 4");
#endif
  delay(500);
  drawAxis();
  tft.drawRoundRect(20, 20, 80, 80, 20, DISPLAY_ORANGE);
  tft.drawRoundRect(-20, 20, -80, 80, 20, DISPLAY_ORANGE);
  tft.drawRoundRect(-20, -20, -80, -80, 20, DISPLAY_ORANGE);
  tft.drawRoundRect(20, -20, 80, -80, 20, DISPLAY_ORANGE);
  delay(500);
  tft.fillRoundRect(20, 20, 80, 80, 20, DISPLAY_ORANGE);
  tft.fillRoundRect(-20, 20, -80, 80, 20, DISPLAY_ORANGE);
  tft.fillRoundRect(-20, -20, -80, -80, 20, DISPLAY_ORANGE);
  tft.fillRoundRect(20, -20, 80, -80, 20, DISPLAY_ORANGE);
  delay(500);
  drawAxis();
  tft.drawLine(-40, -40, 40, 40, DISPLAY_RED);
  tft.drawLine(40, -40, -40, 40, DISPLAY_RED);
  tft.drawLine(-200, -20, 200, -20, DISPLAY_RED);
  tft.drawLine(-200, 20, 200, 20, DISPLAY_RED);
  tft.drawLine(20, -400, 20, 400, DISPLAY_RED);
  tft.drawLine(-20, -400, -20, 400, DISPLAY_RED);
  delay(500);
  drawAxis();
  tft.drawRect(20, 20, 80, 80, DISPLAY_BLUE);
  tft.drawRect(-20, 20, -80, 80, DISPLAY_BLUE);
  tft.drawRect(-20, -20, -80, -80, DISPLAY_BLUE);
  tft.drawRect(20, -20, 80, -80, DISPLAY_BLUE);
  delay(500);
  tft.fillRect(20, 20, 80, 80, DISPLAY_BLUE);
  tft.fillRect(-20, 20, -80, 80, DISPLAY_BLUE);
  tft.fillRect(-20, -20, -80, -80, DISPLAY_BLUE);
  tft.fillRect(20, -20, 80, -80, DISPLAY_BLUE);
  delay(500);
  drawAxis();
  tft.drawCircle(60, 60, 40, DISPLAY_CYAN);
  tft.drawCircle(-60, 60, 40, DISPLAY_CYAN);
  tft.drawCircle(-60, -60, 40, DISPLAY_CYAN);
  tft.drawCircle(60, -60, 40, DISPLAY_CYAN);
  delay(500);
  tft.fillCircle(60, 60, 40, DISPLAY_CYAN);
  tft.fillCircle(-60, 60, 40, DISPLAY_CYAN);
  tft.fillCircle(-60, -60, 40, DISPLAY_CYAN);
  tft.fillCircle(60, -60, 40, DISPLAY_CYAN);
  delay(500);
  drawAxis();
  tft.drawTriangle(0, -120, -80, 120, 80, 120, DISPLAY_GREEN);
  delay(500);
  tft.fillTriangle(0, -120, -80, 120, 80, 120, DISPLAY_GREEN);
  delay(500);
}

