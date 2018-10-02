void HW_SinGraph(){

double x[100],y[100];
	
	for(int i=0; i<100; i++){
		
		x[i]=0.1*i;
		y[i]=TMath::Sin(x[i]);
	} 	

TGraph *gr = new TGraph(100,x,y);

gr->Draw();
}
