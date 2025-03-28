#ifndef NANOTYPECONVERTER_H
#define NANOTYPECONVERTER_H

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TError.h>
#include <TMath.h>
#include <set>

Int_t nanoConvMC(UShort_t code)
{
  switch (code) {
  case    1: return         211; // pi+                  -> pi+
  case    2: return        -211; // pi-                  -> pi-
  case    3: return        2212; // proton               -> proton
  case    4: return       -2212; // antiproton           -> antiproton
  case    5: return         321; // K+                   -> K+
  case    6: return        -321; // K-                   -> K-
  case    7: return         311; // K0                   -> K0
  case    8: return        3122; // Lambda0              -> Lambda0
  case    9: return       -3122; // Lambda#0             -> Lambda0_bar
  case    11: return         22; // Photon conversion    -> photon conversion
  case    12: return         22; // Unconverted Photon   -> gamma
  case    13: return        -11; // e+                   -> e+
  case    14: return         11; // e-                   -> e-
  case    15: return        -13; // mu+                  -> mu+
  case    16: return         13; // mu-                  -> mu-
  case    17: return        421; // D0                   -> D0
  case    18: return       -421; // D#0                  -> D0_bar
  case    19: return          0; // Part of D0           -> ??
  case    20: return          0; // Part of D#0          -> ??
  case    21: return       3222; // Sigma+               -> Sigma+
  case    22: return       3112; // Sigma-               -> Sigma-
  case    23: return       3312; // Xi-                  -> Xi-
  case    24: return      -3312; // Xi#+                 -> Xi-_bar
  }
  return 0;
}
#endif // NANOTYPECONVERTER_H