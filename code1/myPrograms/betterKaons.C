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



void betterKaons()
{   
    int setNumberOfFiles = 1;
    int printPlots = true ;
    bool mcflg = true ;

//****************************************************************************************** Define plots
    //1. Define histograms
    //Kaons 
    TH1D *KaonPlusHist = new TH1D("KaonPlusHist", "Number of #K^{+}", 57, 0, 57);
    TH1D *KaonMinusHist = new TH1D("KaonMinusHist", "Number of#K^{-}", 57, 0, 57);
    TH1D *KaonNeutralHist = new TH1D("KaonNeutralHist", "Number of#K^{0}", 57, 0, 57);
    TH1D *KaonTotalHist = new TH1D("KaonTotalHist", "Total number of #K", 57, 0, 57);

    TH1D *pKaonPlusHist = new TH1D("pKaonPlusHist", "#K^{+} transverse momentum", 57, 0, 57);
    TH1D *pKaonMinusHist = new TH1D("pKaonMinusHist", "#K^{-} transverse momentum", 57, 0, 57);
    TH1D *pKaonNeutralHist = new TH1D("pKaonNeutralHist", "#K^{0} transverse momentum", 57, 0, 57);

    TH1D *ChargedMultiHist = new TH1D("ChargedMultiHist", "Charged Particle Multiplicity", 57, 0, 57);

    TProfile *ProfileKaonMinus = new TProfile("ProfileKaonMinus", "<pT> vs Multiplicity",57, 0, 57);
    TProfile *ProfileKaonPlus = new TProfile("ProfileKaonPlus", "<pT> vs Multiplicity",57, 0, 57);
    TProfile *ProfileKaonNeutral = new TProfile("ProfileKaonNeutral", "<pT> vs Multiplicity",57, 0, 57);


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
    Long64_t NumberOfEntries = t.fChain->GetEntries();
//******************************************************************************************

    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();   

    // 4. Process Data Loop 
    int CurrentFileNumber = -1;
    int FilesProcessed = 0;
//*************************************************************************************************** Data Loop
  
    for (Long64_t i = 0; i < NumberOfEntries; i ++){
        t.fChain->GetEntry(i);
        mcflg = (bool)t.mcflavor;

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
            int KaonPlus = 0;
            int KaonMinus = 0;
            int KaonNeutral = 0;
            int KaonAll =0;
            int charge = 0;

            double_t pKaonNeutral = 0;
            double_t pKaonPlus = 0;
            double_t pKaonMinus = 0;

            double_t pKaonNeutralMean = 0;
            double_t pKaonPlusMean = 0;
            double_t pKaonMinusMean = 0;

            bool skipEvent = false;
        
            for (int j = 0; j < t.npart; j++){
                if ( abs(t.pmomx[j]) > 45 |abs(t.pmomy[j]) > 45| abs(t.pmomz[j]) > 45 ){
                    skipEvent = true;
                    break;
                }
                int truepdg = nanoConvMC((int)t.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                if (truepdg != 0){
                    if( particle->Charge() !=0 ){
                        charge +=1;
                    }
                }
            }
            
            if (skipEvent) continue;

            for (int j = 0; j < t.npart; j++){
                int truepdg = nanoConvMC((int)t.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 
            

                if (truepdg == 321){
                    KaonPlus += 1;
                    KaonAll += 1;
                    pKaonPlus += sqrt(t.pmomx[j]*t.pmomx[j] +t.pmomy[j]*t.pmomy[j]);
                    pKaonPlusMean = pKaonPlus / KaonPlus;
                    
                }

                if (truepdg == -321){
                    KaonMinus += 1;
                    KaonAll += 1;
                    pKaonMinus += sqrt(t.pmomx[j]*t.pmomx[j] +t.pmomy[j]*t.pmomy[j]);
                    pKaonMinusMean = pKaonMinus / KaonMinus;
                }

                // No PDG conversion for neutral Kaons
                if (truepdg == 311){
                    KaonNeutral += 1;
                    KaonAll += 1;
                    pKaonNeutral += sqrt(t.pmomx[j]*t.pmomx[j] +t.pmomy[j]*t.pmomy[j]);
                    pKaonNeutralMean = pKaonNeutral / KaonNeutral;
                }


            }
            // Number of Kaons fill
            KaonPlusHist->Fill(KaonPlus);
            KaonMinusHist->Fill(KaonMinus);
            KaonNeutralHist->Fill(KaonNeutral);
            KaonTotalHist->Fill(KaonAll);

            // Total Momentum of Kaons fill
            pKaonPlusHist->Fill(pKaonPlus);
            pKaonMinusHist->Fill(pKaonMinus);
            pKaonNeutralHist->Fill(pKaonNeutral);


            ProfileKaonPlus->Fill(charge,pKaonPlusMean);  // ⟨pT⟩ vs Multiplicity
            ProfileKaonMinus->Fill(charge,pKaonMinusMean );  // ⟨pT⟩ vs Multiplicity
            ProfileKaonNeutral->Fill(charge,pKaonNeutralMean); 
            // Charged multiplicity fill
            ChargedMultiHist->Fill(charge);



        }
    }   


if (printPlots == true){


// 6. Draw TRatioPlot
// TCanvas *c1 = new TCanvas("c1", "#K^{-} and #K^{+}", 1000, 600);
// pKaonPlusHist->Draw("same");
// KaonMinusHist->Draw("same");
// KaonTotalHist->Draw("same");
// ChargedMultiHist->Draw("same");

// c1->Divide(2,1);
// c1->cd(1);

// ProfileKaonMinus->SetTitle(" #K^{-}");  // Title inside the plot
// ProfileKaonMinus->SetXTitle("Multiplicity (npart)");
// ProfileKaonMinus->SetYTitle(" <p_{T}> (GeV)");
// ProfileKaonMinus->Draw("");  // "E" ensures error bars are displayed


// c1->cd(2);
// ProfileKaonPlus->SetTitle(" #K^{+}");  // Title inside the plot
// ProfileKaonPlus->SetXTitle("Multiplicity (npart)");
// ProfileKaonPlus->SetYTitle(" <p_{T}> (GeV)");
// ProfileKaonPlus->Draw("");  // "E" ensures error bars are displayed


// // Create  new canvas
// TCanvas *c2 = new TCanvas("c2", "Ratio Plot", 800, 600);
// Chain->Draw("cmenergy");


// 7. Save histograms

TFile *outFile = new TFile(mcflg ? "/USERS/magnussellebjerg/BA/plots/mcKaons.root" : "/USERS/magnussellebjerg/BA/plots/daKaons.root", "RECREATE");
// Number of Kaons in histogrms
KaonPlusHist->Write();
KaonMinusHist->Write();
KaonNeutralHist->Write();
KaonTotalHist->Write();

// Summed momentum of Kaons
pKaonPlusHist->Write();
pKaonMinusHist->Write();
pKaonNeutralHist->Write();
ChargedMultiHist->Write();

ProfileKaonPlus->SetTitle("K^{+}");  // Title inside the plot
ProfileKaonPlus->SetXTitle("N_{charged}");
ProfileKaonPlus->SetYTitle(" <p_{T}> (GeV)");
ProfileKaonPlus->Write();  // "E" ensures error bars are displayed

ProfileKaonMinus->SetTitle(" K^{-}");  // Title inside the plot
ProfileKaonMinus->SetXTitle("N_{charged}");
ProfileKaonMinus->SetYTitle(" <p_{T}> (GeV)");
ProfileKaonMinus->Write();  // "E" ensures error bars are displayed

ProfileKaonNeutral->SetTitle(" K^{0}");  // Title inside the plot
ProfileKaonNeutral->SetXTitle("N_{charged}");
ProfileKaonNeutral->SetYTitle(" <p_{T}> (GeV)");
ProfileKaonNeutral->Write();  // "E" ensures error bars are displayed

// mcChargedMultiHist->Write();
// profile->Write();
outFile->Close();

}
}
