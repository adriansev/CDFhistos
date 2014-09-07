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

#include "AliLog.h"
#include "AliEmcalJet.h"
#include "AliJetContainer.h"
#include "AliParticleContainer.h"
#include "AliClusterContainer.h"

#include "AliAnalysisTaskEmcalJet.h"

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

        Double_t                    DeltaR ( const AliVParticle* part1, const AliVParticle* part2 );   // return dR dinstance in eta,phi plane between 2 AliVParticle derived objects

        //Setters
        void SetTriggerClass           ( const char* n )    { fTriggerClass       = n; }

        Double_t GetZ ( const AliVParticle* trk, const AliEmcalJet* jet )       const; // Get Z of constituent trk // could be added in EmcalJet?
        Double_t GetZ ( const Double_t trkPx, const Double_t trkPy, const Double_t trkPz, const Double_t jetPx, const Double_t jetPy, const Double_t jetPz ) const; // Get Z of constituent trk

    protected:
        Bool_t                      FillHistograms()   ;
//         Int_t                       FillHistograms_container ( Int_t idx_jet_container );

        void                        ExecOnce();
        Bool_t                      Run() ;
        std::vector<Int_t>          SortTracksPt ( AliVEvent* event ) const;
        std::vector<Int_t>          SortTracksPt ( AliParticleContainer* track_container ) const;

        TString                     fTriggerClass;       // trigger class to analyze EJ1 or EJ2

        // Histograms    ( are owned by fListOfHistos TList )
        TH1D*       fH1;           //!  Pt distribution of jets
        TH1D*       fH2;           //!  Eta distribution of jets
        TH1D*       fH3;           //!  Phi distribution of jets
        TH1D*       fH4;           //!  Multiplicity of jets // 1 unit of multiplicity /bin
        TH1D*       fH5;           //!  Distribution of jets in events
        TH1D*       fH5acc;        //!  Distribution of accepted jets in events
        TH1D*       fH6;           //!  Jet1 Multiplicity Distribution
        TProfile*   fH7;           //!  N(jet1) vs P_{T}(jet1)
        TH1D*       fH8;           //!  Momentum distribution for leading jet (fragmentation function)
        TH1D*       fH8xi;         //!  Xi distribution for leading jet (fragmentation function)
        TProfile*   fH9;           //!  N vs the Azimuthal Angle from Jet1
        TProfile*  fH10;           //!  P_{T} sum vs the Azimuthal Angle from Jet1
        TH1D*      fH20;           //!  Distribution of R in leading jet

        TProfile*  fH21;           //!  N(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH21Toward;     //!  N(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH21Transverse; //!  N(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH21Away;       //!  N(in the event - including jet1) vs P_{T}(jet1)

        TProfile*  fH22;           //!  PT_{sum}(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH22Toward;     //!  PT_{sum}(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH22Transverse; //!  PT_{sum}(in the event - including jet1) vs P_{T}(jet1)
        TProfile*  fH22Away;       //!  PT_{sum}(in the event - including jet1) vs P_{T}(jet1)

        TH1D*      fH23;           //!  Event Pt Distribution of particles
        TH1D*      fH23jet1;       //!  Jet1 Pt Distribution of particles
        TH1D*      fH23Toward;     //!  'Toward' Pt Distribution of particles
        TH1D*      fH23Transverse; //!  'Transverse' Pt Distribution of particles
        TH1D*      fH23Away;       //!  'Away' Pt Distribution of particles

        TProfile*  fH24;           //!  Jet1 Size vs P_{T}(jet1) - 80% of particles
        TProfile*  fH25;           //!  Jet1 Size vs P_{T}(jet1) - 80% of Pt
        TProfile*  fH26;           //!  N_{chg} vs the Distance R from Jet1 - 80% of particles
        TProfile*  fH27;           //!  N_{chg} vs the Distance R from Jet1 - 80% of Pt
        TProfile*  fH28;           //!  PT_{sum} vs the Distance R from Jet1 - 80% of particles
        TProfile*  fH29;           //!  PT_{sum} vs the Distance R from Jet1 - 80% of Pt


        TProfile*  fH40;           //!  total particles fNPart w.r.t PTmax (pt of leading particle from leading jet)
        TProfile*  fH40toward;     //!  total particles fNPart w.r.t PTmax (pt of leading particle from leading jet)
        TProfile*  fH40away;       //!  total particles fNPart w.r.t PTmax (pt of leading particle from leading jet)
        TProfile*  fH40transmin;   //!  total particles fNPart w.r.t PTmax (pt of leading particle from leading jet)
        TProfile*  fH40transmax;   //!  total particles fNPart w.r.t PTmax (pt of leading particle from leading jet)

        TProfile*  fH41;           //!  PTsum w.r.t PTmax
        TProfile*  fH41toward;     //!  PTsum w.r.t PTmax
        TProfile*  fH41away;       //!  PTsum w.r.t PTmax
        TProfile*  fH41transmin;   //!  PTsum w.r.t PTmax
        TProfile*  fH41transmax;   //!  PTsum w.r.t PTmax




        AliJetContainer*           fJetsCont;                   //!Jets
        AliParticleContainer*      fTracksCont;                 //!Tracks
        AliClusterContainer*       fCaloClustersCont;           //!Clusters

    private:
        struct sort_descend
            { // sort in decreasing order
            // first value of the pair is Pt and the second is entry index
            bool operator () (const std::pair<Double_t, Int_t>& p1, const std::pair<Double_t, Int_t>& p2)  { return p1.first > p2.first ; }
            };

        AliAnalysisTaskEmcalJetCDF ( const AliAnalysisTaskEmcalJetCDF& );            // not implemented
        AliAnalysisTaskEmcalJetCDF& operator= ( const AliAnalysisTaskEmcalJetCDF& ); // not implemented

        ClassDef ( AliAnalysisTaskEmcalJetCDF, 1 ) // jet sample analysis task
    };
#endif
// kate: indent-mode none; indent-width 4; replace-tabs on;
