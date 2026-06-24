set terminal pngcairo size 900,600
set output "lu_vs_qr.png"

set xlabel "Matrix size N"
set ylabel "Time (seconds)"
set title "LU vs QR complexity comparison"


set logscale xy


f(x)=a*x**3
g(x)=b*x**3

fit f(x) "lu.times.data" via a
fit g(x) "qr.times.data" via b

plot \
  "lu.times.data" w p title "LU", \
  "qr.times.data" w p title "QR", \
  f(x) with lines lc rgb "#fc66ff" title sprintf("LU fit %.3e N^3",a), \
  g(x) with lines lc rgb "#5fb4ff" title sprintf("QR fit %.3e N^3",b)