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



void pions()
{
    int setNumberOfFiles = 1;
    int printPlots = true ;

//****************************************************************************************** Define plots
    //1. Define histograms
    //Pions 
    TH1D *daPionNeutralHist = new TH1D("daPionNeutralHist", "#pi{0}", 57, 0, 57);
    TH1D *daPionPlusHist = new TH1D("daPionPlusHist", "#pi{-}", 57, 0, 57);
    TH1D *daPionMinusHist = new TH1D("daPionMinusHist", "#pi{-}", 57, 0, 57);
    TH1D *daPionTotalHist = new TH1D("daPionTotalHist", "all #pi", 57, 0, 57);
    TH1D *dapPionPlusHist = new TH1D("dapPionTotalHist", "all #pi", 57, 0, 57);

    TH1D *daChargedMultiHist = new TH1D("daMultiHist", "Charged Particle Multiplicity", 57, 0, 57);


    TProfile *daProfilePionMinus = new TProfile("daProfilePionMinus", "<pT> vs Multiplicity",57, 0, 57);
    TProfile *daProfilePionPlus = new TProfile("daProfilePionPlus", "<pT> vs Multiplicity",57, 0, 57);

    TH1D *mcPionNeutralHist = new TH1D("mcPionNeutralHist", "#pi{0}", 57, 0, 57);
    TH1D *mcPionPlusHist = new TH1D("mcPionPlusHist", "#pi{-}", 57, 0, 57);
    TH1D *mcPionMinusHist = new TH1D("mcPionMinusHist", "#pi{-}", 57, 0, 57);
    TH1D *mcPionTotalHist = new TH1D("mcPionTotalHist", "all #pi", 57, 0, 57);
    TH1D *mcChargedMultiHist = new TH1D("mcMultiHist", "Charged Particle Multiplicity", 57, 0, 57);
    TH1D *mcpPionPlusHist = new TH1D("mcpPionTotalHist", "all #pi", 57, 0, 57);

    TProfile *mcProfilePionMinus = new TProfile("mcProfilePionMinus", "<pT> vs Multiplicity",57, 0, 57);
    TProfile *mcProfilePionPlus = new TProfile("mcProfilePionPlus", "<pT> vs Multiplicity",57, 0, 57);

    //Kaons
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



    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();   

    std::vector<int> daMulti;
    std::vector<int> mcMulti;

    

    // 4. Process Data Loop 
    int daCurrentFileNumber = -1;
    int daFilesProcessed = 0;
//*************************************************************************************************** Data Loop
  
    for (Long64_t i = 0; i < daNumberOfEntries; i ++){
        da.fChain->GetEntry(i);
        if (da.cmenergy > 90.8 &&  da.cmenergy < 91.6){

            Long64_t localEntry = da.fChain->LoadTree(i);
            int newFileNumber = daChain->GetTreeNumber();
            if (newFileNumber != daCurrentFileNumber) {
                daCurrentFileNumber = newFileNumber;
                daFilesProcessed++;
                if (daFilesProcessed > setNumberOfFiles){
                    break;}
                std::cout << "=== New file loaded: "
                            << daChain->GetCurrentFile()->GetName()
                            << " ===" << std::endl;
            }
            int pionNeutral = 0;
            int pionPlus = 0;
            int pionMinus = 0;
            int pionAll =0;
            int charge = 0;
            double_t pPionPlus = 0;
            double_t pPionMinus = 0;
            double_t pPionPlusMean = 0;
            double_t pPionMinusMean = 0;
        
            for (int j = 0; j < da.npart; j++){
                int truepdg = nanoConvMC((int)da.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                if (truepdg != 0){
                    if( particle->Charge() !=0 ){
                        charge +=1;
                    }
                }
            }

            for (int j = 0; j < da.npart; j++){
                int truepdg = nanoConvMC((int)da.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 
            
                if (truepdg == 111){
                    pionNeutral += 1;
                    pionAll += 1;
                }
                if (truepdg == 211){
                    pionPlus += 1;
                    pionAll += 1;
                    pPionPlus += sqrt(da.pmomx[j]*da.pmomx[j] +da.pmomy[j]*da.pmomy[j]);
                    pPionPlusMean = pPionPlus / pionPlus;
                    daProfilePionPlus->Fill(charge,pPionPlus );  // ⟨pT⟩ vs Multiplicity
                }

                if (truepdg == -211){
                    pionMinus += 1;
                    pionAll += 1;
                    pPionMinus += sqrt(da.pmomx[j]*da.pmomx[j] +da.pmomy[j]*da.pmomy[j]);
                    pPionMinusMean = pPionMinus / pionMinus;
                    daProfilePionMinus->Fill(charge,pPionMinus );  // ⟨pT⟩ vs Multiplicity
                }
            }
            // daPionNeutralHist->Fill(pionNeutral);
            daPionPlusHist->Fill(pionPlus);
            daPionMinusHist->Fill(pionMinus);
            daPionTotalHist->Fill(pionAll);
            daChargedMultiHist->Fill(charge);
            dapPionPlusHist->Fill(pPionPlus);

            // daProfilePionMinus->Fill(charge,pPionMinusMean );  // ⟨pT⟩ vs Multiplicity
            // daProfilePionPlus->Fill(charge,pPionPlusMean );  // ⟨pT⟩ vs Multiplicity
            
        }
    }   

//*************************************************************************************************** Loop stop

// 5. Process MC Loop
    int mcCurrentFileNumber = -1;
    int mcFilesProcessed = 0;

//*************************************************************************************************** mcData Loop
    for (Long64_t i = 0; i < mcNumberOfEntries; i ++){
        mc.fChain->GetEntry(i);
        if (mc.cmenergy > 90.8 &&  mc.cmenergy < 91.6){

            Long64_t localEntry = mc.fChain->LoadTree(i);
            int newFileNumber = mcChain->GetTreeNumber();
            if (newFileNumber != mcCurrentFileNumber) {
                mcCurrentFileNumber = newFileNumber;
                mcFilesProcessed++;
                if (mcFilesProcessed > setNumberOfFiles){
                    break;}
                std::cout << "=== New file loaded: "
                            << mcChain->GetCurrentFile()->GetName()
                            << " ===" << std::endl;
            }

            int pionNeutral = 0;
            int pionPlus = 0;
            int pionMinus = 0;
            int pionAll = 0;
            int charge = 0;
            double_t pPionPlus = 0;
            double_t pPionMinus = 0;
            double_t pPionPlusMean = 0;
            double_t pPionMinusMean = 0;

            for (int j = 0; j < mc.npart; j++){
                int truepdg = nanoConvMC((int)mc.ptype[j]);
                TParticlePDG* particle =  pdg->GetParticle(truepdg); 

                if (truepdg != 0){
                    if( particle->Charge() !=0 ){
                        charge +=1;
                    }
                }

                if (truepdg == 111){
                    pionNeutral += 1;
                    pionAll += 1;
                }
                if (truepdg == 211){
                    pionPlus += 1;
                    pionAll += 1;
                    pPionPlus += sqrt(da.pmomx[j]*da.pmomx[j] +da.pmomy[j]*da.pmomy[j]);
                    pPionPlusMean = pPionPlus / pionPlus;
                    mcProfilePionPlus->Fill(charge,pPionPlus);  // ⟨pT⟩ vs Multiplicity
                }

                if (truepdg == -211){
                    pionMinus += 1;
                    pionAll += 1;
                    pPionMinus += sqrt(da.pmomx[j]*da.pmomx[j] +da.pmomy[j]*da.pmomy[j]);
                    pPionMinusMean = pPionMinus / pionMinus;
                    mcProfilePionMinus->Fill(charge,pPionMinus);  // ⟨pT⟩ vs Multiplicity
                }
            }
            // daPionNeutralHist->Fill(pionNeutral);
            mcPionPlusHist->Fill(pionPlus);
            mcPionMinusHist->Fill(pionMinus);
            mcPionTotalHist->Fill(pionAll);
            mcChargedMultiHist->Fill(charge);
            mcpPionPlusHist->Fill(pPionPlus);
            

            // mcProfilePionMinus->Fill(charge,pPionMinusMean);  // ⟨pT⟩ vs Multiplicity
            // mcProfilePionPlus->Fill(charge,pPionPlusMean);  // ⟨pT⟩ vs Multiplicity
        }
    }
//*************************************************************************************************** mcData Loop stop


if (mcPionPlusHist->Integral() > 0) {
    mcPionPlusHist->Scale(daPionPlusHist->Integral() / mcPionPlusHist->Integral());
}
if (mcpPionPlusHist->Integral() > 0) {
    mcpPionPlusHist->Scale(dapPionPlusHist->Integral() / mcpPionPlusHist->Integral());
}


if (printPlots == true){


// 6. Draw TRatioPlot
TCanvas *c1 = new TCanvas("c1", "#pi^{-} and #pi^{+}", 1000, 600);
// daPionPlusHist->Draw("same");
// mcPionPlusHist->Draw("same");

dapPionPlusHist->Draw("same");
mcpPionPlusHist->Draw("same");



// daPionMinusHist->Draw("same");
// daPionTotalHist->Draw("same");
// mcChargedMultiHist->Draw("same");
// c1->Divide(2,1);
// c1->cd(1);
// mcProfilePionMinus->SetTitle(" #pi^{-}");  // Title inside the plot
// mcProfilePionMinus->SetXTitle("Multiplicity (npart)");
// mcProfilePionMinus->SetYTitle(" <p_{T}> (GeV)");
// mcProfilePionMinus->Draw("");  // "E" ensures error bars are displayed

// daProfilePionMinus->SetTitle(" #pi^{-}");  // Title inside the plot
// daProfilePionMinus->SetXTitle("Multiplicity (npart)");
// daProfilePionMinus->SetYTitle(" <p_{T}> (GeV)");
// daProfilePionMinus->SetLineColor(kRed); 
// daProfilePionMinus->Draw(" SAME");  // "E" ensures error bars are displayed

// c1->cd(2);
// mcProfilePionPlus->SetTitle(" #pi^{+}");  // Title inside the plot
// mcProfilePionPlus->SetXTitle("Multiplicity (npart)");
// mcProfilePionPlus->SetYTitle(" <p_{T}> (GeV)");
// mcProfilePionPlus->Draw("");  // "E" ensures error bars are displayed

// daProfilePionPlus->SetTitle(" #pi^{+}");  // Title inside the plot
// daProfilePionPlus->SetXTitle("Multiplicity (npart)");
// daProfilePionPlus->SetYTitle(" <p_{T}> (GeV)");
// daProfilePionPlus->SetLineColor(kRed); 
// daProfilePionPlus->Draw(" SAME");  // "E" ensures error bars are displayed

// TCanvas *c2 = new TCanvas("c2", "Ratio Plot", 800, 600);
// mcChain->Draw("cmenergy");


// // 7. Save histograms
// TFile *outFile = new TFile("/USERS/magnussellebjerg/BA/plots/pions.root", "RECREATE");
// daChargedMultiHist->Write();
// mcChargedMultiHist->Write();
// profile->Write();
// outFile->Close();
}
}
