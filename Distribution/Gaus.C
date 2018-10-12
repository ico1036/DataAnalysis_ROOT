#include <iostream>
using namespace std;
using namespace TMath;

void Gaus() {

	double sigma=1;
	double mean=5;
	TH1D *h1 = new TH1D("h1","h1",10000,0,10);
	TF1 *f_gaus = new TF1("gaus","(1/sqrt(2*Pi()*[0]*[0]))*Exp(-1*((x-[1])*(x-[1]))/(2*[0]*[0]))",0,10);
		f_gaus->SetParameters(sigma,mean);

		
	for(int i=0; i<10000; i++){
		h1->Fill(f_gaus->GetRandom());
	}
	
	
	gStyle->SetOptStat(1111111);
	f_gaus->SetTitle("Gaus");

	double norm=1.0/h1->Integral();
	h1->Scale(norm);	
	h1->Rebin(1000);
	h1->Draw("hist");
	f_gaus->Draw("same");
	cout << f_gaus->Integral(0,10) << endl;
	cout << h1->Integral() << endl;

}
