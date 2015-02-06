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

TFile *f = new TFile("lhc11a.root");

TList* hlist_ua104 = (TList*)f->Get("lhc11a.root:CDFhistos_aod_ua104_b0_filter00032_cut01000/CDFhistos_aod_ua104_b0_filter00032_cut01000_j1t0_j1pt0");
TList* hlist_ua107 = (TList*)f->Get("lhc11a.root:CDFhistos_aod_ua107_b0_filter00032_cut01000/CDFhistos_aod_ua107_b0_filter00032_cut01000_j1t0_j1pt0");


TList* mgrstat = (TList*)f->Get("MgrStat");
AliAnalysisStatistics* stats = (AliAnalysisStatistics*) mgrstat->At(0);

cout << "Ninput : " << stats->GetNinput() << endl;
cout << "Nprocessed : " << stats->GetNprocessed() << endl;
cout << "Nfailed : " << stats->GetNfailed() << endl;
cout << "Naccepted : " << stats->GetNaccepted() << endl;
cout << "OfflineMask : " << stats->GetOfflineMask() << endl;

// for ( int i = 0 ; i < mgrstat->GetEntries() ; i++ )
// {
// TObject* obj = mgrstat->At(i);
// cout << obj->ClassName() << endl;
// }




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


//__________________________________________________________________________________________
TCanvas *c1 = new TCanvas("c1","Pt distribution of jets"); c1->cd(); c1->SetLogy();

fH1 = (TH1F*) hlist_ua104->At(0) ; fH1->SetMarkerColor(2) ; fH1->Draw();
fH1->GetXaxis()->CenterTitle(true);
fH1->GetXaxis()->SetRange(1,127);
fH1->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();


fH1_1 = (TH1F*) hlist_ua107->At(0) ; fH1_1->SetMarkerColor(51); fH1_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(20);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH1","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH1_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c1->Modified(); c1->cd(); c1->SetSelected(c1);



//__________________________________________________________________________________________
TCanvas *c2 = new TCanvas("c2","Eta distribution of jets"); c2->cd(); c2->SetLogy();

fH2 = (TH1F*) hlist_ua104->At(1) ; fH2->SetMarkerColor(2) ; fH2->Draw();
fH2->GetXaxis()->CenterTitle(true);
fH2->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();


fH2_1 = (TH1F*) hlist_ua107->At(1) ; fH2_1->SetMarkerColor(51); fH2_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH2","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH2_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c2->Modified(); c2->cd(); c2->SetSelected(c2);


//__________________________________________________________________________________________
TCanvas *c3 = new TCanvas("c3","Phi distribution of jets"); c3->cd(); c3->SetLogy();

fH3 = (TH1F*) hlist_ua104->At(2) ; fH3->SetMarkerColor(2) ; fH3->Draw();
fH3->GetXaxis()->CenterTitle(true);
fH3->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();


fH3_1 = (TH1F*) hlist_ua107->At(2) ; fH3_1->SetMarkerColor(51); fH3_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH3","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH3_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c3->Modified(); c3->cd(); c3->SetSelected(c3);

//__________________________________________________________________________________________
TCanvas *c4 = new TCanvas("c4","Multiplicity of jets // 1 unit of multiplicity /bin"); c4->cd(); c4->SetLogy();

fH4 = (TH1F*) hlist_ua104->At(3) ; fH4->SetMarkerColor(2) ; fH4->Draw();
fH4->GetXaxis()->CenterTitle(true);
fH4->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH4_1 = (TH1F*) hlist_ua107->At(3) ; fH4_1->SetMarkerColor(51); fH4_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH4","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH4_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c4->Modified(); c4->cd(); c4->SetSelected(c4);


//__________________________________________________________________________________________
TCanvas *c5 = new TCanvas("c5","Distribution of jets in events"); c5->cd(); c5->SetLogy();

fH5 = (TH1F*) hlist_ua104->At(4) ; fH5->SetMarkerColor(2) ; fH5->Draw();
fH5->GetXaxis()->CenterTitle(true);
fH5->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH5_1 = (TH1F*) hlist_ua107->At(4) ; fH5_1->SetMarkerColor(51); fH5_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH5","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH5_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c5->Modified(); c5->cd(); c5->SetSelected(c5);




//__________________________________________________________________________________________
TCanvas *c6 = new TCanvas("c6","Jet1 Charged Multiplicity Distribution (Fig 5)"); c6->cd(); c6->SetLogy();

fH6 = (TH1F*) hlist_ua104->At(5) ; fH6->SetMarkerColor(2) ; fH6->Scale( 1. / stats->GetNaccepted() ); fH6->Draw();
fH6->GetXaxis()->CenterTitle(true);
fH6->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();


fH6_1 = (TH1F*) hlist_ua107->At(5) ; fH6_1->SetMarkerColor(51); fH6_1->Scale( 1. / stats->GetNaccepted() ) ; fH6_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH6","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH6_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c6->Modified(); c6->cd(); c6->SetSelected(c6);



//__________________________________________________________________________________________
TCanvas *c7 = new TCanvas("c7","N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)"); c7->cd(); c7->SetLogy();

fH7 = (TProfile*) hlist_ua104->At(6) ; fH7->SetMarkerColor(2) ; fH7->Draw();
fH7->GetXaxis()->CenterTitle(true);
fH7->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH7_1 = (TProfile*) hlist_ua107->At(6) ; fH7_1->SetMarkerColor(51); fH7_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH7","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH7_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c7->Modified(); c7->cd(); c7->SetSelected(c7);



//__________________________________________________________________________________________
TCanvas *c8 = new TCanvas("c8","Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)"); c8->cd(); c8->SetLogy();

fH8 = (TH1F*) hlist_ua104->At(7) ; fH8->SetMarkerColor(2) ; fH8->Draw();
fH8->GetXaxis()->CenterTitle(true);
fH8->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();


fH8_1 = (TH1F*) hlist_ua107->At(7) ; fH8_1->SetMarkerColor(51); fH8_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH8","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH8_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c8->Modified(); c8->cd(); c8->SetSelected(c8);




//__________________________________________________________________________________________
TCanvas *c9 = new TCanvas("c9","N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)"); c9->cd(); c9->SetLogy();

fH9 = (TProfile*) hlist_ua104->At(8) ; fH9->SetMarkerColor(2) ; fH9->Draw();
fH9->GetXaxis()->CenterTitle(true);
fH9->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();


fH9_1 = (TProfile*) hlist_ua107->At(8) ; fH9_1->SetMarkerColor(51); fH9_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH9","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH9_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c9->Modified(); c9->cd(); c9->SetSelected(c9);



//__________________________________________________________________________________________
TCanvas *c10 = new TCanvas("c10","P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)"); c10->cd(); c10->SetLogy();

fH10 = (TProfile*) hlist_ua104->At(9) ; fH10->SetMarkerColor(2) ; fH10->Draw();
fH10->GetXaxis()->CenterTitle(true);
fH10->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();


fH10_1 = (TProfile*) hlist_ua107->At(9) ; fH10_1->SetMarkerColor(51); fH10_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH10","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH10_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c10->Modified(); c10->cd(); c10->SetSelected(c10);


//__________________________________________________________________________________________
TCanvas *c20 = new TCanvas("c20","Distribution of R in leading jet"); c20->cd(); c20->SetLogy();

fH20 = (TH1F*) hlist_ua104->At(10) ; fH20->SetMarkerColor(2) ; fH20->Draw();
fH20->GetXaxis()->CenterTitle(true);
fH20->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();



fH20_1 = (TH1F*) hlist_ua107->At(10) ; fH20_1->SetMarkerColor(51); fH20_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH20","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH20_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c20->Modified(); c20->cd(); c20->SetSelected(c20);




//__________________________________________________________________________________________
TCanvas *c21 = new TCanvas("c21","N_{chg}(in the event - including jet1) vs P_{T}(charged jet1)"); c21->cd(); c21->SetLogy();

fH21 = (TProfile*) hlist_ua104->At(11) ; fH21->SetMarkerColor(2) ; fH21->Draw();
fH21->GetXaxis()->CenterTitle(true);
fH21->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();


fH21_1 = (TProfile*) hlist_ua107->At(11) ; fH21_1->SetMarkerColor(51); fH21_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH21","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH21_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c21->Modified(); c21->cd(); c21->SetSelected(c21);



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

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();


TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
  leg->SetTextFont(62);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(19);
  leg->SetFillStyle(1001);

  TLegendEntry* entry;

  entry=leg->AddEntry("fH21Toward","TOWARD : UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(26);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH21Transverse","TRANSVERSE : UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(24);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH21Away","AWAY: UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(32);
  entry->SetMarkerSize(1);


  entry=leg->AddEntry("fH21Toward_1","TOWARD: UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(26);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH21Transverse_1","TRANSVERSE: UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(24);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH21Away_1","AWAY: UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(32);
  entry->SetMarkerSize(1);

  leg->Draw();
  c21tta->Modified(); c21tta->cd(); c21tta->SetSelected(c21tta);





//__________________________________________________________________________________________
TCanvas *c22 = new TCanvas("c22","PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1)"); c22->cd(); c22->SetLogy();

fH22 = (TProfile*) hlist_ua104->At(15) ; fH22->SetMarkerColor(2) ; fH22->Draw();

fH22->GetXaxis()->CenterTitle(true);
fH22->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH22_1 = (TProfile*) hlist_ua107->At(15) ; fH22_1->SetMarkerColor(51); fH22_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH22","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH22_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c22->Modified(); c22->cd(); c22->SetSelected(c22);



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

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
  leg->SetTextFont(62);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(19);
  leg->SetFillStyle(1001);

  TLegendEntry* entry;

  entry=leg->AddEntry("fH22Toward","TOWARD : UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(26);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH22Transverse","TRANSVERSE : UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(24);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH22Away","AWAY: UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(32);
  entry->SetMarkerSize(1);


  entry=leg->AddEntry("fH22Toward_1","TOWARD: UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(26);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH22Transverse_1","TRANSVERSE: UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(24);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH22Away_1","AWAY: UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(32);
  entry->SetMarkerSize(1);

  leg->Draw();
  c22tta->Modified(); c22tta->cd(); c22tta->SetSelected(c22tta);


//__________________________________________________________________________________________
TCanvas *c23 = new TCanvas("c23","TOTAL Pt Distribution of charged particles"); c23->cd(); c23->SetLogy();

fH23 = (TH1F*) hlist_ua104->At(19) ; fH23->SetMarkerColor(2) ; fH23->Draw();
fH23->GetXaxis()->CenterTitle(true);
fH23->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH23_1 = (TH1F*) hlist_ua107->At(19) ; fH23_1->SetMarkerColor(51); fH23_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH23","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);

   entry=leg->AddEntry("fH23_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   leg->Draw();

   c23->Modified(); c23->cd(); c23->SetSelected(c23);



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

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();


TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
  leg->SetTextFont(62);
  leg->SetLineColor(1);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(19);
  leg->SetFillStyle(1001);

  TLegendEntry* entry;

  entry=leg->AddEntry("fH23Toward","TOWARD : UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(26);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH23Transverse","TRANSVERSE : UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(24);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH23Away","AWAY: UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(2);
  entry->SetMarkerStyle(32);
  entry->SetMarkerSize(1);


  entry=leg->AddEntry("fH23Toward_1","TOWARD: UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(26);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH23Transverse_1","TRANSVERSE: UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(24);
  entry->SetMarkerSize(1);

  entry=leg->AddEntry("fH23Away_1","AWAY: UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
  entry->SetFillStyle(1001);
  entry->SetLineColor(1);
  entry->SetLineStyle(1);
  entry->SetLineWidth(1);
  entry->SetMarkerColor(51);
  entry->SetMarkerStyle(32);
  entry->SetMarkerSize(1);

  leg->Draw();
  c23tta->Modified(); c23tta->cd(); c23tta->SetSelected(c23tta);


//__________________________________________________________________________________________
TCanvas *c24 = new TCanvas("c24","Jet1 Size vs P_{T}(charged jet1) - 80% of particles"); c24->cd();

fH24 = (TProfile*) hlist_ua104->At(23) ; fH24->SetMarkerColor(2) ; fH24->SetMarkerStyle(26); fH24->Draw();

fH24->GetXaxis()->CenterTitle(true);
fH24->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH24_1 = (TProfile*) hlist_ua107->At(23) ; fH24_1->SetMarkerColor(51); fH24_1->SetMarkerStyle(26); fH24_1->Draw("SAME");

TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH24","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "Jet1 Size vs P_{T}(charged jet1) - 80% of particles", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(26);
   entry->SetMarkerSize(1);

   TLegendEntry *entry=leg->AddEntry("fH24_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "Jet1 Size vs P_{T}(charged jet1) - 80% of particles", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(26);
   entry->SetMarkerSize(1);

   leg->Draw();
   c24->Modified(); c24->cd(); c24->SetSelected(c24);


//__________________________________________________________________________________________
TCanvas *c25 = new TCanvas("c25","Jet1 Size vs P_{T}(charged jet1) - 80% of p_{T}"); c25->cd();

fH25 = (TProfile*) hlist_ua104->At(24) ; fH25->SetMarkerColor(2) ; fH25->SetMarkerStyle(32); fH25->Draw();
fH25->GetXaxis()->CenterTitle(true);
fH25->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH25_1 = (TProfile*) hlist_ua107->At(24) ; fH25_1->SetMarkerColor(51); fH25_1->SetMarkerStyle(32); fH25_1->Draw("SAME");


TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH25","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "Jet1 Size vs P_{T}(charged jet1) - 80% of p_{T}", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(1);

   TLegendEntry *entry=leg->AddEntry("fH25_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "Jet1 Size vs P_{T}(charged jet1) - 80% of p_{T}", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(1);

   leg->Draw();

   c25->Modified(); c25->cd(); c25->SetSelected(c25);

//__________________________________________________________________________________________
TCanvas *c26 = new TCanvas("c26","N_{chg} vs the Distance R from Charged Jet1 - 80% of particles"); c26->cd();

fH26 = (TProfile*) hlist_ua104->At(25) ; fH26->SetMarkerColor(2) ; fH26->SetMarkerStyle(32); fH26->Draw();
fH26->GetXaxis()->CenterTitle(true);
fH26->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH26_1 = (TProfile*) hlist_ua107->At(25) ; fH26_1->SetMarkerColor(51); fH26_1->SetMarkerStyle(32); fH26_1->Draw("SAME");


TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH26","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "N_{chg} vs the Distance R from Charged Jet1 - 80% of particles", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(1);

   TLegendEntry *entry=leg->AddEntry("fH26_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "N_{chg} vs the Distance R from Charged Jet1 - 80% of particles", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(1);

   leg->Draw();

   c26->Modified(); c26->cd(); c26->SetSelected(c26);


//__________________________________________________________________________________________
TCanvas *c27 = new TCanvas("c27","N_{chg} vs the Distance R from Charged Jet1 - 80% of p_{T}"); c27->cd();

fH27 = (TProfile*) hlist_ua104->At(26) ; fH27->SetMarkerColor(2) ; fH27->SetMarkerStyle(32); fH27->Draw();
fH27->GetXaxis()->CenterTitle(true);
fH27->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH27_1 = (TProfile*) hlist_ua107->At(26) ; fH27_1->SetMarkerColor(51); fH27_1->SetMarkerStyle(32); fH27_1->Draw("SAME");


TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH27","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(1);

   TLegendEntry *entry=leg->AddEntry("fH27_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(1);

   leg->Draw();

   c27->Modified(); c27->cd(); c27->SetSelected(c27);


//__________________________________________________________________________________________
TCanvas *c28 = new TCanvas("c28","PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles"); c28->cd();

fH28 = (TProfile*) hlist_ua104->At(27) ; fH28->SetMarkerColor(2) ; fH28->SetMarkerStyle(32); fH28->Draw();
fH28->GetXaxis()->CenterTitle(true);
fH28->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH28_1 = (TProfile*) hlist_ua107->At(27) ; fH28_1->SetMarkerColor(51); fH28_1->SetMarkerStyle(32); fH28_1->Draw("SAME");


TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH28","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(1);

   TLegendEntry *entry=leg->AddEntry("fH28_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(1);

   leg->Draw();

   c28->Modified(); c28->cd(); c28->SetSelected(c28);



//__________________________________________________________________________________________
TCanvas *c29 = new TCanvas("c29","PT_{sum} vs the Distance R from Charged Jet1 - 80% of p_{T}"); c29->cd();

fH29 = (TProfile*) hlist_ua104->At(28) ; fH29->SetMarkerColor(2) ; fH29->SetMarkerStyle(32); fH29->Draw();
fH29->GetXaxis()->CenterTitle(true);
fH29->GetYaxis()->CenterTitle(true);

TLatex *   tex = new TLatex(0.538844,0.773679,"pp events at #sqrt{s_{NN}} = 2.76 TeV");
tex->SetNDC();

Int_t ci;   // for color index setting
ci = TColor::GetColor("#800000");
tex->SetTextColor(ci);
tex->SetTextFont(42);
tex->SetTextSize(0.04);
tex->SetLineWidth(2);
tex->Draw();

fH29_1 = (TProfile*) hlist_ua107->At(28) ; fH29_1->SetMarkerColor(51); fH29_1->SetMarkerStyle(32); fH29_1->Draw("SAME");


TLegend *leg = new TLegend(0.454023,0.5127119,0.8333333,0.7224576,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(1001);

   TLegendEntry *entry=leg->AddEntry("fH29","UA1; R = 0.4; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "PT_{sum} vs the Distance R from Charged Jet1 - 80% of p_{T}", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(1);

   TLegendEntry *entry=leg->AddEntry("fH29_1","UA1; R = 0.7; p_{T} cut = 1 GeV","lpf");
   leg->AddEntry((TObject*)0, "PT_{sum} vs the Distance R from Charged Jet1 - 80% of p_{T}", "");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(51);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(1);

   leg->Draw();

   c29->Modified(); c29->cd(); c29->SetSelected(c29);










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

void myGraphSetUp(TGraphErrors *currentGraph=0, Float_t currentMarkerSize = 1.0,
                  int currentMarkerStyle=20, int currentMarkerColor=0,
                  int currentLineStyle=1, int currentLineColor=0)
  {
  currentGraph->SetMarkerSize(currentMarkerSize);
  currentGraph->SetMarkerStyle(currentMarkerStyle);
  currentGraph->SetMarkerColor(currentMarkerColor);
  currentGraph->SetLineStyle(currentLineStyle);
  currentGraph->SetLineColor(currentLineColor);
  return;
  }













