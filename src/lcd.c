#include<lcd.h>

void lcd_set_pins() {
  DDRD = 0b11111111;
  PORTD = 0;
}


inline static void lcd_send_nibble(lcd_reg_select rs, uint8_t byte) {
  SET_MASK(PORTD, 0b00000100, rs << PORTD2);
  _delay_us(1);
  SET_MASK(PORTD, 1 << PORTD3, 0xFF);
  _delay_us(1);
  SET_MASK(PORTD, 0b11110000, ((byte & 0b1111) << PORT4));
  _delay_us(1);
  SET_MASK(PORTD, 1 << PORTD3, 0);
  _delay_us(1);
}

inline static void lcd_send(lcd_reg_select rs, uint8_t byte) {
  lcd_send_nibble(rs, byte >> 4);
  _delay_us(50);
  lcd_send_nibble(rs, byte);
  _delay_us(50);
};

void lcd_clear_bit_mode() {
  for(int i=0; i<3; i++) {
    lcd_send_nibble(LCD_CMD, 0b0011);
    _delay_us(50);
  }
  lcd_send_nibble(LCD_CMD, 0b0010);
  _delay_us(50);
}

void lcd_clear() {
  lcd_send(LCD_CMD, 0b00000001);
  _delay_ms(2);
}

void lcd_return_home() {
  lcd_send(LCD_CMD, 0b00000010);
  _delay_ms(2);
}



void lcd_entry_mode(lcd_entry_direction dir, lcd_entry_shift shift) {
  lcd_send(LCD_CMD, 0b100 | dir << 1 | shift << 0);
  _delay_us(50);
}

void lcd_display(lcd_display_state display, lcd_cursor_state cursor, lcd_blink_state blink) {
  lcd_send(LCD_CMD, 0b1000 | display << 2 | cursor << 1 | blink << 0);
  _delay_us(50);
}

void lcd_shift(lcd_shift_state shift, lcd_cursor_direction dir) {
  lcd_send(LCD_CMD, 0b10000 | shift << 3 | dir << 2);
  _delay_us(50);
}

void lcd_set_function(lcd_bit_mode mode, lcd_line_mode line, lcd_font font) {
  lcd_send(LCD_CMD, 0b00100000 | mode << 4 | line << 3 | font << 2);
  _delay_us(50);
}

void lcd_set_ddram_address(uint8_t addr) {
  lcd_send(LCD_CMD, 0b10000000 | (addr & 0b01111111));
  _delay_us(50);
}

void lcd_set_cgram_address(uint8_t addr) {
  lcd_send(LCD_CMD, 0b01000000 | (addr & 0b00111111));
  _delay_us(50);
}

void lcd_set_ram(uint8_t data) {
  lcd_send(LCD_DATA, data);
  _delay_us(50);
}

void lcd_set_ddram(uint8_t addr, uint8_t data) {
  lcd_set_ddram_address(addr);
  lcd_set_ram(data);
}

void lcd_set_cgram(uint8_t addr, uint8_t data) {
  lcd_set_cgram_address(addr);
  lcd_set_ram(data);
}

void lcd_set_cgram_char(uint8_t c, uint8_t rows[8]) {
  for(uint8_t i=0; i<8; i++) {
    lcd_set_cgram(c * 8 + i, rows[i]);
  }
}

void lcd_set_cgram_chars(uint8_t data[8][8]) {
  for(int c=0; c<8; c++) {
    lcd_set_cgram_char(c, data[c]);
  }
}

uint8_t lcd_get_addr(uint8_t col, uint8_t row) {
  return col + 0x40 * row;
}

void lcd_set_char(uint8_t c, uint8_t col, uint8_t row) {
  lcd_set_ddram(lcd_get_addr(col, row), c);
}

void lcd_set_msg(char* msg, uint8_t len, uint8_t col, uint8_t row) {
  for(uint8_t i=0; i<len; i++) {
    lcd_set_char((uint8_t)msg[i], col+i, row);
  }
}
