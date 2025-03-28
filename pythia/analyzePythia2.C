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
#include "smalldataTreePythia.h"
#include "smalldataTreePythia.C"
#include <TRatioPlot.h> 
using namespace std;



void analyzePythia2()
{   
    int setNumberOfFiles = 1;
    int printPlots = false ;
    bool skipEvent = false ;
    bool mcflg = true ;
//****************************************************************************************** Define plots
    //1. Define histograms
    //Pions 
    TH1D *PionPlusHist = new TH1D("PionPlusHist", "Number of #pi^{+}", 50, 0, 50);
    TH1D *PionMinusHist = new TH1D("PionMinusHist", "Number of #pi^{-}", 50, 0, 50);
    TH1D *PionNeutralHist = new TH1D("PionNeutralHist", "Number of #pi^{0}", 50, 0, 50);
    TH1D *PionTotalHist = new TH1D("PionTotalHist", "Total number of #pi", 50, 0, 50);

    TH1D *pPionPlusHist = new TH1D("pPionPlusHist", "#pi^{+} transverse momentum", 60, -45, 45);
    TH1D *pPionMinusHist = new TH1D("pPionMinusHist", "#pi^{-} transverse momentum", 60, -45, 45);
    TH1D *pPionNeutralHist = new TH1D("pPionNeutralHist", "#pi^{0} transverse momentum",60, -45, 45);

    TH1D *ChargedMultiHist = new TH1D("ChargedMultiHist", "Charged Particle Multiplicity", 60, 0, 60);

    TProfile *ProfilePionMinus = new TProfile("ProfilePionMinus", "<pT> vs Multiplicity",60, 0, 60);
    TProfile *ProfilePionPlus = new TProfile("ProfilePionPlus", "<pT> vs Multiplicity",60, 0, 60);
    TProfile *ProfilePionNeutral = new TProfile("ProfilePionNeutral", "<pT> vs Multiplicity",60, 0, 60);


    //Kaons
//******************************************************************************************

    
//****************************************************************************************** Load data
    // 2. Load Data
    /*We create a Tchain with all the trees from both data and simulation
    the "smalldataTreePythia" files take care of loading branches and defining*/
    TChain *tChain = new TChain("tree");

    tChain->Add("/USERS/magnussellebjerg/BA/pythia/dirtyData.root");
  

    smalldataTreePythia t(tChain);
    Long64_t numberOfEntries = t.fChain->GetEntries();
    cout << numberOfEntries << endl;
//******************************************************************************************

    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();   

    // 4. Process Data Loop 
    int CurrentFileNumber = -1;
    int FilesProcessed = 0;
//*************************************************************************************************** Data Loop
  
    for (Long64_t i = 0; i < numberOfEntries; i ++){
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
            int PionPlus = 0;
            int PionMinus = 0;
            int PionNeutral = 0;
            int PionAll =0;
            int charge = 0;

            double_t pPionNeutral = 0;
            double_t pPionPlus = 0;
            double_t pPionMinus = 0;

            double_t pPionNeutralMean = 0;
            double_t pPionPlusMean = 0;
            double_t pPionMinusMean = 0;

            for (int j = 0; j < t.npart; j++){

                if ( abs(t.pmomx[j]) > 45 |abs(t.pmomy[j]) > 45| abs(t.pmomz[j]) > 45 ){
                    skipEvent = true;
                    break;
                }
                int truepdg = t.ptype[j];
                TParticlePDG* particle =  pdg->GetParticle(truepdg);
                if (!particle) continue;
                if (!particle->Charge()) continue;


                if (truepdg != 0){
                    if( particle->Charge() !=0 ){
                        charge +=1;
                    }
                }
            }
            if (skipEvent) continue;

            for (int j = 0; j < t.npart; j++){
                
                int truepdg = (int)t.ptype[j];
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 
                if (!particle) continue;
                if (!particle->Charge()) continue;
            

                if (truepdg == 211){
                    PionPlus += 1;
                    PionAll += 1;
                    pPionPlus += sqrt(t.pmomx[j]*t.pmomx[j] +t.pmomy[j]*t.pmomy[j]);
                    pPionPlusMean = pPionPlus / PionPlus;
            
                }

                if (truepdg == -211){
                    PionMinus += 1;
                    PionAll += 1;
                    pPionMinus += sqrt(t.pmomx[j]*t.pmomx[j] +t.pmomy[j]*t.pmomy[j]);
                    pPionMinusMean = pPionMinus / PionMinus;

                }

                // No PDG conversion for neutral pions
                if (truepdg == 111){
                    PionNeutral += 1;
                    PionAll += 1;
                    pPionNeutral += sqrt(t.pmomx[j]*t.pmomx[j] +t.pmomy[j]*t.pmomy[j]);
                    pPionNeutralMean = pPionNeutral / PionNeutral;
                }


            }
            // Number of Pions fill
            PionPlusHist->Fill(PionPlus);
            PionMinusHist->Fill(PionMinus);
            PionNeutralHist->Fill(PionNeutral);
            PionTotalHist->Fill(PionAll);

            // Total Momentum of Pions fill
            pPionPlusHist->Fill(pPionPlus);
            pPionMinusHist->Fill(pPionMinus);
            pPionNeutralHist->Fill(pPionNeutral);


             // ⟨pT⟩ vs Multiplicity
             ProfilePionPlus->Fill(charge,pPionPlusMean); 
            ProfilePionMinus->Fill(charge,pPionMinusMean );  // ⟨pT⟩ vs Multiplicity
            ProfilePionNeutral->Fill(charge,pPionNeutralMean); 
            // Charged multiplicity fill
            ChargedMultiHist->Fill(charge);

        }
    }   

// 6. Draw TRatioPlot
TCanvas *c1 = new TCanvas("c1", "#pi^{-} and #pi^{+}", 1000, 600);
// tChain->Draw("ptype");
// PionMinusHist->Draw("HIST");
// PionPlusHist->Draw("HIST SAME");
//PionTotalHist->Draw("same");
//ChargedMultiHist->Draw("same");

c1->Divide(2,1);
c1->cd(1);

ProfilePionMinus->SetTitle(" #pi^{-}");  // Title inside the plot
ProfilePionMinus->SetXTitle("Multiplicity (npart)");
ProfilePionMinus->SetYTitle(" <p_{T}> (GeV)");
ProfilePionMinus->Draw("");  // "E" ensures error bars are displayed

c1->cd(2);
ProfilePionPlus->SetTitle(" #pi^{+}");  // Title inside the plot
ProfilePionPlus->SetXTitle("Multiplicity (npart)");
ProfilePionPlus->SetYTitle(" <p_{T}> (GeV)");
ProfilePionPlus->Draw("");  // "E" ensures error bars are displayed

// TCanvas *c2 = new TCanvas("c2", "#pi^{-} and #pi^{+}", 1000, 600);
// ChargedMultiHist->Draw();
if (printPlots == true){



// 7. Save histograms

TFile *outFile = new TFile(mcflg ? "/USERS/magnussellebjerg/BA/pythia/plots/pythiaPlots.root" : "/USERS/magnussellebjerg/BA/pythia/plots/daPions.root", "RECREATE");
// Number of Pions in histogrms
PionPlusHist->Write();
PionMinusHist->Write();
PionNeutralHist->Write();
PionTotalHist->Write();

// Summed momentum of Pions
pPionPlusHist->Write();
pPionMinusHist->Write();
pPionNeutralHist->Write();
ChargedMultiHist->Write();

ProfilePionPlus->SetTitle(" #pi^{+}");  // Title inside the plot
ProfilePionPlus->SetXTitle("#N_{charged}");
ProfilePionPlus->SetYTitle(" <p_{T}> (GeV)");
ProfilePionPlus->Write();  // "E" ensures error bars are displayed

ProfilePionMinus->SetTitle(" #pi^{-}");  // Title inside the plot
ProfilePionMinus->SetXTitle("#N_{charged}");
ProfilePionMinus->SetYTitle(" <p_{T}> (GeV)");
ProfilePionMinus->Write();  // "E" ensures error bars are displayed

ProfilePionNeutral->SetTitle(" #pi^{0}");  // Title inside the plot
ProfilePionNeutral->SetXTitle("#N_{charged}");
ProfilePionNeutral->SetYTitle(" <p_{T}> (GeV)");
ProfilePionNeutral->Write();  // "E" ensures error bars are displayed

// mcChargedMultiHist->Write();
// profile->Write();
outFile->Close();

}
}
