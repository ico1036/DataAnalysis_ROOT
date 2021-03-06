void correlation(){

	TCanvas *c = new TCanvas();
	TH2F *h2= new TH2F("h2","h2",50,-5,5,50,-5,5);

	long size = 7000;
	vector<double> a,b;
	double mean  = 0;
	double sigma = 1;

// Generate Gaussian random number	
	
	for(int i=0; i<size; i++){
		a.push_back(gRandom->Gaus(mean,sigma));
		b.push_back(gRandom->Gaus(mean,sigma));
	}

// Fill histogram with x=a, y=0.5*a+b
	
	for(int i=0; i<size; i++){
		h2->Fill(a[i],0.5*a[i]+b[i]);
	}

// Draw hist	
	
	gStyle->SetOptStat(00000);
	h2->SetTitle("Correlation");	
	h2->Draw("COLZ");
	
	cout << "CorrelationFactor: "<< " "<< h2->GetCorrelationFactor() << endl;
	
}
