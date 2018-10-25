

void gauss() {


TH1D *h1 = new TH1D("h1","h1",10000,0,10);
	for(int i=0;i<10000; i++){
	h1->Fill(gRandom->Gaus(5,1));
	}

TF1 * f1 = new TF1("f1","TMath::Gaus(x,5,1)",0,10);

h1->Draw();
f1->Draw("same");





}
