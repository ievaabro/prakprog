set terminal pngcairo size 800,600
set output 'fig_waves.png'

set xlabel "r (Bohr radii)"
set ylabel "f(r)"
set grid lw 1 dt 2
set key box

set samples 500   # smoother analytic curve

plot "wavefunction.dat" using 1:2 with lines lw 2 lc rgb "#6A0DAD" title "Ground state", \
     "wavefunction.dat" using 1:3 with lines lw 2 dt 2 lc rgb "#E67E22" title "1st excited", \
     "wavefunction.dat" using 1:4 with lines lw 2 dt 3 lc rgb "#E91E63" title "2nd excited", \
     2*x*exp(-x) with lines lw 2 dt 4 lc rgb "#F1C40F" title "Exact ground state"