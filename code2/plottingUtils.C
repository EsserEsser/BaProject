#include "plottingUtils.h"
#include <TCanvas.h>
#include <TFile.h>

void drawProfileGrid(const std::vector<ParticleHistograms>& particleHists, const std::vector<std::string>& names) {
    // Determine grid dimensions (for example, 2 columns).
    int n = particleHists.size();
    int cols = 2;
    int rows = (n + 1) / 2;
    
    TCanvas* c = new TCanvas("c", "Particle Profiles", 1200, 800);
    c->Divide(cols, rows);
    
    // Draw each profile histogram.
    for (size_t i = 0; i < particleHists.size(); ++i) {
        c->cd(i + 1);
        particleHists[i].pTvsChargeMulti->SetTitle((names[i] + " <pT> vs Multiplicity").c_str());
        particleHists[i].pTvsChargeMulti->GetXaxis()->SetTitle("Charge Multiplicity");
        particleHists[i].pTvsChargeMulti->GetYaxis()->SetTitle("<p_{T}> (GeV)");
        particleHists[i].pTvsChargeMulti->Draw();
    }
    c->Update();

}

//This function can be edited for plotting quick histograms
void drawQuickHistograms(QuickHistograms quickHists){
    TCanvas* c2 = new TCanvas("c2", "Quick plots", 1200, 800);
    quickHists.quick1Hist->Draw();
    quickHists.quick2Hist->Draw();
    quickHists.quick3Hist->Draw();
    quickHists.quick4Hist->Draw();
    quickHists.quick5Hist->Draw();
    quickHists.quick6Hist->Draw();
}


void saveParticleHistograms(const std::vector<ParticleHistograms>& particleHists, const std::string& fileName) {
    TFile* file = new TFile(fileName.c_str(), "RECREATE");
    //Loops over all entries in the vector
    for (const auto& h : particleHists) {
        h.countHist->Write();
        h.pxHist->Write();
        h.pyHist->Write();
        h.pzHist->Write();
        h.pTHist->Write();
        h.pTThrustHist->Write();
        h.pTvsChargeMulti->Write();
        h.pTvsChargeMultiThrust->Write();
    }
    file->Close();
}

void saveGlobalHistograms(GlobalHistograms globalHists, const std::string& fileName) {
    TFile* file = new TFile(fileName.c_str(), "RECREATE");
        //Angles
        globalHists.thetaHist->Write();
        globalHists.phiHist->Write();
        globalHists.thetaChargeHist->Write();
        globalHists.phiChargeHist->Write();
        globalHists.thetaPhotonsHist->Write();
        globalHists.phiPhotonsHist->Write();

        //Multiplicity
        globalHists.multiHist->Write();
        globalHists.multiChargeHist->Write();

        // Momentum
        globalHists.pxHist->Write();
        globalHists.pyHist->Write();
        globalHists.pzHist->Write();
        globalHists.pTHist->Write();
        globalHists.pTThrustHist->Write();
        globalHists.pTvsChargeMulti->Write();
        globalHists.pTvsChargeMultiThrust->Write();
    file->Close();
}


void saveParticleRatioPlots(ParticleRatioPlots ratioPlots, const std::string& fileName) {
    TFile* file = new TFile(fileName.c_str(), "RECREATE");    
        ratioPlots.rapidity->Write();
        ratioPlots.kaonpionRatio->Write();           
        ratioPlots.phipionRatio->Write();        
        ratioPlots.protonpionRatio->Write();         
        ratioPlots.lambdapionRatio->Write();           
        ratioPlots.sigmapionRatio->Write();          
        ratioPlots.xipionRatio ->Write();          

        TCanvas* c1 = new TCanvas("c1", "RatioPlots", 1200, 800);
        c1->Divide(2, 3);
        c1->cd(1);
        ratioPlots.kaonpionRatio->GetYaxis()->SetTitle("Particle Yield Ratio");
        ratioPlots.kaonpionRatio->Draw("HIST E");
        c1->cd(2);    
        ratioPlots.phipionRatio ->Draw("HIST E");
        c1->cd(3);        
        ratioPlots.protonpionRatio->GetYaxis()->SetTitle("Particle Yield Ratio");
        ratioPlots.protonpionRatio->Draw("HIST E");
        c1->cd(4);
        ratioPlots.lambdapionRatio->Draw("HIST E");
        c1->cd(5);
        ratioPlots.sigmapionRatio->GetYaxis()->SetTitle("Particle Yield Ratio");
        ratioPlots.sigmapionRatio->GetXaxis()->SetTitle("Charged Multiplicity");
        ratioPlots.sigmapionRatio->Draw("HIST E");
        c1->cd(6);
        ratioPlots.xipionRatio->GetXaxis()->SetTitle("Charged Multiplicity");
        ratioPlots.xipionRatio->Draw("HIST E");  
        c1->Update();
        c1->Write();
        c1->SaveAs("/pngFiles/ratioPlots.png");
        c1->Close();

    file->Close();
}