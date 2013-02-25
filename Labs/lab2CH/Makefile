#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -Wall -W -ansi -pedantic-errors -m64
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast
CC        = g++
LDFLAGS += 

# insert this line somewhere at the top of the file
DEBUG = false
# insert the following lines after the definitions of CXXFLAGS and LDFLAGS
ifeq ($(DEBUG), true)
	CXXFLAGS += -ggdb
	LDFLAGS += -ggdb
else
	CXXFLAGS += -O2
endif

ALLTARGETS = ltest reciprocal vgtest graph_test

sources = $(wildcard *.cc)

.PHONY: install uninstall all clean cleaner build graph

all: $(ALLTARGETS)

%.dd: %.cc
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


# Linking:
ltest: ltest.o list.o

graph_test: graph_test.o vertex.o vertexlist.o

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
