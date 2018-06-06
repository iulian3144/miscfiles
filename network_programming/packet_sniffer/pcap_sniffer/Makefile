#   File: Makefile
# Synopsis:
#   $ make
#   $ make clean
#   $ make help
# Author: Iulian PAUN

GCC     = gcc
FLAGS   =
LIBS    = -lpcap
SRCDIR  = src
OBJDIR  = bin
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.c))
INCLUDE = -Ih
TARGET  = sniffer.exe


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(GCC) $^ -o $@ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if ! [ -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
	$(GCC) $(FLAGS) $(INCLUDE) -o $@ -c $<

help:
	@echo "Sources directory: $(SRCDIR)"
	@echo "Objects directory: $(OBJDIR)"
	@echo "\nSynopsis:"
	@echo "  $$ make"
	@echo "  $$ make clean"
	@echo "  $$ make help"
clean:
	rm -rvf $(OBJDIR)
