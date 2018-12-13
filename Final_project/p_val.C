#include "TMath.h"
double GetPvalue(double nbkg, int nsigNbkg);
double GetExclusion(double nsigNbkg, int nbkg);


void p_val() {


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
	
	TString histname = "h_mass4l_mat"; 
	


	
// --Weighting: Number of expected events
	TH1F *hSignal = (TH1F*)fSignal->Get(histname); hSignal->Scale(xsecSignal/10000*Lumi) ;
	TH1F *hBKG 	  = (TH1F*)fBKG	  ->Get(histname); hBKG	  ->Scale(xsecBKG/10000*Lumi) ;


// --rebinning: Inegrate the mass point
    rebin=10;
	hSignal->Rebin(rebin);
    hBKG->Rebin(rebin);

// --some variables..
	double XMIN = -1;
	double XMAX = -1;
	long YMAX   = 100;
	int Startbin = hSignal->GetXaxis()->FindBin(110);
	int Endbin = hSignal->GetXaxis()->FindBin(140);
	double x[Endbin-Startbin+1];
	double y_pval[Endbin-Startbin+1];
	double y_exclu[Endbin-Startbin+1];

// --Pvalue of Exclusion calculation
	for(int nbin = Startbin; nbin <= Endbin; nbin++){
	
		double N_exptect_sig = hSignal->GetBinContent(nbin);
		double N_exptect_bgr = hBKG->GetBinContent(nbin);
		
		double pvalue_expected       = GetPvalue(N_exptect_bgr,N_exptect_bgr + N_exptect_sig);
		//double significance_expected = ROOT::Math::gaussian_quantile_c(pvalue_expected,1);

		double exclusion_expected = GetExclusion(N_exptect_bgr + N_exptect_sig,N_exptect_bgr);

	
			//cout <<hSignal->GetXaxis()->GetBinCenter(nbin) << "						"<< pvalue_expected << endl;
			//cout <<hSignal->GetXaxis()->GetBinCenter(nbin) << "						"<< exclusion_expected << endl;
			
			x[nbin-Startbin] = hSignal->GetXaxis()->GetBinCenter(nbin);
			y_pval[nbin-Startbin] = pvalue_expected;
			y_exclu[nbin-Startbin] = exclusion_expected;

	}

// --Plotting P-value or CLs
	//TGraph *g_pval = new TGraph(Endbin-Startbin+1,x,y_pval);	XMAX=140; XMIN=110;  YMIN=1.0e-14;YMAX=10; TString YaxisName="Local P value";
	TGraph *g_exclu = new TGraph(Endbin-Startbin+1,x,y_exclu);	XMAX=140; XMIN=110;  YMIN=1.0e-10; YMAX=10; TString YaxisName="Exclusion rate";
	


// --graph design	
	
	//g_pval->SetMarkerStyle(20);		g_pval->SetMarkerColor(1);
	g_exclu->SetMarkerStyle(20);	g_exclu->SetMarkerColor(1);

	double xperbin  = (XMAX-XMIN)/(Endbin-Startbin+1);
	
	// --Exclution Limit 95%
	TLine *l1 = new TLine(110,0.05,140,0.05);
	l1->SetLineStyle(7);
	l1->SetLineWidth(4);
	l1->SetLineColor(2);
	
	// --Significance 5 sigma
	TLine *l2 = new TLine(110,2.9e-07,140,2.9e-07);
	l2->SetLineStyle(7);
	l2->SetLineWidth(4);
	l2->SetLineColor(2);

	
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
		pad1->SetLogy();
	   	pad1->Draw();
		pad1->cd();
   		TH2F *null1 = new TH2F("null1","", 2, XMIN, XMAX, 2, YMIN,YMAX);
   		null1->GetYaxis()->SetTitle(YaxisName);
   		null1->GetXaxis()->SetTitle(Form("M_{4l} / %3.1f GeV",xperbin));
   		null1->GetYaxis()->SetTitleOffset(1.4);
   		null1->GetXaxis()->SetTitleOffset(1.2);
   		null1->GetYaxis()->SetTitleSize(0.03);
   		null1->GetYaxis()->SetLabelSize(0.03);
   		null1->Draw();
		//g_pval->Draw("pc same");	// P value distribution
		g_exclu->Draw("pc same");	// Exclusion distribution
		l1->Draw("same"); 		// Line 95%  CLs 
		//l2->Draw("same"); 			// Line 5 sigmma
	pad1->cd();
            TLatex latex;
            latex.SetNDC();
            latex.SetTextSize(0.04);
            latex.SetTextAlign(11);
            latex.DrawLatex(0.6,0.91,Form("%.1f fb^{-1} (13 TeV)", Lumi/1000.0));



	//c1->Print("P_val.png");
	c1->Print("CLs.png");

}



// --Function for calculating p-value
double GetPvalue(double nbkg, int nsigNbkg){

  double integral = 1.; 
  for(int i = 0; i < nsigNbkg; i++){
    integral -= TMath::Poisson(i,nbkg);
  }
  
  return integral;
  
} 

// --Fuction for caculating Exclusion rate
double GetExclusion(double nsigNbkg, int nbkg){

	double integral =0;
	for(int i=0; i< nbkg; i++){
		integral += TMath::Poisson(i,nsigNbkg);

	}

	return integral;

}
