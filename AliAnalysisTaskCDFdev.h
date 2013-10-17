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

class AliAnalysisTaskCDFdev : public AliAnalysisTaskSE
{
 public:

  AliAnalysisTaskCDFdev ();
  AliAnalysisTaskCDFdev ( const char* name );
  virtual ~AliAnalysisTaskCDFdev();

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
  AliAnalysisTaskCDFdev(const AliAnalysisTaskCDFdev&);             // not implemented
  AliAnalysisTaskCDFdev &operator=(const AliAnalysisTaskCDFdev&);  // not implemented

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

  AliESDEvent*             fESD;             //! ESD object
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

ClassDef(AliAnalysisTaskCDFdev, 1); // Analysis task for CDF jet analysis
};


#endif
