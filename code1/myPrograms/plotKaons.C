#include <iostream>
#include <sstream>

#include <TH1D.h>
#include <TRatioPlot.h> 
using namespace std;

void plotKaons(){
TH1D* KaonPlusHist[2];
TH1D* pKaonPlusHist[2];
TH1D* ProfileKaonPlus[2];

TH1D* KaonMinusHist[2];
TH1D* pKaonMinusHist[2];
TH1D* ProfileKaonMinus[2];

TH1D* KaonNeutralHist[2];
TH1D* pKaonNeutralHist[2];
TH1D* ProfileKaonNeutral[2];

for (int i = 0; i < 2; i++){
    TFile *myFile = new TFile(i==0 ?"/USERS/magnussellebjerg/BA/plots/daKaons.root" : "/USERS/magnussellebjerg/BA/plots/mcKaons.root");

    KaonPlusHist[i] = (TH1D*)myFile->Get("KaonPlusHist");
    KaonPlusHist[i]->SetDirectory(0);
    pKaonPlusHist[i] = (TH1D*)myFile->Get("pKaonPlusHist");
    pKaonPlusHist[i]->SetDirectory(0);
    ProfileKaonPlus[i] = (TH1D*)myFile->Get("ProfileKaonPlus");
    ProfileKaonPlus[i]->SetDirectory(0);

    KaonMinusHist[i] = (TH1D*)myFile->Get("KaonMinusHist");
    KaonMinusHist[i]->SetDirectory(0);
    pKaonMinusHist[i] = (TH1D*)myFile->Get("pKaonMinusHist");
    pKaonMinusHist[i]->SetDirectory(0);
    ProfileKaonMinus[i] = (TH1D*)myFile->Get("ProfileKaonMinus");
    ProfileKaonMinus[i]->SetDirectory(0);

    KaonNeutralHist[i] = (TH1D*)myFile->Get("KaonNeutralHist");
    KaonNeutralHist[i]->SetDirectory(0);
    pKaonNeutralHist[i] = (TH1D*)myFile->Get("pKaonNeutralHist");
    pKaonNeutralHist[i]->SetDirectory(0);
    ProfileKaonNeutral[i] = (TH1D*)myFile->Get("ProfileKaonNeutral");
    ProfileKaonNeutral[i]->SetDirectory(0);


}
double_t scale = 1.0;
if (pKaonPlusHist[1]->Integral() > 0) {
    scale = pKaonPlusHist[0]->Integral() / pKaonPlusHist[1]->Integral();
}
KaonPlusHist[1]->Scale(scale);
KaonMinusHist[1]->Scale(scale);
KaonNeutralHist[1]->Scale(scale);

pKaonPlusHist[1]->Scale(scale);
pKaonMinusHist[1]->Scale(scale);
pKaonNeutralHist[1]->Scale(scale);


TCanvas *c1 = new TCanvas("c1", "#K^{+} #K^{-} #K^{0}", 1000, 600);

c1->Divide(3,1);
c1->cd(1);
KaonPlusHist[0]->Draw();
ProfileKaonPlus[0]->Draw("E");
ProfileKaonPlus[1]->Draw("E same");
ProfileKaonPlus[1]->SetLineColor(kRed); 

c1->cd(2);
ProfileKaonMinus[0]->Draw("E");
ProfileKaonMinus[1]->Draw("E same");
ProfileKaonMinus[1]->SetLineColor(kRed); 

c1->cd(3);

ProfileKaonNeutral[0]->Draw("E");
ProfileKaonNeutral[1]->Draw("E same");
ProfileKaonNeutral[1]->SetLineColor(kRed); 
}
