#ifndef PHYSICS_UTILS_H
#define PHYSICS_UTILS_H

#include <cmath>
// using namespace std;

Float_t computeRapidity(Float_t Energy,Float_t pz);

// Float_t_t pseudorapidity(Float_t_t theta);


// Computes the momentum component perpendicular to a given thrust axis.
// Parameters:
//   px, py, pz: The momentum components of the particle.
//   thrux, thruy, thruz: The components of the thrust axis.
// Returns the perpendicular momentum.
double pPerpendicularThrust(Float_t px, Float_t py, Float_t pz, Float_t thrux, Float_t thruy, Float_t thruz);

// Computes the magnitude of a momentum vector.
// Parameters: px, py, pz: The momentum components.
// Returns the magnitude of the momentum vector.
double computeMomentum(Float_t px, Float_t py, Float_t pz);


double azimuthalAngle(Float_t px, Float_t py);
double polarAngle(Float_t px,Float_t py,Float_t pz);
#endif // PHYSICS_UTILS_H