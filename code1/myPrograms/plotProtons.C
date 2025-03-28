#include <iostream>
#include <sstream>

#include <TH1D.h>
#include <TRatioPlot.h> 
using namespace std;

void plotProtons(){
TH1D* pProtonHist[2];
TH1D* pAntiprotonHist[2];
TH1D* ProfileProton[2];
TH1D* ProfileAntiproton[2];
TH1D* ProfileProtonMean[2];
TH1D* ProfileAntiprotonMean[2];

for (int i = 0; i < 2; i++){
    TFile *myFile = new TFile(i==0 ?"/USERS/magnussellebjerg/BA/plots/daProtons.root" : "/USERS/magnussellebjerg/BA/plots/mcProtons.root");
    pProtonHist[i] = (TH1D*)myFile->Get("pProtonHist");
    pProtonHist[i]->SetDirectory(0);
    pAntiprotonHist[i] = (TH1D*)myFile->Get("pProtonHist");
    pAntiprotonHist[i]->SetDirectory(0);


    ProfileProton[i] = (TH1D*)myFile->Get("ProfileProton");
    ProfileProton[i]->SetDirectory(0);
    ProfileAntiproton[i] = (TH1D*)myFile->Get("ProfileAntiproton");
    ProfileAntiproton[i]->SetDirectory(0);



}
// double_t scale = 1.0;
// if (pProtonHist[1]->Integral() > 0) {
//     scale = pProtonHist[0]->Integral() / pProtonHist[1]->Integral();
// }
// pProtonHist[1]->Scale(scale);

TCanvas *c1 = new TCanvas("c1", "Proton and Antiproton", 1000, 600);
c1->Divide(2,1);
c1->cd(1);
ProfileProton[0]->Draw("E");
ProfileProton[1]->Draw("E same");
ProfileProton[1]->SetLineColor(kRed); 

c1->cd(2);
//pProtonHist[0]->Draw();
ProfileAntiproton[0]->Draw("E");
ProfileAntiproton[1]->Draw("E same");
ProfileAntiproton[1]->SetLineColor(kRed); 

}
