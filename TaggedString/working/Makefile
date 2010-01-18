CXX 	= `which gcc`
CFLAGS 	= -fPIC -g -Wall
INCPATH = ./include
LIBNAME = libtaggedstring
VERNUM  = 1

release: components
	$(CXX) -shared -Wl,-soname,$(LIBNAME).so.$(VERNUM) \
		-o $(LIBNAME).so.$(VERNUM) *.o -lc
	rm -rf ../release
	mkdir ../release
#	rm -rf ../release/$(LIBNAME).so
	mv $(LIBNAME).so.$(VERNUM) ../release/
	ln -s ../release/$(LIBNAME).so.$(VERNUM) ../release/$(LIBNAME).so
	cp include/taggedstring/TaggedString.h ../release/

components: 
	$(CXX) $(CFLAGS) -I$(INCPATH) -c src/*.c

clean:
	rm -rf test *.o
