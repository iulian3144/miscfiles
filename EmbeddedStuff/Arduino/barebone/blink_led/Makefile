# $ avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
# $ avr-gcc -mmcu=atmega328p led.o -o led
# $ avr-objcopy -O ihex -R .eeprom led led.hex
# $ avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:led.hex

GCC         = avr-gcc
OBJ_COPY    = avr-objcopy
FLAGS       = -Os -DF_CPU=16000000UL -mmcu=atmega328p -IsymTbl
SERIAL_PORT = /dev/ttyACM?
SOURCES     = $(wildcard *.c)
OBJECTS     = $(SOURCES:.c=.o)
HEX_TARGET  = main.hex
TARGET      = main.exe
SYM_TBL     = symTbl/symTbl.c
SYM_OBJ     = $(SYM_TBL:.c=.o)
DIR_PATH    = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SYM_CREATE  = $(realpath $(DIR_PATH)/../../.. )/util/makeSymTbl.tcl

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(GCC) -mmcu=atmega328p $^ -o $@

$(HEX_TARGET): $(TARGET)
	$(GCC) $(FLAGS) $(TARGET) $(SYM_OBJ) -o $(SYM_OBJ)
	$(OBJ_COPY) -O ihex -R .eeprom $^ $(HEX_TARGET)

symtbl: $(TARGET)
	$(SYM_CREATE) "" $(TARGET) $(SYM_TBL)
	$(GCC) $(FLAGS) -c $(SYM_TBL) -o $(SYM_OBJ)

%.o: %.c %.h
	$(GCC) $(FLAGS) -c $<

%.o: %.c
	$(GCC) $(FLAGS) -c $<

info:
	@echo "SYM_TBL   : $(SYM_TBL)"
	@echo "DIR_PATH  : $(DIR_PATH)"
	@echo "SYM_CREATE: $(SYM_CREATE)"
	@echo "SOURCES   : $(SOURCES)"
	@echo "OBJECTS   : $(OBJECTS)"

clean:
	rm -f *.o $(TARGET) $(HEX_TARGET) $(SYM_TBL) $(SYM_OBJ)

upload:
	@echo "Uploading..."
	@echo "       File: $(HEX_TARGET)"
	@echo "SERIAL_PORT: $(SERIAL_PORT)"
	avrdude -F -V -c arduino -p ATMEGA328P -P $(SERIAL_PORT) -b 115200 -U flash:w:$(HEX_TARGET)

