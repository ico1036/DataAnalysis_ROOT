void hw_n05(){

	TCanvas *c = new TCanvas();


	TH1F *h_gaus = new TH1F("gaussian","gaussain",100,0,10);					// Histogram fog gaussian distribution n=1000
	TH1F *h_uniform = new TH1F("uniform","unifomr",100,0,10);					// Histogram for uniform distibution   n=10000
	TH1F *h_sum = new TH1F("gaus+uniform","gaus+uniform",100,0,10);				// Sum of above two histograms
	
	TH1F *h_uni_norm = new TH1F("uniform","uniform",100,0,10);					// Normalized(n=10000) uniform  histogram from n=200000
	TH1F *h_sub = new TH1F("uni-gaus","uni-gaus",100,0,10);						// h_sum - h_uni_norm
	
// Fill  gaussian distribution n=1000
	for(int i=0; i<1000; i++){

		h_gaus->Fill(gRandom->Gaus(5,1));
	}
// Fill uniform distibution   n=10000
	for(int i=0; i<10000; i++){

		h_uniform->Fill(gRandom->Uniform(0,10));
	}
// Fill unifom distribution n=200000	
	for(int i=0; i<200000; i++){

		h_uni_norm->Fill(gRandom->Uniform(0,10));
	}

// Sum of gaussian(n=1000) and uniform(n=100000)
	h_sum->Add(h_uniform);
	h_sum->Add(h_gaus);

// Normalize unifom(n=200000) to be a (n=10000)
	h_uni_norm->Scale(1/20.0);

// h_sum - h_uni_norm
	h_sub->Add(h_sum);
	h_sub->Add(h_uni_norm,-1);

// Plotting
	c->Divide(2,1);
	gStyle->SetOptStat(1111111);
	//h_gaus->Draw("E");
	//h_uniform->Draw("E");
	//h_sum->Draw();
	//h_uni_norm->Draw();
	
	h_sub->Draw("E");




}
