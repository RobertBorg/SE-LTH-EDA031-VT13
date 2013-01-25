#
# Makefile for CPP-2005
#

# Compiler and linker
CXX     = g++
CC      = g++

# Preprocessor, compiler and linker options
#CPPFLAGS  = -DNDEBUG
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast -std=c++11
#CXXFLAGS += -ggdb
#LDFLAGS = -ggdb

# Sources and object files
SRC	= $(wildcard *.cc)
OBJ	= $(SRC:.cc=.o)

# Executables
PROGS	= memtest countobj fibtest improvedfibtest

all: $(PROGS)

memtest: memtest.o
countobj: countobj.o
fibtest: fibtest.o fibonacci.o
improvedfibtest: improvedfibtest.o improvedfibonacci.o

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
