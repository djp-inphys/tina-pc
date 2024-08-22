SHELL = /bin/sh
CC=gcc

HFILES = 

CFLAGS = $(TINA_COMPILE_FLAGS) -I$(TINA_INCLUDEDIR)

LIBRARY = $(TINA_LIBDIR)/libtinaserialise.a

.PRECIOUS : $(LIBRARY)

$(LIBRARY):\
	$(LIBRARY)(ddlist.o)\
	$(LIBRARY)(edge_conn.o)\
	$(LIBRARY)(imrect.o)\
	$(LIBRARY)(imstack.o)\
	$(LIBRARY)(list.o)\
	$(LIBRARY)(matrix.o)\
	$(LIBRARY)(narray.o)\
	$(LIBRARY)(nvector.o)\
	$(LIBRARY)(prop.o)\
	$(LIBRARY)(rindex.o)\
	$(LIBRARY)(ts_set.o)\
	$(LIBRARY)(vector.o)\
	$(LIBRARY)(windex.o)
	$(RANLIB) $(LIBRARY)

$(LIBRARY)($(OFILES)): $(HFILES)
