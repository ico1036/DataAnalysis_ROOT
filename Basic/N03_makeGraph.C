void N03_makeGraph(){

double x[] = {1,2,3,4,5	};
double y[] = {0.5,2.,3.,3.2,4.7};


TGraph* gr = new TGraph(5,x,y);
gr->SetMarkerStyle(20);
gr->Draw("AP");

}
