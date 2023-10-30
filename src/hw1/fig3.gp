# Execute command
# gnuplot -p .\fig3.gp ; .\output\fig3.png

# save data y # yellow bean
set table './data/fig3_y.dat'
plot '-'
0 2
150 0
300 0
e
unset table
reset session

# save data r # red bean
set table './data/fig3_r.dat'
plot '-'
0 2
150 3
300 4
e
unset table
reset session

# save data g # mung bean
set table './data/fig3_g.dat'
plot '-'
0 4
150 4
300 4
e
unset table
reset session

# save data p # black rice
set table './data/fig3_p.dat'
plot '-'
0 0
150 1
300 0
e
unset table
reset session

# plot
set terminal pngcairo font 'arial,35' size 1920,1080
set output './output/fig3.png'
set title 'Row 5 \& 6 beans distribution (opacity: 0.5)'
set xrange[0:300]
set yrange[0:8]
set xlabel 'How many shakes (times)'
set ylabel 'Count in total (blocks)'
set xtics ('0' 0, '150' 150, '300' 300)
plot './data/fig3_y.dat' title 'yellow bean' with lines lw 5 lt rgb '0x55ffff00', './data/fig3_r.dat' title 'red bean' with lines lw 5 lt rgb '0x55ff0000', './data/fig3_g.dat' title 'mung bean' with lines lw 5 lt rgb '0x55008000', './data/fig3_p.dat' title 'black rice' with lines lw 5 lt rgb '0x55800080'
