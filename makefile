# Compiler and compile flags
COMPILER = clang++
FLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Force laptop to use Clang libraries not GNU.
USER = $(shell whoami)
ifeq ($(USER),bandarussr)
FLAGS += -stdlib=libc++
endif

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Files
TARGET = $(BUILD_DIR)/target
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))


# Build
all: $(TARGET)

# Link
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(COMPILER) $(FLAGS) $^ -o $@

# Compile into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(wildcard $(INC_DIR)/*)
	@mkdir -p $(BUILD_DIR)
	$(COMPILER) $(FLAGS) -c $< -o $@


# Run
INPUT ?= ./trace.dat
run: all
	./$(TARGET) < $(INPUT)


# Init
ifeq ($(INCLUDE), true)
init:
	@mkdir -p $(SRC_DIR) $(INC_DIR)
else
init:
	@mkdir -p $(SRC_DIR)
endif

# Clean
clean:
	rm -rf $(BUILD_DIR)/*


.PHONY: all build run clean init
