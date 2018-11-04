#include <iostream>
using namespace std;


// Class for position definition and moving
class Point{

	private:
		
		int position;

	public:
		
		void Initialize();
		int Step();
};

// Method for Initializing position
// Initialize the location at x=0
	void Point::Initialize(){
		position=0;
	}

// Method for random stepping
// Rndm is an uniform random number generator r=[0,1]
// r > 0.5: go +1 step (step forward)
// r<= 0.5: go -1 step (backstep)

	int Point::Step(){
		if(gRandom->Rndm(3) > 0.5){
			position++;		
		}else{
			position--;
		}
// This method return the final position after moving		
		return position;
	}
	
	

void hw_n01(){

	TCanvas *c1 = new TCanvas();
	TCanvas *c2 = new TCanvas();
	//c2->Divide(2,1);

// Create "pos" instance from "Point" class 
	Point *pos = new Point();
	
	TH1D *h1 = new TH1D("position","position",100,-50,50);
	TH1D *h2 = new TH1D("position","position",200,-100,100);
	TH1D *h3 = new TH1D("position","position",2000,-1000,1000);

// Single particle move 1000 times
	pos->Initialize();
	for(int i=0;  i<1000; i++){
		h1->Fill(pos->Step());
	}
// 1000 particles move 1000 times
	for(int epoch=0; epoch<1000; epoch++){
		
		pos->Initialize();
		for(int i=0;  i<1000; i++){
			h2->Fill(pos->Step());
		}
	}
// Single particle moves 1000,000 times
	pos->Initialize();
	for(int i=0;  i<1000000; i++){
		h3->Fill(pos->Step());
	}

// Plotting
	gStyle->SetOptStat(111111);
	h1->SetTitle("single 1000 times");
	h1->GetXaxis()->SetTitle("position");
	h2->SetTitle("many particles");
	h2->GetXaxis()->SetTitle("position");
	h3->SetTitle("single particle");
	h3->GetXaxis()->SetTitle("position");

	c1->cd(); h1->Draw();
	c2->cd();	h2->Draw();
	//c2->cd(2);	h3->Draw();

// Delete instance from memory
	c1->Print("hw_n01_SingleParticle.png");
	c2->Print("hw_n01_ManyParticles.png");
	delete pos;

}
