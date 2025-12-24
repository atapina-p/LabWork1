CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = labwork
TEST_TARGET = test

SRC = main.cpp BMPImage.cpp BMPHeader.cpp
OBJ = $(SRC:.cpp=.o)

TEST_SRC = tests.cpp BMPImage.cpp BMPHeader.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJ) -lgtest -lpthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET) $(TEST_TARGET)