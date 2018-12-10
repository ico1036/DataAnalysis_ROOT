#include "TMath.h"

void draw() {

double XMIN = -1;
double XMAX = -1;
long YMAX   = 100;

const double Lumi         = 150000.0;
//const double xsecSignal   = 0.00031847;
const double xsecSignal   = 0.00127224;

// --ZZ
//const double xsecBKG      = 0.020879202;

// --4l
const double xsecBKG      = 0.02461615231;

//TFile *fSignal     = TFile::Open("Htozz.root")     ; //--eeChannel
//TFile *fBKG	       = TFile::Open("BKG_4l.root")  ;

TFile *fSignal     = TFile::Open("HtoZZto4l.root")     ;
//TFile *fBKG	       = TFile::Open("BKG_ZZ.root")         ;
TFile *fBKG	       = TFile::Open("BKG4l.root")         ;

TString histname = "h_mass4l_mat"; XMAX=200; XMIN=70; rebin=20; YMAX=100;
//TString histname = "h_mass4l"; XMAX=200; XMIN=0; rebin=20; YMAX=140;

//TString histname = "h_Z1Mass"; XMAX=200; XMIN=0; rebin=1; YMAX=1000;
//TString histname = "h_Z2Mass"; XMAX=200; XMIN=0; rebin=1; YMAX=1000;


TH1F *hSignal = (TH1F*)fSignal->Get(histname); hSignal->Scale(xsecSignal/10000*Lumi) ;
TH1F *hBKG 	  = (TH1F*)fBKG	  ->Get(histname); hBKG	  ->Scale(xsecBKG/10000*Lumi) ;

hSignal->SetLineWidth(3); hSignal->SetLineColor(2);
hBKG->SetFillColor(38); hBKG->SetLineColor(38);

hSignal->Rebin(rebin);
hBKG->Rebin(rebin);

gStyle->SetOptStat(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadColor(0);
   gStyle->SetFrameBorderMode(0);


	double binwidth= hBKG->GetBinWidth(1)/5.0;


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
    hBKG->Draw("same hist");
    hSignal->Draw("same");
   //TLegend *l0 = new TLegend(0.5,0.89,0.80,0.65);
   TLegend *l0 = new TLegend(0.65,0.89,0.90,0.65);
   l0->SetFillStyle(0);
   l0->SetBorderSize(0);
   l0->SetTextSize(0.03);

           TLegendEntry* l01 = l0->AddEntry(hSignal,"Signal"   ,"f"  ); l01->SetTextColor(hSignal->GetLineColor());  
           TLegendEntry* l02 = l0->AddEntry(hBKG,"Background"     ,"f"  ); l02->SetTextColor(hBKG->GetLineColor());

 l0->Draw();

pad1->cd();
    TLatex latex;
   latex.SetNDC();
   latex.SetTextSize(0.04);
    latex.SetTextAlign(11);
    latex.DrawLatex(0.64,0.91,Form("%.1f fb^{-1} (13 TeV)", Lumi/1000.0));


    //c1->Print(histname + "Kinematic_ll.png");
    //c1->Print("window200_" +histname + "Kinematic_ZZ.png");


	double maxIntibin = hSignal->GetXaxis()->FindBin(200);
	cout << hSignal->Integral(0,maxIntibin) << endl;
	cout << hBKG->Integral(0,maxIntibin) << endl;


}
