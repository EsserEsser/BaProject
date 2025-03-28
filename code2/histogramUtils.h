#ifndef HISTOGRAM_UTILS_H
#define HISTOGRAM_UTILS_H

#include <TH1D.h>
#include <TProfile.h>
#include <string>

// A structure to hold several histograms for a given particle type.
struct ParticleHistograms {
    TH1D* countHist;
    TH1D* pxHist;
    TH1D* pyHist;
    TH1D* pzHist;
    TH1D* pTHist;
    TH1D* pTThrustHist;
    TProfile* pTvsChargeMulti;
    TProfile* pTvsChargeMultiThrust;
};

// Creates a set of histograms for a particle.
// Parameters:
//   name: A string used to label the histograms (e.g., "Pion").
//   chargeMultBins: Number of bins for the profile histograms.
// Returns a ParticleHistograms struct with initialized histograms.
ParticleHistograms createHistogramsForParticle(const std::string& name, int chargeMultBins);

struct GlobalHistograms {
    TH1D *thetaHist;
    TH1D *phiHist;
    TH1D *thetaChargeHist;
    TH1D *phiChargeHist;
    TH1D *thetaPhotonsHist;
    TH1D *phiPhotonsHist;
    TH1D* multiHist;
    TH1D* multiChargeHist;
    TH1D* thrust;
    TH1D* thrustSin;
    TH1D* thrustPhi;
    TH1D* pxHist;
    TH1D* pyHist;
    TH1D* pzHist;
    TH1D* pTHist;
    TH1D* pTThrustHist;
    TProfile* pTvsChargeMulti;
    TProfile* pTvsChargeMultiThrust;
    
};
GlobalHistograms createHistogramsGlobal(const std::string& name);

struct QuickHistograms {
    TH1D* quick1Hist;
    TH1D* quick2Hist;
    TH1D* quick3Hist;
    TH1D* quick4Hist;
    TH1D* quick5Hist;
    TH1D* quick6Hist;

};
QuickHistograms createQuickHistograms(const std::string& name);


struct ParticleRatioPlots {
    TH1D* rapidity;
    TProfile* kaonpionRatio;
    TProfile* phipionRatio;
    TProfile* protonpionRatio;
    TProfile* lambdapionRatio;
    TProfile* sigmapionRatio;
    TProfile* xipionRatio;
};
ParticleRatioPlots createParticleRatioPlots(const std::string& name);











#endif // HISTOGRAM_UTILS_H