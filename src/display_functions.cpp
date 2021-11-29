#include "display_functions.h"
#include "logo.h"

// SSD1306 Controller
// Mode F = Full screen buffer mode
// SW = Software SPI/I2C
// u8g2(orientation, clock, data)
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 3, 2);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, 3, 2);

#define LCDWidth u8g2.getDisplayWidth()
#define ALIGN_CENTER(t) ((LCDWidth - (u8g2.getUTF8Width(t))) / 2)
#define ALIGN_RIGHT(t) (LCDWidth - u8g2.getUTF8Width(t))
#define ALIGN_LEFT 0

void print_splash()
{
  u8g2.clearBuffer();
  print_menuline("Rack-MIDI 2021");
  u8g2.drawXBM(45, 2, gug_logo_width, gug_logo_height, gug_logo_bits);
  u8g2.sendBuffer();
}

void print_menuline(const char *text)
{
  u8g2.setFont(u8g2_font_tenthinguys_tf);
  u8g2.setCursor(ALIGN_CENTER(text), 62);
  u8g2.print(text);
}

void print_status(const char *text)
{
  u8g2.setFont(u8g2_font_bitcasual_t_all);
  u8g2.setCursor(ALIGN_CENTER(text), 32);
  u8g2.print(text);
}

void print_note(int note)
{
  u8g2.clearBuffer();
  print_menuline("MIDI Note On");

  // u8g2.setFont(u8g2_font_logisoso38_tf);
  // u8g2.setCursor(ALIGN_CENTER(output), 42);
  // u8g2.print(output);

  u8g2.setFont(u8g2_font_fub20_tn);
  u8g2.drawButtonUTF8(ALIGN_CENTER(String(note).c_str()), 30, U8G2_BTN_INV|U8G2_BTN_BW2, 0,  2,  2, String(note).c_str());

  // u8g2.setFont(u8g2_font_unifont_t_76);
  // u8g2.drawGlyph(5, 20, 0x266a);

  // u8g2.setFont(u8g2_font_streamline_music_audio_t);
  // u8g2.drawGlyph(5, 20, 0x0031);
  u8g2.sendBuffer();
}

void print_control(byte controller, byte value)
{
  String outputStr = String(controller,DEC) + ":" + String(value,DEC);
  u8g2.clearBuffer();
  print_menuline("MIDI CC");
  
  u8g2.setFont(u8g2_font_fub20_tn);
  // u8g2 erwartet nicht Strings, sondern C-Strings (terminierte char-Arrays)
  // String bietet einen Getter für den intern genutzten C-String an: .c_str()
  // So kann String auch dort genutzt werden, wo char[] gefordert sind.
  u8g2.drawButtonUTF8(64, 30, U8G2_BTN_INV|U8G2_BTN_BW2|U8G2_BTN_HCENTER, 90,  2,  2, outputStr.c_str());

  u8g2.sendBuffer();
}