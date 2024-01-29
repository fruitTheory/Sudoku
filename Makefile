CC = g++
FLAGS = -g -Wall -Wextra -Wno-unused-parameter -fdiagnostics-color=always
LIBRARY_DIR ?=
LINKED_LIBRARIES =

SRC = main.cpp sudoku.cpp sudoku_utility.cpp sudoku_solve.cpp sudoku_zones.cpp
OBJECTS = $(SRC:%.cpp=$(BUILD)%.o)

BUILD = ./build/
BINARIES = ./bin/
SOURCES = ./src/
INCLUDES ?= -I ./include/

# The main call
all: directories main

directories:
	if [ ! -d bin ]; then mkdir bin; fi	
	if [ ! -d build ]; then mkdir build; fi

main: $(OBJECTS)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIBRARY_DIR) $(LINKED_LIBRARIES) -o $(BINARIES)main
	make run

# Build all - wildcard
$(BUILD)%.o: $(SOURCES)%.cpp
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean run

# Clean build folder if needed
clean:
	rm -f $(BUILD)*.o
	rm -f $(BINARIES)*.exe
	
RUN_FILE = main
EXT = exe
run:
	$(BINARIES)$(RUN_FILE).$(EXT)

