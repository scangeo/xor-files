SHELL = /bin/sh
ARCH = $(shell arch)
PROGRAM = $(shell pwd)
CC = gcc
EXECS = xor-files
LARGE_FILE_FLAGS = -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64


ifeq ($(ARCH),i686)
	CFLAGS = -m32 -lm -O2 -I ./include -D_REENTRANT $(LARGE_FILE_FLAGS)
	LDFLAGS = -m32
else
	CFLAGS = -lm -O2 -I ./include -D_REENTRANT $(LARGE_FILE_FLAGS)
	LDFLAGS =
endif

all:
	echo ""

install:
	$(CC) $(PROGRAM)/debian/source/xor-files.c -o xor-files $(CFLAGS) $(LDFLAGS) $^
	@mkdir -p $(DESTDIR)/usr/bin
	@cp xor-files $(DESTDIR)/usr/bin
	
uninstall:
	@rm -rf $(DESTDIR)/usr/bin/xor-files
	
reinstall: uninstall install

clean:
	/bin/rm -f *.o *~ ./$(EXECS)*
	

	

	




