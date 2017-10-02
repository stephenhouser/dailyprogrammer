# Makefile - generic makefile template for /r/dailyprogrammer
#
# 2017-02-10/Stephen Houser
#
TARGET = nln
HEADERS = 
SOURCES = $(TARGET).cpp

# Include all .c files in current directory
#OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp)) \
# 		   $(patsubst %.c, %.o, $(wildcard *.c))
#HEADERS = $(wildcard *.h)
# Include only .c files from $(SOURCES)
C_SOURCES = $(filter %.c,$(SOURCES))
CXX_SOURCES = $(filter %.cpp,$(SOURCES))
OBJECTS = $(C_SOURCES:.c=.o) $(CXX_SOURCES:.cpp=.o)

CC = gcc
CFLAGS = -g -Wall 
LFLAGS = 

CXX = g++
CXXFLAGS = -std=c++1z -g -Wall
LXXFLAGS = 

.PHONY: default all clean distclean

default: $(TARGET)
all: default

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
