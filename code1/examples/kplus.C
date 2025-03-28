#include <iostream>
#include <sstream>
#include <TFile.h>
#include <TH1F.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <vector>
#include <TDatabasePDG.h>
#include <TParticlePDG.h>
#include "Extract.h"
using namespace std;


void kplus(){

    TH1F *myHist = new TH1F("myHist", "Particle Multiplicity", 100, 0, 57);

    TFile *myFile = new TFile("/USERS/magnussellebjerg/BA/data/zqqda91.root");
    TTree *myTree = (TTree*)myFile->Get("tree");

    //// Print to check Ntuples
    //myTree->Print();

    
    UChar_t         mcflavor;
    Float_t         cmenergy;
    Float_t         thru[3];
    Float_t         pquark[3];
    Float_t         pudsh1;
    Float_t         pudsh2;
    Float_t         b1nn;
    Float_t         b2nn;
    Float_t         ch1nn;
    Float_t         ch2nn;
    Float_t         pjet1[4];
    Float_t         pjet2[4];
    Float_t         pjet3[4];
    UShort_t        nbsv;
    Float_t         pxbsv[2];   //[nbsv]
    Float_t         pybsv[2];   //[nbsv]
    Float_t         pzbsv[2];   //[nbsv]
    Float_t         lbsv[2];   //[nbsv]
    Float_t         elbsv[2];   //[nbsv]
    Float_t         chbsv[2];   //[nbsv]
    UChar_t         codebsv[2];   //[nbsv]
    UShort_t        npart;
    Float_t         pmomx[57];   //[npart]
    Float_t         pmomy[57];   //[npart]
    Float_t         pmomz[57];   //[npart]
    Float_t         pmass[57];   //[npart]
    Float_t         pflight[57];   //[npart]
    UShort_t        nphot;
    Float_t         pphotx[22];   //[nphot]
    Float_t         pphoty[22];   //[nphot]
    Float_t         pphotz[22];   //[nphot]
    UChar_t         pbits[57];   //[npart]
    UChar_t         ptype[57];   //[npart]
    UChar_t         ptruth[57];   //[npart]
    UShort_t        pmoth[57];   //[npart]

    // myTree->SetBranchAddress("npart",&npart);
    // myTree->SetBranchAddress("pbits",pbits);
    // myTree->SetBranchAddress("ptype",ptype);
    // myTree->SetBranchAddress("ptruth",ptruth);
    // myTree->SetBranchAddress("pmoth",pmoth);

    myTree->SetBranchAddress("mcflavor", &mcflavor);
    myTree->SetBranchAddress("cmenergy", &cmenergy);
    myTree->SetBranchAddress("thru", thru);
    myTree->SetBranchAddress("pquark", pquark);
    myTree->SetBranchAddress("pudsh1", &pudsh1);
    myTree->SetBranchAddress("pudsh2", &pudsh2);
    myTree->SetBranchAddress("b1nn", &b1nn);
    myTree->SetBranchAddress("b2nn", &b2nn);
    myTree->SetBranchAddress("ch1nn", &ch1nn);
    myTree->SetBranchAddress("ch2nn", &ch2nn);
    myTree->SetBranchAddress("pjet1", pjet1);
    myTree->SetBranchAddress("pjet2", pjet2);
    myTree->SetBranchAddress("pjet3", pjet3);
    myTree->SetBranchAddress("nbsv", &nbsv);
    myTree->SetBranchAddress("pxbsv", pxbsv);
    myTree->SetBranchAddress("pybsv", pybsv);
    myTree->SetBranchAddress("pzbsv", pzbsv);
    myTree->SetBranchAddress("lbsv", lbsv);
    myTree->SetBranchAddress("elbsv", elbsv);
    myTree->SetBranchAddress("chbsv", chbsv);
    myTree->SetBranchAddress("codebsv", codebsv);
    myTree->SetBranchAddress("npart", &npart);
    myTree->SetBranchAddress("pmomx", pmomx);
    myTree->SetBranchAddress("pmomy", pmomy);
    myTree->SetBranchAddress("pmomz", pmomz);
    myTree->SetBranchAddress("pmass", pmass);
    myTree->SetBranchAddress("pflight", pflight);
    myTree->SetBranchAddress("nphot", &nphot);
    myTree->SetBranchAddress("pphotx", pphotx);
    myTree->SetBranchAddress("pphoty", pphoty);
    myTree->SetBranchAddress("pphotz", pphotz);
    myTree->SetBranchAddress("pbits", pbits);
    myTree->SetBranchAddress("ptype", ptype);
    myTree->SetBranchAddress("ptruth", ptruth);
    myTree->SetBranchAddress("pmoth", pmoth);

    //This is the class for Particle data, where we can get the names of particles and suc
    TDatabasePDG* pdg = TDatabasePDG::Instance();    
    //Set verbose = true and set needed range for debugging
    int verbose = false;

    std::cout << "Loop begun" << std::endl;    

    TProfile *profile = new TProfile("profile", "<pT> vs Multiplicity",57, 0, 20);
    int kcounter = 0;
    int skips = 0;

    Long64_t numberOfEntries = myTree->GetEntries();
    for (Long64_t i = 0; i < 1; i++) {
    //for (Long64_t i = 0; i < numberOfEntries; i++) {
        myTree->GetEntry(i);


        double totalMomentum = 0.0;
        int chargemulti = 0;
        int specificparticlecounter = 0;

        for (int j = 0; j < 57; j++) {
            Long64_t truepdg = ConvMC((int)ptype[j]);
            
            TParticlePDG* particle =  pdg->GetParticle(truepdg);
            
            if (!particle) {
                skips += 1;
                continue;}

            if (particle->Charge() != 0){
                chargemulti += 1;

            if (truepdg == 311){
                
                specificparticlecounter += 1;
                kcounter += 1;

 
                double px = pmomx[j];
                double py = pmomy[j];
                double pz = pmomz[j];
                double pT = sqrt(px*px +py*py);

                totalMomentum += pT;
                }

            }
        }
        if (specificparticlecounter > 0){
            double avgMomentum = (chargemulti > 0) ? fabs(totalMomentum) / specificparticlecounter : 0;
            profile->Fill(npart, avgMomentum);  // ⟨pT⟩ vs Multiplicity
        }

    }
// Draw the profile with error bars
cout << "Kaons counted in code " << kcounter << endl;
cout << "Code breaking particles skipped " << skips << endl;
TCanvas* c1 = new TCanvas("c1", " Transverse Momentum vs Multiplicity", 800, 650);
profile->SetTitle(" #pi^{+}");  // Title inside the plot
profile->SetXTitle("Multiplicity (npart)");
profile->SetYTitle(" <p_{T}> (GeV)");
profile->Draw("E");  // "E" ensures error bars are displayed
c1->Update();
//c1->Print("momentum_vs_multiplicity.png");
        //*************************************************************************************************** Stopping 


}
