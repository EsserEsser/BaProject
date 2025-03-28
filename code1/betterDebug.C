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

void betterDebug()
{   
    int setNumberOfFiles = 1;
    bool mcflg = true ;
    bool printPlots = false;
    bool savePlots = false ;
//****************************************************************************************** Define plots
    //1. Define histograms

    TH1D *ChargedMultiHist = new TH1D("ChargedMultiHist", "Charged Particle Multiplicity", 57, 0, 57);
    TH1D *Particle1Hist = new TH1D("PartHist", "Number of #Protons", 57, 0, 57);
    TH1D *pxParticle1Hist = new TH1D("pxParticle1Hist", "Particle1 px momentum", 100, -150, 150);
    TH1D *pyParticle1Hist = new TH1D("pyParticle1Hist", "Particle1 py momentum", 100, -150, 150);
    TH1D *pzParticle1Hist = new TH1D("pzParticle1Hist", "Particle1 pz momentum", 100, -150, 150);
    TH1D *pParticle1Hist = new TH1D("pParticle1Hist", "Particle1 transverse momentum", 100, -150, 150);
    TProfile *Particle1Profile = new TProfile("Particle1Profile", "Particle1 <pT> vs Charged Multiplicity",57, 0, 57);

    TH1D *Particle2Hist = new TH1D("PartHist", "Number of #Protons", 57, 0, 57);
    TH1D *pxParticle2Hist = new TH1D("pxParticle2Hist", "Particle2 px momentum", 100, -150, 150);
    TH1D *pyParticle2Hist = new TH1D("pyParticle2Hist", "Particle2 py momentum", 100, -150, 150);
    TH1D *pzParticle2Hist = new TH1D("pzParticle2Hist", "Particle2 pz momentum", 100, -150, 150);
    TH1D *pParticle2Hist = new TH1D("pParticle2Hist", "Particle2 transverse momentum", 100, -150, 150);
    TProfile *Particle2Profile = new TProfile("Particle2Profile", "Particle2 <pT> vs Charged Multiplicity",57, 0, 57);

    TH1D *Particle3Hist = new TH1D("PartHist", "Number of #Protons", 57, 0, 57);
    TH1D *pxParticle3Hist = new TH1D("pxParticle3Hist", "Particle3 px momentum", 100, -150, 150);
    TH1D *pyParticle3Hist = new TH1D("pyParticle3Hist", "Particle3 py momentum", 100, -150, 150);
    TH1D *pzParticle3Hist = new TH1D("pzParticle3Hist", "Particle3 pz momentum", 100, -150, 150);
    TH1D *pParticle3Hist = new TH1D("pParticle3Hist", "Particle3 transverse momentum", 100, -150, 150);
    TProfile *Particle3Profile = new TProfile("Particle3Profile", "Particle3 <pT> vs Charged Multiplicity",57, 0, 57);



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
    tChain->Add("/USERS/magnussellebjerg/BA/data/zqqda95.root");

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

    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();   
    int Particle1PDG = 321;
    int Particle2PDG = -321;
    int Particle3PDG = 311;

    // This is where we define the save location of the root file
    const char* mcSave = "/USERS/magnussellebjerg/BA/plots/mcProtons.root";
    const char* daSave = "/USERS/magnussellebjerg/BA/plots/daProtons.root";

    // Cuts
    double_t momentumCut = 150.0;

    // int ch[10];
    // float n[10];
    int ch0 = 0;
    int ch1 = 0;
    int ch2 = 0;
    int ch3 = 0;
    int ch4 = 0;
    int ch5 = 0;
    int ch6 = 0;
    int ch7 = 0;
    int ch8 = 0;
    int ch9 = 0;
    int ch10 = 0;

    float n0 = 0;
    float n1 = 0;
    float n2 = 0;
    float n3 = 0;
    float n4 = 0;
    float n5 = 0;
    float n6 = 0;
    float n7 = 0;
    float n8 = 0;
    float n9 = 0;
    float n10 = 0;

//*************************************************************************************************** Data Loop
  
    for (Long64_t i = 0; i < numberOfEntries; i ++){
        t.fChain->GetEntry(i);
        mcflg = (bool)t.mcflavor;

        int chargeMulti = 0;

        int Particle1Count = 0;
        double_t pParticle1 = 0;
        double_t pParticle1Mean = 0;

        int Particle2Count = 0;
        double_t pParticle2 = 0;
        double_t pParticle2Mean = 0;

        int Particle3Count =0;
        double_t pParticle3 = 0;
        double_t pParticle3Mean = 0;

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
                if ( abs(t.pmomx[j]) > momentumCut |abs(t.pmomy[j]) > momentumCut| abs(t.pmomz[j]) > momentumCut ){
                    skipEvent = true;
                }
                if (skipEvent) break;

                int truepdg = nanoConvMC((int)t.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                if (truepdg != 0){
                    if( particle->Charge() !=0 ){
                        chargeMulti +=1;
                    }
                }
            }

            if (skipEvent) continue;
            if (chargeMulti == 0){
                ch0 ++;
                n0 += t.npart;
                cout << "Number of Particles = " << t.npart <<" Charge = " << chargeMulti << endl;
                for (int j = 0; j < t.npart;j++){
                    cout << "id" <<(int)t.ptype[j] << " Momenta = " << abs(t.pmomx[j]) << ", " << abs(t.pmomy[j]) << ", " << abs(t.pmomy[j])<<endl;
                }
            }   
            if (chargeMulti == 1){
                ch1 ++;
                n1 += t.npart;
                cout << "Number of Particles = " << t.npart <<" Charge = " << chargeMulti << endl;
                for (int j = 0; j < t.npart;j++){
                    cout << "id" <<(int)t.ptype[j] << " Momenta = " << abs(t.pmomx[j]) << ", " << abs(t.pmomy[j]) << ", " << abs(t.pmomy[j])<<endl;
                }
            }   
            if (chargeMulti == 2){
                ch2++;
                n2 += t.npart;
            }
            if (chargeMulti == 3){
                ch3++;
                n3 += t.npart;
            }
            if (chargeMulti == 4){
                ch4++;
                n4 += t.npart;
            }
            if (chargeMulti == 5){
                ch5++;
                n5 += t.npart;
            }
            if (chargeMulti == 6){
                ch6++;
                n6 += t.npart;
            }
            if (chargeMulti == 7){
                ch7++;
                n7 += t.npart;
            }
            if (chargeMulti == 8){
                ch8++;
                n8 += t.npart;
            }
            if (chargeMulti == 9){
                ch9++;
                n9 += t.npart;
            }
            if (chargeMulti == 10){
                ch10++;
                n10 += t.npart;
            }

        }
    } 
    if (ch0 > 0){
        cout << ch0 << " and average npart = " << static_cast<float>(n0)/ch0 << endl;
    } else {
        cout << "ch0 is zero or negative, skipping." << endl;
    }
    if (ch1 > 0){
        cout << ch1 << " and average npart = " << static_cast<float>(n1)/ch1 << endl;
    } else {
        cout << "ch1 is zero or negative, skipping." << endl;
    }
    
    if (ch2 > 0){
        cout << ch2 << " and average npart = " << static_cast<float>(n2)/ch2 << endl;
    } else {
        cout << "ch2 is zero or negative, skipping." << endl;
    }
    
    if (ch3 > 0){
        cout << ch3 << " and average npart = " << static_cast<float>(n3)/ch3 << endl;
    } else {
        cout << "ch3 is zero or negative, skipping." << endl;
    }
    
    if (ch4 > 0){
        cout << ch4 << " and average npart = " << static_cast<float>(n4)/ch4 << endl;
    } else {
        cout << "ch4 is zero or negative, skipping." << endl;
    }
    
    if (ch5 > 0){
        cout << ch5 << " and average npart = " << static_cast<float>(n5)/ch5 << endl;
    } else {
        cout << "ch5 is zero or negative, skipping." << endl;
    }
    
    if (ch6 > 0){
        cout << ch6 << " and average npart = " << static_cast<float>(n6)/ch6 << endl;
    } else {
        cout << "ch6 is zero or negative, skipping." << endl;
    }
    
    if (ch7 > 0){
        cout << ch7 << " and average npart = " << static_cast<float>(n7)/ch7 << endl;
    } else {
        cout << "ch7 is zero or negative, skipping." << endl;
    }
    
    if (ch8 > 0){
        cout << ch8 << " and average npart = " << static_cast<float>(n8)/ch8 << endl;
    } else {
        cout << "ch8 is zero or negative, skipping." << endl;
    }
    
    if (ch9 > 0){
        cout << ch9 << " and average npart = " << static_cast<float>(n9)/ch9 << endl;
    } else {
        cout << "ch9 is zero or negative, skipping." << endl;
    }
    
    if (ch10 > 0){
        cout << ch10 << " and average npart = " << static_cast<float>(n10)/ch10 << endl;
    } else {
        cout << "ch10 is zero or negative, skipping." << endl;
    }
    
    

    if (printPlots == true){
    // Draw TRatioPlot
    TCanvas *c1 = new TCanvas("c1", "Profile for Particle1 and Particle2", 800, 600);

    c1->Divide(2,1);
    c1->cd(1);
    Particle1Profile->SetTitle("Particle 1"); 
    Particle1Profile->SetXTitle("Charged Multiplicity");
    Particle1Profile->SetYTitle(" <p_{T}> (GeV)");
    Particle1Profile->Draw("SAME"); 

    c1->cd(2);
    Particle2Profile->SetTitle("Particle 2"); 
    Particle2Profile->SetXTitle("Charged Multiplicity");
    Particle2Profile->SetYTitle(" <p_{T}> (GeV)");
    Particle2Profile->Draw("SAME"); 

    }

    if (savePlots == true){

    // 5. Save histograms

    TFile *outFile = new TFile(mcflg ? mcSave : daSave, "RECREATE");
    
    ChargedMultiHist->Write();

    Particle1Hist->Write();
    pParticle1Hist->Write();
    Particle1Profile->SetTitle("Profile particle1");  // Title inside the plot
    Particle1Profile->SetXTitle("Charge Multiplicity ");
    Particle1Profile->SetYTitle(" <p_{T}> (GeV)");
    Particle1Profile->Write();  // "E" ensures error bars are displayed

    Particle2Hist->Write();
    pParticle2Hist->Write();
    Particle2Profile->SetTitle("Profile Particle2");  // Title inside the plot
    Particle2Profile->SetXTitle("Charge Multiplicity");
    Particle2Profile->SetYTitle(" <p_{T}> (GeV)");
    Particle2Profile->Write();  // "E" ensures error bars are displayed

    Particle3Hist->Write();
    pParticle3Hist->Write();
    Particle3Profile->SetTitle("Profile Particle3");  // Title inside the plot
    Particle3Profile->SetXTitle("Charge Multiplicity");
    Particle3Profile->SetYTitle(" <p_{T}> (GeV)");
    Particle3Profile->Write();  // "E" ensures error bars are displayed

    outFile->Close();
    }
}
