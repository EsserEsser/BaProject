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
const int NUM_PARTICLE_TYPES = 7;
const double MOMENTUM_CUT = 45.0;

void ratioPlots() {
    int setNumberOfFiles = 5;
    bool mcflg = true ;
    bool printPlots = false;
    bool savePlots = false;
    // // Example call to a physics function:
    // double pPerp = pPerpendicularThrust(1.0, 2.0, 3.0, 0.5, 0.5, 0.7);
    // std::cout << "Perpendicular momentum: " << pPerp << std::endl;


    int particleCodes[NUM_PARTICLE_TYPES] = {211,2212,321,3122,333,3312,3222};
    std::vector<string> particleNames = {"#pi^{+}","p","K^{+}","#Lambda","#phi","#Xi^{-},#Sigma^(+)"};



    ParticleRatioPlots hists = createParticleRatioPlots();
    
   
//******************************************************************************************
    /*We create a Tchain with all the trees from both data and simulation
    the "smalldataTree" files take care of loading branches and defining*/
    TChain *tChain = new TChain("tree");


    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda91Magnus.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda92Magnus.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda93Magnus.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda94Magnus.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda95Magnus.root");

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

        // int kaonpion = 0;
        // int protonpion = 0;
        // int phipion = 0;
        // int lambdapion = 0;
        // int sigmapion = 0;
        // int xipion = 0;

        double pion = 0;
        double proton = 0;
        double kaon = 0;
        double lambda = 0;
        double phi = 0;
        double xi = 0;
        double sigma = 0;

        double mass = 0;
        double energy = 0;
        double rapidity = 0;

        for (int j = 0; j <t.npart; j++){
            int truepdg = nanoConvMC((int)t.ptype[j]);
            TParticlePDG* particle =  pdg->GetParticle(truepdg); 
            mass = particle->Mass();
            energy = std::sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j] + t.pmomz[j]*t.pmomz[j] + mass*mass);


            multi++;
            if (particle->Charge() != 0){
                multiCharge++;
            }


            skipEvent = false;
            if ( abs(t.pmomx[j]) > MOMENTUM_CUT ||abs(t.pmomy[j]) > MOMENTUM_CUT|| abs(t.pmomz[j]) > MOMENTUM_CUT || 1-t.thru[2] > 0.1 ){
                skipEvent = true;
                if (skipEvent) break;
            }
        }

        if (skipEvent) continue;

        for (int j = 0; j < t.npart; j++){
            int truepdg = nanoConvMC((int)t.ptype[j]);
            TParticlePDG* particle =  pdg->GetParticle(truepdg);
            mass = particle->Mass();
            energy = std::sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j] + t.pmomz[j]*t.pmomz[j] + mass*mass);
            rapidity = computeRapidity(energy, t.pmomz[j]);

            for (int k = 0; k < NUM_PARTICLE_TYPES; k++){
                if (truepdg == particleCodes[k] && abs(rapidity)<3){
                    particleCounts[k]++;
                }
            }
        } 
        
        pion = particleCounts[0];
        proton = particleCounts[1];
        kaon = particleCounts[2];
        lambda = particleCounts[3];
        phi = particleCounts[4];
        xi = particleCounts[5];
        sigma = particleCounts[6];


        if(pion > 0 ){
            hists.kaonpionRatio->Fill(multiCharge,kaon/pion);
        }
        if( pion > 0 ){
            hists.phipionRatio->Fill(multiCharge,phi/pion);
        }
        if(pion > 0 ){
            hists.protonpionRatio->Fill(multiCharge,proton/pion);
        }
        if(pion > 0 ){
            hists.lambdapionRatio->Fill(multiCharge,lambda/pion);
        }
        if(pion > 0 ){
            hists.sigmapionRatio->Fill(multiCharge,sigma/pion);
        }
        if(pion > 0 ){
            hists.xipionRatio->Fill(multiCharge,xi/pion);
        }
    }


    // Save histograms to a file.

    if (mcflg == true){
        saveParticleRatioPlots(hists, "/USERS/magnussellebjerg/BA/code2/plots/mcParticleRatioPlots.root");
    }
    else {
        saveParticleRatioPlots(hists, "/USERS/magnussellebjerg/BA/code2/plots/daParticleRatioPlots.root");
    }
    std::cout << "Code Compiled" << std::endl;
}
