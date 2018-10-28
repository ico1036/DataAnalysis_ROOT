// Homework No2
//Make a program to produce a histogram (TH1D) by picking up random
//numbers [0, 10] in the probability density function (TF1) of the Gaussian
//distribution with m=5 and s=1 in the ROOT framework. Then compare the
//histogram with the probability function for the Gaussian distribution.
//(Total number of events, n=10000)

#include <iostream>
using namespace std;
using namespace TMath;

void HW_N02() {

	TCanvas *c = new TCanvas("c","c",1500,1500);
	// Set standard deviation and mean value
	double sigma=1;
	double mean=5;
	
	// Define Gauss function 
	TH1D *h1 = new TH1D("h1","h1",10000,0,10);
	TF1 *f_gaus = new TF1("gaus","(1/sqrt(2*Pi()*[0]*[0]))*Exp(-1*((x-[1])*(x-[1]))/(2*[0]*[0]))",0,10);
		f_gaus->SetParameters(sigma,mean);

	// Produce random number through gauss distribution
	// Fill histogram
	for(int i=0; i<10000; i++){
		h1->Fill(f_gaus->GetRandom());
	}
	
	
	gStyle->SetOptStat(1111111);
	f_gaus->SetTitle("Gaus");

	//Normalize histogram
	double norm=1.0/h1->Integral();
	h1->Scale(norm);	
	
	h1->Rebin(1000);
	h1->Draw("hist");
	h1->SetMaximum(0.5);
	h1->SetTitle("Gauss Distribution");
	//Overlap gauss distribution function on the histogram
	f_gaus->Draw("same");
	c->Print("HW_N02.png");

}
