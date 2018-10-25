// Random number generate using gRandom


void ran0_v2(){

TCanvas *c1 = new TCanvas();
c1->Divide(2,2);

TH1D *h1 = new TH1D("h1","h1",100,0,1);
TH1D *h2 = new TH1D("h2","h2",1000,0,1);
TH1D *h3 = new TH1D("h3","h3",10000,0,1);
TH1D *h4 = new TH1D("h4","h4",100000,0,1);


    for(int i=0; i<100; i++){
        h1->Fill(gRandom->Rndm());
    }
    for(int i=0; i<1000; i++){
        h2->Fill(gRandom->Rndm());
    }
    for(int i=0; i<10000; i++){
        h3->Fill(gRandom->Rndm());
    }
    for(int i=0; i<100000; i++){
        h4->Fill(gRandom->Rndm());
    }

    c1->cd(1); h1->Draw();
    c1->cd(2); h2->Draw();
    c1->cd(3); h3->Draw();
    c1->cd(4); h4->Draw();

}






