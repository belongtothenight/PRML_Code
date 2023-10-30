# Execute command
# gnuplot -p .\fig2.gp ; .\output\fig2.png

# save data y # yellow bean
set table './data/fig2_y.dat'
plot '-'
0 3
150 3
300 7
e
unset table
reset session

# save data r # red bean
set table './data/fig2_r.dat'
plot '-'
0 1
150 3
300 1
e
unset table
reset session

# save data g # mung bean
set table './data/fig2_g.dat'
plot '-'
0 2
150 2
300 0
e
unset table
reset session

# save data p # black rice
set table './data/fig2_p.dat'
plot '-'
0 2
150 0
300 0
e
unset table
reset session

# plot
set terminal pngcairo font 'arial,35' size 1920,1080
set output './output/fig2.png'
set title 'Row 3 \& 4 beans distribution (opacity: 0.5)'
set xrange[0:300]
set yrange[0:8]
set xlabel 'How many shakes (times)'
set ylabel 'Count in total (blocks)'
set xtics ('0' 0, '150' 150, '300' 300)
plot './data/fig2_y.dat' title 'yellow bean' with lines lw 5 lt rgb '0x55ffff00', './data/fig2_r.dat' title 'red bean' with lines lw 5 lt rgb '0x55ff0000', './data/fig2_g.dat' title 'mung bean' with lines lw 5 lt rgb '0x55008000', './data/fig2_p.dat' title 'black rice' with lines lw 5 lt rgb '0x55800080'
