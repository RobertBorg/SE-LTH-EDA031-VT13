#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast

ALLTARGETS = ltest

# Linking:
ltest: ltest.o list.o
	$(CXX) -o $@ $^

# Dependencies, the implicit rule .cc => .o is used
ltest.o: ltest.cc list.h
list.o: list.cc list.h

.PHONY: install uninstall all clean cleaner build

install: all
	mkdir -p lib bin
	cp $(ALLTARGETS) ./bin

uninstall:
	cd ./bin; rm $(ALLTARGETS)
 
all: $(ALLTARGETS)

