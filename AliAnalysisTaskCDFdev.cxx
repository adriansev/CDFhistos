/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* $Id: AliAnalysisTaskCDFdev.cxx */

#include "AliAnalysisTaskCDFdev.h"

using namespace std;


ClassImp ( AliAnalysisTaskCDFdev )

//______________________________________________________________________________
AliAnalysisTaskCDFdev::AliAnalysisTaskCDFdev ( ) :
    AliAnalysisTaskSE(),
    fNonStdBranch     ( "" ),
    fNonStdFile       ( "" ),
    fDeltaAODBranch   ( "" ),
    fAODBranch        ( "" ),
    fDeltaAODBranchMC ( "" ),
    fAODBranchMC      ( "" ),
    fUseAODInput   (kTRUE),
    fFillAOD       (kFALSE),
    fFromAod       (kFALSE),
    fDeltaAOD      (kFALSE),
    fESD           (NULL),
    fAOD           (NULL),
    fAODin         (NULL),
    fAODout        (NULL),
    fAODExtension  (NULL),
    fListOfHistos  (NULL),
    fRadius        (0.7),
    fJetMinTracks  (1),
    fJetPtCut      (0.),
    fNJets         (0),
    fNPart         (0),
    jet1           (NULL),
    fPtArray       (NULL),
    fIdxArray      (NULL),
    fRefArr        (NULL),
    fJets          (NULL),
    fAODtracks     (NULL),
    fH1            (NULL),
    fH2            (NULL),
    fH3            (NULL),
    fH4            (NULL),
    fH5            (NULL)
{
  // Default constructor
}


//______________________________________________________________________________
AliAnalysisTaskCDFdev::AliAnalysisTaskCDFdev ( const char *name) :
    AliAnalysisTaskSE( name ),
    fNonStdBranch     ( "" ),
    fNonStdFile       ( "" ),
    fDeltaAODBranch   ( "" ),
    fAODBranch        ( "" ),
    fDeltaAODBranchMC ( "" ),
    fAODBranchMC      ( "" ),
    fUseAODInput   (kTRUE),
    fFillAOD       (kFALSE),
    fFromAod       (kFALSE),
    fDeltaAOD      (kFALSE),
    fESD           (NULL),
    fAOD           (NULL),
    fAODin         (NULL),
    fAODout        (NULL),
    fAODExtension  (NULL),
    fListOfHistos  (NULL),
    fRadius        (0.7),
    fJetMinTracks  (1),
    fJetPtCut      (0.),
    fNJets         (0),
    fNPart         (0),
    jet1           (NULL),
    fPtArray       (NULL),
    fIdxArray      (NULL),
    fRefArr        (NULL),
    fJets          (NULL),
    fAODtracks     (NULL),
    fH1            (NULL),
    fH2            (NULL),
    fH3            (NULL),
    fH4            (NULL),
    fH5            (NULL)
{
  // Default constructor
  DefineOutput ( 1, TList::Class() );
}

//______________________________________________________________________________
AliAnalysisTaskCDFdev::~AliAnalysisTaskCDFdev()
{
// destructor
// delete fListOfHistos;
}

//______________________________________________________________________________
void AliAnalysisTaskCDFdev::UserCreateOutputObjects()
{
// Create the output container
if ( AliAnalysisTaskSE::fDebug > 1 ) AliInfo("AnalysisTaskCDFdev::CreateOutPutData()");

  //  Histograms
  OpenFile(1);
  CreateHistos();
  PostData(1, fListOfHistos); // PostData at least once
}

//______________________________________________________________________________
void AliAnalysisTaskCDFdev::UserExec ( Option_t */*option*/ )
{
// Execute analysis for current event
if ( fDebug > 1 ) { printf("\n CDFdev:: ConnectInputData() \n"); }

//---------------------
//    enable aod writing for all tasks
//---------------------

// only need this once but !!! ACLIC does NOT like "static"
AliAODHandler* aodH_out = dynamic_cast<AliAODHandler*>(AliAnalysisManager::GetAnalysisManager()->GetOutputEventHandler());
aodH_out->SetFillAODforRun ( kTRUE );
aodH_out->SetFillExtension ( kTRUE );
aodH_out->SetFillAOD       ( kTRUE );

// general pointers to data
fAODin  = dynamic_cast<AliAODEvent*>(InputEvent());
fAODout = dynamic_cast<AliAODEvent*>(AODEvent());


fESD = dynamic_cast<AliESDEvent*>(InputEvent());
if (!fESD)
  {
  AliError("ESD not available");
  fAODin = dynamic_cast<AliAODEvent*>(InputEvent());
  }

fAODout = dynamic_cast<AliAODEvent*>(AODEvent());

if( !fESD )
  { fAOD = fAODin;  }
else
  { fAOD = fAODout; }

if( !fAOD ){  if (fDebug > 1 ) { printf("%s:%d AODEvent not found in the Output",(char*)__FILE__,__LINE__); } return; }


if ( fDebug > 0 )
  {
  cout << "--> CDF Histos :: places to look out for found jets" << endl;
  cout << "fNonStdFile : "   << fNonStdFile << endl;
  cout << "fNonStdBranch : " << fNonStdBranch << endl;
  }


if(fNonStdFile.Length()!=0)
  {
  // case that we have an AOD extension we can fetch the jets from the extended output
  AliAODHandler* aodH = dynamic_cast<AliAODHandler*>(AliAnalysisManager::GetAnalysisManager()->GetOutputEventHandler());
  fAODExtension = ( aodH ? aodH->GetExtension(fNonStdFile.Data()) : 0 );
  if ( !fAODExtension ) { if(fDebug>1) Printf("AODExtension found for %s",fNonStdFile.Data()); }
  }


if ( fAOD && ( fDebug > 0 ) )
  {
  cout << "fAOD pointer : " << fAOD << endl;
  cout << "AOD : " << fAOD->GetName() << endl ; fAOD->Print();
  }

if ( fAODExtension && ( fDebug > 0 ) )
  {
  cout << "fAODExtension pointer : " << fAODExtension << endl;
  cout << "fAODExtension : " << fAODExtension->GetName() << endl;
  fAODExtension->Print();
  }

// fetch jets
if ( fNonStdBranch.Length() != 0 )
  {
  cout << "CDF histos :: Branch : " << fNonStdBranch.Data() << endl;
  // !fJets evaluated first --> if NO_JETS then rest is evaluated
  if ( fAODExtension && !fJets ) { fJets = dynamic_cast<TClonesArray*> ( fAODExtension->GetAOD()->FindListObject(fNonStdBranch.Data())); }
  if ( fAOD          && !fJets ) { fJets = dynamic_cast<TClonesArray*> ( fAOD->FindListObject (fNonStdBranch.Data()) ); }
  }
else
  { fJets = fAOD->GetJets(); }

// protection against not finding jets
if ( !fJets )           { cout << "Jets pointer NULL" << endl; return; }
if ( fJets->IsEmpty() ) { cout << "Jets EMPTY" << endl; return; }

if ( fDebug > 0 )
  {
  cout << "Jets pointer : "  << fJets << endl;
  fJets->Print();
  }

  fNPart = fAOD->GetNTracks();
  fNJets = fAOD->GetNJets();

  printf ( "fNJets = %i ; fNPart = %i \n", fNJets, fNPart ); fflush(stdout);
  printf ( "CDFdev::end of ConnectInputData() \n");       fflush(stdout);

  if ((fNJets == 0) || (fNPart == 0)) { return; }

// global jet propreties
  for (Int_t i = 0 ; i < fNJets ; i++ )
      { // loop over jets; here will be made in jet analysis
      AliAODJet* jet = fAOD->GetJet(i);

      fH1->Fill ( jet->Pt() );  // Pt distribution of jets
      fH2->Fill ( jet->Eta() ); // Eta distribution of jets
      fH3->Fill ( jet->Phi() ); // Phi distribution of jets
      fH4->Fill ( jet->GetRefTracks()->GetEntries() );  // Multiplicity of jets // 1 unit of multiplicity /bin
      }

  // Distribution of jets in events
  fH5->Fill ( fNJets );

printf ("CDFdev:: end of global jet histos \n"); fflush(stdout);

// Post the data
PostData ( 1, fListOfHistos );
}

//______________________________________________________________________________
void AliAnalysisTaskCDFdev::Clean()
{ // CLEANING SECTION
cout << "IN Clean() :: starting Clean()" << endl;



}

//______________________________________________________________________________
void AliAnalysisTaskCDFdev::Terminate ( Option_t */*option*/ )
{  // Terminate analysis
  if( fDebug > 1 ) AliInfo("AliAnalysisTaskCDFdev: Terminate() \n");

  // Update pointers reading them from the output slot
  fListOfHistos = dynamic_cast<TList*> (GetOutputData(0));
}

//______________________________________________________________________________
void AliAnalysisTaskCDFdev::CreateHistos()
{
//  Histograms
  if (!fListOfHistos) fListOfHistos = new TList();
  fListOfHistos->SetOwner(kTRUE);

  // Create the list of histograms. Only the list is owned.

  fH1 = new TH1F ("histo1", "Pt distribution of jets", 400, 0, 400);  // 1GeV/bin
  fH1->SetStats(kTRUE);
  fH1->GetXaxis()->SetTitle("P_{T} of jets");
  fH1->GetYaxis()->SetTitle("Number of jets");
  fH1->GetXaxis()->SetTitleColor(1);
  fH1->SetMarkerStyle(kFullCircle);
  fListOfHistos->Add(fH1);

  fH2 = new TH1F ("histo2", "Eta distribution of jets", 200, -1., 1.); // 1 unit of rapidity / 100 bin
  fH2->SetStats(kTRUE);
  fH2->GetXaxis()->SetTitle("Eta of jets");
  fH2->GetYaxis()->SetTitle("Number of jets");
  fH2->GetXaxis()->SetTitleColor(1);
  fH2->SetMarkerStyle(kFullCircle);
  fListOfHistos->Add(fH2);

  fH3 = new TH1F ("histo3", "Phi distribution of jets", 126, 0.,6.3);
  fH3->SetStats(kTRUE);
  fH3->GetXaxis()->SetTitle("Phi of jets");
  fH3->GetYaxis()->SetTitle("Number of jets");
  fH3->GetXaxis()->SetTitleColor(1);
  fH3->SetMarkerStyle(kFullCircle);
  fListOfHistos->Add(fH3);

  fH4 = new TH1F ("histo4", "Multiplicity of jets", 100, 0,100);  // 1 unit of multiplicity /bin
  fH4->SetStats(kTRUE);
  fH4->GetXaxis()->SetTitle("Particles in jets");
  fH4->GetYaxis()->SetTitle("Number of jets");
  fH4->GetXaxis()->SetTitleColor(1);
  fH4->SetMarkerStyle(kFullCircle);
  fListOfHistos->Add(fH4);

  fH5 = new TH1F ("histo5", "Distribution of jets in events", 20, 0, 20);
  fH5->SetStats(kTRUE);
  fH5->GetXaxis()->SetTitle("Number of jets");
  fH5->GetYaxis()->SetTitle("Number of events");
  fH5->GetXaxis()->SetTitleColor(1);
  fH5->SetMarkerStyle(kFullCircle);
  fListOfHistos->Add(fH5);


  // =========== Switch on Sumw2 for all histos ===========
  for (Int_t i=0; i < fListOfHistos->GetEntries(); ++i)
    {
    TH1 *h1 = dynamic_cast<TH1*>(fListOfHistos->At(i));
    if (h1) { h1->Sumw2(); continue; }

    TProfile *hprof1 = dynamic_cast<TProfile*>(fListOfHistos->At(i));
    if (hprof1) { hprof1->Sumw2(); }
    }

  // Post the data
  PostData ( 1, fListOfHistos );

}

//______________________________________________________________________________
void AliAnalysisTaskCDFdev::LocalInit()
{
  // Initialization
  if ( fDebug > 1 ) { printf ( "AnalysisTaskJets::Init() \n" ); }

}

