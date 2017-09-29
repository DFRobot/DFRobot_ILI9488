# ILI9488_SPI
============

## Credits

## Usage

Check out the examples folder for a few comprehensive demonstrations how to use the library. 

## Features

* Draw pixels at given coordinates
* Draw lines from given coordinates to given coordinates
* Draw or fill a rectangle with given dimensions
* Draw Text at given coordinates
* Draw picture at given coordinates

## API

### class

``` C++
#include "DFRobot_ILI9488_SPI.h"

/*
 * @brief def objective
 *
 * @param pin_cs ili9488 cs pin
 * @param pin_cd ili9488 cd pin
 * @param pin_rst ili9488 rst pin
 */
DFRobot_ILI9488_SPI  tft(pin_cs, pin_cd, pin_rst);

```

### display control

``` C++

/*
 * @brief ili9488 begin
 */
void begin(void);

/*
 * @brief draw line at given location (x0, y0) to (x1, y1) in color
 *
 * @param x0 from 0 to 320
 * @param y0 from 0 to 480
 * @param x1 from 0 to 320
 * @param y1 from 0 to 480
 * @param color your 16bit color data
 *     ILI9488_WHITE, ILI9488_BLACK, ILI9488_CYAN, ILI9488_RED, ILI9488_GREEN, ILI9488_BLUE
 *     ILI9488_NAVY, ILI9488_DARKGREEN, ILI9488_DARKCYAN, ILI9488_MAROON, ILI9488_PURPLE
 *     ILI9488_OLIVE, ILI9488_LIGHTGREY, ILI9488_DARKGREY, ILI9488_MAGENTA, ILI9488_YELLOW
 *     ILI9488_ORANGE, ILI9488_GREENYELLOW, ILI9488_PINK
 */
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

/*
 * @brief draw a pixel at a given location in color
 *
 * @param x from 0 to 320
 * @param y from 0 to 480
 * @param color your 16bit color data
 */
void drawPixel(int16_t x, int16_t y, uint16_t color);

/*
 * @brief draw a vertical line at a given location in color
 *
 * @param x from 0 to 320
 * @param y from 0 to 480
 * @param h line lenth from 0 to 480
 * @param color your 16bit color data
 */
void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

/*
 * @brief draw a horizontal line at a given location in color
 *
 * @param x from 0 to 320
 * @param y from 0 to 480
 * @param w line lenth from 0 to 320
 * @param color your 16bit color data
 */
void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

/*
 * @brief draw a vertical line at a given location in color
 *
 * @param x from 0 to 320
 * @param y from 0 to 480
 * @param h line lenth from 0 to 480
 * @param color your 16bit color data
 */
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

/*
 * @brief fill screen in given color
 *
 * @param color your 16bit color data
 */
void fillScreen(uint16_t color);

/*
 * @brief invert display
 *
 * @param i invert select
 */
void invertDisplay(boolean i);

/*
 * @brief convert 888 color data to 16bit color data
 *
 * @param r, g, b 888 color data
 *
 * @return 16bit color data
 */
uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

/*
 * @brief set screen rotation
 *
 * @param r rotaion
 */
void setRotation(uint8_t r);

/*
 * @brief draw a image at given location
 *
 * @param *img image data
 * @param x from 0 to 320
 * @param y from 0 to 480
 * @param w image width from 0 to 320
 * @param h image height from 0 to 480
 */
void drawImage(uint8_t* img, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

```

## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266  |             |             |      √      | 
FireBeetle-BLE4.1 |             |       √      |            | 
