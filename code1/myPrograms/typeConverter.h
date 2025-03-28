#ifndef TYPECONVERTER_H
#define TYPECONVERTER_H

#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TError.h>
#include <TMath.h>
#include <set>

Int_t ConvMC(UShort_t code)
{
  switch (code) {
  case    1: return         22; // gamma                -> gamma
  case    2: return        -11; // e+                   -> e+
  case    3: return         11; // e-                   -> e-
  case    4: return         12; // nu_e                 -> nu_e
  case    5: return        -13; // mu+                  -> mu+
  case    6: return         13; // mu-                  -> mu-
  case    7: return        111; // pi0                  -> pi0
  case    8: return        211; // pi+                  -> pi+
  case    9: return       -211; // pi-                  -> pi-
  case   10: return        130; // K_L0                 -> K_L0
  case   11: return        321; // K+                   -> K+
  case   12: return       -321; // K-                   -> K-
  case   13: return       2112; // neutron              -> neutron
  case   14: return       2212; // proton               -> proton
  case   15: return      -2212; // antiproton           -> antiproton
  case   16: return        310; // K_S0                 -> K_S0
  case   17: return        221; // eta                  -> eta
  case   18: return       3122; // Lambda0              -> Lambda0
  case   19: return       3222; // Sigma+               -> Sigma+
  case   20: return       3212; // Sigma0               -> Sigma0
  case   21: return       3112; // Sigma-               -> Sigma-
  case   22: return       3322; // Xi0                  -> Xi0
  case   23: return       3312; // Xi-                  -> Xi-
  case   24: return       3334; // Omega-               -> Omega-
  case   25: return      -2112; // antineutron          -> antineutron
  case   26: return      -3122; // Lambda#0             -> Lambda0_bar
  case   27: return      -3112; // Sigma#-              -> Sigma-_bar
  case   28: return      -3212; // Sigma#0              -> Sigma0_bar
  case   29: return      -3222; // Sigma#+              -> Sigma+_bar
  case   30: return      -3322; // Xi#0                 -> Xi0_bar
  case   31: return      -3312; // Xi#+                 -> Xi-_bar
  case   32: return      -3334; // Omega#+              -> Omega+
  case   33: return        -15; // tau+                 -> tau+
  case   34: return         15; // tau-                 -> tau-
  case   35: return        411; // D+                   -> D+
  case   36: return       -411; // D-                   -> D-
  case   37: return        421; // D0                   -> D0
  case   38: return       -421; // D#0                  -> D0_bar
  case   39: return        431; // D_s+                 -> D_s+
  case   40: return       -431; // D_s-                 -> D_s-
  case   41: return       4122; // Lambda_c+            -> Lambda_c+
  case   42: return         24; // W+                   -> W+
  case   43: return        -24; // W-                   -> W-
  case   44: return         23; // Z0                   -> Z0
  case   45: return 1000001020; // Deuteron             -> Deuteron
  case   46: return 1000001030; // Tritium              -> Tritium
  case   47: return 1000002040; // Alpha                -> Alpha
  case   48: return          0; // Rootino              -> Rootino
  case   54: return         35; // H0                   -> H0
  case   55: return        551; // eta_b                -> eta_b
  case   56: return        311; // K0                   -> K0
  case   57: return       -311; // K0#                  -> K0_bar
  case   58: return         12; // nu_e                 -> nu_e
  case   59: return        -12; // nu_e#                -> nu_e_bar
  case   60: return         14; // nu_mu                -> nu_mu
  case   61: return        -14; // nu_mu#               -> nu_mu_bar
  case   62: return         16; // nu_tau               -> nu_tau
  case   63: return        -16; // nu_tau#              -> nu_tau_bar
  case   69: return        331; // eta'                 -> eta'
  case   73: return        443; // J/psi                -> J/psi
  case   74: return     100443; // psi'                 -> psi'
  case   75: return        441; // eta_c                -> eta_c
  case   76: return        213; // rho+                 -> rho+
  case   77: return       -213; // rho-                 -> rho-
  case   78: return        323; // K*+                  -> K*+
  case   79: return       -323; // K*-                  -> K*-
  case   80: return        313; // K*0                  -> K*0
  case   81: return       -313; // K*#0                 -> K*0_bar
  case   82: return        423; // D*0                  -> D*0
  case   83: return       -423; // D*#0                 -> D*0_bar
  case   84: return        413; // D*+                  -> D*+
  case   85: return       -413; // D*-                  -> D*-
  case   86: return        433; // D*_s+                -> D*_s+
  case   87: return       -433; // D*_s-                -> D*_s-
  case   88: return        113; // rho0                 -> rho0
  case   89: return        223; // omega                -> omega
  case   90: return        333; // phi                  -> phi
  case   94: return        553; // Upsilon              -> Upsilon
  case  100: return         21; // g                    -> g
  case  101: return          2; // u                    -> u
  case  102: return          1; // d                    -> d
  case  103: return          3; // s                    -> s
  case  104: return          4; // c                    -> c
  case  105: return          5; // b                    -> b
  case  106: return          6; // t                    -> t
  case  107: return         -2; // u#                   -> u_bar
  case  108: return         -1; // d#                   -> d_bar
  case  109: return         -3; // s#                   -> s_bar
  case  110: return         -4; // c#                   -> c_bar
  case  111: return         -5; // b#                   -> b_bar
  case  112: return         -6; // t#                   -> t_bar
  case  115: return       -521; // B-                   -> B-
  case  116: return        521; // B+                   -> B+
  case  117: return        511; // B0                   -> B0
  case  118: return       -511; // B#0                  -> B0_bar
  case  119: return        531; // B_s0                 -> B_s0
  case  120: return       -531; // B_s#0                -> B_s0_bar
  case  121: return       -541; // B_c-                 -> B_c-
  case  122: return        541; // B_c+                 -> B_c+
  case  123: return       -523; // B*-                  -> B*-
  case  124: return        523; // B*+                  -> B*+
  case  125: return        513; // B*0                  -> B*0
  case  126: return       -513; // B*#0                 -> B*0_bar
  case  127: return        533; // B*_s0                -> B*_s0
  case  151: return       2224; // Delta++              -> Delta++
  case  153: return       2214; // Delta+               -> Delta+
  case  154: return      -1114; // Delta#-              -> Delta-_bar
  case  155: return       2114; // Delta0               -> Delta0
  case  156: return      -2114; // Delta#0              -> Delta0_bar
  case  157: return       1114; // Delta-               -> Delta-
  case  158: return      -2214; // Delta#+              -> Delta+_bar
  case  159: return       3224; // Sigma*+              -> Sigma*+
  case  160: return      -3114; // Sigma*#-             -> Sigma*-_bar
  case  161: return       3214; // Sigma*0              -> Sigma*0
  case  162: return      -3214; // Sigma*#0             -> Sigma*0_bar
  case  163: return       3114; // Sigma*-              -> Sigma*-
  case  164: return      -3224; // Sigma*#+             -> Sigma*+_bar
  case  165: return       3324; // Xi*0                 -> Xi*0
  case  166: return      -3324; // Xi*#0                -> Xi*0_bar
  case  167: return       3314; // Xi*-                 -> Xi*-
  case  168: return      -3314; // Xi*#+                -> Xi*+
  case  169: return       4222; // Sigma_c++            -> Sigma_c++
  case  171: return       4212; // Sigma_c+             -> Sigma_c+
  case  173: return       4112; // Sigma_c0             -> Sigma_c0
  case  174: return      -4112; // Sigma_c#0            -> Sigma_c0_bar
  case  175: return       4232; // Xi_c+                -> Xi_c+
  case  177: return       4132; // Xi_c0                -> Xi_c0
  case  178: return      -4132; // Xi_c#0               -> Xi_c0_bar
  case  179: return       4332; // Omega_c0             -> Omega_c0
  case  180: return      -4332; // Omega_c#0            -> Omega_c0_bar
  case  185: return       4224; // Sigma*_c++           -> Sigma*_c++
  case  187: return       4214; // Sigma*_c+            -> Sigma*_c+
  case  189: return       4114; // Sigma*_c0            -> Sigma*_c0
  case  190: return      -4114; // Sigma*_c#0           -> Sigma*_c0_bar
  case  191: return       4324; // Xi*_c+               -> Xi*_c+
  case  193: return       4314; // Xi*_c0               -> Xi*_c0
  case  194: return      -4314; // Xi*_c#0              -> Xi*_c0_bar
  case  195: return       4334; // Omega*_c0            -> Omega*_c0
  case  196: return      -4334; // Omega*_c#0           -> Omega*_c0_bar
  case  197: return       4422; // Xi_cc++              -> Xi_cc++
  case  199: return       4412; // Xi_cc+               -> Xi_cc+
  case  201: return       4432; // Omega_cc+            -> Omega_cc+
  case  203: return       4424; // Xi*_cc++             -> Xi*_cc++
  case  205: return       4414; // Xi*_cc+              -> Xi*_cc+
  case  207: return       4434; // Omega*_cc+           -> Omega*_cc+
  case  211: return       5222; // Sigma_b+             -> Sigma_b+
  case  212: return      -5112; // Sigma_b#-            -> Sigma_b-_bar
  case  213: return       5212; // Sigma_b0             -> Sigma_b0
  case  214: return      -5212; // Sigma_b#0            -> Sigma_b0_bar
  case  215: return       5112; // Sigma_b-             -> Sigma_b-
  case  216: return      -5222; // Sigma_b#+            -> Sigma_b+_bar
  case  217: return       5232; // Xi_b0                -> Xi_b0
  case  218: return      -5232; // Xi_b#0               -> Xi_b0_bar
  case  219: return       5132; // Xi_b-                -> Xi_b-
  case  220: return      -5132; // Xi_b#+               -> Xi_b+
  case  221: return       5332; // Omega_b-             -> Omega_b-
  case  222: return      -5332; // Omega_b#+            -> Omega_b+
  case  223: return       5242; // Xi_bc+               -> Xi_bc+
  case  225: return       5142; // Xi_bc0               -> Xi_bc0
  case  226: return      -5142; // Xi_bc#0              -> Xi_bc0_bar
  case  227: return       5342; // Omega_bc0            -> Omega_bc0
  case  228: return      -5342; // Omega_bc#0           -> Omega_bc0_bar
  case  229: return       5442; // Omega_bcc+           -> Omega_bcc+
  case  231: return       5522; // Xi_bb0               -> Xi_bb0
  case  232: return      -5522; // Xi_bb#0              -> Xi_bb0_bar
  case  233: return       5512; // Xi_bb-               -> Xi_bb-
  case  234: return      -5512; // Xi_bb#+              -> Xi_bb+
  case  235: return       5532; // Omega_bb-            -> Omega_bb-
  case  236: return      -5532; // Omega_bb#+           -> Omega_bb+
  case  237: return       5542; // Omega_bbc0           -> Omega_bbc0
  case  238: return      -5542; // Omega_bbc#0          -> Omega_bbc0_bar
  case  259: return       5122; // Lambda_b0            -> Lambda_b0
  case  260: return      -5122; // Lambda_b#0           -> Lambda_b0_bar
  case  283: return       5224; // Sigma*_b+            -> Sigma*_b+
  case  284: return      -5114; // Sigma*_b#-           -> Sigma*_b-_bar
  case  285: return       5214; // Sigma*_b0            -> Sigma*_b0
  case  286: return      -5214; // Sigma*_b#0           -> Sigma*_b0_bar
  case  287: return       5114; // Sigma*_b-            -> Sigma*_b-
  case  288: return      -5224; // Sigma*_b#+           -> Sigma*_b+_bar
  case  289: return       5324; // Xi*_b0               -> Xi*_b0
  case  290: return      -5324; // Xi*_b#0              -> Xi*_b0_bar
  case  291: return       5314; // Xi*_b-               -> Xi*_b-
  case  292: return      -5314; // Xi*_b#+              -> Xi*_b+
  case  293: return       5334; // Omega*_b-            -> Omega*_b-
  case  294: return      -5334; // Omega*_b#+           -> Omega*_b+
  case  295: return       5424; // Xi*_bc+              -> Xi*_bc+
  case  297: return       5414; // Xi*_bc0              -> Xi*_bc0
  case  298: return      -5414; // Xi*_bc#0             -> Xi*_bc0_bar
  case  299: return       5434; // Omega*_bc0           -> Omega*_bc0
  case  300: return      -5434; // Omega*_bc#0          -> Omega*_bc0_bar
  case  301: return       5444; // Omega*_bcc+          -> Omega*_bcc+
  case  351: return       5524; // Xi*_bb0              -> Xi*_bb0
  case  352: return      -5524; // Xi*_bb#0             -> Xi*_bb0_bar
  case  353: return       5514; // Xi*_bb-              -> Xi*_bb-
  case  354: return      -5514; // Xi*_bb#+             -> Xi*_bb+
  case  355: return       5534; // Omega*_bb-           -> Omega*_bb-
  case  356: return      -5534; // Omega*_bb#+          -> Omega*_bb+
  case  357: return       5544; // Omega*_bbc0          -> Omega*_bbc0
  case  358: return      -5544; // Omega*_bbc#0         -> Omega*_bbc0_bar
  // Below follows the unknown particles, 168 in total 
  case   49: return          0; // GeantMino
  case   50: return          0; // GeantBino
  case   51: return          0; // GeantAbino
  case   52: return          0; // GeantPhino
  case   53: return          0; // Lambda_c#-
  case   64: return          0; // a1+
  case   65: return          0; // a1-
  case   66: return          0; // a10
  case   67: return          0; // f0_975
  case   68: return          0; // a0_980
  case   70: return          0; // chi_c0
  case   71: return          0; // chi_c1
  case   72: return          0; // chi_c2
  case   91: return          0; // chi_b0
  case   92: return          0; // chi_b1
  case   93: return          0; // chi_b2
  case   95: return          0; // Upsilon_2s
  case   96: return          0; // eta_t
  case   97: return          0; // chi_t0
  case   98: return          0; // chi_t1
  case   99: return          0; // chi_t2
  case  113: return          0; // Theta
  case  114: return          0; // Thetapr
  case  128: return          0; // Bs*#0
  case  129: return          0; // Bc*-
  case  130: return          0; // Bc*+
  case  131: return          0; // T0
  case  132: return          0; // T#0
  case  133: return          0; // T+
  case  134: return          0; // T-
  case  135: return          0; // T_s+
  case  136: return          0; // T_s-
  case  137: return          0; // T_c0
  case  138: return          0; // T_c#0
  case  139: return          0; // T_b+
  case  140: return          0; // T_b-
  case  141: return          0; // T*0
  case  142: return          0; // T*#0
  case  143: return          0; // T*+
  case  144: return          0; // T*-
  case  145: return          0; // T*_s+
  case  146: return          0; // T*_s-
  case  147: return          0; // T*_c0
  case  148: return          0; // T*_c#0
  case  149: return          0; // T*_b+
  case  150: return          0; // T*_b-
  case  152: return          0; // Delta#--
  case  170: return          0; // Sigma_c#--
  case  172: return          0; // Sigma_c#-
  case  176: return          0; // Xi_c#-
  case  181: return          0; // Xi0_c+
  case  182: return          0; // Xi0_c#-
  case  183: return          0; // Xi0_c0
  case  184: return          0; // Xi0_c#0
  case  186: return          0; // Sigma*_c#--
  case  188: return          0; // Sigma*_c#-
  case  192: return          0; // Xi*_c#-
  case  198: return          0; // Xi_cc#--
  case  200: return          0; // Xi_cc#-
  case  202: return          0; // Omega_cc#-
  case  204: return          0; // Xi*_cc#--
  case  206: return          0; // Xi*_cc#-
  case  208: return          0; // Omega*_cc#-
  case  209: return          0; // Omega_ccc++
  case  210: return          0; // Omega_ccc#--
  case  224: return          0; // Xi_bc#-
  case  230: return          0; // Omega_bcc#-
  case  239: return          0; // Sigma_t++
  case  240: return          0; // Sigma_t#--
  case  241: return          0; // Sigma_t+
  case  242: return          0; // Sigma_t#-
  case  243: return          0; // Sigma_t0
  case  244: return          0; // Sigma_t#0
  case  245: return          0; // Xi_t+
  case  246: return          0; // Xi_t#-
  case  247: return          0; // Xi_t0
  case  248: return          0; // Xi_t#0
  case  249: return          0; // Omega_t0
  case  250: return          0; // Omega_t#0
  case  251: return          0; // Xi_tc++
  case  252: return          0; // Xi_tc#--
  case  253: return          0; // Xi_tc+
  case  254: return          0; // Xi_tc#-
  case  255: return          0; // Omega_tc+
  case  256: return          0; // Omega_tc#-
  case  257: return          0; // Omega_tcc++
  case  258: return          0; // Omega_tcc#--
  case  261: return          0; // Xi0_b0
  case  262: return          0; // Xi0_b#0
  case  263: return          0; // Xi0_b-
  case  264: return          0; // Xi0_b#+
  case  265: return          0; // Xi0_bc+
  case  266: return          0; // Xi0_bc#-
  case  267: return          0; // Xi0_bc0
  case  268: return          0; // Xi0_bc#0
  case  269: return          0; // Omega_0bc0
  case  270: return          0; // Omega_0bc#0
  case  271: return          0; // Lambda_t+
  case  272: return          0; // Lambda_t#-
  case  273: return          0; // Xi0_t+
  case  274: return          0; // Xi0_t#-
  case  275: return          0; // Xi0_t0
  case  276: return          0; // Xi0_t#0
  case  277: return          0; // Xi0_tc0++
  case  278: return          0; // Xi0_tc0#--
  case  279: return          0; // Xi0_tc+
  case  280: return          0; // Xi0_tc#-
  case  281: return          0; // Omega_0tc+
  case  282: return          0; // Omega_0tc#-
  case  296: return          0; // Xi*_bc#-
  case  302: return          0; // Omega*_bcc#-
  case  303: return          0; // Sigma*_t++
  case  304: return          0; // Sigma*_t#--
  case  305: return          0; // Sigma*_t+
  case  306: return          0; // Sigma*_t#-
  case  307: return          0; // Sigma*_t0
  case  308: return          0; // Sigma*_t#0
  case  309: return          0; // Xi*_t+
  case  310: return          0; // Xi*_t#-
  case  311: return          0; // Xi*_t0
  case  312: return          0; // Xi*_t#0
  case  313: return          0; // Omega*_t0
  case  314: return          0; // Omega*_t#0
  case  315: return          0; // Xi*_tc++
  case  316: return          0; // Xi*_tc#--
  case  317: return          0; // Xi*_t+
  case  318: return          0; // Xi*_t#-
  case  319: return          0; // Omega*_tc+
  case  320: return          0; // Omega*_tc#-
  case  321: return          0; // Omega*_tcc++
  case  322: return          0; // Omega*_tcc#--
  case  323: return          0; // Xi*_tb+
  case  324: return          0; // Xi*_tb#-
  case  325: return          0; // Xi*_tb0
  case  326: return          0; // Xi*_tb#0
  case  327: return          0; // Omega*_tb0
  case  328: return          0; // Omega*_tb#0
  case  329: return          0; // Omega*_tbc+
  case  330: return          0; // Omega*_tbc#-
  case  331: return          0; // Omega*_tbb0
  case  332: return          0; // Omega*_tbb#0
  case  333: return          0; // Xi_tb+
  case  334: return          0; // Xi_tb#-
  case  335: return          0; // Xi_tb0
  case  336: return          0; // Xi_tb#0
  case  337: return          0; // Omega_tb0
  case  338: return          0; // Omega_tb#0
  case  339: return          0; // Omega_tbc+
  case  340: return          0; // Omega_tbc#-
  case  341: return          0; // Omega_tbb0
  case  342: return          0; // Omega_tbb#0
  case  343: return          0; // Xi0_tb+
  case  344: return          0; // Xi0_tb#-
  case  345: return          0; // Xi0_tb0
  case  346: return          0; // Xi0_tb#0
  case  347: return          0; // Omega_0tb0
  case  348: return          0; // Omega_0tb#0
  case  349: return          0; // Omega_0tbc+
  case  350: return          0; // Omega_0tbc#-
  case  359: return          0; // Omega_bbb-
  case  360: return          0; // Omega_bbb#+
  case  361: return          0; // beam_e+
  case  362: return          0; // beam_e-
  case  363: return          0; // Charged
  case  364: return          0; // Ecal
  case  365: return          0; // Hcal
  case  366: return          0; // CALobj
  case  367: return          0; // last_st_par
  }
  return 0;
}
#endif // TYPECONVERTER_H