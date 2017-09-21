#include "DFRobot_ILI9488_SPI.h"


DFRobot_ILI9488_SPI::DFRobot_ILI9488_SPI(uint8_t pin_cs, uint8_t pin_cd, uint8_t pin_rst) : 
                      Adafruit_GFX_DF(ILI9488_TFTWIDTH, ILI9488_TFTHEIGHT)
{
  this->pin_cs    = pin_cs;
  this->pin_cd    = pin_cd;
  this->pin_rst   = pin_rst;
  pinMode(this->pin_cd, OUTPUT);
  pinMode(this->pin_cs, OUTPUT);
  pinMode(this->pin_rst, OUTPUT);
  digitalWrite(this->pin_cd, 1);
  digitalWrite(this->pin_cs, 1);
  digitalWrite(this->pin_rst, 1);
}


void DFRobot_ILI9488_SPI::begin(void)
{
  ILI9488_SPIBEGIN();
  digitalWrite(this->pin_rst, 0);
  delay(20);
  digitalWrite(this->pin_rst, 1);
  delay(150);

  this->writeCmd(0xE0);
	this->writeDat(0x00);
	this->writeDat(0x03);
	this->writeDat(0x09);
	this->writeDat(0x08);
	this->writeDat(0x16);
	this->writeDat(0x0A);
	this->writeDat(0x3F);
	this->writeDat(0x78);
	this->writeDat(0x4C);
	this->writeDat(0x09);
	this->writeDat(0x0A);
	this->writeDat(0x08);
	this->writeDat(0x16);
	this->writeDat(0x1A);
	this->writeDat(0x0F);

	this->writeCmd(0XE1);
	this->writeDat(0x00);
	this->writeDat(0x16);
	this->writeDat(0x19);
	this->writeDat(0x03);
	this->writeDat(0x0F);
	this->writeDat(0x05);
	this->writeDat(0x32);
	this->writeDat(0x45);
	this->writeDat(0x46);
	this->writeDat(0x04);
	this->writeDat(0x0E);
	this->writeDat(0x0D);
	this->writeDat(0x35);
	this->writeDat(0x37);
	this->writeDat(0x0F);

	this->writeCmd(0XC0);      //Power Control 1
	this->writeDat(0x17);    //Vreg1out
	this->writeDat(0x15);    //Verg2out

	this->writeCmd(0xC1);      //Power Control 2
	this->writeDat(0x41);    //VGH,VGL

	this->writeCmd(0xC5);      //Power Control 3
	this->writeDat(0x00);
	this->writeDat(0x12);    //Vcom
	this->writeDat(0x80);

	this->writeCmd(0x36);      //Memory Access
	this->writeDat(0x48);

	this->writeCmd(0x3A);      // Interface Pixel Format
	this->writeDat(0x66); 	  //18 bit

	this->writeCmd(0XB0);      // Interface Mode Control
	this->writeDat(0x80);     			 //SDO NOT USE

	this->writeCmd(0xB1);      //Frame rate
	this->writeDat(0xA0);    //60Hz

	this->writeCmd(0xB4);      //Display Inversion Control
	this->writeDat(0x02);    //2-dot

	this->writeCmd(0XB6);      //Display Function Control  RGB/MCU Interface Control

	this->writeDat(0x02);    //MCU
	this->writeDat(0x02);    //Source,Gate scan dieection

	this->writeCmd(0XE9);      // Set Image Functio
	this->writeDat(0x00);    // Disable 24 bit data

	this->writeCmd(0xF7);      // Adjust Control
	this->writeDat(0xA9);
	this->writeDat(0x51);
	this->writeDat(0x2C);
	this->writeDat(0x82);    // D7 stream, loose

	this->writeCmd(ILI9488_SLPOUT);    //Exit Sleep
  delay(120);
  this->writeCmd(ILI9488_DISPON);    //Display on
  
	ILI9488_SPIEND();
}


void DFRobot_ILI9488_SPI::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if((x >= ILI9488_TFTWIDTH) || (y >= ILI9488_TFTHEIGHT) || (x < 0) || (y < 0)) {
    return;
  }
  
  uint8_t colorBuf[3] = {((color & 0xf800) >> 11) * 255 / 31, ((color & 0x07e0) >> 5) * 255 / 63, (color & 0x001f) * 255 / 31};
  this->setCursorAddr(x, y, x, y);
  this->writeToRam();
  ILI9488_SPIBEGIN();
  digitalWrite(this->pin_cd, 1);
  digitalWrite(this->pin_cs, 0);
  SPI.transferBytes(colorBuf, NULL, 3);
  digitalWrite(this->pin_cs, 1);
  ILI9488_SPIEND();
}

void DFRobot_ILI9488_SPI::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }
  for (; x0<=x1; x0++) {
    if (steep) {
      this->drawPixel(y0, x0, color);
    } else {
      this->drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


void DFRobot_ILI9488_SPI::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  uint8_t colorBuf[3] = {((color & 0xf800) >> 11) * 255 / 31, ((color & 0x07e0) >> 5) * 255 / 63, (color & 0x001f) * 255 / 31};
  if((x >= _width) || (y >= _height)) return;
  if((y+h-1) >= _height)
    h = _height-y;

  this->setCursorAddr(x, y, x, y + h - 1);
  this->writeToRam();
  ILI9488_SPIBEGIN();
  digitalWrite(this->pin_cd, HIGH);
  digitalWrite(this->pin_cs, LOW);
  while (h--) {
    SPI.transferBytes(colorBuf, NULL, 3);
  }
  digitalWrite(this->pin_cs, HIGH);
  ILI9488_SPIEND();
}


void DFRobot_ILI9488_SPI::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
  uint8_t colorBuf[3] = {((color & 0xf800) >> 11) * 255 / 31, ((color & 0x07e0) >> 5) * 255 / 63, (color & 0x001f) * 255 / 31};
  if((x >= _width) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;

  this->setCursorAddr(x, y, x+w-1, y);
  this->writeToRam();
  ILI9488_SPIBEGIN();
  digitalWrite(this->pin_cd, HIGH);
  digitalWrite(this->pin_cs, LOW);
  while (w--) {
    SPI.transferBytes(colorBuf, NULL, 3);
  }
  digitalWrite(this->pin_cs, HIGH);
  ILI9488_SPIEND();
}


void DFRobot_ILI9488_SPI::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  int16_t       i = x;
  for (i = x; i < x + w; i ++) {
    this->drawFastVLine(i, y, h, color);
  }
}


void DFRobot_ILI9488_SPI::fillScreen(uint16_t color)
{
  uint16_t    i = 0;
  uint8_t*    pColorBuf = (uint8_t*) malloc(320 * 3);
  uint8_t     colorBuf[3] = {((color & 0xf800) >> 11) * 255 / 31, ((color & 0x07e0) >> 5) * 255 / 63, (color & 0x001f) * 255 / 31};

  for(i = 0; i < 320 * 3; i ++) {
    pColorBuf[i] = colorBuf[0];
    pColorBuf[++ i] = colorBuf[1];
    pColorBuf[++ i] = colorBuf[2];
  }
  ILI9488_SPIBEGIN();
  this->setCursorAddr(0, 0, ILI9488_TFTWDAT, ILI9488_TFTHDAT);
  this->writeToRam();
  digitalWrite(this->pin_cd, 1);
  digitalWrite(this->pin_cs, 0);
  for(i = 0; i < 480; i ++) {
    SPI.transferBytes(pColorBuf, NULL, 320 * 3);
  }
  free(pColorBuf);
  digitalWrite(this->pin_cs, 1);
  ILI9488_SPIEND();
}


void DFRobot_ILI9488_SPI::invertDisplay(boolean i)
{
  this->writeCmd(i ? ILI9488_INVON : ILI9488_INVOFF);
}


#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

void DFRobot_ILI9488_SPI::setRotation(uint8_t r)
{
  ILI9488_SPIBEGIN();
  this->writeCmd(ILI9488_MADCTL);
  rotation = r % 4; // can't be higher than 3
  switch (rotation) {
   case 0:
     this->writeDat(MADCTL_MX | MADCTL_BGR);
     _width  = ILI9488_TFTWIDTH;
     _height = ILI9488_TFTHEIGHT;
     break;
   case 1:
     this->writeDat(MADCTL_MV | MADCTL_BGR);
     _width  = ILI9488_TFTHEIGHT;
     _height = ILI9488_TFTWIDTH;
     break;
  case 2:
    this->writeDat(MADCTL_MY | MADCTL_BGR);
     _width  = ILI9488_TFTWIDTH;
     _height = ILI9488_TFTHEIGHT;
    break;
   case 3:
     this->writeDat(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
     _width  = ILI9488_TFTHEIGHT;
     _height = ILI9488_TFTWIDTH;
     break;
  }
  ILI9488_SPIEND();
}


void DFRobot_ILI9488_SPI::drawImage(uint8_t* img, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  if((x >= _width) || (y >= _height)) return;
  if((x + w - 1) >= _width)  w = _width  - x;
  if((y + h - 1) >= _height) h = _height - y;

  uint16_t        i = 0;

  ILI9488_SPIBEGIN();
  this->setCursorAddr(x, y, x+w-1, y+h-1);
  this->writeToRam();
  digitalWrite(this->pin_cd, HIGH);
  digitalWrite(this->pin_cs, LOW);
  for(i = 0; i < h; i ++) {
    SPI.transferBytes(img, NULL, w * 3);
    img += w * 3;
  }
  digitalWrite(this->pin_cs, HIGH);
  ILI9488_SPIEND();
}


uint16_t DFRobot_ILI9488_SPI::color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


void DFRobot_ILI9488_SPI::setCursorAddr(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
  uint8_t addrBuf[4] = {x0 >> 8, x0, x1 >> 8, x1};
  this->writeCmd(ILI9488_CASET);
  digitalWrite(this->pin_cd, 1);
  digitalWrite(this->pin_cs, 0);
  SPI.transferBytes(addrBuf, NULL, 4);
  digitalWrite(this->pin_cs, 1);
  addrBuf[0] = y0 >> 8; addrBuf[1] = y0; addrBuf[2] = y1 >> 8; addrBuf[3] = y1;
  this->writeCmd(ILI9488_PASET);
  digitalWrite(this->pin_cd, 1);
  digitalWrite(this->pin_cs, 0);
  SPI.transferBytes(addrBuf, NULL, 4);
  digitalWrite(this->pin_cs, 1);
}


void DFRobot_ILI9488_SPI::writeToRam(void)
{
  this->writeCmd(ILI9488_RAMWR);
}


void DFRobot_ILI9488_SPI::writeCmd(uint8_t cmd)
{
  digitalWrite(this->pin_cd, 0);
  digitalWrite(this->pin_cs, 0);
  SPI.transfer(cmd);
  digitalWrite(this->pin_cs, 1);
}


void DFRobot_ILI9488_SPI::writeDat(uint8_t dat)
{
  digitalWrite(this->pin_cd, 1);
  digitalWrite(this->pin_cs, 0);
  SPI.transfer(dat);
  digitalWrite(this->pin_cs, 1);
}


