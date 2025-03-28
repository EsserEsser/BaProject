//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb 26 15:45:37 2025 by ROOT version 6.35.01
// from TTree tree/zqq tree
// found on file: /USERS/magnussellebjerg/BA/data/zqqda91.root
//////////////////////////////////////////////////////////

#ifndef smalldataTree_h
#define smalldataTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class smalldataTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UChar_t         mcflavor;
   Float_t         cmenergy;
   Float_t         thru[3];
   Float_t         pquark[3];
   Float_t         pudsh1;
   Float_t         pudsh2;
   Float_t         b1nn;
   Float_t         b2nn;
   Float_t         ch1nn;
   Float_t         ch2nn;
   Float_t         pjet1[4];
   Float_t         pjet2[4];
   Float_t         pjet3[4];
   UShort_t        nbsv;
   Float_t         pxbsv[2];   //[nbsv]
   Float_t         pybsv[2];   //[nbsv]
   Float_t         pzbsv[2];   //[nbsv]
   Float_t         lbsv[2];   //[nbsv]
   Float_t         elbsv[2];   //[nbsv]
   Float_t         chbsv[2];   //[nbsv]
   UChar_t         codebsv[2];   //[nbsv]
   UShort_t        npart;
   Float_t         pmomx[57];   //[npart]
   Float_t         pmomy[57];   //[npart]
   Float_t         pmomz[57];   //[npart]
   Float_t         pmass[57];   //[npart]
   Float_t         pflight[57];   //[npart]
   UShort_t        nphot;
   Float_t         pphotx[22];   //[nphot]
   Float_t         pphoty[22];   //[nphot]
   Float_t         pphotz[22];   //[nphot]
   UChar_t         pbits[57];   //[npart]
   UChar_t         ptype[57];   //[npart]
   UChar_t         ptruth[57];   //[npart]
   UShort_t        pmoth[57];   //[npart]

   // List of branches
   TBranch        *b_mcflavor;   //!
   TBranch        *b_cmenergy;   //!
   TBranch        *b_thru;   //!
   TBranch        *b_pquark;   //!
   TBranch        *b_pudsh1;   //!
   TBranch        *b_pudsh2;   //!
   TBranch        *b_b1nn;   //!
   TBranch        *b_b2nn;   //!
   TBranch        *b_ch1nn;   //!
   TBranch        *b_ch2nn;   //!
   TBranch        *b_pjet1;   //!
   TBranch        *b_pjet2;   //!
   TBranch        *b_pjet3;   //!
   TBranch        *b_nbsv;   //!
   TBranch        *b_pxbsv;   //!
   TBranch        *b_pybsv;   //!
   TBranch        *b_pzbsv;   //!
   TBranch        *b_lbsv;   //!
   TBranch        *b_elbsv;   //!
   TBranch        *b_chbsv;   //!
   TBranch        *b_codebsv;   //!
   TBranch        *b_npart;   //!
   TBranch        *b_pmomx;   //!
   TBranch        *b_pmomy;   //!
   TBranch        *b_pmomz;   //!
   TBranch        *b_pmass;   //!
   TBranch        *b_pflight;   //!
   TBranch        *b_nphot;   //!
   TBranch        *b_pphotx;   //!
   TBranch        *b_pphoty;   //!
   TBranch        *b_pphotz;   //!
   TBranch        *b_pbits;   //!
   TBranch        *b_ptype;   //!
   TBranch        *b_ptruth;   //!
   TBranch        *b_pmoth;   //!

   smalldataTree(TTree *tree=0);
   virtual ~smalldataTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef smalldataTree_cxx
smalldataTree::smalldataTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/USERS/magnussellebjerg/BA/data/zqqda91.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/USERS/magnussellebjerg/BA/data/zqqda91.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

smalldataTree::~smalldataTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t smalldataTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t smalldataTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void smalldataTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mcflavor", &mcflavor, &b_mcflavor);
   fChain->SetBranchAddress("cmenergy", &cmenergy, &b_cmenergy);
   fChain->SetBranchAddress("thru", thru, &b_thru);
   fChain->SetBranchAddress("pquark", pquark, &b_pquark);
   fChain->SetBranchAddress("pudsh1", &pudsh1, &b_pudsh1);
   fChain->SetBranchAddress("pudsh2", &pudsh2, &b_pudsh2);
   fChain->SetBranchAddress("b1nn", &b1nn, &b_b1nn);
   fChain->SetBranchAddress("b2nn", &b2nn, &b_b2nn);
   fChain->SetBranchAddress("ch1nn", &ch1nn, &b_ch1nn);
   fChain->SetBranchAddress("ch2nn", &ch2nn, &b_ch2nn);
   fChain->SetBranchAddress("pjet1", pjet1, &b_pjet1);
   fChain->SetBranchAddress("pjet2", pjet2, &b_pjet2);
   fChain->SetBranchAddress("pjet3", pjet3, &b_pjet3);
   fChain->SetBranchAddress("nbsv", &nbsv, &b_nbsv);
   fChain->SetBranchAddress("pxbsv", pxbsv, &b_pxbsv);
   fChain->SetBranchAddress("pybsv", pybsv, &b_pybsv);
   fChain->SetBranchAddress("pzbsv", pzbsv, &b_pzbsv);
   fChain->SetBranchAddress("lbsv", lbsv, &b_lbsv);
   fChain->SetBranchAddress("elbsv", elbsv, &b_elbsv);
   fChain->SetBranchAddress("chbsv", chbsv, &b_chbsv);
   fChain->SetBranchAddress("codebsv", codebsv, &b_codebsv);
   fChain->SetBranchAddress("npart", &npart, &b_npart);
   fChain->SetBranchAddress("pmomx", pmomx, &b_pmomx);
   fChain->SetBranchAddress("pmomy", pmomy, &b_pmomy);
   fChain->SetBranchAddress("pmomz", pmomz, &b_pmomz);
   fChain->SetBranchAddress("pmass", pmass, &b_pmass);
   fChain->SetBranchAddress("pflight", pflight, &b_pflight);
   fChain->SetBranchAddress("nphot", &nphot, &b_nphot);
   fChain->SetBranchAddress("pphotx", pphotx, &b_pphotx);
   fChain->SetBranchAddress("pphoty", pphoty, &b_pphoty);
   fChain->SetBranchAddress("pphotz", pphotz, &b_pphotz);
   fChain->SetBranchAddress("pbits", pbits, &b_pbits);
   fChain->SetBranchAddress("ptype", ptype, &b_ptype);
   fChain->SetBranchAddress("ptruth", ptruth, &b_ptruth);
   fChain->SetBranchAddress("pmoth", pmoth, &b_pmoth);
   Notify();
}

bool smalldataTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
   std::cout << "=== New file loaded in TChain === " << std::endl;


   return true;
}

void smalldataTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t smalldataTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef smalldataTree_cxx
