CXXFLAGS += -std=c++23 -Wall -O
LDLIBS = -lstdc++ -lm -lpthread 
TIME = time --append --output $@ --format "$$nthreads %e %U"

times.svg: out.times Makefile
	echo '\
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "Number of threads" ;\
		set ylabel "Real time (sec)" ;\
		a=1; b=10;\
		f(x)=a+b/x;\
		fit f(x) "$<" using 1:2 via a,b ;\
		plot \
			 "$<" using 1:2 with linespoints title "Times" \
			 ,f(x) title "Fit with 1/n" ;\
	'| tee log.times |gnuplot

N=1000000000

out.times: main Makefile
	>$@
	for nthreads in $$(seq 8); do \
		echo -n "$$nthreads " >> $@ ; \
		/usr/bin/time -f "%e" ./main -terms $(N) -threads $$nthreads 2>> $@ ; \
	done


all: out1 out2 out3 out4
out1: main ; ./main -threads 1 -terms 1e8 > $@
out2: main ; ./main -threads 1 -terms 2e8 > $@
out3: main ; ./main -threads 1 -terms 3e8 > $@
out4: main ; ./main -threads 1 -terms 4e8 > $@

test: main
	./main -threads 1 -terms 1e8 > out5 &
	./main -threads 1 -terms 2e8 > out6 &
	./main -threads 1 -terms 3e8 > out6 &
	./main -threads 1 -terms 4e8 > out7 &

clean:
	$(RM) main fit.log