#ifndef ARDUINO_MENU_ICONS_H
#define ARDUINO_MENU_ICONS_H

#ifndef PROGMEM
#define PROGMEM  
#endif

#include <Arduino.h>

// 'Screenshot 2022-06-19 at 13', 16x16px
extern uint16_t _bmp_play_off [256] PROGMEM;
// 'Screenshot 2022-06-19 at 13', 16x16px
extern uint16_t _bmp_play_on [256] PROGMEM ;
// 'Screenshot 2022-06-19 at 12', 16x16px
extern uint16_t _bmp_settings_off [256] PROGMEM;
// 'Screenshot 2022-06-19 at 12', 16x16px
extern uint16_t _bmp_edit_off [256] PROGMEM ;
// 'Screenshot 2022-06-19 at 12', 16x16px
extern uint16_t _bmp_edit_on [256] PROGMEM;
// 'Screenshot 2022-06-19 at 12', 16x16px
extern uint16_t _bmp_settings_on [256] PROGMEM;

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1632)
static int _bmp_allArray_LEN = 6;
static uint16_t* _bmp_allArray[6] = {
	_bmp_play_off,
	_bmp_play_on,
	_bmp_settings_off,
	_bmp_settings_on,
	_bmp_edit_off,
	_bmp_edit_on
};

#endif // ARDUINO_MENU_ICONS_H