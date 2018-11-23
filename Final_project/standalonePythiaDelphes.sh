#!/bin/bash

# Setting for ui02 machine 
# Root is not installed
# We run root in cmssw enviroment

export SCRAM_ARCH=slc6_amd64_gcc530
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
source ${VO_CMS_SW_DIR}/cmsset_default.sh
cd /hcp/data/data02/ycyang/ZGammaVBS/20170425/CMSSW_8_0_26_patch1/src
eval `scramv1 runtime -sh`


# Current directory

FirstDir=`pwd`
cd $FirstDir

#Madpgrah home directory

export MG5Dir=/hcp/home/jwkim2/MG5/MG5_aMC_v2_3_3 

# Input file directory
LHEDir=`readlink -f $1`
echo "### Using $LHEDir/unweighted_events.lhe.gz "

# Input file: "*.lhe" checking
if [ ! -f $LHEDir/unweighted_events.lhe.gz ]; then echo "### Error NotFound $LHEDir/unweighted_events.lhe.gz"; exit; fi

# Temporary directory for log data of Pythia and Delphes running
tempDir="saPythiaDelphes${RANDOM}_${RANDOM}"
mkdir -p $tempDir/Cards
mkdir -p $tempDir/Events
cd $tempDir/Events
echo "### Temporary working dir for Pythia and Delphes `pwd` "
cp $LHEDir/unweighted_events.lhe.gz .
gzip -d unweighted_events.lhe.gz 
ls -al unweighted_events.lhe

# Check the pythia_card.dat
if [ -f $LHEDir/../../Cards/pythia_card.dat ]; then
	echo "### Using $LHEDir/../../Cards/pythia_card.dat"
	cp $LHEDir/../../Cards/pythia_card.dat ../Cards/pythia_card.dat
else
	echo "### Using $MG5Dir/Template/LO/Cards/pythia_card_default.dat"
	cp $MG5Dir/Template/LO/Cards/pythia_card_default.dat ../Cards/pythia_card.dat
	ls -al ../Cards/
fi

if [ ! -f ../Cards/pythia_card.dat ]; then echo "### Error Not Found ../Cards/pythia_card.dat"; exit; fi

# Run pythia
# lhe file -> hep file
echo "$MG5Dir/Template/Common/bin/internal/run_pythia $MG5Dir/pythia-pgs/src"
$MG5Dir/Template/Common/bin/internal/run_pythia $MG5Dir/pythia-pgs/src 
ls -al

# Run Delphes
# hep file-> root file
echo "$MG5Dir/Delphes/DelphesSTDHEP $MG5Dir/Delphes/cards/delphes_card_CMS.tcl tag_s_delphes_events.root pythia_events.hep"
$MG5Dir/Delphes/DelphesSTDHEP $MG5Dir/Delphes/cards/delphes_card_CMS.tcl tag_s_delphes_events.root pythia_events.hep >& /dev/null

# Move the essetial files from temp to input directory
mv unweighted_events.lhe     $LHEDir/  
mv beforeveto.tree           $LHEDir/  
mv xsecs.tree                $LHEDir/  
mv pythia_events.hep         $LHEDir/  
mv fort.0                    $LHEDir/  
mv events.tree               $LHEDir/  
mv pythia.done               $LHEDir/  
mv tag_s_delphes_events.root $LHEDir/  

# Final output file check
ls -al $LHEDir/tag_s_delphes_events.root

cd $FirstDir
#rm -rf $tempDir
echo "Done $LHEDir/unweighted_events.lhe.gz To $LHEDir/tag_s_delphes_events.root"



