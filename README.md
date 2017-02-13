Description
==============
A demo of some of the features of a HD44780 equivalent LCD controller.

How to use
=============
I used an old Arduino Duemilanov, but you can probably use any ATMEGA328P board
provided you account for the pin mappings. Here `Dx` corresponds to the arduino
digital I/O pins and `PDx` corresponds to the `PORTDx` pins on the
microcontroller itself.

| LCD Pin | Description       | Other Pin         |
|---------|-------------------|-------------------|
|      16 | B. Light (-)      | GND               |
|      15 | B. Light (+)      | VCC + 1k RES      |
|   14-11 | Bit 7-4           | D7-D4, PD7-PD4    |
|    7-10 | Bit 3-0           | GND               |
|       6 | CLK (-\_)         | D3 / PD3          |
|       5 | R/W               | GND               |
|       4 | RS                | D2 / PD2          |
|       3 | VO (Contrast ...) | 10k VAR-RES + VSS |
|       2 | VCC               | VCC               |
|       1 | GND               | GND               |

Show me
=========
![Alt Text](https://github.com/badly-drawn-wizards/avr-lcd-demo/raw/master/assets/demo.gif)
