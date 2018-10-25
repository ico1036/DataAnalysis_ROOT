#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

float ran(long *idum)
{
	long k;
	float ans;

	*idum ^= MASK;
	k=(*idum)/IQ;
	*idum=IA*(*idum-k*IQ)-IR*k;
	if (*idum < 0) *idum += IM;
	ans=AM*(*idum);
	*idum ^= MASK;
	return ans;
}

void ran0(){

TCanvas *c1 = new TCanvas();
c1->Divide(2,2);

TH1D *h1 = new TH1D("h1","h1",100,0,1);
TH1D *h2 = new TH1D("h2","h2",1000,0,1);
TH1D *h3 = new TH1D("h3","h3",10000,0,1);
TH1D *h4 = new TH1D("h4","h4",100000,0,1);

long seed1=10;
long seed2=1;
long seed3=14;
long seed4=5;

	for(int i=0; i<100; i++){
		h1->Fill(ran(&seed1));
	}
	for(int i=0; i<1000; i++){
		h2->Fill(ran(&seed2));
	}
	for(int i=0; i<10000; i++){
		h3->Fill(ran(&seed3));
	}
	for(int i=0; i<100000; i++){
		h4->Fill(ran(&seed4));
	}
	
	c1->cd(1); h1->Draw();
	c1->cd(2); h2->Draw();
	c1->cd(3); h3->Draw();
	c1->cd(4); h4->Draw();

}

#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef MASK
/* (C) Copr. 1986-92 Numerical Recipes Software 31191a+)-. */
