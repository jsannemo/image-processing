CFLAGS := -Wall -g -std=gnu99
LDLIBS := -lpng -lm

all: blur channel resize

blur: blur_tool.o blur.o image.o

channel: channel_tool.o image.o

resize: resize_tool.o resize.o image.o

fx: fx_tool.o fx.o image.o

.PHONY: clean
clean:
	rm -f blur channel resize
	rm -f *.o
