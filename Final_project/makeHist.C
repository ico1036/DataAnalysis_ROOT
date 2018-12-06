#include <iostream>
#include "TClonesArray.h"
#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
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
	
	TClonesArray* muTCA = new TClonesArray("Muon");inChain->SetBranchAddress("Muon",&muTCA);
	TClonesArray *muSelTCA =  new TClonesArray("Muon");


	TH1F *h_mass4e 	 = new TH1F("h_mass4e","4eMass",10000,0,1000);
	TH1F *h_mass4m 	 = new TH1F("h_mass4m","4muMass",10000,0,1000);
	TH1F *h_mass2e2m = new TH1F("h_mass2e2m","2e2muMass",10000,0,1000);
	TH1F *h_mass4l 	 = new TH1F("h_mass4l","4lMass",10000,0,1000);

	TH1F *h_mass4e_mat 	 = new TH1F("h_mass4e_mat","4eMass",10000,0,1000);
	TH1F *h_mass4m_mat 	 = new TH1F("h_mass4m_mat","4muMass",10000,0,1000);
	TH1F *h_mass4l_mat 	 = new TH1F("h_mass4l_mat","4lMass",10000,0,1000);


	TH1F *h_elePT = new TH1F("h_elePT","elePT",1000,0,200);
	TH1F *h_ele1PT = new TH1F("h_ele1PT","ele1PT",1000,0,200);
	TH1F *h_ele2PT = new TH1F("h_ele2PT","ele2PT",1000,0,200);
	TH1F *h_ele3PT = new TH1F("h_ele3PT","ele3PT",1000,0,200);
	TH1F *h_ele4PT = new TH1F("h_ele4PT","ele4PT",1000,0,200);
	
	TH1F *h_muPT  = new TH1F("h_muPT" ,"muPT" ,1000,0,200);
	//TH1F *h_mu1PT = new TH1F("h_mu1PT","mu1PT",1000,0,200);
	//TH1F *h_mu2PT = new TH1F("h_mu2PT","mu2PT",1000,0,200);
	//TH1F *h_mu3PT = new TH1F("h_mu3PT","mu3PT",1000,0,200);
	//TH1F *h_mu4PT = new TH1F("h_mu4PT","mu4PT",1000,0,200);
	
	//TH1F *h_l1PT = new TH1F("h_l1PT","l1PT",1000,0,200);
	//TH1F *h_l2PT = new TH1F("h_l2PT","l2PT",1000,0,200);

                                                            
	TH1F *h_eleEta = new TH1F("h_eleEta","eleEta",1000,-6,6);
	TH1F *h_muEta  = new TH1F("h_muEta" ,"muEta" ,1000,-6,6);

	TH1F *h_M12Vec = new TH1F("h_M12Vech","h_M12Vec",1000,0,200);
	TH1F *h_M34Vec = new TH1F("h_M34Vech","h_M34Vec",1000,0,200);
	TH1F *h_M13Vec = new TH1F("h_M13Vech","h_M13Vec",1000,0,200);
	TH1F *h_M24Vec = new TH1F("h_M24Vech","h_M24Vec",1000,0,200);
	TH1F *h_M14Vec = new TH1F("h_M14Vech","h_M14Vec",1000,0,200);
	TH1F *h_M23Vec = new TH1F("h_M23Vech","h_M23Vec",1000,0,200);


	TH1F *h_Z1Mass = new TH1F("Z1Mass","Z1Mass",1000,0,200);
	TH1F *h_Z2Mass = new TH1F("Z2Mass","Z2Mass",1000,0,200);

// Save data information as tree 

	TTree* outTree = new TTree("tree","tree");
    outTree->Branch("nttype", &nttype);
    outTree->Branch("ntxsec", &ntxsec);
    outTree->Branch("ntgenN", &ntgenN);

	int total_event = inChain->GetEntries();
	int per99 		= total_event/99;
	int per100		=0;	

	int	num_4ele   = 0 ;
	int	num_4mu    = 0 ;
	int	num_2e2m   = 0 ;
	
	int num_eletot = 0 ;int num_eleSeltot =0;
	int num_mutot = 0 ;	int num_muSeltot  =0;
	int num_lepcut1 = 0 ;
	int num_lepcut2 = 0 ;
	
	int num_4mu_matching=0;
	int num_4ele_matching=0;

// --Event Loop start
	
	for(int eventLoop=0; eventLoop < total_event; eventLoop++){
		inChain->GetEntry(eventLoop); // load data in tree
		if((eventLoop%per99) ==0) cout << "Run" << per100++ << " %" << endl; // Showing progress 

		eleSelTCA->Clear("C");
		muSelTCA->Clear("C");
	
		//cout << eleTCA->GetEntries() << "  " << muTCA->GetEntries() << endl;
	
	// --Electron selection		
		for(int eleLoop=0; eleLoop < eleTCA->GetEntries(); eleLoop++){
			Electron *elePtr = (Electron*)eleTCA->At(eleLoop);
			
			num_eletot++;		
			
			h_elePT->Fill(elePtr->PT);
			h_eleEta->Fill(elePtr->Eta);

			if(abs(elePtr->Eta) > 2.5) continue;
			if(elePtr->PT < 7 ) continue;
				
			num_eleSeltot++;		
			new((*eleSelTCA)[(int)eleSelTCA->GetEntries()]) Electron(*elePtr);
		
		}// Electron Loop end 
	
	// --Muon selection		
		for(int muLoop=0; muLoop < muTCA->GetEntries(); muLoop++){
			Muon *muPtr = (Muon*)muTCA->At(muLoop);
						
			h_muPT->Fill(muPtr->PT);
			h_muEta->Fill(muPtr->Eta);
			num_mutot++;
			if(abs(muPtr->Eta) > 2.4) continue;
			if(muPtr->PT < 5 ) continue;
			num_muSeltot++;
			new((*muSelTCA)[(int)muSelTCA->GetEntries()]) Muon(*muPtr);
		
		}// Muon Loop end 
	
	



	// --Select Final state leptons
		
		if(eleSelTCA->GetEntries() < 2 && muSelTCA->GetEntries() <2) continue;
		num_lepcut1++;
		if(eleSelTCA->GetEntries() >= 2 && eleSelTCA->GetEntries() <4 && muSelTCA->GetEntries() <2) continue; 
		if(muSelTCA->GetEntries() >=2 && muSelTCA->GetEntries() <4 && eleSelTCA->GetEntries() <2) continue; 
		num_lepcut2++;



	// --4 Electrons	
		if(eleSelTCA->GetEntries() == 4){
		
			Electron* elePtr1 = (Electron*)eleSelTCA->At(0); 
			Electron* elePtr2 = (Electron*)eleSelTCA->At(1); 
			Electron* elePtr3 = (Electron*)eleSelTCA->At(2); 
			Electron* elePtr4 = (Electron*)eleSelTCA->At(3); 
			
			if(elePtr1->Charge+elePtr2->Charge+elePtr3->Charge+elePtr4->Charge!=0) continue;
			num_4ele++;
			
			TLorentzVector ele1Vec = elePtr1->P4();
			TLorentzVector ele2Vec = elePtr2->P4();
			TLorentzVector ele3Vec = elePtr3->P4();
			TLorentzVector ele4Vec = elePtr4->P4();
			TLorentzVector alleVec = ele1Vec+ele2Vec+ele3Vec+ele4Vec;
			
			TLorentzVector M12Vec = ele1Vec+ele2Vec;
			TLorentzVector M34Vec = ele3Vec+ele4Vec;
			TLorentzVector M13Vec = ele1Vec+ele3Vec;
			TLorentzVector M24Vec = ele2Vec+ele4Vec;
			TLorentzVector M14Vec = ele1Vec+ele4Vec;
			TLorentzVector M23Vec = ele2Vec+ele3Vec;
			
			h_ele1PT->Fill(ele1Vec.Pt());	
			h_ele2PT->Fill(ele2Vec.Pt());
			h_ele3PT->Fill(ele3Vec.Pt());
			h_ele4PT->Fill(ele4Vec.Pt());
			
			h_M12Vec->Fill(M12Vec.M());
        	h_M34Vec->Fill(M34Vec.M());
        	h_M13Vec->Fill(M13Vec.M());
        	h_M24Vec->Fill(M24Vec.M());
        	h_M14Vec->Fill(M14Vec.M());
        	h_M23Vec->Fill(M23Vec.M());
			h_mass4e->Fill(alleVec.M());
  	
	// --Matching opposite charged two leptons		
			if(elePtr1->Charge+elePtr2->Charge !=0 || elePtr3->Charge+elePtr4->Charge!=0) continue;
			num_4ele_matching++;
			
			TLorentzVector M12Z1Vec;
			TLorentzVector M12Z2Vec;
			TLorentzVector M34Z1Vec;
			TLorentzVector M34Z2Vec;
	
		
		if(M12Vec.M() > 50 && ele1Vec.Pt() > 20 && ele2Vec.Pt() >10){
			M12Z1Vec = M12Vec;
		}else{
			M12Z2Vec = M12Vec;
		}
		
		if(M34Vec.M() > 50 && ele3Vec.Pt() > 20 && ele4Vec.Pt() >10){
			 M34Z1Vec = M34Vec;
		}else{
			 M34Z2Vec = M34Vec;
		}
	
			
		TLorentzVector Z1Vec = M12Z1Vec+M34Z1Vec;
		TLorentzVector Z2Vec = M12Z2Vec+M34Z2Vec;

		if(Z1Vec.M() < 40 || Z1Vec.M() > 120) continue;		
		if(Z2Vec.M() < 12 || Z2Vec.M() > 120) continue;		
			
		TLorentzVector Z1Z2Vec = Z1Vec + Z2Vec;
		h_mass4e_mat->Fill(Z1Z2Vec.M());


			h_Z1Mass->Fill(Z1Vec.M());
	    	h_Z2Mass->Fill(Z2Vec.M());
		
		}
	// --4 Muons	
		if(muSelTCA->GetEntries() == 4){

		Muon* muPtr1 = (Muon*)muSelTCA->At(0); 
		Muon* muPtr2 = (Muon*)muSelTCA->At(1); 
		Muon* muPtr3 = (Muon*)muSelTCA->At(2); 
		Muon* muPtr4 = (Muon*)muSelTCA->At(3); 

		if(muPtr1->Charge+muPtr2->Charge+muPtr3->Charge+muPtr4->Charge!=0) continue;
			num_4mu++;
			
			TLorentzVector mu1Vec = muPtr1->P4();
			TLorentzVector mu2Vec = muPtr2->P4();
			TLorentzVector mu3Vec = muPtr3->P4();
			TLorentzVector mu4Vec = muPtr4->P4();
	
			TLorentzVector allmVec = mu1Vec+mu2Vec+mu3Vec+mu4Vec;		
			
			TLorentzVector M12Vec = mu1Vec+mu2Vec;
			TLorentzVector M34Vec = mu3Vec+mu4Vec;
			//TLorentzVector M13Vec = mu1Vec+mu3Vec;
			//TLorentzVector M24Vec = mu2Vec+mu4Vec;
			//TLorentzVector M14Vec = mu1Vec+mu4Vec;
			//TLorentzVector M23Vec = mu2Vec+mu3Vec;
			
			//h_mu1PT->Fill(mu1Vec.Pt());	
			//h_mu2PT->Fill(mu2Vec.Pt());
			//h_mu3PT->Fill(mu3Vec.Pt());
			//h_mu4PT->Fill(mu4Vec.Pt());
			h_mass4m->Fill(allmVec.M());



	// --Matching opposite charged two leptons		
	if(muPtr1->Charge+muPtr2->Charge !=0 || muPtr3->Charge+muPtr4->Charge!=0) continue;
			num_4mu_matching++;
		
			TLorentzVector M12Z1Vec;
			TLorentzVector M12Z2Vec;
			TLorentzVector M34Z1Vec;
			TLorentzVector M34Z2Vec;
	
		
		if(M12Vec.M() > 50 && mu1Vec.Pt() > 20 && mu2Vec.Pt() >10){
			M12Z1Vec = M12Vec;
		}else{
			M12Z2Vec = M12Vec;
		}
		
		if(M34Vec.M() > 50 && mu3Vec.Pt() > 20 && mu4Vec.Pt() >10){
			 M34Z1Vec = M34Vec;
		}else{
			 M34Z2Vec = M34Vec;
		}
	
			
		TLorentzVector Z1Vec = M12Z1Vec+M34Z1Vec;
		TLorentzVector Z2Vec = M12Z2Vec+M34Z2Vec;

		if(Z1Vec.M() < 40 || Z1Vec.M() > 120) continue;		
		if(Z2Vec.M() < 12 || Z2Vec.M() > 120) continue;		
		
		TLorentzVector Z1Z2Vec = Z1Vec + Z2Vec;
		h_mass4m_mat->Fill(Z1Z2Vec.M());

		h_Z1Mass->Fill(Z1Vec.M());
	    h_Z2Mass->Fill(Z2Vec.M());
				
		}



	// --2 Electrons and 2 Muons
		if(muSelTCA->GetEntries() == 2 && eleSelTCA->GetEntries() == 2){

		Electron* onelePtr1 = (Electron*)eleSelTCA->At(0); 
		Electron* onelePtr2 = (Electron*)eleSelTCA->At(1); 
		Muon* onmuPtr1 = (Muon*)muSelTCA->At(0); 
		Muon* onmuPtr2 = (Muon*)muSelTCA->At(1); 

		if(onelePtr1->Charge+onelePtr2->Charge+onmuPtr1->Charge+onmuPtr2->Charge!=0)continue;
		if(onelePtr1->Charge+onelePtr2->Charge !=0 || onmuPtr1->Charge+onmuPtr2->Charge!=0) continue;
		num_2e2m++;
		TLorentzVector onele1Vec = onelePtr1->P4();
		TLorentzVector onele2Vec = onelePtr2->P4();
		TLorentzVector onmu1Vec = onmuPtr1->P4();
		TLorentzVector onmu2Vec = onmuPtr2->P4();

		TLorentzVector allVec = onele1Vec+onele2Vec+onmu1Vec+onmu2Vec;
		TLorentzVector eeVec = onele1Vec+onele2Vec;
		TLorentzVector mmVec = onmu1Vec+onmu2Vec;
		TLorentzVector eeZ1Vec ;
		TLorentzVector mmZ1Vec ;
		TLorentzVector eeZ2Vec ;
		TLorentzVector mmZ2Vec ;
		
		
		if(eeVec.M() > 50 && onele1Vec.Pt() > 20 && onele2Vec.Pt() >10){
			eeZ1Vec = eeVec;
		}else{
			eeZ2Vec = eeVec;
		}
		
		if(mmVec.M() > 50 && onmu1Vec.Pt() > 20 && onmu2Vec.Pt() >10){
			 mmZ1Vec = mmVec;
		}else{
			 mmZ2Vec = mmVec;
		}
		
		
		TLorentzVector Z1Vec = eeZ1Vec+mmZ1Vec;
		TLorentzVector Z2Vec = eeZ2Vec+mmZ2Vec;

		if(Z1Vec.M() < 40 || Z1Vec.M() > 120) continue;		
		if(Z2Vec.M() < 12 || Z2Vec.M() > 120) continue;		

		h_Z1Mass->Fill(Z1Vec.M());
    	h_Z2Mass->Fill(Z2Vec.M());
		
		//h_l1PT->Fill(Z1Vec.Pt());
		//h_l2PT->Fill(Z2Vec.Pt());

		TLorentzVector Z1Z2Vec = Z1Vec + Z2Vec;
		h_mass2e2m->Fill(Z1Z2Vec.M());
		}



outTree->Fill();

	} // Event Loop end
/*	
	TCanvas *c1 = new TCanvas();	
	TCanvas *c2 = new TCanvas();	
	TCanvas *c3 = new TCanvas();	
	TCanvas *c4 = new TCanvas();	

	//c1->Divide(2,1);
	//c1->cd(1); h_Z1Mass->Draw();
	//c1->cd(2); h_Z2Mass->Draw();
	
//	
//
	c1->Divide(2,2);
	c1->cd(1); h_ele1PT->Draw();
	c1->cd(2); h_ele2PT->Draw();
	c1->cd(3); h_ele3PT->Draw();
	c1->cd(4); h_ele4PT->Draw();
	
	c2->Divide(2,1);
	c2->cd(1); h_M12Vec->Draw();	
	c2->cd(2); h_M34Vec->Draw();	
	
	c3->Divide(2,1);
	c3->cd(1); h_M13Vec->Draw();	
	c3->cd(2); h_M24Vec->Draw();	
	
	c4->Divide(2,1);
	c4->cd(1); h_M14Vec->Draw();	
	c4->cd(2); h_M23Vec->Draw();	


	//c1->Print("RECO_Z1Z2Mass.png");
	
	c1->Print("elePT.png");
	c2->Print("M12M34.png");
	c3->Print("M13M24.png");
	c4->Print("M14M23.png");
*/
	//cout << "Total Event: " << total_event << endl;
	
	//cout << " ##########	num_eletot	" <<	num_eletot << endl;
	//cout << " ##########	num_mutot	" <<	num_mutot  << endl;
	//cout << " ##########	num_lepcut1	" <<	num_lepcut1 << endl;
	//cout << " ##########	num_eleSeltot"<<	num_eleSeltot << endl;
	//cout << " ##########	num_muSeltot "<<	num_muSeltot << endl;
	//cout << " ##########	num_lepcut2	" <<	num_lepcut2 << endl;

	cout << " ##########	num_4ele  	" <<	num_4ele   << endl;
	cout << " ##########	ele_matching " <<	num_4ele_matching   << endl;
	cout << " ##########	num_4mu   	" <<	num_4mu    << endl;
	cout << " ##########	mu_mathcing  " <<	num_4mu_matching    << endl;
	cout << " ##########	num_2e2m  	" <<	num_2e2m   << endl;
	
	h_mass4l->Add(h_mass2e2m);
	h_mass4l->Add(h_mass4m);
	h_mass4l->Add(h_mass4e);

	h_mass4l_mat->Add(h_mass2e2m);
	h_mass4l_mat->Add(h_mass4m_mat);
	h_mass4l_mat->Add(h_mass4e_mat);
	outFile->Write();

	return 0;

}


	




