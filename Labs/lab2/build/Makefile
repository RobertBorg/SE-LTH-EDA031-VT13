#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast
CC        = g++

ALLTARGETS = ltest encode decode hello

VPATH= ../src/

sources = $(wildcard *.cc) $(notdir $(foreach dir,$(VPATH),$(wildcard $(dir)/*.cc)))

.PHONY: install uninstall all clean cleaner build

all: $(ALLTARGETS)

%.dd: %.cc
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


# Linking:
ltest: ltest.o list.o

encode: encode.o coding.o

decode: decode.o coding.o


# Dependencies, the implicit rule .cc => .o is used
include $(sources:.cc=.dd)

install: all
	mkdir -p lib bin
	cp $(ALLTARGETS) ./bin

uninstall:
	cd ./bin; rm $(ALLTARGETS)
 
clean:
	$(RM) *.o *.dd

cleaner:
	$(RM) *.dd *.o $(ALLTARGETS)
