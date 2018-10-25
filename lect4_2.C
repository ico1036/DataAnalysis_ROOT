// Binomial Distribution
#include <iostream>
using namespace std;
double f1(int k, int l)
{
  double func = TMath::Power(l,k)*TMath::Exp(-k);
  for (int i=1;i<=k;i++) {
    func /= i; //  /k!
  }
  return func; 
}

void lect4_2()
{
  gROOT->SetStyle("Plain");

  TCanvas* c = new TCanvas("c","",200,10,1000,800);
  c->Divide(2,2);

  gStyle->SetOptStat(11111);
  h1 = new TH1F("h1","",20,0.0,20); h1->SetMaximum(0.4);
  h1->SetFillColor(5);

  for (int i=0;i<20;i++) {
    h1->Fill(i,f1(i, 10));
  }
  c->cd(1); h1->Draw("hist");

}


