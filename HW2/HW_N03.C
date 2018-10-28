// Homework No3
//Create a program to draw overlap plot for below distributions on same
//canvas using the ROOT framework.
//a) Binominal distribution (n=50, p=0.5)
//b) Poisson distribution (l=25)
//c) Gaussian distribution (m=25, s=5)
//Compare three distributions with respect to the mean and variance values
//and explain the results. (If there will no explanation, the score will be zero.)

#include <iostream>
using namespace TMath;

// Prototypes of poisson and Binomial distribution function

double Poi(int n, int lamda);
double Bin(int n, int N, double p);

void HW_N03(){

	TCanvas * c = new TCanvas("c","c",1500,1500);

// Definition of the three distributions(Poisson,Gaus,Binomial)
	TH1F* h_Poi = new TH1F("h_Poi","",50,0.0,50); 
    TH1F* h_Bin = new TH1F("h_Bin","",50,0.0,50); 
    TH1F* h_Gaus = new TH1F("h_Gaus","",50,0.0,50); 
    
	h_Poi->SetLineColor(2);
	h_Poi->SetLineWidth(2);
	h_Bin->SetLineColor(3);
	h_Bin->SetLineWidth(2);
	h_Gaus->SetLineColor(4);
	h_Gaus->SetLineWidth(2);
   
	h_Poi->GetXaxis()->SetTitle("x");
    h_Poi->GetYaxis()->SetTitle("P(x)");
    
// Set the parameters of gaussian distribution( standard deviation = 5, mean = 25)
	double sigma=5; double mean=25;

// Define the gaussian distribution using TF1 class	
	TF1 *f_gaus = new TF1("gaus","(1/sqrt(2*Pi()*[0]*[0]))*Exp(-1*((x-[1])*(x-[1]))/(2*[0]*[0]))",0,50);
    f_gaus->SetParameters(sigma,mean);
	
// Fill the histograms of three distributions
    for (int i=0;i<10000;i++) {
        h_Poi->Fill(i,Poi(i, 25));
    }
    
	for (int i=0;i<10000;i++) {
        h_Bin->Fill(i,Bin(i,50,0.5));
    }
    
	for(int i=0; i<10000; i++){
        h_Gaus->Fill(f_gaus->GetRandom());
    }

// Normalize the histograms
	h_Gaus->Scale(1/h_Gaus->Integral());
	h_Bin->Scale(1/h_Bin->Integral());
	h_Poi->Scale(1/h_Poi->Integral());

// Set the Y-axis range
	h_Gaus->GetYaxis()->SetRangeUser(0,0.14);
	h_Bin->GetYaxis()->SetRangeUser(0,0.14);
	h_Poi->GetYaxis()->SetRangeUser(0,0.14);
	
	h_Gaus->GetYaxis()->SetTitleOffset(1.4);
	h_Bin->GetYaxis()->SetTitleOffset(1.4);
	h_Poi->GetYaxis()->SetTitleOffset(1.4);

	h_Gaus->SetTitle("Compare 3 distributions");
	h_Bin->SetTitle("Compare 3 distributions");
	h_Poi->SetTitle("Compare 3 distributions");
	

// Check all distributions are normalized
	cout <<"Gaus: "<< h_Gaus->Integral() << endl;
	cout <<"Binary: "<< h_Bin->Integral() << endl;
	cout <<"Poisson: "<< h_Poi->Integral() << endl;

	
	h_Poi->Draw("hist");
    h_Bin->Draw("hist same");	
	h_Gaus->Draw("hist same");

	gStyle->SetOptStat(000000);

// Set the legends(Poisson: Red ,Binomial: Green,  Gaussian: Blue)
	TLegend *l0 = new TLegend(0.65,0.89,0.90,0.65);
	l0->SetFillStyle(0);
	l0->SetBorderSize(0);
	l0->SetTextSize(0.03);
	TLegendEntry* l01 =	l0->AddEntry(h_Poi,"Poisson"   ,"f"  );  l01->SetTextColor(h_Poi->GetLineColor());
    TLegendEntry* l02 = l0->AddEntry(h_Bin,"Binomial"   ,"f"  ); l02->SetTextColor(h_Bin->GetLineColor());
    TLegendEntry* l03 = l0->AddEntry(h_Gaus,"Gaussian"   ,"f"  ); l03->SetTextColor(h_Gaus->GetLineColor());
	l0->Draw();

	c->Print("HW_N03.png");
}

// Definition of the poisson distribution function
double Poi(int n, int lamda)
{
  double func = TMath::Power(lamda,n)*TMath::Exp(-lamda);
  for (int i=1;i<=n;i++) {
    func /= i;
  }
  return func;
}

// Definition of the Binomial distribution function
double Bin(int n, int N, double p)
{
  double func = TMath::Power(p,n)*TMath::Power((1.0-p),N-n);
  for (int i=1;i<=n;i++,N--) {
    func /= i;
    func *= N;
  }
  return func;
}
