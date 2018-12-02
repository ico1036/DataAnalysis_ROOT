
void readhist(){



	TFile *f = new TFile("higgs_to_gg.root");



	TH1F *hsig = (TH1F*)f->Get("hsig");
	TH1F *hbkg = (TH1F*)f->Get("hbgr");
	TH1F *hdat = (TH1F*)f->Get("hdat");
	
	hsig->SetLineColor(3);


	TF1 *func = new TF1("hsignal","gaus",100,160);
	TF1 *func2 = new TF1("hsignal","expo",100,160);
	
	// gaus parapeter start form 0
	// expo  parapeter start form 3
	TF1 *sum_f = new TF1("fdat","gaus(0)+expo(3)",100,160); 
	
	//sum_f->SetParameters(447,125,2,11.82,-0.02);
	
	sum_f->SetParNames("St","m","sig","cost","slp");
	sum_f->SetParLimits(1,120, 130);  // mass range limit
	sum_f->SetParLimits(2,1, 3);		// sigma range limit (bump is too low)

	double par[5];
	sum_f->GetParameters(par);
	func->SetParameters(par);
	func2->SetParameters(par+3);


//	hsig->Fit(func);	
//	hsig->Draw("hist");
//	func->Draw("Same");


	hdat->Fit(sum_f);
	hdat->Draw();
	sum_f->Draw("same");
	func->Draw("same");
	func2->Draw("same");
		
}
