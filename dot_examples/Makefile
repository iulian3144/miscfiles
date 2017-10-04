SOURCES     = $(wildcard *.dot)
IMAGES      = $(SOURCES:.dot=.png)

all: $(IMAGES)
	@echo "Done"

%.png: %.dot
	@echo  "$< -> $@"
	dot -Tpng $< -o $@

clean:
	rm -rf *.png
