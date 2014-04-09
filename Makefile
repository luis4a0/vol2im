CC=gcc
CCPARAMS=-g -Wall -O2
LDPARAMS=
CCINCLUDES=-I/usr/include/libpng
CCLIBDIRS=-L/lib/x86_64-linux-gnu
CCLIBS=-lm -lpng

EXEC_NAME=vol2im
OBJECTS=vol2im.o volumetric_structure.o stdout_backend.o png_backend.o \
	png_frontend.o stpng8_frontend.o stpng816_frontend.o

all: ${EXEC_NAME}

.c.o:
	${CC} ${CCPARAMS} ${CCINCLUDES} -c $<

${EXEC_NAME}: ${OBJECTS}
	${CC} ${LDPARAMS} ${CCLIBDIRS} ${OBJECTS} -o ${EXEC_NAME} ${CCLIBS}

clean:
	rm -f ${OBJECTS}

distclean:
	rm -f ${OBJECTS} ${EXEC_NAME}
