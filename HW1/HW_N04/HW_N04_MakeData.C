#include <iostream>

/*
4. Draw points of the sine function, sin(x) every 0.1 radian in 0<x<10 using
TGraph in ROOT framework.

a) Save the values for x, sin(x) points in the text file named as dat.txt.

*/


void HW_N04_MakeData(){

	// c++ 에서 파일을 쓰기위한 과정입니다
	ofstream myfile;
	myfile.open("dat.txt");
	
	
	const int size=100;
    double x[size],y[size];

	// 0 에서 10 까지 0.1 간격의 x 데이터
	// y=sin(x) 데이터가 순차적으로 dat.txt 파일에 들어갑니다
    for(int i=0; i<size; i++){
        cout << i*0.1 << "		" << sin(i*0.1) << endl;
		myfile << i*0.1 << "		" << sin(i*0.1) << "\n";
    }

	myfile.close();
}

