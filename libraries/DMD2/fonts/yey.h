

/*
 * Fareed Read
 * http://www.facebook.com/fareedreads
 *
 * fontku
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : yey.h
 * Date                : 04.08.2019
 * Font size in bytes  : 8568
 * Font width          : 10
 * Font height         : 17
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef FONTKU_H
#define FONTKU_H

#define FONTKU_WIDTH 10
#define FONTKU_HEIGHT 17

const static uint8_t fontku[] PROGMEM = {
    0x21, 0x78, // size
    0x0A, // width
    0x11, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x02, 0x05, 0x08, 0x06, 0x08, 0x07, 0x02, 0x04, 0x04, 
    0x06, 0x06, 0x02, 0x04, 0x02, 0x07, 0x06, 0x03, 0x06, 0x06, 
    0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x02, 0x02, 0x05, 0x05, 
    0x05, 0x06, 0x08, 0x06, 0x06, 0x06, 0x06, 0x04, 0x04, 0x06, 
    0x06, 0x02, 0x06, 0x06, 0x04, 0x07, 0x06, 0x06, 0x06, 0x07, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x0A, 0x07, 0x06, 0x06, 0x04, 
    0x05, 0x04, 0x05, 0x06, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x03, 0x05, 0x05, 0x02, 0x02, 0x05, 0x02, 0x08, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x03, 0x05, 0x06, 0x0A, 0x06, 0x06, 
    0x05, 0x06, 0x02, 0x06, 0x06, 0x06, 
    
    // font data
    0xFE, 0xFE, 0x1B, 0x1B, 0x00, 0x00, // 33
    0x1E, 0x1E, 0x00, 0x1E, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0x00, 0x20, 0xE0, 0xFE, 0x3E, 0xE0, 0xFE, 0x3E, 0x03, 0x1F, 0x1F, 0x03, 0x1F, 0x1F, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0x3C, 0x7E, 0xE7, 0xC7, 0x9E, 0x1C, 0x0E, 0x1E, 0x38, 0x39, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 36
    0x7E, 0x42, 0x7E, 0x80, 0x60, 0x9C, 0x82, 0x80, 0x00, 0x10, 0x0E, 0x01, 0x00, 0x1F, 0x10, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
    0x3C, 0xFE, 0xC6, 0xC6, 0xDE, 0xDC, 0xC0, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 38
    0x1E, 0x1E, 0x00, 0x00, 0x00, 0x00, // 39
    0xF0, 0xFC, 0x0E, 0x02, 0x0F, 0x3F, 0x70, 0x40, 0x00, 0x00, 0x00, 0x00, // 40
    0x02, 0x0E, 0xFC, 0xF0, 0x40, 0x70, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, // 41
    0x6C, 0x28, 0xFE, 0xFE, 0x28, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x80, 0x80, 0xE0, 0xE0, 0x80, 0x80, 0x01, 0x01, 0x07, 0x07, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x38, 0x18, 0x00, 0x00, // 44
    0x80, 0x80, 0x80, 0x80, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, // 45
    0x00, 0x00, 0x18, 0x18, 0x00, 0x00, // 46
    0x00, 0x00, 0x80, 0xE0, 0x7C, 0x1E, 0x02, 0x10, 0x1E, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 47
    0xFC, 0xFE, 0x06, 0x06, 0xFE, 0xFC, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 48
    0x0C, 0xFE, 0xFE, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, // 49
    0x1C, 0x1E, 0x86, 0xE6, 0x7E, 0x1C, 0x18, 0x1E, 0x1F, 0x19, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 50
    0x1C, 0x1E, 0x46, 0xE6, 0xBE, 0x1C, 0x0E, 0x1E, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x00, 0xE0, 0xF8, 0x1E, 0xC6, 0xC0, 0x00, 0x07, 0x07, 0x06, 0x06, 0x1F, 0x1F, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 52
    0x7E, 0x7E, 0x66, 0x66, 0xE6, 0xC6, 0x0E, 0x1E, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0xFC, 0xFE, 0xC6, 0xC6, 0xCE, 0x8C, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 54
    0x0E, 0x0E, 0x06, 0xE6, 0xFE, 0x0E, 0x00, 0x18, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0xBC, 0xFE, 0x46, 0x46, 0xFE, 0xBC, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0x7C, 0xFE, 0xC6, 0xC6, 0xFE, 0xFC, 0x0C, 0x1C, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 57
    0xC0, 0xC0, 0x18, 0x18, 0x00, 0x00, // 58
    0xC0, 0xC0, 0x38, 0x18, 0x00, 0x00, // 59
    0x80, 0xC0, 0x60, 0x60, 0x30, 0x00, 0x01, 0x03, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x60, 0x60, 0x60, 0x60, 0x60, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x30, 0x60, 0x60, 0xC0, 0x80, 0x06, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x0C, 0x8E, 0xC6, 0x66, 0x7E, 0x3C, 0x00, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 63
    0xFC, 0x02, 0x02, 0x22, 0x92, 0xE2, 0x02, 0xFC, 0x0F, 0x10, 0x10, 0x11, 0x12, 0x13, 0x12, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 64
    0x00, 0xF0, 0xFE, 0xFE, 0xF8, 0x00, 0x1C, 0x1F, 0x06, 0x06, 0x1F, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 65
    0xFE, 0xFE, 0xC6, 0xC6, 0xFE, 0x3C, 0x1F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 66
    0xFC, 0xFE, 0x06, 0x06, 0x1E, 0x1C, 0x0F, 0x1F, 0x18, 0x18, 0x1E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 67
    0xFE, 0xFE, 0x06, 0x06, 0xFE, 0xFC, 0x1F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 68
    0xFE, 0xFE, 0xC6, 0xC6, 0x1F, 0x1F, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, // 69
    0xFE, 0xFE, 0xC6, 0xC6, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 70
    0xFC, 0xFE, 0x06, 0xC6, 0xDE, 0xDC, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 71
    0xFE, 0xFE, 0xC0, 0xC0, 0xFE, 0xFE, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 72
    0xFE, 0xFE, 0x1F, 0x1F, 0x00, 0x00, // 73
    0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 74
    0xFE, 0xFE, 0xE0, 0xBC, 0x0E, 0x02, 0x1F, 0x1F, 0x01, 0x0F, 0x1E, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 75
    0xFE, 0xFE, 0x00, 0x00, 0x1F, 0x1F, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, // 76
    0xFE, 0xFE, 0xF0, 0x00, 0xF0, 0xFE, 0xFE, 0x1F, 0x1F, 0x00, 0x07, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 77
    0xFE, 0xFE, 0x78, 0xC0, 0xFE, 0xFE, 0x1F, 0x1F, 0x00, 0x07, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 78
    0xFC, 0xFE, 0x06, 0x06, 0xFE, 0xFC, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 79
    0xFE, 0xFE, 0x86, 0x86, 0xFE, 0xFC, 0x1F, 0x1F, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0xFC, 0xFE, 0x06, 0x06, 0xFE, 0xFC, 0x00, 0x0F, 0x1F, 0x18, 0x1B, 0x1F, 0x1F, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 81
    0xFE, 0xFE, 0x06, 0xC6, 0xFE, 0x7C, 0x1F, 0x1F, 0x00, 0x07, 0x1F, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 82
    0x1C, 0x3E, 0x66, 0xC6, 0x9E, 0x1C, 0x0C, 0x1C, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 83
    0x06, 0x06, 0xFE, 0xFE, 0x06, 0x06, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 84
    0xFE, 0xFE, 0x00, 0x00, 0xFE, 0xFE, 0x0F, 0x1F, 0x18, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 85
    0x0E, 0xFE, 0x80, 0x80, 0xFE, 0x0E, 0x00, 0x03, 0x1F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 86
    0x1E, 0xFE, 0x80, 0x80, 0xFE, 0xFE, 0x80, 0x80, 0xFE, 0x1E, 0x00, 0x01, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 87
    0x02, 0x1E, 0xFC, 0xE0, 0xFC, 0x1E, 0x02, 0x10, 0x1E, 0x0F, 0x01, 0x0F, 0x1E, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 88
    0x06, 0x7E, 0xF0, 0xF0, 0x7E, 0x06, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89
    0x06, 0x06, 0xC6, 0xF6, 0x3E, 0x06, 0x18, 0x1F, 0x1B, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 90
    0xFE, 0xFE, 0x06, 0x06, 0x7F, 0x7F, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, // 91
    0x06, 0x7E, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x07, 0x1F, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, // 92
    0x06, 0x06, 0xFE, 0xFE, 0x60, 0x60, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, // 93
    0x10, 0x1C, 0x06, 0x1C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 95
    0x08, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 96
    0x40, 0x60, 0x60, 0xE0, 0xC0, 0x0E, 0x1F, 0x19, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, // 97
    0xFE, 0xFE, 0x60, 0xE0, 0xC0, 0x1F, 0x1F, 0x18, 0x1F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, // 98
    0xC0, 0xE0, 0x60, 0xE0, 0xC0, 0x0F, 0x1F, 0x18, 0x1C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, // 99
    0xC0, 0xE0, 0x60, 0xFE, 0xFE, 0x0F, 0x1F, 0x18, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, // 100
    0xC0, 0xE0, 0x60, 0xE0, 0xC0, 0x0F, 0x1F, 0x19, 0x1D, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, // 101
    0xFC, 0xFE, 0x66, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, // 102
    0xC0, 0xE0, 0x60, 0xE0, 0xE0, 0xCF, 0xDF, 0x98, 0xFF, 0xFF, 0x00, 0x80, 0x80, 0x80, 0x00, // 103
    0xFE, 0xFE, 0x40, 0xE0, 0xC0, 0x1F, 0x1F, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, // 104
    0xEC, 0xEC, 0x1F, 0x1F, 0x00, 0x00, // 105
    0xEC, 0xEC, 0xFF, 0xFF, 0x80, 0x00, // 106
    0xFE, 0xFE, 0x80, 0xE0, 0x20, 0x1F, 0x1F, 0x07, 0x1C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // 107
    0xFE, 0xFE, 0x1F, 0x1F, 0x00, 0x00, // 108
    0xE0, 0xE0, 0x40, 0xE0, 0xC0, 0x60, 0xE0, 0xC0, 0x1F, 0x1F, 0x00, 0x1F, 0x1F, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 109
    0xE0, 0xE0, 0x40, 0xE0, 0xE0, 0x1F, 0x1F, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, // 110
    0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x1F, 0x3F, 0x30, 0x3F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, // 111
    0xE0, 0xE0, 0x60, 0xE0, 0xC0, 0xFF, 0xFF, 0x18, 0x1F, 0x0F, 0x80, 0x80, 0x00, 0x00, 0x00, // 112
    0xC0, 0xE0, 0x60, 0xE0, 0xE0, 0x0F, 0x1F, 0x18, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x80, 0x80, // 113
    0xE0, 0xE0, 0x60, 0xE0, 0xC0, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 114
    0xC0, 0xE0, 0x60, 0xE0, 0xC0, 0x0D, 0x1D, 0x1B, 0x1E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, // 115
    0xF8, 0xF8, 0x60, 0x0F, 0x1F, 0x18, 0x00, 0x00, 0x00, // 116
    0xE0, 0xE0, 0x00, 0xE0, 0xE0, 0x0F, 0x1F, 0x18, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, // 117
    0x60, 0xE0, 0x00, 0x00, 0xE0, 0x60, 0x00, 0x07, 0x1F, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 118
    0x60, 0xE0, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x00, 0xE0, 0x60, 0x00, 0x03, 0x1F, 0x1F, 0x03, 0x03, 0x1F, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 119
    0x20, 0xE0, 0xC0, 0xC0, 0xE0, 0x20, 0x10, 0x1C, 0x0F, 0x0F, 0x1C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 120
    0x60, 0xE0, 0x00, 0x00, 0xE0, 0x60, 0x00, 0x87, 0xFF, 0x7F, 0x07, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, // 121
    0x60, 0x60, 0x60, 0xE0, 0x60, 0x18, 0x1E, 0x1B, 0x19, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, // 122
    0x00, 0x80, 0xFC, 0xFE, 0x06, 0x06, 0x01, 0x03, 0xFE, 0xFE, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, // 123
    0xFE, 0xFE, 0xFF, 0xFF, 0x00, 0x00, // 124
    0x06, 0x06, 0xFE, 0xFC, 0x80, 0x00, 0x80, 0x80, 0xFE, 0xFE, 0x03, 0x01, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, // 125
    0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFF, 0x01, 0x01, 0x01, 0x01, 0xFF, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 127
    
};

#endif
