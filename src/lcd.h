#ifndef _LCD_H_
#define _LCD_H_

#include<avr/io.h>
#include <util/delay.h>

#define SET_MASK(VAR, MSK, VAL) {VAR |= ((VAL) & (MSK)); VAR &= ((VAL) | ~(MSK));}

void lcd_set_pins();

typedef enum {LCD_CMD, LCD_DATA} lcd_reg_select;

void lcd_clear_bit_mode();

void lcd_clear();

void lcd_return_home();

typedef enum {LCD_ENTRY_DEC, LCD_ENTRY_INC} lcd_entry_direction;
typedef enum {LCD_ENTRY_NO_SHIFT, LCD_ENTRY_SHIFT} lcd_entry_shift;
void lcd_entry_mode(lcd_entry_direction dir, lcd_entry_shift shift);

typedef enum {LCD_DISPLAY_OFF, LCD_DISPLAY_ON} lcd_display_state;
typedef enum {LCD_CURSOR_OFF, LCD_CURSOR_ON} lcd_cursor_state;
typedef enum {LCD_BLINK_OFF, LCD_BLINK_ON} lcd_blink_state;
void lcd_display(lcd_display_state display, lcd_cursor_state cursor, lcd_blink_state blink);

typedef enum {LCD_SHIFT_OFF, LCD_SHIFT_ON} lcd_shift_state;
typedef enum {LCD_CURSOR_LEFT, LCD_CURSOR_RIGHT} lcd_cursor_direction;
void lcd_shift(lcd_shift_state shift, lcd_cursor_direction dir);

typedef enum {LCD_FOUR_BIT, LCD_EIGHT_BIT} lcd_bit_mode;
typedef enum {LCD_ONE_LINE, LCD_TWO_LINE} lcd_line_mode;
typedef enum {LCD_5x8, LCD_5x11} lcd_font;
void lcd_set_function(lcd_bit_mode mode, lcd_line_mode line, lcd_font font);

void lcd_set_cgram_chars(uint8_t data[8][8]);
void lcd_set_msg(char* msg, uint8_t len, uint8_t col, uint8_t row);

#endif
