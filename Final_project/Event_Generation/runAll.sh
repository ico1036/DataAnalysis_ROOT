#!/bin/bash


for i in `seq 2 9`
do

./runDelphes_withPythia8.sh HtoZZto4l/Events/run_0$i 
./runDelphes_withPythia8.sh BKG4l/Events/run_0$i 
done

./runDelphes_withPythia8.sh HtoZZto4l/Events/run_10 
./runDelphes_withPythia8.sh BKG4l/Events/run_10 



