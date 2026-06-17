set terminal svg size 800,600 background "white"

set output "dif_eq.svg"
set title "Solving differential equation"
set xlabel "x"
set ylabel "y"
plot "out.data" using 1:2 with lines lw 3 title "numerical", \
     "out.data" using 1:3 with lines lw 3 title "exact"

set output "example_pend.svg"
set title "Solving example pendulum"
set xlabel "x"
set ylabel "y"
plot "pendulum.data" using 1:2 with lines lw 3 title "theta(t)", \
     "pendulum.data" using 1:3 with lines lw 3 title "omega(t)"

set output "orbit.svg"
set size square
set title "Orbits"
set xlabel "x"
set ylabel "y"

plot \
"orbit.data" index 0 using (1/$2)*cos($1):(1/$2)*sin($1) with lines title "Circular", \
"orbit.data" index 1 using (1/$2)*cos($1):(1/$2)*sin($1) with lines title "Relativistic", \
"orbit.data" index 2 using (1/$2)*cos($1):(1/$2)*sin($1) with lines title "Elliptical"