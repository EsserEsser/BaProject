#include "physicsUtils.h"


// // This functions computes the rapidity, but it requires an energy input
Float_t computeRapidity(Float_t Energy,Float_t pz){
    return 0.5*log( (Energy+pz)/(Energy-pz) );
}

// //This function only needs an angle
// Float_t_t pseudorapidity(Float_t_t theta){
//     return -log( tan(theta/2) );
// }

#include "physicsUtils.h"

// Definition for pPerpendicularThrust.
// Calculates the transverse momentum component relative to the thrust axis.
double pPerpendicularThrust(Float_t px, Float_t py, Float_t pz, Float_t thrux, Float_t thruy, Float_t thruz) {
    Float_t dotProduct = px * thrux + py * thruy + pz * thruz;
    Float_t pMagSquared = px * px + py * py + pz * pz;
    Float_t parallelComponentSquared = dotProduct * dotProduct;
    Float_t perpComponentSquared = pMagSquared - parallelComponentSquared;
    
    // Guard against negative numbers due to rounding errors.
    if (perpComponentSquared < 0)
        perpComponentSquared = 0;
    
    return std::sqrt(perpComponentSquared);
}

// Definition for computeMomentum.
// Returns the magnitude of the momentum vector.
double computeMomentum(Float_t px, Float_t py, Float_t pz) {
    return std::sqrt(px * px + py * py + pz * pz);
}

double polarAngle(Float_t px,Float_t py,Float_t pz){
    Float_t radius = sqrt(px*px +py*py + pz*pz);
    return acos(pz/radius);
}

double azimuthalAngle(Float_t px, Float_t py){
    return atan2(py,px);
}