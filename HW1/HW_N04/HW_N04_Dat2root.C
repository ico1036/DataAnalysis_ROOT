#include <iostream>

//4-b  Create ROOT file “dat.root” with tree structure including the x, sin(x)
//values


void HW_N04_Dat2root(){

// ROOT 에서는 Ntuple 이라는 편리한 데이터 포맷을 지원합니다.
// Tree->Branch->leaf 순의 트리구조를 갖고있습니다
 	
	// 파일포맷을 .root 로 dat.root 라는 이름으로 output 한다고 선언합니다
	// 같은 이름의 파일이 있더라도 덮어씁니다(RECREATE)
	TFile *f1 = new TFile("dat.root","RECREATE");
	
	// nt라는 이름의 트리구조 중 가장 상위의 tree를 만듭니다
	TTree *mytree = new TTree("nt","nt");
	
	// dat.txt에서 서로 띄어져 있기만 하면 알아서 데이터를 구분해서
	// x와 y라는 leaf 에 저장합니다
	// root 파일이 만들어지면 TBrowser 를 통해 볼 수 있습니다
	// 본래는 라인을 따는 코드이지만 위의 부가기능이 강력합니다
	Long64_t nlines = mytree->ReadFile("dat.txt","x:y");
	
	
	mytree->Write();

}
