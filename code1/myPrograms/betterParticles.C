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

void betterParticles()
{   
    int setNumberOfFiles = 1;
    bool mcflg = true ;
    bool printPlots = true;
    bool savePlots = false ;
//****************************************************************************************** Define plots
    //1. Define histograms

    TH1D *ChargedMultiHist = new TH1D("ChargedMultiHist", "Charged Particle Multiplicity", 57, 0, 57);
    TH1D *ParticlesHist = new TH1D("ParticlesHist", "Number of #Protons", 57, 0, 57);
    TH1D *pxParticlesHist = new TH1D("pxParticlesHist", "Particles px momentum", 100, -150, 150);
    TH1D *pyParticlesHist = new TH1D("pyParticlesHist", "Particles py momentum", 100, -150, 150);
    TH1D *pzParticlesHist = new TH1D("pzParticlesHist", "Particles pz momentum", 100, -150, 150);
    TH1D *pParticlesHist = new TH1D("pParticlesHist", "Particles transverse momentum", 100, -150, 150);
    TProfile *ParticlesProfile = new TProfile("ParticlesProfile", "Particles <pT> vs Charged Multiplicity",57, 0, 57);

    TH1D *ChargedParticlesHist = new TH1D("ChargedParticlesHist", "Number of #Protons", 57, 0, 57);
    TH1D *pxChargedParticlesHist = new TH1D("pxChargedParticlesHist", "ChargedParticles px momentum", 100, -150, 150);
    TH1D *pyChargedParticlesHist = new TH1D("pyChargedParticlesHist", "ChargedParticles py momentum", 100, -150, 150);
    TH1D *pzChargedParticlesHist = new TH1D("pzChargedParticlesHist", "ChargedParticles pz momentum", 100, -150, 150);
    TH1D *pChargedParticlesHist = new TH1D("pChargedParticlesHist", "ChargedParticles transverse momentum", 1000, 0, 2);
    TProfile *ChargedParticlesProfile = new TProfile("ChargedParticlesProfile", "ChargedParticles <pT> vs Charged Multiplicity",57, 0, 57);





//******************************************************************************************

    
//****************************************************************************************** Load data
    // 2. Load Data
    /*We create a Tchain with all the trees from both data and simulation
    the "smalldataTree" files take care of loading branches and defining*/
    TChain *tChain = new TChain("tree");

    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda91.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda92.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda93.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda94.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda95.root");

    //tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc91.root");
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

    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();   

    // // Not being used 
    // const int ParticlesPDG = 321;
    // const int ChargedParticlesPDG = -321;
    // const int Particle3PDG = 311;

    // This is where we define the save location of the root file
    const char* mcSave = "/USERS/magnussellebjerg/BA/plots/mcParticles.root";
    const char* daSave = "/USERS/magnussellebjerg/BA/plots/daParticles.root";

    // Cuts
    double_t momentumCut = 45;

//*************************************************************************************************** Data Loop
  
    for (Long64_t i = 0; i < numberOfEntries; i ++){
        t.fChain->GetEntry(i);
        mcflg = (bool)t.mcflavor;

        int chargeMulti = 0;

        int ParticlesCount = 0;
        double_t pParticles = 0;
        double_t pParticlesMean = 0;

        int ChargedParticlesCount = 0;
        double_t pChargedParticles = 0;
        double_t pChargedParticlesMean = 0;

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

            for (int j = 0; j < t.npart; j++){
                skipEvent = false;
                if ( abs(t.pmomx[j]) > momentumCut |abs(t.pmomy[j]) > momentumCut| abs(t.pmomz[j]) > momentumCut){
                    skipEvent = true;
                    if (skipEvent) break;
                }

                int truepdg = nanoConvMC((int)t.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                ParticlesCount += 1;
                if (truepdg != 0){
                    if( particle->Charge() !=0 ){
                        chargeMulti +=1;
                    }
                }
            }
            // When one particle has an abnormal momentum a bunch of other entries in the event also do. Thus, the whole event is skipped.
            if (skipEvent) continue;

            for (int j = 0; j < t.npart; j++){
                int truepdg = nanoConvMC((int)t.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                pParticles += sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]);
                pParticlesHist->Fill(sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));
                // pxParticlesHist->Fill(t.pmomx[j]);
                // pyParticlesHist->Fill(t.pmomy[j]);
                // pzParticlesHist->Fill(t.pmomz[j]);
                ParticlesProfile->Fill(ParticlesCount,sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));
            
                if (particle->Charge() != 0){
                    ChargedParticlesCount += 1;
                    pChargedParticles += sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]);
                
                    // pxChargedParticlesHist->Fill(t.pmomx[j]);
                    // pyChargedParticlesHist->Fill(t.pmomy[j]);
                    // pzChargedParticlesHist->Fill(t.pmomz[j]);
                    ChargedParticlesProfile->Fill(chargeMulti,sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));
                    pChargedParticlesHist->Fill(sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));

                }
            }

        
            ChargedMultiHist->Fill(chargeMulti);

            ParticlesHist->Fill(ParticlesCount);


            ChargedParticlesHist->Fill(ChargedParticlesCount);
            //pChargedParticlesHist->Fill(pChargedParticles);


        }
    }   
    if (printPlots == true){
    // Draw TRatioPlot
    TCanvas *c1 = new TCanvas("c1", "Profile for Particles and ChargedParticles", 800, 600);

    // c1->Divide(2,1);
    // c1->cd(1);
    pChargedParticlesHist->Draw();
    
    // ParticlesProfile->SetTitle("All Particles"); 
    // ParticlesProfile->SetXTitle("Multiplicity");
    // ParticlesProfile->SetYTitle(" <p_{T}> (GeV)");
    // ParticlesProfile->Draw("SAME"); 

    // c1->cd(2);
    // ChargedParticlesProfile->SetTitle("Charged Particles"); 
    // ChargedParticlesProfile->SetXTitle("Charged Multiplicity");
    // ChargedParticlesProfile->SetYTitle(" <p_{T}> (GeV)");
    // ChargedParticlesProfile->Draw("SAME"); 


    }

    if (savePlots == true){

    // 5. Save histograms

    TFile *outFile = new TFile(mcflg ? mcSave : daSave, "RECREATE");
    
    ChargedMultiHist->Write();

    ParticlesHist->Write();
    pParticlesHist->Write();
    ParticlesProfile->SetTitle("Profile Particles");  // Title inside the plot
    ParticlesProfile->SetXTitle("Charge Multiplicity ");
    ParticlesProfile->SetYTitle(" <p_{T}> (GeV)");
    ParticlesProfile->Write();  // "E" ensures error bars are displayed

    ChargedParticlesHist->Write();
    pChargedParticlesHist->Write();
    ChargedParticlesProfile->SetTitle("Profile ChargedParticles");  // Title inside the plot
    ChargedParticlesProfile->SetXTitle("Charge Multiplicity");
    ChargedParticlesProfile->SetYTitle(" <p_{T}> (GeV)");
    ChargedParticlesProfile->Write();  // "E" ensures error bars are displayed

    outFile->Close();
    }
}
