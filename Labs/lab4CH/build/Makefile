#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -Wall -W -ansi -pedantic-errors -std=c++11
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast
CC        = $(CXX)

ALLTARGETS = simplebitsettest bitsettest1 bitsettest2

# insert this line somewhere at the top of the file
DEBUG = false
# insert the following lines after the definitions of CXXFLAGS and LDFLAGS
ifeq ($(DEBUG), true)
	CXXFLAGS += -ggdb
	LDFLAGS += -ggdb
else
	CXXFLAGS += -O2
endif

VPATH= ../bitset/

sources = $(wildcard *.cc) $(notdir $(foreach dir,$(VPATH),$(wildcard $(dir)/*.cc)))

.PHONY: install uninstall all clean cleaner build

all: $(ALLTARGETS)

%.dd: %.cc
	@set -e; rm -f $@; \
	$(CC) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


# Linking:
simplebitsettest: simplebitsettest.o simplebitset.o

bitsettest1: bitsettest1.o bitreference.o bitset.o

bitsettest2: bitsettest2.o bitreference.o bitset.o bitsetiterator.o

# Dependencies, the implicit rule .cc => .o is used
include $(sources:.cc=.dd)

install: all
	mkdir -p lib bin
	cp $(ALLTARGETS) ./bin

uninstall:
	cd ./bin; rm $(ALLTARGETS)
 
clean:
	$(RM) *.o *.dd*

cleaner:
	$(RM) *.dd* *.o $(ALLTARGETS)
