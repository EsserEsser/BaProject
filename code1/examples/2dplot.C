#include <iostream>
#include <sstream>
#include <TFile.h>
#include <TH1F.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <vector>
using namespace std;

void mytreereader() {

    TFile *myFile = new TFile("folders.root");
    if (!myFile || myFile->IsZombie()) {
        cout << "Error: Could not open 'folders.root'!" << endl;
        return;
    }


    TDirectory *dir = (TDirectory*)myFile->Get("example2");
    if (!dir) {
        cout << "Error: Directory 'example2' not found in 'folders.root'!" << endl;
        return;
    }

    TTree *tree = (TTree*)dir->Get("histogramList");
    if (!tree) {
        cout << "Error: Tree 'histogramList' not found in 'example2'!" << endl;
        return;
    }

    TTreeReader myReader(tree);
    TTreeReaderValue<Int_t> myhistNumber(myReader, "histNumber");
    TTreeReaderValue<Double_t> myx(myReader, "x");
    
    vector<Int_t> histvec;
    vector<Double_t> xvec;
    vector<Double_t> exvec;

    vector<Double_t> mean,emean;

    
    while (myReader.Next()) {


        ////// VERY unorganized code

        // Just access the data as if myPx and myPy were iterators (note the '*'
        // in front of them):
        //arr[i] = 
        Int_t hist_value =*myhistNumber;
        Double_t x_value =*myx;

        histvec.push_back(hist_value);
        xvec.push_back(x_value);

        Int_t exvalue = 0;
        exvec.push_back(exvalue);

        // Getting the filenames for histograms by converting strings
        std::ostringstream os;
        os << "hist" << hist_value;
        TString histogramName = os.str();


        TH1D* histPtr= (TH1D*) dir->Get(histogramName);
        //Calculating mean value for Y-axis
        histPtr->Fit("gaus","Q0"); // 0 stops plots from being drawn. Q stops all parameters from being shown. 
        TF1* fitfunc = histPtr->GetFunction("gaus");
        Double_t meanvalue = fitfunc->GetParameter(1);
        Double_t emeanvalue = fitfunc->GetParameter(2);
        mean.push_back(meanvalue);
        emean.push_back(emeanvalue);



    }

    TCanvas* c1 = new TCanvas("c1","Graph",800,650);
    //c1->SetLogx();
    c1->SetGrid();
    auto myHist = new TGraphErrors(xvec.size(),xvec.data(),mean.data(),exvec.data(),emean.data());
    myHist->SetTitle("Seligman Exercise 13 plot ;x; Histogam mean value ");
    myHist->Draw("AP");
    myHist->SetMarkerColor(4);
    myHist->SetMarkerStyle(21);
    myHist->GetXaxis()->CenterTitle(true);
    myHist->GetYaxis()->CenterTitle(true);
    c1->Update();

    }