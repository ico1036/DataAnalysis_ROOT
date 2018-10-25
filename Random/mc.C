#include <iostream>
using namespace std;



void mc() {

long N=100000;
double	x,y;
int n=0;


	for(int i=0; i<N; i++){

		x=gRandom->Rndm();
		y=gRandom->Rndm();

		if(sqrt(x*x+y*y) <= 1){
			n++;
		}
	}
		cout << N << endl;
		cout << n << endl;

double pi =4*(double)n/N;
cout << pi << endl;
}
