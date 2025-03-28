#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// ROOT headers
#include <TFile.h>
#include <TChain.h>
#include <TH1D.h>
#include <TDatabasePDG.h>
#include <TParticlePDG.h>
#include <TRatioPlot.h>

// Custom headers
#include "nanoTypeConverter.h"
#include "smalldataTreePythia.h"
#include "physicsUtils.h"
#include "histogramUtils.h"
#include "plottingUtils.h"

// Implementation files (only if running in ROOT interpreter, not for g++ compilation)
#include "smalldataTreePythia.C"
#include "physicsUtils.C"
#include "histogramUtils.C"
#include "plottingUtils.C"

using namespace std;

// Constants
const int NUM_PARTICLE_TYPES = 6;
const double MOMENTUM_CUT = 45.0;

// File save paths

void mainPythia() {
    int setNumberOfFiles = 5;
    bool mcflg = true ;
    bool printPlots = false;
    bool savePlots = false;
    // // Example call to a physics function:
    // double pPerp = pPerpendicularThrust(1.0, 2.0, 3.0, 0.5, 0.5, 0.7);
    // std::cout << "Perpendicular momentum: " << pPerp << std::endl;


    int particleCodes[NUM_PARTICLE_TYPES] = {211,2212,321,3122,333,3312};
    std::vector<string> particleNames = {"#pi^{+}","p","K^{+}","#Lambda","#phi","#Xi^{-}"};

    // Create histograms
    // The vector is a struct type I've defined in the histogramUtils files
    std::vector<ParticleHistograms> particleHists;
    GlobalHistograms globalHists = createHistogramsGlobal("GlobalParticles");

    for (int i=0; i<NUM_PARTICLE_TYPES; i++){
        ParticleHistograms hist = createHistogramsForParticle(particleNames[i],57);
        particleHists.push_back(hist);
    }
   
//******************************************************************************************
    /*We create a Tchain with all the trees from both data and simulation
    the "smalldataTree" files take care of loading branches and defining*/
    TChain *tChain = new TChain("tree");

    tChain->Add("/USERS/magnussellebjerg/BA/pythia/pythiaData.root");



    // This is used for printing when we open a new file
    int CurrentFileNumber = -1;
    int FilesProcessed = 0;

    smalldataTreePythia t(tChain);
    Long64_t numberOfEntries = t.fChain->GetEntries();
    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();   

//******************************************************************************************
//******************************************************************************************
//******************************************************************************************
//****************************************************************************************** Main Loop

    for (Long64_t i = 0; i < numberOfEntries; i ++){
        t.fChain->GetEntry(i);
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
        mcflg = (bool)t.mcflavor;
        bool skipEvent = false;

        std::vector<int> particleCounts(NUM_PARTICLE_TYPES,0);
        int multi = 0;
        int multiCharge = 0;
        int photCounter = 0;
        float_t thrustx = 0;
        float_t thrusty = 0;
        float_t thrustz = 0;

        for (int j = 0; j <t.npart; j++){
            skipEvent = false;
            if ( abs(t.pmomx[j]) > MOMENTUM_CUT ||abs(t.pmomy[j]) > MOMENTUM_CUT|| abs(t.pmomz[j]) > MOMENTUM_CUT){
                skipEvent = true;
                if (skipEvent) break;
            }
            int truepdg = (int)t.ptype[j];
            TParticlePDG* particle =  pdg->GetParticle(truepdg); 
            multi++;
            if (particle->Charge() != 0){
                multiCharge++;
            }
        }
        if (skipEvent) continue;

        for (int j = 0; j < t.npart; j++){
            thrustx=sqrt(1.-t.thru[0]*t.thru[0])*cos(t.thru[1]);
            thrusty=sqrt(1.-t.thru[0]*t.thru[0])*sin(t.thru[1]);
            thrustz=fabs(t.thru[0]);
            
            double pT = sqrt(t.pmomx[j]*t.pmomx[j]+ t.pmomy[j]*t.pmomy[j]);
            double pTThrust = pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz);
            double theta = polarAngle(t.pmomx[j],t.pmomy[j],t.pmomz[j]);
            double phi = azimuthalAngle(t.pmomx[j],t.pmomy[j]);
            int nphot = t.nphot;
            
            int truepdg = (int)t.ptype[j];
            TParticlePDG* particle =  pdg->GetParticle(truepdg); 
            if (particle->Charge() != 0){
                globalHists.thetaChargeHist->Fill(theta);
                globalHists.phiChargeHist->Fill(phi);
            }

            if (photCounter < nphot){
                double thetaPhoton = polarAngle(t.pphotx[j],t.pphoty[j],t.pphotz[j]);
                double phiPhoton = azimuthalAngle(t.pphotx[j],t.pphoty[j]);
                globalHists.thetaPhotonsHist->Fill(thetaPhoton);
                globalHists.phiPhotonsHist->Fill(phiPhoton);
                photCounter++;
            }

            for (int k = 0; k < NUM_PARTICLE_TYPES; k++){
                if (truepdg == particleCodes[k]){
                    particleCounts[k]++;
                    particleHists[k].pxHist->Fill(t.pmomx[j]);
                    particleHists[k].pyHist->Fill(t.pmomy[j]);
                    particleHists[k].pzHist->Fill(t.pmomz[j]);
                    particleHists[k].pTHist->Fill(pT);
                    particleHists[k].pTThrustHist->Fill(pTThrust);
                    particleHists[k].pTvsChargeMulti->Fill(multiCharge,pT);
                    particleHists[k].pTvsChargeMultiThrust->Fill(multiCharge,pTThrust);
                }
            }

            globalHists.thetaHist->Fill(theta);
            globalHists.phiHist->Fill(phi);
            globalHists.pxHist->Fill(t.pmomx[j]);
            globalHists.pyHist->Fill(t.pmomy[j]);
            globalHists.pzHist->Fill(t.pmomz[j]);
            globalHists.pTHist->Fill(pT);
            globalHists.pTThrustHist->Fill(pTThrust);
            globalHists.pTvsChargeMulti->Fill(multiCharge,pT);
            globalHists.pTvsChargeMultiThrust->Fill(multiCharge,pTThrust);
        }
        for (int k = 0; k < NUM_PARTICLE_TYPES; k++){
            particleHists[k].countHist->Fill(particleCounts[k]);
        }

        globalHists.multiHist->Fill(multi);
        globalHists.multiChargeHist->Fill(multiCharge);
    }
    

    // Draw the profiles on a canvas.
    drawProfileGrid(particleHists, particleNames);

    // Save histograms to a file.
    saveParticleHistograms(particleHists, "/USERS/magnussellebjerg/BA/code2/plots/pythiaParticlePlots.root");
    saveGlobalHistograms(globalHists, "/USERS/magnussellebjerg/BA/code2/plots/pythiaGlobalPlots.root");

    std::cout << "Code Compiled" << std::endl;
}
