INCLUDES ?= -I ./include/ 
BUILD = ./build/
SOURCES = ./src/
BINARIES = ./bin/
FLAGS = -g -Wall -Wextra -Wno-unused-parameter -fdiagnostics-color=always #-O3
CC = g++
OBJECTS =
LIBRARY_DIR ?=
LINKED_LIBRARIES =

all: ${OBJECTS}
	if [ ! -d bin ]; then mkdir bin; fi
	if [ ! -d build ]; then mkdir build; fi
	${CC} ${FLAGS} ${INCLUDES} ${OBJECTS} ${SOURCES}main.cpp ${LIBRARY_DIR} ${LINKED_LIBRARIES} -o ${BINARIES}main
	make run

# Build all - wildcards
${BUILD}%.o:${SOURCES}%.cpp
	${CC} ${FLAGS} ${INCLUDES} -c $< -o $@

.PHONY: clean run

# Clean build folder if needed
clean:
	rm ${BINARIES}*.exe
	rm ${BUILD}*.o

# Run with file
RUN_FILE = main
EXT = exe
run:
	${BINARIES}${RUN_FILE}.${EXT}

