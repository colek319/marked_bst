CXX = clang++

CXXFLAGS = -Wall -Wextra -std=c++11 

all: test experiment

experiment: marked_bst.o experiment.o
	$(CXX) $(CXXFLAGS) -o experiment marked_bst.o experiment.o

test: marked_bst.o test.o
	$(CXX) $(CXXFLAGS) -o test marked_bst.o test.o

experiment.o: ../src/experiment.cpp ../includes/marked_bst.h
	$(CXX) $(CXXFLAGS) -c ../src/experiment.cpp

test.o: ../test/test.cpp ../includes/marked_bst.h
	$(CXX) $(CXXFLAGS) -c ../test/test.cpp

marked_bst.o: ../src/marked_bst.cpp ../includes/marked_bst.h
	$(CXX) $(CXXFLAGS) -c ../src/marked_bst.cpp

clean:
	rm -rf test experiment *.o
