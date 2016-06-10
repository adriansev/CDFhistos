/**************************************************************************
 * Copyright(c) 1998-2016, ALICE Experiment at CERN, All rights reserved. *
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

#include <cmath>

#include <TClonesArray.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TProfile.h>

#include <AliVCluster.h>
#include <AliVParticle.h>
#include <AliLog.h>

#include "AliTLorentzVector.h"
#include "AliEmcalJet.h"
#include "AliRhoParameter.h"
#include "AliJetContainer.h"
#include "AliParticleContainer.h"
#include "AliClusterContainer.h"

#include "AliEmcalList.h"


// #include <Rtypes.h>
// #include <TMath.h>
// #include <TMathBase.h>
// #include <TArray.h>
// #include <TArrayI.h>
//
// #include <TAxis.h>
// #include <TSeqCollection.h>
// #include <TCollection.h>
// #include <TLorentzVector.h>
// #include <TVector2.h>
// #include <TAttMarker.h>
//
// #include <AliAODCaloCluster.h>
// #include <AliESDCaloCluster.h>
// #include <AliVTrack.h>
// #include <AliVEvent.h>

#include "AliAnalysisTaskEmcalJetCDF.h"

/// \cond CLASSIMP
ClassImp ( AliAnalysisTaskEmcalJetCDF );
/// \endcond

/**
 * Default constructor. Needed by ROOT I/O
 */
AliAnalysisTaskEmcalJetCDF::AliAnalysisTaskEmcalJetCDF() :
    AliAnalysisTaskEmcalJet (),
    fH1( NULL ),
    fH2( NULL ),
    fH3( NULL ),
    fH4( NULL ),
    fH4c( NULL ),
    fH5( NULL ),
    fH6( NULL ),
    fH6c( NULL ),
    fH8( NULL ),
    fH8xi( NULL ),
    fH8_all( NULL ),
    fH8xi_all( NULL ),
    fH15_bin( NULL ),
    fH15_bin_n90( NULL ),
    fH15_bin_n85( NULL ),
    fH15_bin_n80( NULL ),
    fH15_bin_n75( NULL ),
    fH15_bin_n70( NULL ),
    fH15_bin_pt90( NULL ),
    fH15_bin_pt85( NULL ),
    fH15_bin_pt80( NULL ),
    fH15_bin_pt75( NULL ),
    fH15_bin_pt70( NULL ),
    fH15all_bin( NULL ),
    fH15all_bin_n90( NULL ),
    fH15all_bin_n85( NULL ),
    fH15all_bin_n80( NULL ),
    fH15all_bin_n75( NULL ),
    fH15all_bin_n70( NULL ),
    fH15all_bin_pt90( NULL ),
    fH15all_bin_pt85( NULL ),
    fH15all_bin_pt80( NULL ),
    fH15all_bin_pt75( NULL ),
    fH15all_bin_pt70( NULL ),
    fH20( NULL ),
    fH20_n90( NULL ),
    fH20_n85( NULL ),
    fH20_n80( NULL ),
    fH20_n75( NULL ),
    fH20_n70( NULL ),
    fH20_pt90( NULL ),
    fH20_pt85( NULL ),
    fH20_pt80( NULL ),
    fH20_pt75( NULL ),
    fH20_pt70( NULL ),
    fH20all( NULL ),
    fH20all_n90( NULL ),
    fH20all_n85( NULL ),
    fH20all_n80( NULL ),
    fH20all_n75( NULL ),
    fH20all_n70( NULL ),
    fH20all_pt90( NULL ),
    fH20all_pt85( NULL ),
    fH20all_pt80( NULL ),
    fH20all_pt75( NULL ),
    fH20all_pt70( NULL ),
    fHg( NULL ),
    fHg_n90( NULL ),
    fHg_n85( NULL ),
    fHg_n80( NULL ),
    fHg_n75( NULL ),
    fHg_n70( NULL ),
    fHg_pt90( NULL ),
    fHg_pt85( NULL ),
    fHg_pt80( NULL ),
    fHg_pt75( NULL ),
    fHg_pt70( NULL ),
    fHptd( NULL ),
    fHptd_n90( NULL ),
    fHptd_n85( NULL ),
    fHptd_n80( NULL ),
    fHptd_n75( NULL ),
    fHptd_n70( NULL ),
    fHptd_pt90( NULL ),
    fHptd_pt85( NULL ),
    fHptd_pt80( NULL ),
    fHptd_pt75( NULL ),
    fHptd_pt70( NULL ),
    fJetsCont ( NULL ),
    fTracksCont ( NULL ),
    fCaloClustersCont ( NULL ),
    fTracksContArray ( NULL ),
    idx_jetcont(0),
    fNJets_accepted ( 0 ),
    fNaccPart ( 0 ),
    fNaccClus ( 0 ),
    fHistManager()
  {
  // Default constructor.
  fDebug = AliLog::GetGlobalDebugLevel();
  }

/**
 * Standard constructor. Should be used by the user.
 *
 * @param[in] name Name of the task
 */
AliAnalysisTaskEmcalJetCDF::AliAnalysisTaskEmcalJetCDF ( const char *name ) :
    AliAnalysisTaskEmcalJet ( name, kTRUE ),
    fH1( NULL ),
    fH2( NULL ),
    fH3( NULL ),
    fH4( NULL ),
    fH4c( NULL ),
    fH5( NULL ),
    fH6( NULL ),
    fH6c( NULL ),
    fH8( NULL ),
    fH8xi( NULL ),
    fH8_all( NULL ),
    fH8xi_all( NULL ),
    fH15_bin( NULL ),
    fH15_bin_n90( NULL ),
    fH15_bin_n85( NULL ),
    fH15_bin_n80( NULL ),
    fH15_bin_n75( NULL ),
    fH15_bin_n70( NULL ),
    fH15_bin_pt90( NULL ),
    fH15_bin_pt85( NULL ),
    fH15_bin_pt80( NULL ),
    fH15_bin_pt75( NULL ),
    fH15_bin_pt70( NULL ),
    fH15all_bin( NULL ),
    fH15all_bin_n90( NULL ),
    fH15all_bin_n85( NULL ),
    fH15all_bin_n80( NULL ),
    fH15all_bin_n75( NULL ),
    fH15all_bin_n70( NULL ),
    fH15all_bin_pt90( NULL ),
    fH15all_bin_pt85( NULL ),
    fH15all_bin_pt80( NULL ),
    fH15all_bin_pt75( NULL ),
    fH15all_bin_pt70( NULL ),
    fH20( NULL ),
    fH20_n90( NULL ),
    fH20_n85( NULL ),
    fH20_n80( NULL ),
    fH20_n75( NULL ),
    fH20_n70( NULL ),
    fH20_pt90( NULL ),
    fH20_pt85( NULL ),
    fH20_pt80( NULL ),
    fH20_pt75( NULL ),
    fH20_pt70( NULL ),
    fH20all( NULL ),
    fH20all_n90( NULL ),
    fH20all_n85( NULL ),
    fH20all_n80( NULL ),
    fH20all_n75( NULL ),
    fH20all_n70( NULL ),
    fH20all_pt90( NULL ),
    fH20all_pt85( NULL ),
    fH20all_pt80( NULL ),
    fH20all_pt75( NULL ),
    fH20all_pt70( NULL ),
    fHg( NULL ),
    fHg_n90( NULL ),
    fHg_n85( NULL ),
    fHg_n80( NULL ),
    fHg_n75( NULL ),
    fHg_n70( NULL ),
    fHg_pt90( NULL ),
    fHg_pt85( NULL ),
    fHg_pt80( NULL ),
    fHg_pt75( NULL ),
    fHg_pt70( NULL ),
    fHptd( NULL ),
    fHptd_n90( NULL ),
    fHptd_n85( NULL ),
    fHptd_n80( NULL ),
    fHptd_n75( NULL ),
    fHptd_n70( NULL ),
    fHptd_pt90( NULL ),
    fHptd_pt85( NULL ),
    fHptd_pt80( NULL ),
    fHptd_pt75( NULL ),
    fHptd_pt70( NULL ),
    fJetsCont ( NULL ),
    fTracksCont ( NULL ),
    fCaloClustersCont ( NULL ),
    fTracksContArray ( NULL ),
    idx_jetcont(0),
    fNJets_accepted ( 0 ),
    fNaccPart ( 0 ),
    fNaccClus ( 0 ),
    fHistManager(name)
  {
  // Standard constructor.
  fDebug = AliLog::GetGlobalDebugLevel();
  SetMakeGeneralHistograms ( kTRUE );
  }

/// Destructor
AliAnalysisTaskEmcalJetCDF::~AliAnalysisTaskEmcalJetCDF()
  {
  // Destructor.
  if ( fJetsCont )         { delete fJetsCont ;         fJetsCont = NULL; }
  if ( fTracksCont )       { delete fTracksCont ;       fTracksCont = NULL; }
  if ( fCaloClustersCont ) { delete fCaloClustersCont ; fCaloClustersCont = NULL; }

  if ( fTracksContArray )    { delete fTracksContArray ;    fTracksContArray = NULL; }
  if ( fCaloClustContArray ) { delete fCaloClustContArray ; fCaloClustContArray = NULL; }

  }

/**
 * Run analysis code here, if needed.
 * It will be executed before FillHistograms().
 * If this function return kFALSE, FillHistograms() will *not*
 * be executed for the current event
 * @return Always kTRUE
 */
Bool_t AliAnalysisTaskEmcalJetCDF::Run()
  {
  return ProcessJetContainer(idx_jetcont);
  }

//________________________________________________________________________
Bool_t AliAnalysisTaskEmcalJetCDF::ProcessJetContainer(Int_t idx_jet_container)
  {
  fJetsCont = GetJetContainer ( idx_jet_container );
  fJetsCont->ResetCurrentID();

  if ( !fJetsCont )
      {
      std::cout << "ERROR :: Jet Container not found!!!" << std::endl;
      return kFALSE;
      }

  // get particles connected to jets
  fTracksCont = fJetsCont->GetParticleContainer();
  if (fTracksCont)
    {
    fTracksCont->ResetCurrentID();
    fTracksCont->SetClassName ( "AliVTrack" );

    // get array of tracks
    fTracksContArray = fTracksCont->GetArray();

    // Multiplicity in event - accepted tracks in tracks container
    fNaccPart = fTracksCont->GetNAcceptedParticles();
    }

  // get clusters connected to jets
  fCaloClustersCont = fJetsCont->GetClusterContainer();
  if (fCaloClustersCont)
    {
    fCaloClustersCont->SetClassName ( "AliVCluster" );

    // get array of constituents
    fCaloClustContArray = fCaloClustersCont->GetArray();

    // accepted clusters in cluster container
    fNaccClus = fCaloClustersCont->GetNAcceptedClusters();
    }

  // Number of Jets found in event - accepted cuts applied by JetContainer
  fNJets_accepted = fJetsCont->GetNJets();

  // protection
  if ( ( fNJets_accepted < 1 ) || ( fNaccPart < 1 ) )
      {
      if ( fDebug > 1 )
          {
          std::cout << "accepted (fNJets || fNPart) == 0" << std::endl;
          }
      return kFALSE;
      }

  if ( fDebug > 1 )
      {
      std::cout << "fNJets = " << fNJets_accepted << " ; fNPart = " << fNaccPart << std::endl;
      }

  // Run analysis code here, if needed. It will be executed before FillHistograms().
  return kTRUE; // If return kFALSE FillHistogram() will NOT be executed.
  }

//________________________________________________________________________
Bool_t AliAnalysisTaskEmcalJetCDF::FillHistograms()
  {
  AliVParticle* track = NULL;
  AliEmcalJet*    jet = NULL;

  fH5->Fill ( fNJets_accepted ); // Distribution of jets in events;

  UShort_t counter_part = 0; Double_t counter_pt = 0.; // counter for npart and pt recording

  UShort_t jet_n90 = -99 ; Double_t jet_pt90 = -99.99 ;
  UShort_t jet_n85 = -99 ; Double_t jet_pt85 = -99.99 ;
  UShort_t jet_n80 = -99 ; Double_t jet_pt80 = -99.99 ;
  UShort_t jet_n75 = -99 ; Double_t jet_pt75 = -99.99 ;
  UShort_t jet_n70 = -99 ; Double_t jet_pt70 = -99.99 ;

  // variables used to compute g and ptD
  Double_t g_tot = 0.; Double_t sum_part_pt_tot = 0.; Double_t sum_part_pt2_tot = 0.;

  Double_t g_n90 = 0.; Double_t sum_part_pt_n90 = 0.; Double_t sum_part_pt2_n90 = 0.;
  Double_t g_n85 = 0.; Double_t sum_part_pt_n85 = 0.; Double_t sum_part_pt2_n85 = 0.;
  Double_t g_n80 = 0.; Double_t sum_part_pt_n80 = 0.; Double_t sum_part_pt2_n80 = 0.;
  Double_t g_n75 = 0.; Double_t sum_part_pt_n75 = 0.; Double_t sum_part_pt2_n75 = 0.;
  Double_t g_n70 = 0.; Double_t sum_part_pt_n70 = 0.; Double_t sum_part_pt2_n70 = 0.;

  Double_t g_pt90 = 0.; Double_t sum_part_pt_pt90 = 0.; Double_t sum_part_pt2_pt90 = 0.;
  Double_t g_pt85 = 0.; Double_t sum_part_pt_pt85 = 0.; Double_t sum_part_pt2_pt85 = 0.;
  Double_t g_pt80 = 0.; Double_t sum_part_pt_pt80 = 0.; Double_t sum_part_pt2_pt80 = 0.;
  Double_t g_pt75 = 0.; Double_t sum_part_pt_pt75 = 0.; Double_t sum_part_pt2_pt75 = 0.;
  Double_t g_pt70 = 0.; Double_t sum_part_pt_pt70 = 0.; Double_t sum_part_pt2_pt70 = 0.;

// **************************************************************
//                        ALL JETS
// **************************************************************
  // jet propreties
  Double_t jet_pt = 0. ; UShort_t jet_npart = 0; UShort_t jet_nconst = 0;

  // vector of sorted indexes of particles in jet
  std::vector< int > jet_sorted_idxvec ;

  fJetsCont->ResetCurrentID();
  while ( (jet = fJetsCont->GetNextAcceptJet()) )
    {
    Int_t track_idx = -999; // index variable for tracks

    // jet : Sorting by p_T jet constituents
    jet_sorted_idxvec = jet->SortConstituentsPt ( fTracksContArray );

    jet_pt = jet->Pt();
    jet_npart = jet->GetNumberOfTracks();
    jet_nconst = jet->GetNumberOfConstituents();

    g_tot = 0.; sum_part_pt_tot = 0.; sum_part_pt2_tot = 0.;

    g_n90 = 0.; sum_part_pt_n90 = 0.; sum_part_pt2_n90 = 0.;
    g_n85 = 0.; sum_part_pt_n85 = 0.; sum_part_pt2_n85 = 0.;
    g_n80 = 0.; sum_part_pt_n80 = 0.; sum_part_pt2_n80 = 0.;
    g_n75 = 0.; sum_part_pt_n75 = 0.; sum_part_pt2_n75 = 0.;
    g_n70 = 0.; sum_part_pt_n70 = 0.; sum_part_pt2_n70 = 0.;

    g_pt90 = 0.; sum_part_pt_pt90 = 0.; sum_part_pt2_pt90 = 0.;
    g_pt85 = 0.; sum_part_pt_pt85 = 0.; sum_part_pt2_pt85 = 0.;
    g_pt80 = 0.; sum_part_pt_pt80 = 0.; sum_part_pt2_pt80 = 0.;
    g_pt75 = 0.; sum_part_pt_pt75 = 0.; sum_part_pt2_pt75 = 0.;
    g_pt70 = 0.; sum_part_pt_pt70 = 0.; sum_part_pt2_pt70 = 0.;

    jet_n90  = ( UShort_t ) ( 0.9 * jet_npart );
    jet_pt90 = 0.9 * jet_pt;

    jet_n85  = ( UShort_t ) ( 0.85 * jet_npart );
    jet_pt85 = 0.85 * jet_pt;

    jet_n80  = ( UShort_t ) ( 0.8 * jet_npart );
    jet_pt80 = 0.8 * jet_pt;

    jet_n75  = ( UShort_t ) ( 0.75 * jet_npart );
    jet_pt75 = 0.75 * jet_pt;

    jet_n70  = ( UShort_t ) ( 0.7 * jet_npart );
    jet_pt70 = 0.7 * jet_pt;

    fH1->Fill ( jet_pt );            // Pt distribution of jets
    fH2->Fill ( jet->Eta() );        // Eta distribution of jets
    fH3->Fill ( jet->Phi() );        // Phi distribution of jets
    fH4->Fill ( jet_npart );         // Multiplicity of jets
    fH4c->Fill ( jet_nconst );       // Multiplicity of jets - all constituents
    fH7all->Fill ( jet_pt, jet_nconst ); // N(jet) vs P_{T} - all jets

    counter_part = 0; counter_pt = 0.; // reset counters

    for ( Size_t i = 0; i < jet_npart; i++ )
      {
      track_idx = jet_sorted_idxvec.at (i);
      track = jet->TrackAt ( track_idx, fTracksContArray );
      if (!track) { std::cout << "Parsing tracks of jets :: track not defined but it should!!!" << std::endl; continue; }

      Double_t dpart = jet->DeltaR ( track );
      Double_t track_pt = track->Pt();

      fH8_all->Fill   ( jet->GetZ  ( track ) );  // Momentum distribution for jets (FF)
      fH8xi_all->Fill ( jet->GetXi ( track ) );  // Momentum distribution for jets (FF) xi

      Double_t z_p = Z_ptot(jet,track);
      fH8_all_p->Fill   ( z_p );  // Momentum distribution for jets (FF)
      fH8xi_all_p->Fill ( Xi (z_p)  );  // Momentum distribution for jets (FF) xi

      Double_t z_pt = Z_pt(jet,track);
      fH8_all_pt->Fill   ( z_pt );  // Momentum distribution for jets (FF)
      fH8xi_all_pt->Fill ( Xi (z_pt) );  // Momentum distribution for jets (FF) xi

      fH20all->Fill ( dpart );                   // Distribution of R in leading jet

      fH15all->Fill ( dpart, track_pt );         // p_{T} track vs the Distance R from Jet1
      fH15all_bin->Fill ( dpart, track_pt );     // p_{T} track vs the Distance R from jet axis

      fH23all->Fill ( jet_pt, dpart );           //  Jet1 Size vs P_{T} - all jets

      // computing components for g and ptD in the jet tracks loop
      g_tot += (track_pt * dpart)/jet_pt;
      sum_part_pt_tot += track_pt;
      sum_part_pt2_tot += TMath::Power( track_pt, 2 );

//#############################################################################################
      if ( counter_part <= jet_n90 )         /// N90
          {
          fH15all_n90->Fill ( dpart, track_pt );         // p_{T} track vs the Distance R from Jet - 80% of particles
          fH15all_bin_n90->Fill ( dpart, track_pt );     // p_{T} track vs the Distance R from Jet - 80% of particles
          fH20all_n90->Fill ( dpart );                   //  Distribution of R in leading jet

          // computing components for g and ptD in the jet tracks loop
          g_n90 += (track_pt * dpart)/jet_pt;
          sum_part_pt_n90 += track_pt;
          sum_part_pt2_n90 += TMath::Power( track_pt, 2 );
          }

      if ( counter_pt <= jet_pt90 )         /// PT90
          {
          fH15all_pt90->Fill ( dpart, track_pt ); //  p_{T} track vs the Distance R from Jet - 80% of pt
          fH15all_bin_pt90->Fill ( dpart, track_pt ); //  p_{T} track vs the Distance R from Jet - 80% of pt
          fH20all_pt90->Fill ( dpart );               //  Distribution of R in leading jet

          // computing components for g and ptD in the jet tracks loop
          g_pt90 += (track_pt * dpart)/jet_pt;
          sum_part_pt_pt90 += track_pt;
          sum_part_pt2_pt90 += TMath::Power( track_pt, 2 );
          }

//#############################################################################################
      if ( counter_part <= jet_n85 )        /// N85
          {
          fH15all_n85->Fill ( dpart, track_pt ); // p_{T} track vs the Distance R from Jet - 80% of particles
          fH15all_bin_n85->Fill ( dpart, track_pt ); // p_{T} track vs the Distance R from Jet - 80% of particles
          fH20all_n85->Fill ( dpart );      //  Distribution of R in leading jet

          // computing components for g and ptD in the jet tracks loop
          g_n85 += (track_pt * dpart)/jet_pt;
          sum_part_pt_n85 += track_pt;
          sum_part_pt2_n85 += TMath::Power( track_pt, 2 );
          }

      if ( counter_pt <= jet_pt85 )        /// PT85
          {
          fH15all_pt85->Fill ( dpart, track_pt ); //  p_{T} track vs the Distance R from Jet - 80% of pt
          fH15all_bin_pt85->Fill ( dpart, track_pt ); //  p_{T} track vs the Distance R from Jet - 80% of pt
          fH20all_pt85->Fill ( dpart );               //  Distribution of R in leading jet

          // computing components for g and ptD in the jet tracks loop
          g_pt85 += (track_pt * dpart)/jet_pt;
          sum_part_pt_pt85 += track_pt;
          sum_part_pt2_pt85 += TMath::Power( track_pt, 2 );
          }

//#############################################################################################
      if ( counter_part <= jet_n80 )        /// N80
          {
          fH15all_n80->Fill ( dpart, track_pt ); // p_{T} track vs the Distance R from Jet - 80% of particles
          fH15all_bin_n80->Fill ( dpart, track_pt ); // p_{T} track vs the Distance R from Jet - 80% of particles
          fH20all_n80->Fill ( dpart );      //  Distribution of R in leading jet
          fH24all->Fill ( jet_pt, dpart ); //  Jet1 Size vs P_{T} - all jets - 80% of particles

          // computing components for g and ptD in the jet tracks loop
          g_n80 += (track_pt * dpart)/jet_pt;
          sum_part_pt_n80 += track_pt;
          sum_part_pt2_n80 += TMath::Power( track_pt, 2 );
          }

      if ( counter_pt <= jet_pt80 )         /// PT80
          {
          fH15all_pt80->Fill ( dpart, track_pt ); //  p_{T} track vs the Distance R from Jet - 80% of pt
          fH15all_bin_pt80->Fill ( dpart, track_pt ); //  p_{T} track vs the Distance R from Jet - 80% of pt
          fH20all_pt80->Fill ( dpart );               //  Distribution of R in leading jet
          fH25all->Fill ( jet_pt, dpart );             //  Jet1 Size vs P_{T} - all jets - 80% of Pt

          // computing components for g and ptD in the jet tracks loop
          g_pt80 += (track_pt * dpart)/jet_pt;
          sum_part_pt_pt80 += track_pt;
          sum_part_pt2_pt80 += TMath::Power( track_pt, 2 );
          }

//#############################################################################################
      if ( counter_part <= jet_n75 )        /// N75
          {
          fH15all_n75->Fill ( dpart, track_pt ); // p_{T} track vs the Distance R from Jet - 80% of particles
          fH15all_bin_n75->Fill ( dpart, track_pt ); // p_{T} track vs the Distance R from Jet - 80% of particles
          fH20all_n75->Fill ( dpart );      //  Distribution of R in leading jet

          // computing components for g and ptD in the jet tracks loop
          g_n75 += (track_pt * dpart)/jet_pt;
          sum_part_pt_n75 += track_pt;
          sum_part_pt2_n75 += TMath::Power( track_pt, 2 );
          }

      if ( counter_pt <= jet_pt75 )         /// PT75
          {
          fH15all_pt75->Fill ( dpart, track_pt ); //  p_{T} track vs the Distance R from Jet - 80% of pt
          fH15all_bin_pt75->Fill ( dpart, track_pt ); //  p_{T} track vs the Distance R from Jet - 80% of pt
          fH20all_pt75->Fill ( dpart );               //  Distribution of R in leading jet

          // computing components for g and ptD in the jet tracks loop
          g_pt75 += (track_pt * dpart)/jet_pt;
          sum_part_pt_pt75 += track_pt;
          sum_part_pt2_pt75 += TMath::Power( track_pt, 2 );
          }

//#############################################################################################
      if ( counter_part <= jet_n70 )       /// N70
          {
          fH15all_n70->Fill ( dpart, track_pt ); // p_{T} track vs the Distance R from Jet - 80% of particles
          fH15all_bin_n70->Fill ( dpart, track_pt ); // p_{T} track vs the Distance R from Jet - 80% of particles
          fH20all_n80->Fill ( dpart );      //  Distribution of R in leading jet

          // computing components for g and ptD in the jet tracks loop
          g_n70 += (track_pt * dpart)/jet_pt;
          sum_part_pt_n70 += track_pt;
          sum_part_pt2_n70 += TMath::Power( track_pt, 2 );
          }

      if ( counter_pt <= jet_pt70 )        /// PT70
          {
          fH15all_pt70->Fill ( dpart, track_pt ); //  p_{T} track vs the Distance R from Jet - 80% of pt
          fH15all_bin_pt70->Fill ( dpart, track_pt ); //  p_{T} track vs the Distance R from Jet - 80% of pt
          fH20all_pt70->Fill ( dpart );               //  Distribution of R in leading jet

          // computing components for g and ptD in the jet tracks loop
          g_pt70 += (track_pt * dpart)/jet_pt;
          sum_part_pt_pt70 += track_pt;
          sum_part_pt2_pt70 += TMath::Power( track_pt, 2 );
          }
      ++counter_part; counter_pt += track_pt;
      } // end of loop over jet tracks

    fHg->Fill     ( g_tot );
    fHg_n70->Fill ( g_n70 );    fHg_pt70->Fill ( g_pt70 );
    fHg_n75->Fill ( g_n75 );    fHg_pt75->Fill ( g_pt75 );
    fHg_n80->Fill ( g_n80 );    fHg_pt80->Fill ( g_pt80 );
    fHg_n85->Fill ( g_n85 );    fHg_pt85->Fill ( g_pt85 );
    fHg_n90->Fill ( g_n90 );    fHg_pt90->Fill ( g_pt90 );

    fHptd->Fill( TMath::Sqrt(sum_part_pt2_tot)/sum_part_pt_tot );

    fHptd->Fill( TMath::Sqrt(sum_part_pt2_n70)/sum_part_pt_n70 );
    fHptd->Fill( TMath::Sqrt(sum_part_pt2_n75)/sum_part_pt_n75 );
    fHptd->Fill( TMath::Sqrt(sum_part_pt2_n80)/sum_part_pt_n80 );
    fHptd->Fill( TMath::Sqrt(sum_part_pt2_n85)/sum_part_pt_n85 );
    fHptd->Fill( TMath::Sqrt(sum_part_pt2_n90)/sum_part_pt_n90 );

    fHptd->Fill( TMath::Sqrt(sum_part_pt2_pt70)/sum_part_pt_pt70 );
    fHptd->Fill( TMath::Sqrt(sum_part_pt2_pt75)/sum_part_pt_pt75 );
    fHptd->Fill( TMath::Sqrt(sum_part_pt2_pt80)/sum_part_pt_pt80 );
    fHptd->Fill( TMath::Sqrt(sum_part_pt2_pt85)/sum_part_pt_pt85 );
    fHptd->Fill( TMath::Sqrt(sum_part_pt2_pt90)/sum_part_pt_pt90 );

    jet = fJetsCont->GetNextAcceptJet();
    jet_sorted_idxvec.clear();
    } // end of loop over jets

  jet = NULL; track = NULL;

// **************************************************************
//                          LEADING JETS
// **************************************************************
  AliEmcalJet* jet1 = fJetsCont->GetLeadingJet(); // internaly checked for AcceptedJet

  if ( fDebug > 1 )
    {
    if (jet1)
      {
      std::cout << "+++++++++++++++++>>>>>>>>> Leading jet found" << std::endl;
      jet1->Print();
      }
    else
      { Printf ( "Jet1 not found (did not survive cuts?)\n" ); }
    }

  if (jet1)
    {
    //vector of sorted indexes of particles in leading jet
    std::vector< int > jet1_sorted_idxvec;

    // jet1 : Sorting by p_T jet constituents
    jet1_sorted_idxvec = jet1->SortConstituentsPt ( fTracksContArray );

    Int_t track_idx = -999;            // index variable for tracks
    Double_t jet1_pt = jet1->Pt();
    UInt_t jet1_npart = jet1->GetNumberOfTracks();
    UInt_t jet1_nconst = jet1->GetNumberOfConstituents();

    UShort_t jet1_n90  = ( UShort_t ) ( 0.9 * jet1_npart );
    Double_t jet1_pt90 = 0.9 * jet1_pt;

    UShort_t jet1_n85  = ( UShort_t ) ( 0.85 * jet1_npart );
    Double_t jet1_pt85 = 0.85 * jet1_pt;

    UShort_t jet1_n80  = ( UShort_t ) ( 0.8 * jet1_npart );
    Double_t jet1_pt80 = 0.8 * jet1_pt;

    UShort_t jet1_n75  = ( UShort_t ) ( 0.75 * jet1_npart );
    Double_t jet1_pt75 = 0.75 * jet1_pt;

    UShort_t jet1_n70  = ( UShort_t ) ( 0.7 * jet1_npart );
    Double_t jet1_pt70 = 0.7 * jet1_pt;

    fH6->Fill  ( jet1_npart );        // Multiplicity of jet1 - charged tracks
    fH6c->Fill ( jet1_nconst );       // Multiplicity of jet1 - all constituents
    fH7->Fill ( jet1_pt, jet1_nconst ); // N(jet) vs P_{T}(jet1)

    counter_part = 0; counter_pt = 0.; // reset counters

    //___________________________________________________________________________
    // parsing tracks of jet1 (leading jet) in decreasing order of Pt

    for ( Size_t i = 0; i < jet1_npart; i++ )
        {
        track_idx = jet1_sorted_idxvec.at (i);
        track = jet1->TrackAt ( track_idx, fTracksContArray );
        if (!track) { std::cout << "Parsing tracks of jet1 :: track not defined but it should!!!" << std::endl; continue; }

        Double_t dpart = jet1->DeltaR ( track );
        Double_t track_pt = track->Pt();

        fH8->Fill   ( jet1->GetZ  ( track ) );  // Momentum distribution for leading jet (FF)
        fH8xi->Fill ( jet1->GetXi ( track ) );  // Momentum distribution for leading jet (FF) xi

        Double_t z_p = Z_ptot(jet1, track);
        fH8_p->Fill   ( z_p );  // Momentum distribution for jets (FF)
        fH8xi_p->Fill ( Xi (z_p)  );  // Momentum distribution for jets (FF) xi

        Double_t z_pt = Z_pt(jet1, track);
        fH8_pt->Fill   ( z_pt );  // Momentum distribution for jets (FF)
        fH8xi_pt->Fill ( Xi (z_pt) );  // Momentum distribution for jets (FF) xi

        fH20->Fill ( dpart );                    // Distribution of R in leading jet
        fH15->Fill ( dpart, track_pt );          // <p_{T}> track vs the Distance R from Jet1
        fH15_bin->Fill ( dpart, track_pt );      // p_{T} sum track vs the Distance R from Jet1

        fH23->Fill ( jet1_pt, dpart );           //  Jet1 Size vs P_{T}(jet1)

        // fill histograms for 70% of particles with highest pt
        if ( counter_part <= jet1_n70 )
            {
            fH15_n70->Fill ( dpart, track_pt );     // <p_{T}> track vs the Distance R from Jet1 - 80% of particles
            fH15_bin_n70->Fill ( dpart, track_pt ); // p_{T} sum track vs the Distance R from Jet1 - 80% of particles
            fH20_n70->Fill ( dpart );               // Distribution of R in leading jet
            }
        // fill histograms for 75% of particles with highest pt
        if ( counter_part <= jet1_n75 )
            {
            fH15_n75->Fill ( dpart, track_pt );     // <p_{T}> track vs the Distance R from Jet1 - 80% of particles
            fH15_bin_n75->Fill ( dpart, track_pt ); // p_{T} sum track vs the Distance R from Jet1 - 80% of particles
            fH20_n75->Fill ( dpart );               //  Distribution of R in leading jet
            }
        // fill histograms for 80% of particles with highest pt
        if ( counter_part <= jet1_n80 )
            {
            fH15_n80->Fill ( dpart, track_pt );     // <p_{T}> track vs the Distance R from Jet1 - 80% of particles
            fH15_bin_n80->Fill ( dpart, track_pt ); // p_{T} sum track vs the Distance R from Jet1 - 80% of particles
            fH20_n80->Fill ( dpart );               // Distribution of R in leading jet
            fH24->Fill ( jet1_pt, dpart );          // Jet1 Size vs P_{T}(jet1) - 80% of particles
            }
        // fill histograms for 85% of particles with highest pt
        if ( counter_part <= jet1_n85 )
            {
            fH15_n85->Fill ( dpart, track_pt );     // <p_{T}> track vs the Distance R from Jet1 - 80% of particles
            fH15_bin_n85->Fill ( dpart, track_pt ); // p_{T} sum track vs the Distance R from Jet1 - 80% of particles
            fH20_n85->Fill ( dpart );               //  Distribution of R in leading jet
            }
        // fill histograms for 90% of particles with highest pt
        if ( counter_part <= jet1_n90 )
            {
            fH15_n90->Fill ( dpart, track_pt );     // <p_{T}> track vs the Distance R from Jet1 - 80% of particles
            fH15_bin_n90->Fill ( dpart, track_pt ); // p_{T} sum track vs the Distance R from Jet1 - 80% of particles
            fH20_n90->Fill ( dpart );               //  Distribution of R in leading jet
            }

        // fill histograms for particles that have first 70% of pt
        if ( counter_pt <= jet1_pt70 )
            {
            fH15_pt70->Fill ( dpart, track_pt );     //  <p_{T}> track vs the Distance R from Jet1 - 80% of pt
            fH15_bin_pt70->Fill ( dpart, track_pt ); //  p_{T} sum track vs the Distance R from Jet1 - 80% of pt
            fH20_pt70->Fill ( dpart );               //  Distribution of R in leading jet
            }
        // fill histograms for particles that have first 75% of pt
        if ( counter_pt <= jet1_pt75 )
            {
            fH15_pt75->Fill ( dpart, track_pt );     //  <p_{T}> track vs the Distance R from Jet1 - 80% of pt
            fH15_bin_pt75->Fill ( dpart, track_pt ); //  p_{T} sum track vs the Distance R from Jet1 - 80% of pt
            fH20_pt75->Fill ( dpart );               //  Distribution of R in leading jet
            }
        // fill histograms for particles that have first 80% of pt
        if ( counter_pt <= jet1_pt80 )
            {
            fH15_pt80->Fill ( dpart, track_pt );     //  <p_{T}> track vs the Distance R from Jet1 - 80% of pt
            fH15_bin_pt80->Fill ( dpart, track_pt ); //  p_{T} sum track vs the Distance R from Jet1 - 80% of pt
            fH20_pt80->Fill ( dpart );     //  Distribution of R in leading jet
            fH25->Fill ( jet1_pt, dpart ); //  Jet1 Size vs P_{T}(jet1) - 80% of Pt
            }
        // fill histograms for particles that have first 80% of pt
        if ( counter_pt <= jet1_pt85 )
            {
            fH15_pt85->Fill ( dpart, track_pt );     //  <p_{T}> track vs the Distance R from Jet1 - 80% of pt
            fH15_bin_pt85->Fill ( dpart, track_pt ); //  p_{T} sum track vs the Distance R from Jet1 - 80% of pt
            fH20_pt85->Fill ( dpart );     //  Distribution of R in leading jet
            }
        // fill histograms for particles that have first 80% of pt
        if ( counter_pt <= jet1_pt90 )
            {
            fH15_pt90->Fill ( dpart, track_pt );     //  <p_{T}> track vs the Distance R from Jet1 - 80% of pt
            fH15_bin_pt90->Fill ( dpart, track_pt ); //  p_{T} sum track vs the Distance R from Jet1 - 80% of pt
            fH20_pt90->Fill ( dpart );     //  Distribution of R in leading jet
            }

        ++counter_part; counter_pt += track_pt;
        } // end of loop over jet1 tracks
    jet1_sorted_idxvec.clear();
    } // end of jet1 (leading jet) processing


  track = NULL; jet1 = NULL;

  // post data at every processing
  PostData ( 1, fOutput ); // Post data for ALL output slots > 0 here.
  return kTRUE;
  }

//________________________________________________________________________
void AliAnalysisTaskEmcalJetCDF::UserCreateOutputObjects()
  {
  // Create user output.
  AliAnalysisTaskEmcalJet::UserCreateOutputObjects();

  TString histname = "", histtitle = "", groupname = "";
  AliJetContainer* jetCont = 0;
  TIter next(&fJetCollArray);
  while ((jetCont = static_cast<AliJetContainer*>(next())))
    {
    groupname = jetCont->GetName();
    fHistManager.CreateHistoGroup(groupname);
    for (Int_t cent = 0; cent < fNcentBins; cent++)
      {
      Int_t h1_nbin = 200; Double_t h1_binwidth = 1; Double_t h1_low = 0;
      Double_t h1_high = h1_low + h1_binwidth * h1_nbin; // 1GeV/bin
      histname = TString::Format("%s/histo1_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s;#it{p}_{T,jet} (GeV/#it{c}) (accepted);Jets", histname.Data()); // Pt distro of jets
      fHistManager.CreateTH1(histname, histtitle, h1_nbin, h1_low, h1_high);

      Int_t h2_nbin = 200; Double_t h2_binwidth = 0.01; Double_t h2_low = -1;
      Double_t h2_high = h2_low + h2_binwidth * h2_nbin;
      histname = TString::Format("%s/histo2_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s;#it{#eta}_{jet};Jets", histname.Data());  // Eta distro of jets
      fHistManager.CreateTH1(histname, histtitle, h2_nbin, h2_low, h2_high); // 1 unit of rapidity / 100 bin

      Int_t h3_nbin = 126; Double_t h3_binwidth = 0.05; Double_t h3_low = 0.;
      Double_t h3_high = h3_low + h3_binwidth * h3_nbin;
      histname = TString::Format("%s/histo3_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s;#it{#phi}_{jet};Jets", histname.Data()); // Phi distro of jets
      fHistManager.CreateTH1(histname, histtitle, h3_nbin, h3_low, h3_high);

      //#####################################
      Int_t h4_nbin = 100; Double_t h4_binwidth = 1; Double_t h4_low = 0;
      Double_t h4_high = h4_low + h4_binwidth * h4_nbin; // 1 unit of multiplicity /bin
      histname = TString::Format("%s/histo4_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s;N_{tracks}(jet);Jets", histname.Data()); // Multiplicity of jets; chg tracks
      fHistManager.CreateTH1(histname, histtitle, h4_nbin, h4_low, h4_high);

      histname = TString::Format("%s/histo4c_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s;N_{tracks}(jet);Jets", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h4_nbin, h4_low, h4_high); // Multiplicity of jets; all tracks

      histname = TString::Format("%s/histo6_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s;N_{tracks}(jet1);Jets", histname.Data()); // Multiplicity of jet1; chg tracks
      fHistManager.CreateTH1(histname, histtitle, h4_nbin, h4_low, h4_high);

      histname = TString::Format("%s/histo6c_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s;N_{tracks}(jet1);Jets", histname.Data()); // Multiplicity of jet1; all tracks
      fHistManager.CreateTH1(histname, histtitle, h4_nbin, h4_low, h4_high);
      //#####################################

      Int_t h5_nbin = 200; Double_t h5_binwidth = 1; Double_t h5_low = 0;
      Double_t h5_high = h5_low + h5_binwidth * h5_nbin;
      histname = TString::Format("%s/histo5_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s;N_{jets};Events", histname.Data()); // Distribution of jets in events
      fHistManager.CreateTH1(histname, histtitle, h5_nbin, h5_low, h5_high);

      //#####################################
      Int_t h7_xnbin = 100; Double_t h7_xbinwidth = 1; Double_t h7_xlow = 0;
      Double_t h7_xhigh = h7_xlow + h7_xbinwidth * h7_xnbin;
      Int_t h7_ynbin = 200; Double_t h7_ybinwidth = 1; Double_t h7_ylow = 0;
      Double_t h7_yhigh = h7_ylow + h7_ybinwidth * h7_ynbin;

      histname = TString::Format("%s/histo7_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s;#it{p}_{T,jet1} (GeV/c);N_{tracks}(jet1)", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h7_xnbin, h7_xlow, h7_xhigh, h7_ynbin, h7_ylow, h7_yhigh);

      histname = TString::Format("%s/histo7all_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s;#it{p}_{T,jet} (GeV/c);N_{tracks}(jets)", histname.Data()); // N vs pt all jets
      fHistManager.CreateTH2(histname, histtitle, h7_xnbin, h7_xlow, h7_xhigh, h7_ynbin, h7_ylow, h7_yhigh);
      //#####################################

      //########################################################
      Int_t h8_nbin = 101; Double_t h8_binwidth = 0.01; Double_t h8_low = 0;
      Double_t h8_high = h8_low + h8_binwidth * h8_nbin;

      // Standard implementation of Z
      histname = TString::Format("%s/histo8_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;z;F(Z) = 1/N_{jet1} dN/dz", histname.Data()); // scalar z ; jet1
      fHistManager.CreateTH1(histname, histtitle, h8_nbin, h8_low, h8_high);

      histname = TString::Format("%s/histo8_all_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;z;F(Z) = 1/N_{jets} dN/dz", histname.Data()); // scalar z ; all jets
      fHistManager.CreateTH1(histname, histtitle, h8_nbin, h8_low, h8_high);

      //########################################################
      // P_tot implementation of Z
      histname = TString::Format("%s/histo8_p_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1 P_tot;z = p_{track}/p_{jet1};F(Z) = 1/N_{jet1} dN/dz", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h8_nbin, h8_low, h8_high);

      histname = TString::Format("%s/histo8_all_p_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets P_tot;z = p_{track}/p_{jet};F(Z) = 1/N_{jets} dN/dz", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h8_nbin, h8_low, h8_high);

      //########################################################
      // Pt implementation of Z
      histname = TString::Format("%s/histo8_pt_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1 Pt;z = p_{T,track}/p_{T,jet1};F(Z) = 1/N_{jet1} dN/dz", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h8_nbin, h8_low, h8_high);

      histname = TString::Format("%s/histo8_all_pt_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets Pt;z = p_{T,track}/p_{T,jet1};F(Z) = 1/N_{jets} dN/dz", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h8_nbin, h8_low, h8_high);
      //########################################################

      //########################################################
      Int_t h8xi_nbin = 300; Double_t h8xi_binwidth = 0.05; Double_t h8xi_low = 0;
      Double_t h8xi_high = h8xi_low + h8xi_binwidth * h8xi_nbin;
      histname = TString::Format("%s/histo8xi_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;#xi = ln(1/z);D(#xi) = 1/N_{jet1} dN/d#xi", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h8xi_nbin, h8xi_low, h8xi_high);

      histname = TString::Format("%s/histo8xi_all_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;#xi = ln(1/z);D(#xi) = 1/N_{jets} dN/d#xi", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h8xi_nbin, h8xi_low, h8xi_high);

      //########################################################
      histname = TString::Format("%s/histo8xi_p_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1 P_tot;#xi = ln(1/z);D(#xi) = 1/N_{jet1} dN/d#xi", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h8xi_nbin, h8xi_low, h8xi_high);

      histname = TString::Format("%s/histo8xi_all_p_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets P_tot;#xi = ln(1/z);D(#xi) = 1/N_{jets} dN/d#xi", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h8xi_nbin, h8xi_low, h8xi_high);

      //########################################################
      histname = TString::Format("%s/histo8xi_pt_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1 Pt;#xi = ln(1/z);D(#xi) = 1/N_{jet1} dN/d#xi", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h8xi_nbin, h8xi_low, h8xi_high);

      histname = TString::Format("%s/histo8xi_all_pt_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets Pt;#xi = ln(1/z);D(#xi) = 1/N_{jets} dN/d#xi", histname.Data());
      fHistManager.CreateTH1(histname, histtitle, h8xi_nbin, h8xi_low, h8xi_high);
      //########################################################

      //########################################################
      Int_t h15_xnbin = 100; Double_t h15_xbinwidth = 0.01; Double_t h15_xlow = 0.;
      Double_t h15_xhigh = h15_xlow + h15_xbinwidth * h15_xnbin;
      Int_t h15_ynbin = 1000; Double_t h15_ybinwidth = 1.; Double_t h15_ylow = 0.;
      Double_t h15_yhigh = h15_ylow + h15_ybinwidth * h15_ynbin;
      //########################################################

      histname = TString::Format("%s/histo15_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15_n70_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15_n75_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15_n80_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15_n85_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15_n90_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      //=====================================================================================
      histname = TString::Format("%s/histo15_pt70_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15_pt75_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15_pt80_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15_pt85_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15_pt90_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - jet1;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      //___________________________________________
      histname = TString::Format("%s/histo15all_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15all_n70_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15all_n75_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15all_n80_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15all_n85_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15all_n90_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      //=====================================================================================
      histname = TString::Format("%s/histo15all_pt70_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15all_pt75_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15all_pt80_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15all_pt85_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);

      histname = TString::Format("%s/histo15all_pt90_%d", groupname.Data(), cent);
      histtitle = TString::Format("%s - all jets;dR;<p_{T}> track", histname.Data()); // N vs pt jet1
      fHistManager.CreateTH2(histname, histtitle, h15_xnbin, h15_xlow, h15_xhigh, h15_ynbin, h15_ylow, h15_yhigh);




/// TODO

// DE VAZUT DACA LA TH2 PE LINGA PROFIL SE POATE FACE SI SUMA PE O AXA







      }
    }




    //____________________________________________________________________________________
      fH15_bin = new TH1D ( "histo15_bin", "p_{T} SUM (track) in dR(jet1)", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin->GetXaxis()->SetTitle ( " R" );
      fH15_bin->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );


    //=====================================================================================
      fH15_bin_n70 = new TH1D ( "histo15_bin_n70", "p_{T} SUM (track) in dR(jet1) - 70% of particles", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin_n70->GetXaxis()->SetTitle ( "R" );
      fH15_bin_n70->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15_bin_n75 = new TH1D ( "histo15_bin_n75", "p_{T} SUM (track) in dR(jet1) - 75% of particles", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin_n75->GetXaxis()->SetTitle ( "R" );
      fH15_bin_n75->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15_bin_n80 = new TH1D ( "histo15_bin_n80", "p_{T} SUM (track) in dR(jet1) - 80% of particles", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin_n80->GetXaxis()->SetTitle ( "R" );
      fH15_bin_n80->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15_bin_n85 = new TH1D ( "histo15_bin_n85", "p_{T} SUM (track) in dR(jet1) - 85% of particles", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin_n85->GetXaxis()->SetTitle ( "R" );
      fH15_bin_n85->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15_bin_n90 = new TH1D ( "histo15_bin_n90", "p_{T} SUM (track) in dR(jet1) - 90% of particles", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin_n90->GetXaxis()->SetTitle ( "R" );
      fH15_bin_n90->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

    //=====================================================================================
      fH15_bin_pt70 = new TH1D ( "histo15_bin_pt70", "p_{T} SUM (track) in dR(jet1) - 70% of Pt", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin_pt70->GetXaxis()->SetTitle ( "R" );
      fH15_bin_pt70->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15_bin_pt75 = new TH1D ( "histo15_bin_pt75", "p_{T} SUM (track) in dR(jet1) - 75% of Pt", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin_pt75->GetXaxis()->SetTitle ( "R" );
      fH15_bin_pt75->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15_bin_pt80 = new TH1D ( "histo15_bin_pt80", "p_{T} SUM (track) in dR(jet1) - 80% of Pt", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin_pt80->GetXaxis()->SetTitle ( "R" );
      fH15_bin_pt80->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15_bin_pt85 = new TH1D ( "histo15_bin_pt85", "p_{T} SUM (track) in dR(jet1) - 85% of Pt", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin_pt85->GetXaxis()->SetTitle ( "R" );
      fH15_bin_pt85->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15_bin_pt90 = new TH1D ( "histo15_bin_pt90", "p_{T} SUM (track) in dR(jet1) - 90% of Pt", h15_nbin, h15_xlow, h15_xhigh );
      fH15_bin_pt90->GetXaxis()->SetTitle ( "R" );
      fH15_bin_pt90->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );


    //____________________________________________________________________________________
      fH15all_bin = new TH1D ( "histo15_bin_all", "p_{T} SUM (track) in dR (jet)", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin->GetXaxis()->SetTitle ( "R" );
      fH15all_bin->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

    //=====================================================================================
      fH15all_bin_n70 = new TH1D ( "histo15_bin_n70_all", "p_{T} SUM (track) in dR (jet) - 70% of particles", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin_n70->GetXaxis()->SetTitle ( "R" );
      fH15all_bin_n70->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15all_bin_n75 = new TH1D ( "histo15_bin_n75_all", "p_{T} SUM (track) in dR (jet) - 75% of particles", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin_n75->GetXaxis()->SetTitle ( "R" );
      fH15all_bin_n75->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15all_bin_n80 = new TH1D ( "histo15_bin_n80_all", "p_{T} SUM (track) in dR (jet) - 80% of particles", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin_n80->GetXaxis()->SetTitle ( "R" );
      fH15all_bin_n80->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15all_bin_n85 = new TH1D ( "histo15_bin_n85_all", "p_{T} SUM (track) in dR (jet) - 85% of particles", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin_n85->GetXaxis()->SetTitle ( "R" );
      fH15all_bin_n85->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15all_bin_n90 = new TH1D ( "histo15_bin_n90_all", "p_{T} SUM (track) in dR (jet) - 90% of particles", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin_n90->GetXaxis()->SetTitle ( "R" );
      fH15all_bin_n90->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

    //=====================================================================================
      fH15all_bin_pt70 = new TH1D ( "histo15_bin_pt70_all", "p_{T} SUM (track) in dR (jet) - 70% of Pt", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin_pt70->GetXaxis()->SetTitle ( "R" );
      fH15all_bin_pt70->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15all_bin_pt75 = new TH1D ( "histo15_bin_pt75_all", "p_{T} SUM (track) in dR (jet) - 75% of Pt", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin_pt75->GetXaxis()->SetTitle ( "R" );
      fH15all_bin_pt75->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15all_bin_pt80 = new TH1D ( "histo15_bin_pt80_all", "p_{T} SUM (track) in dR (jet) - 80% of Pt", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin_pt80->GetXaxis()->SetTitle ( "R" );
      fH15all_bin_pt80->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15all_bin_pt85 = new TH1D ( "histo15_bin_pt85_all", "p_{T} SUM (track) in dR (jet) - 85% of Pt", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin_pt85->GetXaxis()->SetTitle ( "R" );
      fH15all_bin_pt85->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

      fH15all_bin_pt90 = new TH1D ( "histo15_bin_pt90_all", "p_{T} SUM (track) in dR (jet) - 90% of Pt", h15_nbin, h15_xlow, h15_xhigh );
      fH15all_bin_pt90->GetXaxis()->SetTitle ( "R" );
      fH15all_bin_pt90->GetYaxis()->SetTitle ( "p_{T} SUM (track)" );

    //____________________________________________________________________________________
      Int_t h20_nbin = 100;
      Double_t h20_binwidth = 0.01;
      Double_t h20_low = 0.;
      Double_t h20_high = h20_low + h20_binwidth * h20_nbin;
      fH20 = new TH1D ( "histo20", "dN/dR (jet1)", h20_nbin, h20_low, h20_high );
      fH20->GetXaxis()->SetTitle ( "R" );
      fH20->GetYaxis()->SetTitle ( "dN/dR" );

    //=====================================================================================
      fH20_n70 = new TH1D ( "histo20_n70", "dN/dR (jet1) - 70% of particles", h20_nbin, h20_low, h20_high );
      fH20_n70->GetXaxis()->SetTitle ( "R" );
      fH20_n70->GetYaxis()->SetTitle ( "dN/dR" );

      fH20_n75 = new TH1D ( "histo20_n75", "dN/dR (jet1) - 75% of particles", h20_nbin, h20_low, h20_high );
      fH20_n75->GetXaxis()->SetTitle ( "R" );
      fH20_n75->GetYaxis()->SetTitle ( "dN/dR" );

      fH20_n80 = new TH1D ( "histo20_n80", "dN/dR (jet1) - 80% of particles", h20_nbin, h20_low, h20_high );
      fH20_n80->GetXaxis()->SetTitle ( "R" );
      fH20_n80->GetYaxis()->SetTitle ( "dN/dR" );

      fH20_n85 = new TH1D ( "histo20_n85", "dN/dR (jet1) - 85% of particles", h20_nbin, h20_low, h20_high );
      fH20_n85->GetXaxis()->SetTitle ( "R" );
      fH20_n85->GetYaxis()->SetTitle ( "dN/dR" );

      fH20_n90 = new TH1D ( "histo20_n90", "dN/dR (jet1) - 90% of particles", h20_nbin, h20_low, h20_high );
      fH20_n90->GetXaxis()->SetTitle ( "R" );
      fH20_n90->GetYaxis()->SetTitle ( "dN/dR" );

    //=====================================================================================
      fH20_pt70 = new TH1D ( "histo20_pt70", "dN/dR (jet1) - 70% of Pt", h20_nbin, h20_low, h20_high );
      fH20_pt70->GetXaxis()->SetTitle ( "R" );
      fH20_pt70->GetYaxis()->SetTitle ( "dN/dR" );

      fH20_pt75 = new TH1D ( "histo20_pt75", "dN/dR (jet1) - 75% of Pt", h20_nbin, h20_low, h20_high );
      fH20_pt75->GetXaxis()->SetTitle ( "R" );
      fH20_pt75->GetYaxis()->SetTitle ( "dN/dR" );

      fH20_pt80 = new TH1D ( "histo20_pt80", "dN/dR (jet1) - 80% of Pt", h20_nbin, h20_low, h20_high );
      fH20_pt80->GetXaxis()->SetTitle ( "R" );
      fH20_pt80->GetYaxis()->SetTitle ( "dN/dR" );

      fH20_pt85 = new TH1D ( "histo20_pt85", "dN/dR (jet1) - 85% of Pt", h20_nbin, h20_low, h20_high );
      fH20_pt85->GetXaxis()->SetTitle ( "R" );
      fH20_pt85->GetYaxis()->SetTitle ( "dN/dR" );

      fH20_pt90 = new TH1D ( "histo20_pt90", "dN/dR (jet1) - 90% of Pt", h20_nbin, h20_low, h20_high );
      fH20_pt90->GetXaxis()->SetTitle ( "R" );
      fH20_pt90->GetYaxis()->SetTitle ( "dN/dR" );


    //____________________________________________________________________________________
      fH20all = new TH1D ( "histo20_all", "dN/dR - all jets", h20_nbin, h20_low, h20_high );
      fH20all->GetXaxis()->SetTitle ( "R" );
      fH20all->GetYaxis()->SetTitle ( "dN/dR" );


    //=====================================================================================
      fH20all_n70 = new TH1D ( "histo20_n70_all", "dN/dR - all jets - 70% of particles", h20_nbin, h20_low, h20_high );
      fH20all_n70->GetXaxis()->SetTitle ( "R" );
      fH20all_n70->GetYaxis()->SetTitle ( "dN/dR" );

      fH20all_n75 = new TH1D ( "histo20_n75_all", "dN/dR - all jets - 75% of particles", h20_nbin, h20_low, h20_high );
      fH20all_n75->GetXaxis()->SetTitle ( "R" );
      fH20all_n75->GetYaxis()->SetTitle ( "dN/dR" );

      fH20all_n80 = new TH1D ( "histo20_n80_all", "dN/dR - all jets - 80% of particles", h20_nbin, h20_low, h20_high );
      fH20all_n80->GetXaxis()->SetTitle ( "R" );
      fH20all_n80->GetYaxis()->SetTitle ( "dN/dR" );

      fH20all_n85 = new TH1D ( "histo20_n85_all", "dN/dR - all jets - 85% of particles", h20_nbin, h20_low, h20_high );
      fH20all_n85->GetXaxis()->SetTitle ( "R" );
      fH20all_n85->GetYaxis()->SetTitle ( "dN/dR" );

      fH20all_n90 = new TH1D ( "histo20_n90_all", "dN/dR - all jets - 90% of particles", h20_nbin, h20_low, h20_high );
      fH20all_n90->GetXaxis()->SetTitle ( "R" );
      fH20all_n90->GetYaxis()->SetTitle ( "dN/dR" );

    //=====================================================================================
      fH20all_pt70 = new TH1D ( "histo20_pt70_all", "dN/dR - all jets - 70% of Pt", h20_nbin, h20_low, h20_high );
      fH20all_pt70->GetXaxis()->SetTitle ( "R" );
      fH20all_pt70->GetYaxis()->SetTitle ( "dN/dR" );

      fH20all_pt75 = new TH1D ( "histo20_pt75_all", "dN/dR - all jets - 75% of Pt", h20_nbin, h20_low, h20_high );
      fH20all_pt75->GetXaxis()->SetTitle ( "R" );
      fH20all_pt75->GetYaxis()->SetTitle ( "dN/dR" );

      fH20all_pt80 = new TH1D ( "histo20_pt80_all", "dN/dR - all jets - 80% of Pt", h20_nbin, h20_low, h20_high );
      fH20all_pt80->GetXaxis()->SetTitle ( "R" );
      fH20all_pt80->GetYaxis()->SetTitle ( "dN/dR" );

      fH20all_pt85 = new TH1D ( "histo20_pt85_all", "dN/dR - all jets - 85% of Pt", h20_nbin, h20_low, h20_high );
      fH20all_pt85->GetXaxis()->SetTitle ( "R" );
      fH20all_pt85->GetYaxis()->SetTitle ( "dN/dR" );

      fH20all_pt90 = new TH1D ( "histo20_pt90_all", "dN/dR - all jets - 90% of Pt", h20_nbin, h20_low, h20_high );
      fH20all_pt90->GetXaxis()->SetTitle ( "R" );
      fH20all_pt90->GetYaxis()->SetTitle ( "dN/dR" );

      //____________________________________________________________________________________
      Int_t h23_nbin = 400;
      Double_t h23_binwidth = 1.;
      Double_t h23_low = 0.;
      Double_t h23_high = h23_low + h23_binwidth * h23_nbin;

      fH23 = new TProfile ( "histo23", "Jet1 Size vs P_{T}(jet1)", h23_nbin, h23_low, h23_high );
      fH23->GetXaxis()->SetTitle ( "p_{T}(jet1) (GeV/c)" );
      fH23->GetYaxis()->SetTitle ( "<R(jet1)> in 1 GeV/c bin" );

      fH24 = new TProfile ( "histo24", "Jet1 Size vs P_{T}(jet1) - 80% of particles", h23_nbin, h23_low, h23_high );
      fH24->GetXaxis()->SetTitle ( "p_{T}(jet1) (GeV/c)" );
      fH24->GetYaxis()->SetTitle ( "<R(jet1)> in 1 GeV/c bin" );

      fH25 = new TProfile ( "histo25", "Jet1 Size vs P_{T}(jet1) - 80% of Pt", h23_nbin, h23_low, h23_high );
      fH25->GetXaxis()->SetTitle ( "p_{T}(jet1) (GeV/c)" );
      fH25->GetYaxis()->SetTitle ( "<R(jet1)> in 1 GeV/c bin" );

      fH23all = new TProfile ( "histo23all", "Jet1 Size vs P_{T} - all jets", h23_nbin, h23_low, h23_high );
      fH23all->GetXaxis()->SetTitle ( "p_{T}(jet) (GeV/c)" );
      fH23all->GetYaxis()->SetTitle ( "<R(jet1)> in 1 GeV/c bin" );

      fH24all = new TProfile ( "histo24all", "Jet1 Size vs P_{T}(jet1) - 80% of particles", h23_nbin, h23_low, h23_high );
      fH24all->GetXaxis()->SetTitle ( "p_{T}(jet) (GeV/c)" );
      fH24all->GetYaxis()->SetTitle ( "<R(jet1)> in 1 GeV/c bin" );

      fH25all = new TProfile ( "histo25all", "Jet1 Size vs P_{T}(jet1) - 80% of Pt", h23_nbin, h23_low, h23_high );
      fH25all->GetXaxis()->SetTitle ( "p_{T}(jet) (GeV/c)" );
      fH25all->GetYaxis()->SetTitle ( "<R(jet1)> in 1 GeV/c bin" );

    //=============================================================
      Int_t hg_nbin = 100;
      Double_t hg_binwidth = 0.01;
      Double_t hg_low = 0.;
      Double_t hg_high = hg_low + hg_binwidth * hg_nbin;

      fHg = new TH1D ( "histo_g", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg->GetXaxis()->SetTitle ( "g" );
      fHg->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHg_n90 = new TH1D ( "histo_g_n90", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg_n90->GetXaxis()->SetTitle ( "g" );
      fHg_n90->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHg_n85 = new TH1D ( "histo_g_n85", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg_n85->GetXaxis()->SetTitle ( "g" );
      fHg_n85->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHg_n80 = new TH1D ( "histo_g_n80", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg_n80->GetXaxis()->SetTitle ( "g" );
      fHg_n80->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHg_n75 = new TH1D ( "histo_g_n75", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg_n75->GetXaxis()->SetTitle ( "g" );
      fHg_n75->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHg_n70 = new TH1D ( "histo_g_n70", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg_n70->GetXaxis()->SetTitle ( "g" );
      fHg_n70->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHg_pt90 = new TH1D ( "histo_g_pt90", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg_pt90->GetXaxis()->SetTitle ( "g" );
      fHg_pt90->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHg_pt85 = new TH1D ( "histo_g_pt85", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg_pt85->GetXaxis()->SetTitle ( "g" );
      fHg_pt85->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHg_pt80 = new TH1D ( "histo_g_pt80", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg_pt80->GetXaxis()->SetTitle ( "g" );
      fHg_pt80->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHg_pt75 = new TH1D ( "histo_g_pt75", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg_pt75->GetXaxis()->SetTitle ( "g" );
      fHg_pt75->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHg_pt70 = new TH1D ( "histo_g_pt70", "dN/dg", hg_nbin, hg_low, hg_high );
      fHg_pt70->GetXaxis()->SetTitle ( "g" );
      fHg_pt70->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );


    //=============================================================
      Int_t hptd_nbin = 100;
      Double_t hptd_binwidth = 0.01;
      Double_t hptd_low = 0.;
      Double_t hptd_high = hptd_low + hptd_binwidth * hptd_nbin;

      fHptd = new TH1D ( "histo_g", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd->GetXaxis()->SetTitle ( "g" );
      fHptd->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHptd_n90 = new TH1D ( "histo_ptd_n90", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd_n90->GetXaxis()->SetTitle ( "g" );
      fHptd_n90->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHptd_n85 = new TH1D ( "histo_ptd_n85", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd_n85->GetXaxis()->SetTitle ( "g" );
      fHptd_n85->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHptd_n80 = new TH1D ( "histo_ptd_n80", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd_n80->GetXaxis()->SetTitle ( "g" );
      fHptd_n80->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHptd_n75 = new TH1D ( "histo_ptd_n75", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd_n75->GetXaxis()->SetTitle ( "g" );
      fHptd_n75->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHptd_n70 = new TH1D ( "histo_ptd_n70", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd_n70->GetXaxis()->SetTitle ( "g" );
      fHptd_n70->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHptd_pt90 = new TH1D ( "histo_ptd_pt90", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd_pt90->GetXaxis()->SetTitle ( "g" );
      fHptd_pt90->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHptd_pt85 = new TH1D ( "histo_ptd_pt85", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd_pt85->GetXaxis()->SetTitle ( "g" );
      fHptd_pt85->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHptd_pt80 = new TH1D ( "histo_ptd_pt80", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd_pt80->GetXaxis()->SetTitle ( "g" );
      fHptd_pt80->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHptd_pt75 = new TH1D ( "histo_ptd_pt75", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd_pt75->GetXaxis()->SetTitle ( "g" );
      fHptd_pt75->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );

      fHptd_pt70 = new TH1D ( "histo_ptd_pt70", "dN/dg", hptd_nbin, hptd_low, hptd_high );
      fHptd_pt70->GetXaxis()->SetTitle ( "g" );
      fHptd_pt70->GetYaxis()->SetTitle ( "1/N_{jets} dN/dg" );


  // =========== Switch on Sumw2 for all histos ===========
  for ( Int_t i = 0; i < fOutput->GetEntries(); ++i )
      {
      TH1 *h1 = dynamic_cast<TH1 *> ( fOutput->At (i) );
      if ( h1 ) { h1->Sumw2();continue; }

      TH2 *h2 = dynamic_cast<TH2 *> ( fOutput->At (i) );
      if ( h2 ) { h2->Sumw2();continue; }

      TProfile *hprof1 = dynamic_cast<TProfile *> ( fOutput->At (i) );
      if ( hprof1 ) { hprof1->Sumw2(); }
      }

  TIter next(fHistManager.GetListOfHistograms());
  TObject* obj = 0;
  while ((obj = next())) { fOutput->Add(obj); }

  PostData ( 1, fOutput ); // Post data for ALL output slots > 0 here.
  }

//________________________________________________________________________
Double_t AliAnalysisTaskEmcalJetCDF::DeltaR ( const AliVParticle *part1, const AliVParticle *part2 )
  {
  // Helper function to calculate the distance between two jets or a jet and
  // particle
  Double_t dPhi = part1->Phi() - part2->Phi();
  Double_t dEta = part1->Eta() - part2->Eta();
  dPhi = TVector2::Phi_mpi_pi ( dPhi );

  return TMath::Sqrt ( dPhi * dPhi + dEta * dEta );
  }

//__________________________________________________________________________________________________
std::vector<Int_t> AliAnalysisTaskEmcalJetCDF::SortTracksPt ( AliVEvent *event ) const
  {
  //___________________________________________
  // Sorting by p_T (decreasing) event tracks
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  Int_t entries = event->GetNumberOfTracks();

  // Create vector for Pt sorting
  std::vector<ptidx_pair> pair_list;
  pair_list.reserve ( entries );

  for ( Int_t i_entry = 0; i_entry < entries; i_entry++ )
      {
      AliVParticle *track = event->GetTrack ( i_entry );

      if ( !track )
          {
          AliError ( Form ( "Unable to find track %d in collection %s", i_entry, event->GetName() ) );
          continue;
          }

      pair_list.push_back ( std::make_pair ( track->Pt(), i_entry ) );
      }

  std::stable_sort ( pair_list.begin(), pair_list.end(), sort_descend() );

  // return an vector of indexes of constituents (sorted descending by pt)
  std::vector<Int_t> index_sorted_list;
  index_sorted_list.reserve ( entries );

  for ( std::vector< std::pair <Double_t, Int_t> >::iterator it = pair_list.begin(); it != pair_list.end(); ++it )
      {
      index_sorted_list.push_back ( ( *it ).second );
      } // populating the return object with indexes of sorted tracks

  return index_sorted_list;
  }

//__________________________________________________________________________________________________
std::vector<Int_t> AliAnalysisTaskEmcalJetCDF::SortTracksPt ( AliParticleContainer *trackscont ) const
  {
  //___________________________________________
  // Sorting by p_T (decreasing) event tracks
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  // Create vector for Pt sorting
  std::vector<ptidx_pair> pair_list;

  trackscont->ResetCurrentID();
  AliVTrack *track = NULL;
  UInt_t i_entry = 0;
  while( (track = dynamic_cast<AliVTrack*>(fTracksCont->GetNextAcceptParticle()) ))
    {
    i_entry++;
    pair_list.push_back ( std::make_pair ( track->Pt(), i_entry ) );
    }

  std::stable_sort ( pair_list.begin(), pair_list.end(), sort_descend() );

  // return an vector of indexes of constituents (sorted descending by pt)
  std::vector<Int_t> index_sorted_list;
  index_sorted_list.reserve ( i_entry );

  for ( std::vector< std::pair <Double_t, Int_t> >::iterator it = pair_list.begin(); it != pair_list.end(); ++it )
      {
      index_sorted_list.push_back ( ( *it ).second );
      } // populating the return object with indexes of sorted tracks

  return index_sorted_list;
  }

//________________________________________________________________________
Bool_t AliAnalysisTaskEmcalJetCDF::IdxInArray ( Int_t index, TArrayI &array )
  {
  for ( Int_t i = 0; i < array.GetSize(); i++ )
      {
      if ( index == array[i] ) { return kTRUE; }
      }

  return kFALSE;
  }

//________________________________________________________________________
void AliAnalysisTaskEmcalJetCDF::ExecOnce()
  {
  AliAnalysisTaskEmcalJet::ExecOnce();

  if ( fJetsCont )          { delete fJetsCont ; fJetsCont = 0; }
  if ( fTracksCont )        { delete fTracksCont ; fTracksCont = 0; }
  if ( fCaloClustersCont )  { delete fCaloClustersCont ; fCaloClustersCont = 0; }
  }

//________________________________________________________________________
void AliAnalysisTaskEmcalJetCDF::Terminate ( Option_t * )
  {
  // Called once at the end of the analysis.
  // Update pointers reading them from the output slot
  fOutput = dynamic_cast<AliEmcalList*> ( GetOutputData (0) );
  }

//________________________________________________________________________
Double_t AliAnalysisTaskEmcalJetCDF::Z_ptot( const AliEmcalJet* jet, const AliVParticle* trk)  const
{
  if (trk->P() < 1e-6) return 0.;
  return (trk != 0) ? trk->P()/ jet->P() : 0.;
}

//________________________________________________________________________
Double_t AliAnalysisTaskEmcalJetCDF::Z_pt( const AliEmcalJet* jet, const AliVParticle* trk)  const
{
  if (trk->P() < 1e-6) return 0.;
  return (trk != 0) ? trk->Pt() / jet->Pt() : 0.;
}

//________________________________________________________________________
TObject* AliAnalysisTaskEmcalJetCDF::GetHistogram ( const char* histName )
{
  return fHistManager.FindObject(histName);
}


// kate: indent-mode none; indent-width 2; replace-tabs on;

