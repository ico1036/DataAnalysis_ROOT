void masswindw(){

	TFile *fsignal = new TFile("HtoZZto4l.root");
	TFile *fbkg    = new TFile("BKG4l.root");

	TF1 *fGaus1 = new TF1("gaus","gaus",70,100);
	TF1 *fGaus2 = new TF1("gaus","gaus",180,200);
	TF1 *fLand = new TF1("Landau","[0]*TMath::Landau(-x,[1],[2])",100,180); 
	
	







}
