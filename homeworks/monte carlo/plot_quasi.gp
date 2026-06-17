set terminal pngcairo size 800,600
set output "quasi.png"

set logscale xy

set xlabel "N"
set ylabel "Error"

set grid

plot \
    "compare.dat" using 1:2 with linespoints title "LC error", \
    "compare.dat" using 1:3 with linespoints title "mt19937 error", \
    "compare.dat" using 1:4 with linespoints title "quasi-MC"