void a(){



	TH1F *h1 = new TH1F("h1","h1",50,0,50);
	
	for(int i=0; i<50; i++){
	h1->Fill(i);

	}
	
	//cout << h1->GetNbinsX() << endl;
	//cout << h1->GetBinWidth(2) << endl;
	//cout << h1->GetXaxis()->FindBin(25);
	
	cout << h1->Integral(3,3) << endl; 





}
