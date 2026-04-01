CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -O2
CFLAGS += -I./raylib-src/src

LDFLAGS = -L./raylib-src/build/raylib
LDLIBS  = -lraylib -lm -lpthread -ldl -lGL -lX11 -lXrandr -lXinerama -lXcursor -lXi -lXext

SRC = $(shell find src -name '*.c')
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
BIN = build/mangox

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(BIN)

clean:
	rm -rf build
