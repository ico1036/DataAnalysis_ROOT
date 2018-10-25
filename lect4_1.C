// Binomial Distribution
#include <iostream>
using namespace std;
double f1(int n, int N, double p)
{
  double func = TMath::Power(p,n)*TMath::Power((1.0-p),N-n);
  for (int i=1;i<=n;i++,N--) {
    func /= i; //  /k!
    func *= N; 
  }
  return func; 
}

void lect4_1()
{
  gROOT->SetStyle("Plain");

  TCanvas* c = new TCanvas("c","",200,10,1000,800);
  c->Divide(2,2);

  gStyle->SetOptStat(11111);
  h1 = new TH1F("h1","",20,0.0,20); h1->SetMaximum(0.4);
  h2 = new TH1F("h2","",20,0.0,20); h2->SetMaximum(0.4);
  h3 = new TH1F("h3","",20,0.0,20); h3->SetMaximum(0.4);
  h4 = new TH1F("h4","",20,0.0,20); h4->SetMaximum(0.4);
  h1->SetFillColor(5);
  h2->SetFillColor(5);
  h3->SetFillColor(5);
  h4->SetFillColor(5);

  for (int i=0;i<20;i++) {
    h1->Fill(i,f1(i, 5,0.5));
  }

  for (int i=0;i<20;i++) {
    h2->Fill(i,f1(i, 10,0.5));
  }

  for (int i=0;i<20;i++) {
    h3->Fill(i,f1(i, 20,0.2));
  }

  for (int i=0;i<20;i++) {
    h4->Fill(i,f1(i, 20,0.5));
  }
  c->cd(1); h1->Draw("hist");
  c->cd(2); h2->Draw("hist");
  c->cd(3); h3->Draw("hist");
  c->cd(4); h4->Draw("hist");

	cout << sqrt(20*0.25) << endl;

}


