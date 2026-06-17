CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -O2

OBJS = main.o rkstep.o ode.o vec.o

main: $(OBJS)
	$(CXX) $(OBJS) -o main

main.o: main.cc
rkstep.o: rkstep.cc
ode.o: ode.cc
vec.o: vec.cc

clean:
	rm -f *.o main

plot: main
	./main
	gnuplot orbit.gp threebody.gp 