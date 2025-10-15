PROJECT = timer
OBJECTS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

run: build
	bin/$(PROJECT) 00:00:15

build: $(OBJECTS)
	gcc build/*.o -o bin/$(PROJECT) -lncurses

build/%.o: src/%.c
	gcc -Wall -Wextra -Iinclude -lncurses -c $< -o $@

clean:
	rm -rf build/* bin/$(PROJECT)

