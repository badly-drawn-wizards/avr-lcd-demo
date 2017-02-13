#include <lcd.h>
#include <dickbutt_chars.h>

#include <util/delay.h>

#include <stdint.h>

void demo_init() {
  lcd_set_pins();
  lcd_clear_bit_mode();
  lcd_set_function(LCD_FOUR_BIT, LCD_TWO_LINE, LCD_5x8);
  lcd_return_home();
  lcd_entry_mode(LCD_ENTRY_INC, LCD_ENTRY_NO_SHIFT);
  lcd_display(LCD_DISPLAY_ON, LCD_CURSOR_OFF, LCD_BLINK_OFF);
  lcd_set_cgram_chars(dickbutt_chars);
  lcd_clear();
}

void cool_stuff() {
  lcd_set_msg("This LCD can do     ", 20, 0, 0);
  lcd_set_msg(" pretty cool stuff. ", 20, 0, 1);
}

void scroll_and_cursors() {
  lcd_set_msg("You can scroll text,", 20, 20, 0);
  for(int i=0; i<16; i++) {
    lcd_shift(LCD_SHIFT_ON, LCD_CURSOR_LEFT);
    _delay_ms(100);
  }
  for(int i=0; i<4; i++) {
    lcd_shift(LCD_SHIFT_ON, LCD_CURSOR_LEFT);
    _delay_ms(200);
  }
  _delay_ms(1000);
  char cursor_text[] = " display a cursor";
  lcd_display(LCD_DISPLAY_ON, LCD_CURSOR_ON, LCD_BLINK_OFF);
  for(uint8_t i=0; i<17; i++) {
    lcd_set_msg(cursor_text+i, 1, 20+i, 1);
    _delay_ms(100);
  }
  lcd_display(LCD_DISPLAY_ON, LCD_CURSOR_ON, LCD_BLINK_ON);
  _delay_ms(1000);
  lcd_display(LCD_DISPLAY_ON, LCD_CURSOR_ON, LCD_BLINK_OFF);
  char space[]=" ";
  for(uint8_t i=0; i<17; i++) {
    lcd_set_msg(space, 1, 36-i, 1);
    _delay_ms(50);
  }
  for(uint8_t i=0; i<20; i++) {
    lcd_set_msg(space, 1, 39-i, 0);
    _delay_ms(30);
  }
  lcd_display(LCD_DISPLAY_ON, LCD_CURSOR_OFF, LCD_BLINK_OFF);
  _delay_ms(200);
  lcd_clear();
}

void build_up() {
  char cg_text[][20] = {
    "                    ",
    "You                 ",

    "                    ",
    "  can               ",

    "                    ",
    "    even            ",

    "                    ",
    "     have           ",

    "       up           ",
    "                    ",

    "       up to        ",
    "                    ",

    "       up to        ",
    "       EIGHT        ",

    "     CUSTOMIZED     ",
    "                    ",

    "     CUSTOMIZED     ",
    "     CHARACTERS     ",

    "        LIKE        ",
    "                    ",

    "        LIKE        ",
    "        THIS        ",
  };

  for(uint8_t i=0; i<22; i++) {
    lcd_set_msg(cg_text[i], 20, 0, i&1);
    if(i&1) {
      _delay_ms(250);
    }
  }
  lcd_clear();
  _delay_ms(700);
}

char img[2][5] = {{0,1,2,3},{4,5,6,7}};
void dickbutt() {
  lcd_set_msg(img[0], 4, 8, 0);
  lcd_set_msg(img[1], 4, 8, 1);
  _delay_ms(1000);
  lcd_set_msg("DICK", 4, 3, 0);
  lcd_set_msg("BUTT", 4, 13, 1);
}

int main() {
  while(1) {
    demo_init();
    _delay_ms(1000);

    cool_stuff();
    _delay_ms(2000);

    scroll_and_cursors();
    _delay_ms(1000);

    build_up();
    _delay_ms(700);

    dickbutt();
    _delay_ms(2000);
  }
}
