# Define the compiler options
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast

ALLTARGETS = hello.ii hello.s ltest encode decode liblab1.a liblab1.so liblab1.so.1 liblab1.so.1.0 ltest_s encode_s decode_s

# Define what to do when make is executed without arguments.
all: $(ALLTARGETS)

# The following rule means "if ltest is older than ltest.o or list.o,
# then link ltest".
hello.ii: hello.cc
	g++ -E -o hello.ii hello.cc

hello.s: hello.cc
	g++ -S -o hello.s hello.cc

ltest: ltest.o liblab1.a
	g++ -o ltest ltest.o -L. -llab1

encode: encode.o liblab1.a
	g++ -o encode encode.o -L. -llab1

decode: decode.o liblab1.a
	g++ -o decode decode.o -L. -llab1

ltest_s: ltest_PIC.o liblab1.so.1.0
	g++ -o ltest_s ltest_PIC.o -L. -llab1

encode_s: encode_PIC.o liblab1.so.1.0
	g++ -o encode_s encode_PIC.o -L. -llab1

decode_s: decode_PIC.o liblab1.so.1.0
	g++ -o decode_s decode_PIC.o -L. -llab1

liblab1.so.1.0: list_PIC.o coding_PIC.o
	g++ -shared -Wl,-soname,liblab1.so.1 -o liblab1.so.1.0 list_PIC.o coding_PIC.o

liblab1.so.1: liblab1.so.1.0
	ln -s liblab1.so.1.0 liblab1.so.1

liblab1.so: liblab1.so.1
	ln -s liblab1.so.1 liblab1.so

liblab1.a: coding.o list.o
	ar crv liblab1.a coding.o list.o

# Define the rules for the object files.
ltest.o: ltest.cc list.h debug.h
	g++ -c $(CXXFLAGS) ltest.cc
list.o: list.cc list.h
	g++ -c $(CXXFLAGS) list.cc

encode.o: encode.cc coding.h
	g++ -c $(CXXFLAGS) encode.cc
coding.o: coding.cc coding.h
	g++ -c $(CXXFLAGS) coding.cc
decode.o: decode.cc coding.h
	g++ -c $(CXXFLAGS) decode.cc

coding_PIC.o: coding.cc coding.h
	g++ -fPIC -c $(CXXFLAGS) -o coding_PIC.o coding.cc

list_PIC.o: list.cc list.h
	g++ -fPIC -c $(CXXFLAGS) -o list_PIC.o list.cc

ltest_PIC.o: ltest.cc list.h debug.h
	g++ -fPIC -c $(CXXFLAGS) -o ltest_PIC.o ltest.cc

encode_PIC.o: coding.h encode.cc
	g++ -fPIC -c $(CXXFLAGS) -o encode_PIC.o encode.cc

decode_PIC.o: coding.h decode.cc
	g++ -fPIC -c $(CXXFLAGS) -o decode_PIC.o decode.cc

clean:
	rm *.o

cleaner:
	rm *.o $(ALLTARGETS)