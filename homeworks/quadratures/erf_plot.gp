set terminal svg size 800,600 background "white"

set output "erf_func.svg"
set size square
set title "Errorfunction"
set xlabel "x"
set ylabel "y"

plot \
"erf_data.dat" index 0 using 1:2 with lines lc rgb "#6a0dad" lw 3 title "Numrical", \
"erf_data.dat" index 0 using 1:3 with lines lc rgb "#d77f21" lw 3 dt 2 title "Reference"

set output "erf_compare.svg"
set logscale xy
set xtics rotate by 45 right
set size square
set title "Accuracy of Errorfunction"
set xlabel "acc"
set ylabel "absolute error"

plot \
"erf_convergence.dat" index 0 using 1:2 with lines lc rgb "#6a0dad" lw 3 title "Convergence"