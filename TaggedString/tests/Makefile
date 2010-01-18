CXX	= `which gcc`
CFLAGS	= -g -Wall
INCPATH = ../release
LIBPATH = ../release
SRCS	= TestSuite.c
LIBNAME = taggedstring

main:	
	$(CXX) $(CFLAGS) -I$(INCPATH) -L$(LIBPATH) -l$(LIBNAME) $(SRCS) -o main
	./runme.sh

test:
	./runme.sh

clean:
	rm -rf main *.o
