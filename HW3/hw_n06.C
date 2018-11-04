void hw_n06() {

TCanvas *c = new TCanvas("c","c",1600,1000);

TH1F *h1 = new TH1F("uniform","uniform",100,0,1);
TH1F *h2 = new TH1F("transform","transform",100,0,10);



double x;


// transformation method 
// uniform random distribution 0<r<1  -> random distribution of f(r)=aexp(-ar) (a=1, 0<r<1

	for(int i=0; i<1000; i++){

		h1->Fill(gRandom->Rndm(1));
		x = -1*log(gRandom->Rndm(1));
		h2->Fill(x);

	}


	c->Divide(2,1);
	c->cd(1);
	h1->Draw();
	c->cd(2);
	h2->Draw();
	c->Print("hw_n06.png");


}
