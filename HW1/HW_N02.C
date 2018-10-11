#include <fstream>
#include <iostream>


/*

2. Implement below two steps:
a) Create a ROOT macro to plot points using the TGraph class with in an
attached file, graph.txt in LMS. Try to change a marker point with a
blue box. Look at the possible options for drawing the TGraph in
TGraphPainter, plot a line connecting the points.

b) Display points with their errors in x, y using TGraphErrors with a
graph_err.txt in LMS.

Pull Data:

*/

void HW_N02() {

	// 에러바가 없는 그래프 (a) 와 있는 그래프(b)를 한 번에 보기 좋게
	// 캔버스를 나눠서 출력했습니다.
	TCanvas*c1 = new TCanvas("c1","c1",800,2000);
	c1->Divide(1,2);
	
	// 먼저 에러바가 없는 그래프입니다
	c1->cd(1);

	// TGraph 로 바로 dat/txt/csv 파일을 읽어 옵니다
	TGraph *gr1 = new TGraph("graph.txt");
	
	// 사각형 마커(21) 파랑색(4)	
	gr1->SetTitle("Graph");
	gr1->SetMarkerStyle(21);
	gr1->SetMarkerColor(4);
	gr1->Draw("ALP");
	
	// 에러바가 들어간 그래프입니다
	// TGraphErrors(개수,데이터1,데이터2,데이터1_오차,데이터2_오차)
	// TGraph 처럼 바로 텍스트 파일을 읽어올 수 있습니다.
	c1->cd(2);
	
	TGraphErrors *gre1 = new TGraphErrors("graph_err.txt");
	gre1->SetTitle("Graph with error bars");
	gre1->SetMarkerStyle(21);
	gre1->SetMarkerColor(4);
	gre1->Draw("ALP");
	
	c1->Print("HW_N02.png");

}
