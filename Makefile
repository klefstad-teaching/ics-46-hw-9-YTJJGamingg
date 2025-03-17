CXX = g++
CXXFLAGS = -std=c++20 -fsanitize=address -g -I src

TARGET = ladder_program

OBJ_FILES = src/ladder.o src/ladder_main.o

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $@

src/%.o: src/%.cpp src/ladder.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_FILES) $(TARGET)
