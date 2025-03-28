#include <iostream>
#include <sstream>

#include <TH1D.h>
#include <TRatioPlot.h> 
using namespace std;

void plot(){
TH1D* momentumPionPlus[2];

for (int i = 0; i < 2; i++){
    TFile *myFile = new TFile(i==0 ?"/USERS/magnussellebjerg/BA/plots/dapions.root" : "/USERS/magnussellebjerg/BA/plots/mcpions.root");
    momentumPionPlus[i] = (TH1D*)myFile->Get("pPionTotalHist");
    momentumPionPlus[i]->SetDirectory(0);
}
double_t scale = 1.0;
if (momentumPionPlus[1]->Integral() > 0) {
    scale = momentumPionPlus[0]->Integral() / momentumPionPlus[1]->Integral();
}
momentumPionPlus[1]->Scale(scale);

momentumPionPlus[0]->Draw("E");
momentumPionPlus[1]->Draw("E same");

}
