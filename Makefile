CXX=g++
CXXPARAMS=-g
LDPARAMS=
CXXINCLUDES=-I/usr/include/libpng
CXXLIBDIRS=-L/lib/x86_64-linux-gnu
CXXLIBS=-lpng

EXEC_NAME=vol2im
OBJECTS=vol2im.o volumetric_structure.o stdout_backend.o png_backend.o \
	png_frontend.o stpng8_frontend.o

all: ${EXEC_NAME}

.o: %.cpp
	${CXX} ${CXXPARAMS} ${CXXINCLUDES} -c $<

vol2im: ${OBJECTS}
	${CXX} ${LDPARAMS} ${CXXLIBDIRS} ${OBJECTS} -o ${EXEC_NAME} ${CXXLIBS}

clean:
	rm -f ${OBJECTS}

distclean:
	rm -f ${OBJECTS} ${EXEC_NAME}
