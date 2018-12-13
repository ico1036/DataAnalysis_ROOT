#include "TMath.h"

void draw() {

double XMIN = -1;
double XMAX = -1;
long YMAX   = 100;

// --Lumi and xsec
	const double Lumi         = 150000.0;
	//const double xsecSignal   = 0.00031847;
	const double xsecSignal   = 0.00127224;
	
	// --ZZ
	//const double xsecBKG      = 0.020879202;
	
	// --4l
	const double xsecBKG      = 0.02461615231;

// --read file,hist
	TFile *fSignal     = TFile::Open("HtoZZto4l.root")     ;
	//TFile *fBKG	       = TFile::Open("BKG_ZZ.root")         ;
	TFile *fBKG	       = TFile::Open("BKG4l.root")         ;
	
	TString histname = "h_mass4l_mat"; XMAX=180; XMIN=70; rebin=1; YMAX=10;
	//TString histname = "4lMass"; XMAX=140; XMIN=110; rebin=1; YMAX=20;
	//TString histname = "h_mass4l"; XMAX=200; XMIN=0; rebin=20; YMAX=140;
	//TString histname = "h_Z1Mass"; XMAX=200; XMIN=0; rebin=1; YMAX=1000;
	//TString histname = "h_Z2Mass"; XMAX=200; XMIN=0; rebin=1; YMAX=1000;
	
// --Weighting	
	TH1F *hSignal = (TH1F*)fSignal->Get(histname); hSignal->Scale(xsecSignal/10000*Lumi) ;
	TH1F *hBKG 	  = (TH1F*)fBKG	  ->Get(histname); hBKG	  ->Scale(xsecBKG/10000*Lumi) ;


// --histrogram design	
	//hSignal->SetLineWidth(3); hSignal->SetLineColor(2);
	//hBKG->SetFillColor(38); hBKG->SetLineColor(38);
	
	hSignal->SetMarkerStyle(34); hSignal->SetMarkerColor(2);
	hBKG->SetMarkerStyle(34);	hBKG->SetMarkerColor(4);


// --rebinning
	hSignal->Rebin(rebin);
	hBKG->Rebin(rebin);
	

// --fitting function
	

	TF1 *gaus1  = new TF1("gaus1", "gaus",70,180);
	TF1 *sigfit = new TF1("sigfit", "gaus",70,180);
	TF1 *f1 	= new TF1("f1","[0]*TMath::Landau(x,[1],[2])",70,180);
	TF1 *bkgfit = new TF1("bkgfit","gaus(0)+f1",70,180);
	
	bkgfit->SetParLimits(1,80,100);	
	bkgfit->SetParLimits(2,0.5,2);	
	bkgfit->SetParLimits(3,8,15);	
	bkgfit->SetParLimits(4,120,140);	
	bkgfit->SetParLimits(5,12,30);	
	
	//bkgfit->SetParLimits(1,80,100);	
	//bkgfit->SetParLimits(2,1,3);	
	//bkgfit->SetParLimits(4,120,135);	
	//bkgfit->SetParLimits(5,1,3);	
	//bkgfit->SetParLimits(7,135,150);	
	//bkgfit->SetParLimits(8,1,3);	
	//bkgfit->SetParLimits(10,150,180);	
	//bkgfit->SetParLimits(11,1,3);	




	//glbfit->SetParLimits(1,80,100);
	//glbfit->SetParLimits(2,1,3);
	//glbfit->SetParLimits(4,110,130);
	//glbfit->SetParLimits(5,1,3);
	//glbfit->SetParLimits(6,20,30);	
	//glbfit->SetParLimits(7,120,140);	
	//glbfit->SetParLimits(8,10,40);	

	sigfit->SetLineColor(2);	
	bkgfit->SetLineColor(4);	
	//glbfit->SetLineColor(6);

	bkgfit->SetParNames("bkg_strength","bkg_mean","bkg_sigma","bkg_scale","bkg_mpv","bkg_landau_sigma");
	sigfit->SetParNames("sig_strength","sig_mean","sig_sigma");


// --fitting histogram
	hSignal->Fit(sigfit);
	hBKG->Fit(bkgfit);
	TF1 *glbfit = new TF1("glbfit","sigfit+bkgfit",70,180);
	glbfit->SetLineColor(6);	


	cout << "background Chi2/ndf: " << bkgfit->GetChisquare()/5 << endl;
	cout << "signal 	Chi2/ndf: " << sigfit->GetChisquare()/2 << endl;


// --Pad Design
   gStyle->SetOptStat(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadColor(0);
   gStyle->SetFrameBorderMode(0);


	double binwidth= hBKG->GetBinWidth(1);

	TCanvas* c1 = new TCanvas("c1", "c1", 1500, 1500);
	   	TPad *pad1 = new TPad("pad1", "pad1", 0.0, 0.0001, 1.0, 1.0);
		//   pad1->SetBottomMargin(0.01);
	   	pad1->SetGrid();
		 //  pad1->SetLogy();
	   	pad1->Draw();
		pad1->cd();
   		TH2F *null1 = new TH2F("null1","", 2, XMIN, XMAX, 2, 0.09,YMAX);
   		null1->GetYaxis()->SetTitle(Form("Number of events / %3.1f GeV",binwidth));
   		null1->GetXaxis()->SetTitle("M_{4l}");
   		null1->GetYaxis()->SetTitleOffset(1.8);
   		null1->GetXaxis()->SetTitleOffset(1.2);
   		null1->GetYaxis()->SetTitleSize(0.03);
   		null1->GetYaxis()->SetLabelSize(0.03);
   		null1->Draw();
   		 hBKG->Draw("same p");
   		 hSignal->Draw("same p");
   		 bkgfit->Draw("same");
   		 sigfit->Draw("same");
		 glbfit->Draw("same");

// --legend	
   	TLegend *l0 = new TLegend(0.65,0.89,0.90,0.65);
   		l0->SetFillStyle(0);
   		l0->SetBorderSize(0);
   		l0->SetTextSize(0.03);

	  //TLegendEntry* l01 = l0->AddEntry(hSignal,"Signal"   ,"l"  );    l01->SetTextColor(hSignal->GetMarkerColor());  
	  //TLegendEntry* l02 = l0->AddEntry(hBKG,"Background"     ,"l"  ); l02->SetTextColor(hBKG->GetMarkerColor());
	  
	  TLegendEntry* l01 = l0->AddEntry(hSignal,"Signal"   ,"l"  );    l01->SetTextColor(sigfit->GetLineColor());  
	  TLegendEntry* l02 = l0->AddEntry(hBKG,"Background"     ,"l"  ); l02->SetTextColor(bkgfit->GetLineColor());
	  
	  TLegendEntry* l03 = l0->AddEntry(glbfit,"GlobalFit"     ,"l"  ); l03->SetTextColor(glbfit->GetLineColor());
	
 		l0->Draw();

		pad1->cd();
    		TLatex latex;
   			latex.SetNDC();
   			latex.SetTextSize(0.04);
    		latex.SetTextAlign(11);
    		latex.DrawLatex(0.6,0.91,Form("%.1f fb^{-1} (13 TeV)", Lumi/1000.0));


    //c1->Print(histname + "Kinematic_ll.png");
    //c1->Print("window200_" +histname + "Kinematic_ZZ.png");
	c1->Print("fit_result_global.png");
	//c1->Print("fit_result_narrow.png");

	double maxIntibin = hSignal->GetXaxis()->FindBin(200);
	cout << hSignal->Integral(0,maxIntibin) << endl;
	cout << hBKG->Integral(0,maxIntibin) << endl;


}
