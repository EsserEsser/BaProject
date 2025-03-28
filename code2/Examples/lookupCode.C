#include <unordered_map>

// Build a lookup table once (e.g., at the beginning of your function)
std::unordered_map<int, int> pdgToIndex;
for (int k = 0; k < 6; k++) {
    pdgToIndex[particleCodes[k]] = k;
}

// Then, in your loop over particles:
for (int j = 0; j < t.npart; j++) {
    int truepdg = nanoConvMC(static_cast<int>(t.ptype[j]));
    auto it = pdgToIndex.find(truepdg);
    if (it != pdgToIndex.end()) {
        int idx = it->second; // Get the index for the particle type

        // Fill the histograms for the corresponding particle:
        particleHists[idx].countHist->Fill(1);
        particleHists[idx].pxHist->Fill(t.pmomx[j]);
        particleHists[idx].pyHist->Fill(t.pmomy[j]);
        particleHists[idx].pzHist->Fill(t.pmomz[j]);

        double pt = std::sqrt(t.pmomx[j] * t.pmomx[j] + t.pmomy[j] * t.pmomy[j]);
        particleHists[idx].pTHist->Fill(pt);
        
        // Optionally fill other histograms, e.g. a profile histogram:
        // particleHists[idx].pTvsMult->Fill(multiplicity, pt);
    }
}
