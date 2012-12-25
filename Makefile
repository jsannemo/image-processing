all: blur channel

blur: blur.o image.o
	cc -o blur image.o blur.o -lpng

channel: channel.o
	cc -o channel image.o channel.o -lpng

channel.o:
	cc -c channel.c -std=gnu99

blur.o:
	cc -c blur.c -std=gnu99

image.o:
	cc -c image.h image.c -std=gnu99

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.gch
	rm -f blur
	rm -f channel
