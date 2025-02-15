set output "dhrystone-mcs51-size.svg"
set terminal svg size 640,480
set style data lines
set xlabel "revision"
set ylabel "size [B]"
set arrow from 9618, 12845 to 9618, 12795
set label "3.6.0" at 9618, 12845
set arrow from 10233, 13154 to 10233, 13104
set label "3.7.0" at 10233, 13154
set arrow from 10582, 12936 to 10582, 12886
set label "3.8.0" at 10582, 12936
set arrow from 11214, 13673 to 11214, 13573
set label "3.9.0" at 11214, 13673
set arrow from 11533, 13680 to 11533, 13580
set label "4.0.0" at 11533, 13680
set arrow from 12085, 13711 to 12085, 13611
set label "4.1.0" at 12085, 13711
plot "dhrystone-mcs51-sizetable" using 1:4 title "default", "dhrystone-mcs51-sizetable" using 1:2 title "size", "dhrystone-mcs51-sizetable" using 1:3 title "speed"

