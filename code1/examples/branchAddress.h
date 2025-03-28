
#ifndef branchAddress_h
#define branchAddress_h

/* This is where i define all of the branches */


    
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

// myTree->SetBranchAddress("npart",&npart);
// myTree->SetBranchAddress("pbits",pbits);
// myTree->SetBranchAddress("ptype",ptype);
// myTree->SetBranchAddress("ptruth",ptruth);
// myTree->SetBranchAddress("pmoth",pmoth);

myTree->SetBranchAddress("mcflavor", &mcflavor);
myTree->SetBranchAddress("cmenergy", &cmenergy);
myTree->SetBranchAddress("thru", thru);
myTree->SetBranchAddress("pquark", pquark);
myTree->SetBranchAddress("pudsh1", &pudsh1);
myTree->SetBranchAddress("pudsh2", &pudsh2);
myTree->SetBranchAddress("b1nn", &b1nn);
myTree->SetBranchAddress("b2nn", &b2nn);
myTree->SetBranchAddress("ch1nn", &ch1nn);
myTree->SetBranchAddress("ch2nn", &ch2nn);
myTree->SetBranchAddress("pjet1", pjet1);
myTree->SetBranchAddress("pjet2", pjet2);
myTree->SetBranchAddress("pjet3", pjet3);
myTree->SetBranchAddress("nbsv", &nbsv);
myTree->SetBranchAddress("pxbsv", pxbsv);
myTree->SetBranchAddress("pybsv", pybsv);
myTree->SetBranchAddress("pzbsv", pzbsv);
myTree->SetBranchAddress("lbsv", lbsv);
myTree->SetBranchAddress("elbsv", elbsv);
myTree->SetBranchAddress("chbsv", chbsv);
myTree->SetBranchAddress("codebsv", codebsv);
myTree->SetBranchAddress("npart", &npart);
myTree->SetBranchAddress("pmomx", pmomx);
myTree->SetBranchAddress("pmomy", pmomy);
myTree->SetBranchAddress("pmomz", pmomz);
myTree->SetBranchAddress("pmass", pmass);
myTree->SetBranchAddress("pflight", pflight);
myTree->SetBranchAddress("nphot", &nphot);
myTree->SetBranchAddress("pphotx", pphotx);
myTree->SetBranchAddress("pphoty", pphoty);
myTree->SetBranchAddress("pphotz", pphotz);
myTree->SetBranchAddress("pbits", pbits);
myTree->SetBranchAddress("ptype", ptype);
myTree->SetBranchAddress("ptruth", ptruth);
myTree->SetBranchAddress("pmoth", pmoth);



#endif