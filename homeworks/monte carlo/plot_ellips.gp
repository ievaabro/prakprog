set terminal pngcairo size 800,600
set output "ellipsoid.png"

set logscale xy

set xlabel "N"
set ylabel "Error"

set grid

plot \
    "ellipsoid.dat" using 1:2 with linespoints title "Estimated error", \
    "ellipsoid.dat" using 1:3 with linespoints title "Actual error", \
    1/sqrt(x) title "1/sqrt(N)"