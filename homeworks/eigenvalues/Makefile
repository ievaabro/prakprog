CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS += -lm

OBJS = main.o matrix.o vec.o EVD.o

Out.txt: main
	./$< > $@
# 	./$< -rmax 10 -dr 0.3 > $@

all: main

main: $(OBJS)
	$(CXX) $(OBJS) -o main $(LDLIBS)

main.o: main.cc matrix.h vec.h EVD.h
matrix.o: matrix.cc matrix.h vec.h
vec.o: vec.cc vec.h
EVD.o: EVD.cc EVD.h matrix.h vec.h

clean:
	rm -f *.o main wavefunction.dat

test:
	./main

waves:
	gnuplot waves.gp
	@echo "Saved → fig_waves.png"

timing:
	gnuplot timing.gp
	@echo "Saved → fig_timing.png"

plots: waves, timing

plot:
	./main
	gnuplot timing.gp