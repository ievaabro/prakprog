CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O3 -march=native
LDLIBS += -lm

OBJS = main.o matrix.o vector.o lu.o

all: main

main: $(OBJS)
	$(CXX) $(OBJS) -o main $(LDLIBS)
	./main

main.o: main.cc matrix.h vector.h lu.h
matrix.o: matrix.cc matrix.h vector.h
vector.o: vector.cc vector.h
lu.o: lu.cc lu.h matrix.h vector.h

LU_OBJS = main_lu.o matrix.o vector.o lu.o
QR_OBJS = main_qr.o matrix.o vector.o qr.o

main_lu: $(LU_OBJS)
	$(CXX) $(LU_OBJS) -o main_lu $(LDLIBS)

main_qr: $(QR_OBJS)
	$(CXX) $(QR_OBJS) -o main_qr $(LDLIBS)

main_lu.o: main_lu.cc matrix.h vector.h lu.h
main_qr.o: main_qr.cc matrix.h vector.h qr.h
qr.o: qr.cc qr.h matrix.h vector.h


lu.times.data: main_lu
	@rm -f $@
	@for N in 100 200 300 400 500 600 700 800 900 1000; do \
		echo "LU $$N"; \
		/usr/bin/time -f "$$N %e" -a -o $@ ./main_lu -size $$N > /dev/null; \
	done

qr.times.data: main_qr
	@rm -f $@
	@for N in 100 200 300 400 500 600 700 800 900 1000; do \
		echo "QR $$N"; \
		/usr/bin/time -f "$$N %e" -a -o $@ ./main_qr -size $$N > /dev/null; \
	done

report: lu.times.data qr.times.data
	@echo "===== RESULT SUMMARY ====="
	@echo "LU timings:"
	@cat lu.times.data
	@echo ""
	@echo "QR timings:"
	@cat qr.times.data

clean:
	rm -f *.o main
