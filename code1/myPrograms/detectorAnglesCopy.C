#include <iostream>
#include <sstream>
#include <TFile.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <vector>
#include <TDatabasePDG.h>
#include <TParticlePDG.h>
#include "nanoTypeConverter.h"
#include "smalldataTree.h"
#include "smalldataTree.C"
#include <TRatioPlot.h> 
using namespace std;

//Defining functions
Double_t polarAngle(Float_t px,Float_t py,Float_t pz){
    Float_t radius = sqrt(px*px +py*py + pz*pz);
    return acos(pz/radius);
}

Double_t azimuthalAngle(Float_t px, Float_t py){
    return atan2(py,px);
}

// These functions project the particle momenta onto thrust axes. 
// The thru array in daMagnus files are redefined as
// thru[0] = cosin of thrust, thru[1] = phi of thrust, thru[2] = thrust value
// the original thru array can be extracted from thru[1],thru[2]

Double_t pParallelThrust(Float_t px, Float_t py, Float_t pz,Float_t thrux, Float_t thruy, Float_t thruz) {
// Longitudinal component (scalar)
return (px * thrux)  + (py * thruy) + (pz * thruz);
}
Double_t pPerpendicularThrust(Float_t px, Float_t py, Float_t pz, Float_t thrux, Float_t thruy, Float_t thruz) {
float dotProduct = px * thrux + py * thruy + pz * thruz;
float pMagSquared = px*px + py*py + pz*pz;
float parallelComponentSquared = dotProduct * dotProduct;
float perpComponentSquared = pMagSquared - parallelComponentSquared;
return sqrt(perpComponentSquared);
}

void detectorAnglesCopy()
{   
    int setNumberOfFiles = 1;
    int printPlots = false ;
    bool mcflg = true ;
//****************************************************************************************** Define plots
    //1. Define histograms
    //Kaons 
    TH1D *totalMomentumHist = new TH1D("totalMomentumHist", "Total Momentum of all particles", 1000, -20, 20);
    TH1D *transMomentumHist = new TH1D("transMomentumHist", "Total Momentum of all particles", 1000, 0, 5);
    TH1D *polarAngleHist = new TH1D("polarAngleHist", "Polar angle distribution from particles in npart",100, 0,3.15);
    TH1D *azimuthalAngleHist = new TH1D("azimuthalAngleHist", "Azimuthal angle distribution from particles in npart",1000, -6.29,6.29);
    TH1D *projectionAlongThrustHist = new TH1D("projectionAlongThrustHist", "Projection along thrust axis for all particles", 1000, -20, 20);
    TH1D *projectionPerpendicularToThrustHist = new TH1D("projectionPerpendicularToThrustHist ", "Projection perpendicular to thrust axis for all particles", 1000, 0, 5);

    TH1D *totalMomentumPhotonsHist = new TH1D("totalMomentumPhotonsHist", "Total Momentum of photons", 1000, -20, 20);
    TH1D *transMomentumPhotonsHist = new TH1D("transMomentumPhotonsHist", "Total Momentum of all particles", 1000, 0, 5);
    TH1D *polarAnglePhotonsHist = new TH1D("polarAnglePhotonsHist", "Polar angle distribution from photons",100, 0,3.15);
    TH1D *azimuthalAnglePhotonsHist = new TH1D("azimuthalAnglePhotonsHist", "Azimuthal angle distribution from photons",100, -6.29,6.29);
    TH1D *projectionAlongThrustPhotonsHist = new TH1D("projectionAlongThrustPhotonsHist", "Projection along thrust axis for photons", 100, -30, 30);
    TH1D *projectionPerpendicularToThrustPhotonsHist = new TH1D("projectionPerpendicularToThrustPhotonsHist ", "Projection perpendicular to thrust axis for photons", 100, -30, 30);


    //Kaons
//******************************************************************************************

    
//****************************************************************************************** Load data
    // 2. Load Data
    /*We create a Tchain with all the trees from both data and simulation
    the "smalldataTree" files take care of loading branches and defining*/
    TChain *tChain = new TChain("tree");

    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda91.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda92.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda93.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda94.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda95.root");

    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc91.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc92.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc93.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc94.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc95.root");

    smalldataTree t(tChain);
    Long64_t numberOfEntries = t.fChain->GetEntries();
//******************************************************************************************

    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();   

    // 4. Process Data Loop 
    int CurrentFileNumber = -1;
    int FilesProcessed = 0;
    double momentumCut = 45.0;

//*************************************************************************************************** Data Loop
    for (Long64_t i = 0; i < numberOfEntries;i++){
        t.fChain->GetEntry(i);
        mcflg = (bool)t.mcflavor;
        bool skipEvent = false;

        // Cut for Z^0 energies
        if (t.cmenergy > 90.8 &&  t.cmenergy < 91.6){
            
            Long64_t localEntry = t.fChain->LoadTree(i);
            int newFileNumber = tChain->GetTreeNumber();
            if (newFileNumber != CurrentFileNumber) {
                CurrentFileNumber = newFileNumber;
                FilesProcessed++;
                if (FilesProcessed > setNumberOfFiles){
                    break;}
                std::cout << "=== New file loaded: "
                            << tChain->GetCurrentFile()->GetName()
                            << " ===" << std::endl;
            }
            for (int j = 0; j < t.npart; j++){
                skipEvent = false;
                if ( abs(t.pmomx[j]) > momentumCut |abs(t.pmomy[j]) > momentumCut| abs(t.pmomz[j]) > momentumCut){
                    skipEvent = true;
                    if (skipEvent) break;
                }
            }
            if (skipEvent) continue;

            double_t pmom = 0;
            double_t theta = 0;
            double_t phi = 0;
            double_t pTrans = 0;
            double_t pPar= 0;
            double_t pPerp = 0;
            

            // Particle loop
            for (int j = 0; j < t.npart; j++){


                int truepdg = nanoConvMC((int)t.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 
                if (truepdg != 0){


                    pmom = sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j] +t.pmomz[j]*t.pmomz[j]);
                    pTrans = sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]);
                    theta = polarAngle(t.pmomx[j],t.pmomy[j],t.pmomz[j]);
                    phi = azimuthalAngle(t.pmomx[j],t.pmomy[j]);
                    pPar =pParallelThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],t.thru[0],t.thru[1],t.thru[2]);
                    pPerp =pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],t.thru[0],t.thru[1],t.thru[2]);

                    polarAngleHist->Fill(theta);
                    azimuthalAngleHist->Fill(phi);
                    transMomentumHist->Fill(pTrans);
                    totalMomentumHist->Fill(pmom);
                    projectionAlongThrustHist->Fill(pPar);
                    projectionPerpendicularToThrustHist->Fill(pPerp);
                }
            }

            double_t pmomPhot = 0;
            double_t thetaPhot = 0;
            double_t phiPhot = 0;
            double_t pTransPhot = 0;
            double_t pParPhot = 0;
            double_t pPerpPhot = 0;
            // Photon loop
            for (int j = 0; j < t.nphot; j++){
                pmomPhot = sqrt(t.pphotx[j]*t.pphotx[j] + t.pphoty[j]*t.pphoty[j] + t.pphotz[j]*t.pphotz[j]);
                thetaPhot = polarAngle(t.pphotx[j],t.pphoty[j],t.pphotz[j]);
                phiPhot = azimuthalAngle(t.pphotx[j],t.pphoty[j]);
                pParPhot =pParallelThrust(t.pphotx[j],t.pphoty[j],t.pphotz[j],t.thru[0],t.thru[1],t.thru[2]);
                pPerpPhot =pPerpendicularThrust(t.pphotx[j],t.pphoty[j],t.pphotz[j],t.thru[0],t.thru[1],t.thru[2]);


                polarAnglePhotonsHist->Fill(thetaPhot);
                azimuthalAnglePhotonsHist->Fill(phiPhot);
                transMomentumPhotonsHist->Fill(pTransPhot);
                totalMomentumPhotonsHist->Fill(pmomPhot);
                projectionAlongThrustPhotonsHist->Fill(pParPhot);
                projectionPerpendicularToThrustPhotonsHist->Fill(pPerpPhot);

            }
        }
    }  

    TCanvas *c1 = new TCanvas("c1", "Different Angles", 1000, 600);
    c1->Divide(3,1);
    c1->cd(1);
    //polarAngleHist->Draw("HIST");
    polarAnglePhotonsHist->Draw("HIST SAME");

    c1->cd(2);
    //azimuthalAngleHist->Draw("HIST");
    tChain->Draw("nphot");
    //azimuthalAnglePhotonsHist->Draw("HIST SAME");
    c1->cd(3);
    //totalMomentumHist->Draw("HIST");
    totalMomentumPhotonsHist->Draw("SAME");

    TCanvas *c2 = new TCanvas("c2", "Different Angles", 1000, 600);
    c2->Divide(2,1);
    c2->cd(1);
    projectionAlongThrustHist->Draw();
    totalMomentumHist->Draw("SAME");
    totalMomentumHist->SetLineColor(kRed); 

    c2->cd(2);
    projectionPerpendicularToThrustHist->Draw();
    transMomentumHist->Draw("SAME");
    transMomentumHist->SetLineColor(kRed); 

    if (printPlots == true){
        // 4. Save histograms
        
        TFile *outFile = new TFile(mcflg ? "/USERS/magnussellebjerg/BA/plots/mcDetectorAngles.root" : "/USERS/magnussellebjerg/BA/plots/daDetectorAngles.root", "RECREATE");
        polarAngleHist->Write();
        azimuthalAngleHist->Write();
        totalMomentumHist->Write();
        
        polarAnglePhotonsHist->Write();
        azimuthalAnglePhotonsHist->Write();
        totalMomentumPhotonsHist->Write();
        outFile->Close();
        
        }
        
 }