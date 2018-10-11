#define test_cxx
#include "test.h"
#include <TH2.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

void test::Loop()
{
//   In a ROOT session, you can do:
//      root> .L test.C
//      root> test t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
	
	// 그래프에 들어갈 x,y 배열을 새로 정의했습니다.
	double ax[100],ay[100];

   Long64_t nbytes = 0, nb = 0;
   
	// Ntuple을 하나하나 씩 순회하는 루프입니다	
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   
	// 루프를 돌 때마다 leaf에 저장된 모든 서로 다른 값들이 x,y에 할당되고  
	// ax ay배열로 들어가게됩니다
	ax[jentry]=x;
	ay[jentry]=y;
		
	} // 이벤트 루프 끝

	
	// 추출한 사인함수 데이터를 이용해 그래프를 그리고
	// 데이터가 맞게 들어왔는지 확인해봅니다 
	TGraph *gr = new TGraph(100,ax,ay);
	TCanvas *c1 = new TCanvas("c1","c1",1500,1500);
	c1->cd(1);
	gr->GetXaxis()->SetTitle("x");
	gr->GetXaxis()->SetRangeUser(0,10);
	gr->GetYaxis()->SetTitle("y=sin(x)");
	gr->SetTitle("y=sin(x)");
	gr->SetMarkerStyle(21);
	gr->SetMarkerColor(4);
	gr->Draw("ALP");
	c1->Print("HW_N04.png");
}
