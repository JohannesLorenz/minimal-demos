# flags you can customize
CFLAGS=-g -ggdb -pipe
LFLAGS=
FLAGS=-Wall -Wextra
CC=clang++
SRC=song.cpp
OUTFILE=song
MODULES=minimal-zynaddsubfx

# flags you should not customize
FIXED_CFLAGS=-fPIC `pkg-config --cflags minimal ${MODULES}`
FIXED_LFLAGS=-shared `pkg-config --libs minimal ${MODULES}`
FIXED_FLAGS=-std=c++11
OBJ=$(SRC:%.cpp=%.cpp.o)

# rules
${OUTFILE}: ${OBJ}
	${CC} ${FIXED_FLAGS} ${FLAGS} ${FIXED_LFLAGS} ${LFLAGS} ${OBJ} -o ${OUTFILE}
%.cpp.o: %.cpp
	${CC} ${FIXED_FLAGS} ${FLAGS} ${FIXED_CFLAGS} ${CFLAGS} -c $< -o $<.o
clean-obj:
	rm -f ${OBJ}
clean: clean-obj
	rm -f ${OUTFILE}
release: ${OUTFILE} clean-obj
rebuild: clean
	${MAKE} ${OUTFILE}
