CXX 	= `which gcc`
DEL 	= `which rm`

CFLAGS 	= -fPIC -g -Wall
INCPATH = ./include
LIBNAME = libnecessity

OUTDIR  = ../../output
VERNUM  = 1

library: objects
	$(CXX) -shared -Wl,-soname,$(LIBNAME).so.$(VERNUM) \
		-o $(LIBNAME).so.$(VERNUM) *.o -lc
	rm -rf $(OUTDIR) 
	mkdir $(OUTDIR) 
	mv $(LIBNAME).so.$(VERNUM) $(OUTDIR)/$(LIBNAME).so.$(VERNUM) 
	cp -r ../include/* $(OUTDIR)
	cd $(OUTDIR) && ln -s $(LIBNAME).so.$(VERNUM) $(LIBNAME).so

objects: 
	$(CXX) $(CFLAGS) -I$(INCPATH) -c *.c

clean:
	$(DEL) -rf *.o* *.so*

# References:
# # http://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html 
