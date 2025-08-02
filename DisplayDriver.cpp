/*
  Author: Paulo H. Langone Miranda
  Date:   jul/2025
  Brief:  Library for MAX7219 display driver
*/

// Standard C
#include <stdint.h>

// Arduino includes
#include <Arduino.h>
#include <SPI.h>

// Library include
#include "DisplayDriver.h"
#include "SnakeGame.h"

// Initialize driver
void DisplayDriver::begin(void)
{
  /*
   * Initializes SPI
   */
  SPI.begin();

  /*
   * Initializes driver for 8 digits operation
   */
  if(displayMode == DIGITS)
  {
    // Stardard settings - 8 digits mode
    setShutdown();
    setDecode();
    setIntensity();
    setScanLimit();
  }

  /*
   * Initializes driver for matrix operation
   */
  else if(displayMode == MATRIX)
  {
    // Settings for matrix mode
    setShutdown();
    setDecode(NO_DECODE);
    setIntensity();
    setScanLimit();   
  }
}

// Set decode mode
void DisplayDriver::setDecode(uint8_t mode)
{
  slaveEnable();
  SPI.beginTransaction(mySettings);
  SPI.transfer(DECODE_MODE_REG);
  SPI.transfer(mode);
  SPI.endTransaction(); 
  slaveDisable();
}

// Set display intensity (brightness)
void DisplayDriver::setIntensity(uint8_t intensity)
{
  slaveEnable();
  SPI.beginTransaction(mySettings);
  SPI.transfer(INTENSITY_REG);
  SPI.transfer(intensity);
  SPI.endTransaction();
  slaveDisable();  
}

// Set digits scan limit
void DisplayDriver::setScanLimit(uint8_t limit)
{
  slaveEnable();
  SPI.beginTransaction(mySettings);
  SPI.transfer(SCAN_LIMIT_REG);
  SPI.transfer(limit);
  SPI.endTransaction();
  slaveDisable(); 
}

// Set shutdown mode
void DisplayDriver::setShutdown(uint8_t mode)
{
  slaveEnable();
  SPI.beginTransaction(mySettings);
  SPI.transfer(SHUTDOWN_REG);
  SPI.transfer(mode);
  SPI.endTransaction();
  slaveDisable(); 
}

// Set test mode
void DisplayDriver::setTest(uint8_t mode)
{
  slaveEnable();
  SPI.beginTransaction(mySettings);
  SPI.transfer(DISP_TEST_REG);
  SPI.transfer(mode);
  SPI.endTransaction();
  slaveDisable(); 
}

// Draw a pixel on the display
void DisplayDriver::drawPixel(uint8_t row, uint8_t col)
{
  slaveEnable();
  SPI.beginTransaction(mySettings);
  SPI.transfer(row+1);
  SPI.transfer((1 << col));
  SPI.endTransaction();
  slaveDisable();   
}

// Clear display
void DisplayDriver::clearDisplay(void)
{
  if(displayMode == DIGITS)
  {

  }

  else if(displayMode == MATRIX)
  {
    for(uint8_t row = 0; row <= HEIGHT; row++)
    {
      fillRow(row, 0x00);
    }
  }
}

// Fill Display (turn all on)
void DisplayDriver::fillDisplay(void)
{
  for(int i = 0; i <= HEIGHT ; i++)
  {
    fillRow(i-1, 0xff);
  }
}

// Fill row with a value
void DisplayDriver::fillRow(uint8_t row, uint8_t val)
{
  slaveEnable();
  SPI.beginTransaction(mySettings);
  SPI.transfer(row+1);
  SPI.transfer(val);
  SPI.endTransaction();
  slaveDisable();   
}

// Draw a referenced bitmap on the display
void DisplayDriver::drawBitmap(uint8_t *bmp)
{
  for(uint8_t row = 0; row <= HEIGHT; row++)
	{
	  fillRow(row-1, bmp[row-1]);
	}
}

// Draw a line on the display
void DisplayDriver::drawLine(uint8_t xi, uint8_t yi, uint8_t xf, uint8_t yf)
{
  // Same line
  if(xi == xf)
  {
    if (yi > yf)
    {
        uint8_t temp = yi;
        yi = yf;
        yf = temp;
    }

    uint8_t val = 0x00;
    for (int i = yi; i <= yf; i++) 
    {
      val |= (1 << i);
    }
    fillRow(xi, val);  
  }

  // Same column
  else if(yi == yf)
  {
    if (xi > xf)
    {
        uint8_t temp = xi;
        xi = xf;
        xf = temp;
    }

    for(int i = xi; i <= xf; i++)
    {
      drawPixel(i, yi);
    }
  }

  // Draw line using Bresenham's algorithm
  else
  {
    int dx = abs((int)xf - (int)xi);
    int dy = abs((int)yf - (int)yi);

    int sx = (xi < xf) ? 1 : -1;
    int sy = (yi < yf) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        
        if (xi < 8 && yi < 8)
        {
            drawPixel(xi, yi);
        }

        if (xi == xf && yi == yf) break;

        int e2 = 2 * err;

        if (e2 > -dy) 
        {
            err -= dy;
            xi += sx;
        }

        if (e2 < dx) 
        {
            err += dx;
            yi += sy;
        }
    }
  }
}