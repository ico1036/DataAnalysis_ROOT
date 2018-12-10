void gaus_fit(){


	TFile *file = new TFile("higgs_to_gg.root");
	TH1D *h1 = (TH1D*)file->Get("hsig");

	gStyle->SetOptStat(11111);
	
	TF1 *f_signal = new TF1("f_signal","gaus",100,160);
	f_signal->SetParameters(2000,100,5); // integral mean signa

	h1->Fit(f_signal);
	h1->Draw("hist");
	f_signal->Draw("same");






}
