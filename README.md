# ILI9488

FireBeetle Covers-3.5'' TFT LCD is 320x480 dots 3.5" color tft lcd module display with ILI9488 controller, 
superior display quality, super wide viewing angle.
You can draw different graphs in the module. Additionally, there is a SD card with SPI interface that make colorful image displays are available.
The module can shine your works in many fields. You can put the module to small works, embed it into industrial products as a display.

For your reference, demos are available to display the module.
These demos are available in Arduino uno, Arduino leonardo, fireBeetle bluno 2, fireBeetle esp8266, fireBeetle esp32.
The screen only need 3 IO interfaces to drive, you can do more with unoccupied pins.
Good frame rate is available in the ESP series of controllers.

![back face](https://raw.githubusercontent.com/DFRobot/binaryfiles/master/DFR0480/DFR0480svg1.png)

## DFRobot_ILI9488 Library for Arduino
---------------------------------------------------------
Provide a library faciltates operations in the LCD(Liquid Crysatal DISPLAY) that drived by ILI9488.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Result](#result)
* [Methods](#methods)

* [History](#history)
* [Depends](#depends)
* [Compatibility](#compatibility)
* [Credits](#credits)
<snippet>
<content>

## Summary

Input commands and draw different figures in the LCD.

## Feature

Support different drawings in the screen, including point, line, circle, rectangle, triangle,rounded rectangle and some commands.<br>
Support English characters.<br>
SPI: the redraw rate can reach to 10 frames per second when redrawed by ESP series controllers.<br>

## Installation

Download the library ZIP file and unzip it to the Arduino folder of the library.<br>
(If you haven't download DFRobot display library before,you need to download it first to drive (https://github.com/DFRobot/DFRobot_Display))<br>
SPI_SD interface is available when compatible SD card libraries of ESP32 and ESP8266(https://github.com/DFRobot/SD_SPI)

## Result

Functions supports. <0 means error;>0 means warning, 0 means OK .

begin type

value              |             result            
------------------ | -------------------------------------------
-1                 |             error             
1                  |      no feedback test         

function type

Value              |            result              
------------------ | -------------------------------------------
-4                 |          mem overflow
-3                 |          not support
-2                 |          param
-1                 |          error
1                  |          out range

## Methods

```C++

#include "DFRobot_ILI9488_SPI.h"

Except special instructions, all axis as below are relative to the source node , color represents 16 bits 565 color data 

//color define 
#define DISPLAY_BLACK       0x0000      /*   0,   0,   0 */
#define DISPLAY_NAVY        0x000F      /*   0,   0, 128 */
#define DISPLAY_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DISPLAY_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define DISPLAY_MAROON      0x7800      /* 128,   0,   0 */
#define DISPLAY_PURPLE      0x780F      /* 128,   0, 128 */
#define DISPLAY_OLIVE       0x7BE0      /* 128, 128,   0 */
#define DISPLAY_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define DISPLAY_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define DISPLAY_BLUE        0x001F      /*   0,   0, 255 */
#define DISPLAY_GREEN       0x07E0      /*   0, 255,   0 */
#define DISPLAY_CYAN        0x07FF      /*   0, 255, 255 */
#define DISPLAY_RED         0xF800      /* 255,   0,   0 */
#define DISPLAY_MAGENTA     0xF81F      /* 255,   0, 255 */
#define DISPLAY_YELLOW      0xFFE0      /* 255, 255,   0 */
#define DISPLAY_WHITE       0xFFFF      /* 255, 255, 255 */
#define DISPLAY_ORANGE      0xFD20      /* 255, 165,   0 */
#define DISPLAY_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define DISPLAY_PINK        0xF81F

/*
 * @brief ILI9488 objective
 *
 * @param ILI9488 control Pin
 *    pin_cs        ILI9488 cs pin
 *    pin_cd        ILI9488 cd/rs pin
 *
 * @remark if there is not have a power-on reset circuit.please hand-reset
 */
DFRobot_ILI9488_SPI(uint8_t pin_cs, uint8_t pin_cd);

/*
 * @brief lib begin
 *
 * @return begin result
 */
int16_t begin(void);

/*
 * @brief fill screen
 */
void fillScreen(uint16_t color);

/*
 * @brief draw a pixel
 *
 * @param x       x-axis coordinates
 *        y       y-axis coordinates
 */
void drawPixel(int16_t x, int16_t y, uint16_t color);

/*
 * @brief draw a line
 *
 * @param x0        The x-axis of the starting point
 *        y0        The y-axis of the starting point
 *        x1        The x-axis of the terminal point
 *        y1        The y-axis of the terminal point
 */
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
              uint16_t color);

/*
 * @brief draw a horizontal line
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        width     The line lenth
 */
void drawHLine(int16_t x, int16_t y, int16_t width, uint16_t color);

/*
 * @brief draw a vertical line
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        height    The line lenth
 */
void drawVLine(int16_t x, int16_t y, int16_t height, uint16_t color);

/*
 * @brief draw a rectangle
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        width     The rectangle width
 *        height    The rectangle height
 */
void drawRect(int16_t x, int16_t y, int16_t width, int16_t height, 
              uint16_t color);

/*
 * @brief draw a fill rectangle
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        width     The rectangle width
 *        height    The rectangle height
 */
void fillRect(int16_t x, int16_t y, int16_t width, int16_t height, 
              uint16_t color);

/*
 * @brief draw a circle
 *
 * @param x         The x-axis of the center
 *        y         The y-axis of the center
 *        r         The circle radius 
 */
void drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color);

/*
 * @brief draw a fill circle
 *
 * @param x         The x-axis of the center
 *        y         The y-axis of the center
 *        r         The circle radius
 */
void fillCircle(int16_t x, int16_t y, int16_t r, uint16_t color);

/*
 * @brief draw a triangle
 *
 * @param x0        The x-axis of the first point
 *        y0        The y-axis of the first point
 *        x0        The x-axis of the second point
 *        y0        The y-axis of the second point
 *        x0        The x-axis of the third point
 *        y0        The y-axis of the third point
 */
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
                  int16_t x2, int16_t y2, uint16_t color);
                  
/*
 * @brief draw a fill triangle
 *
 * @param x0        The x-axis of the first point
 *        y0        The y-axis of the first point
 *        x0        The x-axis of the second point
 *        y0        The y-axis of the second point
 *        x0        The x-axis of the third point
 *        y0        The y-axis of the third point
 */
void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
                  int16_t x2, int16_t y2, uint16_t color);

/*
 * @brief draw a rounded rectangle
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        width     The rectangle width
 *        height    The rectangle height
 *        r         The rounded corner radius
 */
void drawRoundRect(int16_t x, int16_t y, int16_t, width, int16_t height, 
                   int16_t r, uint16_t color);
                   
/*
 * @brief draw a fill rounded rectangle
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        width     The rectangle width
 *        height    The rectangle height
 *        r         The rounded corner radius
 */
void fillRoundRect(int16_t x, int16_t y, int16_t, width, int16_t height, 
                   int16_t r, uint16_t color);
                   
/*
 * @brief Set axis of the source node(relative to the top left corner)
 *
 * @param x         The x-axis of the source node
 *        y         The y-axis of the source node
 */
void setOrign(int16_t x, int16_t y);

/*
 * @brief Get axis of the source node(relative to the top left corner)
 *
 * @param x         Address to store varialbles of the source node x-axis
 *        y         Address to store varialbles of the source node y-axis
 */
void getOrign(int16_t* pX, int16_t* pY);

/*
 * @brief Set printing point axis (relative to the top left corner)
 *
 * @param x         x-axis of the printed point
 *        y         y-axis of the printed point
 */
void setCursor(int16_t x, int16_t y);

/*
 * @brief Get axis of the printed point(relative to the top left corner)
 *
 * @param x         Address to store varialbles of the printed point x-axis
 *        y         Address to store varialbles of the printed point y-axis
 */
void getCursor(int16_t* pX, int16_t* pY);

/*
 * @brief Set text color
 */
void setTextColor(uint16_t color);

/*
 * @brief Get text color
 *
 * @return 16 bits color data
 */
uint16_t getTextColor(void);

/*
 * @brief Set text size
 *
 * @param size        text size
 */
void setTextSize(uint8_t size);

/*
 * @brief Get text size
 *
 * @return text size
 */
uint8_t getTextSize(void);

/*
 * @brief Print text in the print point, the usage method is as same as the serial port
 */
size_t print(...);
size_t println(...);

size_t printf(...);  //Only ESP series cpntrollers are supportive

enum eROTATION {
  eROTATION_0,
  eROTATION_90,
  eROTATION_180,
  eROTATION_270
};

/*
 * @brief Set the screen to rotate
 *
 * @param eRotation       The rotation angle
 */
void setRotation(eROTATION eRotation);  //Need the hardware support

/*
 * @brief Get the screen rotation
 *
 * @return The rotation angle
 */
eROTATION getRotation(void);

/*
 * @brief Get screen width
 *
 * @return The screen width
 */
int16_t getWidth(void);

/*
 * @brief Get screen hight
 *
 * @return The  screen hight
 */
int16_t getHeight(void);

/*
 * @brief Display bmp file
 *
 * @param s       file objectiv
 *        x       The x-axis of the starting point
 *        y       The y-axis of the starting point
 *
 * @return Error message
 */
int16_t drawBmp(Stream *s, int16_t x, int16_t y);

/*
 * @brief invertDisplay
 *
 * @param eInvert       
 */
int16_t getWidth(void);

/*
 * @brief Get screen hight
 *
 * @return The  screen hight
 */
int16_t getHeight(void);

/*
 * @brief Display bmp file
 *
 * @param s       file objectiv
 *        x       The x-axis of the starting point
 *        y       The y-axis of the starting point
 *
 * @return Error message
 */
int16_t drawBmp(Stream *s, int16_t x, int16_t y);

/*
 * @brief invertDisplay
 *
 * @param eInvert       
 */
int16_t getWidth(void);

/*
 * @brief display ON
 */
void displayON(void);

/*
 * @brief display OFF
 */
void displayOFF(void);

/*
 * @brief display sleep IN
 */
void displaySleepIN(void);

/*
 * @brief display sleep OUT
 */
void displaySleepOUT(void);

```

## Depends

Projects           |                     URL                       | Remarks
------------------ | :-------------------------------------------: | -----------
DFRobot_Display    |  https://github.com/DFRobot/DFRobot_Display   | must
SPI_SD             |  https://github.com/DFRobot/SD_SPI            | optional

## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266  |      √       |             |            | 
FireBeetle-BLE4.1 |       √      |             |            | 
Arduino uno |       √      |             |            | 
Arduino leonardo |      √       |             |            | 

## History



## Credits

Written by DFRobot_xiaowo, 2017. (Welcome to our [website](https://www.dfrobot.com/))
