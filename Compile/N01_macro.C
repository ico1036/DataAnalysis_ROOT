#include <iostream>
using namespace std;

void N01_macro(int val){

int ret=42;
ret += val;

cout << ret << endl;

}


// Direct excute
// root
// .x N01_macro(103)


// compile
// root
// .L N01_macro.C+
// N01_macro(133)
