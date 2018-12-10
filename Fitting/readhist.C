
void readhist(){


// --Read file and histograms
	TFile *f = new TFile("higgs_to_gg.root");
	TH1F *hsig = (TH1F*)f->Get("hsig");
	TH1F *hbkg = (TH1F*)f->Get("hbgr");
	TH1F *hdat = (TH1F*)f->Get("hdat");
	
// --Define some functions
	TF1 *fGaus = new TF1("hsignal","gaus",100,160);
	TF1 *fExpo = new TF1("hsignal","expo",100,160);	

// --Define fitting function
	// gaus parapeter start form 0
	// expo  parapeter start form 3
	TF1 *fsum = new TF1("fdat","gaus(0)+expo(3)",100,160); 
	
	fsum->SetParNames("Strength","Mean","Sigma","Constant","Slope");
	fsum->SetParLimits(1,120,130);  // mass range limit
	fsum->SetParLimits(2,1,3);		// sigma range limit (bump is too low)

// --Fit the "hdat" using "fsum "
	hdat->Fit(fsum);

// --read the parameters to show parameter information
	double par[5];
	fsum->GetParameters(par);
	fGaus->SetParameters(par);
	fExpo->SetParameters(par+3);

	hdat->Draw("e");
	fExpo->Draw("same");
	fGaus->Draw("same");
	fsum->Draw("same");
		
	hdat->  SetLineColor(kBlue); hdat->SetMarkerColor(kBlue);
	fExpo-> SetLineColor(kRed); fExpo->SetLineStyle(2);
	fGaus->	SetLineColor(kRed);
	fsum->	SetLineColor(kRed);

}
