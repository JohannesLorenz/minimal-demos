# flags you can customize
CFLAGS=-g -pipe
LFLAGS=
FLAGS=-Wall -Wextra -Werror
CC=clang++
SRC=song.cpp
OUTFILE=song

# flags you should not customize
FIXED_CFLAGS=-fPIC `pkg-config --cflags minimal minimal-zynaddsubfx`
FIXED_LFLAGS=-shared `pkg-config --libs minimal minimal-zynaddsubfx`
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
