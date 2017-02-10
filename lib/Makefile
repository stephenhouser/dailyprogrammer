# Makefile - generic makefile template for /r/dailyprogrammer
#
# 2017-02-10/Stephen Houser
#
TARGET = libhouser.a
HEADERS = stack.h queue.h read_line.h
SOURCES = stack.c queue.c read_line.c

CC = gcc
CFLAGS = -g -Wall
LFLAGS = 

AR = ar
AFLAGS = -rcs

.PHONY: default all clean distclean

default: $(TARGET)
all: default

# Include all .c files in current directory
#OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
#HEADERS = $(wildcard *.h)
# Include only .c files from $(SOURCES)
OBJECTS= $(patsubst %.c, %.o, $(SOURCES))

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ 

# https://www.gnu.org/software/make/manual/html_node/Special-Targets.html
# if make is killed or interrupted during the execution of their 
# recipes, the target is not deleted.
.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(AR) $(AFLAGS) $@ $^

clean:
	-rm -f *.o
	#-rm -f $(TARGET)	
	-rm -f core a.out

distclean: clean
	-rm -f $(TARGET)	
