void Hist_scale(){

	TH1F *h1 = new TH1F("h1","h1",10,0,10);
	
	h1->Fill(3);
	h1->Fill(3);
	h1->Fill(3);
	h1->Fill(1);
	h1->Fill(2);
	h1->Fill(2);
	h1->Fill(4);
	h1->Fill(4);
	h1->Fill(5);
	
	h1->Scale(1/9.0);
	cout << h1->Integral() << endl;

	h1->Draw();

}
