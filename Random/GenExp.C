void GenExp(){


// Output filename 
	TFile *outFile = new TFile("Expo.root","RECREATE");
	
	TCanvas *c =new TCanvas();
	c->cd();

// Define histogram	
	TH1F *h1 = new TH1F("h1","h1",100,0,30);

// Fill histogram with Expo distribution	
	for(int i=0;i<10000;i++){
		h1->Fill(gRandom->Exp(2));
	}
// Define fitting function	
	TF1 * f_exp = new TF1("Expo","expo(2)",0,30);

// Fitting
	h1->Fit(f_exp);	
	
// Draw hist 
	
	h1->SetTitle("Expo fitting");
	h1->GetYaxis()->SetTitle("(log scale)");
	c->SetLogy();
	h1->Draw();
	outFile->Write();
}


