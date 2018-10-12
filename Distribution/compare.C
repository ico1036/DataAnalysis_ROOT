using namespace TMath;
void compare(){

	TF1 *bin = new TF1("Binomial","Factorial([0])/(Factorial(x)*Factorial([0]-x))*(Power([1],x)*TMath::Power((1.0-[1]),[0]-x)",0,10);
	bin->SetParameters(50,0.5);


	


}


