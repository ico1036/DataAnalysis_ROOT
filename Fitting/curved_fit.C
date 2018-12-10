// Linear fit

double f1(double *x, double *par)
{
  return par[2]+par[0]*x[0] + par[1]*x[0]*x[0];
}

void curved_fit()
{
  int n = 5;
  double x[n], y[n], e[n];

  x[0] = 1.0; x[1] = 2.0; x[2] = 3.0; x[3] =  4.0; x[4] =  5.0;
  y[0] = 7.0; y[1] = 5.0; y[2] = 9.0; y[3] = 11.0; y[4] = 20.0;
  e[0] = 2.0; e[1] = 1.5; e[2] = 2.5; e[3] =  3.0; e[4] =  5.0;

  TGraphErrors *g = new TGraphErrors(n, x, y, 0, e);
  auto axis = g->GetXaxis();
  axis->SetLimits(0.,6.);  
  g->GetYaxis()->SetRangeUser(0,28);
  //g->GetHistogram()->SetMinimum(0);
  g->SetMarkerStyle(20);
  g->SetMarkerSize(2.0);
  g->SetLineColor(2);
  g->SetLineWidth(3.0);

  TF1 *func = new TF1("func",f1,0,6,3); // xmin, xmax, npar

  TCanvas *c1 = new TCanvas("c1","Linear fitting");
  g->Draw("ap");
  g->Fit("func");
  g->GetFunction("func")->SetLineColor(4);
}
