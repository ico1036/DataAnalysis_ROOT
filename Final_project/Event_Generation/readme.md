### Madgraph  
#### ex) higgs to 4 electrons  
> ./bin/mg5_aMC  
> import heft  
> generate p p > h, (h > z e+ e-, z > e+ e-)  
---
### Pythia8 with Delphes  
1. You need to edit cmnd file -> edit the location of your lhe file  
2. run DelphesPythia8 as followings:  
>./DelphesPythia8 path~/delphes_card_CMS.tcl config.cmnd output.root  
  
  
---
### Simple Analysis ( Generator level: ExRootAnalysis )  
#### This is example for draw the Electron PT  
> root
> gSystem->Load("lib/libExRootAnalysis.so");
> TFile::Open("Yourfile.root");
> LHEF->Draw("Particle.PT","Particle.PID==11");
---
### Simple Analysis ( Detector level: Delphes )  
#### This is example for draw the Electron PT  
> root delphes_output_file.root
> Delphes->Draw("Particle.PT","Particle.PID == 11")



