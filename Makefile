INCLUDES ?= -I ./include/ 
BUILD = ./build/
SOURCES = ./src/
BINARIES = ./bin/
FLAGS = -g -Wall -Wextra -fdiagnostics-color=always #-fsanitize=address -O3
CC = g++
OBJECTS =
LIBRARY_DIR ?=
LINKED_LIBRARIES =

all: ${OBJECTS}
	if not exist "bin" mkdir bin
	if not exist "build" mkdir build
	${CC} ${FLAGS} ${INCLUDES} ${OBJECTS} ${SOURCES}main.cpp ${LIBRARY_DIR} ${LINKED_LIBRARIES} -o ${BINARIES}main
	mingw32-make run

# Build all - wildcards
${BUILD}%.o:${SOURCES}%.cpp
	${CC} ${FLAGS} ${INCLUDES} -c $< -o $@

.PHONY: clean run

# Clean build folder if needed
clean:
	del "${BUILD}"

# Run with file
RUN_FILE = main
EXT = exe
run:
	${BINARIES}${RUN_FILE}.${EXT}

