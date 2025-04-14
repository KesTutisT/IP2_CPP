CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRC_DIR = src
OBJS = $(SRC_DIR)/map.o

all: demo test

$(SRC_DIR)/map.o: $(SRC_DIR)/map.cpp $(SRC_DIR)/map.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/map.cpp -o $(SRC_DIR)/map.o

demo: $(SRC_DIR)/demo.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o demo $(SRC_DIR)/demo.cpp $(OBJS)

test: $(SRC_DIR)/test.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o test $(SRC_DIR)/test.cpp $(OBJS)

runtest: test
	./test

clean:
	rm -f $(SRC_DIR)/*.o demo test test_results.txt

rebuild: clean all
