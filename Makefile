CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2 -D_GNU_SOURCE
CFLAGS += -I./raylib-src/src -I./src

LDFLAGS = -L./raylib-src/build/raylib
LDLIBS  = -lraylib -lm -lpthread -ldl -lGL -lX11 -lXrandr -lXinerama -lXcursor -lXi -lXext

SRC     = $(shell find src -name '*.c')
OBJ     = $(patsubst src/%.c, build/%.o, $(SRC))
BIN     = build/mangox

EXAMPLES_SRC = $(wildcard examples/*.c)
EXAMPLES_BIN = $(patsubst examples/%.c, build/examples/%, $(EXAMPLES_SRC))
LIB_OBJ      = $(filter-out build/main.o, $(OBJ))

.PHONY: all examples clean run

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

examples: $(EXAMPLES_BIN)

build/examples/%: examples/%.c $(LIB_OBJ)
	@mkdir -p build/examples
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

run: all
	./$(BIN)

clean:
	rm -rf build
