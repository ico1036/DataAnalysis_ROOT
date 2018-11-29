#include <iostream>
#include "TClonesArray.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "classes/DelphesClasses.h"


using namespace std;
int main(int argc, char** argv) {


     
	TFile* outFile = new TFile(argv[1],"recreate");
	TChain* inChain = new TChain("Delphes");

	int    nttype = atoi(argv[2]); // data type: 0-> signal, others->background
	double ntxsec = atof(argv[3]); // cross section
	double ntgenN = atof(argv[4]); // number of generated data

// This allows to deal with multiple input data

	for(int iFile = 5; iFile<argc; iFile++) {
        cout << "### InFile " << iFile-4 << " " << argv[iFile] << endl;
        inChain->Add(argv[iFile]);
    }

	TClonesArray* eleTCA = new TClonesArray("Electron");inChain->SetBranchAddress("Electron",&eleTCA);
	TClonesArray *eleSelTCA =  new TClonesArray("Electron");

	TH1F *h_mass4e = new TH1F("h_mass4e","ElectronsMass",10000,0,1000);

// Save data information as tree 

	TTree* outTree = new TTree("tree","tree");
    outTree->Branch("nttype", &nttype);
    outTree->Branch("ntxsec", &ntxsec);
    outTree->Branch("ntgenN", &ntgenN);

	int total_event = inChain->GetEntries();
	int per99 		= total_event/99;
	int per100		=0;	

// Event Loop start

	for(int eventLoop=0; eventLoop < total_event; eventLoop++){
		inChain->GetEntry(eventLoop); // load data in tree
		if((eventLoop%per99) ==0) cout << "Run" << per100++ << " %" << endl; // Showing progress 

		eleSelTCA->Clear("C");
				
		for(int eleLoop=0; eleLoop < eleTCA->GetEntries(); eleLoop++){
			Electron *elePtr = (Electron*)eleTCA->At(eleLoop);
		
			//if(abs(elePtr->Eta) > 2.47) continue;
			//if(elePtr->PT < 20 ) continue;
			new((*eleSelTCA)[(int)eleSelTCA->GetEntries()]) Electron(*elePtr);
		
		}// Electron Loop end 

		
		if(eleSelTCA->GetEntries() !=4) continue;
		Electron* elePtr1 = (Electron*)eleSelTCA->At(0); 
		Electron* elePtr2 = (Electron*)eleSelTCA->At(1); 
		Electron* elePtr3 = (Electron*)eleSelTCA->At(2); 
		Electron* elePtr4 = (Electron*)eleSelTCA->At(3); 

		TLorentzVector ele1Vec = elePtr1->P4();
		TLorentzVector ele2Vec = elePtr2->P4();
		TLorentzVector ele3Vec = elePtr3->P4();
		TLorentzVector ele4Vec = elePtr4->P4();

		TLorentzVector alleVec = ele1Vec+ele2Vec+ele3Vec+ele4Vec;
		h_mass4e->Fill(alleVec.M());
		outTree->Fill();

	} // Event Loop end
	
	outFile->Write();
	return 0;

}


	




