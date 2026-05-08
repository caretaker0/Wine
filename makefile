PROGNAME=wine
VERSION=0.1

OSXINCS=-I/opt/homebrew/include
OSXLIBS=-L/opt/homebrew/lib \
        -lglfw \
        -framework OpenGL 

INCS=-Iinclude ${OSXINCS}

LIBS=-lglfw -lGL -lm -ldl
# OSX Uncomment
 LIBS=${OSXLIBS}

CC=cc
CPPFLAGS=-D_POSIX_C_SOURCE=200809L -DPROGNAME=\"${PROGNAME}\" -DGLFW_BUILD_WAYLAND=1
CFLAGS=-Wall -pedantic -std=c99 ${CPPFLAGS} ${INCS}
LDFLAGS=${LIBS}

all: ${PROGNAME}

glad.o: glad.c
	${CC} -c ${INCS} $<

.c.o:
	${CC} -c ${CFLAGS} $<	

${PROGNAME}: main.o loadshader.o util.o glad.o
	${CC} -o $@ $^ ${LDFLAGS}

clean:
	rm -f *.o ${PROGNAME}
