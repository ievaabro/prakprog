set terminal pdfcairo enhanced font "Times,12" size 10cm,7cm
set output 'fig_decay.pdf'

set xlabel "Time (days)"
set ylabel "Activity"
set title "Radioactive decay of ThX"
set grid lw 1 dt 2
set key box

set pointintervalbox 0

plot \
"fit.dat" using 1:3:4 with filledcurves fs solid 1 lc rgb "#e72bd7" title "Exponential fit band", \
"fit.dat" using 1:2 with lines lc rgb "#6A0DAD" lw 2.4 title "Exponential fit", \
"data.txt" using 1:2:3 with yerrorbars lc rgb "#cb730e" pt 7 ps 0.5 lw 1.3 title "Experimental data"
