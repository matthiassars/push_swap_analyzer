reset session
set terminal svg enhanced background rgb "#FFFFFF" font "Lato"
set xrange [1:1024]
set yrange [0:1]
set autoscale z
set border behind
set ticslevel 0
set xlabel "# numbers"
set ylabel "disorder"
set zlabel "# operations" offset 1.5,0
set datafile separator ","

set output "plot1.svg"

set hidden3d
set view 60, 60

splot \
	"data.csv" using 1:2:($3!=$6 ? $3 : NaN) with points pt 7 ps .15 lc rgb "#BB00BB" notitle, \
	"data.csv" using 1:2:($4!=$6 && $4!=$3 ? $4 : NaN) with points pt 7 ps .15 lc rgb "#00BBBB" notitle, \
	"data.csv" using 1:2:($5!=$6 && $4!=$3 && $5!=$4? $5 : NaN) with points pt 7 ps .15 lc rgb "#BBBB00" notitle, \
	"data.csv" using 1:2:($3==$6 ? $3 : NaN) with points pt 7 ps .3 lc rgb "#BB00BB" title "simple", \
	"data.csv" using 1:2:($4==$6 && $4!=$3 ? $4 : NaN) with points pt 7 ps .3 lc rgb "#00BBBB" title "medium", \
	"data.csv" using 1:2:($5==$6 && $4!=$3 && $5!=$4? $5 : NaN) with points pt 7 ps .3 lc rgb "#BBBB00" title "complex"

###############################################################################

reset session
set terminal svg enhanced background rgb "#FFFFFF" font "Lato"
set xrange [1:1024]
set yrange [0:1]
set autoscale z
set border behind
set ticslevel 0
set xlabel "# numbers"
set ylabel "disorder"
set zlabel "# operations" offset 1.5,-1
set datafile separator ","

set output "plot2.svg"

set key top left

set hidden3d
set view 60, 300

set zrange [0:20000]

splot \
	"data.csv" using 1:2:($3!=$6 ? $3 : NaN) with points pt 7 ps .15 lc rgb "#BB00BB" notitle, \
	"data.csv" using 1:2:($4!=$6 && $4!=$3 ? $4 : NaN) with points pt 7 ps .15 lc rgb "#00BBBB" notitle, \
	"data.csv" using 1:2:($5!=$6 && $4!=$3 && $5!=$4? $5 : NaN) with points pt 7 ps .15 lc rgb "#BBBB00" notitle, \
	"data.csv" using 1:2:($3==$6 ? $3 : NaN) with points pt 7 ps .3 lc rgb "#BB00BB" title "simple", \
	"data.csv" using 1:2:($4==$6 && $4!=$3 ? $4 : NaN) with points pt 7 ps .3 lc rgb "#00BBBB" title "medium", \
	"data.csv" using 1:2:($5==$6 && $4!=$3 && $5!=$4? $5 : NaN) with points pt 7 ps .3 lc rgb "#BBBB00" title "complex"

###############################################################################

reset session
set terminal svg enhanced background rgb "#FFFFFF" font "Lato"
set xrange [1:1024]
set yrange [0:1]
set border behind
set xlabel "# numbers"
set ylabel "disorder"
set datafile separator ","

set output "plot3.svg"

unset colorbox

scale = 42
set palette defined ( \
  0 "#BB00BB", \
  2 * scale "#00BBBB", \
  4 * scale "#BBBB00" \
)

get_min(z1, z2, z3) = (z1 <= z2 && z1 <= z3) ? 1 : (z2 <= z3) ? 2 : 3
min(x, y) = (x < y) ? x : y
max(x, y) = (x > y) ? x : y
map_col(z1, z2, z3) = \
	(get_min(z1, z2, z3) == 1) ? \
		scale - min(min(z2, z3) - z1, scale) : \
	(get_min(z1, z2, z3) == 2) ? \
		((z1 <= z3) ? \
			scale + min(z1 - z2, scale) : \
			3 * scale - min(z3 - z2, scale) \
	    ) : \
		3 * scale + min(min(z1, z2) - z3, scale)

plot \
	"data.csv" using 1:2:(map_col($3, $4, $5)) with points pt 7 ps .5 lc palette notitle

###############################################################################

reset session
set terminal svg enhanced background rgb "#FFFFFF" font "Lato"
set xrange [1:1024]
set autoscale y
set border behind
set xlabel "# numbers"
set ylabel "# operations"
set datafile separator ","

set output "plot4.svg"

set key top left
set ticslevel 0
set logscale xy

plot \
	"data.csv" using 1:3 with points pt 7 ps .2 lc rgb "#BB00BB" title "simple", \
	"data.csv" using 1:4 with points pt 7 ps .2 lc rgb "#00BBBB" title "medium", \
	"data.csv" using 1:5 with points pt 7 ps .2 lc rgb "#BBBB00" title "complex", \
	"data.csv" using 1:6 with points pt 7 ps .1 lc rgb "#000000" title "adaptive"
