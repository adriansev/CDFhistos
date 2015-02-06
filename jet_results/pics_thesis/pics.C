
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
gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libSTEERBase.so");
gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libESD.so");
gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libAOD.so");
gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libOADB.so");
gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libANALYSIS.so");
gSystem->Load("$ALICE_ROOT/lib/tgt_linuxx8664gcc/libANALYSISalice.so");
gROOT->ProcessLine(".include $ALICE_ROOT/include");

myOptions();
gROOT->ForceStyle();

TFile *f1 = new TFile("lhc11a.root");
TList* hlist_ua104 = (TList*)f1->Get("lhc11a.root:CDFhistos_aod_ua104_b0_filter00032_cut01000/CDFhistos_aod_ua104_b0_filter00032_cut01000_j1t0_j1pt0");
TList* hlist_ua107 = (TList*)f1->Get("lhc11a.root:CDFhistos_aod_ua107_b0_filter00032_cut01000/CDFhistos_aod_ua107_b0_filter00032_cut01000_j1t0_j1pt0");


TFile *f2 = new TFile("lhc11b10a.root");
TList* hlistmc_ua104 = (TList*)f2->Get("lhc11b10a.root:CDFhistos_aod_ua104_b0_filter00032_cut01000/CDFhistos_aod_ua104_b0_filter00032_cut01000_j1t0_j1pt0");
TList* hlistmc_ua107 = (TList*)f2->Get("lhc11b10a.root:CDFhistos_aod_ua107_b0_filter00032_cut01000/CDFhistos_aod_ua107_b0_filter00032_cut01000_j1t0_j1pt0");

// TFile *f4 = new TFile("lhc10e.root");
// TList* hlist7mc_ua104 = (TList*)f4->Get("lhc10e.root:CDFhistos_aod_ua104_b0_filter00032_cut01000/CDFhistos_aod_ua104_b0_filter00032_cut01000_j1t0_j1pt0");
// TList* hlist7mc_ua107 = (TList*)f4->Get("lhc10e.root:CDFhistos_aod_ua107_b0_filter00032_cut01000/CDFhistos_aod_ua107_b0_filter00032_cut01000_j1t0_j1pt0");

TList* mgrstat1 = (TList*)f1->Get("MgrStat");
AliAnalysisStatistics* stats1 = (AliAnalysisStatistics*) mgrstat1->At(0);
Double_t accepted1  = stats1->GetNaccepted();

TList* mgrstat2 = (TList*)f2->Get("MgrStat");
AliAnalysisStatistics* stats2 = (AliAnalysisStatistics*) mgrstat2->At(0);
Double_t accepted2  = stats2->GetNaccepted();

cout.precision(10);
cout << "accepted1 : " << accepted1 << endl;
cout << "accepted2 : " << accepted2 << endl;




// TList* mgrstat4 = (TList*)f4->Get("MgrStat");
// AliAnalysisStatistics* stats4 = (AliAnalysisStatistics*) mgrstat4->At(0);
// Double_t accepted4  = stats4->GetNaccepted();


makehistos();



// fH1mc7 = (TH1F*) hlist7mc_ua104->At(0) ; fH1mc7->SetMarkerColor(3); fH1mc7->Scale(1./accepted4); fH1mc7->Draw("SAME");
// fH1mc7_1 = (TH1F*) hlist7mc_ua107->At(0) ; fH1mc7_1->SetMarkerColor(3); fH1mc7_1->Scale(1./accepted4); fH1mc7_1->Draw("SAME");



//__________________________________________________________________________________________
TCanvas *c5 = new TCanvas("c5","Distribution of jets in events");
c5->Divide(2,1);
c5_1->cd();
c5_1->SetLogy();

fH5 = (TH1F*) hlist_ua104->At(4) ; fH5->SetMarkerColor(2) ;fH5->SetMarkerSize(1.0);
fH5->Scale(1./accepted1);
fH5->Draw();
fH5->GetXaxis()->SetRangeUser(1,5);
fH5->GetXaxis()->CenterTitle(true);
fH5->GetYaxis()->CenterTitle(true);

fH5mc = (TH1F*) hlistmc_ua104->At(4) ; fH5mc->SetMarkerColor(51);fH5mc->SetMarkerSize(1.0);
fH5mc->Scale(1./accepted2);
fH5mc->Draw("SAME");

legend(4);


c5_2->cd();
c5_2->SetLogy();

fH5_1 = (TH1F*) hlist_ua107->At(4) ; fH5_1->SetMarkerColor(2) ;fH5_1->SetMarkerSize(1.0);
fH5_1->Scale(1./accepted1);
fH5_1->Draw();
fH5_1->GetXaxis()->SetRangeUser(1,5);
fH5_1->GetXaxis()->CenterTitle(true);
fH5_1->GetYaxis()->CenterTitle(true);

fH5mc_1 = (TH1F*) hlistmc_ua107->At(4) ; fH5mc_1->SetMarkerColor(51);fH5mc_1->SetMarkerSize(1.0);
fH5mc_1->Scale(1./accepted2);
fH5mc_1->Draw("SAME");

legend(7);

Double_t jetev    = fH5->GetEntries();
Double_t jetev_mc = fH5_1->GetEntries();



//__________________________________________________________________________________________
TCanvas *c1 = new TCanvas("c1","Pt distribution of jets");
c1->Divide(2,1);
c1_1->cd();
c1_1->SetLogy();

fH1 = (TH1F*) hlist_ua104->At(0) ; fH1->SetMarkerColor(2) ; fH1->SetMarkerSize(1.0);
fH1->Scale(1./jetev);
fH1->Draw();
fH1->GetXaxis()->CenterTitle(true);
fH1->GetXaxis()->SetRange(5,50);
fH1->GetYaxis()->CenterTitle(true);

fH1mc   = (TH1F*) hlistmc_ua104->At(0) ; fH1mc->SetMarkerColor(51); fH1mc->SetMarkerSize(1.0);
fH1mc->Scale(1./jetev_mc);
fH1mc->Draw("SAME");

legend(4);

c1_2->cd();
c1_2->SetLogy();

fH1_1   = (TH1F*) hlist_ua107->At(0) ; fH1_1->SetMarkerColor(2); fH1_1->SetMarkerSize(1.0);
fH1_1->Scale(1./jetev);
fH1_1->Draw();
fH1_1->GetXaxis()->CenterTitle(true);
fH1_1->GetXaxis()->SetRange(5,50);
fH1_1->GetYaxis()->CenterTitle(true);

fH1mc_1 = (TH1F*) hlistmc_ua107->At(0) ; fH1mc_1->SetMarkerColor(51); fH1mc_1->SetMarkerSize(1.0);
fH1mc_1->Scale(1./jetev_mc);
fH1mc_1->Draw("SAME");

legend(7);



/*
//__________________________________________________________________________________________
TCanvas *c2 = new TCanvas("c2","Eta distribution of jets");
c2->Divide(2,1);
c2_1->cd();
c2_1->SetLogy();

fH2 = (TH1F*) hlist_ua104->At(1) ; fH2->SetMarkerColor(2) ; fH2->SetMarkerSize(1.0);
fH2->Scale(1./accepted1);
fH2->Draw();
fH2->GetXaxis()->CenterTitle(true);
fH2->GetYaxis()->CenterTitle(true);

fH2mc = (TH1F*) hlistmc_ua104->At(1) ; fH2mc->SetMarkerColor(51);fH2mc->SetMarkerSize(1.0);
fH2mc->Scale(1./accepted2);
fH2mc->Draw("SAME");

legend(4);

c2_2->cd();
c2_2->SetLogy();

fH2_1 = (TH1F*) hlist_ua107->At(1) ; fH2_1->SetMarkerColor(2);fH2_1->SetMarkerSize(1.0);
fH2_1->Scale(1./accepted1);
fH2_1->Draw();
fH2_1->GetXaxis()->CenterTitle(true);
fH2_1->GetYaxis()->CenterTitle(true);

fH2mc_1 = (TH1F*) hlistmc_ua107->At(1) ; fH2mc_1->SetMarkerColor(51);fH2mc_1->SetMarkerSize(1.0);
fH2mc_1->Scale(1./accepted2);
fH2mc_1->Draw("SAME");

legend(7);
*/

/*
//__________________________________________________________________________________________
TCanvas* c3 = new TCanvas("c3","Phi distribution of jets");
c3->Divide(2,1);
c3_1->cd();
c3_1->SetLogy();

fH3 = (TH1F*) hlist_ua104->At(2) ; fH3->SetMarkerColor(2) ;fH3->SetMarkerSize(1.0);
fH3->Scale(1./accepted1);
fH3->Draw();
fH3->GetXaxis()->CenterTitle(true);
fH3->GetYaxis()->CenterTitle(true);

fH3mc = (TH1F*) hlistmc_ua104->At(2) ; fH3mc->SetMarkerColor(51);fH3mc->SetMarkerSize(1.0);
fH3mc->Scale(1./accepted2);
fH3mc->Draw("SAME");

legend(4);

c3_2->cd();
c3_2->SetLogy();

fH3_1 = (TH1F*) hlist_ua107->At(2) ; fH3_1->SetMarkerColor(2);fH3_1->SetMarkerSize(1.0);
fH3_1->Scale(1./accepted1);
fH3_1->Draw();
fH3_1->GetXaxis()->CenterTitle(true);
fH3_1->GetYaxis()->CenterTitle(true);

fH3mc_1 = (TH1F*) hlistmc_ua107->At(2) ; fH3mc_1->SetMarkerColor(51);fH3mc_1->SetMarkerSize(1.0);
fH3mc_1->Scale(1./accepted2);
fH3mc_1->Draw("SAME");

legend(7);
*/





//__________________________________________________________________________________________
TCanvas *c4 = new TCanvas("c4","Multiplicity of jets // 1 unit of multiplicity /bin");
c4->Divide(2,1);
c4_1->cd();
c4_1->SetLogy();

fH4 = (TH1F*) hlist_ua104->At(3) ; fH4->SetMarkerColor(2) ;fH4->SetMarkerSize(1.0);
fH4->Scale(1./accepted1);
fH4->Draw();
fH4->GetXaxis()->SetRange(0,20);
fH4->GetXaxis()->CenterTitle(true);
fH4->GetYaxis()->CenterTitle(true);

fH4mc = (TH1F*) hlistmc_ua104->At(3) ; fH4mc->SetMarkerColor(51);fH4mc->SetMarkerSize(1.0);
fH4mc->Scale(1./accepted2);
fH4mc->Draw("SAME");

legend(4);


c4_2->cd();
c4_2->SetLogy();

fH4_1 = (TH1F*) hlist_ua107->At(3) ; fH4_1->SetMarkerColor(2);fH4_1->SetMarkerSize(1.0);
fH4_1->Scale(1./accepted1);
fH4_1->Draw();
fH4_1->GetXaxis()->SetRange(0,20);
fH4_1->GetXaxis()->CenterTitle(true);
fH4_1->GetYaxis()->CenterTitle(true);

fH4mc_1 = (TH1F*) hlistmc_ua107->At(3) ; fH4mc_1->SetMarkerColor(51);fH4mc_1->SetMarkerSize(1.0);
fH4mc_1->Scale(1./accepted2);
fH4mc_1->Draw("SAME");

legend(7);



//__________________________________________________________________________________________
TCanvas *c6 = new TCanvas("c6","Jet1 Charged Multiplicity Distribution (Fig 5)");
c6->Divide(2,1);
c6_1->cd();
c6_1->SetLogy();

fH6 = (TH1F*) hlist_ua104->At(5) ; fH6->SetMarkerColor(2) ; fH6->SetMarkerSize(1.0);
fH6->Scale( 1./jetev );
fH6->Draw();
fH6->GetXaxis()->SetRange(0,15);
fH6->GetXaxis()->CenterTitle(true);
fH6->GetYaxis()->CenterTitle(true);

fH6mc = (TH1F*) hlistmc_ua104->At(5) ; fH6mc->SetMarkerColor(51); fH6mc->SetMarkerSize(1.0);
fH6mc->Scale( 1./jetev_mc ) ;
fH6mc->Draw("SAME");

legend(4);

c6_2->cd();
c6_2->SetLogy();

fH6_1 = (TH1F*) hlist_ua107->At(5) ; fH6_1->SetMarkerColor(2) ; fH6_1->SetMarkerSize(1.0);
fH6_1->Scale( 1./jetev );
fH6_1->Draw();
fH6_1->GetXaxis()->SetRange(0,15);
fH6_1->GetXaxis()->CenterTitle(true);
fH6_1->GetYaxis()->CenterTitle(true);

fH6mc_1 = (TH1F*) hlistmc_ua107->At(5) ; fH6mc_1->SetMarkerColor(51); fH6mc_1->SetMarkerSize(1.0);
fH6mc_1->Scale( 1./jetev_mc ) ;
fH6mc_1->Draw("SAME");

legend(7);



//__________________________________________________________________________________________
TCanvas *c7 = new TCanvas("c7","N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)");
c7->Divide(2,1);
c7_1->cd();
c7_1->SetLogy();


fH7 = (TProfile*) hlist_ua104->At(6) ; fH7->SetMarkerColor(2) ; fH7->SetMarkerSize(1.0);
fH7->Draw();
fH7->GetXaxis()->SetRange(5,50);
fH7->GetXaxis()->CenterTitle(true);
fH7->GetYaxis()->CenterTitle(true);

fH7mc = (TProfile*) hlistmc_ua104->At(6) ; fH7mc->SetMarkerColor(51); fH7mc->SetMarkerSize(1.0);
fH7mc->Draw("SAME");

legend(4);

c7_2->cd();
c7_2->SetLogy();


fH7_1 = (TProfile*) hlist_ua107->At(6) ; fH7_1->SetMarkerColor(2) ; fH7_1->SetMarkerSize(1.0);
fH7_1->Draw();
fH7_1->GetXaxis()->SetRange(5,50);
fH7_1->GetXaxis()->CenterTitle(true);
fH7_1->GetYaxis()->CenterTitle(true);

fH7mc_1 = (TProfile*) hlistmc_ua107->At(6) ; fH7mc_1->SetMarkerColor(51); fH7mc_1->SetMarkerSize(1.0);
fH7mc_1->Draw("SAME");

legend(7);





//__________________________________________________________________________________________
TCanvas *c8 = new TCanvas("c8","Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)");
c8->Divide(2,1);
c8_1->cd();
c8_1->SetLogy();

fH8 = (TH1F*) hlist_ua104->At(7) ; fH8->SetMarkerColor(2) ;fH8->SetMarkerSize(1.0);
// fH8->Scale( 1./jetev );
fH8->Draw();
fH8->GetXaxis()->SetRangeUser(0,0.98);
fH8->GetXaxis()->CenterTitle(true);
fH8->GetYaxis()->CenterTitle(true);


fH8mc = (TH1F*) hlistmc_ua104->At(7) ; fH8mc->SetMarkerColor(51);fH8mc->SetMarkerSize(1.0);
// fH8mc->Scale( 1./jetev_mc ) ;
fH8mc->Draw("SAME");

legend(4);


c8_2->cd();
c8_2->SetLogy();

fH8_1 = (TH1F*) hlist_ua107->At(7) ; fH8_1->SetMarkerColor(2) ;fH8_1->SetMarkerSize(1.0);
// fH8_1->Scale( 1./jetev );
fH8_1->Draw();
fH8_1->GetXaxis()->SetRangeUser(0,0.98);
fH8_1->GetXaxis()->CenterTitle(true);
fH8_1->GetYaxis()->CenterTitle(true);


fH8mc_1 = (TH1F*) hlistmc_ua107->At(7) ; fH8mc_1->SetMarkerColor(51);fH8mc_1->SetMarkerSize(1.0);
// fH8mc_1->Scale( 1./jetev_mc ) ;
fH8mc_1->Draw("SAME");

legend(7);



/*

//__________________________________________________________________________________________
TCanvas *c9 = new TCanvas("c9","N_{chg} vs the Azimuthal Angle from Charged Jet1 (Fig 15,17,19)");
c9->Divide(2,1);
c9_1->cd();
c9_1->SetLogy();

fH9 = (TProfile*) hlist_ua104->At(8) ; fH9->SetMarkerColor(2) ;fH9->SetMarkerSize(1.0);


fH9->Draw();
fH9->GetXaxis()->CenterTitle(true);
fH9->GetYaxis()->CenterTitle(true);


fH9mc = (TProfile*) hlistmc_ua104->At(8) ; fH9mc->SetMarkerColor(51);fH9mc->SetMarkerSize(1.0);

fH9mc->Draw("SAME");

legend(4);


c9_2->cd();
c9_2->SetLogy();

fH9_1 = (TProfile*) hlist_ua107->At(8) ; fH9_1->SetMarkerColor(2) ;fH9_1->SetMarkerSize(1.0);


fH9_1->Draw();
fH9_1->GetXaxis()->CenterTitle(true);
fH9_1->GetYaxis()->CenterTitle(true);


fH9mc_1 = (TProfile*) hlistmc_ua107->At(8) ; fH9mc_1->SetMarkerColor(51);fH9mc_1->SetMarkerSize(1.0);

fH9mc_1->Draw("SAME");

legend(7);

*/

/*
//__________________________________________________________________________________________
TCanvas *c10 = new TCanvas("c10","P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)");
c10->Divide(2,1);
c10_1->cd();
c10_1->SetLogy();

fH10 = (TProfile*) hlist_ua104->At(9) ; fH10->SetMarkerColor(2) ;fH10->SetMarkerSize(1.0);

fH10->Draw();
fH10->GetXaxis()->CenterTitle(true);
fH10->GetYaxis()->CenterTitle(true);

fH10mc = (TProfile*) hlistmc_ua104->At(9) ; fH10mc->SetMarkerColor(51); fH10mc->SetMarkerSize(1.0);

fH10mc->Draw("SAME");

legend(4);

c10_2->cd();
c10_2->SetLogy();

fH10_1 = (TProfile*) hlist_ua107->At(9) ; fH10_1->SetMarkerColor(2) ;fH10_1->SetMarkerSize(1.0);

fH10_1->Draw();
fH10_1->GetXaxis()->CenterTitle(true);
fH10_1->GetYaxis()->CenterTitle(true);

fH10mc_1 = (TProfile*) hlistmc_ua107->At(9) ; fH10mc_1->SetMarkerColor(51); fH10mc_1->SetMarkerSize(1.0);

fH10mc_1->Draw("SAME");

legend(7);
*/



//__________________________________________________________________________________________
TCanvas *c20 = new TCanvas("c20","Distribution of R in leading jet");
c20->Divide(2,1);
c20_1->cd();
c20_1->SetLogy();

fH20 = (TH1F*) hlist_ua104->At(10) ; fH20->SetMarkerColor(2) ;fH20->SetMarkerSize(1.0);
fH20->Scale( 1./jetev );
fH20->Draw();
fH20->GetXaxis()->SetRangeUser(0,0.7);
fH20->GetXaxis()->CenterTitle(true);
fH20->GetYaxis()->CenterTitle(true);

fH20mc = (TH1F*) hlistmc_ua104->At(10) ; fH20mc->SetMarkerColor(51);fH20mc->SetMarkerSize(1.0);
fH20mc->Scale( 1./jetev_mc ) ;
fH20mc->Draw("SAME");

legend(4);



c20_2->cd();
c20_2->SetLogy();

fH20_1 = (TH1F*) hlist_ua107->At(10) ; fH20_1->SetMarkerColor(2) ; fH20_1->SetMarkerSize(1.0);
fH20_1->Scale( 1./jetev );
fH20_1->Draw();
fH20_1->GetXaxis()->SetRangeUser(0,0.7);
fH20_1->GetXaxis()->CenterTitle(true);
fH20_1->GetYaxis()->CenterTitle(true);

fH20mc_1 = (TH1F*) hlistmc_ua107->At(10) ; fH20mc_1->SetMarkerColor(51); fH20mc_1->SetMarkerSize(1.0);
fH20mc_1->Scale( 1./jetev_mc ) ;
fH20mc_1->Draw("SAME");

legend(7);






//__________________________________________________________________________________________
TCanvas *c21 = new TCanvas("c21","N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)");
c21->Divide(2,1);
c21_1->cd();


fH21 = (TProfile*) hlist_ua104->At(11) ; fH21->SetMarkerColor(2) ;fH21->SetMarkerSize(1.0);
fH21->GetXaxis()->SetRangeUser(5.,15.);
fH21->GetYaxis()->SetRangeUser(10.,30.);
fH21->GetXaxis()->CenterTitle(true);
fH21->GetYaxis()->CenterTitle(true);
fH21->Draw();


fH21mc = (TProfile*) hlistmc_ua104->At(11) ; fH21mc->SetMarkerColor(51);fH21mc->SetMarkerSize(1.0);
fH21mc->Draw("SAME");

legend(4);


c21_2->cd();

fH21_1 = (TH1F*) hlist_ua107->At(11) ; fH21_1->SetMarkerColor(2) ; fH21_1->SetMarkerSize(1.0);
fH21_1->GetXaxis()->SetRangeUser(5.,15.);
fH21_1->GetYaxis()->SetRangeUser(10.,30.);
fH21_1->GetXaxis()->CenterTitle(true);
fH21_1->GetYaxis()->CenterTitle(true);
fH21_1->Draw();


fH21mc_1 = (TH1F*) hlistmc_ua107->At(11) ; fH21mc_1->SetMarkerColor(51); fH21mc_1->SetMarkerSize(1.0);
fH21mc_1->Draw("SAME");

legend(7);


/*

//__________________________________________________________________________________________
TCanvas *c21tta = new TCanvas("c21tta","N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) - 3 sections"); c21tta->cd(); c21tta->SetLogy();

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
c22->Divide(2,1);
c22_1->cd();

fH22 = (TProfile*) hlist_ua104->At(15) ; fH22->SetMarkerColor(2) ;fH22->SetMarkerSize(1.0);
fH22->GetXaxis()->SetRangeUser(5.,15.);
fH22->GetYaxis()->SetRangeUser(30.,60.);
fH22->GetXaxis()->CenterTitle(true);
fH22->GetYaxis()->CenterTitle(true);
fH22->Draw();


fH22mc = (TProfile*) hlistmc_ua104->At(15) ; fH22mc->SetMarkerColor(51);fH22mc->SetMarkerSize(1.0);
fH22mc->Draw("SAME");

legend(4);


c22_2->cd();

fH22_1 = (TH1F*) hlist_ua107->At(15) ; fH22_1->SetMarkerColor(2) ; fH22_1->SetMarkerSize(1.0);
fH22_1->GetXaxis()->SetRangeUser(5.,15.);
fH22_1->GetYaxis()->SetRangeUser(30.,60.);
fH22_1->GetXaxis()->CenterTitle(true);
fH22_1->GetYaxis()->CenterTitle(true);
fH22_1->Draw();

fH22mc_1 = (TH1F*) hlistmc_ua107->At(15) ; fH22mc_1->SetMarkerColor(51); fH22mc_1->SetMarkerSize(1.0);
fH22mc_1->Draw("SAME");

legend(7);








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





//__________________________________________________________________________________________
TCanvas *c23 = new TCanvas("c23","TOTAL Pt Distribution of charged particles");
c23->Divide(2,1);
c23_1->cd();


fH23 = (TH1F*) hlist_ua104->At(19) ; fH23->SetMarkerColor(2) ;fH23->SetMarkerSize(1.0);
fH23->Scale( 1./jetev );
fH23->Draw();
fH23->GetXaxis()->CenterTitle(true);
fH23->GetYaxis()->CenterTitle(true);

fH23mc = (TH1F*) hlistmc_ua104->At(19) ; fH23mc->SetMarkerColor(51);fH23mc->SetMarkerSize(1.0);
fH23mc->Scale( 1./jetev_mc ) ;
fH23mc->Draw("SAME");

legend(4);


c23_2->cd();


fH23_1 = (TH1F*) hlist_ua107->At(19) ; fH23_1->SetMarkerColor(2) ; fH23_1->SetMarkerSize(1.0);
fH23_1->Scale( 1./jetev );
fH23_1->Draw();
fH23_1->GetXaxis()->CenterTitle(true);
fH23_1->GetYaxis()->CenterTitle(true);

fH23mc_1 = (TH1F*) hlistmc_ua107->At(19) ; fH23mc_1->SetMarkerColor(51); fH23mc_1->SetMarkerSize(1.0);
fH23mc_1->Scale( 1./jetev_mc ) ;
fH23mc_1->Draw("SAME");

legend(7);





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

/*
//__________________________________________________________________________________________
TCanvas *c24 = new TCanvas("c24","Jet1 Size vs P_{T}(charged jet1) - 80% of particles");
c24->Divide(2,1);
c24_1->cd();


fH24 = (TProfile*) hlist_ua104->At(23) ; fH24->SetMarkerColor(2) ; fH24->SetMarkerStyle(26);
fH24->Draw();

fH24->GetXaxis()->CenterTitle(true);
fH24->GetYaxis()->CenterTitle(true);



fH24mc = (TProfile*) hlistmc_ua104->At(23) ; fH24mc->SetMarkerColor(51); fH24mc->SetMarkerStyle(26);
fH24mc->Draw("SAME");

legend(4);


c24_2->cd();


fH24_1 = (TProfile*) hlist_ua107->At(23) ; fH24_1->SetMarkerColor(2) ; fH24_1->SetMarkerStyle(26);
fH24_1->Draw();

fH24_1->GetXaxis()->CenterTitle(true);
fH24_1->GetYaxis()->CenterTitle(true);



fH24mc_1 = (TProfile*) hlistmc_ua107->At(23) ; fH24mc_1->SetMarkerColor(51); fH24mc_1->SetMarkerStyle(26);
fH24mc_1->Draw("SAME");

legend(7);

*/

/*
//__________________________________________________________________________________________
TCanvas *c25 = new TCanvas("c25","Jet1 Size vs P_{T}(charged jet1) - 80% of p_{T}");
c25->Divide(2,1);
c25_1->cd();


fH25 = (TProfile*) hlist_ua104->At(24) ; fH25->SetMarkerColor(2) ; fH25->SetMarkerStyle(26);
fH25->Draw();

fH25->GetXaxis()->CenterTitle(true);
fH25->GetYaxis()->CenterTitle(true);



fH25mc = (TProfile*) hlistmc_ua104->At(24) ; fH25mc->SetMarkerColor(51); fH25mc->SetMarkerStyle(26);
fH25mc->Draw("SAME");

legend(4);


c25_2->cd();


fH25_1 = (TProfile*) hlist_ua107->At(24) ; fH25_1->SetMarkerColor(2) ; fH25_1->SetMarkerStyle(26);
fH25_1->Draw();

fH25_1->GetXaxis()->CenterTitle(true);
fH25_1->GetYaxis()->CenterTitle(true);



fH25mc_1 = (TProfile*) hlistmc_ua107->At(24) ; fH25mc_1->SetMarkerColor(51); fH25mc_1->SetMarkerStyle(26);
fH25mc_1->Draw("SAME");

legend(7);

*/


/*
//__________________________________________________________________________________________
TCanvas *c26 = new TCanvas("c26","N_{chg} vs the Distance R from Charged Jet1 - 80% of particles");
c26->Divide(2,1);
c26_1->cd();


fH26 = (TProfile*) hlist_ua104->At(25) ; fH26->SetMarkerColor(2) ; fH26->SetMarkerStyle(32);
fH26->Draw();

fH26->GetXaxis()->CenterTitle(true);
fH26->GetYaxis()->CenterTitle(true);


fH26mc = (TProfile*) hlistmc_ua104->At(25) ; fH26mc->SetMarkerColor(51); fH26mc->SetMarkerStyle(32);
fH26mc->Draw("SAME");

legend(4);


c26_2->cd();


fH26_1 = (TProfile*) hlist_ua107->At(25) ; fH26_1->SetMarkerColor(2) ; fH26_1->SetMarkerStyle(32);
fH26_1->Draw();

fH26_1->GetXaxis()->CenterTitle(true);
fH26_1->GetYaxis()->CenterTitle(true);



fH26mc_1 = (TProfile*) hlistmc_ua107->At(25) ; fH26mc_1->SetMarkerColor(51); fH26mc_1->SetMarkerStyle(32);
fH26mc_1->Draw("SAME");

legend(7);
*/

/*
//__________________________________________________________________________________________
TCanvas *c27 = new TCanvas("c27","N_{chg} vs the Distance R from Charged Jet1 - 80% of p_{T}");
c27->Divide(2,1);
c27_1->cd();

fH27 = (TProfile*) hlist_ua104->At(26) ; fH27->SetMarkerColor(2) ; fH27->SetMarkerStyle(32);
fH27->Draw();

fH27->GetXaxis()->CenterTitle(true);
fH27->GetYaxis()->CenterTitle(true);


fH27mc = (TProfile*) hlistmc_ua104->At(26) ; fH27mc->SetMarkerColor(51); fH27mc->SetMarkerStyle(32);
fH27mc->Draw("SAME");

legend(4);


c27_2->cd();


fH27_1 = (TProfile*) hlist_ua107->At(26) ; fH27_1->SetMarkerColor(2) ; fH27_1->SetMarkerStyle(32);
fH27_1->Draw();

fH27_1->GetXaxis()->CenterTitle(true);
fH27_1->GetYaxis()->CenterTitle(true);



fH27mc_1 = (TProfile*) hlistmc_ua107->At(26) ; fH27mc_1->SetMarkerColor(51); fH27mc_1->SetMarkerStyle(32);
fH27mc_1->Draw("SAME");

legend(7);
*/







//__________________________________________________________________________________________
TCanvas *c28 = new TCanvas("c28","PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles (Fig 9a)");
c28->Divide(2,1);
c28_1->cd();

fH28 = (TProfile*) hlist_ua104->At(27) ; fH28->SetMarkerColor(2) ; fH28->SetMarkerStyle(32);
fH28->Draw();

fH28->GetXaxis()->CenterTitle(true);
fH28->GetYaxis()->CenterTitle(true);
fH28->GetYaxis()->SetRangeUser(4., 10.);
fH28->GetYaxis()->SetMoreLogLabels();
fH28->GetYaxis()->SetTitleOffset(1);



fH28mc = (TProfile*) hlistmc_ua104->At(27) ; fH28mc->SetMarkerColor(51); fH28mc->SetMarkerStyle(32);
fH28mc->Draw("SAME");

legend(4);


c28_2->cd();


fH28_1 = (TProfile*) hlist_ua107->At(27) ; fH28_1->SetMarkerColor(2) ; fH28_1->SetMarkerStyle(32);
fH28_1->Draw();

fH28_1->GetXaxis()->CenterTitle(true);
fH28_1->GetYaxis()->CenterTitle(true);
fH28_1->GetYaxis()->SetRangeUser(4., 10.);
fH28_1->GetYaxis()->SetMoreLogLabels();
fH28_1->GetYaxis()->SetTitleOffset(1);

fH28mc_1 = (TProfile*) hlistmc_ua107->At(27) ; fH28mc_1->SetMarkerColor(51); fH28mc_1->SetMarkerStyle(32);
fH28mc_1->Draw("SAME");

legend(7);







//__________________________________________________________________________________________
TCanvas *c29 = new TCanvas("c29","PT_{sum} vs the Distance R from Charged Jet1 - 80% of p_{T} (Fig 9b)");
c29->Divide(2,1);
c29_1->cd();

fH29 = (TProfile*) hlist_ua104->At(28) ; fH29->SetMarkerColor(2) ; fH29->SetMarkerStyle(32);
fH29->Draw();

fH29->GetXaxis()->CenterTitle(true);
fH29->GetYaxis()->CenterTitle(true);
fH29->GetYaxis()->SetRangeUser(4., 10.);
fH29->GetYaxis()->SetMoreLogLabels();
fH29->GetYaxis()->SetTitleOffset(1);


fH29mc = (TProfile*) hlistmc_ua104->At(28) ; fH29mc->SetMarkerColor(51); fH29mc->SetMarkerStyle(32);
fH29mc->Draw("SAME");

legend(4);


c29_2->cd();


fH29_1 = (TProfile*) hlist_ua107->At(28) ; fH29_1->SetMarkerColor(2) ; fH29_1->SetMarkerStyle(32);

fH29_1->Draw();

fH29_1->GetXaxis()->CenterTitle(true);
fH29_1->GetYaxis()->CenterTitle(true);
fH29_1->GetYaxis()->SetRangeUser(4., 10.);
fH29_1->GetYaxis()->SetMoreLogLabels();
fH29_1->GetYaxis()->SetTitleOffset(1);

fH29mc_1 = (TProfile*) hlistmc_ua107->At(28) ; fH29mc_1->SetMarkerColor(51); fH29mc_1->SetMarkerStyle(32);
fH29mc_1->Draw("SAME");

legend(7);



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


void legend (Int_t i = 4)
  {

  TString leg_title = Form("pp ; UA1 - R = 0.%i; p_{T} cut = 1 GeV", i);

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

  entry = leg->AddEntry("NULL","LHC period LHC11a - Pass3; 2.76 TeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(20);
  entry->SetMarkerSize(1.0);

  entry = leg->AddEntry("NULL","Pythia, 0.5T, LHC11a anchor runs; 2.76 TeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(20);
  entry->SetMarkerSize(1.0);

/*

  entry = leg->AddEntry("NULL","LHC period LHC10c - Pass2; 7 TeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(4);
  entry->SetMarkerStyle(20);
  entry->SetMarkerSize(1.0);

  entry = leg->AddEntry("NULL","Pythia, 0.5T, LHC10e anchor runs; 7 TeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(3);
  entry->SetMarkerStyle(20);
  entry->SetMarkerSize(1.0);
*/


  leg->Draw();

  }

void makehistos()
{

// 2.76 pp

// Histograms
TH1F*       fH1; //  Pt distribution of jets
TH1F*       fH2; //  Eta distribution of jets
TH1F*       fH3; //  Phi distribution of jets
TH1F*       fH4; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fH5; //  Distribution of jets in events
TH1F*       fH6; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fH6->GetEntries()) )
TProfile*   fH7; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fH8; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fH9; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fH10; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fH20; //  Distribution of R in leading jet

TProfile*  fH21;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fH21Toward;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fH21Transverse; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fH21Away;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fH22;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fH22Toward;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fH22Transverse; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fH22Away;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fH23;           //  TOTAL Pt Distribution of charged particles
TH1F*      fH23Toward;     //  'Toward' Pt Distribution of charged particles
TH1F*      fH23Transverse; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fH23Away;       //  'Away' Pt Distribution of charged particles

TProfile*  fH24;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fH25;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fH26;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fH27;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fH28;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fH29;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)


// 2.76 MC

// Histograms
TH1F*       fH1mc; //  Pt distribution of jets
TH1F*       fH2mc; //  Eta distribution of jets
TH1F*       fH3mc; //  Phi distribution of jets
TH1F*       fH4mc; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fH5mc; //  Distribution of jets in events
TH1F*       fH6mc; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fH6->GetEntries()) )
TProfile*   fH7mc; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fH8mc; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fH9mc; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fH10mc; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fH20mc; //  Distribution of R in leading jet

TProfile*  fH21mc;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fH21Towardmc;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fH21Transversemc; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fH21Awaymc;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fH22mc;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fH22Towardmc;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fH22Transversemc; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fH22Awaymc;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fH23mc;           //  TOTAL Pt Distribution of charged particles
TH1F*      fH23Towardmc;     //  'Toward' Pt Distribution of charged particles
TH1F*      fH23Transversemc; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fH23Awaymc;       //  'Away' Pt Distribution of charged particles

TProfile*  fH24mc;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fH25mc;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fH26mc;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fH27mc;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fH28mc;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fH29mc;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)


// 2.76 0.7

// Histograms
TH1F*       fH1_1; //  Pt distribution of jets
TH1F*       fH2_1; //  Eta distribution of jets
TH1F*       fH3_1; //  Phi distribution of jets
TH1F*       fH4_1; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fH5_1; //  Distribution of jets in events
TH1F*       fH6_1; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fH6->GetEntries()) )
TProfile*   fH7_1; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fH8_1; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fH9_1; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fH10_1; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fH20_1; //  Distribution of R in leading jet

TProfile*  fH21_1;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fH21Toward_1;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fH21Transverse_1; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fH21Away_1;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fH22_1;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fH22Toward_1;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fH22Transverse_1; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fH22Away_1;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fH23_1;           //  TOTAL Pt Distribution of charged particles
TH1F*      fH23Toward_1;     //  'Toward' Pt Distribution of charged particles
TH1F*      fH23Transverse_1; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fH23Away_1;       //  'Away' Pt Distribution of charged particles

TProfile*  fH24_1;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fH25_1;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fH26_1;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fH27_1;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fH28_1;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fH29_1;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)


// 2.76 0.7 MC

// Histograms
TH1F*       fH1mc_1; //  Pt distribution of jets
TH1F*       fH2mc_1; //  Eta distribution of jets
TH1F*       fH3mc_1; //  Phi distribution of jets
TH1F*       fH4mc_1; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fH5mc_1; //  Distribution of jets in events
TH1F*       fH6mc_1; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fH6->GetEntries()) )
TProfile*   fH7mc_1; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fH8mc_1; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fH9mc_1; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fH10mc_1; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fH20mc_1; //  Distribution of R in leading jet

TProfile*  fH21mc_1;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fH21Towardmc_1;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fH21Transversemc_1; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fH21Awaymc_1;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fH22mc_1;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fH22Towardmc_1;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fH22Transversemc_1; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fH22Awaymc_1;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fH23mc_1;           //  TOTAL Pt Distribution of charged particles
TH1F*      fH23Towardmc_1;     //  'Toward' Pt Distribution of charged particles
TH1F*      fH23Transversemc_1; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fH23Awaymc_1;       //  'Away' Pt Distribution of charged particles

TProfile*  fH24mc_1;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fH25mc_1;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fH26mc_1;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fH27mc_1;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fH28mc_1;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fH29mc_1;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)


// 7TeV exp
/*
// Histograms
TH1F*       fH1exp7; //  Pt distribution of jets
TH1F*       fH2exp7; //  Eta distribution of jets
TH1F*       fH3exp7; //  Phi distribution of jets
TH1F*       fH4exp7; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fH5exp7; //  Distribution of jets in events
TH1F*       fH6exp7; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fH6->GetEntries()) )
TProfile*   fH7exp7; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fH8exp7; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fH9exp7; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fH10exp7; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fH20exp7; //  Distribution of R in leading jet

TProfile*  fH21exp7;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fH21Towardexp7;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fH21Transverseexp7; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fH21Awayexp7;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fH22exp7;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fH22Towardexp7;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fH22Transverseexp7; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fH22Awayexp7;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fH23exp7;           //  TOTAL Pt Distribution of charged particles
TH1F*      fH23Towardexp7;     //  'Toward' Pt Distribution of charged particles
TH1F*      fH23Transverseexp7; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fH23Awayexp7;       //  'Away' Pt Distribution of charged particles

TProfile*  fH24exp7;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fH25exp7;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fH26exp7;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fH27exp7;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fH28exp7;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fH29exp7;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)


// 7TeV exp 0.7

// Histograms
TH1F*       fH1exp7_1; //  Pt distribution of jets
TH1F*       fH2exp7_1; //  Eta distribution of jets
TH1F*       fH3exp7_1; //  Phi distribution of jets
TH1F*       fH4exp7_1; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fH5exp7_1; //  Distribution of jets in events
TH1F*       fH6exp7_1; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fH6->GetEntries()) )
TProfile*   fH7exp7_1; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fH8exp7_1; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fH9exp7_1; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fH10exp7_1; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fH20exp7_1; //  Distribution of R in leading jet

TProfile*  fH21exp7_1;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fH21Towardexp7_1;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fH21Transverseexp7_1; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fH21Awayexp7_1;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fH22exp7_1;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fH22Towardexp7_1;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fH22Transverseexp7_1; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fH22Awayexp7_1;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fH23exp7_1;           //  TOTAL Pt Distribution of charged particles
TH1F*      fH23Towardexp7_1;     //  'Toward' Pt Distribution of charged particles
TH1F*      fH23Transverseexp7_1; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fH23Awayexp7_1;       //  'Away' Pt Distribution of charged particles

TProfile*  fH24exp7_1;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fH25exp7_1;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fH26exp7_1;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fH27exp7_1;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fH28exp7_1;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fH29exp7_1;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)



// 7TeV MC

// Histograms
TH1F*       fH1mc7; //  Pt distribution of jets
TH1F*       fH2mc7; //  Eta distribution of jets
TH1F*       fH3mc7; //  Phi distribution of jets
TH1F*       fH4mc7; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fH5mc7; //  Distribution of jets in events
TH1F*       fH6mc7; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fH6->GetEntries()) )
TProfile*   fH7mc7; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fH8mc7; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fH9mc7; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fH10mc7; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fH20mc7; //  Distribution of R in leading jet

TProfile*  fH21mc7;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fH21Towardmc7;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fH21Transversemc7; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fH21Awaymc7;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fH22mc7;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fH22Towardmc7;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fH22Transversemc7; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fH22Awaymc7;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fH23mc7;           //  TOTAL Pt Distribution of charged particles
TH1F*      fH23Towardmc7;     //  'Toward' Pt Distribution of charged particles
TH1F*      fH23Transversemc7; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fH23Awaymc7;       //  'Away' Pt Distribution of charged particles

TProfile*  fH24mc7;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fH25mc7;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fH26mc7;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fH27mc7;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fH28mc7;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fH29mc7;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)


// 7TeV MC 0.7

// Histograms
TH1F*       fH1mc7_1; //  Pt distribution of jets
TH1F*       fH2mc7_1; //  Eta distribution of jets
TH1F*       fH3mc7_1; //  Phi distribution of jets
TH1F*       fH4mc7_1; //  Multiplicity of jets // 1 unit of multiplicity /bin
TH1F*       fH5mc7_1; //  Distribution of jets in events
TH1F*       fH6mc7_1; //  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fH6->GetEntries()) )
TProfile*   fH7mc7_1; //  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
TH1F*       fH8mc7_1; //  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
TProfile*   fH9mc7_1; //  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
TProfile*  fH10mc7_1; //  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
TH1F*      fH20mc7_1; //  Distribution of R in leading jet

TProfile*  fH21mc7_1;           //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
TProfile*  fH21Towardmc7_1;     //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
TProfile*  fH21Transversemc7_1; //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
TProfile*  fH21Awaymc7_1;       //  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

TProfile*  fH22mc7_1;           //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)
TProfile*  fH22Towardmc7_1;     //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
TProfile*  fH22Transversemc7_1; //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
TProfile*  fH22Awaymc7_1;       //  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

TH1F*      fH23mc7_1;           //  TOTAL Pt Distribution of charged particles
TH1F*      fH23Towardmc7_1;     //  'Toward' Pt Distribution of charged particles
TH1F*      fH23Transversemc7_1; //  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
TH1F*      fH23Awaymc7_1;       //  'Away' Pt Distribution of charged particles

TProfile*  fH24mc7_1;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
TProfile*  fH25mc7_1;           //  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
TProfile*  fH26mc7_1;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
TProfile*  fH27mc7_1;           //  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
TProfile*  fH28mc7_1;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
TProfile*  fH29mc7_1;           //  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)

*/






}









