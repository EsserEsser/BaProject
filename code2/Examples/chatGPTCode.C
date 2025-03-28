#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <TFile.h>
#include <TH1D.h>
#include <TRatioPlot.h> 
#include <TDatabasePDG.h>
#include <TParticlePDG.h>
#include "nanoTypeConverter.h"
#include "smalldataTree.h"
#include "physicsUtils.h"
#include "histogramUtils.h"
#include "plottingUtils.h"
#include "smalldataTree.C"
#include "physicsUtils.C"
#include "histogramUtils.C"
#include "plottingUtils.C"
using namespace std;

void chatGPTCode() {
// Define particle codes and names:
int particleCodes[6] = {211, 2122, 321, 3122, 333, 3312};
std::string particleNames[6] = {"Pion", "Proton", "Kaon", "Lambda", "Particle5", "Particle6"};

// Create a vector (or array) of histograms for each particle:
std::vector<ParticleHistograms> particleHists;
for (int i = 0; i < 6; i++) {
    // Create histograms for each particle using the name and desired number of bins.
    ParticleHistograms hists = createHistogramsForParticle(particleNames[i], 57);
    particleHists.push_back(hists);
}

    // 2. Load Data
    /*We create a Tchain with all the trees from both data and simulation
    the "smalldataTree" files take care of loading branches and defining*/
    TChain *tChain = new TChain("tree");

    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda91Magnus.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda92Magnus.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda93Magnus.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda94Magnus.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda95Magnus.root");

    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc91.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc92.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc93.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc94.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc95.root");

    // This is used for printing when we open a new file
    int CurrentFileNumber = -1;
    int FilesProcessed = 0;

    smalldataTree t(tChain);
    Long64_t numberOfEntries = t.fChain->GetEntries();
    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();   

    // This is where we define the save location of the root file
    const char* daSave = "/USERS/magnussellebjerg/BA/plots/da45GevCutArticleParticles.root";
    const char* mcSave = "/USERS/magnussellebjerg/BA/plots/mc45GevCutArticleParticles.root";

// In your event loop, when processing each particle:
for (Long64_t i = 0; i < numberOfEntries; i++) {
    t.fChain->GetEntry(i);
    // Loop over particles in the event:
    for (int j = 0; j < t.npart; j++) {
        int truepdg = nanoConvMC((int)t.ptype[j]);
        // Find which particle it corresponds to by matching the PDG code:
        for (int k = 0; k < 6; k++) {
            if (truepdg == particleCodes[k]) {
                // For example, fill the count histogram:
                particleHists[k].countHist->Fill(1);
                
                // Or fill the momentum histograms:
                particleHists[k].pxHist->Fill(t.pmomx[j]);
                particleHists[k].pyHist->Fill(t.pmomy[j]);
                particleHists[k].pzHist->Fill(t.pmomz[j]);
                
                // Calculate transverse momentum and fill its histogram:
                double pt = std::sqrt(t.pmomx[j] * t.pmomx[j] + t.pmomy[j] * t.pmomy[j]);
                particleHists[k].pTHist->Fill(pt);
                
                // Optionally, fill profile histograms if you have a variable for multiplicity:
                // particleHists[k].pTvsMult->Fill(multiplicity, pt);
                break; // Once found, no need to check other codes.
            }
        }
    }
}

    std::cout << "Code Compiled" << std::endl;
}
