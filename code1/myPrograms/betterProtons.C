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

void betterProtons()
{   
    int setNumberOfFiles = 5;
    bool mcflg = true ;
    bool printPlots = false;
    bool savePlots = true ;
//****************************************************************************************** Define plots
    //1. Define histograms
    //Protons 
    TH1D *ProtonHist = new TH1D("ProtonHist", "Number of #Protons", 57, 0, 57);
    TH1D *AntiprotonHist = new TH1D("AntiprotonHist", "Number of Antiprotons", 57, 0, 57);
    TH1D *ProtonAndAntiprotonHist = new TH1D("ProtonAndAntiprotonHist", "Number of Protons and Antiprotons", 57, 0, 57);

    TH1D *pxProtonHist = new TH1D("pxProtonHist", "Proton px momentum", 100, -150, 150);
    TH1D *pyProtonHist = new TH1D("pyProtonHist", "Proton py momentum", 100, -150, 150);
    TH1D *pzProtonHist = new TH1D("pzProtonHist", "Proton pz momentum", 100, -150, 150);
    TH1D *pProtonHist = new TH1D("pProtonHist", "Proton transverse momentum", 100, -150, 150);

    TH1D *pxAntiprotonHist = new TH1D("pxAntiprotonHist", "Antiproton px momentum", 100, -150, 150);
    TH1D *pyAntiprotonHist = new TH1D("pyAntiprotonHist", "Antiproton py momentum", 100, -150, 150);
    TH1D *pzAntiprotonHist = new TH1D("pzAntiprotonHist", "Antiproton pz momentum", 100, -150, 150);
    TH1D *pAntiprotonHist = new TH1D("pAntiprotonHist", "Antiproton transverse momentum", 100, -150, 150);

    TH1D *ChargedMultiHist = new TH1D("ChargedMultiHist", "Charged Particle Multiplicity", 57, 0, 57);

    TProfile *ProfileProton = new TProfile("ProfileProton", "Proton <pT> vs Charged Multiplicity",57, 0, 57);
    TProfile *ProfileAntiproton = new TProfile("ProfileAntiproton", "Antiproton <pT> vs Charged Multiplicity",57, 0, 57);
    TProfile *ProfileProton2 = new TProfile("ProfileProton2", "Proton <pT> vs Charged Multiplicity",57, 0, 57);
    TProfile *ProfileAntiproton2 = new TProfile("ProfileAntiproton2", "Antiproton <pT> vs Charged Multiplicity",57, 0, 57);

    //Kaons
//******************************************************************************************

    
//****************************************************************************************** Load data
    // 2. Load Data
    /*We create a Tchain with all the trees from both data and simulation
    the "smalldataTree" files take care of loading branches and defining*/
    TChain *tChain = new TChain("tree");

    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda91.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda92.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda93.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda94.root");
    // tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda95.root");

    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc91.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc92.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc93.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc94.root");
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqmc95.root");

    smalldataTree t(tChain);
    Long64_t numberOfEntries = t.fChain->GetEntries();
//******************************************************************************************

    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();   
    double_t pxtot = 0;
    double_t pytot = 0;
    double_t pztot = 0;
    double_t pProton =0;
    // 4. Process Data Loop 
    int CurrentFileNumber = -1;
    int FilesProcessed = 0;
//*************************************************************************************************** Data Loop
  
    for (Long64_t i = 0; i < numberOfEntries; i ++){
        t.fChain->GetEntry(i);
        mcflg = (bool)t.mcflavor;

        int Proton = 0;
        int Antiproton = 0;
        int ProtonAll =0;
        int charge = 0;

    
        double_t pxProton = 0;
        double_t pyProton = 0;
        double_t pzProton = 0;
        double_t pProton = 0;
        double_t pProtonMean = 0;

        double_t pxAntiproton = 0;
        double_t pyAntiproton = 0;
        double_t pzAntiproton = 0;
        double_t pAntiproton = 0;
        double_t pAntiprotonMean = 0;



  
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
                if ( abs(t.pmomx[j]) > 45 |abs(t.pmomy[j]) > 45| abs(t.pmomz[j]) > 45 && t.npart > 0 ){
                    skipEvent = true;
                }
                if (skipEvent) continue;
                int truepdg = nanoConvMC((int)t.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                if (truepdg != 0){
                    if( particle->Charge() !=0 ){
                        charge +=1;
                    }
                }
            }

            for (int j = 0; j < t.npart; j++){
                skipEvent = false;
                if ( abs(t.pmomx[j]) > 45 |abs(t.pmomy[j]) > 45| abs(t.pmomz[j]) > 45){
                    skipEvent = true;
                }
                if (skipEvent) continue;
                int truepdg = nanoConvMC((int)t.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                if (truepdg == 2212){
                    Proton += 1;
                    ProtonAll += 1;
                    pProton += sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]);

                    // pxProtonHist->Fill(t.pmomx[j]);
                    // pyProtonHist->Fill(t.pmomy[j]);
                    // pzProtonHist->Fill(t.pmomz[j]);
                    ProfileProton2->Fill(charge,sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));

                }

                if (truepdg == -2212){
                    Antiproton += 1;
                    ProtonAll += 1;
                    pAntiproton += sqrt(t.pmomx[j]*t.pmomx[j] +t.pmomy[j]*t.pmomy[j]);

                    // pxAntiprotonHist->Fill(t.pmomx[j]);
                    // pyAntiprotonHist->Fill(t.pmomy[j]);
                    // pzAntiprotonHist->Fill(t.pmomz[j]);
                    ProfileAntiproton2->Fill(charge,sqrt(t.pmomx[j]*t.pmomx[j] +t.pmomy[j]*t.pmomy[j])); 

                }
            }
            if (Proton > 0){
                pProtonMean = pProton / Proton;
                ProfileProton->Fill(charge,pProtonMean);
            }
            if (Antiproton > 0){
                pAntiprotonMean = pAntiproton / Antiproton;
                ProfileAntiproton->Fill(charge,pAntiprotonMean );
            }
           
            ProtonHist->Fill(Proton);
            AntiprotonHist->Fill(Antiproton);
            ProtonAndAntiprotonHist->Fill(ProtonAll);
            pProtonHist->Fill(pProton);
            pAntiprotonHist->Fill(pAntiproton);
            
            
            ChargedMultiHist->Fill(charge);
        }
    }   
    if (printPlots == true){
    // Draw TRatioPlot
    TCanvas *c1 = new TCanvas("c1", "Profiles for Protons and Antiprotons", 800, 600);

    c1->Divide(2,1);
    c1->cd(1);
    ProfileProton2->SetTitle(" Proton"); 
    ProfileProton2->SetXTitle("Charged Multiplicity");
    ProfileProton2->SetYTitle(" <p_{T}> (GeV)");
    ProfileProton2->Draw("SAME"); 
    ProfileProton->SetTitle(" Proton"); 
    ProfileProton->SetXTitle("Charged Multiplicity");
    ProfileProton->SetYTitle(" <p_{T}> (GeV)");
    ProfileProton->Draw("SAME"); 


    c1->cd(2);
    ProfileAntiproton2->SetTitle(" Antiproton");
    ProfileAntiproton2->SetXTitle("Charged Multiplicity");
    ProfileAntiproton2->SetYTitle(" <p_{T}> (GeV)");
    ProfileAntiproton2->Draw("SAME");
    ProfileAntiproton->SetTitle(" Antiproton");
    ProfileAntiproton->SetXTitle("Charged Multiplicity");
    ProfileAntiproton->SetYTitle(" <p_{T}> (GeV)");
    ProfileAntiproton->Draw("SAME");

    }

    if (savePlots == true){

    // 5. Save histograms

    TFile *outFile = new TFile(mcflg ? "/USERS/magnussellebjerg/BA/plots/mcProtons.root" : "/USERS/magnussellebjerg/BA/plots/daProtons.root", "RECREATE");
    // Number of Protons in histogrms
    ProtonHist->Write();
    AntiprotonHist->Write();
    ProtonAndAntiprotonHist->Write();

    // Summed momentum of Protons
    pProtonHist->Write();
    pAntiprotonHist->Write();
    ChargedMultiHist->Write();

    ProfileProton->SetTitle("Profile Proton");  // Title inside the plot
    ProfileProton->SetXTitle("Charged Multiplicity ");
    ProfileProton->SetYTitle(" <p_{T}> (GeV)");
    ProfileProton->Write();  // "E" ensures error bars are displayed
    ProfileProton2->SetTitle("Profile2 Proton");  // Title inside the plot
    ProfileProton2->SetXTitle("Charged Multiplicity ");
    ProfileProton2->SetYTitle(" <p_{T}> (GeV)");
    ProfileProton2->Write();  // "E" ensures error bars are displayed

    ProfileAntiproton->SetTitle("Profile Antiproton ");  // Title inside the plot
    ProfileAntiproton->SetXTitle("Charged Multiplicity ");
    ProfileAntiproton->SetYTitle(" <p_{T}> (GeV)");
    ProfileAntiproton->Write();  // "E" ensures error bars are displayed
    ProfileAntiproton2->SetTitle("Profile2 Antiproton");  // Title inside the plot
    ProfileAntiproton2->SetXTitle("Charged Multiplicity ");
    ProfileAntiproton2->SetYTitle(" <p_{T}> (GeV)");
    ProfileAntiproton2->Write();  // "E" ensures error bars are displayed


    // mcChargedMultiHist->Write();
    // profile->Write();
    outFile->Close();
    }
}
