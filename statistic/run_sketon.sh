
#for i in `seq 1 9`
#do
#
#root << EOF
#.L skeleton.C++
#Significance_Optimization(5.$i)
#.q
#EOF
#done


root << EOF
.L skeleton.C++
Significance_Optimization(5)
Significance_Optimization(6)
.q
EOF
