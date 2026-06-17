CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS += -lm

OBJS = main.o matrix.o vector.o lsfit.o qr.o

Out.txt: main
	./$< > $@
# 	./$< -rmax 10 -dr 0.3 > $@

all: main

main: $(OBJS)
	$(CXX) $(OBJS) -o main $(LDLIBS)

main.o: main.cc matrix.h vector.h lsfit.h
matrix.o: matrix.cc matrix.h vector.h
vector.o: vector.cc vector.h
lsfit.o: lsfit.cc lsfit.h matrix.h vector.h
qr.o: qr.cc qr.h matrix.h

clean:
	rm -f *.o main

test:
	./main

decay:
	gnuplot decay.gp
	@echo "Saved → fig_decay.png"


plots: decay

plot:
	./main
	gnuplot decay.gp