void a(){

TF1 *f1 = new TF1("f1","[0]*TMath::Landau(x,[1],[2])",20,30);
f1->SetParameters(100,130,20);
f1->Draw();


}
