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


void jets()
{   
    int setNumberOfFiles = 1;
    int printPlots = false ;
    bool mcflg = true ;
//****************************************************************************************** Define plots
    //1. Define histograms
    //Kaons 
    TH1D *npartHist = new TH1D("npartHist", "branch", 57, 0, 57);
    TH1D *counterHist = new TH1D("counterHist", "mine",57, 0, 57);
   


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

    
    int numPhot = 0;

//*************************************************************************************************** Data Loop
  
    for (Long64_t i = 0; i < 1; i ++){
        t.fChain->GetEntry(i);
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
        mcflg = (bool)t.mcflavor;
        
        // Cut for Z^0 energies
        if (t.cmenergy > 90.8 &&  t.cmenergy < 91.6){
            int counter = 0;
            // Particle loop
            for (int j = 0; j < t.npart; j++){
                int truepdg = nanoConvMC((int)t.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 
                // double_t pjet1mom = sqrt(t.pjet1[0]*t.pjet1[0]+ t.pjet1[1]*t.pjet1[1] + t.pjet1[2]*t.pjet1[2]);
                // double_t pjet2mom = sqrt(t.pjet2[0]*t.pjet2[0]+ t.pjet2[1]*t.pjet2[1] + t.pjet2[2]*t.pjet2[2]);
                // double_t pjet3mom = sqrt(t.pjet3[0]*t.pjet3[0]+ t.pjet3[1]*t.pjet3[1] + t.pjet3[2]*t.pjet3[2]);

            }

        }
    }   

// // Create a single canvas
//TCanvas *c1 = new TCanvas("c1", "Somethings goes here", 1000, 600);
// counterHist->Draw("same");
// counterHist->SetLineColor(kRed);
// c1->Divide(2,1);
// c1->cd(1);

// c1->cd(2);

// // Create another canvas
// TCanvas *c2 = new TCanvas("c2", "Somethinge else goes here", 800, 600);

if (printPlots == true){
// 4. Save histograms

TFile *outFile = new TFile(mcflg ? "/USERS/magnussellebjerg/BA/plots/mcDetectorAngles.root" : "/USERS/magnussellebjerg/BA/plots/daDetectorAngles.root", "RECREATE");

outFile->Close();

}
}
