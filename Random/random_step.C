#include <iostream>
using namespace std;

class Point{

	private:
		
		int position;

	public:
		
		void Initialize();
		int Step();
};

	void Point::Initialize(){
		position=0;
	}
	
	int Point::Step(){
		if(gRandom->Rndm(3) > 0.5){
			position++;		
		}else{
			position--;
		}
		
		return position;
	}
	
	

void random_step(){

	TCanvas *c1 = new TCanvas();
	TCanvas *c2 = new TCanvas();
	c2->Divide(2,1);
	Point *pos = new Point();
	
	TH1D *h1 = new TH1D("position","position",100,-50,50);
	TH1D *h2 = new TH1D("position","position",200,-100,100);
	TH1D *h3 = new TH1D("position","position",2000,-1000,1000);
	
	pos->Initialize();
	for(int i=0;  i<1000; i++){
		h1->Fill(pos->Step());
	}

	for(int epoch=0; epoch<1000; epoch++){
		
		pos->Initialize();
		for(int i=0;  i<1000; i++){
			h2->Fill(pos->Step());
		}
	}

	pos->Initialize();
	for(int i=0;  i<1000000; i++){
		h3->Fill(pos->Step());
	}

	gStyle->SetOptStat(111111);
	h1->SetTitle("single 1000 times");
	h1->GetXaxis()->SetTitle("position");
	h2->SetTitle("many particles");
	h2->GetXaxis()->SetTitle("position");
	h3->SetTitle("single particle");
	h3->GetXaxis()->SetTitle("position");

	c1->cd(); h1->Draw();
	c2->cd(1);	h2->Draw();
	c2->cd(2);	h3->Draw();

}
