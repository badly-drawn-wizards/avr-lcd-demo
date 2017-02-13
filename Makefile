$(shell mkdir -p dist)
DEVICE = atmega328p
CLOCK = 16000000
PROGRAMMER = arduino
PORT = /dev/ttyUSB0
BAUD = 57600

C_FILES = main.c lcd.c
O_FILES = $(patsubst %.c,dist/%.o,$(C_FILES))
HEX_FILE = dist/main.hex
INCLUDES = -Isrc

CC = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) $(INCLUDES)
all: clean build upload

dist/%.hex: dist/%.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

dist/main.elf: $(O_FILES)
	$(CC) -o $@ $^
	avr-size --format=avr --mcu=$(DEVICE) $@

dist/%.o: src/%.c
	$(CC) -o $@ -c $<

clean:
	-rm dist/*

build: $(HEX_FILE)

upload: $(HEX_FILE)
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX_FILE):i
