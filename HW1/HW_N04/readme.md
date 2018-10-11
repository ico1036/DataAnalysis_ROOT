## Ntuple을 이용한 데이터 분석 과정  


#### HW_N04_MakeData.C -> 텍스트파일 형태의 데이터를 만듭니다: dat.txt  
#### HW_N04_Dat2root.C-> dat.txt를 ROOT를 이용해 분석이 쉬운 Ntuple 타입으로 가공합니다: output: dat.root    
#### root 파일을 분석할 수 있는 준비를 합니다  
root  
TTree *myTree = (TTree*)_file01->Get("your tree name");  
myTree->MakeClass("test");  
#### test.C (여기에서 작업합니다) test.h (변수 등을 설명한 헤더파일) 이 생깁니다  
#### 실행:  
root  
.L test.C  
test a  
a.Loop()  
