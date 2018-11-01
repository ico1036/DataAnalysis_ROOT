void read_file(){

	TFile *input_file = new TFile("Expo.root"); //read "Expo.root" file
	
	TH1F *h = (TH1F*)input_file->Get("h1"); //Get "h1" from the input file and copy to h with TH1F format
	h->SetTitle("read hist from rootfile"); 
	h->Draw();

}
