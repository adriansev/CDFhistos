#ifndef AliAnalysisTaskCDFhistos_cxx
#define AliAnalysisTaskCDFhistos_cxx

/*
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved.
 * See cxx source for full Copyright notice
 *
*/

#include <cstdio>

#include <Riostream.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TInterpreter.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TList.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TH2D.h>


#include "AliLog.h"
#include "AliAnalysisTask.h"
#include "AliAnalysisTaskJets.h"
#include "AliAnalysisManager.h"
#include "AliJetHistos.h"
#include "AliESDEvent.h"
#include "AliVEvent.h"
#include "AliMCEvent.h"
#include "AliESDEvent.h"
#include "AliESDInputHandler.h"
#include "AliInputEventHandler.h"
#include "AliESD.h"
#include "AliAODEvent.h"
#include "AliAODHandler.h"
#include "AliAODJet.h"
#include "AliAODJetEventBackground.h"
#include "AliAODHandler.h"
#include "AliAODExtension.h"
#include "AliMCEventHandler.h"
#include "AliESDInputHandler.h"
#include "AliAODInputHandler.h"
#include "AliStack.h"
#include "AliAnalysisHelperJetTasks.h"
#include "AliAODJetEventBackground.h"
#include "AliAODMCParticle.h"

#include "AliAnalysisTaskSE.h"
// #include "AliVEvent.h"

class TObjArray;
class TRefArray;
class TClonesArray;
class TList;
class TH1D;
class TH1F;
class TH2D;
class TH2F;
class TProfile;
class AliAnalysisTaskSE;
class AliESDEvent;
class AliAODEvent;
class AliAODExtension;
class AliAODJet;
// class AliGenPythiaEventHeader;
class AliAODJetEventBackground;

class AliAnalysisTaskCDFhistos : public AliAnalysisTaskSE
{
 public:

  AliAnalysisTaskCDFhistos ();
  AliAnalysisTaskCDFhistos ( const char* name );
  virtual ~AliAnalysisTaskCDFhistos();

// Implementation of interface methods
  virtual void UserCreateOutputObjects();
  virtual void Init() { LocalInit(); };
  virtual void LocalInit() ;
  virtual void UserExec          (Option_t* /*option*/);
  virtual void Terminate         (Option_t* /*option*/);

  void   CreateHistos();
  void   Clean();

  // jet filtering
      void SetJetMinPt (Double_t pt) {        fJetPtCut = pt; }
  Double_t GetJetMinPt ()            { return fJetPtCut; }

   void SetJetMinTraks ( Int_t min_tracks ) {        fJetMinTracks = min_tracks; }
  Int_t GetJetMinTraks ()                   { return fJetMinTracks; }

   void SetDebugLevel ( Int_t debug ) { fDebug = debug; }
  Int_t GetDebugLevel ()              { return fDebug; }


// non standard files for INPUT
  virtual void        SetNonStdFile (const char *c) {        fNonStdFile = c;    }
  virtual const char* GetNonStdFile ()              { return fNonStdFile.Data(); }

// non standard branches for INPUT
  virtual void        SetNonStdBranch(const char *c)  {        fNonStdBranch = c;    }
  virtual const char* GetNonStdBranch()               { return fNonStdBranch.Data(); }

  void SetAODInput    ( Bool_t b )         { fUseAODInput = b;}
  void SetFillAOD     ( Bool_t fill )      { fFillAOD = fill; }
//   void SetJetBranch   ( const Char_t *br ) { fJetBranch = br; }

private:
  AliAnalysisTaskCDFhistos(const AliAnalysisTaskCDFhistos&);             // not implemented
  AliAnalysisTaskCDFhistos &operator=(const AliAnalysisTaskCDFhistos&);  // not implemented

  Int_t       fDebug;             //  Debug flag

  TString     fNonStdBranch;      // the name of the non-std branch name to be read in input
  TString     fNonStdFile;        // Name of the deltaAOD non std file where jets are written
  TString     fDeltaAODBranch;    //  Jet branch name from delta AOD
  TString     fAODBranch;         //  Jet branch name from standard AOD
  TString     fDeltaAODBranchMC;  //  MC Jet branch name from delta AOD
  TString     fAODBranchMC;       //  MC Jet branch name from standard AOD

  Bool_t      fUseAODInput;    // read jets from input AOD
  Bool_t      fFillAOD;        // option to fill AOD branch
  Bool_t      fFromAod ;       // is the data taken from AOD (or ESD filter)
  Bool_t      fDeltaAOD;       // Read jets from delta AOD

        AliAODEvent*             fAOD;             //! AOD Event
        AliAODEvent*             fAODin;           //! AOD event
        AliAODEvent*             fAODout;          //! AOD event
        AliAODExtension*         fAODExtension;    //! where we take the jets from can be input or output AOD

  TList*  fListOfHistos;          //  Output list of histograms

  Double_t             fRadius;         // cone radius
  Int_t                fJetMinTracks;   // minimum particles of a (considered) jet;
  Double_t             fJetPtCut;       // pt cut in total pt of jets
  Int_t                fNJets;          // counter of number of jets
  Int_t                fNPart;          // number of particles in event
  AliAODJet*           jet1;            //! Leading jet

  Double_t*            fPtArray;        //! momentum array
  Int_t*               fIdxArray;       //! index array of sorted pts
  TRefArray*           fRefArr;         //! pointer to references array of tracks from AOD
  TClonesArray*        fJets;           //! reconstructed jets
  TClonesArray*        fAODtracks;      //! list of AOD tracks from AOD
//   TClonesArray*        fArrayJetsAOD;   //! Array of AOD Jets from delta AOD
//   TClonesArray*        fArrayJetsMC;    //! Array of MC  Jets from delta AOD

  // Histograms    ( are owned by fListOfHistos TList )
  TH1F*       fH1; //!  Pt distribution of jets
  TH1F*       fH2; //!  Eta distribution of jets
  TH1F*       fH3; //!  Phi distribution of jets
  TH1F*       fH4; //!  Multiplicity of jets // 1 unit of multiplicity /bin
  TH1F*       fH5; //!  Distribution of jets in events
  TH1F*       fH6; //!  Jet1 Charged Multiplicity Distribution (Fig 5)- MUST BE SCALED WITH ENTRIES ( ->Scale(fH6->GetEntries()) )
  TProfile*   fH7; //!  N_{chg}(jet1) vs P_{T}(charged jet1) (Fig 4)
  TH1F*       fH8; //!  Charge momentum distribution for leading jet (fragmentation function)(Fig 10-12)
  TProfile*   fH9; //!  N_{chg} vs the Azimuthal Angle from Charged Jet1  (Fig 15,17,19)
  TProfile*  fH10; //!  P_{T} sum vs the Azimuthal Angle from Charged Jet1 (Fig 16,18,20)
  TH1F*      fH20; //!  Distribution of R in leading jet

  TProfile*  fH21;           //!  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 13)
  TProfile*  fH21Toward;     //!  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,23,24)
  TProfile*  fH21Transverse; //!  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,28,30,32,33,34)
  TProfile*  fH21Away;       //!  N_{chg}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 21,25,27)

  TProfile*  fH22;           //!  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
  TProfile*  fH22Toward;     //!  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22)
  TProfile*  fH22Transverse; //!  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,29,31)
  TProfile*  fH22Away;       //!  PT_{sum}(in the event - including jet1) vs P_{T}(charged jet1) (Fig 22,26)

  TH1F*      fH23;           //!  TOTAL Pt Distribution of charged particles
  TH1F*      fH23jet1;       //!  jet1 Pt Distribution of charged particles
  TH1F*      fH23Toward;     //!  'Toward' Pt Distribution of charged particles
  TH1F*      fH23Transverse; //!  'Transverse' Pt Distribution of charged particles  (Fig 37,38,39,40,41)
  TH1F*      fH23Away;       //!  'Away' Pt Distribution of charged particles

  TProfile*  fH24;           //!  Jet1 Size vs P_{T}(charged jet1) - 80% of particles  (Fig 6)
  TProfile*  fH25;           //!  Jet1 Size vs P_{T}(charged jet1) - 80% of Pt  (Fig 6)
  TProfile*  fH26;           //!  N_{chg} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 8)
  TProfile*  fH27;           //!  N_{chg} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 8)
  TProfile*  fH28;           //!  PT_{sum} vs the Distance R from Charged Jet1 - 80% of particles   (Fig 9)
  TProfile*  fH29;           //!  PT_{sum} vs the Distance R from Charged Jet1 - 80% of Pt  (Fig 9)


ClassDef(AliAnalysisTaskCDFhistos, 1); // Analysis task for CDF jet analysis
};


#endif
