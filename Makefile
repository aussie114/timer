PROJECT = timer
OBJECTS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

build: $(OBJECTS)
	gcc build/*.o -o $(PROJECT) -Iinclude -lSDL3 -lSDL3_ttf
	./$(PROJECT) 3

build/%.o: src/%.c
	gcc  -Wall -Wextra -Iinclude -c $< -o $@

clean:
	rm -rf build/* $(PROJECT)
