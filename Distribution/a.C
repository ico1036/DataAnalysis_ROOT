#include <iostream>
using namespace std;
using namespace TMath;
double Gau(int x,double E,double s)
{
	double func=(1/sqrt(2*Pi()*s*s))*Exp(-1*((x-E)*(x-E))/2*s*s);

  return func;
}


void a() {

	for(int i=0; i<1000; i++){
		cout << Gau(i*0.05,25,5) << endl;
	}

}
