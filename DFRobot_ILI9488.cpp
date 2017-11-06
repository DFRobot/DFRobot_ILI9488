#include "DFRobot_ILI9488.h"

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04


DFRobot_ILI9488::DFRobot_ILI9488(void) : DFRobot_Display(ILI9488_TFTWIDTH, ILI9488_TFTHEIGHT) {}


void DFRobot_ILI9488::displayON(void)
{
  writeCmd(DISPON);
}


void DFRobot_ILI9488::displayOFF(void)
{
  writeCmd(DISPOFF);
}


void DFRobot_ILI9488::displaySleepIN(void)
{
  writeCmd(SLPIN);
}


void DFRobot_ILI9488::displaySleepOUT(void)
{
  writeCmd(SLPOUT);
}


void DFRobot_ILI9488::fillScreen(uint16_t color)
{
  setCursorAddr(0, 0, 319, 479);
  writeToRam();
  writeRepeatPixel(color, 320, 480);
}


void DFRobot_ILI9488::writeToRam(void)
{
  writeCmd(0x2c);
}


void DFRobot_ILI9488::setCursorAddr(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
  uint8_t addrBuf[4] = {(uint16_t)x0 >> 8, (uint16_t)x0, (uint16_t)x1 >> 8, (uint16_t)x1};
  writeCmd(ILI9488_CASET);
  writeDatBytes(addrBuf, 4);
  addrBuf[0] = (uint16_t)y0 >> 8; addrBuf[1] = (uint16_t)y0; addrBuf[2] = (uint16_t)y1 >> 8; addrBuf[3] = (uint16_t)y1;
  writeCmd(ILI9488_PASET);
  writeDatBytes(addrBuf, 4);
}


int16_t DFRobot_ILI9488::setRotation(eROTATION eRotation)
{
  writeCmd(ILI9488_MADCTL);
  switch (eRotation) {
    case eROTATION_0: {
      writeDat(MADCTL_MX | MADCTL_BGR);
      DFRobot_Display::width  = ILI9488_TFTWIDTH;
      DFRobot_Display::height = ILI9488_TFTHEIGHT;
    } break;
    case eROTATION_90: {
      writeDat(MADCTL_MV | MADCTL_BGR);
      DFRobot_Display::width  = ILI9488_TFTHEIGHT;
      DFRobot_Display::height = ILI9488_TFTWIDTH;
    } break;
    case eROTATION_180: {
      writeDat(MADCTL_MY | MADCTL_BGR);
      DFRobot_Display::width  = ILI9488_TFTWIDTH;
      DFRobot_Display::height = ILI9488_TFTHEIGHT;
    } break;
    case eROTATION_270: {
      writeDat(MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR);
      DFRobot_Display::width  = ILI9488_TFTHEIGHT;
      DFRobot_Display::height = ILI9488_TFTWIDTH;
    } break;
    default: return DISPLAY_ERR_NOTSUPPORT;
  }
  eRotation = eRotation;
  return DISPLAY_ERR_OK;
}


void DFRobot_ILI9488::drawVLine(int16_t x, int16_t y, int16_t height, uint16_t color)
{
  if(limitVLine(x, y, height) < 0) {return;}
  setCursorAddr(x, y, x, y + height - 1);
  writeToRam();
  writeRepeatPixel(color, height, 1);
}


void DFRobot_ILI9488::drawHLine(int16_t x, int16_t y, int16_t width, uint16_t color)
{
  if(limitHLine(x, y, width) < 0) {return;}
  setCursorAddr(x, y, x + width - 1, y);
  writeToRam();
  writeRepeatPixel(color, width, 1);
}


