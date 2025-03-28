//
// Look for resonances decaying into a kaon and a pion at low mass, or two kaons, in the Z->qqbar ntuple
// usage:
//        Remember to set ismc in this script and to choose data or mc files in anal.h first
//        root
//        root> .L fillkpi.C+
//        root> anal t
//        root> t.Loop()


#define anal_cxx
#include <iostream>
#include <cmath>
#include "anal.h"
#include "TArrayF.h"
#include "TMatrixF.h"
#include "TProfile.h"
#include "TGraphErrors.h"
#include <TAxis.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
using namespace std;

double length( double px, double py, double pz) {
  return sqrt(px*px+py*py+pz*pz); // a useful function
}
float chisq( float p1, float p2, float p1m, float p2m, float s1sq, float s2sq, float angle) {
  //chisquared for photon energies p1 and p2, when constraining them to have the pi0 mass (0.135 GeV)
  // assuming
  //       measured energies p1m and p2m with squared errors s1sq and s2sq
  //       assume the error on the opening angle is negligible
  float d1sq= (p1-p1m)*(p1-p1m);
  float d2sq= (p2-p2m)*(p2-p2m);
  float a = 0.135*0.135/2.0/(1.0-cos(angle));
  float d12sq = (p1*p2-a)*(p1*p2-a);           //this is the mass constraint term
  float s12sq = p1*p1*d2sq+p2*p2*d1sq;         //and its error
  //we minimise this: the p1 and p2 pulls from their measured values plus the mass pull from the pi0 mass
  return d1sq/s1sq + d2sq/s2sq + d12sq/s12sq;  
}

void anal::Loop()
{
   if (fChain == 0) return;
//***************************************************************************
// Choose data or MC here
   bool ismc=false;
   //bool ismc=true;
//***************************************************************************   
   

  // Create file for output histograms and trees.
  TFile* outFile=nullptr;
  if(ismc) {
    outFile = new TFile("../hist/mc_mkpi.root", "RECREATE");
    cout << " Running on MC events " << endl;
  }
  if(!ismc) {
    outFile = new TFile("../hist/da_mkpi.root", "RECREATE");
    cout << " Running on real data events " << endl;
  }


  // Book some example histograms

 // Angular distribution of thrust axis
  TH1F *hthru = new TH1F("hthru"," cos(theta-thrust) ",50,0.0,1.0); 
 // K0 pi-+ mass
  TH1F *hksmass = new TH1F("hksmass"," M K0pi ", 250, 0.7, 1.7);
  TH1F *hksmass1 = new TH1F("hksmass1"," M K0pi 0.01<xp<0.025", 250, 0.7, 1.7);  
  TH1F *hksmass2 = new TH1F("hksmass2"," M K0pi 0.025<xp<0.05", 250, 0.7, 1.7);
  TH1F *hksmass3 = new TH1F("hksmass3"," M K0pi 0.05<xp<0.1", 250, 0.7, 1.7);
  TH1F *hksmass4 = new TH1F("hksmass4"," M K0pi 0.1<xp<0.15", 250, 0.7, 1.7);
  TH1F *hksmass5 = new TH1F("hksmass5"," M K0pi 0.15<xp<0.2", 250, 0.7, 1.7);  
  TH1F *hksmass6 = new TH1F("hksmass6"," M K0pi 0.2<xp<0.3", 250, 0.7, 1.7);  
  TH1F *hksmass7 = new TH1F("hksmass7"," M K0pi 0.3<xp<0.5", 250, 0.7, 1.7);  
  TH1F *hksmass8 = new TH1F("hksmass8"," M K0pi 0.5<xp<1.0", 250, 0.7, 1.7);  
  
 // K+- pi-+ mass
  TH1F *hks0mass = new TH1F("hks0mass"," M Kpi ", 250, 0.7, 1.7);
  TH1F *hks0mass1 = new TH1F("hks0mass1"," M Kpi 0.01<xp<0.025", 250, 0.7, 1.7);  
  TH1F *hks0mass2 = new TH1F("hks0mass2"," M Kpi 0.025<xp<0.05", 250, 0.7, 1.7);
  TH1F *hks0mass3 = new TH1F("hks0mass3"," M Kpi 0.05<xp<0.1", 250, 0.7, 1.7);
  TH1F *hks0mass4 = new TH1F("hks0mass4"," M Kpi 0.1<xp<0.15", 250, 0.7, 1.7);
  TH1F *hks0mass5 = new TH1F("hks0mass5"," M Kpi 0.15<xp<0.2", 250, 0.7, 1.7);  
  TH1F *hks0mass6 = new TH1F("hks0mass6"," M Kpi 0.2<xp<0.3", 250, 0.7, 1.7);  
  TH1F *hks0mass7 = new TH1F("hks0mass7"," M Kpi 0.3<xp<0.5", 250, 0.7, 1.7);  
  TH1F *hks0mass8 = new TH1F("hks0mass8"," M Kpi 0.5<xp<1.0", 250, 0.7, 1.7);  
    
 // K+- pi0 mass
  TH1F *hkpi0mass = new TH1F("hkpi0mass"," M Kpi0 ", 250, 0.7, 1.7);
  TH1F *hkpi0mass1 = new TH1F("hkpi0mass1"," M Kpi0 0.01<xp<0.025", 250, 0.7, 1.7);  
  TH1F *hkpi0mass2 = new TH1F("hkpi0mass2"," M Kpi0 0.025<xp<0.05", 250, 0.7, 1.7);
  TH1F *hkpi0mass3 = new TH1F("hkpi0mass3"," M Kpi0 0.05<xp<0.1", 250, 0.7, 1.7);
  TH1F *hkpi0mass4 = new TH1F("hkpi0mass4"," M Kpi0 0.1<xp<0.15", 250, 0.7, 1.7);
  TH1F *hkpi0mass5 = new TH1F("hkpi0mass5"," M Kpi0 0.15<xp<0.2", 250, 0.7, 1.7);  
  TH1F *hkpi0mass6 = new TH1F("hkpi0mass6"," M Kpi0 0.2<xp<0.3", 250, 0.7, 1.7);  
  TH1F *hkpi0mass7 = new TH1F("hkpi0mass7"," M Kpi0 0.3<xp<0.5", 250, 0.7, 1.7);  
  TH1F *hkpi0mass8 = new TH1F("hkpi0mass8"," M Kpi0 0.5<xp<1.0", 250, 0.7, 1.7);  
  
  // K+ K- mass
  TH1F *hkkmass = new TH1F("hkkmass"," M K+K- ",100,0.95,1.15);
  TH1F *hkkmass1 = new TH1F("hkkmass1"," M K+K- 0.01<xp<0.025",100,0.95,1.15);
  TH1F *hkkmass2 = new TH1F("hkkmass2"," M K+K- 0.025<xp<0.05",100,0.95,1.15);
  TH1F *hkkmass3 = new TH1F("hkkmass3"," M K+K- 0.05<xp<0.1",100,0.95,1.15);
  TH1F *hkkmass4 = new TH1F("hkkmass4"," M K+K- 0.1<xp<0.15",100,0.95,1.15);
  TH1F *hkkmass5 = new TH1F("hkkmass5"," M K+K- 0.15<xp<0.2",100,0.95,1.15);
  TH1F *hkkmass6 = new TH1F("hkkmass6"," M K+K- 0.2<xp<0.3",100,0.95,1.15);
  TH1F *hkkmass7 = new TH1F("hkkmass7"," M K+K- 0.3<xp<0.5",100,0.95,1.15);
  TH1F *hkkmass8 = new TH1F("hkkmass8"," M K+K- 0.5<xp<1.0",100,0.95,1.15);  
  
  // K0 K0 mass (wide range)
  TH1F *hk0k0mass = new TH1F("hk0k0mass"," M K0K0 (GeV) ",200,0.95,1.95);
  // K0 K+- mass
  TH1F *hk0kmass = new TH1F("hk0kmass"," M K0K+- (GeV) ",200,0.95,1.95);
  // K+- K+- mass
  TH1F *hkkss = new TH1F("hkkss"," M K+-K+- (GeV) ",200,0.95,1.95);
  // K+- K-+ mass
  TH1F *hkkos = new TH1F("hkkos"," M K+-K-+ (GeV) ",200,0.95,1.95);

  // K+- momentum
  TH1F *hkmom = new TH1F("hkmom"," K+- momentum ",80,0.,40.);
  // K0 momentum
  TH1F *hk0mom = new TH1F("hk0mom"," K+- momentum ",80,0.,40.);
  
  // Some constants here
  double pimass = 0.139570; //pion mass
  double pi0mass =0.135;    //neautral pion mass
  double k0mass=0.497648;   //K0 mass
  double kmass=0.493677;    //K+- mass
  float lambdamass=1.11568; //Lambda (and anti-Lambda) mass
  float cmenergy = 91.2;    //Z mass
  float thresh=0.5;         //consider only combined momenta over 0.5 GeV
  
  // Input tree declaration:

  //MC flavor tag: 1=u,2=d,3=s,4=c,5=b
  //tree->Branch("mcflavor",&mcflavor,"mcflavor/b");

  //center-of-mass energy (2*beamenergy)
  //tree->Branch("cmenergy",&cmenergy,"cmenergy/F");

  //thrust axis, normalised, always positive z
  //tree->Branch("thru",thru,"thru[3]/F");

  //quark momentum (0-45.6)
  //tree->Branch("pquark",pquark,"pquark[3]/F");

  //-log10( light quark probability) in each hemisphere (0-25).
  //tree->Branch("pudsh1",&pudsh1,"pudsh1/F");
  //tree->Branch("pudsh2",&pudsh2,"pudsh2/F");

  //b-quark probability from neural network) (0-1).
  //tree->Branch("b1nn",&b1nn,"b1nn/F");
  //tree->Branch("b2nn",&b2nn,"b2nn/F");

  // neural net jet charges (0=negative and 1=positive) (0-1)
  //tree->Branch("ch1nn",&ch1nn,"ch1nn/F");
  //tree->Branch("ch2nn",&ch2nn,"ch2nn/F");

  // jet four momenta (three highest energy jets)
  //tree->Branch("pjet1",pjet1,"pjet1[4]/F");
  //tree->Branch("pjet2",pjet2,"pjet2[4]/F");
  //tree->Branch("pjet3",pjet3,"pjet3[4]/F");

  // hemisphere secondary vertex
  //tree->Branch("nbsv",&nbsv,"nbsv/s");          //always 2 hemispheres
  //tree->Branch("pxbsv",pxbsv,"pxbsv[nbsv]/F");  //b-hadron momentum [GeV]
  //tree->Branch("pybsv",pybsv,"pybsv[nbsv]/F");
  //tree->Branch("pzbsv",pzbsv,"pzbsv[nbsv]/F");
  //tree->Branch("lbsv",lbsv,"lbsv[nbsv]/F");     //decay length [cm]
  //                                                must be >10^-3
  //tree->Branch("elbsv",elbsv,"elbsv[nbsv]/F"); // its error
  //tree->Branch("chbsv",chbsv,"chbsv[nbsv]/F"); // its charge
  //tree->Branch("codebsv",codebsv,"codebsv[nbsv]/b"); // origin code (for MC)
  // 1=  u ubar, 2= d dbar, 3=s sbar, 4=c cbbar
  // 5= other b hadron, 6= charged B meson,
  // 7= unmixed Bd, 8= unmixed Bs, 9= mixed Bd, 10= mixed Bs
  // 11= Lambda b

  // number of measured charged particles and V0s:

  // tree->Branch("npart",&npart,"npart/s");

  //momentum and mass
  //tree->Branch("pmomx",pmomx,"pmomx[npart]/F");
  //tree->Branch("pmomy",pmomy,"pmomy[npart]/F");
  //tree->Branch("pmomz",pmomz,"pmomz[npart]/F");
  //tree->Branch("pmass",pmass,"pmass[npart]/F");

  //decay length
  //tree->Branch("pflight",pflight,"pflight[npart]/F");

  // Reconstruction info
  //pbits:  bit0: positive charge,
  //        bit1: Not Vdet hits in both projections
  //        bit2: distance to vertex larger than 2mm in xy and 6mm in z.
  //        bit3: lepton ID
  //        bit4: Seven or less TPC hits
  //        bit5: Primary vertex probability from VNFIT  < 1%
  //        bit6: Daugther of V0, Xsi or "kink" candidate.
  //        bit7: Product of reconstructed nuclear interaction in the
  //              detector material.        (0,255)
  //tree->Branch("pbits",pbits,"pbits[npart]/b");

  // Best estimated particle identification
  //ptype: 1 pi+  2 pi-
  //       3 p    4 pbar
  //       5 K+   6 K-
  //       7 K0   8 Lambda  9 Lambdabar 11 photon conversion
  //      12 unconverted photon
  //      13 e+  14 e- 15 mu+  16 mu-
  //      17 D0  18 D0bar 19 part of D0  20 part of D0bar 
  //      21 Sig+ 22 Sig- 
  //      23 Xi-   24 Xi+(bar)
  //      0 no estimate
  //tree->Branch("ptype",ptype,"ptype[npart]/b");

  // true type (only MC)
  //tree->Branch("ptruth",ptruth,"ptruth[npart]/b");


  // number of measured photons/pi0s
  //tree->Branch("nphot",&nphot,"nphot/s");
  //tree->Branch("pphotx",pphotx,"pphotx[nphot]/F");
  //tree->Branch("pphoty",pphoty,"pphoty[nphot]/F");
  //tree->Branch("pphotz",pphotz,"pphotz[nphot]/F");


   Long64_t nentries = fChain->GetEntriesFast();
   cout << " entries in tree " << nentries << endl;
   fChain->SetBranchStatus("*",1);  // enable all branches

   bool debug=true;
   if(debug)     cout << " ALEPH hadronic Z decays " << endl;


   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {   //loop over all events
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      if(jentry>10) debug=false;
      UShort_t mcf=(UShort_t)mcflavor;


      // *******************************Start of event selection
      if(cmenergy < 90.8 || cmenergy > 91.6)  continue;   //only Z peak data is kept
      if(fabs(thru[2])>0.8)   continue;  // cut here, because there are large efficiency losses at very forward angles

      int ngood=0;                     // count good tracks:
                                       //    at least 7 hits in the TPC
      for( int i=0; i< npart; i++) {   //    at least one layer of silicon
        if((UShort_t)pbits[i]<4) ngood++;//  good primary vertex probability
      } 
      if(ngood<2) continue;  // require 2 "good tracks", otherwise this analysis does not make sense
      if(pjet1[3]+pjet2[3]+pjet3[3] < 32.) continue; // anti tau requirement
      // ***********************************End of event selection

      hthru->Fill(thru[2]);

      
      // Here look for K0s (these have been found via their decay to pi+pi- inside the detector)
      for(int i=0;i<npart;i++) {
        if( ptype[i]==7 ) {                   // Loop over K0 candidates
	  float pv0=length(pmomx[i],pmomy[i],pmomz[i]);
	  hk0mom->Fill(pv0);
	  //positive or negative side?
	  float s1 =1.0;
	  if(pmomx[i]*thru[0]+pmomy[i]*thru[1]+pmomz[i]*thru[2]<0) s1=-1.0;
	  
          // Look for K*+- -> K0 + pi+-
          for(int j=0;j<npart;j++) {          //Loop over pion candidates on the same side
   	    if(s1*(pmomx[j]*thru[0]+pmomy[j]*thru[1]+pmomz[j]*thru[2])<0) continue;
            if((ptype[j]==1 || ptype[j]==2) && pbits[j]<4) {
	      float px=pmomx[i]+pmomx[j];
	      float py=pmomy[i]+pmomy[j];
	      float pz=pmomz[i]+pmomz[j];
              float ppi= length(pmomx[j],pmomy[j],pmomz[j]);
              float pk= length(pmomx[i],pmomy[i],pmomz[i]);
              float ener = sqrt(ppi*ppi+pimass*pimass)+sqrt(pk*pk+k0mass*k0mass);
              float plen=length(px,py,pz);
              float ksmass= sqrt(ener*ener-plen*plen);
              if(plen>thresh) {

                hksmass->Fill(ksmass);
  	        float xp = 2.0*plen/cmenergy;
		if(xp<0.025) {
		  hksmass1->Fill(ksmass);
		}else if(xp<0.05) {
		  hksmass2->Fill(ksmass);
		}else if(xp<0.1) {
		  hksmass3->Fill(ksmass);
		}else if(xp<0.15) {
		  hksmass4->Fill(ksmass);
		}else if(xp<0.2) {
		  hksmass5->Fill(ksmass);
		}else if(xp<0.3) {
		  hksmass6->Fill(ksmass);
		}else if(xp<0.5) {
		  hksmass7->Fill(ksmass);
		}else{
		  hksmass8->Fill(ksmass);
		}  
	      }
	    }
	  } // end loop charged pions
	}
      }     // end loop over K0's

      
      //K*0 -> K+  pi-
      for(int i=0;i<npart;i++) {
        if(ptype[i]==5 && pbits[i]<4) {                    // loop over K+ candidates
	  //positive or negative side?
	  float s1 =1.0;
	  if(pmomx[i]*thru[0]+pmomy[i]*thru[1]+pmomz[i]*thru[2]<0) s1=-1.0;
	  
          float pk= length(pmomx[i],pmomy[i],pmomz[i]);
          if(pk>25.) continue;                             //kaon id not reliable above 25 GeV
	  hkmom->Fill(pk);
	  
          for(int j=0;j<npart;j++) {                       // loop over pi- candidates on the same side
            if(s1*(pmomx[j]*thru[0]+pmomy[j]*thru[1]+pmomz[j]*thru[2])<0) continue;	      	    
            if(ptype[j]==2 && pbits[j]<4) {
   	    
	      float px=pmomx[i]+pmomx[j];
	      float py=pmomy[i]+pmomy[j];
	      float pz=pmomz[i]+pmomz[j];
              float ppi= length(pmomx[j],pmomy[j],pmomz[j]);
              float ener = sqrt(ppi*ppi+pimass*pimass)+sqrt(pk*pk+kmass*kmass);
              float plen=length(px,py,pz);
              float ksmass= sqrt(ener*ener-plen*plen);
              if(plen>thresh) {
		hks0mass->Fill(ksmass);
  	        float xp = 2.0*plen/cmenergy;
		if(xp<0.025) {
		  hks0mass1->Fill(ksmass);
		}else if(xp<0.05) {
		  hks0mass2->Fill(ksmass);
		}else if(xp<0.1) {
		  hks0mass3->Fill(ksmass);
		}else if(xp<0.15) {
		  hks0mass4->Fill(ksmass);
		}else if(xp<0.2) {
		  hks0mass5->Fill(ksmass);
		}else if(xp<0.3) {
		  hks0mass6->Fill(ksmass);
		}else if(xp<0.5) {
		  hks0mass7->Fill(ksmass);
		}else{
		  hks0mass8->Fill(ksmass);
		}  
	      }	
 	    }
	  } //end loop over pi- candidates
	  
          // Look also for photons (on the same side)
          for( int j=0; j<nphot-1; j++) {
            float pg1 = length(pphotx[j],pphoty[j],pphotz[j]);
	    if(s1*(pphotx[j]*thru[0]+pphoty[j]*thru[1]+pphotz[j]*thru[2])<0) continue;
	
	    //look for other photons, but allow only one of them to combine into a pi0	
	    float bestchi2=1.0e24;
	    float bestpx=0;
	    float bestpy=0;
	    float bestpz=0;
	    float bestp1=0;
	    float bestp2=0;	

	    for( int k=j+1;k<nphot; k++) {
	      if(s1*(pphotx[k]*thru[0]+pphoty[k]*thru[1]+pphotz[k]*thru[2]) <0) continue;
              float pg2 = length(pphotx[k],pphoty[k],pphotz[k]);
              float p0x=pphotx[j]+pphotx[k];       
              float p0y=pphoty[j]+pphoty[k];       
              float p0z=pphotz[j]+pphotz[k];
              float pp0= length(p0x,p0y,p0z);
	      float epi0= pg1+ pg2;
              float mpi0=sqrt(epi0*epi0-pp0*pp0); // combined invariant mass
	      float angle = acos(1.0 - mpi0*mpi0/(2*pg1*pg2)); // angle betweem the photons.


	      // Do a primitive mass-constrained chi-squared mimimalization
              // The fitted parameters are the two photon energies
	      // These are contrained by the measured energies and the known pi0 mass
	      // performed on photon pairs with initial mass in an range of about +- 2*sigma from the pi0 mass.
	      // we assume an energy resolution Delta(E)/E = 0.18/sqrt(E)
	      float chi2min=1.0e24;
	      float p1min=pg1;
	      float p2min=pg2;
              float s1sq= 0.18*0.18*pg1+0.009*0.009*pg1*pg1;
              float s2sq= 0.18*0.18*pg2+0.009*0.009*pg1*pg1;
	      float p1start = pg1-sqrt(s1sq)*2.0;
	      float p2start = pg2-sqrt(s2sq)*2.0;
	      float p1end = pg1+sqrt(s1sq)*2.0;
	      float p2end = pg2+sqrt(s2sq)*2.0;
	      float step1=(p1end-p1start)/50.;
	      float step2=(p2end-p2start)/50.;
	      if(mpi0 > 0.080 && mpi0 < 0.200) {         // if in pi0 mass range
		for(int istep1=0; istep1<50;istep1++) {  // start scan over photon energies
  	          float p1fit = p1start+step1*istep1;
                  for(int istep2=0; istep2<50;istep2++) {
	            float p2fit = p2start+step2*istep2;
	            float chi2 = chisq(p1fit,p2fit,pg1,pg2,s1sq,s2sq,angle);
	            if(chi2<chi2min) { // choose the energies that minimizes the chisquared of the pi0 hypothesis
		      chi2min=chi2;
		      p1min=p1fit;
		      p2min=p2fit;
	            }	
	          }
	        } // end scan over photon energies

                float newpx=pphotx[j]*p1min/pg1 + pphotx[k]*p2min/pg2;
	        float newpy=pphoty[j]*p1min/pg1 + pphoty[k]*p2min/pg2;
	        float newpz=pphotz[j]*p1min/pg1 + pphotz[k]*p2min/pg2;
	        float newpp=length(newpx,newpy,newpz);
	        float newepi0=sqrt(newpp*newpp+pi0mass*pi0mass);	  
	        float newmpi0=sqrt((p1min+p2min)*(p1min+p2min)-newpp*newpp);
	        if(chi2min<bestchi2) {    // store the best photon-photon combination
	          bestchi2=chi2min;
	          bestpx=newpx;
	          bestpy=newpy;
	          bestpz=newpz;
	          bestp1=p1min;
	          bestp2=p2min;
	        } //end if best combination
	      }//end if in pi0 mass range	  
	    } //end loop over second photon
	    if(bestchi2<3.0){      //if the pi0 hypothesis is acceptable
  	      float bestpp=length(bestpx,bestpy,bestpz);
	      float bestmpi0=sqrt((bestp1+bestp2)*(bestp1+bestp2)-bestpp*bestpp);
	      float bestepi0=sqrt(bestpp*bestpp+pi0mass*pi0mass);

	      // combine the new pi0 with the charged kaon
	      float px=pmomx[i]+bestpx;
	      float py=pmomy[i]+bestpy;
	      float pz=pmomz[i]+bestpz;
              float ener = bestepi0 + sqrt(pk*pk+kmass*kmass);
              float plen=length(px,py,pz);
              float ksmass= sqrt(ener*ener-plen*plen);
              if(plen>thresh) {
		hkpi0mass->Fill(ksmass);
  	        float xp = 2.0*plen/cmenergy;
		if(xp<0.025) {
		  hkpi0mass1->Fill(ksmass);
		}else if(xp<0.05) {
		  hkpi0mass2->Fill(ksmass);
		}else if(xp<0.1) {
		  hkpi0mass3->Fill(ksmass);
		}else if(xp<0.15) {
		  hkpi0mass4->Fill(ksmass);
		}else if(xp<0.2) {
		  hkpi0mass5->Fill(ksmass);
		}else if(xp<0.3) {
		  hkpi0mass6->Fill(ksmass);
		}else if(xp<0.5) {
		  hkpi0mass7->Fill(ksmass);
		}else{
		  hkpi0mass8->Fill(ksmass);
		}  
              }		
	    }
	  } // end loop over first photon
	}  //end if K+ candidate
      }  //end loop over charged particles      
      
      // K*0 -> K-  pi+
      for(int i=0;i<npart;i++) {
	  //positive or negative side?
	  float s1 =1.0;
	  if(pmomx[i]*thru[0]+pmomy[i]*thru[1]+pmomz[i]*thru[2]<0) s1=-1.0;
	
        if(ptype[i]==6 && pbits[i]<4) {                      // loop over K- candidatea
          float pk= length(pmomx[i],pmomy[i],pmomz[i]);
          if(pk>25.) continue;                               // kaon id not reliable above 25 GeV
          for(int j=0;j<npart;j++) {                         // loop over pi+ candidates on the same side
            if(s1*(pmomx[j]*thru[0]+pmomy[j]*thru[1]+pmomz[j]*thru[2])<0) continue;	      	    	    
            if(ptype[j]==1 && pbits[j]<4) {
	      float px=pmomx[i]+pmomx[j];
	      float py=pmomy[i]+pmomy[j];
	      float pz=pmomz[i]+pmomz[j];
              float ppi= length(pmomx[j],pmomy[j],pmomz[j]);
              float ener = sqrt(ppi*ppi+pimass*pimass)+sqrt(pk*pk+kmass*kmass);
              float plen=length(px,py,pz);
              float ksmass= sqrt(ener*ener-plen*plen);
              // plot Kpi mass
              if(plen>thresh) {
		hks0mass->Fill(ksmass);
  	        float xp = 2.0*plen/cmenergy;
		if(xp<0.025) {
		  hks0mass1->Fill(ksmass);
		} else if(xp<0.05) {
		  hks0mass2->Fill(ksmass);
		}else if(xp<0.1) {
		  hks0mass3->Fill(ksmass);
		}else if(xp<0.15) {
		  hks0mass4->Fill(ksmass);
		}else if(xp<0.2) {
		  hks0mass5->Fill(ksmass);
		}else if(xp<0.3) {
		  hks0mass6->Fill(ksmass);
		}else if(xp<0.5) {
		  hks0mass7->Fill(ksmass);
		}else{
		  hks0mass8->Fill(ksmass);
		}
              }		
		
  	    }
	  } //end loop over pi+ candidates
	  
          // Look also for photons (on the same side)
          for( int j=0; j<nphot-1; j++) {
            float pg1 = length(pphotx[j],pphoty[j],pphotz[j]);
	    if(s1*(pphotx[j]*thru[0]+pphoty[j]*thru[1]+pphotz[j]*thru[2])<0) continue;
	
	    //look for other photons, but allow only one of them to combine into a pi0	
	    float bestchi2=1.0e24;
	    float bestpx=0;
	    float bestpy=0;
	    float bestpz=0;
	    float bestp1=0;
	    float bestp2=0;	

	    for( int k=j+1;k<nphot; k++) {
	      if(s1*(pphotx[k]*thru[0]+pphoty[k]*thru[1]+pphotz[k]*thru[2]) <0) continue;
              float pg2 = length(pphotx[k],pphoty[k],pphotz[k]);
              float p0x=pphotx[j]+pphotx[k];       
              float p0y=pphoty[j]+pphoty[k];       
              float p0z=pphotz[j]+pphotz[k];
              float pp0= length(p0x,p0y,p0z);
	      float epi0= pg1+ pg2;
              float mpi0=sqrt(epi0*epi0-pp0*pp0); // combined invariant mass
	      float angle = acos(1.0 - mpi0*mpi0/(2*pg1*pg2)); // angle betweem the photons.


	      // Do a primitive mass-constrained chi-squared mimimalization
              // The fitted parameters are the two photon energies
	      // These are contrained by the measured energies and the known pi0 mass
	      // performed on photon pairs with initial mass in an range of about +- 2*sigma from the pi0 mass.
	      // we assume an energy resolution Delta(E)/E = 0.18/sqrt(E)
	      float chi2min=1.0e24;
	      float p1min=pg1;
	      float p2min=pg2;
              float s1sq= 0.18*0.18*pg1+0.009*0.009*pg1*pg1;
              float s2sq= 0.18*0.18*pg2+0.009*0.009*pg1*pg1;
	      float p1start = pg1-sqrt(s1sq)*2.0;
	      float p2start = pg2-sqrt(s2sq)*2.0;
	      float p1end = pg1+sqrt(s1sq)*2.0;
	      float p2end = pg2+sqrt(s2sq)*2.0;
	      float step1=(p1end-p1start)/50.;
	      float step2=(p2end-p2start)/50.;
	      if(mpi0 > 0.080 && mpi0 < 0.200) {         // if in pi0 mass range
		for(int istep1=0; istep1<50;istep1++) {  // start scan over photon energies
  	          float p1fit = p1start+step1*istep1;
                  for(int istep2=0; istep2<50;istep2++) {
	            float p2fit = p2start+step2*istep2;
	            float chi2 = chisq(p1fit,p2fit,pg1,pg2,s1sq,s2sq,angle);
	            if(chi2<chi2min) { // choose the energies that minimizes the chisquared of the pi0 hypothesis
		      chi2min=chi2;
		      p1min=p1fit;
		      p2min=p2fit;
	            }	
	          }
	        } // end scan over photon energies

                float newpx=pphotx[j]*p1min/pg1 + pphotx[k]*p2min/pg2;
	        float newpy=pphoty[j]*p1min/pg1 + pphoty[k]*p2min/pg2;
	        float newpz=pphotz[j]*p1min/pg1 + pphotz[k]*p2min/pg2;
	        float newpp=length(newpx,newpy,newpz);
	        float newepi0=sqrt(newpp*newpp+pi0mass*pi0mass);	  
	        float newmpi0=sqrt((p1min+p2min)*(p1min+p2min)-newpp*newpp);
	        if(chi2min<bestchi2) {    // store the best photon-photon combination
	          bestchi2=chi2min;
	          bestpx=newpx;
	          bestpy=newpy;
	          bestpz=newpz;
	          bestp1=p1min;
	          bestp2=p2min;
	        } //end if best combination
	      }//end if in pi0 mass range	  
	    } //end loop over second photon
	    if(bestchi2<3.0){      //if the pi0 hypothesis is acceptable
  	      float bestpp=length(bestpx,bestpy,bestpz);
	      float bestmpi0=sqrt((bestp1+bestp2)*(bestp1+bestp2)-bestpp*bestpp);
	      float bestepi0=sqrt(bestpp*bestpp+pi0mass*pi0mass);

	      // combine the new pi0 with the charged kaon
	      float px=pmomx[i]+bestpx;
	      float py=pmomy[i]+bestpy;
	      float pz=pmomz[i]+bestpz;
              float ener = bestepi0 + sqrt(pk*pk+kmass*kmass);
              float plen=length(px,py,pz);
              float ksmass= sqrt(ener*ener-plen*plen);
              if(plen>thresh) {
		hkpi0mass->Fill(ksmass);
  	        float xp = 2.0*plen/cmenergy;
		if(xp<0.025) {
		  hkpi0mass1->Fill(ksmass);
		} else if(xp<0.05) {
		  hkpi0mass2->Fill(ksmass);
		}else if(xp<0.1) {
		  hkpi0mass3->Fill(ksmass);
		}else if(xp<0.15) {
		  hkpi0mass4->Fill(ksmass);
		}else if(xp<0.2) {
		  hkpi0mass5->Fill(ksmass);
		}else if(xp<0.3) {
		  hkpi0mass6->Fill(ksmass);
		}else if(xp<0.5) {
		  hkpi0mass7->Fill(ksmass);
		}else{
		  hkpi0mass8->Fill(ksmass);
		}  
              }		
	    }
	  } // end loop over first photon
	} //end if K- candidate
      } // end loop over charged particles


      

      // Here look for phi -> K+ K-
      for(int i=0;i<npart-1;i++) {       // start loop over first kaon
	//positive or negative side?
	float s1 =1.0;
	if(pmomx[i]*thru[0]+pmomy[i]*thru[1]+pmomz[i]*thru[2]<0) s1=-1.0;
	
        if((ptype[i]==5 || ptype[i]==6) && pbits[i]<4) {
          for(int j=i+1;j<npart;j++) {   // start loop over second kaon with opposite sign
	    if(s1*(pmomx[j]*thru[0]+pmomy[j]*thru[1]+pmomz[j]*thru[2])<0) continue;  // must be on the same side	    
            if( (ptype[j]==5 || ptype[j]==6) && pbits[j]<4 && (pbits[j]%2)!=(pbits[i]%2)) {
	      float px=pmomx[i]+pmomx[j];
	      float py=pmomy[i]+pmomy[j];
	      float pz=pmomz[i]+pmomz[j];
              float ppi= length(pmomx[j],pmomy[j],pmomz[j]);
              float pk= length(pmomx[i],pmomy[i],pmomz[i]);
              float plen=length(px,py,pz);
              float ener = sqrt(ppi*ppi+kmass*kmass)+sqrt(pk*pk+kmass*kmass);
              float kkmass= sqrt(ener*ener-plen*plen);
              if(plen>thresh ) {
		hkkmass->Fill(kkmass);
		hkkos->Fill(kkmass);		
  	        float xp = 2.0*plen/cmenergy;
		if(xp<0.025) {
		  hkkmass1->Fill(kkmass);
		} else if(xp<0.05) {
		  hkkmass2->Fill(kkmass);
		}else if(xp<0.1) {
		  hkkmass3->Fill(kkmass);
		}else if(xp<0.15) {
		  hkkmass4->Fill(kkmass);
		}else if(xp<0.2) {
		  hkkmass5->Fill(kkmass);
		}else if(xp<0.3) {
		  hkkmass6->Fill(kkmass);
		}else if(xp<0.5) {
		  hkkmass7->Fill(kkmass);
		}else{
		  hkkmass8->Fill(kkmass);
		}  
	      } // end if above threshold	
	    }   // end if kaon2 with opp sign  
	  }     // end loop over trk2
          for(int j=i+1;j<npart;j++) { // start loop over second kaon with same sign
	    if(s1*(pmomx[j]*thru[0]+pmomy[j]*thru[1]+pmomz[j]*thru[2])<0) continue;  // must be on the same side	        
            if( (ptype[j]==5 || ptype[j]==6) && pbits[j]<4 && (pbits[j]%2)==(pbits[i]%2)) {
	      float px=pmomx[i]+pmomx[j];
	      float py=pmomy[i]+pmomy[j];
	      float pz=pmomz[i]+pmomz[j];
              float ppi= length(pmomx[j],pmomy[j],pmomz[j]);
              float pk= length(pmomx[i],pmomy[i],pmomz[i]);
              float plen=length(px,py,pz);
              float ener = sqrt(ppi*ppi+kmass*kmass)+sqrt(pk*pk+kmass*kmass);
              float kkmass= sqrt(ener*ener-plen*plen);
              if(plen>thresh ) hkkss->Fill(kkmass);
	    }   // end if kaon2 with same sign  
	  }     // end loop over trk2
          for(int j=0;j<npart;j++) { // start loop over neutral kaons
	    if(s1*(pmomx[j]*thru[0]+pmomy[j]*thru[1]+pmomz[j]*thru[2])<0) continue;  // must be on the same side	    	    
            if( ptype[j]==7) {
	      double px=pmomx[i]+pmomx[j];
	      double py=pmomy[i]+pmomy[j];
	      double pz=pmomz[i]+pmomz[j];
              double p2= length(pmomx[j],pmomy[j],pmomz[j]);
              double p1= length(pmomx[i],pmomy[i],pmomz[i]);
              double plen=length(px,py,pz);
              double ener = sqrt(p1*p1+kmass*kmass)+sqrt(p2*p2+k0mass*k0mass);
              double kkmass= sqrt(ener*ener-plen*plen);
              if(plen>thresh ) hk0kmass->Fill(kkmass);
	      
	    } //end if K0
	  }   //end loop over trk2
	}  // end if kaon1
      }    // end loop over trk1

      // Here look for phi -> K0 K0
      for(int i=0;i<npart-1;i++) {
	float s1 =1.0;
	if(pmomx[i]*thru[0]+pmomy[i]*thru[1]+pmomz[i]*thru[2]<0) s1=-1.0;
	
        if(ptype[i]==7) {
          for(int j=i+1;j<npart;j++) {
	    if(s1*(pmomx[j]*thru[0]+pmomy[j]*thru[1]+pmomz[j]*thru[2])<0) continue;  // must be on the same side	    	    	    
            if( ptype[j]==7) {
	      double px=pmomx[i]+pmomx[j];
	      double py=pmomy[i]+pmomy[j];
	      double pz=pmomz[i]+pmomz[j];
              double p2= length(pmomx[j],pmomy[j],pmomz[j]);
              double p1= length(pmomx[i],pmomy[i],pmomz[i]);
              double plen=length(px,py,pz);
              double ener = sqrt(p1*p1+k0mass*k0mass)+sqrt(p2*p2+k0mass*k0mass);
              double kkmass= sqrt(ener*ener-plen*plen);
              if(plen>thresh ) hk0k0mass->Fill(kkmass);
	      
	    }
	  }
	}
      }
   }

   cout << " End of job. Analysed " << hthru->GetEntries() << " Z->qqbar events "  << endl;
   cout << " Found " << hks0mass->GetEntries() << " K(+-)pi(-+) pairs with momentum > 0.5 GeV"  << endl;
   cout << " Found " << hksmass->GetEntries() << " K0pi(+-) pairs with momentum > 0.5 GeV"  << endl;
   cout << " Found " << hkkmass->GetEntries() << " K+K- pairs with momentum > 0.5 GeV"  << endl;
   cout << " Found " << hk0k0mass->GetEntries() << " K0K0 pairs with momentum > 0.5 GeV"  << endl;         

      
   outFile->Write();  // dump histograms in output file
}
