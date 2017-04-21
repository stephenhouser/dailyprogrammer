# Makefile - generic makefile template for /r/dailyprogrammer
#
# 2017-02-10/Stephen Houser
#
TARGET = ipv4-subnet
HEADERS = 
SOURCES = $(TARGET).c

# Include my C library
LIB_DIR = ../../lib
INC_DIR = ../../lib
LIBS = -lhouser

CC = gcc
CFLAGS = -g -Wall -I$(INC_DIR)
LFLAGS = -L$(LIB_DIR) $(LIBS)

EXPECT = expect

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
	$(CC) $(LFLAGS) $^ $(LIBS) -o $@

test: $(TARGET)
	./$(TARGET) sample.story

clean:
	-rm -f *.o
	-rm -f core a.out

distclean: clean
	-rm -f $(TARGET)
