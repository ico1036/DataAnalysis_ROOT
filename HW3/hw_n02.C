#include <iostream>
using namespace std;



void hw_n02() {

// Generate 100,000 numbers
long N=100000;
double	x,y,z;
int n=0;


	for(int i=0; i<N; i++){

// Generate uniform random number x,y,z=[0,1]
// f(x,y,z) means 1*1*1 cubic
		x=gRandom->Rndm();
		y=gRandom->Rndm();
		z=gRandom->Rndm();

// x*x+y*y+z*z <=1 means volume of 1/8*sphere
		if(x*x+y*y+z*z <= 1){
			h_in->Fill(x,y,z);
	}
		cout << N << endl; // cubic volume
		cout << n << endl; // sphere volume



double pi =6*(double)n/N;  // 4/3 * pi * 1/8 = n/N
cout << "pi: "<< pi << endl;
}
