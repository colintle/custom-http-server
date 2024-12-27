# Compiler
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# Output
TARGET := $(BIN_DIR)/my_program

# Find all source files recursively
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
# Generate object file names, preserving directory structure
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Find all include subdirectories
INCLUDE_PATHS := $(shell find $(INCLUDE_DIR) -type d)
# Add -I flag for each include path
CXXFLAGS += $(foreach dir, $(INCLUDE_PATHS), -I$(dir))

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each source file to an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Rebuild everything
rebuild: clean all

# Phony targets
.PHONY: all clean rebuild

