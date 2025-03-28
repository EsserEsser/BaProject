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
#include "nanoTypeConverter.h"
using namespace std;



void drawBranchesEx(){
    int setNumberOfFiles = 1;
    int printPlots = true ;

//****************************************************************************************** Define plots

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
    TDatabasePDG* pdg = TDatabasePDG::Instance();
    int charge = 0;
    int disagree = 0;
    int agree = 0;
    int count = 0;
    // for (Long64_t i = 0; i < 1;i++ ){
    //     daChain->GetEntry(i);
    //     charge = 0;
    //     //cout << " NEW NEW NEW " <<endl;
    //     for (Long64_t j = 0; j < da.npart; j++){
    //         if ((Long64_t)da.ptype[j] != 0){
    //         int truepdg = nanoConvMC((Long64_t)da.ptype[j]);
    //         TParticlePDG* particle =  pdg->GetParticle(truepdg);
    //         //cout << (Long64_t)da.ptype[j] << " particle " << particle->GetName() <<" charge " << particle->Charge() << endl;
    //         if (particle->Charge() != 0){
    //             charge +=1;
    //         }            
            
    //         }
    //     }
    //     if (charge != da.npart){
    //         disagree += 1;
    //     } 
    //     if (charge == da.npart){
    //         agree += 1;
    //     } 
    //     count +=1;
        
    // //cout << "Charge " << charge << " npart = " << da.npart << endl;
    // }
    // cout << "agree " << agree << endl;
    // cout << "disagree" << disagree << endl;
    // cout << "total count" << count << endl;


    // Long64_t j = 0;
    // daChain->GetEntry(2);
    // cout << j << " Inital j = "<< endl;
    // for (Long64_t j=0;j<57;j++){
    //     //cout << (int)da.ptype[j] << endl;
    // }

    daChain->GetEntry(3);
    for (int j=0;j<57;j++){
        cout << (int)da.ptype[j] << endl;
        //cout << da.npart << endl;
    }

    // cout <<  j << " Second j = "<< endl;
    // daChain->GetEntry(10);
    // for (int j=0;j<57;j++){
    //     cout << (int)da.ptype[j] << endl;
    // }
    // cout << j << " Third j = "<< endl;

    //This is the class for Particle data, where we can get the names of particles and suc

    // 4. Process Data Loop 
    int daCurrentFileNumber = -1;
    int daFilesProcessed = 0;
//*************************************************************************************************** Data Loop
  

//*************************************************************************************************** Loop stop

// 5. Process mc data loop
int mcCurrentFileNumber = -1;
int mcFilesProcessed = 0;
//*************************************************************************************************** Data Loop


//*************************************************************************************************** Loop stop

// TCanvas *c1 = new TCanvas("c1", "Randoms", 800, 600);
// c1->Divide(2,1);

// c1->cd(1);
// daChain->Draw("npart");
// mcChain->Draw("npart","","SAME");
// c1->cd(2);
// mcChain->Draw("npart");

}