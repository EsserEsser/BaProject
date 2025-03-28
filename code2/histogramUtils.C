#include "histogramUtils.h"
#include <sstream>

// Here goes the particle name and the number of bins
// ParticleHistograms is a user defined type
ParticleHistograms createHistogramsForParticle(const std::string& name, int chargeMultiBins) {
    ParticleHistograms hists;
    
    // Create a unique name for each histogram by appending a label.
    hists.countHist = new TH1D((name + "Count").c_str(), ("Number of " + name).c_str(), 20, 0, 20);
    hists.pxHist = new TH1D((name + "Px").c_str(), (name + " px momentum").c_str(), 100, -45, 45);
    hists.pyHist = new TH1D((name + "Py").c_str(), (name + " py momentum").c_str(), 100, -45, 45);
    hists.pzHist = new TH1D((name + "Pz").c_str(), (name + " pz momentum").c_str(), 100, -45, 45);
    hists.pTHist = new TH1D((name + "PT").c_str(), (name + " transverse momentum").c_str(), 100, -45, 45);
    hists.pTThrustHist = new TH1D((name + "PTThrust").c_str(), (name + " thrust transverse momentum").c_str(), 100, -45, 45);

    hists.pTvsChargeMulti = new TProfile((name + "PTvsChargeMulti").c_str(),
                                  (name + " <pT> vs Charged Multiplicity").c_str(),
                                  chargeMultiBins, 0, chargeMultiBins);
    
    hists.pTvsChargeMultiThrust = new TProfile((name + "PTvsChargeMultiThrust").c_str(),
                                        (name + " <pT> (thrust) vs Charged Multiplicity").c_str(),
                                        chargeMultiBins, 0, chargeMultiBins);
    
    return hists;
}

// GeneralHistograms createHistogramsGeneral(const std::string& name)
GlobalHistograms createHistogramsGlobal(const std::string& name){
    GlobalHistograms hists;
    hists.thetaHist = new TH1D((name + "thetaHist").c_str(), ("Particles #theta angle distribution"),100, 0,3.15);
    hists.phiHist = new TH1D((name + "phiHist").c_str(), ("Particles #phi angle distribution "),1000, -6.29,6.29);
    hists.thetaChargeHist = new TH1D((name + "thetaChargeHist").c_str(), ("Charged particles #theta angle distribution"),100, 0,3.15);
    hists.phiChargeHist = new TH1D((name + "phiChargeHist").c_str(), ("Charged particles #phi angle distribution"),1000, -6.29,6.29);
    hists.thetaPhotonsHist = new TH1D((name + "thetaPhotonsHist").c_str(), ("Photons #theta angle distribution "),100, 0,3.15);
    hists.phiPhotonsHist = new TH1D((name + "phiPhotonsHist").c_str(),("Photons #phi angle distribution"),1000, -6.29,6.29);
    hists.multiHist =  new TH1D((name + "Multiplicity").c_str(), (name + " multiplicity" ).c_str(), 57, 0, 57);
    hists.multiChargeHist =  new TH1D((name + "ChargeMultiplicity").c_str(), (name + " charge multiplicity" ).c_str(), 57, 0, 57);
    // hists.thrust =  new TH1D((name + "Thrust").c_str(), (name + "Thrust" ).c_str(), 100, 0, 1);
    // hists.thrustSin =  new TH1D((name + "ThrustSin").c_str(), ("Number of " + name).c_str(), 100, -1, 1);
    // hists.thrustPhi =  new TH1D((name + "ThrustPhi").c_str(), ("Number of " + name).c_str(), 100, -6, 6);
    hists.pxHist = new TH1D((name + "Px").c_str(), (name + " px momentum").c_str(), 100, -45, 45);
    hists.pyHist = new TH1D((name + "Py").c_str(), (name + " py momentum").c_str(), 100, -45, 45);
    hists.pzHist = new TH1D((name + "Pz").c_str(), (name + " pz momentum").c_str(), 100, -45, 45);
    hists.pTHist = new TH1D((name + "PT").c_str(), (name + " transverse momentum").c_str(), 100, -45, 45);
    hists.pTThrustHist = new TH1D((name + "PTThrust").c_str(), (name + " thrust transverse momentum").c_str(), 100, -45, 45);
    hists.pTvsChargeMulti = new TProfile((name + "PTvsChargeMulti").c_str(),
                                  (name + " <pT> vs Charged Multiplicity").c_str(),
                                  57, 0, 57);
    
    hists.pTvsChargeMultiThrust = new TProfile((name + "PTvsChargeMultiThrust").c_str(),
                                        (name + " <pT> (thrust) vs Charged Multiplicity").c_str(),
                                        57, 0, 57);
    return hists;
}


// GeneralHistograms createHistogramsGeneral(const std::string& name)
QuickHistograms createHistogramsQuick(const std::string& name){
    QuickHistograms hists;
    hists.quick1Hist = new TH1D("quick1Hist","quick1Hist",100,-150,150);
    hists.quick2Hist = new TH1D("quick2Hist","quick2Hist",100,-150,150);
    hists.quick3Hist = new TH1D("quick3Hist","quick3Hist",100,-150,150);
    hists.quick4Hist = new TH1D("quick4Hist","quick4Hist",100,-150,150);
    hists.quick5Hist = new TH1D("quick5Hist","quick5Hist",100,-150,150);
    hists.quick6Hist = new TH1D("quick5Hist","quick5Hist",100,-150,150);
    return hists;
}

ParticleRatioPlots createParticleRatioPlots(){
    ParticleRatioPlots hists;
    hists.rapidity = new TH1D("rapidity","Distribution of rapidity",1000,0,5);
    hists.kaonpionRatio = new TProfile(("kaonpionRatio"),"k^{+}/#pi^{+}",36,8,45) ;
    hists.phipionRatio = new TProfile(("phipionRatio"),"#phi^{+}/#pi^{+}",36,8,44) ;
    hists.protonpionRatio = new TProfile(("protonpionRatio"),"p^{+}/#pi^{+}",36,8,44) ;
    hists.lambdapionRatio = new TProfile(("lambdapionRatio"),"#Lambda^{+}/#pi^{+}",36,8,44) ;
    hists.sigmapionRatio = new TProfile(("sigmapionRatio"),"#Sigma^{+}/#pi^{+}",36,8,44) ;
    hists.xipionRatio = new TProfile(("xipionRatio"),"#xi^{+}/#pi^{+}",36,8,44) ;
    return hists;
}