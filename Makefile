CC := gcc
CFLAGS := -O2 -Wall -Wextra -Werror -l ncurses
BUILD_DIR := build/cong

SOURCE_FILES := $(wildcard src/*.c)
OBJECT_FILES := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCE_FILES))

all: build

$(BUILD_DIR)/src/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

build: $(OBJECT_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $(BUILD_DIR)/cong.out

run: build
	$(BUILD_DIR)/cong.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/src

clean:
	rm -rf $(BUILD_DIR)
