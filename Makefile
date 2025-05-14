# Compiler and flags
CXX = clang++
CC = clang
CXXFLAGS = -Wall -g -std=c++17 -Iinclude  # Add include directory for headers
CFLAGS = -Wall -g -std=c11 -Iinclude      # Add include directory for headers
# Program name
PROG = proj

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Find all source files in the src directory
CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)
C_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES = $(CPP_FILES) $(C_FILES)

# Generate object files from source files
OBJ_FILES = $(CPP_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) \
            $(C_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/$(PROG)

# Default target
all: $(TARGET)

# Link object files into the executable
$(TARGET): $(OBJ_FILES)          
	mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_FILES) -o $(TARGET)

# Compile C++ source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*.* $(BIN_DIR)/$(PROG)

# Generate dependencies to recompile files if headers change
-include $(OBJ_FILES:.o=.d)

# Create dependencies for C++ source files
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -M $< > $@

# Create dependencies for C source files
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -M $< > $@
wipe:
	rm -rf $(OBJ_DIR)/*.* $(BIN_DIR)/$(PROG)
	rm -rf $(SRC_FILES)/*.*
	rm -rf $(INC_DIR)/*.*
