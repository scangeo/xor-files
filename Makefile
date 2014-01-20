SHELL = /bin/sh
ARCH = $(shell arch)
PREFIX=/usr/local

CC = gcc
EXECS = xor
LARGE_FILE_FLAGS = -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64


ifeq ($(ARCH),i686)
	CFLAGS = -m32 -lm -O2 -I ./include -D_REENTRANT $(LARGE_FILE_FLAGS)
	LDFLAGS = -m32
else
	CFLAGS = -lm -O2 -I ./include -D_REENTRANT $(LARGE_FILE_FLAGS)
	LDFLAGS =
endif

all: $(EXECS)

clean:
	/bin/rm -f *.o *~ ../$(EXECS)*
	
sg_mam_text: xor.o $(LIBFILES)
	$(CC) -o ../$@ $(LDFLAGS) $^

	




