set terminal pdfcairo enhanced font "Times,12" size 10cm,7cm
set output 'fig_dr.pdf'

set xlabel "Δr"
set ylabel "E₀ (ground state energy)"
set title "Convergence vs Δr (rmax fixed)"

set grid lw 1 dt 2
set key box

set samples 500

plot "energy_vs_dr.dat" using 1:2 with linespoints lw 2 pt 7 lc rgb "#6A0DAD" title "Numerical", \
     -0.5 with lines lw 2 dt 4 lc rgb "#F1C40F" title "Exact (-0.5)"