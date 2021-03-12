hex:
	avr-gcc -Os -DF_CPU=16000000 -mmcu=atmega328p -c color_detector.c
	avr-gcc -DF_CPU=16000000 -mmcu=atmega328p -o color_detector.elf color_detector.o -L. -llcd
	avr-objcopy -O ihex color_detector.elf color_detector.hex
	rm color_detector.o
	rm color_detector.elf

flash:
	avrdude -c arduino -p m328p -P /dev/ttyACM0 -U flash:w:color_detector.hex

clear:
	rm color_detector.hex