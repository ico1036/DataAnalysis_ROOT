#Locate this file in Delphes main directory

############### Set input path

filename=$1
fullpath="/home/jkim/Generator/MG5_aMC_v2_6_4/Higss2z/$filename"


############### Find lhe file

if [! -f $fullpath/unweighted_events.lhe.gz]; then echo '### No LHEfile found'; exit; fi
gzip -d $fullpath/unweighted_events.lhe.gz
ls $fullpath/unweighted_events.lhe

############### Make temporary directory

tempdir="pydelphes_tmp${RANDOM}_${RANDOM}"
mkdir $tempdir
cd $tempdir

############### Write config.cmnd file

cat << EOF > config.cmnd
! 1) Settings used in the main program.

Main:numberOfEvents = 10000            ! number of events to generate
#Main:timesAllowErrors = 3          ! how many aborts before run stops

! 2) Settings related to output in init(), next() and stat().

Init:showChangedSettings = on      ! list changed settings
Init:showChangedParticleData = off ! list changed particle data
Next:numberCount = 200             ! print message every n events
Next:numberShowInfo = 1            ! print event information n times
Next:numberShowProcess = 1         ! print process record n times
Next:numberShowEvent = 0           ! print event record n times

! 3) Set the input LHE file

Beams:frameType = 4
Beams:LHEF = $fullpath/unweighted_events.lhe
EOF

############### Run DelphesPythia8 

../DelphesPythia8 ../cards/delphes_card_CMS.tcl config.cmnd tag_delphes.root
cp tag_delphes.root $fullpath
cd ..
rm -rf $tempdir

