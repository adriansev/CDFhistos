#ifndef ALIANALYSISTASKEMCALJETCDF_H
#define ALIANALYSISTASKEMCALJETCDF_H

#include <cstdio>
#include <Rtypes.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TProfile.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TProfile.h>
#include <TMath.h>
#include <TVector2.h>

#include "AliLog.h"
#include "AliEmcalJet.h"
#include "AliJetContainer.h"
#include "AliParticleContainer.h"
#include "AliClusterContainer.h"

#include "AliAnalysisTaskEmcalJet.h"

// #include <Riostream.h>
// #include <TInterpreter.h>
// #include <TChain.h>
// #include <TFile.h>
// #include <TTree.h>
// #include <TList.h>
// #include <TH2.h>
// #include <TH2F.h>
// #include <TH1D.h>
// #include <TH2D.h>
// #include <TClonesArray.h>
// #include <TLorentzVector.h>
// #include "AliStack.h"
// #include "AliRhoParameter.h"
// #include "AliAnalysisTask.h"
// #include "AliAnalysisTaskSE.h"
// #include "AliAnalysisTaskEmcalJet.h"
// #include "AliAnalysisManager.h"
// #include "AliAnalysisHelperJetTasks.h"
// #include "AliESD.h"
// #include "AliESDEvent.h"
// #include "AliVEvent.h"
// #include "AliMCEvent.h"
// #include "AliESDEvent.h"
// #include "AliESDInputHandler.h"
// #include "AliVCluster.h"
// #include "AliVTrack.h"
// #include "AliInputEventHandler.h"
// #include "AliAODEvent.h"
// #include "AliAODHandler.h"
// #include "AliAODJet.h"
// #include "AliAODJetEventBackground.h"
// #include "AliAODExtension.h"
// #include "AliMCEventHandler.h"
// #include "AliAODInputHandler.h"
// #include "AliAODJetEventBackground.h"
// #include "AliAODMCParticle.h"

class TH1;
class TH2;
class TProfile;
class AliAnalysisUtils;
class AliJetContainer;
class AliParticleContainer;
class AliClusterContainer;

class AliAnalysisTaskEmcalJetCDF : public AliAnalysisTaskEmcalJet
    {
    public:

        AliAnalysisTaskEmcalJetCDF();
        AliAnalysisTaskEmcalJetCDF ( const char* name );
        virtual ~AliAnalysisTaskEmcalJetCDF();

        void                        UserCreateOutputObjects();
        void                        Terminate ( Option_t* option );


        Double_t                    Phi_mpi_pi ( Double_t phi ) { return TVector2::Phi_mpi_pi ( phi ); } // returns phi angle in the interval [-PI,PI)
        Double_t                    DeltaR ( const AliVParticle* part1, const AliVParticle* part2 );   // return dR dinstance in eta,phi plane between 2 AliVParticle derived objects // this could be added in EmcalJet?

        //Setters
        void SetTriggerClass           ( const char* n )    { fTriggerClass       = n; }
//         void SetContainerFull          ( Int_t c )          { fContainerFull      = c; }
//         void SetContainerCharged       ( Int_t c )          { fContainerCharged   = c; }

        Double_t GetZ ( const AliVParticle* trk, const AliEmcalJet* jet )       const; // Get Z of constituent trk // could be added in EmcalJet?
        Double_t GetZ ( const Double_t trkPx, const Double_t trkPy, const Double_t trkPz, const Double_t jetPx, const Double_t jetPy, const Double_t jetPz ) const; // Get Z of constituent trk

    protected:
        Bool_t                      FillHistograms()   ;
        Int_t                       FillHistograms_container ( Int_t idx_jet_container );

        void                        ExecOnce();
        Bool_t                      Run() ;


//         Int_t                       fContainerFull;      //  number of container with full jets DET
//         Int_t                       fContainerCharged;   //  number of container with charged jets DET
        TString                     fTriggerClass;       // trigger class to analyze EJ1 or EJ2
        Int_t*                      fJET1_track_idx;     //! pointer to array of indexes (sorting of jet tracks by pt)
        Double_t*                   fJET1_track_pt;      //! pointer to array of pt (sorting of jet tracks by pt)
        Int_t*                      fTrack_idx;          //! pointer to array of indexes (sorting of event tracks by pt)
        Double_t*                   fTrack_pt;           //! pointer to array of pt (sorting of event tracks by pt)

        // Histograms    ( are owned by fListOfHistos TList )
        TH1F*       fH1;           //!  Pt distribution of jets
        TH1F*       fH2;           //!  Eta distribution of jets
        TH1F*       fH3;           //!  Phi distribution of jets
        TH1F*       fH4;           //!  Multiplicity of jets // 1 unit of multiplicity /bin
        TH1F*       fH5;           //!  Distribution of jets in events
        TH1F*       fH5acc;        //!  Distribution of accepted jets in events
        TH1F*       fH6;           //!  Jet1 Multiplicity Distribution
        TProfile*   fH7;           //!  N(jet1) vs P_{T}(jet1)
        TH1F*       fH8;           //!  Momentum distribution for leading jet (fragmentation function)
        TProfile*   fH9;           //!  N vs the Azimuthal Angle from Jet1
        TProfile*  fH10;           //!  P_{T} sum vs the Azimuthal Angle from Jet1
        TH1F*      fH20;           //!  Distribution of R in leading jet

        TProfile*  fH21;           //!  N(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH21Toward;     //!  N(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH21Transverse; //!  N(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH21Away;       //!  N(in the event - including jet1) vs P_{T}(jet1)

        TProfile*  fH22;           //!  PT_{sum}(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH22Toward;     //!  PT_{sum}(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH22Transverse; //!  PT_{sum}(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH22Away;       //!  PT_{sum}(in the event - including jet1) vs P_{T}(jet1)

        TH1F*      fH23;           //!  Event Pt Distribution of particles
        TH1F*      fH23jet1;       //!  Jet1 Pt Distribution of particles
        TH1F*      fH23Toward;     //!  'Toward' Pt Distribution of particles
        TH1F*      fH23Transverse; //!  'Transverse' Pt Distribution of particles
        TH1F*      fH23Away;       //!  'Away' Pt Distribution of particles

        TProfile*  fH24;           //!  Jet1 Size vs P_{T}(jet1) - 80% of particles
        TProfile*  fH25;           //!  Jet1 Size vs P_{T}(jet1) - 80% of Pt
        TProfile*  fH26;           //!  N_{chg} vs the Distance R from Jet1 - 80% of particles
        TProfile*  fH27;           //!  N_{chg} vs the Distance R from Jet1 - 80% of Pt
        TProfile*  fH28;           //!  PT_{sum} vs the Distance R from Jet1 - 80% of particles
        TProfile*  fH29;           //!  PT_{sum} vs the Distance R from Jet1 - 80% of Pt

        AliJetContainer*           fJetsCont;                   //!Jets
        AliParticleContainer*      fTracksCont;                 //!Tracks
        AliClusterContainer*       fCaloClustersCont;           //!Clusters

    private:
        AliAnalysisTaskEmcalJetCDF ( const AliAnalysisTaskEmcalJetCDF& );            // not implemented
        AliAnalysisTaskEmcalJetCDF& operator= ( const AliAnalysisTaskEmcalJetCDF& ); // not implemented

        ClassDef ( AliAnalysisTaskEmcalJetCDF, 1 ) // jet sample analysis task
    };
#endif
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
