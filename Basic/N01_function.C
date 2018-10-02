void Func1() {

	TF1 *f1 = new TF1("f1","sin(x)/x",0,10);
				  //TF1("object name","formula",range)
	
	TF1 *f2 = new TF1("f2","[0]*TMath::Exp(-x/[1])+[2]");
	f2->SetParameter(0,10);  // First parameter set
	f2->SetParameter(1,0.3); // Second parameter set
	f2->SetParameter(2,3); 	 // Third parameter set
	
	
	TCanvas *c1 = new TCanvas();
	c1->Divide(1,2);
	c1->cd(1);
	f1->Draw();
	c1->cd(2);
	f2->Draw();


}
