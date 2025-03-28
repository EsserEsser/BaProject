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
#include "typeConverter.h"
#include "smalldataTree.h"
#include "smalldataTree.C"
#include <TRatioPlot.h> 
using namespace std;



void trial(){
    int setNumberOfFiles = 1;
    int printPlots = true ;

//****************************************************************************************** Define plots
    //1. Define histograms
    TH1D *danpartHist = new TH1D("danpartHist", "npart Histogram", 57, 1, 57);
    TH1D *mcnpartHist = new TH1D("mcnpartHist", "npart Histogram", 57, 1, 57);

    TH1D *daMultiHist = new TH1D("daMultiHist", "Particle Multiplicity", 57, 1, 57);
    TH1D *mcMultiHist = new TH1D("mcMultiHist", "Particle Multiplicity", 57, 1, 60);

    // TH1D *thruX = new TH1D("thruX", "thru X", 100, -1, 1);
    // TH1D *thruY = new TH1D("thruY", "thru Y", 100, -1, 1);
    // TH1D *thruZ = new TH1D("thruZ", "thru Z", 100, -1, 1);

    TH1D *daChargedMultiHist = new TH1D("daChargedMultiHist", "Charged Particle Multiplicity", 57, 1, 57);
    TH1D *mcChargedMultiHist = new TH1D("mcMultiHist", "Charged Particle Multiplicity", 25, 15, 40);

    // TH1D *daComEnergyHist = new TH1D("daComEnergyHist", "Data Center of Mass Energy", 30, 80, 100);
    // TH1D *mcComEnergyHist = new TH1D("mcComEnergyHist", "MC Center of Mass Energy", 30, 80, 100);
//******************************************************************************************

    
//****************************************************************************************** Load data
    // 2. Load Data
    /*We create a Tchain with all the trees from both data and simulation
    the "smalldataTree" files take care of loading branches and defining*/
    TChain *daChain = new TChain("tree");
    daChain->Add("/USERS/magnussellebjerg/BA/data/zqqda91.root");
    daChain->Add("/USERS/magnussellebjerg/BA/data/zqqda92.root");
    daChain->Add("/USERS/magnussellebjerg/BA/data/zqqda93.root");
    daChain->Add("/USERS/magnussellebjerg/BA/data/zqqda94.root");
    daChain->Add("/USERS/magnussellebjerg/BA/data/zqqda95.root");
    smalldataTree da(daChain);
    Long64_t daNumberOfEntries = da.fChain->GetEntries();

    // 3. Load MC Simulation
    TChain *mcChain = new TChain("tree");
    mcChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc91.root");
    mcChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc92.root");
    mcChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc93.root");
    mcChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc94.root");
    mcChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc95.root");
    smalldataTree mc(mcChain);
    Long64_t mcNumberOfEntries = mc.fChain->GetEntries();
//******************************************************************************************



    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();   

    std::vector<int> daMulti;
    std::vector<int> mcMulti;

    

    // 4. Process Data Loop 
    int daCurrentFileNumber = -1;
    int daFilesProcessed = 0;
//*************************************************************************************************** Data Loop
  
    for (Long64_t i = 0; i < daNumberOfEntries; i ++){
        Long64_t localEntry = da.fChain->LoadTree(i);
        int newFileNumber = daChain->GetTreeNumber();
        if (newFileNumber != daCurrentFileNumber) {
            daCurrentFileNumber = newFileNumber;
            daFilesProcessed++;
            if (daFilesProcessed > setNumberOfFiles){
                break;}
            std::cout << "=== New file loaded: "
                        << daChain->GetCurrentFile()->GetName()
                        << " ===" << std::endl;
        }

        da.fChain->GetEntry(i);
        int multi = 0;
        int charge = 0;

        if (da.cmenergy > 90.8 &&  da.cmenergy < 91.6){
            for (int j = 0; j < da.npart; j++){

                int truepdg = ConvMC((int)da.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 
                if (truepdg != 0){
                    multi += 1;

                    if (particle->Charge() != 0){
                        charge +=1;
                    }

                } 
            }
        }
        daChargedMultiHist->Fill(charge);
        daMultiHist->Fill(multi);
        danpartHist->Fill(da.npart);
        
    }   

//*************************************************************************************************** Loop stop

// 5. Process mc data loop
int mcCurrentFileNumber = -1;
int mcFilesProcessed = 0;
//*************************************************************************************************** Data Loop
  
for (Long64_t i = 0; i < mcNumberOfEntries; i ++){
    Long64_t localEntry = mc.fChain->LoadTree(i);
    int newFileNumber = mcChain->GetTreeNumber();
    if (newFileNumber != mcCurrentFileNumber) {
        mcCurrentFileNumber = newFileNumber;
        mcFilesProcessed++;
        if (mcFilesProcessed > setNumberOfFiles){
            break;}
        std::cout << "=== New file loaded: "
                    << mcChain->GetCurrentFile()->GetName()
                    << " ===" << std::endl;
    }
    mc.fChain->GetEntry(i);


    int multi = 0;
    int charge = 0;

    if (mc.cmenergy > 90.8 &&  mc.cmenergy < 91.6){


        for (int j = 0; j < mc.npart; j++){

            int truepdg = ConvMC((int)mc.ptype[j]);
            TParticlePDG* particle =  pdg->GetParticle(truepdg); 
            if (truepdg != 0){
                multi += 1;

                if (particle->Charge() != 0){
                    charge +=1;
                }

            } 
        }
    }
    mcChargedMultiHist->Fill(charge);
    mcMultiHist->Fill(multi);
    mcnpartHist->Fill(mc.npart);
}   

//*************************************************************************************************** Loop stop

// daChargedMultiHist->Draw();
// mcChargedMultiHist->Draw("same");
daChain->Draw("npart")
// danpartHist->Draw();
// mcnpartHist->Draw("same");

}