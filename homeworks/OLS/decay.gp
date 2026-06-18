set terminal pngcairo size 800,600
set output 'fig_decay.png'

set xlabel "Time (days)"
set ylabel "Activity"
set title "Radioactive decay of ThX"
set grid lw 1 dt 2
set key box

set pointintervalbox 0

plot \
"fit.dat" using 1:3:4 with filledcurves fs solid 1 lc rgb "#767fff" title "Exponential fit band", \
"fit.dat" using 1:2 with lines lc rgb "#000099" lw 2.4 title "Exponential fit", \
"data.txt" using 1:2:3 with yerrorbars lc rgb "#ffd500" pt 7 ps 0.5 lw 1.3 title "Experimental data"
