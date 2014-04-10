
#include "AliAnalysisTaskEmcalJetCDF.h"

ClassImp ( AliAnalysisTaskEmcalJetCDF )

//________________________________________________________________________
AliAnalysisTaskEmcalJetCDF::AliAnalysisTaskEmcalJetCDF() : AliAnalysisTaskEmcalJet ( "AliAnalysisTaskEmcalJetCDF", kTRUE ),
    fContainerFull ( 1 ),
    fContainerCharged ( 0 ),
    fTriggerClass ( "" ),
    fJET1_track_idx ( NULL ),
    fJET1_track_pt ( NULL ),
    fTrack_idx ( NULL ),
    fTrack_pt ( NULL ),
    fH1 ( NULL ),
    fH2 ( NULL ),
    fH3 ( NULL ),
    fH4 ( NULL ),
    fH5 ( NULL ),
    fH5acc ( NULL ),
    fH6 ( NULL ),
    fH7 ( NULL ),
    fH8 ( NULL ),
    fH9 ( NULL ),
    fH10 ( NULL ),
    fH20 ( NULL ),
    fH21 ( NULL ),
    fH21Toward ( NULL ),
    fH21Transverse ( NULL ),
    fH21Away ( NULL ),
    fH22 ( NULL ),
    fH22Toward ( NULL ),
    fH22Transverse ( NULL ),
    fH22Away ( NULL ),
    fH23 ( NULL ),
    fH23jet1 ( NULL ),
    fH23Toward ( NULL ),
    fH23Transverse ( NULL ),
    fH23Away ( NULL ),
    fH24 ( NULL ),
    fH25 ( NULL ),
    fH26 ( NULL ),
    fH27 ( NULL ),
    fH28 ( NULL ),
    fH29 ( NULL ),
    fJetsCont( NULL ),
    fTracksCont( NULL ),
    fCaloClustersCont( NULL )

    {
    // Default constructor.
    SetMakeGeneralHistograms ( kTRUE );
    }

//________________________________________________________________________
AliAnalysisTaskEmcalJetCDF::AliAnalysisTaskEmcalJetCDF ( const char* name ) : AliAnalysisTaskEmcalJet ( name, kTRUE ),
    fContainerFull ( 1 ),
    fContainerCharged ( 0 ),
    fTriggerClass ( "" ),
    fJET1_track_idx ( NULL ),
    fJET1_track_pt ( NULL ),
    fTrack_idx ( NULL ),
    fTrack_pt ( NULL ),
    fH1 ( NULL ),
    fH2 ( NULL ),
    fH3 ( NULL ),
    fH4 ( NULL ),
    fH5 ( NULL ),
    fH5acc ( NULL ),
    fH6 ( NULL ),
    fH7 ( NULL ),
    fH8 ( NULL ),
    fH9 ( NULL ),
    fH10 ( NULL ),
    fH20 ( NULL ),
    fH21 ( NULL ),
    fH21Toward ( NULL ),
    fH21Transverse ( NULL ),
    fH21Away ( NULL ),
    fH22 ( NULL ),
    fH22Toward ( NULL ),
    fH22Transverse ( NULL ),
    fH22Away ( NULL ),
    fH23 ( NULL ),
    fH23jet1 ( NULL ),
    fH23Toward ( NULL ),
    fH23Transverse ( NULL ),
    fH23Away ( NULL ),
    fH24 ( NULL ),
    fH25 ( NULL ),
    fH26 ( NULL ),
    fH27 ( NULL ),
    fH28 ( NULL ),
    fH29 ( NULL ),
    fJetsCont( NULL ),
    fTracksCont( NULL ),
    fCaloClustersCont( NULL )

    {
    // Standard constructor.
    SetMakeGeneralHistograms ( kTRUE );
    }

//________________________________________________________________________
AliAnalysisTaskEmcalJetCDF::~AliAnalysisTaskEmcalJetCDF()
    {
    // Destructor.
    delete [] fTrack_idx ;
    delete [] fTrack_pt ;
    delete [] fJET1_track_idx ;
    delete [] fJET1_track_pt ;
    }

//________________________________________________________________________
Bool_t AliAnalysisTaskEmcalJetCDF::Run()
    {
    // Run analysis code here, if needed. It will be executed before FillHistograms().
    return kTRUE;  // If return kFALSE FillHistogram() will NOT be executed.
    }


//________________________________________________________________________
Bool_t AliAnalysisTaskEmcalJetCDF::FillHistograms()
    {
    // FillHistogram main function .. could parse all jet containers. At this moment only fisrt jet container is parsed
    Int_t result = -999; // return code
    Int_t jetContainers = fJetCollArray.GetEntries();

    jetContainers = 1; // process only first jet container

    for ( Int_t i = 0 ; i < jetContainers; i++ )
        {
        result = FillHistograms_container ( i );
        }

    if ( result != 1 ) { cout << "ERROR :: Fill of histograms failed in container" << endl; }

    if ( result == -1 ) { cout << "ERROR :: LEADING JET NOT FOUND" << endl; }

    if ( result < 1 ) { cout << "ERROR :: Fill histograms failed" << endl; return kFALSE; }

    return kTRUE;
    }

//________________________________________________________________________
Int_t AliAnalysisTaskEmcalJetCDF::FillHistograms_container ( Int_t idx_jet_container )
    {
    // Fill histograms.in container idx_jet_container
    AliJetContainer* cont = GetJetContainer ( idx_jet_container );

    if ( !cont ) { AliError ( Form ( "%s:Container %d not found", GetName(), idx_jet_container ) ); return 0; }

    fJets = cont->GetArray(); // get array of jets

// protection against not finding jets
    if ( !fJets || fJets->IsEmpty() )  { cout << "Jets pointer NULL or jets empty" << endl; return 0; }
    if ( fDebug > 0 ) { cout << "Jets pointer : "  << fJets << endl; fJets->Print(); }

// sort the list of AliEmcalJets
    fJets->Sort();

    const Int_t fNJets = GetNJets ( idx_jet_container ) ;  // Number of Jets found in event
    const Int_t fNPart = fInputEvent->GetNumberOfTracks(); // Multiplicity in event  //  fTracks->GetEntriesFast(); // <<-- faster?
    Bool_t leadJet = kFALSE;

// protection
    if ( ( fNJets == 0 ) || ( fNPart == 0 ) ) { cout << "(fNJets || fNPart) == 0" << endl; return 0; }

    printf ( "fNJets = %i ; fNPart = %i \n", fNJets, fNPart );
    printf ( "CDFhistos::end of ConnectInputData() \n" );       fflush ( stdout );

// consts used in analysis
    Double_t const kPI        = TMath::Pi();
    Double_t const kTWOPI     = 2. * TMath::Pi();
    Double_t const kPI_3      = TMath::Pi() / 3.;
    Double_t const kPI_2      = TMath::Pi() / 2.;

    Int_t fNJets_accepted = 0; // number of jets with accepted cuts

// Global Histograms; only filled with accepted jets
    for ( Int_t ij = 0; ij < fNJets; ij++ )
        {
        AliEmcalJet* jet = static_cast<AliEmcalJet*> ( fJets->At ( ij ) );

        if ( !jet ) { AliError ( Form ( "Could not receive jet %d", ij ) ); continue; }

        if ( !AcceptJet ( jet, idx_jet_container ) ) {continue;}

        fH1->Fill ( jet->Pt() );  // Pt distribution of jets
        fH2->Fill ( jet->Eta() ); // Eta distribution of jets
        fH3->Fill ( jet->Phi() ); // Phi distribution of jets
        fH4->Fill ( jet->GetNumberOfTracks() );  // Multiplicity of jets // 1 unit of multiplicity /bin
        fNJets_accepted++; // multiplicity of accepted jets
        }

// Distribution of jets in events;
    fH5->Fill ( fNJets );                // all jets (no AcceptedJet condition);
    fH5acc->Fill ( fNJets_accepted );    // all accepted jets

    printf ( "CDFhistos:: end of global jet histos \n" ); fflush ( stdout );

// "Transverse" Pt Distribution and computing of pt sum of event
// AND sorting the EVENT tracks by pt
    Double_t event_pt = 0.;
    fTrack_idx = new Int_t    [ fNPart ] ;   // sorted array of event pt
    fTrack_pt  = new Double_t [ fNPart ] ;   // array of event pts

    for ( Int_t i = 0 ; i < fNPart ; i++ )
        {
        // parse particles in event
        AliVParticle* track = fInputEvent->GetTrack ( i );

        if ( track )
            {
            event_pt += track->Pt(); // pt sum of event
            fTrack_idx [i] = -999 ;
            fTrack_pt  [i] = track->Pt();
            }
        }

    if ( fDebug > 1 ) { printf ( "Sum of all Pt in event : pt_sum_event = %g", event_pt ) ; }

    TMath::Sort ( fNPart, fTrack_pt, fTrack_idx ) ; // sorting pt of tracks in EVENT

//__________________________________________________________________
// Leading Jet
    Double_t    jet1_pt    = 0.;
    Int_t       jet1_npart = 0;

    AliEmcalJet* jet1 = cont->GetLeadingJet(); // internaly checked for AcceptedJet

    if ( !jet1 )
        { cout << "LEADING JET NOT FOUND " << endl ; return -1; }
    else
        { leadJet = kTRUE; }

    jet1->SortConstituents(); // Sort constituent by index (increasing). // SORT CONSTITUENT DECREASING BY PT - DONE below; eventually in AliEmcalJet

    jet1_pt    = jet1->Pt();
    jet1_npart = jet1->GetNumberOfTracks();

    fH6->Fill ( jet1_npart );          // Jet1 Multiplicity Distribution ( ->Scale (1/events) )
    fH7->Fill ( jet1_pt, jet1_npart ); // N(jet1) vs P_{T}(jet1)


//___________________________________________
// Sorting by p_T jet1 constituents
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    fJET1_track_idx = new Int_t    [ jet1_npart ] ;   // sorted array of jets pt
    fJET1_track_pt  = new Double_t [ jet1_npart ] ;   // array of jets pts

// filing the jet1_track_idx array
    for ( Int_t i = 0 ; i < jet1_npart ; i++ )
        {
        fJET1_track_idx [i] = -999 ;
        fJET1_track_pt  [i] = jet1->TrackAt ( i, fTracks )->Pt();
        }

    TMath::Sort ( jet1_npart, fJET1_track_pt, fJET1_track_idx ) ; // sorting pt of jets


//___________________________________________________________________________
// Momentum distribution for leading jet (FF)
// and
// N vs the Azimuthal Angle from Jet1

// parsing tracks of jet1 (leading jet)
    for ( Int_t i = 0 ; i < jet1_npart ; i++ )
        {

        AliVParticle* track = jet1->TrackAt ( i, fTracks ); if ( !track ) {continue;}

        Double_t track_pt = track->Pt() ;

        fH8->Fill ( track_pt / jet1_pt ) ; //  Momentum distribution for leading jet (FF)
        fH23jet1->Fill ( track_pt ) ; // jet1 pt distribution
        //___________________________________________________________________________
        // Recomputing of radius of particles in leading jet
        fH20->Fill ( DeltaR ( jet1, track ) ); //  Distribution of R in leading jet
        }

    fH21->Fill ( jet1_pt, fNPart );   // N (in the event - including jet1) vs P_{T}(jet1)
    fH22->Fill ( jet1_pt, event_pt ); // PT_{sum}(in the event - including jet1) vs P_{T}(jet1)

//_______________________________________________________________________
// Computing of radius that contain 80% of Leading Jet ( PT and multiplicity )
//_______________________________________________________________________
    Int_t    counter_part = 0  ;
    Double_t counter_pt   = 0. ;

// parsing tracks of jet1 (leading jet) in decreasing order of Pt //
    for ( Int_t i = 0 ; i < jet1_npart ; i++ )
    {// replace the index order by the sorted array
        Int_t idx_sorted = fJET1_track_idx[i];
        AliVParticle* track = jet1->TrackAt ( idx_sorted, fTracks );
        Double_t dpart = DeltaR ( jet1, track );

        counter_part++;
        counter_pt += track->Pt();

        if ( counter_part <= ( Int_t ) ( 0.8 * jet1_npart ) )
            {
            // fill histograms for 80% of particles
            fH24->Fill ( jet1_pt, dpart );        //  Jet1 Size vs P_{T}(jet1) - 80% of particles
            }

        if ( counter_pt <= 0.8 * jet1_pt )
            {
            // fill histograms for 80% of particles
            fH25->Fill ( jet1_pt, dpart );        //  Jet1 Size vs P_{T}(jet1) - 80% of Pt
            }
        }

    counter_part = 0 ; counter_pt = 0;

// parsing tracks in EVENT in decreasing order of Pt //
    for ( Int_t i = 0 ; i < fNPart ; i++ )
        {// replace the index order by the sorted array
        Int_t idx_sorted = fTrack_idx[i];
        AliVParticle* track = fInputEvent->GetTrack ( idx_sorted );

        if ( !track ) { cout << "track not retrieved from fInputEvent" << endl; continue; }

        Double_t track_pt = track->Pt();
        fH23->Fill ( track_pt ); //  Pt Distribution of particles in event

        Double_t dpart = DeltaR ( jet1, track );
        Double_t dphi_part_jet1 = Phi_mpi_pi ( track->Phi() - jet1->Phi() ) ; // restrict the delta phi to (-pi,pi) interval
        dphi_part_jet1 = TMath::Abs ( dphi_part_jet1 ); // and then to (0,pi) for towards,tranverse and away region histos

        counter_part++;
        counter_pt += track_pt;

        if ( counter_part <= ( Int_t ) ( 0.8 * jet1_npart ) )
            {
            // fill histograms for 80% of particles
            fH26->Fill ( dpart, counter_part );   //  N vs the Distance R from Jet1 - 80% of particles
            fH28->Fill ( dpart, counter_pt );     //  PT_{sum} vs the Distance R from Jet1 - 80% of particles
            }

        if ( counter_pt   <= 0.8 * jet1_pt )
            {
            // fill histograms for 80% of particles
            fH27->Fill ( dpart, counter_part );   //  N vs the Distance R from Jet1 - 80% of Pt
            fH29->Fill ( dpart, counter_pt );     //  PT_{sum} vs the Distance R from Jet1 - 80% of Pt
            }

// dphi distribution (total and per toward,away,transverse regions)

        fH9 ->Fill ( TMath::RadToDeg() * dphi_part_jet1, fNPart )   ; //  N vs the Azimuthal Angle from Jet1
        fH10->Fill ( TMath::RadToDeg() * dphi_part_jet1, event_pt ) ; //  P_{T} sum vs the Azimuthal Angle from Jet1

        if ( dphi_part_jet1 < kPI_3 )
            {
            fH21Toward->Fill ( jet1_pt, fNPart );   // N (in the event - including jet1) vs P_{T}(jet1)
            fH22Toward->Fill ( jet1_pt, event_pt ); // PT_{sum}(in the event - including jet1) vs P_{T}(jet1)
            fH23Toward->Fill ( track_pt );          // Pt Distribution of particles
            }
        else
        if ( ( dphi_part_jet1 >= kPI_3 ) && ( dphi_part_jet1 < ( 2.* kPI_3 ) ) )
            {
            fH21Transverse->Fill ( jet1_pt, fNPart );   // N (in the event - including jet1) vs P_{T}(jet1)
            fH22Transverse->Fill ( jet1_pt, event_pt ); // PT_{sum}(in the event - including jet1) vs P_{T}(jet1)
            fH23Transverse->Fill ( track_pt );          // Pt Distribution of particles
            }
        else
        if ( dphi_part_jet1 >= ( 2.* kPI_3 ) )
            {
            fH21Away->Fill ( jet1_pt, fNPart );   // N (in the event - including jet1) vs P_{T}(jet1)
            fH22Away->Fill ( jet1_pt, event_pt ); // PT_{sum}(in the event - including jet1) vs P_{T}(jet1)
            fH23Away->Fill ( track_pt );          // Pt Distribution of particles
            }
        }

// post data at every processing
    PostData ( 1, fOutput ); // Post data for ALL output slots > 0 here.

    return 1;
    }

//________________________________________________________________________
void AliAnalysisTaskEmcalJetCDF::UserCreateOutputObjects()
    {
    // Create user output.

    AliAnalysisTaskEmcalJet::UserCreateOutputObjects();

    //  Histograms
    fOutput->SetOwner ( kTRUE );

    // Create the list of histograms. Only the list is owned.

    fH1 = new TH1F ( "histo1", "Pt distribution of jets", 400, 0, 400 ); // 1GeV/bin
    fH1->SetStats ( kTRUE );
    fH1->GetXaxis()->SetTitle ( "$p_{T,jet}$ in GeV/$c$" );
    fH1->GetYaxis()->SetTitle ( "Number of jets" );
    fH1->GetXaxis()->SetTitleColor ( 1 );
    fH1->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH1 );

    fH2 = new TH1F ( "histo2", "Eta distribution of jets", 200, -1., 1. ); // 1 unit of rapidity / 100 bin
    fH2->SetStats ( kTRUE );
    fH2->GetXaxis()->SetTitle ( "Eta of jets" );
    fH2->GetYaxis()->SetTitle ( "Number of jets" );
    fH2->GetXaxis()->SetTitleColor ( 1 );
    fH2->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH2 );

    fH3 = new TH1F ( "histo3", "Phi distribution of jets", 126, 0., 6.3 );
    fH3->SetStats ( kTRUE );
    fH3->GetXaxis()->SetTitle ( "Phi of jets" );
    fH3->GetYaxis()->SetTitle ( "Number of jets" );
    fH3->GetXaxis()->SetTitleColor ( 1 );
    fH3->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH3 );

    fH4 = new TH1F ( "histo4", "Multiplicity of jets", 100, 0, 100 ); // 1 unit of multiplicity /bin
    fH4->SetStats ( kTRUE );
    fH4->GetXaxis()->SetTitle ( "Particles in jets" );
    fH4->GetYaxis()->SetTitle ( "Number of jets" );
    fH4->GetXaxis()->SetTitleColor ( 1 );
    fH4->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH4 );

    fH5 = new TH1F ( "histo5", "Distribution of jets in events", 20, 0, 20 );
    fH5->SetStats ( kTRUE );
    fH5->GetXaxis()->SetTitle ( "Number of jets" );
    fH5->GetYaxis()->SetTitle ( "Number of events" );
    fH5->GetXaxis()->SetTitleColor ( 1 );
    fH5->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH5 );

    fH5acc = new TH1F ( "histo5acc", "Distribution of accepted jets in events", 20, 0, 20 );
    fH5acc->SetStats ( kTRUE );
    fH5acc->GetXaxis()->SetTitle ( "Number of jets" );
    fH5acc->GetYaxis()->SetTitle ( "Number of events" );
    fH5acc->GetXaxis()->SetTitleColor ( 1 );
    fH5acc->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH5acc );

    fH6 = new TH1F ( "histo6", "Jet1 Multiplicity Distribution", 100, 0, 100 );
    fH6->SetStats ( kTRUE );
    fH6->GetXaxis()->SetTitle ( "N^{jet1}" );
    fH6->GetYaxis()->SetTitle ( "Number of jets" );
    fH6->GetXaxis()->SetTitleColor ( 1 );
    fH6->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH6 );

    fH7 = new TProfile ( "histo7", "N(jet1) vs P_{T}(jet1)", 400, 0. , 400. , 0., 400. ) ;
    fH7->SetStats ( kTRUE );
    fH7->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH7->GetYaxis()->SetTitle ( "<N(jet1)> in 1 GeV/c bin" );
    fH7->GetXaxis()->SetTitleColor ( 1 );
    fH7->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH7 );

    fH8 = new TH1F ( "histo8", "Momentum distribution for jet1 (FF)", 120, 0 , 1.2 );
    fH8->SetStats ( kTRUE );
    fH8->GetXaxis()->SetTitle ( "z = p/P(jet1)" );
    fH8->GetYaxis()->SetTitle ( "F(Z) = dN/dz" );
    fH8->GetXaxis()->SetTitleColor ( 1 );
    fH8->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH8 );

    fH9 = new TProfile ( "histo9", "N vs the Azimuthal Angle from Jet1", 50 , 0. , 180. , 0 , 20 );
    fH9->SetStats ( kTRUE );
    fH9->GetXaxis()->SetTitle ( "#Delta#phi (degrees)" );
    fH9->GetYaxis()->SetTitle ( "<N> in 3.6 degree bin" );
    fH9->GetXaxis()->SetTitleColor ( 1 );
    fH9->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH9 );

    fH10 = new TProfile ( "histo10", "P_{T} sum vs the Azimuthal Angle from Jet1", 50 , 0. , 180. , 0 , 100 );
    fH10->SetStats ( kTRUE );
    fH10->GetXaxis()->SetTitle ( "|#Delta#phi| (degrees)" );
    fH10->GetYaxis()->SetTitle ( "<P_{T} sum> in 3.6 degree bin" );
    fH10->GetXaxis()->SetTitleColor ( 1 );
    fH10->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH10 );

    fH20 = new TH1F ( "histo20", "Distribution of R in leading jet", 100, 0., 1. );
    fH20->SetStats ( kTRUE );
    fH20->GetXaxis()->SetTitle ( "R" );
    fH20->GetYaxis()->SetTitle ( "dN/dR" );
    fH20->GetXaxis()->SetTitleColor ( 1 );
    fH20->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH20 );

    fH21 = new TProfile ( "histo21", "N(in the event - including jet1) vs P_{T}(jet1)", 200, 0., 200. , 0., 30. ) ;
    fH21->SetStats ( kTRUE );
    fH21->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH21->GetYaxis()->SetTitle ( "<N(in the event - including jet1)> in 1 GeV/c bin" );
    fH21->GetXaxis()->SetTitleColor ( 1 );
    fH21->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH21 );

    fH21Toward = new TProfile ( "histo21_toward", "N(in the event - including jet1) vs P_{T}(jet1)", 200, 0., 200. , 0., 12. ) ;
    fH21Toward->SetStats ( kTRUE );
    fH21Toward->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH21Toward->GetYaxis()->SetTitle ( "<N(in the event - including jet1)> in 1 GeV/c bin" );
    fH21Toward->GetXaxis()->SetTitleColor ( 1 );
    fH21Toward->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH21Toward );

    fH21Transverse = new TProfile ( "histo21_transverse", "N(in the event - including jet1) vs P_{T}(jet1)", 200, 0., 200. , 0., 12. ) ;
    fH21Transverse->SetStats ( kTRUE );
    fH21Transverse->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH21Transverse->GetYaxis()->SetTitle ( "<N(in the event - including jet1)> in 1 GeV/c bin" );
    fH21Transverse->GetXaxis()->SetTitleColor ( 1 );
    fH21Transverse->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH21Transverse );

    fH21Away = new TProfile ( "histo21_away", "N(in the event - including jet1) vs P_{T}(jet1)", 200, 0., 200. , 0., 12. ) ;
    fH21Away->SetStats ( kTRUE );
    fH21Away->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH21Away->GetYaxis()->SetTitle ( "<N(in the event - including jet1)> in 1 GeV/c bin" );
    fH21Away->GetXaxis()->SetTitleColor ( 1 );
    fH21Away->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH21Away );

    //__________________________________________________________________
    fH22 = new TProfile ( "histo22", "PT_{sum}(in the event - including jet1) vs P_{T}(jet1)", 200, 0. , 200. , 0., 50. ) ;
    fH22->SetStats ( kTRUE );
    fH22->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH22->GetYaxis()->SetTitle ( "<PT_{sum}(in the event - including jet1)> in 1 GeV/c bin" );
    fH22->GetXaxis()->SetTitleColor ( 1 );
    fH22->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH22 );

    fH22Toward = new TProfile ( "histo22_toward", "PT_{sum}(in the event - including jet1) vs P_{T}(jet1)", 200, 0. , 200. , 0., 50. ) ;
    fH22Toward->SetStats ( kTRUE );
    fH22Toward->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH22Toward->GetYaxis()->SetTitle ( "<PT_{sum}(in the event - including jet1)> in 1 GeV/c bin" );
    fH22Toward->GetXaxis()->SetTitleColor ( 1 );
    fH22Toward->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH22Toward );

    fH22Transverse = new TProfile ( "histo22_transverse", "PT_{sum}(in the event - including jet1) vs P_{T}(jet1)", 200, 0. , 200. , 0., 50. ) ;
    fH22Transverse->SetStats ( kTRUE );
    fH22Transverse->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH22Transverse->GetYaxis()->SetTitle ( "<PT_{sum}(in the event - including jet1)> in 1 GeV/c bin" );
    fH22Transverse->GetXaxis()->SetTitleColor ( 1 );
    fH22Transverse->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH22Transverse );

    fH22Away = new TProfile ( "histo22_away", "PT_{sum}(in the event - including jet1) vs P_{T}(jet1)", 200, 0. , 200. , 0., 50. ) ;
    fH22Away->SetStats ( kTRUE );
    fH22Away->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH22Away->GetYaxis()->SetTitle ( "<PT_{sum}(in the event - including jet1)> in 1 GeV/c bin" );
    fH22Away->GetXaxis()->SetTitleColor ( 1 );
    fH22Away->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH22Away );

    //____________________________________________________________________________________
    fH23 = new TH1F ( "histo23", "Pt Distribution of particles", 800, 0., 800. );
    fH23->SetStats ( kTRUE );
    fH23->GetXaxis()->SetTitle ( "P_{T}  (GeV/c)" );
    fH23->GetYaxis()->SetTitle ( "dN/dP_{T} (1/GeV/c)" );
    fH23->GetXaxis()->SetTitleColor ( 1 );
    fH23->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH23 );

    fH23jet1 = new TH1F ( "histo23jet1", "Pt Distribution of particles in jet1", 800, 0., 800. );
    fH23jet1->SetStats ( kTRUE );
    fH23jet1->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH23jet1->GetYaxis()->SetTitle ( "dN/dP_{T} (jet1) (1/GeV/c)" );
    fH23jet1->GetXaxis()->SetTitleColor ( 1 );
    fH23jet1->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH23jet1 );

    fH23Toward = new TH1F ( "histo23_toward", "'Toward' Pt Distribution of particles", 800, 0., 800. );
    fH23Toward->SetStats ( kTRUE );
    fH23Toward->GetXaxis()->SetTitle ( "P_{T} (GeV/c)" );
    fH23Toward->GetYaxis()->SetTitle ( "dN/dP_{T} (1/GeV/c)" );
    fH23Toward->GetXaxis()->SetTitleColor ( 1 );
    fH23Toward->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH23Toward );

    fH23Transverse = new TH1F ( "histo23_transverse", "'Transverse' Pt Distribution of particles", 800, 0., 800. );
    fH23Transverse->SetStats ( kTRUE );
    fH23Transverse->GetXaxis()->SetTitle ( "P_{T} (GeV/c)" );
    fH23Transverse->GetYaxis()->SetTitle ( "dN/dP_{T} (1/GeV/c)" );
    fH23Transverse->GetXaxis()->SetTitleColor ( 1 );
    fH23Transverse->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH23Transverse );

    fH23Away = new TH1F ( "histo23_away", "'Away' Pt Distribution of particles", 800, 0., 800. );
    fH23Away->SetStats ( kTRUE );
    fH23Away->GetXaxis()->SetTitle ( "P_{T} (GeV/c)" );
    fH23Away->GetYaxis()->SetTitle ( "dN/dP_{T} (1/GeV/c)" );
    fH23Away->GetXaxis()->SetTitleColor ( 1 );
    fH23Away->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH23Away );

    fH24 = new TProfile ( "histo24", "Jet1 Size vs P_{T}(jet1)", 200, 0., 200. , 0., 0.5 ) ;
    fH24->SetStats ( kTRUE );
    fH24->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH24->GetYaxis()->SetTitle ( "<R(jet1)> in 1 GeV/c bin" );
    fH24->GetXaxis()->SetTitleColor ( 1 );
    fH24->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH24 );

    fH25 = new TProfile ( "histo25", "Jet1 Size vs P_{T}(jet1)", 200, 0., 200. , 0., 0.5 ) ;
    fH25->SetStats ( kTRUE );
    fH25->GetXaxis()->SetTitle ( "P_{T} (jet1) (GeV/c)" );
    fH25->GetYaxis()->SetTitle ( "<R(jet1)> in 1 GeV/c bin" );
    fH25->GetXaxis()->SetTitleColor ( 1 );
    fH25->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH25 );

    fH26 = new TProfile ( "histo26", "N vs the Distance R from Jet1 - 80% of particles", 50, 0., 1., 0., 20. );
    fH26->SetStats ( kTRUE );
    fH26->GetXaxis()->SetTitle ( "Distance R" );
    fH26->GetYaxis()->SetTitle ( "<N> in 0.02 bin" );
    fH26->GetXaxis()->SetTitleColor ( 1 );
    fH26->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH26 );

    fH27 = new TProfile ( "histo27", "N vs the Distance R from Jet1 - 80% of Pt", 50, 0., 1., 0., 20. );
    fH27->SetStats ( kTRUE );
    fH27->GetXaxis()->SetTitle ( "Distance R" );
    fH27->GetYaxis()->SetTitle ( "<N> in 0.02 bin" );
    fH27->GetXaxis()->SetTitleColor ( 1 );
    fH27->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH27 );

    fH28 = new TProfile ( "histo28", "PT_{sum} vs the Distance R from Jet1 - 80% of particles", 50, 0., 1., 0., 10. );
    fH28->SetStats ( kTRUE );
    fH28->GetXaxis()->SetTitle ( "Distance R" );
    fH28->GetYaxis()->SetTitle ( "<PT_{sum} (GeV/c)> in 0.02 bin" );
    fH28->GetXaxis()->SetTitleColor ( 1 );
    fH28->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH28 );

    fH29 = new TProfile ( "histo29", "PT_{sum} vs the Distance R from Jet1 - 80% of Pt", 50, 0., 1., 0., 10. );
    fH29->SetStats ( kTRUE );
    fH29->GetXaxis()->SetTitle ( "Distance R" );
    fH29->GetYaxis()->SetTitle ( "<PT_{sum} (GeV/c)> in 0.02 bin" );
    fH29->GetXaxis()->SetTitleColor ( 1 );
    fH29->SetMarkerStyle ( kFullCircle );
    fOutput->Add ( fH29 );


    // =========== Switch on Sumw2 for all histos ===========
    for ( Int_t i = 0; i < fOutput->GetEntries(); ++i )
        {
        TH1* h1 = dynamic_cast<TH1*> ( fOutput->At ( i ) );

        if ( h1 ) { h1->Sumw2(); continue; }

        TProfile* hprof1 = dynamic_cast<TProfile*> ( fOutput->At ( i ) );

        if ( hprof1 ) { hprof1->Sumw2(); }
        }

    PostData ( 1, fOutput ); // Post data for ALL output slots > 0 here.
    }

//________________________________________________________________________
Double_t AliAnalysisTaskEmcalJetCDF::DeltaR ( const AliVParticle* part1, const AliVParticle* part2 )
    {
    // Helper function to calculate the distance between two jets or a jet and particle
    Double_t dPhi = part1->Phi() - part2->Phi();
    Double_t dEta = part1->Eta() - part2->Eta();
    dPhi = Phi_mpi_pi ( dPhi );

    return TMath::Sqrt ( dPhi * dPhi + dEta * dEta );
    }

//________________________________________________________________________
Double_t AliAnalysisTaskEmcalJetCDF::GetZ ( const AliVParticle* trk, const AliEmcalJet* jet )          const
    {
    // Get Z of constituent trk
    return GetZ ( trk->Px(), trk->Py(), trk->Pz(), jet->Px(), jet->Py(), jet->Pz() );
    }

//________________________________________________________________________
Double_t AliAnalysisTaskEmcalJetCDF::GetZ ( const Double_t trkPx, const Double_t trkPy, const Double_t trkPz, const Double_t jetPx, const Double_t jetPy, const Double_t jetPz ) const
    {
    // Get the z of a constituent inside of a jet
    Double_t pJetSq = jetPx * jetPx + jetPy * jetPy + jetPz * jetPz;

    if ( pJetSq == 0. ) { AliWarning ( Form ( "%s: strange, pJetSq seems to be zero: %f", GetName(), pJetSq ) ); return 0; }

    if ( pJetSq <  0. ) { AliWarning ( Form ( "%s: FATAL, pJetSq seems to be BELOW zero!! IMPOSIBLE: %f", GetName(), pJetSq ) ); return 0; }

    return ( trkPx * jetPx + trkPy * jetPy + trkPz * jetPz ) / pJetSq;
    }


//________________________________________________________________________
void AliAnalysisTaskEmcalJetCDF::Terminate ( Option_t* )
    {
    // Called once at the end of the analysis.
    // Update pointers reading them from the output slot
    fOutput = dynamic_cast<TList*> ( GetOutputData ( 0 ) );
    }
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;

