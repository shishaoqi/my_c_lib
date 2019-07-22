# Makefile for cslib directory
#****************************************************************

OBJECTS = \
    genlib.o \
    simpio.o \
    strlib.o \
    queue.o \
    queuelist.o \
    random.o \
    cmpfn.o \
    ref.o \
    scanadt.o \
    set.o \
    foreach.o \
    stack.o \
    stacklist.o \
    symtab.o \
    iterator1.o \
    iterator2.o \
    exception.o \
    graphics.o \
    xmanager.o \
    xdisplay.o \
    xcompat.o \
    glibrary.o \
    avl.o \
    blt.o

CSLIB = libcs.a

CC = gcc
CFLAGS = -g -I. $(CCFLAGS)
CONFIG = `csh config.csh -DHasPoll $(CC) -E -DHasPoll xcompat.c`

# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(CSLIB) gccmy
# ***************************************************************
# Standard entries to remove files from the directories
#    tidy    -- eliminate unwanted files
#    clean   -- delete derived files in preparation for rebuild
#    scratch -- synonym for clean

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a

# ***************************************************************
# C compilations

genlib.o: genlib.c genlib.h exception.h gcalloc.h
	$(CC) $(CFLAGS) -c genlib.c

avl.o: avl.c avl.h cmpfn.h genlib.h
	$(CC) $(CFLAGS) -c avl.c

blt.o: blt.c blt.h cmpfn.h genlib.h
	$(CC) $(CFLAGS) -c blt.c

cmpfn.o: cmpfn.c cmpfn.h strlib.h genlib.h
	$(CC) $(CFLAGS) -c cmpfn.c

iterator1.o: iterator1.c iterator1.h genlib.h strlib.h symtab.h
	$(CC) $(CFLAGS) -c iterator1.c

iterator2.o: iterator2.c iterator2.h cmpfn.h genlib.h itertype.h
	$(CC) $(CFLAGS) -c iterator2.c

queue.o: queue.c queue.h genlib.h
	$(CC) $(CFLAGS) -c queue.c

queuelist.o: queuelist.c queuelist.h genlib.h
	$(CC) $(CFLAGS) -c queuelist.c

random.o: random.c random.h genlib.h
	$(CC) $(CFLAGS) -c random.c

ref.o: ref.c ref.h genlib.h
	$(CC) $(CFLAGS) -c ref.c

scanadt.o: scanadt.c scanadt.h genlib.h strlib.h
	$(CC) $(CFLAGS) -c scanadt.c

set.o: set.c set.h bst.h genlib.h iterator2.h itertype.h
	$(CC) $(CFLAGS) -c set.c

foreach.o: foreach.c foreach.h genlib.h iterator2.h
	$(CC) $(CFLAGS) -c foreach.c

simpio.o: simpio.c simpio.h strlib.h genlib.h
	$(CC) $(CFLAGS) -c simpio.c

stack.o: stack.c stack.h genlib.h
	$(CC) $(CFLAGS) -c stack.c

stacklist.o: stacklist.c stacklist.h genlib.h
	$(CC) $(CFLAGS) -c stacklist.c

strlib.o: strlib.c strlib.h genlib.h
	$(CC) $(CFLAGS) -c strlib.c

symtab.o: symtab.c symtab.h strlib.h genlib.h itertype.h cmpfn.h
	$(CC) $(CFLAGS) -c symtab.c

exception.o: exception.c exception.h genlib.h
	$(CC) $(CFLAGS) -c exception.c

graphics.o: graphics.c graphics.h extgraph.h xmanager.h xcompat.h \
            glibrary.h genlib.h gcalloc.h simpio.h strlib.h Makefile
	$(CC) $(CONFIG) $(CFLAGS) -c graphics.c

xmanager.o: xmanager.c xmanager.h xdisplay.h xcompat.h glibrary.h \
	    genlib.h exception.h simpio.h Makefile
	$(CC) $(CONFIG) $(CFLAGS) -c xmanager.c

xdisplay.o: xdisplay.c xdisplay.h xmanager.h glibrary.h genlib.h strlib.h \
            Makefile
	$(CC) $(CONFIG) $(CFLAGS) -c xdisplay.c

xcompat.o: xcompat.c xcompat.h Makefile
	$(CC) $(CONFIG) $(CFLAGS) -c xcompat.c

glibrary.o: glibrary.c glibrary.h genlib.h
	$(CC) $(CFLAGS) -c glibrary.c

# ***************************************************************
# Entry to reconstruct the library archive

$(CSLIB): $(OBJECTS)
	-rm -f $(CSLIB)
	ar cr $(CSLIB) $(OBJECTS)
	ranlib $(CSLIB)

# ***************************************************************
# Entry to reconstruct the gccx script

gccmy: Makefile
	@echo '#! /bin/csh -f' > gccmy
	@echo 'set INCLUDE =' `pwd` >> gccmy
	@echo 'set CSLIB = $$INCLUDE/libcs.a' >> gccmy
	@echo 'set LIBRARIES = ($$CSLIB -lX11 -lm)' >> gccmy
	@echo 'foreach x ($$*)' >> gccmy
	@echo '  if ("x$$x" == "x-c") then' >> gccmy
	@echo '    set LIBRARIES = ""' >> gccmy
	@echo '    break' >> gccmy
	@echo '  endif' >> gccmy
	@echo 'end' >> gccmy
	@echo 'gcc -g -I$$INCLUDE $$* $$LIBRARIES' >> gccmy
	@chmod a+x gccmy
	@echo '[gccmy script created]'
