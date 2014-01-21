SHELL = /bin/sh
ARCH = $(shell arch)
CC = gcc
EXECS = xor
LARGE_FILE_FLAGS = -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64


ifeq ($(ARCH),i686)
	CFLAGS = -m32 -lm -O2 -I ./include -D_REENTRANT $(LARGE_FILE_FLAGS); export CFLAGS 
	LDFLAGS = -m32
else
	CFLAGS = -lm -O2 -I ./include -D_REENTRANT $(LARGE_FILE_FLAGS); export CFLAGS 
	LDFLAGS =
endif

all:
	echo ""

install:
	@mkdir -p $(DESTDIR)/usr/bin
	@cp xor $(DESTDIR)/usr/bin

uninstall:
	@rm -rf $(DESTDIR)/usr/bin/xor
	
reinstall: uninstall install

clean:
	/bin/rm -f *.o *~ ./$(EXECS)*
	
sg_mam_text: xor.o $(LIBFILES)
	$(CC) -o ./$@ $(LDFLAGS) $^

	




