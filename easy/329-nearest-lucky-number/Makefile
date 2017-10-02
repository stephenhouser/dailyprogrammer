# Makefile - generic makefile template for /r/dailyprogrammer
#
# 2017-02-10/Stephen Houser
#
TARGET = nln
HEADERS = 
SOURCES = $(TARGET).cpp

CC = gcc
CFLAGS = -g -Wall 
LFLAGS = $(LIBS)

CXX = g++
CXXFLAGS = -std=c++1z -g -Wall
LXXFLAGS = -lstdc++

EXPECT = expect

.PHONY: default all clean distclean

default: $(TARGET)
all: default

# Include all .c files in current directory
#OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
#HEADERS = $(wildcard *.h)
# Include only .c files from $(SOURCES)
OBJECTS= $(patsubst %.cpp, %.o, $(SOURCES)) 

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ 

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

# https://www.gnu.org/software/make/manual/html_node/Special-Targets.html
# if make is killed or interrupted during the execution of their 
# recipes, the target is not deleted.
.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) $^ $(LIBS) -o $@

test: $(TARGET)
	@./$(TARGET) 103
	@./$(TARGET) 225
	@./$(TARGET) 997
	@./$(TARGET) -1

clean:
	-rm -f *.o
	-rm -f core a.out

distclean: clean
	-rm -f $(TARGET)
