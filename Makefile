CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = labwork

SRC = main.cpp BMPImage.cpp BMPHeader.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET)