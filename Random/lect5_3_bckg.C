void lect5_3_bckg() 
{
  TCanvas *c1 = new TCanvas("c1","The MC example",200,10,800,600);
  c1->SetGrid();

  TH1F *bckg  = new TH1F("bckg","Main background",100,100,160);
  bckg->SetFillColor(16);
  gSystem->Unlink("bckg.gif"); // delete old file

  // Fill histograms randomly
  gRandom->SetSeed();
  const int kUPDATE = 2000;
  float xbckg;
  int seed;
  for (int i=0; i<1000000; i++) {
    xbckg = -log ( gRandom->Rndm(seed) ) * 100.;
    bckg->Fill(xbckg);
    if (i && (i%kUPDATE) == 0) {
      if (i == kUPDATE) {
        bckg->SetMinimum(0);
        bckg->Draw("same");
        c1->Update();
      }
      c1->Modified();
      c1->Update();
      c1->Print("bckg.gif+");
      printf("i = %d\n", i);
    }
  }
  bckg->Draw("hist"); // to redraw axis hidden by the fill area
  c1->Modified();
  c1->Print("bckg.gif++");
}
