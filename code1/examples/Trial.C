#include <iostream>
#include <sstream>
#include <TFile.h>
#include <TH1F.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <vector>
#include <TDatabasePDG.h>
#include <TParticlePDG.h>
#include "nanoTypeConverter.h"
#include "smalldataTree.h"
#include "smalldataTree.C"

using namespace std;


void Trial(){

    TH1F *myHist = new TH1F("myHist", "Particle Multiplicity", 100, 0, 10);

    TChain *chain = new TChain("tree");
    chain->Add("/USERS/magnussellebjerg/BA/data/zqqda91.root");
    chain->Add("/USERS/magnussellebjerg/BA/data/zqqda92.root");
    chain->Add("/USERS/magnussellebjerg/BA/data/zqqda93.root");
    chain->Add("/USERS/magnussellebjerg/BA/data/zqqda94.root");
    chain->Add("/USERS/magnussellebjerg/BA/data/zqqda95.root");
    smalldataTree t(chain);

    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance(); 
    if (!pdg->GetParticle(1000001020)) {
        pdg->AddParticle("deuteron", "deuteron", 1.8756, true, 0, 0, "Ion", 1000001020);
    }
    if (!pdg->GetParticle(1000001030)) {
        pdg->AddParticle("tritium", "tritium", 2.8089, true, 0, 0, "Ion", 1000001030);
    }
    if (!pdg->GetParticle(1000002040)) {
        pdg->AddParticle("alpha", "alpha", 3.7274, true, 0, 6, "Ion", 1000002040);
    }


    std::cout << "Loop begun" << std::endl;    

    TProfile *profile = new TProfile("profile", "<pT> vs Multiplicity",57, 0, 57);
    
    /* 
    Here we keep count of the total number of a specific particles
    We also keep count of the amount of event which are skipped if it is for any reason
    */
    int totalParticleCounter = 0;
    int skips = 0;


    /*
    This is where we loop over all the trees 
    */
    Long64_t numberOfEntries = t.fChain->GetEntries();
    int currentFileNumber = -1;
    int filesProcessed = 0;

//*************************************************************************************************** Loop start
    for (Long64_t i = 0; i < numberOfEntries; i++) {  
        /*
        This part prints whenever a new file in the chain is loaded
        We can change the if statement for filesProcessed to loop over a specific amount of trees
        */
        Long64_t localEntry = t.fChain->LoadTree(i);
        int newFileNumber = chain->GetTreeNumber();
        if (newFileNumber != currentFileNumber) {
            currentFileNumber = newFileNumber;
            filesProcessed++;
            std::cout << "=== New file loaded: "
                      << chain->GetCurrentFile()->GetName()
                      << " ===" << std::endl;
            if (filesProcessed > 5){
            break;}
            
        }

        t.fChain->GetEntry(i);
        double totalMomentum = 0.0;
        int chargemulti = 0;
        int particleCounter = 0;

        for (int j = 0; j < 57; j++) {
            int truepdg = nanoConvMC((int)t.ptype[j]);
            TParticlePDG* particle =  pdg->GetParticle(truepdg);
            
            if (particle->Charge() != 0){
                chargemulti += 1;

            if (truepdg == 211){

                particleCounter += 1;
                totalParticleCounter += 1;

                double px = t.pmomx[j];
                double py = t.pmomy[j];
                double pz = t.pmomz[j];
                double pT = sqrt(px*px +py*py);

                totalMomentum += pT;
                }
            }
        }
        if (particleCounter > 0){
            double avgMomentum = (chargemulti > 0) ? fabs(totalMomentum) / particleCounter : 0;
            profile->Fill(chargemulti, avgMomentum);  // ⟨pT⟩ vs Multiplicity
        }
    }
//*************************************************************************************************** Loop stop




// Draw the profile with error bars
cout << "Pions counted in code " << totalParticleCounter << endl;
cout << "Code breaking particles skipped " << skips << endl;
TCanvas* c1 = new TCanvas("c1", " Transverse Momentum vs Multiplicity", 800, 650);
profile->SetTitle(" #pi^{+}");  // Title inside the plot
profile->SetXTitle("Multiplicity (npart)");
profile->SetYTitle(" <p_{T}> (GeV)");
profile->Draw("E");  // "E" ensures error bars are displayed
c1->Update();



    // Create a ROOT file to store the histogram
    TFile *outFile = new TFile("output.root", "RECREATE");

    // Write the histogram and profile to the file
    myHist->Write();
    profile->Write();

    // Close the file
    outFile->Close();

    std::cout << "Histograms saved to output.root" << std::endl;

}
