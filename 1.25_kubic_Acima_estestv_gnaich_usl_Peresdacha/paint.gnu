set xrange [-5.5:5.5]
set yrange [-5.5:5.5]

plot 'aproxPoints.txt' with points pt 1 linecolor "red" title 'Aprox Points', \
     'realPoints.txt' with points pt 1 linecolor "blue" title 'Real Points', \
     'nodesPoints.txt' with points pt 7 linecolor "black" title 'Real Points'

