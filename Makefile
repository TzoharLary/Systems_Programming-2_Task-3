# The CXX variable contains the compiler to be used
CXX = g++
# The CXXFLAGS variable contains the flags to be passed to the compiler
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
# The LDFLAGS variable contains the flags to be passed to the linker
LDFLAGS = -Llib -lgtest -lpthread

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
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
# The TEST_OBJECTS variable contains all the .o files in the build directory
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SOURCES))

EXEC = build_catan
TEST_EXEC = run_tests
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

test: $(TEST_EXEC)

$(TEST_EXEC): $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(CTN) $(TEST_EXEC)

.PHONY: all test clean built_obj
