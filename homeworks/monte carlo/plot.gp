set terminal pngcairo size 800,600
set output "mc.png"

set logscale xy

set xlabel "N"
set ylabel "Error"

set grid

plot \
    "mc.dat" using 1:2 with linespoints lw 3 lc rgb '#ccccff' title "Estimated error", \
    "mc.dat" using 1:3 with linespoints lw 3 lc rgb '#5d5dff' title "Actual error", \
    1/sqrt(x) with lines lw 3 lc rgb '#ee9aff' title "1/sqrt(N)"