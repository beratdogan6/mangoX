CC      = gcc
CXX     = g++
CFLAGS  = -Wall -Wextra -std=c11 -O2 -D_GNU_SOURCE
CFLAGS += -I./src -I./glfw-src/include -I./glad-src/include

CXXFLAGS  = -Wall -Wextra -std=c++17 -O2
CXXFLAGS += -I./src -I./glfw-src/include -I./glad-src/include

LDFLAGS = -L./glfw-src/build/src
LDLIBS  = -lglfw3 -lGL -lm -lpthread -ldl -lX11 -lXrandr -lXinerama -lXcursor -lXi -lXext

# main project sources (C and C++ under src/)
SRC_C   = $(shell find src -name '*.c')
SRC_CXX = $(shell find src -name '*.cpp')
OBJ_C   = $(patsubst src/%.c,   build/%.o,   $(SRC_C))
OBJ_CXX = $(patsubst src/%.cpp, build/%.o,   $(SRC_CXX))

# glad is a single C file compiled separately
GLAD_OBJ = build/glad.o

OBJ = $(OBJ_C) $(OBJ_CXX) $(GLAD_OBJ)
BIN = build/mangox

# examples still use raylib
RAYLIB_FLAGS  = -I./raylib-src/src
RAYLIB_LFLAGS = -L./raylib-src/build/raylib
RAYLIB_LIBS   = -lraylib -lGL -lm -lpthread -ldl -lX11 -lXrandr -lXinerama -lXcursor -lXi -lXext
EXAMPLES_SRC  = $(wildcard examples/*.c)
EXAMPLES_BIN  = $(patsubst examples/%.c, build/examples/%, $(EXAMPLES_SRC))
LIB_OBJ       = $(filter-out build/main.o, $(OBJ_C))

.PHONY: all examples clean run

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

build/glad.o: glad-src/src/glad.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

examples: $(EXAMPLES_BIN)

build/examples/%: examples/%.c $(LIB_OBJ)
	@mkdir -p build/examples
	$(CC) $(CFLAGS) $(RAYLIB_FLAGS) $^ -o $@ $(RAYLIB_LFLAGS) $(RAYLIB_LIBS)

run: all
	./$(BIN)

clean:
	rm -rf build
