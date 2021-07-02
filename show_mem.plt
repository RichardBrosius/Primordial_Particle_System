set term png small size 800,600
set output "mem-graph.png"

set ylabel "VSZ"


set ytics nomirror


set yrange [0:*]


plot "mem.log" using 2 with lines axes x1y1 title "Memory", \
