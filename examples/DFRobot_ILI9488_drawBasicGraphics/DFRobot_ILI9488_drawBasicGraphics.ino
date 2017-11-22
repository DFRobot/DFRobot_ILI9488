#include "DFRobot_ILI9488_SPI.h"

//set control pins
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
  Serial.print("\n  ILI9488 DISPLAY TEST !");
  tft.begin();  //begin
  //tft.supportChineseFont();
}


//draw axis
#define drawAxis()        tft.fillScreen(0); \
                          tft.drawVLine(0, -240, 480, DISPLAY_WHITE); \
                          tft.drawHLine(-160, 0, 320, DISPLAY_WHITE)

void loop(void)
{
  tft.fillScreen(DISPLAY_RED); delay(500);
  
  //set orign
  tft.setOrign(160, 240);
  drawAxis();
  //config text
  tft.setTextColor(DISPLAY_YELLOW);
  tft.setTextSize(4);
  //set text cursor
  tft.setCursor(0, 0);
  //print
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
  //draw round rectangle
  tft.drawRoundRect(20, 20, 80, 80, 20, DISPLAY_ORANGE);
  tft.drawRoundRect(-20, 20, -80, 80, 20, DISPLAY_ORANGE);
  tft.drawRoundRect(-20, -20, -80, -80, 20, DISPLAY_ORANGE);
  tft.drawRoundRect(20, -20, 80, -80, 20, DISPLAY_ORANGE);
  delay(500);
  //fill round rectangle
  tft.fillRoundRect(20, 20, 80, 80, 20, DISPLAY_ORANGE);
  tft.fillRoundRect(-20, 20, -80, 80, 20, DISPLAY_ORANGE);
  tft.fillRoundRect(-20, -20, -80, -80, 20, DISPLAY_ORANGE);
  tft.fillRoundRect(20, -20, 80, -80, 20, DISPLAY_ORANGE);
  delay(500);
  drawAxis();
  //draw lines
  tft.drawLine(-40, -40, 40, 40, DISPLAY_RED);
  tft.drawLine(40, -40, -40, 40, DISPLAY_RED);
  tft.drawLine(-200, -20, 200, -20, DISPLAY_RED);
  tft.drawLine(-200, 20, 200, 20, DISPLAY_RED);
  tft.drawLine(20, -400, 20, 400, DISPLAY_RED);
  tft.drawLine(-20, -400, -20, 400, DISPLAY_RED);
  delay(500);
  drawAxis();
  //draw rectangle
  tft.drawRect(20, 20, 80, 80, DISPLAY_BLUE);
  tft.drawRect(-20, 20, -80, 80, DISPLAY_BLUE);
  tft.drawRect(-20, -20, -80, -80, DISPLAY_BLUE);
  tft.drawRect(20, -20, 80, -80, DISPLAY_BLUE);
  delay(500);
  //fill rectangle
  tft.fillRect(20, 20, 80, 80, DISPLAY_BLUE);
  tft.fillRect(-20, 20, -80, 80, DISPLAY_BLUE);
  tft.fillRect(-20, -20, -80, -80, DISPLAY_BLUE);
  tft.fillRect(20, -20, 80, -80, DISPLAY_BLUE);
  delay(500);
  drawAxis();
  //draw circle
  tft.drawCircle(60, 60, 40, DISPLAY_CYAN);
  tft.drawCircle(-60, 60, 40, DISPLAY_CYAN);
  tft.drawCircle(-60, -60, 40, DISPLAY_CYAN);
  tft.drawCircle(60, -60, 40, DISPLAY_CYAN);
  delay(500);
  //fill circle
  tft.fillCircle(60, 60, 40, DISPLAY_CYAN);
  tft.fillCircle(-60, 60, 40, DISPLAY_CYAN);
  tft.fillCircle(-60, -60, 40, DISPLAY_CYAN);
  tft.fillCircle(60, -60, 40, DISPLAY_CYAN);
  delay(500);
  drawAxis();
  //draw triangle
  tft.drawTriangle(0, -120, -80, 120, 80, 120, DISPLAY_GREEN);
  delay(500);
  //fill triangle
  tft.fillTriangle(0, -120, -80, 120, 80, 120, DISPLAY_GREEN);
  delay(500);
}

