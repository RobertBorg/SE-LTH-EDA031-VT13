#
# Makefile for CPP-2005
#

# Compiler and linker
CXX     = g++
CC      = g++

# Preprocessor, compiler and linker options
#CPPFLAGS  = -DNDEBUG
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast
#CXXFLAGS += -ggdb
#LDFLAGS = -ggdb

# Sources and object files
SRC	= $(wildcard *.cc)
OBJ	= $(SRC:.cc=.o)

# Executables
PROGS	= shapetest shapearraytest inputtest

all: $(PROGS)

shapetest: shapetest.o
shapearraytest: shapearraytest.o
inputtest: inputtest.o rangereader.o

clean:
	rm -f *.o

cleaner: clean
	rm -f $(PROGS) *.d

%.d: %.cc
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(SRC:.cc=.d)
