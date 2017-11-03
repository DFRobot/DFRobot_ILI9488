#ifndef DFROBOT_ILI9488_H
#define DFROBOT_ILI9488_H

#include "DFRobot_Display_Config.h"

#define ILI9488_TFTWIDTH  320
#define ILI9488_TFTHEIGHT 480

#define ILI9488_TFTWDAT   319
#define ILI9488_TFTHDAT   479

#define ILI9488_NOP     0x00
#define ILI9488_SWRESET 0x01
#define ILI9488_RDDID   0x04
#define ILI9488_RDDST   0x09

#define ILI9488_SLPIN   0x10
#define ILI9488_SLPOUT  0x11
#define ILI9488_PTLON   0x12
#define ILI9488_NORON   0x13

#define ILI9488_RDMODE  0x0A
#define ILI9488_RDMADCTL  0x0B
#define ILI9488_RDPIXFMT  0x0C
#define ILI9488_RDIMGFMT  0x0D
#define ILI9488_RDSELFDIAG  0x0F

#define ILI9488_INVOFF  0x20
#define ILI9488_INVON   0x21
#define ILI9488_GAMMASET 0x26
#define ILI9488_DISPOFF 0x28
#define ILI9488_DISPON  0x29

#define ILI9488_CASET   0x2A
#define ILI9488_PASET   0x2B
#define ILI9488_RAMWR   0x2C
#define ILI9488_RAMRD   0x2E

#define ILI9488_PTLAR   0x30
#define ILI9488_MADCTL  0x36
#define ILI9488_PIXFMT  0x3A

#define ILI9488_FRMCTR1 0xB1
#define ILI9488_FRMCTR2 0xB2
#define ILI9488_FRMCTR3 0xB3
#define ILI9488_INVCTR  0xB4
#define ILI9488_DFUNCTR 0xB6

#define ILI9488_PWCTR1  0xC0
#define ILI9488_PWCTR2  0xC1
#define ILI9488_PWCTR3  0xC2
#define ILI9488_PWCTR4  0xC3
#define ILI9488_PWCTR5  0xC4
#define ILI9488_VMCTR1  0xC5
#define ILI9488_VMCTR2  0xC7

#define ILI9488_RDID1   0xDA
#define ILI9488_RDID2   0xDB
#define ILI9488_RDID3   0xDC
#define ILI9488_RDID4   0xDD

#define ILI9488_GMCTRP1 0xE0
#define ILI9488_GMCTRN1 0xE1

#define ILI9488_DRAWBEGIN       0x01
#define ILI9488_DRAWREPEAT      0x02


class DFRobot_ILI9488 : public DFRobot_Display
{
  public:
    DFRobot_ILI9488(void);
  
    virtual int16_t     begin() = 0;
    virtual void        writeCmd(uint8_t cmd) = 0;
    virtual void        writeDat(uint8_t dat) = 0;
    virtual void        writeDatBytes(uint8_t* pDat, uint16_t count) = 0;
    virtual void        writeRepeatPixel(uint16_t color, uint16_t count, uint16_t repeatCount) = 0;

    int16_t     setRotation(eROTATION eRotation);
    void        writeToRam(void);
    void        invertDisplay(eINVERT invert);
    void        fillScreen(uint16_t color);
    void        drawVLine(int16_t x, int16_t y, int16_t height, uint16_t color);
  	void        drawHLine(int16_t x, int16_t y, int16_t width, uint16_t color);

  protected:
    void        setCursorAddr(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
};

#endif

