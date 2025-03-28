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



void chargedMultiplicity()
{
    int setNumberOfFiles = 5;
    int printPlots = true ;

//****************************************************************************************** Define plots
    //1. Define histograms
    // TH1D *daMultiHist = new TH1D("daMultiHist", "Particle Multiplicity", 57, 0, 57);
    // TH1D *mcMultiHist = new TH1D("mcMultiHist", "Particle Multiplicity", 57, 0, 57);

    // TH1D *thruX = new TH1D("thruX", "thru X", 100, -1, 1);
    // TH1D *thruY = new TH1D("thruY", "thru Y", 100, -1, 1);
    // TH1D *thruZ = new TH1D("thruZ", "thru Z", 100, -1, 1);

    TH1D *daChargedMultiHist = new TH1D("daChargedMultiHist", "Charged Particle Multiplicity", 40, 0, 40);
    TH1D *mcChargedMultiHist = new TH1D("mcChargedMultiHist", "Charged Particle Multiplicity", 40, 0, 40);

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
    Long64_t numberOfEntries = da.fChain->GetEntries();

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
  
    for (Long64_t i = 0; i < numberOfEntries; i ++){
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
            if (da.cmenergy > 90.8 &&  da.cmenergy < 91.6){
            int multi = 0;
            int charge = 0;
            for (int j = 0; j < da.npart; j++){
                int truepdg = nanoConvMC((int)da.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                if (truepdg != 0){
                    multi +=1;
                    if( particle->Charge() != 0){
                        charge +=1;
                    }
                }
            }
            if (multi == 0){
                cout << "No particles" << endl;
            }
            daChargedMultiHist->Fill(charge);
        }
    }   


//*************************************************************************************************** Loop stop


// 5. Process MC Loop
    int mcCurrentFileNumber = -1;
    int mcFilesProcessed = 0;
//*************************************************************************************************** mcData Loop
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
                int truepdg = nanoConvMC((int)mc.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                if (truepdg != 0){
                    multi +=1;
                    if( particle->Charge() !=0 ){
                        charge +=1;
                    }
                }
            }


            mcChargedMultiHist->Fill(charge);

        }
    }
//*************************************************************************************************** mcData Loop stop

// for (int i=0; i < 1; i++){
//     cout << "Data multi and MC multi"<< daMulti[i] << " " << mcMulti[i] << endl;
// }


std::cout << "Data Energy Histogram Entries: " << daChargedMultiHist->GetEntries() << std::endl;
std::cout << "MC Energy Histogram Entries: " << mcChargedMultiHist->GetEntries() << std::endl;

if (mcChargedMultiHist->Integral() > 0) {
    mcChargedMultiHist->Scale(daChargedMultiHist->Integral() / mcChargedMultiHist->Integral());
}


if (printPlots == true){



// 6. Draw TRatioPlot
TCanvas *c1 = new TCanvas("c1", "Ratio Plot", 800, 600);
TRatioPlot *rp1 = new TRatioPlot(daChargedMultiHist,mcChargedMultiHist);
rp1->Draw("E0P");  // "E" for error bars
rp1->GetLowerRefYaxis()->SetTitle("ratio");
rp1->GetUpperRefYaxis()->SetTitle("entries");
c1->Update();



// 6. Save histograms
TFile *outFile = new TFile("/USERS/magnussellebjerg/BA/plots/chargedMultiplictyRatio.root", "RECREATE");
c1->Write();
c1->Draw();
c1->SaveAs("/USERS/magnussellebjerg/BA/plots/chargedMultiplictyRatio.png");
daChargedMultiHist->Write();
mcChargedMultiHist->Write();
outFile->Close();

std::cout << "Histograms saved to ratiplots.root" << std::endl;
}
}
