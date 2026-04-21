#define USER_SETUP_LOADED

// ===== DRIVER =====
#define ST7735_DRIVER

// ===== DISPLAY SIZE =====
#define TFT_WIDTH  128
#define TFT_HEIGHT 160

// ===== PIN CONFIG =====
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5
#define TFT_DC   16
#define TFT_RST  17

// ===== PANEL TYPE =====
// This is the correct base for most ST7735S 1.8" displays
#define ST7735_GREENTAB

// ===== INTERNAL OFFSETS (FINAL CALIBRATION) =====
#define CGRAM_OFFSET
#define TFT_OFFSET_X  0
#define TFT_OFFSET_Y  14

// ===== COLOR ORDER =====
#define TFT_RGB_ORDER TFT_BGR

// ===== OPTIONAL =====
// Uncomment ONLY if colors are inverted
// #define TFT_INVERSION_ON

// ===== SPI SPEED =====
#define SPI_FREQUENCY 27000000
#define SPI_READ_FREQUENCY 20000000

// ===== TRANSACTIONS =====
#define SUPPORT_TRANSACTIONS