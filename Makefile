CC := gcc
CFLAGS := -O2 -Wall -Wextra -Werror -l ncurses
BUILD_DIR := build/pong

all: build

$(BUILD_DIR)/src/ball.o: src/ball.c src/ball.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/ball.c -o $(BUILD_DIR)/src/ball.o

$(BUILD_DIR)/src/paddle.o: src/paddle.c src/paddle.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/paddle.c -o $(BUILD_DIR)/src/paddle.o

$(BUILD_DIR)/src/main.o: src/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/main.c -o $(BUILD_DIR)/src/main.o

build: $(BUILD_DIR)/src/ball.o $(BUILD_DIR)/src/paddle.o $(BUILD_DIR)/src/main.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(BUILD_DIR)/src/ball.o $(BUILD_DIR)/src/paddle.o $(BUILD_DIR)/src/main.o -o $(BUILD_DIR)/pong.out

run: build
	$(BUILD_DIR)/pong.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/src

clean:
	rm -rf $(BUILD_DIR)/pong.out
	rm -rf $(BUILD_DIR)/src
