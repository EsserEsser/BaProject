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
#include <cmath>
using namespace std;

//****************************************************************************************** Define function
Double_t pPerpendicularThrust(Float_t px, Float_t py, Float_t pz, Float_t thrux, Float_t thruy, Float_t thruz) {
    float dotProduct = px * thrux + py * thruy + pz * thruz;
    float pMagSquared = px*px + py*py + pz*pz;
    float parallelComponentSquared = dotProduct * dotProduct;
    float perpComponentSquared = pMagSquared - parallelComponentSquared;

    //If statement introduced because rounding errors can cause negative numbers to be returned
    if (perpComponentSquared < 0)
    perpComponentSquared = 0;
    return sqrt(perpComponentSquared);
    }
//****************************************************************************************** Main program
void betterDebug2()
{   
    int setNumberOfFiles = 5;
    bool mcflg = true ;
    bool printPlots = false;
    bool savePlots = false ;
//****************************************************************************************** Define plots
    //1. Define histograms

//****************************************************************************************** Load data
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
//******************************************************************************************
int counter = 0;
//*************************************************************************************************** Data Loop
  
    for (Long64_t i = 0; i < numberOfEntries; i ++){
        t.fChain->GetEntry(i);
        mcflg = (bool)t.mcflavor;
        float thrust = t.thru[2];
        if (thrust > 1){
            counter++;

        }
        bool skipEvent = false;

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
            if (skipEvent) continue;

        }
    }   
    cout << counter << endl;
    tChain->Draw("thru[2]", "thru[2] <1");
}
