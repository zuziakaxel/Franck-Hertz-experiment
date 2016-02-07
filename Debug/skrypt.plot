reset
#set terminal epslatex size 13cm,9cm color colortext
set terminal png
set output 'wyk3.png'
set grid
set style line 1 linecolor rgb '#314F77' linetype 1 linewidth 2
set xlabel "U [V]"
set ylabel "I względny"
plot "wyniki3.dat" u 1:2 w l ls 1 notitle
#"wyniki.dat" u 1:3 axes x1y2 w l title "v(t)",
