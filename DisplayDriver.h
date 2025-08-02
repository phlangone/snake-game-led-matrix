/*
  Author: Paulo H. Langone Miranda
  Date:   jul/2025
  Brief:  Library for MAX7219 display driver
*/

#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

// Standard C
#include <stdint.h>

// Arduino includes
#include <Arduino.h>
#include <SPI.h>

/**
 * Defines & addresses
 */
#define WIDTH 		8		// Matrix width
#define HEIGHT 		8		// Matrix height

// Registers Address
#define DECODE_MODE_REG	  0x09	// Decode mode register address
#define INTENSITY_REG	    0x0a	// Display Intensity register address
#define SCAN_LIMIT_REG 	  0x0b	// Scan limit register address
#define SHUTDOWN_REG	    0x0c	// Shutdown register address
#define DISP_TEST_REG	    0x0f	// Display test register address

// Display addresses (from datasheet) are the rows
#define ROW0		0x01	// Row 0 address
#define ROW1		0x02	// Row 1 address
#define ROW2		0x03	// Row 2 address
#define ROW3		0x04	// Row 3 address
#define ROW4		0x05	// Row 4 address
#define ROW5		0x06	// Row 5 address
#define ROW6		0x07	// Row 6 address
#define ROW7		0x08	// Row 7 address

// Display digits (from datasheet) are the columns
#define COL0		0x80	// Column 0 code
#define COL1		0x40	// Column 1 code
#define COL2		0x20	// Column 2 code
#define COL3		0x10	// Column 3 code
#define COL4		0x08	// Column 4 code
#define COL5		0x04	// Column 5 code
#define COL6		0x02	// Column 6 code
#define COL7		0x01	// Column 7 code

// Decode Mode (BCD Code B decoder, check datasheet for further info)
#define NO_DECODE             0x00  // No decode - SELECT THIS TO LED MATRIX
#define DECODE_DIG0           0x01  // Decode digit 0 only
#define DECODE_DIG3_TO_DIG0   0x0f  // Decode from digit 3 to digit 0
#define DECODE_ALL            0xff  // Decode all digits 

// Intensity Duty Cycle (%)
#define INTENSITY_3   0x00  // 3%
#define INTENSITY_9   0x01  // 9%
#define INTENSITY_16  0x02  // 16%
#define INTENSITY_22  0x03  // 22%
#define INTENSITY_28  0x04  // 28%
#define INTENSITY_34  0x05  // 34%
#define INTENSITY_41  0x06  // 41%
#define INTENSITY_47  0x07  // 47%
#define INTENSITY_53  0x08  // 53%
#define INTENSITY_59  0x09  // 59%
#define INTENSITY_66  0x0a  // 66%
#define INTENSITY_72  0x0b  // 72%
#define INTENSITY_78  0x0c  // 78%
#define INTENSITY_84  0x0d  // 84%
#define INTENSITY_91  0x0e  // 91%
#define INTENSITY_97  0x0f  // 97%

// Scan Limit
#define SCAN_DIG0       0x00  // Scan 0
#define SCAN_TIL_DIG1   0x01  // Scan 0 & 1
#define SCAN_TIL_DIG2   0x02  // Scan 0, 1 & 2
#define SCAN_TIL_DIG3   0x03  // Scan 0, 1, 2, & 3
#define SCAN_TIL_DIG4   0x04  // Scan 0, 1, 2, 3 & 4
#define SCAN_TIL_DIG5   0x05  // Scan 0, 1, 2, 3, 4 & 5
#define SCAN_TIL_DIG6   0x06  // Scan 0, 1, 2, 3, 4, 5 & 6
#define SCAN_ALL        0x07  // Scan all

// Shutdown
#define SHUTDOWN_OFF  0x01
#define SHUTDOWN_ON   0x00

// Display test
#define TEST_OFF  0x00
#define TEST_ON   0x01

// MAX7219 USAGE
#define DIGITS 0
#define MATRIX 1

// Main class
class DisplayDriver
{
  public:
    // Class constructor
    DisplayDriver(uint8_t din, uint8_t cs, uint8_t clk, uint8_t mode) : dinPin(din), csPin(cs), clkPin(clk), displayMode(mode), mySettings(8000000, MSBFIRST, SPI_MODE0) {}

    // Initialize driver
    void begin(void);

    // Decode mode
    void setDecode(uint8_t mode = DECODE_ALL);

    // Intensity (Display brightness)
    void setIntensity(uint8_t intensity = INTENSITY_97);

    // Scan limit
    void setScanLimit(uint8_t limit = SCAN_ALL);

    // Shutdown mode
    void setShutdown(uint8_t mode = SHUTDOWN_OFF);

    // Test mode
    void setTest(uint8_t mode = TEST_OFF);

    // Draw Pixel
    void drawPixel(uint8_t row, uint8_t col);

    // Clear Display
    void clearDisplay(void);

    // Fill Display
    void fillDisplay(void);

    // Fill Row
    void fillRow(uint8_t row, uint8_t val);

    // Draw Bitmap
    void drawBitmap(uint8_t * bmp);

    // Draw Line
    void drawLine(uint8_t xi, uint8_t yi, uint8_t xf, uint8_t yf);

    // Draw Circle

    // Draw Rectangle

  private:
    // MAX7219 Pins
    uint8_t dinPin, csPin, clkPin;

    // MAX7219 Mode
    uint8_t displayMode;

    // SPI Settings
    SPISettings mySettings;

    // Slave enable
    inline void slaveEnable() { digitalWrite(csPin, LOW); }

    // Slave Disable
    inline void slaveDisable() { digitalWrite(csPin, HIGH); }
};

#endif // DISPLAYDRIVER_H