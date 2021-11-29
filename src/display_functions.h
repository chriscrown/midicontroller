#ifndef DISPLAY_FUNCTIONS_H
#define DISPLAY_FUNCTIONS_H

#include <Arduino.h>
#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

void print_splash();
void print_menuline(const char *text);
void print_status(const char *text);
void print_note(int note);
void print_control(byte controller, byte value);

#endif