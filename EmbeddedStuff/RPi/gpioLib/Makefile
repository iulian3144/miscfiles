

GCC         = gcc
SOURCES     = $(wildcard *.c)
OBJECTS     = $(SOURCES:.c=.o)
TARGET      = main.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(GCC) $^ -o $@

%.o: %.c %.h
	$(GCC) -c $<

%.o: %.c
	$(GCC) -c $<

info:
	@echo "SOURCES   : $(SOURCES)"
	@echo "OBJECTS   : $(OBJECTS)"

clean:
	rm -f *.o $(TARGET)

