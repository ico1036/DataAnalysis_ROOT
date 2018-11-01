void lect5_3_sig() 
{
  TCanvas *c1 = new TCanvas("c1","The MC example",200,10,800,600);
  c1->SetGrid();

  TH1F *sig = new TH1F("sig","This is the first signal",100,100,160);
  sig->SetFillColor(2);
  gSystem->Unlink("sig.gif"); // delete old file

  // Fill histograms randomly
  gRandom->SetSeed();
  const int kUPDATE = 2000;
  float xsig;
  int gifcnt = 0;
  for (int i=0; i<1000000; i++) {
    xsig   = gRandom->Gaus(125,1.5);
    sig->Fill(xsig,0.002);
    if (i && (i%kUPDATE) == 0) {
      if (i == kUPDATE) {
        sig->Draw("hist same");
        c1->Update();
      }
      c1->Modified();
      c1->Update();
      c1->Print("sig.gif+");
      printf("i = %d\n", i);
    }
  }
  sig->Draw("hist"); // to redraw axis hidden by the fill area
  c1->Modified();
  // make infinite animation by adding "++" to the file name
  // You can view the animated file sig.gif with Netscape/IE or mozilla
  c1->Print("sig.gif++");
}

