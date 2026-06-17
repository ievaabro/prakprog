CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -O2

OBJS = main.o ode.o matrix.o jacobi.o newton.o qr.o rkstep.o

main: $(OBJS)
	$(CXX) $(OBJS) -o main

main.o: main.cc
ode.o: ode.cc
matrix.o: matrix.cc
jacobian.o: jacobi.cc
newton.o: newton.cc
qr.o: qr.cc
rkstep.o: rkstep.cc

clean:
	rm -f *.o main

plot: main
	./main
	gnuplot plot_wf.gp