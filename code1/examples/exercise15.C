#include <iostream>
#include <sstream>
#include <TFile.h>
#include <TH1F.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <vector>
#include "ExampleEvent.h"
using namespace std;



void exercise15() {
  
// Here we load the library which the tree is dependent on. might have to use .dylib file rather than .so file if there are errors. 
gSystem->Load("libExampleEvent.dylib");

// These are files fore creating my own Tuple
TFile *outputFile = new TFile("exampleNtuple.root", "RECREATE");
TNtuple *ntuple = new TNtuple("eventData", "Event Data", "run:event:totalEnergy:numLeptons:boolIndicator:muonEnergy:numMuons");

//Loading root fille
TFile *myFile = new TFile("exampleEvents.root");
//Debugging code for any errors in loading the file

if (!myFile || myFile->IsZombie()) {
    cout << "Error: Could not open file exampleEvents.root!" << endl;
    return;
}

// Loading single tree inside root file
TTree *myTree = (TTree*)myFile->Get("exampleEventsTree");
//Debugging code for any errors in loading the tree
if (!myTree){
    cout << "Error in loading tree" << endl;
    myFile->Close();
    return;
}


// // Here we do some stuff that has to do with the header file ExampleEvent.h - I guess ExampleEvent is a class created in the header
// // This class allows us to obtain information from the tree or something, but I am not sure
// Don't know why we need to set a nullptr here
ExampleEvent *event = nullptr;
//Fills event pointer with data or something I don't know
myTree->SetBranchAddress("exampleEventsBranch",&event);



//Function for getting the mass of a given particle and calculating said mass -- Copied from the internet ** I don't understand the notation**
auto getMassFromPDG = [](int pdg) -> double {  // Explicitly declares return type
    if (pdg == 11 || pdg == -11) return 0.000511; // Electron
    if (pdg == 13 || pdg == -13) return 0.1057; // Muon
    // I think pdg == 22 is a photon, but i don't know about pdf == 211 nor why we return 0.0; 
    if (pdg == 22) return 0.0;
    if (pdg == 211 || pdg == -211) return 0.1396;
    return 0.0;
};


//This gives the length of the loop
Long64_t numberOfEntries = myTree->GetEntries();
for (Long64_t i = 0; i < numberOfEntries; i++) {
    // Here we get the i'th entry in the tree events
    myTree->GetEntry(i);
        // Here we get the run number and event number
        Int_t runNumber = event->GetRun();
        Int_t eventNumber = event->GetEvent();

        // *****Here we get the data for the leptons*****
        Int_t numberOfLeptons = event->GetNumberLeptons();
        Double_t totalEnergy = 0;
        Double_t totalEnergyOfMuons = 0;
        Int_t booleanIndicator = 0;
        Int_t muonNumber = 0;

        //When the number of leptons is greater than zero we can calculate the energy of each lepton in the event
        // We need to loop over the event since there might be more than one lepton 
        if (numberOfLeptons > 0){
            for (Long64_t j = 0 ; j < numberOfLeptons; j++){
                // Her we calculate the momenntum of the lepton
                Double_t LeptonPxValue = event->LeptonPx(j);
                Double_t LeptonPyValue = event->LeptonPy(j);
                Double_t LeptonPzValue = event->LeptonPz(j);

                // Here we check the type of lepton. This is how we find the mass for the total energy of the particle. 
                Int_t leptonType = event->LeptonPDG(j);
                //We then get the mass from the PDG-value insereted into our mass function
                Double_t leptonMass = getMassFromPDG(leptonType);

                //First we compute the total energy of all the particles in an event
                Double_t energy = sqrt( (LeptonPxValue * LeptonPxValue) + (LeptonPyValue * LeptonPyValue) + (LeptonPzValue * LeptonPzValue) + (leptonMass * leptonMass) );
                totalEnergy += energy;

                //Then we ccheck if the event has muons, and if they do we add to a seperate energy for the muons. 
                if (leptonType == 13 || leptonType == -13) {
                    totalEnergyOfMuons += energy;
                    muonNumber +=1;
                }
            if (muonNumber == 1){
                booleanIndicator = 1;
            }
            }
            
        }    
    ntuple->Fill(runNumber, eventNumber, totalEnergy, numberOfLeptons, booleanIndicator, totalEnergyOfMuons, muonNumber);
    }
outputFile->Write();
outputFile->Close();
}







// //the run number;
// runNumber
// //the event number;
// eventNumber
// //the total energy of all the particles in the event;
// totalEnergy
// //the total number of particles in the event.
// numberOfLeptons
// //a boolean indicator: does the event have only one muon?
// booleanIndicator
// //the total energy of all the muons in the event;
// totalEnergyOfMuons
// //the number of muons in the event;  
// muonNumber 

// // // Code for manually loading a branch in a tree
// //Loading the branch in the tree
// TBranch *myBranch = myTree->GetBranch("exampleEventsBranch");
// //Debuggin code for the branch
// if (!myBranch){
//     cout <<"Error in loading branch" << endl;
//     return;
// }
// myBranch->Print();
