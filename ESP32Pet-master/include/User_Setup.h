#pragma once

#define USER_SETUP_LOADED

#define ST7735_DRIVER

#define TFT_WIDTH  128
#define TFT_HEIGHT 160

#define ST7735_BLACKTAB

// ===== PINS =====
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   16
#define TFT_RST  17

// ===== SPEED =====
#define SPI_FREQUENCY  27000000
#define SPI_READ_FREQUENCY 20000000

// ===== ENABLE FONTS (THIS FIXES YOUR ISSUE) =====
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF