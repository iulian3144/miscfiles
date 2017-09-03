# $ avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
# $ avr-gcc -mmcu=atmega328p led.o -o led
# $ avr-objcopy -O ihex -R .eeprom led led.hex
# $ avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:led.hex

GCC         = avr-gcc
OBJ_COPY    = avr-objcopy
FLAGS       = -Os -DF_CPU=16000000UL -mmcu=atmega328p
SERIAL_PORT = /dev/ttyACM?
SOURCES     = $(wildcard *.c)
OBJECTS     = $(SOURCES:.c=.o)
HEX_TARGET  = main.hex
TARGET      = main.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(GCC) -mmcu=atmega328p $^ -o $@
	$(OBJ_COPY) -O ihex -R .eeprom $@ $(HEX_TARGET)

%.o: %.c %.h
	$(GCC) $(FLAGS) -c $<

%.o: %.c
	$(GCC) $(FLAGS) -c $<

clean:
	rm -f *.o $(TARGET) $(HEX_TARGET)

upload:
	@echo "Uploading..."
	@echo "       File: blink_led.hex"
	@echo "SERIAL_PORT: $(SERIAL_PORT)"
	avrdude -F -V -c arduino -p ATMEGA328P -P $(SERIAL_PORT) -b 115200 -U flash:w:$(HEX_TARGET)

