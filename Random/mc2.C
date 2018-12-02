#include <iostream>
using namespace std;



void mc2() {

long N=100000;
double	x,y,z;
int n=0;


	for(int i=0; i<N; i++){

		x=gRandom->Rndm();
		y=gRandom->Rndm();
		z=gRandom->Rndm();

	// hits in sphere volume
		if(x*x+y*y+z*z <= 1){
			n++;
		}
	}
		cout << N << endl; // cubic volume
		cout << n << endl; // sphere volume

double pi =6*(double)n/N;  // 4/3 * pi * 1/8 = n/N
cout << "pi: "<< pi << endl;
}
