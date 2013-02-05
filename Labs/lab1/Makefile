# Define the compiler options
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast

ALLTARGETS = ltest encode decode liblab1.a

# Define what to do when make is executed without arguments.
all: $(ALLTARGETS)

# The following rule means "if ltest is older than ltest.o or list.o,
# then link ltest".
ltest: ltest.o liblab1.a
	g++ -o ltest ltest.o -L. -llab1

encode: encode.o liblab1.a
	g++ -o encode encode.o -L. -llab1

decode: decode.o liblab1.a
	g++ -o decode decode.o -L. -llab1

liblab1.a: coding.o list.o
	ar crv liblab1.a coding.o list.o

# Define the rules for the object files.
ltest.o: ltest.cc list.h
	g++ -c $(CXXFLAGS) ltest.cc
list.o: list.cc list.h
	g++ -c $(CXXFLAGS) list.cc

encode.o: coding.h
	g++ -c $(CXXFLAGS) encode.cc
coding.o: coding.h
	g++ -c $(CXXFLAGS) coding.cc
decode.o: coding.h
	g++ -c $(CXXFLAGS) decode.cc

clean:
	rm *.o

cleaner:
	rm *.o $(ALLTARGETS)