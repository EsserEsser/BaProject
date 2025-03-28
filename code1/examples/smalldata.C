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


void smalldata(){

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
    Long64_t numberOfEntries = myTree->GetEntries();

    // //*************************************************************************************************** Looping over entries start
    // for (Long64_t i = 0; i < numberOfEntries; i++) {
    // //for (Long64_t i = 0; i < 100; i++) {
    //     myTree->GetEntry(i);  
        
    //     // For loop for all possible particles in an event. There are 57 possible particles in each event
    //     // for (Int_t j = 3; j < 4; j++) {

    //     //     //These files are from ALEPH data and don't store PDG-numbers like the ones used in the TDatabasePDG Class
    //     //     //Thus a function ConvMC is made in the header file Extract.h for converting the values in the branch "ptype" to PDG-values
    //     //     int truepdg = ConvMC((int)ptype[j]);
            
    //     //     //Here we get the particle from the truepdg number
    //     //     TParticlePDG* particle =  pdg->GetParticle(truepdg);
    //     //     particle->Print("d");

            
    //     //     // Prints Particle names in the list if verbose == True
    //     //     if (verbose == true && particle && truepdg != 0){
    //     //         cout << truepdg << " is particle " << particle->GetName() << " With Charge " << particle->Charge()/3 << endl; // Charge/3 because it comes in units of 1/3e, this a proton has 3 charge here 
    //     //     }   else if (verbose == true) {
    //     //         cout << "npart list index " << j  << " with truepdg = " << truepdg <<" Returns Null "<< endl;
    //     //   }
    //     // }

    //     myHist->Fill(npart);
    // }
    
    // std::cout << "Loop done" << std::endl;
    // //*************************************************************************************************** Looping over entries end
    // TCanvas* c1 = new TCanvas("c1","Graph",800,650);
    // //c1->SetLogx();
    // c1->SetGrid();
    // myHist->Draw();
    // c1->Update();

    // myFile->Close();
    // delete myFile;

    //*************************************************************************************************** Calculating momentum and charge multiplicity

    TProfile *profile = new TProfile("profile", "<pT> vs Multiplicity", 100, 0, 57);

    for (Long64_t i = 0; i < 1; i++) {
    //for (Long64_t i = 0; i < numberOfEntries; i++) {
        myTree->GetEntry(i);

        double totalMomentum = 0.0;
        int chargemulti = 0;
        for (int j = 0; j < 57; j++) {
            int truepdg = ConvMC((int)ptype[j]);
            TParticlePDG* particle =  pdg->GetParticle(truepdg);
            if (particle->Charge() != 0){
            chargemulti += 1;

            double pT = sqrt(pmomx[j] * pmomx[j] + pmomy[j] * pmomy[j]);  // Transverse momentum

            totalMomentum += pT;

            }
        }      
        double avgMomentum = (chargemulti > 0) ? totalMomentum / chargemulti : 0;
        profile->Fill(npart, avgMomentum);  // ⟨pT⟩ vs Multiplicity
    }
// Draw the profile with error bars
TCanvas* c2 = new TCanvas("cc2", "Momentum vs Multiplicity", 800, 650);
profile->SetXTitle("Multiplicity (npart)");
profile->SetYTitle("<p_{T}> (GeV)");
profile->Draw("E");  // "E" ensures error bars are displayed
c2->Update();
c2->Print("momentum_vs_multiplicity.png");
        //*************************************************************************************************** Stopping 




}

// void smalldata(){
//     TFile *myFile = new TFile("/USERS/magnussellebjerg/BA/data/zqqda91.root");
//     TTree *myTree = (TTree*)myFile->Get("tree");

//     //// Print to check Ntuples
//     //myTree->Print();

    
//     UChar_t         mcflavor;
//     Float_t         cmenergy;
//     Float_t         thru[3];
//     Float_t         pquark[3];
//     Float_t         pudsh1;
//     Float_t         pudsh2;
//     Float_t         b1nn;
//     Float_t         b2nn;
//     Float_t         ch1nn;
//     Float_t         ch2nn;
//     Float_t         pjet1[4];
//     Float_t         pjet2[4];
//     Float_t         pjet3[4];
//     UShort_t        nbsv;
//     Float_t         pxbsv[2];   //[nbsv]
//     Float_t         pybsv[2];   //[nbsv]
//     Float_t         pzbsv[2];   //[nbsv]
//     Float_t         lbsv[2];   //[nbsv]
//     Float_t         elbsv[2];   //[nbsv]
//     Float_t         chbsv[2];   //[nbsv]
//     UChar_t         codebsv[2];   //[nbsv]
//     UShort_t        npart;
//     Float_t         pmomx[57];   //[npart]
//     Float_t         pmomy[57];   //[npart]
//     Float_t         pmomz[57];   //[npart]
//     Float_t         pmass[57];   //[npart]
//     Float_t         pflight[57];   //[npart]
//     UShort_t        nphot;
//     Float_t         pphotx[22];   //[nphot]
//     Float_t         pphoty[22];   //[nphot]
//     Float_t         pphotz[22];   //[nphot]
//     UChar_t         pbits[57];   //[npart]
//     UChar_t         ptype[57];   //[npart]
//     UChar_t         ptruth[57];   //[npart]
//     UShort_t        pmoth[57];   //[npart]

//     // myTree->SetBranchAddress("npart",&npart);
//     // myTree->SetBranchAddress("pbits",pbits);
//     // myTree->SetBranchAddress("ptype",ptype);
//     // myTree->SetBranchAddress("ptruth",ptruth);
//     // myTree->SetBranchAddress("pmoth",pmoth);

//     myTree->SetBranchAddress("mcflavor", &mcflavor);
//     myTree->SetBranchAddress("cmenergy", &cmenergy);
//     myTree->SetBranchAddress("thru", thru);
//     myTree->SetBranchAddress("pquark", pquark);
//     myTree->SetBranchAddress("pudsh1", &pudsh1);
//     myTree->SetBranchAddress("pudsh2", &pudsh2);
//     myTree->SetBranchAddress("b1nn", &b1nn);
//     myTree->SetBranchAddress("b2nn", &b2nn);
//     myTree->SetBranchAddress("ch1nn", &ch1nn);
//     myTree->SetBranchAddress("ch2nn", &ch2nn);
//     myTree->SetBranchAddress("pjet1", pjet1);
//     myTree->SetBranchAddress("pjet2", pjet2);
//     myTree->SetBranchAddress("pjet3", pjet3);
//     myTree->SetBranchAddress("nbsv", &nbsv);
//     myTree->SetBranchAddress("pxbsv", pxbsv);
//     myTree->SetBranchAddress("pybsv", pybsv);
//     myTree->SetBranchAddress("pzbsv", pzbsv);
//     myTree->SetBranchAddress("lbsv", lbsv);
//     myTree->SetBranchAddress("elbsv", elbsv);
//     myTree->SetBranchAddress("chbsv", chbsv);
//     myTree->SetBranchAddress("codebsv", codebsv);
//     myTree->SetBranchAddress("npart", &npart);
//     myTree->SetBranchAddress("pmomx", pmomx);
//     myTree->SetBranchAddress("pmomy", pmomy);
//     myTree->SetBranchAddress("pmomz", pmomz);
//     myTree->SetBranchAddress("pmass", pmass);
//     myTree->SetBranchAddress("pflight", pflight);
//     myTree->SetBranchAddress("nphot", &nphot);
//     myTree->SetBranchAddress("pphotx", pphotx);
//     myTree->SetBranchAddress("pphoty", pphoty);
//     myTree->SetBranchAddress("pphotz", pphotz);
//     myTree->SetBranchAddress("pbits", pbits);
//     myTree->SetBranchAddress("ptype", ptype);
//     myTree->SetBranchAddress("ptruth", ptruth);
//     myTree->SetBranchAddress("pmoth", pmoth);

//     //This is the class for Particle data, where we can get the names of particles and suc
//     TDatabasePDG* pdg = TDatabasePDG::Instance();    
    
//     std::cout << "Before reading entries" << std::endl;    
//     Long64_t numberOfEntries = myTree->GetEntries();
//     // for (Long64_t i = 0; i < numberOfEntries; i++) {
//     for (Long64_t i = 0; i < 1; i++) {
//         myTree->GetEntry(i);  
//         cout << nbsv << endl;
        
//         //Prints Pmoth of current entry
//         for (Int_t j = 0; j < 57; j++) {
//             TParticlePDG* particle =  pdg->GetParticle((int)ptype[j]);

//             //This converts the alpeh pdg-number to the standard pdg numbers used in TDatabasePDG
//             int truepdg = ConvMC((int)ptype[j]);

//             if (particle && (int)ptype[j]>0){
//                 cout << truepdg << " is particle: "<< particle->GetName() << endl;
//                 //cout << (int)ptype[j] << " is particle: "<< endl;    
//             }   else{
//                 cout << "npart list index " << j  << " with pdg,convertedpdg = " << (int)ptype[j] <<"," << truepdg << " Returns Null "<< endl;

//             }
            
//         }
//     }
//     std::cout << "After reading entries" << std::endl;

// myFile->Close();
// delete myFile;

//}




    // //Can be used to get information about the tree
    // myTree->MakeClass("smalldataTree");
