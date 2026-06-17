set terminal pngcairo size 800,600
set output "wf.png"

set xlabel "x"
set ylabel "y"

set grid

plot \
    "wf.dat" using 1:2 with lines title "Wavefunction"