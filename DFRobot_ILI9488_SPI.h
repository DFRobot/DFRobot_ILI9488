#ifndef _DFRobot_ILI9488_SPI_h
#define _DFRobot_ILI9488_SPI_h

#include "DFRobot_ILI9488.h"

#define ILI9488_SPIBEGIN()        SPI.begin();SPI.beginTransaction(SPISettings(40000000, MSBFIRST, SPI_MODE0))
#define ILI9488_SPIEND()          SPI.endTransaction()


class DFRobot_ILI9488_SPI : public DFRobot_ILI9488
{
  public:
    DFRobot_ILI9488_SPI(uint8_t pin_cs, uint8_t pin_cd, uint8_t pin_rst);  //set pins

    int16_t     begin(void);
    void        drawPixel(int16_t x, int16_t y, uint16_t color);
  	void        drawBuffer_24(int16_t x, int16_t y, uint8_t* pBuf, uint16_t count);

  private:
    uint8_t     pin_cs, pin_cd, pin_rst;
    
    void        writeCmd(uint8_t cmd);
    void        writeDat(uint8_t dat);
    void        writeDatBytes(uint8_t* pDat, uint16_t count);
    void        writeRepeatPixel(uint16_t color, uint16_t count, uint16_t repeatCount);
};


#endif

