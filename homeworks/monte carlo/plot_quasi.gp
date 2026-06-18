set terminal pngcairo size 800,600
set output "quasi.png"

set logscale xy

set xlabel "N"
set ylabel "Error"

set grid

plot \
    "compare.dat" using 1:2 with linespoints lw 3 lc rgb '#ffccfd' title "LC error", \
    "compare.dat" using 1:3 with linespoints lw 3 lc rgb '#ff05ee' title "mt19937 error", \
    "compare.dat" using 1:4 with linespoints lw 3 lc rgb '#5900ff' title "quasi-MC"