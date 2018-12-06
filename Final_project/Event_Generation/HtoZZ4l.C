#define HtoZZ4l_cxx
#include "HtoZZ4l.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void HtoZZ4l::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
	
	TH1F *h1 = new TH1F("Z1mass","Z1",10000,0,200);
	TH1F *h2 = new TH1F("Z2mass","Z2",10000,0,200);
	
	h1->SetTitle("Z1");
	h2->SetTitle("Z2");



	// --EventLoop start
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   	
		if(Particle_size != 8){

         double Z1=  sqrt(2*Particle_PT[5]*Particle_PT[6]*(cosh(Particle_Eta[5]-Particle_Eta[6])-cos(Particle_Phi[5]-Particle_Phi[6])));
         double Z2=  sqrt(2*Particle_PT[7]*Particle_PT[8]*(cosh(Particle_Eta[7]-Particle_Eta[8])-cos(Particle_Phi[7]-Particle_Phi[8])));
         h1->Fill(Z1);
         h2->Fill(Z2);
      }else{

         double Z1=  sqrt(2*Particle_PT[4]*Particle_PT[5]*(cosh(Particle_Eta[4]-Particle_Eta[5])-cos(Particle_Phi[4]-Particle_Phi[5])));
         double Z2=  sqrt(2*Particle_PT[6]*Particle_PT[7]*(cosh(Particle_Eta[6]-Particle_Eta[7])-cos(Particle_Phi[6]-Particle_Phi[7])));
         h1->Fill(Z1);
         h2->Fill(Z2);
		}
	} // EventLoop End
	
	TCanvas *c = new TCanvas();
	c->Divide(2,1);
	c->cd(1);	h1->Draw();
	c->cd(2);	h2->Draw();
	
	c->Print("GenLevel_Z1Z2.png");
}
