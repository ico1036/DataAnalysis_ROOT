// Binomial Distribution

double f1(int n, int N, double p)
{
  double func = TMath::Power(p,n)*TMath::Power((1.0-p),N-n);
  for (int i=1;i<=n;i++,N--) {
    func /= i;
    func *= N; 
  }
  return func; 
}

void Binomial()
{
  gROOT->SetStyle("Plain");

  TCanvas* c = new TCanvas("c","",200,10,1000,800);

  h1 = new TH1F("h1","",20,0.0,20); h1->SetMaximum(0.4);
  h1->SetFillColor(5);

  for (int i=0;i<20;i++) {
    h1->Fill(i,f1(i, 5,0.5));
  }
  c->cd(1); h1->Draw("hist");
}


