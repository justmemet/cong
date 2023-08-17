COMPILER := gcc
COMMON_FLAGS := -O2 -Wall -Wextra -Werror -l ncurses

bin/:
	mkdir bin/

ball.o: bin/ src/ball.c src/ball.h
	$(COMPILER) $(COMMON_FLAGS) -c src/ball.c -o bin/ball.o

paddle.o: bin src/paddle.c src/paddle.h
	$(COMPILER) $(COMMON_FLAGS) -c src/paddle.c -o bin/paddle.o

main.o: bin/ src/main.c
	$(COMPILER) $(COMMON_FLAGS) -c src/main.c -o bin/main.o

build: bin/ ball.o paddle.o main.o
	$(COMPILER) $(COMMON_FLAGS) bin/ball.o bin/paddle.o bin/main.o -o bin/pong

run: build
	bin/pong

clean:
	rm -rf bin/ball.o
	rm -rf bin/paddle.o
	rm -rf bin/main.o
	rm -rf bin/pong