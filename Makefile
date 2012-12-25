all: blur channel

blur: blur_tool.o blur.o image.o
	cc -o blur blur.o blur_tool.o image.o -lpng

channel: channel_tool.o
	cc -o channel image.o channel_tool.o -lpng

channel_tool.o:
	cc -c channel_tool.c -std=gnu99

blur_tool.o:
	cc -c blur_tool.c -std=gnu99

blur.o:
	cc -c blur.h blur.c -std=gnu99

image.o:
	cc -c image.h image.c -std=gnu99

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.gch
	rm -f blur
	rm -f channel
