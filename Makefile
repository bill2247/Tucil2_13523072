# Makefile for Quadtree Image Compressor

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++14 -Wall -Wextra -O3 -I./src/header -Wno-missing-field-initializers

# Directories
SRC_DIR := src/modules
HEADER_DIR := src/header
BIN_DIR := bin
TEST_DIR := test

# Source files
SOURCES := $(SRC_DIR)/ErrorCalculator.cpp \
           $(SRC_DIR)/ImagePixel.cpp \
           $(SRC_DIR)/QuadTreeNode.cpp \
           $(SRC_DIR)/main.cpp \
           $(SRC_DIR)/stb_implementation.cpp

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SOURCES))
EXECUTABLE := $(BIN_DIR)/quadtree_compressor

# Main target
all: $(EXECUTABLE)

# Link all object files
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each source file to object file
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)/*.o $(EXECUTABLE)

run: all
	@$(EXECUTABLE) $(TEST_DIR)/input.png 1 30.0 4 0.0 $(TEST_DIR)/output.png

.PHONY: all clean run