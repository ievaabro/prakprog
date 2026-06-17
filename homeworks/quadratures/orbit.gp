set terminal svg size 800,600 background "white"

set output "erf_func.svg"
set size square
set title "Errorfunction"
set xlabel "x"
set ylabel "y"

plot \
"erf_data.dat" index 0 using 1:2 with lines lc rgb "#6a0dad" lw 3