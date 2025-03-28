#include <iostream>
#include <sstream>

#include <TH1D.h>
#include <TRatioPlot.h> 
using namespace std;

void plotPions(){
TH1D* PionPlusHist[2];
TH1D* pPionPlusHist[2];
TH1D* ProfilePionPlus[2];

TH1D* PionMinusHist[2];
TH1D* pPionMinusHist[2];
TH1D* ProfilePionMinus[2];

TH1D* PionNeutralHist[2];
TH1D* pPionNeutralHist[2];
TH1D* ProfilePionNeutral[2];

for (int i = 0; i < 2; i++){
    TFile *myFile = new TFile(i==0 ?"/USERS/magnussellebjerg/BA/plots/daPions.root" : "/USERS/magnussellebjerg/BA/plots/mcPions.root");

    PionPlusHist[i] = (TH1D*)myFile->Get("PionPlusHist");
    PionPlusHist[i]->SetDirectory(0);
    pPionPlusHist[i] = (TH1D*)myFile->Get("pPionPlusHist");
    pPionPlusHist[i]->SetDirectory(0);
    ProfilePionPlus[i] = (TH1D*)myFile->Get("ProfilePionPlus");
    ProfilePionPlus[i]->SetDirectory(0);

    PionMinusHist[i] = (TH1D*)myFile->Get("PionMinusHist");
    PionMinusHist[i]->SetDirectory(0);
    pPionMinusHist[i] = (TH1D*)myFile->Get("pPionMinusHist");
    pPionMinusHist[i]->SetDirectory(0);
    ProfilePionMinus[i] = (TH1D*)myFile->Get("ProfilePionMinus");
    ProfilePionMinus[i]->SetDirectory(0);

    PionNeutralHist[i] = (TH1D*)myFile->Get("PionNeutralHist");
    PionNeutralHist[i]->SetDirectory(0);
    pPionNeutralHist[i] = (TH1D*)myFile->Get("pPionNeutralHist");
    pPionNeutralHist[i]->SetDirectory(0);
    ProfilePionNeutral[i] = (TH1D*)myFile->Get("ProfilePionNeutral");
    ProfilePionNeutral[i]->SetDirectory(0);


}
double_t scale = 1.0;
if (pPionPlusHist[1]->Integral() > 0) {
    scale = pPionPlusHist[0]->Integral() / pPionPlusHist[1]->Integral();
}

// We scale the MC-data because MC has more entries
PionPlusHist[1]->Scale(scale);
PionMinusHist[1]->Scale(scale);
PionNeutralHist[1]->Scale(scale);

pPionPlusHist[1]->Scale(scale);
pPionMinusHist[1]->Scale(scale);
pPionNeutralHist[1]->Scale(scale);


TCanvas *c1 = new TCanvas("c1", "#K^{+} #K^{-} #K^{0}", 1000, 600);

c1->Divide(2,1);
c1->cd(1);
PionPlusHist[0]->Draw();
ProfilePionPlus[0]->Draw("E");
ProfilePionPlus[1]->Draw("E same");
ProfilePionPlus[1]->SetLineColor(kRed); 

c1->cd(2);
ProfilePionMinus[0]->Draw("E");
ProfilePionMinus[1]->Draw("E same");
ProfilePionMinus[1]->SetLineColor(kRed); 

// c1->cd(3);

// ProfilePionNeutral[0]->Draw("E");
// ProfilePionNeutral[1]->Draw("E same");
// ProfilePionNeutral[1]->SetLineColor(kRed); 


// TCanvas *c2 = new TCanvas("c2", "#K^{+} #K^{-} #K^{0}", 1000, 600);
// PionPlusHist[0]->Draw("HIST");
// PionMinusHist[0]->Draw("HIST SAME");
// PionNeutralHist[0]->Draw("HIST SAME");
}


