
static  int      myDarkRed     = TColor::GetColor(128,0,0);
static  int      myDarkGreen   = TColor::GetColor(0,128,0);
static  int      myDarkBlue    = TColor::GetColor(0,0,128);

void pics()
{
gSystem->Load("libTree.so");
gSystem->Load("libGeom.so");
gSystem->Load("libVMC.so");
gSystem->Load("libPhysics.so");
gSystem->Load("libMinuit.so");
// gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libSTEERBase.so");
// gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libESD.so");
// gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libAOD.so");
// gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libOADB.so");
// gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libANALYSIS.so");
// gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libANALYSISalice.so");
// gROOT->ProcessLine(".include $ALICE_ROOT/include");

myOptions();
gROOT->ForceStyle();

TFile *f1 = new TFile("cdfout.root");

// f1->ls();

TList* hlist_ua104 = (TList*)f1->Get("cdfout.root:CDFhistos_aod_ua104_b2_filter00032_cut01000/CDFhistos_aod_ua104_b2_filter00032_cut01000_j1t0_j1pt0");
TList* hlist_ua107 = (TList*)f1->Get("cdfout.root:CDFhistos_aod_ua107_b2_filter00032_cut01000/CDFhistos_aod_ua107_b2_filter00032_cut01000_j1t0_j1pt0");
TList* hlist_ua104_cut2 = (TList*)f1->Get("cdfout.root:CDFhistos_aod_ua104_b2_filter00032_cut02000/CDFhistos_aod_ua104_b2_filter00032_cut02000_j1t0_j1pt0");
TList* hlist_ua107_cut2 = (TList*)f1->Get("cdfout.root:CDFhistos_aod_ua107_b2_filter00032_cut02000/CDFhistos_aod_ua107_b2_filter00032_cut02000_j1t0_j1pt0");


// cout << hlist_ua104 << endl ;
// cout << hlist_ua107 << endl ;
// cout << hlist_ua104_cut2 << endl ;
// cout << hlist_ua107_cut2 << endl ;

makehistos();

Int_t list_idx = -1 ;

//__________________________________________________________________________________________
TCanvas *c5 = new TCanvas("c5","Distribution of jets in events");
c5->cd(); c5->SetLogy();
list_idx = 4 ;

fh04_01_5  = (TH1F*) hlist_ua104->At(list_idx) ; fh04_01_5->SetMarkerColor(2) ; fh04_01_5->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_5->Draw();

fh04_01_5->GetXaxis()->SetRangeUser(1,7);
fh04_01_5->GetXaxis()->CenterTitle(true);
fh04_01_5->GetYaxis()->CenterTitle(true);

fh04_02_5  = (TH1F*) hlist_ua104_cut2->At(list_idx) ; fh04_02_5->SetMarkerColor(51) ; fh04_02_5->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_5->Draw("SAME");

fh07_01_5  = (TH1F*) hlist_ua107->At(list_idx) ; fh07_01_5->SetMarkerColor(4) ; fh07_01_5->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_5->Draw("SAME");

fh07_02_5  = (TH1F*) hlist_ua107_cut2->At(list_idx) ; fh07_02_5->SetMarkerColor(3) ; fh07_02_5->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_5->Draw("SAME");


legend();

Double_t jetev_04_01  = fh04_01_5->GetEntries();
Double_t jetev_04_02  = fh04_02_5->GetEntries();
Double_t jetev_07_01  = fh07_01_5->GetEntries();
Double_t jetev_07_02  = fh07_02_5->GetEntries();

cout.setf(ios::fixed,ios::floatfield);
cout << "jetev_04_01 : " << jetev_04_01 << endl ;
cout << "jetev_04_02 : " << jetev_04_02 << endl ;
cout << "jetev_07_01 : " << jetev_07_01 << endl ;
cout << "jetev_07_02 : " << jetev_07_02 << endl ;






//__________________________________________________________________________________________
TCanvas *c23 = new TCanvas("c23","TOTAL Pt Distribution of charged particles");
c23->cd(); c23->SetLogy();
list_idx = 19;

fh04_01_23  = (TH1F*) hlist_ua104->At(list_idx) ; fh04_01_23->SetMarkerColor(2) ; fh04_01_23->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_23->Draw();

// fh04_01_23->GetXaxis()->SetRangeUser(1,7);
fh04_01_23->GetXaxis()->CenterTitle(true);
fh04_01_23->GetYaxis()->CenterTitle(true);

fh04_02_23  = (TH1F*) hlist_ua104_cut2->At(list_idx) ; fh04_02_23->SetMarkerColor(51) ; fh04_02_23->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_23->Draw("SAME");

fh07_01_23  = (TH1F*) hlist_ua107->At(list_idx) ; fh07_01_23->SetMarkerColor(4) ; fh07_01_23->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_23->Draw("SAME");

fh07_02_23  = (TH1F*) hlist_ua107_cut2->At(list_idx) ; fh07_02_23->SetMarkerColor(3) ; fh07_02_23->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_23->Draw("SAME");

legend();

//__________________________________________________________________________________________
TCanvas *c23jet1 = new TCanvas("c23jet1","TOTAL Pt Distribution of charged particles - jet1");
c23jet1->cd(); c23jet1->SetLogy();
list_idx = 20;

fh04_01_23jet1  = (TH1F*) hlist_ua104->At(list_idx) ; fh04_01_23jet1->SetMarkerColor(2) ; fh04_01_23jet1->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_23jet1->Draw();

// fh04_01_23jet1->GetXaxis()->SetRangeUser(1,7);
fh04_01_23jet1->GetXaxis()->CenterTitle(true);
fh04_01_23jet1->GetYaxis()->CenterTitle(true);

fh04_02_23jet1  = (TH1F*) hlist_ua104_cut2->At(list_idx) ; fh04_02_23jet1->SetMarkerColor(51) ; fh04_02_23jet1->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_23jet1->Draw("SAME");

fh07_01_23jet1  = (TH1F*) hlist_ua107->At(list_idx) ; fh07_01_23jet1->SetMarkerColor(4) ; fh07_01_23jet1->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_23jet1->Draw("SAME");

fh07_02_23jet1  = (TH1F*) hlist_ua107_cut2->At(list_idx) ; fh07_02_23jet1->SetMarkerColor(3) ; fh07_02_23jet1->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_23jet1->Draw("SAME");

legend();





//__________________________________________________________________________________________
TCanvas *c1 = new TCanvas("c1","Pt distribution of jets");
c1->cd(); c1->SetLogy();
list_idx = 0;

fh04_01_1  = (TH1F*) hlist_ua104->At(list_idx) ; fh04_01_1->SetMarkerColor(2) ; fh04_01_1->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_1->Draw();

// fh04_01_1->GetXaxis()->SetRangeUser(1,7);
fh04_01_1->GetXaxis()->CenterTitle(true);
fh04_01_1->GetYaxis()->CenterTitle(true);

fh04_02_1  = (TH1F*) hlist_ua104_cut2->At(list_idx) ; fh04_02_1->SetMarkerColor(51) ; fh04_02_1->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_1->Draw("SAME");

fh07_01_1  = (TH1F*) hlist_ua107->At(list_idx) ; fh07_01_1->SetMarkerColor(4) ; fh07_01_1->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_1->Draw("SAME");

fh07_02_1  = (TH1F*) hlist_ua107_cut2->At(list_idx) ; fh07_02_1->SetMarkerColor(3) ; fh07_02_1->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_1->Draw("SAME");

legend();



//__________________________________________________________________________________________
TCanvas *c2 = new TCanvas("c2","Eta distribution of jets");
c2->cd(); c2->SetLogy();
list_idx = 1;

fh04_01_2  = (TH1F*) hlist_ua104->At(list_idx) ; fh04_01_2->SetMarkerColor(2) ; fh04_01_2->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_2->Draw();

// fh04_01_2->GetXaxis()->SetRangeUser(1,7);
fh04_01_2->GetXaxis()->CenterTitle(true);
fh04_01_2->GetYaxis()->CenterTitle(true);

fh04_02_2  = (TH1F*) hlist_ua104_cut2->At(list_idx) ; fh04_02_2->SetMarkerColor(51) ; fh04_02_2->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_2->Draw("SAME");

fh07_01_2  = (TH1F*) hlist_ua107->At(list_idx) ; fh07_01_2->SetMarkerColor(4) ; fh07_01_2->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_2->Draw("SAME");

fh07_02_2  = (TH1F*) hlist_ua107_cut2->At(list_idx) ; fh07_02_2->SetMarkerColor(3) ; fh07_02_2->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_2->Draw("SAME");

legend();




//__________________________________________________________________________________________
TCanvas* c3 = new TCanvas("c3","Phi distribution of jets");
c3->cd(); c3->SetLogy();
list_idx = 2 ;

fh04_01_3  = (TH1F*) hlist_ua104->At(list_idx) ; fh04_01_3->SetMarkerColor(2) ; fh04_01_3->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_3->Draw();

// fh04_01_3->GetXaxis()->SetRangeUser(1,7);
fh04_01_3->GetXaxis()->CenterTitle(true);
fh04_01_3->GetYaxis()->CenterTitle(true);

fh04_02_3  = (TH1F*) hlist_ua104_cut2->At(list_idx) ; fh04_02_3->SetMarkerColor(51) ; fh04_02_3->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_3->Draw("SAME");

fh07_01_3  = (TH1F*) hlist_ua107->At(list_idx) ; fh07_01_3->SetMarkerColor(4) ; fh07_01_3->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_3->Draw("SAME");

fh07_02_3  = (TH1F*) hlist_ua107_cut2->At(list_idx) ; fh07_02_3->SetMarkerColor(3) ; fh07_02_3->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_3->Draw("SAME");

legend();



//__________________________________________________________________________________________
TCanvas *c4 = new TCanvas("c4","Multiplicity of jets // 1 unit of multiplicity /bin");
c4->cd(); c4->SetLogy();
list_idx = 3;

fh04_01_4  = (TH1F*) hlist_ua104->At(list_idx) ; fh04_01_4->SetMarkerColor(2) ; fh04_01_4->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_4->Draw();

// fh04_01_4->GetXaxis()->SetRangeUser(1,7);
fh04_01_4->GetXaxis()->CenterTitle(true);
fh04_01_4->GetYaxis()->CenterTitle(true);

fh04_02_4  = (TH1F*) hlist_ua104_cut2->At(list_idx) ; fh04_02_4->SetMarkerColor(51) ; fh04_02_4->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_4->Draw("SAME");

fh07_01_4  = (TH1F*) hlist_ua107->At(list_idx) ; fh07_01_4->SetMarkerColor(4) ; fh07_01_4->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_4->Draw("SAME");

fh07_02_4  = (TH1F*) hlist_ua107_cut2->At(list_idx) ; fh07_02_4->SetMarkerColor(3) ; fh07_02_4->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_4->Draw("SAME");

legend();



//__________________________________________________________________________________________
TCanvas *c6 = new TCanvas("c6","Jet1 Charged Multiplicity Distribution (Fig 5)");
c6->cd(); c6->SetLogy();
list_idx = 5;

fh04_01_6  = (TH1F*) hlist_ua104->At(list_idx) ; fh04_01_6->SetMarkerColor(2) ; fh04_01_6->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_6->Draw();

// fh04_01_6->GetXaxis()->SetRangeUser(1,7);
fh04_01_6->GetXaxis()->CenterTitle(true);
fh04_01_6->GetYaxis()->CenterTitle(true);

fh04_02_6  = (TH1F*) hlist_ua104_cut2->At(list_idx) ; fh04_02_6->SetMarkerColor(51) ; fh04_02_6->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_6->Draw("SAME");

fh07_01_6  = (TH1F*) hlist_ua107->At(list_idx) ; fh07_01_6->SetMarkerColor(4) ; fh07_01_6->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_6->Draw("SAME");

fh07_02_6  = (TH1F*) hlist_ua107_cut2->At(list_idx) ; fh07_02_6->SetMarkerColor(3) ; fh07_02_6->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_6->Draw("SAME");

legend();




//__________________________________________________________________________________________
TCanvas *c7 = new TCanvas("c7","N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)");
c7->cd(); c7->SetLogy();
list_idx = 6;

fh04_01_7  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_7->SetMarkerColor(2) ; fh04_01_7->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_7->Draw();

// fh04_01_7->GetXaxis()->SetRangeUser(1,7);
fh04_01_7->GetXaxis()->CenterTitle(true);
fh04_01_7->GetYaxis()->CenterTitle(true);

fh04_02_7  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_7->SetMarkerColor(51) ; fh04_02_7->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_7->Draw("SAME");

fh07_01_7  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_7->SetMarkerColor(4) ; fh07_01_7->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_7->Draw("SAME");

fh07_02_7  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_7->SetMarkerColor(3) ; fh07_02_7->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_7->Draw("SAME");

legend();


//__________________________________________________________________________________________
TCanvas *c8 = new TCanvas("c8","Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)");
c8->cd(); c8->SetLogy();
list_idx = 7;

fh04_01_8  = (TH1F*) hlist_ua104->At(list_idx) ; fh04_01_8->SetMarkerColor(2) ; fh04_01_8->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_8->Draw();

// fh04_01_8->GetXaxis()->SetRangeUser(1,7);
fh04_01_8->GetXaxis()->CenterTitle(true);
fh04_01_8->GetYaxis()->CenterTitle(true);

fh04_02_8  = (TH1F*) hlist_ua104_cut2->At(list_idx) ; fh04_02_8->SetMarkerColor(51) ; fh04_02_8->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_8->Draw("SAME");

fh07_01_8  = (TH1F*) hlist_ua107->At(list_idx) ; fh07_01_8->SetMarkerColor(4) ; fh07_01_8->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_8->Draw("SAME");

fh07_02_8  = (TH1F*) hlist_ua107_cut2->At(list_idx) ; fh07_02_8->SetMarkerColor(3) ; fh07_02_8->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_8->Draw("SAME");

legend();


//__________________________________________________________________________________________
TCanvas *c9 = new TCanvas("c9","N_{chg} vs the Azimuthal Angle from Charged Jet1 (Fig 15,17,19)");
c9->cd(); c9->SetLogy();
list_idx = 8;

fh04_01_9  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_9->SetMarkerColor(2) ; fh04_01_9->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_9->Draw();

// fh04_01_9->GetXaxis()->SetRangeUser(1,7);
fh04_01_9->GetXaxis()->CenterTitle(true);
fh04_01_9->GetYaxis()->CenterTitle(true);

fh04_02_9  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_9->SetMarkerColor(51) ; fh04_02_9->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_9->Draw("SAME");

fh07_01_9  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_9->SetMarkerColor(4) ; fh07_01_9->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_9->Draw("SAME");

fh07_02_9  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_9->SetMarkerColor(3) ; fh07_02_9->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_9->Draw("SAME");

legend();





//__________________________________________________________________________________________
TCanvas *c10 = new TCanvas("c10","P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)");
c10->cd(); c10->SetLogy();
list_idx = 9;

fh04_01_10  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_10->SetMarkerColor(2) ; fh04_01_10->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_10->Draw();

// fh04_01_10->GetXaxis()->SetRangeUser(1,7);
fh04_01_10->GetXaxis()->CenterTitle(true);
fh04_01_10->GetYaxis()->CenterTitle(true);

fh04_02_10  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_10->SetMarkerColor(51) ; fh04_02_10->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_10->Draw("SAME");

fh07_01_10  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_10->SetMarkerColor(4) ; fh07_01_10->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_10->Draw("SAME");

fh07_02_10  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_10->SetMarkerColor(3) ; fh07_02_10->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_10->Draw("SAME");

legend();


//__________________________________________________________________________________________
TCanvas *c20 = new TCanvas("c20","Distribution of R in leading jet");
c20->cd(); c20->SetLogy();
list_idx = 10;

fh04_01_20  = (TH1F*) hlist_ua104->At(list_idx) ; fh04_01_20->SetMarkerColor(2) ; fh04_01_20->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_20->Draw();

// fh04_01_20->GetXaxis()->SetRangeUser(1,7);
fh04_01_20->GetXaxis()->CenterTitle(true);
fh04_01_20->GetYaxis()->CenterTitle(true);

fh04_02_20  = (TH1F*) hlist_ua104_cut2->At(list_idx) ; fh04_02_20->SetMarkerColor(51) ; fh04_02_20->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_20->Draw("SAME");

fh07_01_20  = (TH1F*) hlist_ua107->At(list_idx) ; fh07_01_20->SetMarkerColor(4) ; fh07_01_20->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_20->Draw("SAME");

fh07_02_20  = (TH1F*) hlist_ua107_cut2->At(list_idx) ; fh07_02_20->SetMarkerColor(3) ; fh07_02_20->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_20->Draw("SAME");

legend();



//__________________________________________________________________________________________
TCanvas *c21 = new TCanvas("c21","N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)");
c21->cd(); c21->SetLogy();
list_idx = 11;

fh04_01_21  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_21->SetMarkerColor(2) ; fh04_01_21->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_21->Draw();

// fh04_01_21->GetXaxis()->SetRangeUser(1,7);
fh04_01_21->GetXaxis()->CenterTitle(true);
fh04_01_21->GetYaxis()->CenterTitle(true);

fh04_02_21  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_21->SetMarkerColor(51) ; fh04_02_21->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_21->Draw("SAME");

fh07_01_21  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_21->SetMarkerColor(4) ; fh07_01_21->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_21->Draw("SAME");

fh07_02_21  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_21->SetMarkerColor(3) ; fh07_02_21->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_21->Draw("SAME");

legend();


/*
//__________________________________________________________________________________________
TCanvas *c21tta = new TCanvas("c21tta","N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) - 3 sections");
c21tta->cd(); c21tta->SetLogy();

fH21Toward = (TProfile*) hlist_ua104->At(12) ; fH21Toward->SetMarkerColor(2) ;fH21Toward->SetMarkerStyle(26); fH21Toward->Draw();
fH21Toward_1 = (TProfile*) hlist_ua107->At(12) ; fH21Toward_1->SetMarkerColor(51);fH21Toward_1->SetMarkerStyle(26); fH21Toward_1->Draw("SAME");

fH21Transverse = (TProfile*) hlist_ua104->At(13) ; fH21Transverse->SetMarkerColor(2) ; fH21Transverse->SetMarkerStyle(24); fH21Transverse->Draw("SAME");
fH21Transverse_1 = (TProfile*) hlist_ua107->At(13) ; fH21Transverse_1->SetMarkerColor(51); fH21Transverse_1->SetMarkerStyle(24); fH21Transverse_1->Draw("SAME");

fH21Away = (TProfile*) hlist_ua104->At(14) ; fH21Away->SetMarkerColor(2) ; fH21Away->SetMarkerStyle(32); fH21Away->Draw("SAME");
fH21Away_1 = (TProfile*) hlist_ua107->At(14) ; fH21Away_1->SetMarkerColor(51); fH21Away_1->SetMarkerStyle(32); fH21Away_1->Draw("SAME");

fH21Toward->GetXaxis()->CenterTitle(true);
fH21Toward->GetYaxis()->CenterTitle(true);
*/



//__________________________________________________________________________________________
TCanvas *c22 = new TCanvas("c22","PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)");
c22->cd(); c22->SetLogy();
list_idx = 15;

fh04_01_22  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_22->SetMarkerColor(2) ; fh04_01_22->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_01_22->Draw();

// fh04_01_22->GetXaxis()->SetRangeUser(1,7);
fh04_01_22->GetXaxis()->CenterTitle(true);
fh04_01_22->GetYaxis()->CenterTitle(true);

fh04_02_22  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_22->SetMarkerColor(51) ; fh04_02_22->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_22->Draw("SAME");

fh07_01_22  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_22->SetMarkerColor(4) ; fh07_01_22->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_22->Draw("SAME");

fh07_02_22  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_22->SetMarkerColor(3) ; fh07_02_22->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_22->Draw("SAME");

legend();


/*
//__________________________________________________________________________________________
TCanvas *c22tta = new TCanvas("c22tta","PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) - 3 sections"); c22tta->cd(); c22tta->SetLogy();

fH22Toward = (TProfile*) hlist_ua104->At(16) ; fH22Toward->SetMarkerColor(2) ;fH22Toward->SetMarkerStyle(26); fH22Toward->Draw();
fH22Toward_1 = (TProfile*) hlist_ua107->At(16) ; fH22Toward_1->SetMarkerColor(51);fH22Toward_1->SetMarkerStyle(26); fH22Toward_1->Draw("SAME");

fH22Transverse = (TProfile*) hlist_ua104->At(17) ; fH22Transverse->SetMarkerColor(2) ; fH22Transverse->SetMarkerStyle(24); fH22Transverse->Draw("SAME");
fH22Transverse_1 = (TProfile*) hlist_ua107->At(17) ; fH22Transverse_1->SetMarkerColor(51); fH22Transverse_1->SetMarkerStyle(24); fH22Transverse_1->Draw("SAME");

fH22Away = (TProfile*) hlist_ua104->At(18) ; fH22Away->SetMarkerColor(2) ; fH22Away->SetMarkerStyle(32); fH22Away->Draw("SAME");
fH22Away_1 = (TProfile*) hlist_ua107->At(18) ; fH22Away_1->SetMarkerColor(51); fH22Away_1->SetMarkerStyle(32); fH22Away_1->Draw("SAME");

fH22Toward->GetXaxis()->CenterTitle(true);
fH22Toward->GetYaxis()->CenterTitle(true);
*/


/*
//__________________________________________________________________________________________
TCanvas *c23tta = new TCanvas("c23tta","Pt Distribution of charged particles - 3 sections"); c23tta->cd(); c23tta->SetLogy();

fH23Toward = (TH1F*) hlist_ua104->At(20) ; fH23Toward->SetMarkerColor(2) ;fH23Toward->SetMarkerStyle(26); fH23Toward->Draw();
fH23Toward_1 = (TH1F*) hlist_ua107->At(20) ; fH23Toward_1->SetMarkerColor(51);fH23Toward_1->SetMarkerStyle(26); fH23Toward_1->Draw("SAME");

fH23Transverse = (TH1F*) hlist_ua104->At(21) ; fH23Transverse->SetMarkerColor(2) ; fH23Transverse->SetMarkerStyle(24); fH23Transverse->Draw("SAME");
fH23Transverse_1 = (TH1F*) hlist_ua107->At(21) ; fH23Transverse_1->SetMarkerColor(51); fH23Transverse_1->SetMarkerStyle(24); fH23Transverse_1->Draw("SAME");

fH23Away = (TH1F*) hlist_ua104->At(22) ; fH23Away->SetMarkerColor(2) ; fH23Away->SetMarkerStyle(32); fH23Away->Draw("SAME");
fH23Away_1 = (TH1F*) hlist_ua107->At(22) ; fH23Away_1->SetMarkerColor(51); fH23Away_1->SetMarkerStyle(32); fH23Away_1->Draw("SAME");


fH23Toward->GetXaxis()->CenterTitle(true);
fH23Toward->GetYaxis()->CenterTitle(true);
*/


//__________________________________________________________________________________________
TCanvas *c24 = new TCanvas("c24","Jet1 Size vs P_{T}(charged jet1) - 80% of particles");
c24->cd();
list_idx = 24;

fh04_01_24  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_24->SetMarkerColor(2) ; fh04_01_24->SetMarkerSize(0.7);
fh04_01_24->SetName("Jet1 Size vs P_{T}(charged jet1) - 80% of particles");
// fH5->Scale(1./accepted1);
fh04_01_24->Draw();

fh04_01_24->GetYaxis()->SetRangeUser(0,0.5);
fh04_01_24->GetXaxis()->SetRangeUser(0,120);
fh04_01_24->GetXaxis()->CenterTitle(true);
fh04_01_24->GetYaxis()->CenterTitle(true);

fh04_02_24  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_24->SetMarkerColor(51) ; fh04_02_24->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_24->Draw("SAME");

fh07_01_24  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_24->SetMarkerColor(4) ; fh07_01_24->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_24->Draw("SAME");

fh07_02_24  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_24->SetMarkerColor(3) ; fh07_02_24->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_24->Draw("SAME");

legend();



//__________________________________________________________________________________________
TCanvas *c25 = new TCanvas("c25","Jet1 Size vs P_{T}(charged jet1) - 80% of p_{T}");
c25->cd();
list_idx = 25;

fh04_01_25  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_25->SetMarkerColor(2) ; fh04_01_25->SetMarkerSize(0.7);
fh04_01_25->SetName("Jet1 Size vs P_{T}(charged jet1) - 80% of p_{T}");
// fH5->Scale(1./accepted1);
fh04_01_25->Draw();

fh04_01_25->GetYaxis()->SetRangeUser(0,0.5);
fh04_01_25->GetXaxis()->SetRangeUser(0,120);
fh04_01_25->GetXaxis()->CenterTitle(true);
fh04_01_25->GetYaxis()->CenterTitle(true);

fh04_02_25  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_25->SetMarkerColor(51) ; fh04_02_25->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_25->Draw("SAME");

fh07_01_25  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_25->SetMarkerColor(4) ; fh07_01_25->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_25->Draw("SAME");

fh07_02_25  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_25->SetMarkerColor(3) ; fh07_02_25->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_25->Draw("SAME");

legend();




//__________________________________________________________________________________________
TCanvas *c26 = new TCanvas("c26","N_{chg} vs the Distance R from Charged Jet1 - 80% of particles");
c26->cd();
list_idx = 26;

fh04_01_26  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_26->SetMarkerColor(2) ; fh04_01_26->SetMarkerSize(0.7);
fh04_01_26->SetName("N_{chg} vs the Distance R from Charged Jet1 - 80% of particles");
// fH5->Scale(1./accepted1);
fh04_01_26->Draw();

fh04_01_26->GetYaxis()->SetRangeUser(0,10);
fh04_01_26->GetXaxis()->CenterTitle(true);
fh04_01_26->GetYaxis()->CenterTitle(true);

fh04_02_26  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_26->SetMarkerColor(51) ; fh04_02_26->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_26->Draw("SAME");

fh07_01_26  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_26->SetMarkerColor(4) ; fh07_01_26->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_26->Draw("SAME");

fh07_02_26  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_26->SetMarkerColor(3) ; fh07_02_26->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_26->Draw("SAME");

legend();




//__________________________________________________________________________________________
TCanvas *c27 = new TCanvas("c27","N_{chg} vs the Distance R from Charged Jet1 - 80% of p_{T}");
c27->cd();
list_idx = 27;

fh04_01_27  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_27->SetMarkerColor(2) ; fh04_01_27->SetMarkerSize(0.7);
fh04_01_27->SetName("N_{chg} vs the Distance R from Charged Jet1 - 80% of p_{T}");
// fH5->Scale(1./accepted1);
fh04_01_27->Draw();

fh04_01_27->GetYaxis()->SetRangeUser(0,10);
fh04_01_27->GetXaxis()->CenterTitle(true);
fh04_01_27->GetYaxis()->CenterTitle(true);

fh04_02_27  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_27->SetMarkerColor(51) ; fh04_02_27->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_27->Draw("SAME");

fh07_01_27  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_27->SetMarkerColor(4) ; fh07_01_27->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_27->Draw("SAME");

fh07_02_27  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_27->SetMarkerColor(3) ; fh07_02_27->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_27->Draw("SAME");

legend();


//__________________________________________________________________________________________
TCanvas *c28 = new TCanvas("c28","PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles (Fig 9a)");
c28->cd();
list_idx = 28;

fh04_01_28  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_28->SetMarkerColor(2) ; fh04_01_28->SetMarkerSize(0.7);
fh04_01_28->SetName("PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles (Fig 9a)");
// fH5->Scale(1./accepted1);
fh04_01_28->Draw();

fh04_01_28->GetYaxis()->SetRangeUser(0,10);
fh04_01_28->GetXaxis()->CenterTitle(true);
fh04_01_28->GetYaxis()->CenterTitle(true);

fh04_02_28  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_28->SetMarkerColor(51) ; fh04_02_28->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_28->Draw("SAME");

fh07_01_28  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_28->SetMarkerColor(4) ; fh07_01_28->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_28->Draw("SAME");

fh07_02_28  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_28->SetMarkerColor(3) ; fh07_02_28->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_28->Draw("SAME");

legend();



//__________________________________________________________________________________________
TCanvas *c29 = new TCanvas("c29","PT_{sum} vs the Distance R from Charged Jet1 - 80% of p_{T} (Fig 9b)");
c29->cd();
list_idx = 29;

fh04_01_29  = (TProfile*) hlist_ua104->At(list_idx) ; fh04_01_29->SetMarkerColor(2) ; fh04_01_29->SetMarkerSize(0.7);
fh04_01_29->SetName("PT_{sum} vs the Distance R from Charged Jet1 - 80% of p_{T} (Fig 9b)");
// fH5->Scale(1./accepted1);
fh04_01_29->Draw();

fh04_01_29->GetYaxis()->SetRangeUser(0,10);
fh04_01_29->GetXaxis()->CenterTitle(true);
fh04_01_29->GetYaxis()->CenterTitle(true);

fh04_02_29  = (TProfile*) hlist_ua104_cut2->At(list_idx) ; fh04_02_29->SetMarkerColor(51) ; fh04_02_29->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh04_02_29->Draw("SAME");

fh07_01_29  = (TProfile*) hlist_ua107->At(list_idx) ; fh07_01_29->SetMarkerColor(4) ; fh07_01_29->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_01_29->Draw("SAME");

fh07_02_29  = (TProfile*) hlist_ua107_cut2->At(list_idx) ; fh07_02_29->SetMarkerColor(3) ; fh07_02_29->SetMarkerSize(0.7);
// fH5->Scale(1./accepted1);
fh07_02_29->Draw("SAME");

legend();

}




void myOptions(Int_t lStat=0)
{
  // Set gStyle
  int font = 42;
  // From plain
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(10);
  gStyle->SetCanvasColor(10);
  gStyle->SetTitleFillColor(10);
  gStyle->SetTitleBorderSize(1);
  gStyle->SetStatColor(10);
  gStyle->SetStatBorderSize(1);
  gStyle->SetLegendBorderSize(1);
  gStyle->SetOptTitle(1);

  //
  gStyle->SetDrawBorder(0);
  gStyle->SetTextFont(font);
  gStyle->SetStatFont(font);
  gStyle->SetStatFontSize(0.05);
  gStyle->SetStatX(0.97);
  gStyle->SetStatY(0.98);
  gStyle->SetStatH(0.03);
  gStyle->SetStatW(0.3);
  gStyle->SetTickLength(0.02,"y");
  gStyle->SetEndErrorSize(3);
  gStyle->SetLabelSize(0.05,"xyz");
  gStyle->SetLabelFont(font,"xyz");
  gStyle->SetLabelOffset(0.01,"xyz");
  gStyle->SetTitleFont(font,"xyz");
  gStyle->SetTitleOffset(1.0,"xyz");
  gStyle->SetTitleSize(0.06,"xyz");
  gStyle->SetMarkerSize(1);
  gStyle->SetPalette(1,0);
  if (lStat)
    {
    gStyle->SetOptTitle(1);
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(1111);
    }
  else
    {
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    }
}


void myLegendSetUp ( TLegend* currentLegend = 0, float currentTextSize=0.07)
  {
  currentLegend->SetTextFont(42);
  currentLegend->SetBorderSize(0);
  currentLegend->SetFillStyle(0);
  currentLegend->SetFillColor(0);
  currentLegend->SetMargin(0.25);
  currentLegend->SetTextSize(currentTextSize);
  currentLegend->SetEntrySeparation(0.5);
  return;
  }

void myPadSetUp ( TPad *currentPad, float currentLeft=0.11, float currentTop=0.04, float currentRight=0.04, float currentBottom=0.15)
  {
  currentPad->SetLeftMargin(currentLeft);
  currentPad->SetTopMargin(currentTop);
  currentPad->SetRightMargin(currentRight);
  currentPad->SetBottomMargin(currentBottom);
  return;
  }


void legend ()
  {

  TString leg_title = Form("LHC period LHC10h (Pb-Pb) - 3500 ZGeV, + + (with Pass0)");

  TLegend *leg = new TLegend(0.2508426,0.8059182,0.9002499,0.9009111,NULL,"brNDC");
  leg->SetHeader(leg_title.Data());
  leg->SetTextAlign(22);
  leg->SetTextSize(0.02655717);

  leg->SetBorderSize(1);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);

  TLegendEntry* entry = NULL;

  entry = leg->AddEntry("NULL","UA1 R = 0.4 ; p_{T} >= 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(20);
  entry->SetMarkerSize(0.7);

  entry = leg->AddEntry("NULL","UA1 R = 0.4 ; p_{T} >= 2 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(20);
  entry->SetMarkerSize(0.7);

  entry = leg->AddEntry("NULL","UA1 R = 0.7 ; p_{T} >= 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(4);
  entry->SetMarkerStyle(20);
  entry->SetMarkerSize(0.7);

  entry = leg->AddEntry("NULL","UA1 R = 0.7 ; p_{T} >= 2 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(3);
  entry->SetMarkerStyle(20);
  entry->SetMarkerSize(0.7);



  leg->Draw();

  }

void makehistos()
{

// lhc10h

// Histograms
TH1F*       fh04_01_1; //  Pt distribution of jets
TH1F*       fh04_01_2; //  Eta distribution of jets
TH1F*       fh04_01_3; //  Phi distribution of jets
TH1F*       fh04_01_4; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fh04_01_5; //  Distribution of jets in events
TH1F*       fh04_01_6; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fh04_01_6->GetEntries()) )
TProfile*   fh04_01_7; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fh04_01_8; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fh04_01_9; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fh04_01_10; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fh04_01_20; //  Distribution of R in leading jet

TProfile*  fh04_01_21;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fh04_01_21Toward;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fh04_01_21Transverse; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fh04_01_21Away;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fh04_01_22;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fh04_01_22Toward;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fh04_01_22Transverse; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fh04_01_22Away;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fh04_01_23;           //  TOTAL Pt Distribution of charged particles
TH1F*      fh04_01_23Toward;     //  'Toward' Pt Distribution of charged particles
TH1F*      fh04_01_23Transverse; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fh04_01_23Away;       //  'Away' Pt Distribution of charged particles

TProfile*  fh04_01_24;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fh04_01_25;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fh04_01_26;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fh04_01_27;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fh04_01_28;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fh04_01_29;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)


// Histograms
TH1F*       fh04_02_1; //  Pt distribution of jets
TH1F*       fh04_02_2; //  Eta distribution of jets
TH1F*       fh04_02_3; //  Phi distribution of jets
TH1F*       fh04_02_4; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fh04_02_5; //  Distribution of jets in events
TH1F*       fh04_02_6; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fh04_02_6->GetEntries()) )
TProfile*   fh04_02_7; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fh04_02_8; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fh04_02_9; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fh04_02_10; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fh04_02_20; //  Distribution of R in leading jet

TProfile*  fh04_02_21;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fh04_02_21Toward;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fh04_02_21Transverse; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fh04_02_21Away;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fh04_02_22;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fh04_02_22Toward;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fh04_02_22Transverse; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fh04_02_22Away;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fh04_02_23;           //  TOTAL Pt Distribution of charged particles
TH1F*      fh04_02_23Toward;     //  'Toward' Pt Distribution of charged particles
TH1F*      fh04_02_23Transverse; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fh04_02_23Away;       //  'Away' Pt Distribution of charged particles

TProfile*  fh04_02_24;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fh04_02_25;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fh04_02_26;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fh04_02_27;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fh04_02_28;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fh04_02_29;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)


// Histograms
TH1F*       fh07_01_1; //  Pt distribution of jets
TH1F*       fh07_01_2; //  Eta distribution of jets
TH1F*       fh07_01_3; //  Phi distribution of jets
TH1F*       fh07_01_4; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fh07_01_5; //  Distribution of jets in events
TH1F*       fh07_01_6; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fh07_01_6->GetEntries()) )
TProfile*   fh07_01_7; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fh07_01_8; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fh07_01_9; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fh07_01_10; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fh07_01_20; //  Distribution of R in leading jet

TProfile*  fh07_01_21;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fh07_01_21Toward;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fh07_01_21Transverse; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fh07_01_21Away;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fh07_01_22;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fh07_01_22Toward;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fh07_01_22Transverse; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fh07_01_22Away;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fh07_01_23;           //  TOTAL Pt Distribution of charged particles
TH1F*      fh07_01_23Toward;     //  'Toward' Pt Distribution of charged particles
TH1F*      fh07_01_23Transverse; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fh07_01_23Away;       //  'Away' Pt Distribution of charged particles

TProfile*  fh07_01_24;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fh07_01_25;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fh07_01_26;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fh07_01_27;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fh07_01_28;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fh07_01_29;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)



// Histograms
TH1F*       fh07_02_1; //  Pt distribution of jets
TH1F*       fh07_02_2; //  Eta distribution of jets
TH1F*       fh07_02_3; //  Phi distribution of jets
TH1F*       fh07_02_4; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fh07_02_5; //  Distribution of jets in events
TH1F*       fh07_02_6; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fh07_02_6->GetEntries()) )
TProfile*   fh07_02_7; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fh07_02_8; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fh07_02_9; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fh07_02_10; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fh07_02_20; //  Distribution of R in leading jet

TProfile*  fh07_02_21;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fh07_02_21Toward;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fh07_02_21Transverse; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fh07_02_21Away;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fh07_02_22;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fh07_02_22Toward;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fh07_02_22Transverse; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fh07_02_22Away;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fh07_02_23;           //  TOTAL Pt Distribution of charged particles
TH1F*      fh07_02_23Toward;     //  'Toward' Pt Distribution of charged particles
TH1F*      fh07_02_23Transverse; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fh07_02_23Away;       //  'Away' Pt Distribution of charged particles

TProfile*  fh07_02_24;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fh07_02_25;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fh07_02_26;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fh07_02_27;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fh07_02_28;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fh07_02_29;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)















}









