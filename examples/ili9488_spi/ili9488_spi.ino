#include "DFRobot_ILI9488_SPI.h"

#define TFT_CS         D4
#define TFT_DC         D5
#define TFT_LED        D6
#define TFT_RST        D7

DFRobot_ILI9488_SPI tft = DFRobot_ILI9488_SPI(TFT_CS, TFT_DC, TFT_RST);


void testFillScreen(void)
{
  tft.fillScreen(ILI9488_RED);
  delay(500);
  tft.fillScreen(ILI9488_GREEN);
  delay(500);
  tft.fillScreen(ILI9488_BLUE);
  delay(500);
  tft.fillScreen(ILI9488_WHITE);
  delay(500);
  tft.fillScreen(ILI9488_BLACK);
}


void testText(void)
{
  tft.fillScreen(ILI9488_BLACK);
  delay(500);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9488_WHITE);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9488_YELLOW);
  tft.println(1234.56);
  tft.setTextSize(2);
  tft.println("my foonting turlingdrom");
  tft.println("And hooptiously drangle me");
  tft.setTextSize(3);
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
}


uint32_t testLines(uint16_t color)
{
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(ILI9488_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6)  {
    tft.drawLine(x1, y1, x2, y2, color);
  }
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6)  {
    tft.drawLine(x1, y1, x2, y2, color);
  }
  t    += micros() - start;

  tft.fillScreen(ILI9488_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6)  {
    tft.drawLine(x1, y1, x2, y2, color);
  }
  x2    = 0;
  for(y2=0; y2<h; y2+=6)  {
    tft.drawLine(x1, y1, x2, y2, color);
  }
  return micros() - start;
}


unsigned long testFastLines(uint16_t color1, uint16_t color2)
{
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9488_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}


unsigned long testRects(uint16_t color)
{
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(ILI9488_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}


unsigned long testFilledRects(uint16_t color1, uint16_t color2)
{
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9488_BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}


unsigned long testFilledCircles(uint8_t radius, uint16_t color)
{
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(ILI9488_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
  return micros() - start;
}


unsigned long testCircles(uint8_t radius, uint16_t color)
{
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
  return 1;
}


unsigned long testTriangles()
{
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9488_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(0, 0, i));
  }

  return micros() - start;
}


unsigned long testFilledTriangles()
{
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9488_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i, i, 0));
  }

  return t;
}


unsigned long testRoundRects()
{
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9488_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}


unsigned long testFilledRoundRects()
{
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9488_BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
  }

  return micros() - start;
}


void testRotation(void)
{
  for(uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(500);
  }
  tft.setRotation(0);
}


void setup(void)
{

  uint16_t i = 0, j = 0;
  uint8_t colorBuf[3] = {255, 255, 0};

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println("ILI9488 Test!");

  tft.begin();

}


void loop(void)
{

  Serial.println("testFillScreen");
  testFillScreen();
  delay(500);
  

  Serial.println("test image");
  tft.drawImage((uint8_t *) (table_bmp_pic1 + 54), 0, 0, 320, 480);
  delay(500);
  /*
  Serial.println("testText");
  testText();
  delay(500);
  
  Serial.println("testFastLines");
  testFastLines(ILI9488_RED, ILI9488_BLUE);
  delay(500);
  
  Serial.println("testRects");
  testRects(ILI9488_GREEN);
  delay(500);
  
  Serial.println("testFilledRects");
  testFilledRects(ILI9488_YELLOW, ILI9488_MAGENTA);
  delay(500);
  
  Serial.println("testTriangles");
  testTriangles();
  delay(500);

  Serial.println("testFilledTriangles");
  testFilledTriangles();
  delay(500);

  Serial.println("testRoundRects");
  testRoundRects();
  delay(500);

  Serial.println("testFilledRoundRects");
  testFilledRoundRects();
  delay(500);

  Serial.println("test rotation");
  testRotation();
  delay(500);

  Serial.println("testLines");
  testLines(ILI9488_CYAN);
  delay(500);

  Serial.println("testFilledCircles");
  testFilledCircles(10, ILI9488_MAGENTA);
  delay(500);
  
  Serial.println("testCircles");
  testCircles(10, ILI9488_CYAN);
  delay(500);
*/
}

