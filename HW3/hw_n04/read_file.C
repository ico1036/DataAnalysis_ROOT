void read_file(){

	TCanvas *c = new TCanvas();
	TFile *input_file = new TFile("Expo.root"); //read "Expo.root" file
	
	TH1F *h = (TH1F*)input_file->Get("h1"); //Get "h1" from the input file and copy to h with TH1F format
	h->SetTitle("read hist from rootfile"); 
	
	c->SetLogy();
	h->Draw();
	c->Print("hw_n05.png");
}
