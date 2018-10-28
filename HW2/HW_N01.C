// Homework No1
//Produce below plots for the Poisson distribution using the ROOT
//framework [ Use the exponential function in ROOT → TMath::Exp() ]
// Poisson Distribution


double f1(int n, int lamda); // Function for poisson distribution


void HW_N01()
{
	gROOT->SetStyle("Plain");

	TCanvas* c = new TCanvas("c","",2000,1500);
	c->Divide(2,1);

	h1 = new TH1F("h1","",20,0.0,20); 
	h2 = new TH1F("h2","",20,0.0,20); 
	
	// Y-axis Limit 
	h1->SetMaximum(0.25);
    h2->SetMaximum(0.25);
	
	// Design the canvas,histogram 
	h1->SetFillColor(5);
	h1->GetXaxis()->SetTitle("k");
	h1->GetYaxis()->SetTitle("Prob");
	h2->SetFillColor(5);
	h2->GetXaxis()->SetTitle("k");
	h2->GetYaxis()->SetTitle("Prob");
	h1->GetXaxis()->SetTitleOffset(1.2);
	h2->GetXaxis()->SetTitleOffset(1.2)
	h1->SetTitle("Poisson(mean=5)");
	h2->SetTitle("Poisson(mean=10)");

	// First we Fill the number by order
	// Then we weight with poisson distribution function(f1)
	
	// A distribution with Lamda(mean) = 5
	for (int i=0;i<20;i++) {
		h1->Fill(i,f1(i, 5));
	}
	// A distribution with Lamda(mean) = 10
	for (int i=0;i<20;i++) {
    	h2->Fill(i,f1(i, 10));
  	}
  
	c->cd(1); h1->Draw("hist");
	c->cd(2); h2->Draw("hist");


	c->Print("HW_N01.png");

}



// Definition of poisson distribution
double f1(int n, int lamda)
{
  double func = TMath::Power(lamda,n)*TMath::Exp(-lamda);
  for (int i=1;i<=n;i++) {
    func /= i; 
  }
  return func; 
}
