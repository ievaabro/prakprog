CXX = g++
CXXFLAGS = -Wall -std=c++23

# Default target
all: fig1.svg fig2.svg fig3.svg

# Compile program
main: main.cc
	$(CXX) $(CXXFLAGS) $< -o $@

# Generate data files
erf.data: main
	./main -mode erf > $@

erf_tab.data: main
	./main -mode erf-tab > $@

gamma.data: main
	./main -mode gamma > $@

gamma_tab.data: main
	./main -mode gamma-tab > $@

lngamma.data: main
	./main -mode lngamma > $@

# fig1: Error function, curve + tabulated points
fig1.svg: erf.data erf_tab.data
	echo '\
	set terminal svg size 900,600 ;\
	set output "$@" ;\
	set title "Error function" ;\
	set xlabel "x" ;\
	set ylabel "erf(x)" ;\
	set grid ;\
	plot "erf.data" using 1:2 with lines lw 2 title "curve", \
	     "erf_tab.data" using 1:2 with points pt 7 ps 1.5 lc rgb "red" title "tabulated points" ;\
	' | gnuplot

# fig3: Gamma function, curve + factorial points, vertical lines at poles
fig2.svg: gamma.data gamma_tab.data
	echo '\
	set terminal svg size 900,600 ;\
	set output "$@" ;\
	set title "Gamma function" ;\
	set xlabel "x" ;\
	set ylabel "Γ(x)" ;\
	set grid ;\
	set yrange [-10:150] ;\
	set arrow from -1,-10 to -1,150 nohead dt 2 ;\
	set arrow from -2,-10 to -2,150 nohead dt 2 ;\
	set arrow from -3,-10 to -3,150 nohead dt 2 ;\
	plot "gamma.data" using 1:2 with lines lw 2 title "Gamma curve", \
	     "gamma_tab.data" using 1:2 with points pt 7 ps 1.5 lc rgb "red" title "factorials" ;\
	' | gnuplot

# Optional: log gamma plot (curve only)
fig3.svg: lngamma.data
	echo '\
	set terminal svg size 900,600 ;\
	set output "$@" ;\
	set title "Log Gamma function" ;\
	set xlabel "x" ;\
	set ylabel "ln Γ(x)" ;\
	set grid ;\
	plot "lngamma.data" using 1:2 with lines lw 2 title "ln Gamma(x)" ;\
	' | gnuplot

# Clean everything
clean:
	rm -f main *.data *.svg log.* *.gpi