void HW_N01(){

//1. Draw points on the sine function every 0.1 radian in 0<x<10 using TGraph.

	
	TCanvas *c1 = new TCanvas("c1","c1",1500,1500);
		
	// 데이터의 총 개수를 정의합니다(100개).
	// 데이터를 집어넣을 배열 자료구조를 선언합니다.
	const int size=100;
	double x[size],y[size];
	
	// 배열에 데이터를 저장합니다
	// x에는 0 부터 10 까지 0.1간격으로 총 100개의 데이터가 들어갑니다
	// y = sin(x)  
	for(int i=0; i<size; i++){
		x[i]=i*0.1;
		y[i]=sin(x[i]);
	}
	
	// TGraph(100개의 데이터,x,y)
	TGraph *gr = new TGraph(size,x,y);
	// 그래프의 X축 범위를 0부터 10 까지 설정합니다
	gr->GetXaxis()->SetRangeUser(0,10);
	// 그래프에 타이틀을 입력하고, 마커 스타일 등을 설정해 꾸밉니다
	gr->GetXaxis()->SetTitle("x");
	gr->GetYaxis()->SetTitle("y");
	gr->SetTitle("y=sin(x)");
	gr->SetMarkerStyle(31);
	
	// 축을 표시하고(A) 점으로 표시합니다(P)
	gr->Draw("AP");
	
	c1->Print("HW_N01.png");		

}
