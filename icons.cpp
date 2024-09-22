#include <Arduino.h>

// 'Screenshot 2022-06-19 at 13', 16x16px
uint16_t _bmp_play_off [] = {
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xe71c, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x2124, 0xa514, 0xf7be, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0000, 0x0841, 0x6b6d, 0xdefb, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0000, 0x0000, 0x0000, 0x39c7, 0xbdd7, 0xffdf, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0000, 0x0000, 0x0000, 0x0000, 0x10a2, 0x8c71, 0xef5d, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x528a, 0xdedb, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x528a, 0xdedb, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0000, 0x0000, 0x0000, 0x0000, 0x10a2, 0x8c71, 0xef5d, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0000, 0x0000, 0x0000, 0x39c7, 0xbdd7, 0xffdf, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0000, 0x0841, 0x6b6d, 0xdefb, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x2124, 0xa514, 0xf7be, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xe71c, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
};
// 'Screenshot 2022-06-19 at 13', 16x16px
uint16_t _bmp_play_on [] PROGMEM = {
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xe71c, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x1322, 0xa514, 0xf7be, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0380, 0x0360, 0x6b6d, 0xdefb, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x03a0, 0x03e0, 0x03a0, 0x1b83, 0xbdd7, 0xffdf, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x03a0, 0x03e0, 0x03e0, 0x03e0, 0x0380, 0x8c71, 0xef5d, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x03a0, 0x03e0, 0x03e0, 0x03e0, 0x03e0, 0x0380, 0x4308, 0xdedb, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x03a0, 0x03e0, 0x03e0, 0x03e0, 0x03e0, 0x0380, 0x4308, 0xdedb, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x03a0, 0x03e0, 0x03e0, 0x03e0, 0x0380, 0x8c71, 0xef5d, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x03a0, 0x03e0, 0x03a0, 0x1b83, 0xbdd7, 0xffdf, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x0380, 0x0360, 0x6b6d, 0xdefb, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xbdf7, 0x1322, 0xa514, 0xf7be, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xe71c, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
};
// 'Screenshot 2022-06-19 at 12', 16x16px
uint16_t _bmp_settings_off [] PROGMEM = {
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xef7d, 0x0000, 0x0000, 0x0000, 0x0000, 0xf7be, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb596, 0x0000, 0x0000, 0x0000, 0x0000, 0xb5b6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xe73c, 0x6b6d, 0xe71c, 0xe73c, 0x52aa, 0x0000, 0x0000, 0x0000, 0x0000, 0x52aa, 0xe73c, 0xe71c, 0x6b6d, 0xe73c, 0xffff, 
	0xffff, 0x6b6d, 0x0000, 0x0000, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0861, 0x0000, 0x0000, 0x6b6d, 0xffff, 
	0xce79, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd69a, 
	0x4a69, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3186, 0xce79, 0xce79, 0x3186, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x528a, 
	0xd6ba, 0x0000, 0x0000, 0x0000, 0x0000, 0x3186, 0xffdf, 0xa514, 0xa514, 0xffdf, 0x31a6, 0x0000, 0x0000, 0x0000, 0x0000, 0xd6ba, 
	0xffff, 0xce79, 0x0000, 0x0000, 0x0000, 0xbdd7, 0xa534, 0x0000, 0x0000, 0xa534, 0xad55, 0x0000, 0x0000, 0x0000, 0xce79, 0xffff, 
	0xffff, 0xce79, 0x0000, 0x0000, 0x0000, 0xb596, 0xa534, 0x0000, 0x0000, 0xa534, 0xad55, 0x0000, 0x0000, 0x0000, 0xce79, 0xffff, 
	0xd6ba, 0x0000, 0x0000, 0x0000, 0x0000, 0x31a6, 0xffdf, 0xa514, 0xa514, 0xffdf, 0x31a6, 0x0000, 0x0000, 0x0000, 0x0000, 0xd6ba, 
	0x4a69, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x31a6, 0xce79, 0xce79, 0x31a6, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4a69, 
	0xd69a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd69a, 
	0xffff, 0x6b6d, 0x0000, 0x0000, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1082, 0x0000, 0x0000, 0x6b6d, 0xffff, 
	0xffff, 0xe73c, 0x6b6d, 0xe71c, 0xe73c, 0x52aa, 0x0000, 0x0000, 0x0000, 0x0000, 0x52aa, 0xe73c, 0xe71c, 0x6b6d, 0xe73c, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb596, 0x0000, 0x0000, 0x0000, 0x0000, 0xb5b6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xef7d, 0x0000, 0x0000, 0x0000, 0x0000, 0xf7be, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
};
// 'Screenshot 2022-06-19 at 12', 16x16px
uint16_t _bmp_edit_off [] PROGMEM = {
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdedb, 0xdedb, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd6ba, 0x39c7, 0x39c7, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd6ba, 0x39c7, 0x0000, 0x0000, 0x39c7, 0xd6ba, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffdf, 0x8430, 0x0020, 0x0000, 0x0000, 0x0000, 0x39c7, 0xd6ba, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd6ba, 0x8430, 0xdefb, 0x7bcf, 0x0020, 0x0000, 0x0000, 0x0000, 0x39c7, 0xd6ba, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xd6ba, 0x39c7, 0x0020, 0x7bcf, 0xdefb, 0x7bcf, 0x0020, 0x0000, 0x0000, 0x0000, 0x39c7, 0xdefb, 
	0xffff, 0xffff, 0xffff, 0xd6ba, 0x39c7, 0x0000, 0x0000, 0x0020, 0x7bcf, 0xdefb, 0x7bcf, 0x0020, 0x0000, 0x0000, 0x39c7, 0xdefb, 
	0xffff, 0xffff, 0xd6ba, 0x39c7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x7bcf, 0xdefb, 0x7bcf, 0x0020, 0x39c7, 0xd6ba, 0xffff, 
	0xffff, 0xd6ba, 0x39c7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x7bcf, 0xdefb, 0x8430, 0xd6ba, 0xffff, 0xffff, 
	0xdedb, 0x39c7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x8430, 0xffdf, 0xffff, 0xffff, 0xffff, 
	0xbdf7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39c7, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xbdf7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39c7, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xbdf7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39c7, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xbdf7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39c7, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xbdf7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39c7, 0xd6ba, 0xe71c, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xe71c, 
	0xe71c, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xdedb, 0xffff, 0xe71c, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xe71c
};
// 'Screenshot 2022-06-19 at 12', 16x16px
uint16_t _bmp_edit_on [] PROGMEM = {
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdedb, 0xdedb, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd6ba, 0x98e3, 0x98e3, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd6ba, 0x98e3, 0xa800, 0xa800, 0x98c3, 0xd6ba, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffdf, 0x8430, 0x9800, 0xa800, 0xa800, 0xa800, 0x98c3, 0xd6ba, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd6ba, 0x8430, 0xdefb, 0x7bcf, 0x9800, 0xa800, 0xa800, 0xa800, 0x98c3, 0xd6ba, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xd6ba, 0x98e3, 0x9800, 0x7bcf, 0xdefb, 0x7bcf, 0x9800, 0xa800, 0xa800, 0xa800, 0x98e3, 0xdefb, 
	0xffff, 0xffff, 0xffff, 0xd6ba, 0x98c3, 0xa800, 0xa800, 0x9800, 0x7bcf, 0xdefb, 0x7bcf, 0x9800, 0xa800, 0xa800, 0x98e3, 0xdefb, 
	0xffff, 0xffff, 0xd6ba, 0x98c3, 0xa800, 0xa800, 0xa800, 0xa800, 0x9800, 0x7bcf, 0xdefb, 0x7bcf, 0x9800, 0x98e3, 0xd6ba, 0xffff, 
	0xffff, 0xd6ba, 0x98c3, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0x9800, 0x7bcf, 0xdefb, 0x8430, 0xd6ba, 0xffff, 0xffff, 
	0xdedb, 0x98e3, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0x9800, 0x8430, 0xffdf, 0xffff, 0xffff, 0xffff, 
	0xbdf7, 0xa000, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0x98e3, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xbdf7, 0xa000, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0x98c3, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xbdf7, 0xa000, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0x98c3, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xbdf7, 0xa000, 0xa800, 0xa800, 0xa800, 0xa800, 0xa800, 0x98c3, 0xd6ba, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xbdf7, 0x9000, 0xa000, 0xa000, 0xa000, 0xa000, 0x98e3, 0xd6ba, 0xe71c, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xe71c, 
	0xe71c, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xdedb, 0xffff, 0xe71c, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xbdf7, 0xe71c
};
// 'Screenshot 2022-06-19 at 12', 16x16px
uint16_t _bmp_settings_on [] PROGMEM = {
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xef7d, 0x21da, 0x221c, 0x221c, 0x21da, 0xf7be, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb596, 0x21da, 0x221c, 0x221c, 0x21da, 0xb5b6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xe73c, 0x6b6e, 0xe71c, 0xe73c, 0x4a91, 0x21fb, 0x221c, 0x221c, 0x21fb, 0x4a91, 0xe73c, 0xe71c, 0x6b6e, 0xe73c, 0xffff, 
	0xffff, 0x6b4e, 0x19b9, 0x21da, 0x21da, 0x21fb, 0x21fc, 0x221c, 0x221c, 0x21fc, 0x21fb, 0x21da, 0x21da, 0x19b9, 0x6b4e, 0xffff, 
	0xce79, 0x19b9, 0x21fc, 0x221c, 0x221c, 0x221c, 0x21fc, 0x21db, 0x21db, 0x21fc, 0x221c, 0x221c, 0x221c, 0x21fc, 0x19b9, 0xd69a, 
	0x4254, 0x21fb, 0x221c, 0x221c, 0x221c, 0x21fc, 0x29f9, 0xce79, 0xce79, 0x29f9, 0x21fc, 0x221c, 0x221c, 0x221c, 0x21db, 0x4a71, 
	0xd6ba, 0x19b9, 0x21fc, 0x221c, 0x21fc, 0x29f9, 0xffdf, 0xa514, 0xa514, 0xffdf, 0x29f9, 0x21fc, 0x221c, 0x21fc, 0x19b9, 0xd6ba, 
	0xffff, 0xce79, 0x21db, 0x21fc, 0x21db, 0xbdd7, 0xa534, 0x0000, 0x0000, 0xa534, 0xad55, 0x21db, 0x21fc, 0x21db, 0xce79, 0xffff, 
	0xffff, 0xce79, 0x21db, 0x21fc, 0x21db, 0xb596, 0xa534, 0x0000, 0x0000, 0xa534, 0xad55, 0x21db, 0x21fc, 0x21db, 0xce79, 0xffff, 
	0xd6ba, 0x19b9, 0x21fc, 0x221c, 0x21fc, 0x29f9, 0xffdf, 0xa514, 0xa514, 0xffdf, 0x29f9, 0x21fc, 0x221c, 0x21fc, 0x19b9, 0xd6ba, 
	0x4254, 0x21fb, 0x221c, 0x221c, 0x221c, 0x21fc, 0x29f9, 0xce79, 0xce79, 0x29f9, 0x21fc, 0x221c, 0x221c, 0x221c, 0x21fb, 0x4254, 
	0xd69a, 0x19b9, 0x21fc, 0x221c, 0x221c, 0x221c, 0x21fc, 0x21db, 0x21db, 0x21fc, 0x221c, 0x221c, 0x221c, 0x21fc, 0x19b9, 0xd69a, 
	0xffff, 0x6b4e, 0x19b9, 0x21da, 0x21da, 0x21fb, 0x21fc, 0x221c, 0x221c, 0x21fc, 0x21fb, 0x21da, 0x21da, 0x19b9, 0x6b4e, 0xffff, 
	0xffff, 0xe73c, 0x6b6e, 0xe71c, 0xe73c, 0x4a91, 0x21fb, 0x221c, 0x221c, 0x21fb, 0x4a91, 0xe73c, 0xe71c, 0x6b6e, 0xe73c, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xb596, 0x21da, 0x221c, 0x221c, 0x21da, 0xb5b6, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xef7d, 0x21da, 0x221c, 0x221c, 0x21da, 0xf7be, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
};