#include "DFRobot_ILI9488_SPI.h"


DFRobot_ILI9488_SPI::DFRobot_ILI9488_SPI(uint8_t pin_cs_, uint8_t pin_cd_, uint8_t pin_rst_)
{
  pin_cs    = pin_cs_;
  pin_cd    = pin_cd_;
  pin_rst   = pin_rst_;
  pinMode(pin_cd, OUTPUT);
  pinMode(pin_cs, OUTPUT);
  pinMode(pin_rst, OUTPUT);
  digitalWrite(pin_cd, 1);
  digitalWrite(pin_cs, 1);
  digitalWrite(pin_rst, 1);
}


int16_t DFRobot_ILI9488_SPI::begin(void)
{
  digitalWrite(pin_rst, 0);
  delay(20);
  digitalWrite(pin_rst, 1);
  delay(150);

  writeCmd(0xE0);
  writeDat(0x00);
  writeDat(0x03);
  writeDat(0x09);
  writeDat(0x08);
  writeDat(0x16);
  writeDat(0x0A);
  writeDat(0x3F);
  writeDat(0x78);
  writeDat(0x4C);
  writeDat(0x09);
  writeDat(0x0A);
  writeDat(0x08);
  writeDat(0x16);
  writeDat(0x1A);
  writeDat(0x0F);

  writeCmd(0XE1);
  writeDat(0x00);
  writeDat(0x16);
  writeDat(0x19);
  writeDat(0x03);
  writeDat(0x0F);
  writeDat(0x05);
  writeDat(0x32);
  writeDat(0x45);
  writeDat(0x46);
  writeDat(0x04);
  writeDat(0x0E);
  writeDat(0x0D);
  writeDat(0x35);
  writeDat(0x37);
  writeDat(0x0F);

  writeCmd(0XC0);      //Power Control 1
  writeDat(0x17);    //Vreg1out
  writeDat(0x15);    //Verg2out

  writeCmd(0xC1);      //Power Control 2
  writeDat(0x41);    //VGH,VGL

  writeCmd(0xC5);      //Power Control 3
  writeDat(0x00);
  writeDat(0x12);    //Vcom
  writeDat(0x80);

  writeCmd(0x36);      //Memory Access
  writeDat(0x48);

  writeCmd(0x3A);      // Interface Pixel Format
  writeDat(0x66); 	  //18 bit

  writeCmd(0XB0);      // Interface Mode Control
  writeDat(0x80);     			 //SDO NOT USE

  writeCmd(0xB1);      //Frame rate
  writeDat(0xA0);    //60Hz

  writeCmd(0xB4);      //Display Inversion Control
  writeDat(0x02);    //2-dot

  writeCmd(0XB6);      //Display Function Control  RGB/MCU Interface Control

  writeDat(0x02);    //MCU
  writeDat(0x02);    //Source,Gate scan dieection

  writeCmd(0XE9);      // Set Image Functio
  writeDat(0x00);    // Disable 24 bit data

  writeCmd(0xF7);      // Adjust Control
  writeDat(0xA9);
  writeDat(0x51);
  writeDat(0x2C);
  writeDat(0x82);    // D7 stream, loose

  writeCmd(ILI9488_SLPOUT);    //Exit Sleep
  delay(120);
  writeCmd(ILI9488_DISPON);    //Display on
  
  return BEGIN_WAR_NOTEST;
}


void DFRobot_ILI9488_SPI::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  uint8_t colorBuf[3] = {((color & 0xf800) >> 11) * 255 / 31, ((color & 0x07e0) >> 5) * 255 / 63, (color & 0x001f) * 255 / 31};
  if(limitPixel(x, y) < 0) {return;}
  setCursorAddr(x, y, x, y);
  writeToRam();
  writeDatBytes(colorBuf, 3);
}


#define ESP_WRITEDATBYTES()       uint8_t* pColorBuf = (uint8_t*) malloc(count * 3); \
                                  for(i = 0; i < count * 3; i ++) { \
                                    pColorBuf[i] = colorBuf[0]; \
                                    pColorBuf[++ i] = colorBuf[1]; \
                                    pColorBuf[++ i] = colorBuf[2]; \
                                  } \
                                  for(i = 0; i < repeatCount; i ++) { \
                                    writeDatBytes(pColorBuf, count * 3); \
                                  } \
                                  free(pColorBuf);

void DFRobot_ILI9488_SPI::writeRepeatPixel(uint16_t color, uint16_t count, uint16_t repeatCount)
{
  uint8_t       colorBuf[3] = {((color & 0xf800) >> 11) * 255 / 31, ((color & 0x07e0) >> 5) * 255 / 63, (color & 0x001f) * 255 / 31};
  uint16_t      i = 0, j = 0;
#ifdef __AVR__
  _DEBUG_PRINT("\n  writeRepeat count:");
  _DEBUG_PRINTVAR(repeatCount * count, DEC);
  for(i = 0; i < repeatCount; i ++) {
    for(j = 0; j < count; j ++) {
      writeDatBytes(colorBuf, 3);
    }
  }
#elif ((defined __ets__) || (defined ESP_PLATFORM))
  ESP_WRITEDATBYTES();
#else
  ESP_WRITEDATBYTES();
  #warning untest platform
#endif
}


void DFRobot_ILI9488_SPI::drawBuffer_24(int16_t x, int16_t y, uint8_t* pBuf, uint16_t count)
{
  int16_t       bufPixelWidth = 0;
  bufPixelWidth = count / 3;
  if(bufPixelWidth + x > width) {
    bufPixelWidth = width - x;
  }
  _DEBUG_PRINT("\n  drawBuffer width:");
  _DEBUG_PRINTVAR(bufPixelWidth, DEC);
  _DEBUG_PRINT(" ");
  _DEBUG_PRINTVAR(x, DEC);
  _DEBUG_PRINT(" ");
  _DEBUG_PRINTVAR(y, DEC);
  _DEBUG_PRINT(" ");
  _DEBUG_PRINTVAR(count, DEC);
  setCursorAddr(x, y, x + bufPixelWidth, y);
  writeToRam();
  writeDatBytes(pBuf, bufPixelWidth * 3);
}


void DFRobot_ILI9488_SPI::writeCmd(uint8_t cmd)
{
  ILI9488_SPIBEGIN();
  digitalWrite(pin_cd, 0);
  digitalWrite(pin_cs, 0);
  SPI.transfer(cmd);
  digitalWrite(pin_cs, 1);
  ILI9488_SPIEND();
}


void DFRobot_ILI9488_SPI::writeDat(uint8_t dat)
{
  ILI9488_SPIBEGIN();
  digitalWrite(pin_cd, 1);
  digitalWrite(pin_cs, 0);
  SPI.transfer(dat);
  digitalWrite(pin_cs, 1);
  ILI9488_SPIEND();
}


void DFRobot_ILI9488_SPI::writeDatBytes(uint8_t* pDat, uint16_t count)
{
  ILI9488_SPIBEGIN();
  digitalWrite(pin_cd, 1);
  digitalWrite(pin_cs, 0);
#ifdef __AVR__
  while(count --) {
    SPI.transfer(*pDat);
    pDat ++;
  }
#else
  SPI.transferBytes(pDat, NULL, count);
#endif
  digitalWrite(pin_cs, 1);
  ILI9488_SPIEND();
}


