#define Analyze_cxx
// The class definition in Analyze.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("Analyze.C")
// root> T->Process("Analyze.C","some options")
// root> T->Process("Analyze.C+")
//


#include "Analyze.h"
#include <TH2.h>
#include <TStyle.h>

//******** Definition section *********
  TH1* ebeamHist = nullptr;
  TH1* chi2Hist = nullptr;
  TH2* scatHist= nullptr;
  TH2* chi2thetaHist = nullptr;
void Analyze::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   //******** Initialization section *********
  chi2Hist = new TH1D("chi2","Histogram of Chi2",100,0,2);
  ebeamHist = new TH1D("ebeam","Histogram of ebeam",100,149,151);
  scatHist = new TH2D("scatHist","Scatterplot of chi2 and ebeam",100,0,20,100,149,151);
  chi2thetaHist = new TH2D("chi2thetaHist","Scatterplot of Chi2 and Theta",100,0,20,0,360,151);

  chi2Hist->GetXaxis()->SetTitle("chi2");
  chi2Hist->GetYaxis()->SetTitle("number of events");

  ebeamHist->GetXaxis()->SetTitle("ebeam");
  ebeamHist->GetYaxis()->SetTitle("number of events");
  
  scatHist->GetXaxis()->SetTitle("chi2");
  scatHist->GetYaxis()->SetTitle("ebeam");

  chi2thetaHist->GetXaxis()->SetTitle("chi2");
  chi2thetaHist->GetYaxis()->SetTitle("ebeam");
}   

void Analyze::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

bool Analyze::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetLocalEntry(entry);
   //******** Loop section *********
    Double_t pt = TMath::Sqrt((*px)*(*px) + (*py)*(*py));       
    Double_t theta = TMath::ATan2(pt,*pz);

    chi2Hist->Fill(*chi2);
    ebeamHist->Fill(*ebeam);
    scatHist->Fill(*chi2,*ebeam);
    chi2thetaHist->Fill(*chi2,theta);

   return true;
}

void Analyze::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Analyze::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   //******** Wrap-up section *********
  TCanvas* c1 = new TCanvas("c1","Chi2 and Ebeam Histograms",800,600);
  c1->Divide(2,2);
  
  c1->cd(1);
  chi2Hist->Draw("e");
  
  c1->cd(2);
  ebeamHist->Draw("e");
  
  c1->cd(3);
  scatHist->Draw();
  
  c1->cd(4);
  chi2thetaHist->Draw();
  
  c1->Update();
}
