#ifndef PLOTTING_UTILS_H
#define PLOTTING_UTILS_H

#include "histogramUtils.h"
#include <vector>
#include <string>

// Draws a grid of profile histograms from a vector of ParticleHistograms.
// Each histogram is labeled with the corresponding name from the names vector.
void drawProfileGrid(const std::vector<ParticleHistograms>& particleHists, const std::vector<std::string>& names);
void drawQuickHistograms(QuickHistograms quickHists);

// Saves all histograms in the vector to a ROOT file.
// Parameters:
//   particleHists: Vector of ParticleHistograms.
//   fileName: The name of the ROOT file to save the histograms in.
void saveParticleHistograms(const std::vector<ParticleHistograms>& particleHists, const std::string& fileName);
void saveGlobalHistograms(GlobalHistograms globalHists, const std::string& fileName);
void saveparticleRatioPlots(ParticleRatioPlots ratioPlots, const std::string& fileName);

#endif // PLOTTING_UTILS_H
