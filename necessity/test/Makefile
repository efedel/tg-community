CXX	= `which gcc`
CFLAGS	= -g -Wall
INCPATH = ../output/necessity
LIBPATH = ../output
SRCS	= TestSuite.c
LIBNAME = necessity

main:	
	$(CXX) $(CFLAGS) -I$(INCPATH) -L$(LIBPATH) -l$(LIBNAME) $(SRCS) -o main
	./runme.sh

test:
	./runme.sh

clean:
	rm -rf main *.o
