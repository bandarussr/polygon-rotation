# Compiler and compile flags
COMPILER = clang++
FLAGS = -std=c++17 -Wall -Wextra -Wshadow -Wunreachable-code -O3

ifneq ($(filter $(USER), shashanksrb bandarussr banda),)
	FLAGS += -stdlib=libc++
endif

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = bin

# Files
TARGET = $(BUILD_DIR)/PolygonRotation
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

# Build
all: $(TARGET)

$(TARGET): $(SRC_FILES)
	@mkdir -p $(BUILD_DIR)
	$(COMPILER) $(FLAGS) $^ -o $@ -I $(INCLUDE_DIR)

debug: FLAGS += -g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer
debug: $(TARGET)

# Clean
clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all debug clean
