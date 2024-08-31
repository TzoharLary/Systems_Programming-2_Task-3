# The CXX variable contains the compiler to be used
CXX = g++
# The CXXFLAGS variable contains the flags to be passed to the compiler
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Isrc -Itests

# The SRC_DIR variable contains the name of the directory where the source files are located
# The TEST_DIR variable contains the name of the directory where the test files are located
# The BUILD_DIR variable contains the name of the directory where the object files will be placed
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# The SOURCES variable contains all the .cpp files in the src directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# The OBJECTS variable contains all the .o files in the build directory
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
# The TEST_SOURCES variable contains all the .cpp files in the tests directory
TEST_SOURCES = $(filter-out $(SRC_DIR)/main.cpp, $(SOURCES)) $(wildcard $(TEST_DIR)/*.cpp)
# The TEST_OBJECTS variable contains all the .o files in the build directory
TEST_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter $(SRC_DIR)/%.cpp, $(TEST_SOURCES))) \
               $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter $(TEST_DIR)/%.cpp, $(TEST_SOURCES)))

EXEC = build_catan
TEST_EXEC = build_test
TEST = test
CTN = catan

all: $(EXEC)

# for the command make catan
# this target builds the catan program if it's not built yet 
# and then turn it on
$(CTN): $(EXEC)
	./$(CTN)

# this targat depends on the $(OBJECTS) target 
# and she's responsible for linking the object files to catan program
$(EXEC): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) -o $(CTN) $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TEST): CXXFLAGS += -DRUNNING_TESTS

$(TEST): $(TEST_EXEC)
	./$(TEST)

$(TEST_EXEC): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST) $^ 

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(CTN) $(TEST)

.PHONY: all test clean built_obj
