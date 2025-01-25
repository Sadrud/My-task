CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread -Iinclude


SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj


SOURCES = $(SRC_DIR)/Logger.cpp $(SRC_DIR)/main.cpp
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.cpp=.o)))


TARGET = $(BUILD_DIR)/app
LIBRARY = $(BUILD_DIR)/liblogger.so


all: $(TARGET)


$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/Logger.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@


$(LIBRARY): $(OBJECTS)
	$(CXX) -shared -o $@ $^


clean:
	rm -rf $(BUILD_DIR)


test: $(TARGET)
	./$(TARGET) logfile.txt INFO

.PHONY: all clean test
