#include <iostream>
using namespace TMath;

double Poi(int n, int lamda)
{
  double func = TMath::Power(lamda,n)*TMath::Exp(-lamda);
  for (int i=1;i<=n;i++) {
    func /= i;
  }
  return func;
}

double Bin(int n, int N, double p)
{
  double func = TMath::Power(p,n)*TMath::Power((1.0-p),N-n);
  for (int i=1;i<=n;i++,N--) {
    func /= i;
    func *= N;
  }
  return func;
}




void compare(){


	TH1F* h_Poi = new TH1F("h_Poi","",50,0.0,50); 
    TH1F* h_Bin = new TH1F("h_Bin","",50,0.0,50); 
    TH1F* h_Guas = new TH1F("h_Gaus","",50,0.0,50); 
    
	h_Poi->SetLineColor(2);
	h_Bin->SetLineColor(3);
	h_Gaus->SetLineColor(4);
   
	h_Poi->GetXaxis()->SetTitle("n");
    h_Poi->GetYaxis()->SetTitle("Prob");
    h_Poi->GetYaxis()->SetRangeUser(0,0.16);
    
	TF1 *f_gaus = new TF1("gaus","(1/sqrt(2*Pi()*[0]*[0]))*Exp(-1*((x-[1])*(x-[1]))/(2*[0]*[0]))",0,50);
    f_gaus->SetParameters(5,25);



    for (int i=0;i<50;i++) {
        h_Poi->Fill(i,Poi(i, 25));
    }
    
	for (int i=0;i<50;i++) {
        h_Bin->Fill(i,Bin(i,50,0.5));
    }
    
	for(int i=0; i<50; i++){
        h_Gaus->Fill(f_gaus->GetRandom());
    }


	h_Poi->Draw("hist");
    h_Bin->Draw("hist same");	

	gStyle->SetOptStat(000000);

	TLegend *l0 = new TLegend(0.65,0.89,0.90,0.65);
	l0->SetFillStyle(0);
	l0->SetBorderSize(0);
	l0->SetTextSize(0.03);


	TLegendEntry* l01 =	l0->AddEntry(h_Poi,"Poisson"   ,"f"  );  l01->SetTextColor(h_Poi->GetLineColor());
    TLegendEntry* l02 = l0->AddEntry(h_Bin,"Binomial"   ,"f"  ); l02->SetTextColor(h_Bin->GetLineColor());
    //TLegendEntry* l03 = l0->AddEntry(h_Gaus,"Gaussian"   ,"f"  ); l03->SetTextColor(h_Gaus->GetLineColor());
	l0->Draw();

}

