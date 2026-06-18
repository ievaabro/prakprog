CXXFLAGS = -Wall -O2 -std=c++14

all: main plot

main: main.cc linspline.cc quadspline.cc
	$(CXX) $(CXXFLAGS) main.cc linspline.cc quadspline.cc -o main

plot: main
	./main
	echo '\
	set terminal svg size 800,600 background "white"; \
	set output "interpolation.svg"; \
	set title "Linear spline interpolation of cos(x)"; \
	set xlabel "x"; set ylabel "y"; \
	plot "interp.data" using 1:2 with lines title "Interpolant", \
	     "interp.data" using 1:3 with lines title "cos(x) exact", \
	     "points.data" using 1:2 with points pt 7 ps 1.2 title "Table data"; \
	set output "integration.svg"; \
	set title "Integral of linear spline"; \
	plot "integ.data" using 1:2 with lines title "Spline integral", \
	     "integ.data" using 1:3 with lines title "sin(x) exact"; \
	' | gnuplot

clean:
	rm -f main *.data *.svg