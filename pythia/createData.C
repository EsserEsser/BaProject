#include <iostream>
#include <cmath>
#include "TFile.h"
#include "TTree.h"
#include "Pythia8/Pythia.h"
#include <vector>

int main()
{
    TFile *output = new TFile("pythiaData.root", "recreate");

    TTree *tree = new TTree("tree","tree");

    // Declare variables with the correct types.
    UChar_t  mcflavor;
    Float_t  cmenergy;
    Float_t  thru[3];
    Float_t  pquark[3];
    Float_t  pudsh1;
    Float_t  pudsh2;
    Float_t  b1nn;
    Float_t  b2nn;
    Float_t  ch1nn;
    Float_t  ch2nn;
    Float_t  pjet1[4];
    Float_t  pjet2[4];
    Float_t  pjet3[4];

    UShort_t nbsv;
    Float_t  pxbsv[2];   // size = nbsv
    Float_t  pybsv[2];   // size = nbsv
    Float_t  pzbsv[2];   // size = nbsv
    Float_t  lbsv[2];    // size = nbsv
    Float_t  elbsv[2];   // size = nbsv
    Float_t  chbsv[2];   // size = nbsv
    UChar_t  codebsv[2]; // size = nbsv

    UShort_t npart;
    Float_t  pmomx[500];  // size = npart
    Float_t  pmomy[500];  // size = npart
    Float_t  pmomz[500];  // size = npart
    Float_t  pmass[500];  // size = npart
    Float_t  pflight[500];// size = npart

    UShort_t nphot;
    Float_t  pphotx[500]; // size = nphot
    Float_t  pphoty[500]; // size = nphot
    Float_t  pphotz[500]; // size = nphot
    UChar_t  pbits[500];  // size = npart
    Int_t    ptype[500];   // size = npart  
    UChar_t  ptruth[500]; // size = npart
    UShort_t pmoth[500];  // size = npart

    // Create branches with leaf lists.
    // For scalar variables, include the type indicator:
    tree->Branch("mcflavor", &mcflavor, "mcflavor/b");
    tree->Branch("cmenergy", &cmenergy, "cmenergy/F");
    // For fixed-size arrays, provide the dimension:
    tree->Branch("thru", thru, "thru[3]/F");
    tree->Branch("pquark", pquark, "pquark[3]/F");
    tree->Branch("pudsh1", &pudsh1, "pudsh1/F");
    tree->Branch("pudsh2", &pudsh2, "pudsh2/F");
    tree->Branch("b1nn", &b1nn, "b1nn/F");
    tree->Branch("b2nn", &b2nn, "b2nn/F");
    tree->Branch("ch1nn", &ch1nn, "ch1nn/F");
    tree->Branch("ch2nn", &ch2nn, "ch2nn/F");
    tree->Branch("pjet1", pjet1, "pjet1[4]/F");
    tree->Branch("pjet2", pjet2, "pjet2[4]/F");
    tree->Branch("pjet3", pjet3, "pjet3[4]/F");

    // For arrays whose length is determined by another variable,
    // first create the branch for the size variable:
    tree->Branch("nbsv", &nbsv, "nbsv/s");
    tree->Branch("pxbsv", pxbsv, "pxbsv[nbsv]/F");
    tree->Branch("pybsv", pybsv, "pybsv[nbsv]/F");
    tree->Branch("pzbsv", pzbsv, "pzbsv[nbsv]/F");
    tree->Branch("lbsv", lbsv, "lbsv[nbsv]/F");
    tree->Branch("elbsv", elbsv, "elbsv[nbsv]/F");
    tree->Branch("chbsv", chbsv, "chbsv[nbsv]/F");
    tree->Branch("codebsv", codebsv, "codebsv[nbsv]/b");

    tree->Branch("npart", &npart, "npart/s");
    tree->Branch("pmomx", pmomx, "pmomx[npart]/F");
    tree->Branch("pmomy", pmomy, "pmomy[npart]/F");
    tree->Branch("pmomz", pmomz, "pmomz[npart]/F");
    tree->Branch("pmass", pmass, "pmass[npart]/F");
    tree->Branch("pflight", pflight, "pflight[npart]/F");

    tree->Branch("nphot", &nphot, "nphot/s");
    tree->Branch("pphotx", pphotx, "pphotx[nphot]/F");
    tree->Branch("pphoty", pphoty, "pphoty[nphot]/F");
    tree->Branch("pphotz", pphotz, "pphotz[nphot]/F");

    tree->Branch("pbits", pbits, "pbits[npart]/b");
    // For the particle type, we use a renamed variable ptype_arr to avoid conflict with the branch name.
    tree->Branch("ptype", ptype, "ptype[npart]/I");
    tree->Branch("ptruth", ptruth, "ptruth[npart]/b");
    tree->Branch("pmoth", pmoth, "pmoth[npart]/s");



    Pythia8::Pythia pythia;

    // Number of events.
    int nevents = 1e5;
    // Allow no substructure in e+- beams: normal for corrected LEP data.
    pythia.readString("PDF:lepton = off");
    // Process selection.
    pythia.readString("WeakSingleBoson:ffbar2gmZ = on");
    // Switch off all Z0 decays and then switch back on those to quarks.
    pythia.readString("23:onMode = off");
    pythia.readString("23:onIfAny = 1 2 3 4 5");

    // LEP1 initialization at Z0 mass.
    pythia.readString("Beams:idA =  11");
    pythia.readString("Beams:idB = -11");
    double mZ = pythia.particleData.m0(23);
    pythia.settings.parm("Beams:eCM", mZ);

    

    bool decay = true;
    if (decay == true){
        pythia.readString("3122:mayDecay = off"); 
        pythia.readString("3312:mayDecay = off"); 
        pythia.readString("-3122:mayDecay = off");
        pythia.readString("-3312:mayDecay = off"); 
        pythia.init();
    }
    
    // Create thr object from the Thrust class t
    Pythia8::Thrust thrAnalyzer;
    Pythia8::Sphericity sph;
    Float_t thr;     // thrust value
    Float_t cthr;    // cos(theta) of thrust axis   
    Float_t phthr;   // phi of thrust axis

    for(int i = 0; i < nevents; i++){   
        if(!pythia.next()) continue;

        int entries = pythia.event.size();
        if (i%10000 == 0){
            //std::cout << "Event" << i << std::endl;
        }
    
        npart = 0;
        for(int j = 0; j < entries; j++){
            if (pythia.event[j].isFinal() && npart < 500){
                ptype[npart] = pythia.event[j].id();
                cmenergy = mZ;
                pmomx[npart] = pythia.event[j].px();
                pmomy[npart] = pythia.event[j].py();
                pmomz[npart] = pythia.event[j].pz();
                pmass[npart] = pythia.event[j].m();
                npart++;
           }
        }
        // if (thr.analyze(pythia.event)){
            
        //     Pythia8::Vec4 thrustVec = thr.eventAxis(1);
        //     double tx = thrustVec.px();
        //     double ty = thrustVec.py();
        //     double tz = thrustVec.pz();
        //     double tMag = thrustVec.pAbs();  // should be ~1.0
        //     double cosTheta = tz / tMag;                // or just tz if tMag ≈ 1
        //     double phi = atan2(ty, tx);                 // returns phi in [-π, π]
        //     // thru[0] = thrustVec.px();
        //     // thru[1] = thrustVec.py();
        //     // thru[2] = thrustVec.pz();
        //     thru[0] = cosTheta;
        //     thru[1] = phi;
        //     thru[2] = thr.thrust();
        // }
        
        if (thrAnalyzer.analyze(pythia.event)) {
            Pythia8::Vec4 thrustVec = thrAnalyzer.eventAxis(1);  // axis with max alignment
            double tx = thrustVec.px();
            double ty = thrustVec.py();
            double tz = thrustVec.pz();
            double tMag = thrustVec.pAbs(); // should be ~1
        
            thr   = thrAnalyzer.thrust();     // thrust value
            cthr  = tz / tMag;                // cos(theta) of thrust axis
            phthr = atan2(ty, tx);            // phi in radians

            if (phthr < 0) phthr += 2 * M_PI; // optional: keep in [0, 2π]
        } else {
            thr = cthr = phthr = -1; // or some flag value in case of failure
        }
        thru[0] = abs(cthr);
        thru[1] = phthr;
        thru[2] = thr;
        tree->Fill(); //Where should this be??????
    }
    output->Write();
    output->Close();

    return 0;
} 