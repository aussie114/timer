NAME = timer
OBJECTS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

build: $(OBJECTS)
	gcc `pkg-config --libs gtk4` build/*.o -o bin/$(NAME)

run: build
	bin/$(NAME) 3

build/%.o: src/%.c
	gcc -Wall -Wextra -Iinclude `pkg-config --cflags gtk4` -c $< -o $@

clean:
	rm -rf build/* bin/$(NAME)
