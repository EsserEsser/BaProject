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

void drawTrees(){
    TH1D *varX = new TH1D("thruX", "Var X", 100, 80, 100);

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
    Long64_t mcNumberOfEntries = mcChain->GetEntries();
//******************************************************************************************

    cout << "MC Entries: " << daChain->GetEntries() << endl;
    
    for (int i=0; i < daNumberOfEntries;i++){
        daChain->GetEntry(i);
        if (da.cmenergy > 90.8 &&  da.cmenergy < 91.6) {
            varX->Fill(da.cmenergy);
        }
    }

    varX->Draw();


}