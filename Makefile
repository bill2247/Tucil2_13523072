# Makefile
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O3 -I./src/header -Wno-missing-field-initializers

SRC_DIR := src/modules
HEADER_DIR := src/header
BIN_DIR := bin
TEST_DIR := test

# List all source files except stb_implementation.cpp for regular compilation
MAIN_SOURCES := $(SRC_DIR)/ErrorCalculator.cpp \
                $(SRC_DIR)/ImagePixel.cpp \
                $(SRC_DIR)/QuadTreeNode.cpp \
                $(SRC_DIR)/main.cpp

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(MAIN_SOURCES))
STB_OBJECT := $(BIN_DIR)/stb_implementation.o
EXECUTABLE := $(BIN_DIR)/quadtree_compressor

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(STB_OBJECT)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(STB_OBJECT): $(SRC_DIR)/stb_implementation.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)/*.o $(EXECUTABLE)

run: all
	@$(EXECUTABLE) $(TEST_DIR)/input.png 1 30.0 4 0.0 $(TEST_DIR)/output.png

.PHONY: all clean run