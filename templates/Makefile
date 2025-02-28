# Makefile - generic makefile template for /r/dailyprogrammer
#
# Replace TEMPLATE with the name of the target.
#
# 2017-02-10/Stephen Houser
#
TARGET = template
HEADERS = 
SOURCES = $(TARGET).cpp

# Gnu make specific!
ifdef $(SOURCES)
# Include only .c files from $(SOURCES)
C_SOURCES = $(filter %.c,$(SOURCES))
CXX_SOURCES = $(filter %.cpp,$(SOURCES))
OBJECTS = $(C_SOURCES:.c=.o) $(CXX_SOURCES:.cpp=.o)
else
# Include all .c files in current directory
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp)) \
			$(patsubst %.c, %.o, $(wildcard *.c))
endif

# C Preprocessor flags (for c and c++ code)
CPPFLAGS = -g -Wall 

# C specific flags
CC = gcc
CFLAGS = 
LFLAGS = 

# C++ specific flags
CXX = g++
CXXFLAGS = -std=c++1z
LXXFLAGS = 

.PHONY: default all clean distclean

default: $(TARGET)
all: default

# default rule for compiling c code
#%.o: %.c $(HEADERS)
#	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@ 

# default rule for compiling c++ code
#%.o: %.cpp $(HEADERS)
#	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@ 

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
