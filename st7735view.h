#include "View.h"

class ST7735 : public View {
public:
    ST7735(Adafruit_ST7735 &tft): View(128,128), adafruit(tft) {

    }
    ~ST7735() {

    }

    void drawPixel(int16_t x, int16_t y, uint16_t color) override {
        adafruit.drawPixel(x, y, color);
    }

    void fillScreen(uint16_t color) override {
        adafruit.fillScreen(color);
    }
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override {
        adafruit.drawFastVLine(x,y,h,color);
    }
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override {
        adafruit.drawFastHLine(x,y,w,color);
    }
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override {
        adafruit.fillRect(x,y,w,h,color);
    }
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override {
        adafruit.drawRect(x,y,w,h,color);
    }
    void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size_x, uint8_t size_y) override {
        adafruit.drawChar(x,y,c, color, bg, size_x, size_y);
    }
private:
    Adafruit_ST7735 &adafruit;
};