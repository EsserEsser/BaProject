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
void masterTemplate(){
    int setNumberOfFiles = 1;
    bool mcflg = true ;
    bool printPlots = true;
    bool savePlots = false ;
//****************************************************************************************** General histograms


    TH1D *ChargedMultiHist = new TH1D("ChargedMultiHist", "Charged Particle Multiplicity", 57, 0, 57);

//****************************************************************************************** Particle specific Histograms
    const int Particle1PDG = 211;
    TH1D *Particle1Hist = new TH1D("Particle1Hist", "Number of Particle1", 20, 0, 20);
    TH1D *pxParticle1Hist = new TH1D("pxParticle1Hist", "Particle1 px momentum", 100, -150, 150);
    TH1D *pyParticle1Hist = new TH1D("pyParticle1Hist", "Particle1 py momentum", 100, -150, 150);
    TH1D *pzParticle1Hist = new TH1D("pzParticle1Hist", "Particle1 pz momentum", 100, -150, 150);
    TH1D *pParticle1Hist = new TH1D("pParticle1Hist", "Particle1 transverse momentum", 100, -150, 150);
    TProfile *Particle1Profile = new TProfile("Particle1Profile", "Particle1 <pT> vs Charged Multiplicity",57, 0, 57);
    TProfile *Particle1ThrustProfile = new TProfile("Particle1ThrustProfile", "Particle1 Thrust axis <pT> vs Charged Multiplicity",57, 0, 57);

    const int Particle2PDG = 2212;
    TH1D *Particle2Hist = new TH1D("Particle2Hist", "Number of Particle2", 20, 0, 20);
    TH1D *pxParticle2Hist = new TH1D("pxParticle2Hist", "Particle2 px momentum", 100, -150, 150);
    TH1D *pyParticle2Hist = new TH1D("pyParticle2Hist", "Particle2 py momentum", 100, -150, 150);
    TH1D *pzParticle2Hist = new TH1D("pzParticle2Hist", "Particle2 pz momentum", 100, -150, 150);
    TH1D *pParticle2Hist = new TH1D("pParticle2Hist", "Particle2 transverse momentum", 100, -150, 150);
    TProfile *Particle2Profile = new TProfile("Particle2Profile", "Particle2 <pT> vs Charged Multiplicity",57, 0, 57);
    TProfile *Particle2ThrustProfile = new TProfile("Particle2ThrustProfile", "Particle2 Thrust axis <pT> vs Charged Multiplicity",57, 0, 57);

    const int Particle3PDG = 321;
    TH1D *Particle3Hist = new TH1D("Particle3Hist", "Number of Particle3", 20, 0, 20);
    TH1D *pxParticle3Hist = new TH1D("pxParticle3Hist", "Particle3 px momentum", 100, -150, 150);
    TH1D *pyParticle3Hist = new TH1D("pyParticle3Hist", "Particle3 py momentum", 100, -150, 150);
    TH1D *pzParticle3Hist = new TH1D("pzParticle3Hist", "Particle3 pz momentum", 100, -150, 150);
    TH1D *pParticle3Hist = new TH1D("pParticle3Hist", "Particle3 transverse momentum", 100, -150, 150);
    TProfile *Particle3Profile = new TProfile("Particle3Profile", "Particle3 <pT> vs Charged Multiplicity",57, 0, 57);
    TProfile *Particle3ThrustProfile = new TProfile("Particle3ThrustProfile", "Particle3 Thrust axis <pT> vs Charged Multiplicity",57, 0, 57);

    const int Particle4PDG = 3122;
    TH1D *Particle4Hist = new TH1D("Particle4Hist", "Number of Particle4", 20, 0, 20);
    TH1D *pxParticle4Hist = new TH1D("pxParticle4Hist", "Particle4 px momentum", 100, -150, 150);
    TH1D *pyParticle4Hist = new TH1D("pyParticle4Hist", "Particle4 py momentum", 100, -150, 150);
    TH1D *pzParticle4Hist = new TH1D("pzParticle4Hist", "Particle4 pz momentum", 100, -150, 150);
    TH1D *pParticle4Hist = new TH1D("pParticle4Hist", "Particle4 transverse momentum", 100, -150, 150);
    TProfile *Particle4Profile = new TProfile("Particle4Profile", "Particle4 <pT> vs Charged Multiplicity",57, 0, 57);
    TProfile *Particle4ThrustProfile = new TProfile("Particle4ThrustProfile", "Particle4 Thrust axis <pT> vs Charged Multiplicity",57, 0, 57);

    const int Particle5PDG = 333;
    TH1D *Particle5Hist = new TH1D("Particle5Hist", "Number of Particle5", 20, 0, 20);
    TH1D *pxParticle5Hist = new TH1D("pxParticle5Hist", "Particle5 px momentum", 100, -150, 150);
    TH1D *pyParticle5Hist = new TH1D("pyParticle5Hist", "Particle5 py momentum", 100, -150, 150);
    TH1D *pzParticle5Hist = new TH1D("pzParticle5Hist", "Particle5 pz momentum", 100, -150, 150);
    TH1D *pParticle5Hist = new TH1D("pParticle5Hist", "Particle5 transverse momentum", 100, -150, 150);
    TProfile *Particle5Profile = new TProfile("Particle5Profile", "Particle5 <pT> vs Charged Multiplicity",57, 0, 57);
    TProfile *Particle5ThrustProfile = new TProfile("Particle5ThrustProfile", "Particle5 Thrust axis <pT> vs Charged Multiplicity",57, 0, 57);

    const int Particle6PDG = 3312;
    TH1D *Particle6Hist = new TH1D("Particle6Hist", "Number of Particle6", 20, 0, 20);
    TH1D *pxParticle6Hist = new TH1D("pxParticle6Hist", "Particle6 px momentum", 100, -150, 150);
    TH1D *pyParticle6Hist = new TH1D("pyParticle6Hist", "Particle6 py momentum", 100, -150, 150);
    TH1D *pzParticle6Hist = new TH1D("pzParticle6Hist", "Particle6 pz momentum", 100, -150, 150);
    TH1D *pParticle6Hist = new TH1D("pParticle6Hist", "Particle6 transverse momentum", 100, -150, 150);
    TProfile *Particle6Profile = new TProfile("Particle6Profile", "Particle6 <pT> vs Charged Multiplicity",57, 0, 57);
    TProfile *Particle6ThrustProfile = new TProfile("Particle6ThrustProfile", "Particle6 Thrust axis <pT> vs Charged Multiplicity",57, 0, 57);
//****************************************************************************************** 
//****************************************************************************************** Load data
    // 2. Load Data
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

    // This is where we define the save location of the root file
    const char* daSave = "/USERS/magnussellebjerg/BA/plots/daArticleParticles.root";
    const char* mcSave = "/USERS/magnussellebjerg/BA/plots/mcArticleParticles.root";

//****************************************************************************************** Define cuts
    // Cuts
    double_t momentumCut = 45.0;

//*************************************************************************************************** Data Loop
    for (Long64_t i = 0; i < numberOfEntries; i ++){
        t.fChain->GetEntry(i);
        mcflg = (bool)t.mcflavor;

        int chargeMulti = 0;

        int Particle1Count = 0;
        double_t pParticle1 = 0;
        double_t pThrustParticle1 = 0;
        double_t pParticle1Mean = 0;
        double_t pThrustParticle1Mean = 0;

        int Particle2Count = 0;
        double_t pParticle2 = 0;
        double_t pThrustParticle2 = 0;
        double_t pParticle2Mean = 0;
        double_t pThrustParticle2Mean = 0;

        int Particle3Count =0;
        double_t pParticle3 = 0;
        double_t pThrustParticle3 = 0;
        double_t pParticle3Mean = 0;
        double_t pThrustParticle3Mean = 0;

        int Particle4Count = 0;
        double_t pParticle4 = 0;
        double_t pThrustParticle4 = 0;
        double_t pParticle4Mean = 0;
        double_t pThrustParticle4Mean = 0;

        int Particle5Count = 0;
        double_t pParticle5 = 0;
        double_t pThrustParticle5 = 0;
        double_t pParticle5Mean = 0;
        double_t pThrustParticle5Mean = 0;

        int Particle6Count =0;
        double_t pParticle6 = 0;
        double_t pThrustParticle6 = 0;
        double_t pParticle6Mean = 0;
        double_t pThrustParticle6Mean = 0;

        float_t thrustx = 0;
        float_t thrusty = 0;
        float_t thrustz = 0;
        float_t pperp = 0;
  
        bool skipEvent = false;

        // if (t.cmenergy > 90.8 &&  t.cmenergy < 91.6 && 1-t.thru[2] < 0.1){
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

                if (truepdg != 0){
                    if( particle->Charge() !=0 ){
                        chargeMulti +=1;
                    }
                }
            }
            // When one particle has an abnormal momentum a bunch of other entries in the event also do. Thus, the whole event is skipped.
            if (skipEvent) continue;

            for (int j = 0; j < t.npart; j++){

                // Here we create the thrust vector
                thrustx=sqrt(1.-t.thru[0]*t.thru[0])*cos(t.thru[1]);
                thrusty=sqrt(1.-t.thru[0]*t.thru[0])*sin(t.thru[1]);
                thrustz=fabs(t.thru[0]);
      
                int truepdg = nanoConvMC((int)t.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                if (truepdg == Particle1PDG){
                    Particle1Count += 1;
                    pParticle1 += sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]);
                    pThrustParticle1 += pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz);
                    // pxParticle1Hist->Fill(t.pmomx[j]);
                    // pyParticle1Hist->Fill(t.pmomy[j]);
                    // pzParticle1Hist->Fill(t.pmomz[j]);
                    Particle1Profile->Fill(chargeMulti,sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));
                    Particle1ThrustProfile->Fill(chargeMulti,pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz));
                }

                if (truepdg == Particle2PDG){
                    Particle2Count += 1;
                    pParticle2 += sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]);
                    pThrustParticle2 += pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz);
                    // pxParticle2Hist->Fill(t.pmomx[j]);
                    // pyParticle2Hist->Fill(t.pmomy[j]);
                    // pzParticle2Hist->Fill(t.pmomz[j]);
                    Particle2Profile->Fill(chargeMulti,sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));
                    Particle2ThrustProfile->Fill(chargeMulti,pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz));
                }

                if (truepdg == Particle3PDG){
                    Particle3Count += 1;
                    pParticle3 += sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]);
                    pThrustParticle3 += pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz);

                
                    // pxParticle3Hist->Fill(t.pmomx[j]);
                    // pyParticle3Hist->Fill(t.pmomy[j]);
                    // pzParticle3Hist->Fill(t.pmomz[j]);
                    Particle3Profile->Fill(chargeMulti,sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));
                    Particle3ThrustProfile->Fill(chargeMulti,pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz));

                }

                if (truepdg == Particle4PDG){
                    Particle4Count += 1;
                    pParticle4 += sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]);
                    pThrustParticle4 += pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz);
                    // pxParticle4Hist->Fill(t.pmomx[j]);
                    // pyParticle4Hist->Fill(t.pmomy[j]);
                    // pzParticle4Hist->Fill(t.pmomz[j]);
                    Particle4Profile->Fill(chargeMulti,sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));
                    Particle4ThrustProfile->Fill(chargeMulti,pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz));


                }

                if (truepdg == Particle5PDG){
                    Particle5Count += 1;
                    pParticle5 += sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]);
                    pThrustParticle5 += pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz);
                    // pxParticle5Hist->Fill(t.pmomx[j]);
                    // pyParticle5Hist->Fill(t.pmomy[j]);
                    // pzParticle5Hist->Fill(t.pmomz[j]);
                    Particle5Profile->Fill(chargeMulti,sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));
                    Particle5ThrustProfile->Fill(chargeMulti,pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz));
                }

                if (truepdg == Particle6PDG){
                    Particle6Count += 1;
                    pParticle6 += sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]);
                    pThrustParticle6 += pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz);

                
                    // pxParticle6Hist->Fill(t.pmomx[j]);
                    // pyParticle6Hist->Fill(t.pmomy[j]);
                    // pzParticle6Hist->Fill(t.pmomz[j]);
                    Particle6Profile->Fill(chargeMulti,sqrt(t.pmomx[j]*t.pmomx[j] + t.pmomy[j]*t.pmomy[j]));
                    Particle6ThrustProfile->Fill(chargeMulti,pPerpendicularThrust(t.pmomx[j],t.pmomy[j],t.pmomz[j],thrustx,thrusty,thrustz));

                }

            }
            
            ChargedMultiHist->Fill(chargeMulti);

            Particle1Hist->Fill(Particle1Count);
            pParticle1Hist->Fill(pParticle1);

            Particle2Hist->Fill(Particle2Count);
            pParticle2Hist->Fill(pParticle2);
         
            Particle3Hist->Fill(Particle3Count);
            pParticle3Hist->Fill(pParticle3);

            Particle4Hist->Fill(Particle4Count);
            pParticle4Hist->Fill(pParticle4);

            Particle5Hist->Fill(Particle5Count);
            pParticle5Hist->Fill(pParticle5);
         
            Particle6Hist->Fill(Particle6Count);
            pParticle6Hist->Fill(pParticle6);

        }
    }   
//****************************************************************************************** 
//****************************************************************************************** Printing plots
    if (printPlots == true){
    // Draw TRatioPlot
        TCanvas *c1 = new TCanvas("c1", "Profile for Particle1 and Particle2", 800, 600);

        c1->Divide(2,3);
        c1->cd(1);
        Particle1Profile->SetTitle("Particle1"); 
        Particle1Profile->SetXTitle("Charged Multiplicity");
        Particle1Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle1Profile->Draw("SAME"); 

        c1->cd(2);
        Particle2Profile->SetTitle("Particle2"); 
        Particle2Profile->SetXTitle("Charged Multiplicity");
        Particle2Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle2Profile->Draw("SAME"); 

        c1->cd(3);
        Particle3Profile->SetTitle("Particle3"); 
        Particle3Profile->SetXTitle("Charged Multiplicity");
        Particle3Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle3Profile->Draw("SAME"); 

        c1->cd(4);
        Particle4Profile->SetTitle("Particle 4"); 
        Particle4Profile->SetXTitle("Charged Multiplicity");
        Particle4Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle4Profile->Draw("SAME"); 

        c1->cd(5);
        Particle5Profile->SetTitle("Particle 5"); 
        Particle5Profile->SetXTitle("Charged Multiplicity");
        Particle5Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle5Profile->Draw("SAME"); 

        c1->cd(6);
        Particle6Profile->SetTitle("Particle 6"); 
        Particle6Profile->SetXTitle("Charged Multiplicity");
        Particle6Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle6Profile->Draw("SAME"); 
    }
//****************************************************************************************** 
//****************************************************************************************** Saving Plots

    if (savePlots == true){
    // 5. Save histograms
        TFile *outFile = new TFile(mcflg ? mcSave : daSave, "RECREATE");
        
        ChargedMultiHist->Write();

        Particle1Profile->SetTitle("Profile particle1");  // Title inside the plot
        Particle1Profile->SetXTitle("Charge Multiplicity ");
        Particle1Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle1Profile->Write();  // "E" ensures error bars are displayed
        Particle1Hist->Write();
        pParticle1Hist->Write();


        Particle2Profile->SetTitle("Profile Particle2");  // Title inside the plot
        Particle2Profile->SetXTitle("Charge Multiplicity");
        Particle2Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle2Profile->Write();  // "E" ensures error bars are displayed
        Particle2Hist->Write();
        pParticle2Hist->Write();


        Particle3Profile->SetTitle("Profile Particle3");  // Title inside the plot
        Particle3Profile->SetXTitle("Charge Multiplicity");
        Particle3Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle3Profile->Write();  // "E" ensures error bars are displayed
        Particle3Hist->Write();
        pParticle3Hist->Write();


        Particle4Profile->SetTitle("Profile Particle4");  // Title inside the plot
        Particle4Profile->SetXTitle("Charge Multiplicity ");
        Particle4Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle4Profile->Write();  // "E" ensures error bars are displayed
        Particle4Hist->Write();
        pParticle4Hist->Write();


        Particle5Profile->SetTitle("Profile Particle5");  // Title inside the plot
        Particle5Profile->SetXTitle("Charge Multiplicity");
        Particle5Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle5Profile->Write();  // "E" ensures error bars are displayed
        Particle5Hist->Write();
        pParticle5Hist->Write();


        Particle6Profile->SetTitle("Profile Particle6");  // Title inside the plot
        Particle6Profile->SetXTitle("Charge Multiplicity");
        Particle6Profile->SetYTitle(" <p_{T}> (GeV)");
        Particle6Profile->Write();  // "E" ensures error bars are displayed
        Particle6Hist->Write();
        pParticle6Hist->Write();

        outFile->Close();
    }
}