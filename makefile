# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -g

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Output binary
TARGET = $(BUILD_DIR)/sac

# Detect OS
OS := $(shell uname 2>/dev/null || echo Windows)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Cross-platform clean rule
clean:
ifeq ($(OS), Windows)
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
else
	@rm -rf $(BUILD_DIR)
endif

.PHONY: all clean
