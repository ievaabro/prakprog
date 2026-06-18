CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O2

all: main

main: main.o matrix.o nn.o
	$(CXX) $(CXXFLAGS) -o main main.o matrix.o nn.o

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc

matrix.o: matrix.cc
	$(CXX) $(CXXFLAGS) -c matrix.cc

nn.o: nn.cc nn.h
	$(CXX) $(CXXFLAGS) -c nn.cc


clean:
	rm -f *.o main