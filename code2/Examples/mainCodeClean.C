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
#include "smalldataTree.h"
#include "physicsUtils.h"
#include "histogramUtils.h"
#include "plottingUtils.h"

// Implementation files (only if running in ROOT interpreter, not for g++ compilation)
#include "smalldataTree.C"
#include "physicsUtils.C"
#include "histogramUtils.C"
#include "plottingUtils.C"

using namespace std;

// Constants
const int NUM_PARTICLE_TYPES = 6;
const int NUM_PARTICLES_PER_EVENT = 57;
const double MOMENTUM_CUT = 45.0;

// File save paths
const char* daSavePath = "/USERS/magnussellebjerg/BA/plots/da45GevCutArticleParticles.root";
const char* mcSavePath = "/USERS/magnussellebjerg/BA/plots/mc45GevCutArticleParticles.root";

void mainCode() {
    // Configuration
    int maxFiles = 5;
    bool mcFlag = true;
    bool printPlots = false;
    bool savePlots = false;

    // Particle info
    int particleCodes[NUM_PARTICLE_TYPES] = {211, 2122, 321, 3122, 333, 3312};
    std::string particleNames[NUM_PARTICLE_TYPES] = {
        "#Pi^{+}", "Proton", "Kaon^{+}", "Lambda", "Phi", "Xi^{-}"
    };

    // Initialize histograms
    std::vector<ParticleHistograms> particleHists;
    for (int i = 0; i < NUM_PARTICLE_TYPES; ++i) {
        particleHists.push_back(createHistogramsForParticle(particleNames[i], NUM_PARTICLES_PER_EVENT));
    }

    // Load data into TChain
    TChain* tChain = new TChain("tree");

    // Uncomment appropriate data or MC files
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda91Magnus.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc91.root");

    if (tChain->GetEntries() == 0) {
        std::cerr << "No entries found in TChain! Check file paths." << std::endl;
        return;
    }

    // Setup the small data tree and PDG database
    smalldataTree t(tChain);
    Long64_t numberOfEntries = t.fChain->GetEntries();
    TDatabasePDG* pdg = TDatabasePDG::Instance();

    std::cout << "Total entries: " << numberOfEntries << std::endl;

    // Loop over entries
    for (Long64_t i = 0; i < numberOfEntries; ++i) {
        t.fChain->GetEntry(i);
        mcFlag = static_cast<bool>(t.mcflavor);

        for (int j = 0; j < NUM_PARTICLES_PER_EVENT; ++j) {
            particleHists[0].pxHist->Fill(t.pmomx[j]);  // Placeholder: apply cuts as needed
        }

        if (i % 100000 == 0) {
            std::cout << "Processed entry: " << i << std::endl;
        }
    }

    // Plotting (just one histogram shown here)
    particleHists[0].pxHist->Draw();

    std::cout << "Code executed successfully." << std::endl;
}
