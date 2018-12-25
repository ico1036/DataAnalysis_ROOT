#----4lepton 100,000
#./makeHist.exe HtoZZto4l.root  0 0.00127224			100000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/HtoZZto4l/Events/run_*/tag_delphes.root &
#./makeHist.exe BKG_ZZ.root 1 0.020879202			100000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/BKG_ZZ/Events/run_*/tag_delphes.root
#./makeHist.exe BKG4l.root 1 0.02461615231		100000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/BKG4l/Events/run_*/tag_delphes.root


#----4lepton 100,000--- V2
#./makeHist_v2.exe HtoZZto4l_v2.root  0 0.00127224			100000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/HtoZZto4l/Events/run_*/tag_delphes.root &
#./makeHist.exe BKG_ZZ.root 1 0.020879202			100000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/BKG_ZZ/Events/run_*/tag_delphes.root
#./makeHist_v2.exe BKG4l_v2.root 1 0.02461615231		100000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/BKG4l/Events/run_*/tag_delphes.root



#----4lepton 1,000,000
./makeHist_v2.exe HtoZZto4l_more_v2.root  0 0.0012723			1000000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/HtoZZto4l_more/Events/run_*/tag_delphes.root &
./makeHist_v2.exe BKG4l_more_v2.root 1 0.02460380139		1000000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/BKG4l_more/Events/run_*/tag_delphes.root


#----4lepton 10,000 for test
#./makeHist.exe HtoZZto4l_test.root  0 0.0012739 		10000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/HtoZZto4l/Events/run_01/tag_delphes.root &
#./makeHist.exe BKG_ZZ.root 	   1 0.02087858 			10000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/BKG_ZZ/Events/run_01/tag_delphes.root
#./makeHist.exe BKG4l_test.root 1 0.0245630959			10000 /home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/BKG4l/Events/run_01/tag_delphes.root



