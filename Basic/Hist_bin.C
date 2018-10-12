#include <iostream>
using namespace std;

void Hist_bin(){

	TH1F *h1 = new TH1F("h1","h1",5,0,5);
	h1->Fill(1);
	h1->Fill(2);
	h1->Fill(3);
	h1->Fill(3);
	h1->Fill(3);
	
	// Rebin(N) 을 하면 N 개의 bin 을 하나로 합칩니다.
	// 그 하나의 bin은 Nbin 안에 들어있던 엔트리 갯수가 모두 더해진 엔트리를 가집니다.
	// 합칠때의 기준은 가장높은 엔트리를 기준으로 합니다 
	//h1->Rebin(3);
	
	cout << h1->GetXaxis()->GetBinCenter(3)<< endl;
	cout << "Integral :" << " "<< h1->Integral() << endl;
	

	h1->Draw();


}
