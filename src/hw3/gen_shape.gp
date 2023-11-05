# Store shape_1 in shape_1.dat
set table './output/shape_1.dat'
plot '-'
150 500
200 500
200 550
150 550
150 500
e
unset table
reset

# Store shape_2 in shape_2.dat
set table './output/shape_2.dat'
plot '-'
350 350
550 350
550 450
450 450
450 500
350 500
350 350
e
unset table
reset

# Store shape_3 in shape_3.dat
set table './output/shape_3.dat'
plot '-'
50 350
250 350
250 450
50 450
50 350
e
unset table
reset

# Store shape_4 in shape_4.dat
set table './output/shape_4.dat'
plot '-'
200 200
300 200
300 300
200 300
200 200
e
unset table
reset

# Store shape_5 in shape_5.dat
set table './output/shape_5.dat'
plot '-'
100 100
200 100
200 150
150 150
150 175
100 175
100 100
e
unset table
reset

# Store shape_6 in shape_6.dat
set table './output/shape_6.dat'
plot '-'
400 50
550 50
550 250
450 250
450 150
400 150
400 50
e
unset table
reset

# Store shape_1 shrunked to longest side is 50 in shape_1_shrunked.dat
# X 1
set table './output/shape_1_shrunked.dat'
plot '-'
0 0
50 0
50 50
0 50
0 0
e
unset table
reset

# Store shape_2 shrunked to longest side is 50 in shape_2_shrunked.dat
# X 0.25
set table './output/shape_2_shrunked.dat'
plot '-'
0 0
50 0
50 25
25 25
25 37.5
0 37.5
0 0
e
unset table
reset

# Store shape_3 shrunked to longest side is 50 in shape_3_shrunked.dat
# X 0.25
set table './output/shape_3_shrunked.dat'
plot '-'
0 0
50 0
50 25
0 25
0 0
e
unset table
reset

# Store shape_4 shrunked to longest side is 50 in shape_4_shrunked.dat
# X 0.5
set table './output/shape_4_shrunked.dat'
plot '-'
0 0
50 0
50 50
0 50
0 0
e
unset table
reset

# Store shape_5 shrunked to longest side is 50 in shape_5_shrunked.dat
# X 0.5
set table './output/shape_5_shrunked.dat'
plot '-'
0 0
50 0
50 25
25 25
25 37.5
0 37.5
0 0
e
unset table
reset

# Store shape_6 shrunked to longest side is 50 in shape_6_shrunked.dat
# X 0.25
set table './output/shape_6_shrunked.dat'
plot '-'
0 0
37.5 0
37.5 50
12.5 50
12.5 25
0 25
0 0
e
unset table
reset

# Store shape_6 shrunked and rotated in shape_6_shrunked_rotated.dat
# X 0.25
# R 90 CW
set table './output/shape_6_shrunked_rotated.dat'
plot '-'
0 0
50 0
50 25
25 25
25 37.5
0 37.5
0 0
e
unset table
reset

# Plot shape_1
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_1.png'
set title 'Shape R_1'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [125:225]
set yrange [475:575]
set xtics ('150' 150, '200' 200)
set ytics ('500' 500, '550' 550)
plot './output/shape_1.dat' notitle with lines lw 5
reset

# Plot shape_2
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_2.png'
set title 'Shape R_2'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [325:575]
set yrange [325:525]
plot './output/shape_2.dat' notitle with lines lw 5
reset

# Plot shape_3
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_3.png'
set title 'Shape R_3'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [25:275]
set yrange [325:475]
set ytics ('350' 350, '400' 400, '450' 450)
plot './output/shape_3.dat' notitle with lines lw 5
reset

# Plot shape_4
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_4.png'
set title 'Shape R_4'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [175:325]
set yrange [175:325]
set xtics ('200' 200, '250' 250, '300' 300)
set ytics ('200' 200, '250' 250, '300' 300)
plot './output/shape_4.dat' notitle with lines lw 5
reset

# Plot shape_5
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_5.png'
set title 'Shape R_5'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [75:225]
set yrange [75:200]
set xtics ('100' 100, '150' 150, '200' 200)
set ytics ('100' 100, '125' 125, '150' 150, '175' 175)
plot './output/shape_5.dat' notitle with lines lw 5
reset

# Plot shape_6
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_6.png'
set title 'Shape R_6'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [375:575]
set yrange [25:275]
plot './output/shape_6.dat' notitle with lines lw 5
reset

# Plot shape_1 shrunked to longest side is 50
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_1_shrunked.png'
set title 'Shape R_1 Shrunked to Longest Side is 50'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [-10:60]
set yrange [-10:60]
plot './output/shape_1_shrunked.dat' notitle with lines lw 5
reset

# Plot shape_2 shrunked to longest side is 50
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_2_shrunked.png'
set title 'Shape R_2 Shrunked to Longest Side is 50'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [-10:60]
set yrange [-10:60]
plot './output/shape_2_shrunked.dat' notitle with lines lw 5
reset

# Plot shape_3 shrunked to longest side is 50
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_3_shrunked.png'
set title 'Shape R_3 Shrunked to Longest Side is 50'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [-10:60]
set yrange [-10:60]
plot './output/shape_3_shrunked.dat' notitle with lines lw 5
reset

# Plot shape_4 shrunked to longest side is 50
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_4_shrunked.png'
set title 'Shape R_4 Shrunked to Longest Side is 50'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [-10:60]
set yrange [-10:60]
plot './output/shape_4_shrunked.dat' notitle with lines lw 5
reset

# Plot shape_5 shrunked to longest side is 50
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_5_shrunked.png'
set title 'Shape R_5 Shrunked to Longest Side is 50'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [-10:60]
set yrange [-10:60]
plot './output/shape_5_shrunked.dat' notitle with lines lw 5
reset

# Plot shape_6 shrunked to longest side is 50
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_6_shrunked.png'
set title 'Shape R_6 Shrunked to Longest Side is 50'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [-10:60]
set yrange [-10:60]
plot './output/shape_6_shrunked.dat' notitle with lines lw 5
reset

# Plot shape_6 shrunked and rotated
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set size ratio -1
set output './output/shape_6_shrunked_rotated.png'
set title 'Shape R_6 Shrunked and Rotated'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [-10:60]
set yrange [-10:60]
plot './output/shape_6_shrunked_rotated.dat' notitle with lines lw 5
reset

# Plot the shapes in one figure
set terminal pngcairo size 1080,1080 enhanced font 'Arial,25'
set output './output/shapes.png'
set title '2D Regions for RST Feature Extraction'
set xlabel 'x_1'
set ylabel 'x_2'
set xrange [0:600]
set yrange [0:600]
set label 'R_1' at 160,525
set label 'R_2' at 430,405
set label 'R_3' at 140,400
set label 'R_4' at 240,250
set label 'R_5' at 120,130
set label 'R_6' at 470,120
plot './output/shape_1.dat' notitle with lines lw 5, './output/shape_2.dat' notitle with lines lw 5, './output/shape_3.dat' notitle with lines lw 5, './output/shape_4.dat' notitle with lines lw 5, './output/shape_5.dat' notitle with lines lw 5, './output/shape_6.dat' notitle with lines lw 5
reset
