set terminal pngcairo size 800,600
set output "higgs.png"

set xlabel "Energy E [GeV]"
set ylabel "Signal"
set title "Higgs Breit-Wigner fit"

set grid

plot \
    "higgsdata.txt" using 1:2:3 with yerrorbars lc rgb '#767fff' title "Data", \
    "higgs_fit.dat" using 1:2 with lines lw 2 lc rgb '#ff99ff'  title "Fit"