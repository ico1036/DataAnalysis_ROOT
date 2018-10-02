void N02_makeHist(){

TH1D *h1 = new TH1D("h1","Example hist",40,-4,4);
TH1D *h2 = new TH1D("h2","Example hist",40,-4,4);
			  //TH1D("name",title",bin,range)

	for(int i=0; i<1000; i++){
	
		double x = gRandom->Gaus(0,1);
		h1->Fill(x);
	}

	h2->FillRandom("gaus",10000);

h1->SetLineColor(kRed);
h1->SetTitle("HIST");
h1->SetXTitle("x");
h2->SetMarkerStyle(20);


h1->Draw();
h2->Draw("same"); // Multiple histogrma in one space

}
