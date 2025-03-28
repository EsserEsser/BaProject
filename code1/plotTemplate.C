#include <iostream>
#include <sstream>

#include <TH1D.h>
#include <TRatioPlot.h> 
using namespace std;

void plotTemplate(){
TH1D* Particle1Hist[2];
TH1D* pParticle1Hist[2];
TH1D* Particle1Profile[2];

TH1D* Particle2Hist[2];
TH1D* pParticle2Hist[2];
TH1D* Particle2Profile[2];

TH1D* Particle3Hist[2];
TH1D* pParticle3Hist[2];
TH1D* Particle3Profile[2];

for (int i = 0; i < 2; i++){
    TFile *myFile = new TFile(i==0 ?"/USERS/magnussellebjerg/BA/plots/daKaons.root" : "/USERS/magnussellebjerg/BA/plots/mcKaons.root");
    Particle1Hist[i] = (TH1D*)myFile->Get("Particle1Hist");
    Particle1Hist[i]->SetDirectory(0);

    pParticle1Hist[i] = (TH1D*)myFile->Get("pParticle1Hist");
    pParticle1Hist[i]->SetDirectory(0);
    Particle1Profile[i] = (TH1D*)myFile->Get("Particle1Profile");
    Particle1Profile[i]->SetDirectory(0);

    Particle2Hist[i] = (TH1D*)myFile->Get("Particle2Hist");
    Particle2Hist[i]->SetDirectory(0);
    pParticle2Hist[i] = (TH1D*)myFile->Get("pParticle2Hist");
    pParticle2Hist[i]->SetDirectory(0);
    Particle2Profile[i] = (TH1D*)myFile->Get("Particle2Profile");
    Particle2Profile[i]->SetDirectory(0);

    Particle3Hist[i] = (TH1D*)myFile->Get("Particle3Hist");
    Particle3Hist[i]->SetDirectory(0);
    pParticle3Hist[i] = (TH1D*)myFile->Get("pParticle3Hist");
    pParticle3Hist[i]->SetDirectory(0);
    Particle3Profile[i] = (TH1D*)myFile->Get("Particle3Profile");
    Particle3Profile[i]->SetDirectory(0);




}
// double_t scale = 1.0;
// if (pParticle1Hist[1]->Integral() > 0) {
//     scale = pParticle1Hist[0]->Integral() / pParticle1Hist[1]->Integral();
// }
// pParticle1Hist[1]->Scale(scale);

TCanvas *c1 = new TCanvas("c1", "Particle1 and Particle2", 800, 600);
c1->Divide(3,1);
c1->cd(1);
Particle1Profile[0]->Draw("E");
Particle1Profile[1]->Draw("E same");
Particle1Profile[1]->SetLineColor(kRed); 

c1->cd(2);
Particle2Profile[0]->Draw("E");
Particle2Profile[1]->Draw("E same");
Particle2Profile[1]->SetLineColor(kRed); 

c1->cd(3);
Particle3Profile[0]->Draw("E");
Particle3Profile[1]->Draw("E same");
Particle3Profile[1]->SetLineColor(kRed); 

TCanvas *c2 = new TCanvas("c2", "Particles", 800, 600);
c2->Divide(3,1);
c2->cd(1);
Particle1Hist[0]->Draw("");
Particle1Hist[1]->Draw(" same");
Particle1Hist[1]->SetLineColor(kRed); 
c2->cd(2);
Particle2Hist[0]->Draw("");
Particle2Hist[1]->Draw("same");
Particle2Hist[1]->SetLineColor(kRed); 
c2->cd(3);
Particle3Hist[0]->Draw("");
Particle3Hist[1]->Draw(" same");
Particle3Hist[1]->SetLineColor(kRed); 

}
