// Poisson Distribution

double f1(int n, int lamda)
{
  double func = TMath::Power(lamda,n)*TMath::Exp(-lamda);
  for (int i=1;i<=n;i++) {
    func /= i; 
  }
  return func; 
}

void poisson()
{
	gROOT->SetStyle("Plain");

	TCanvas* c = new TCanvas("c","",200,10,1500,800);
	c->Divide(2,1);

	h1 = new TH1F("h1","",20,0.0,20); h1->SetMaximum(0.4);
	h2 = new TH1F("h2","",20,0.0,20); h2->SetMaximum(0.4);
	h1->SetFillColor(5);
	h1->GetXaxis()->SetTitle("k");
	h1->GetYaxis()->SetTitle("Prob");
	h2->SetFillColor(5);
	h2->GetXaxis()->SetTitle("k");
	h2->GetYaxis()->SetTitle("Prob");

	for (int i=0;i<20;i++) {
		h1->Fill(i,f1(i, 5));
	}
	for (int i=0;i<20;i++) {
    	h2->Fill(i,f1(i, 10));
  	}
  
	c->cd(1); h1->Draw("hist");
	c->cd(2); h2->Draw("hist");
}


