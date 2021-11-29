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
  String outputStr = "" + String(note);
  char output[sizeof(outputStr)];
  outputStr.toCharArray(output, sizeof(output));

  u8g2.clearBuffer();
  print_menuline("MIDI Note On");
  u8g2.setFont(u8g2_font_logisoso38_tf);
  u8g2.setCursor(ALIGN_CENTER(output), 42);
  u8g2.print(output);

//   u8g2.setFont(u8g2_font_helvR08_tr);
//   u8g2.drawButtonUTF8(62, 20, U8G2_BTN_INV|U8G2_BTN_BW2, 0,  2,  2, output);

  // u8g2.setFont(u8g2_font_unifont_t_76);
  // u8g2.drawGlyph(5, 20, 0x266a);

  // u8g2.setFont(u8g2_font_streamline_all_t);
  // u8g2.drawGlyph(5, 20, 0x01b0);

  // 'Free vectors icons and illustrations from Streamline'
  // The link must be visible and readable as a hyperlink text and link to https://streamlinehq.com


  u8g2.sendBuffer();
}