set terminal pngcairo size 800,600
set output "nnA.png"

set xlabel "x"
set ylabel "y"
set title "Artificial Neural Network assignment A"

set grid

plot \
'ann.data' using 1:2 with lines lw 3 lc rgb '#ccccff' title 'true', \
'ann.data' using 1:3 with lines lw 2 lc rgb '#000099' dt 2 title 'ann'

set terminal pngcairo size 800,600
set output "nnB.png"

set xlabel "x" font ",20"
set ylabel "Function / Antiderivative" font ",20"
set y2label "Derivatives" font ",20"

set xrange [-1:1]
set yrange [-1:1]
set y2range [-30:30]
set title "Artificial Neural Network assignment B"

set ytics nomirror
set y2tics

set border linewidth 1.5
set tics scale 0.75
set grid lw 1 dt 2

plot \
'ann_opgB.data' using 1:2 with lines lw 3 lc rgb '#ccccff' title 'true', \
'ann_opgB.data' using 1:3 with lines lw 2 lc rgb '#000099' dt 2 title 'ann', \
'ann_opgB.data' using 1:4 axes x1y2 with lines lw 3 lc rgb '#ff99ff' dt 3 title 'first derivative (ann)', \
'ann_opgB.data' using 1:5 axes x1y2 with lines lw 3 lc rgb '#cc00cc' dt 2 title 'second derivative (ann)', \
'ann_opgB.data' using 1:6 with lines lw 3 lc rgb '#ff007f' title 'integrant (ann)'