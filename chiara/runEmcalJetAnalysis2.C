#ifndef __CINT__
// Standard includes
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdio>

// ROOT includes
#include "Riostream.h"
#include "Rtypes.h"
#include "TROOT.h"
#include "TObject.h"
#include "TSystem.h"
#include "TApplication.h"
#include "TString.h"
#include "TList.h"
#include "TEnv.h"
#include "TKey.h"
#include "TBits.h"
#include "TError.h"
#include "TNamed.h"
#include "TDirectory.h"
#include "TDirectoryFile.h"
#include "TFile.h"
#include "TFileCollection.h"
#include "TCollection.h"
#include "TChain.h"
#include "TObjString.h"
#include "TObjArray.h"

// AliROOT includes
#include "AliAnalysisManager.h"
#include "AliAnalysisGrid.h"
#include "AliAnalysisAlien.h"
#include "AliAnalysisDataContainer.h"
#include "AliMultiInputEventHandler.h"
#include "AliLog.h"
#include "AliAODHandler.h"
#include "AliAODInputHandler.h"
#include "AliESDInputHandler.h"
#include "AliMCEventHandler.h"
#include "AliAnalysisTaskTagCreator.h"
#include "AliPhysicsSelectionTask.h"
#include "AliCentralitySelectionTask.h"
#include "AliEmcalCompatTask.h"
#include "AliEmcalSetupTask.h"
#include "AliAnalysisTaskEmcal.h"
#include "AliEMCALRecParam.h"
#include "AliEmcalJetTask.h"
#include "AliAnalysisTaskRho.h"

#include "AliAnalysisTaskEmcal.h"
#include "AliAnalysisTaskEmcalJet.h"
#include "AliAnalysisTaskEmcalJetSample.h"

#include "AddAODHandler.C" // $ALICE_ROOT/ANALYSIS/macros/train/AddAODHandler.C
#include "AddESDHandler.C" // $ALICE_ROOT/ANALYSIS/macros/train/AddESDHandler.C
#include "AddMCHandler.C"  // $ALICE_ROOT/ANALYSIS/macros/train/AddMCHandler.C

#include "AddTaskCentrality.C"            // $ALICE_ROOT/ANALYSIS/macros/AddTaskCentrality.C
#include "AddTaskEmcalPhysicsSelection.C" // $ALICE_ROOT/PWG/EMCAL/macros/AddTaskEmcalPhysicsSelection.C
#include "AddTaskEmcalCompat.C"           // $ALICE_ROOT/PWG/EMCAL/macros/AddTaskEmcalCompat.C
#include "AddTaskEmcalSetup.C"            // $ALICE_ROOT/PWG/EMCAL/macros/AddTaskEmcalSetup.C
#include "AddTaskEMCALTender.C"           // $ALICE_ROOT/PWG/EMCAL/macros/AddTaskEMCALTender.C
#include "AddTaskEmcalPreparation.C"      // $ALICE_ROOT/PWG/EMCAL/macros/AddTaskEmcalPreparation.C
#include "AddTaskRho.C"                   // $ALICE_ROOT/PWGJE/EMCALJetTasks/macros/AddTaskRho.C
#include "AddTaskJetPreparation.C"        // $ALICE_ROOT/PWGJE/EMCALJetTasks/macros/AddTaskJetPreparation.C
#include "AddTaskEmcalJet.C"              // $ALICE_ROOT/PWGJE/EMCALJetTasks/macros/AddTaskEmcalJet.C
#include "AddTaskEmcalJetSample.C"        // $ALICE_ROOT/PWGJE/EMCALJetTasks/macros/AddTaskEmcalJetSample.C

#include "InputData.C"

#endif


//______________________________________________________________________________
// enum Jets used
enum AlgoType {kKT, kANTIKT};                           // AddTaskEmcalJet.C
enum JetType  {kFULLJETS, kCHARGEDJETS, kNEUTRALJETS};  // AddTaskEmcalJet.C
enum JetAcceptanceType { kTPC, kEMCAL, kUser };         // AliJetContainer
enum runModeType {  kLocal, kGrid };                    // AliAnalysisTaskLocalRho
enum fitModulationType { kNoFit, kV2, kV3, kCombined, kFourierSeries, kIntegratedFlow, kQC2, kQC4 }; // AliAnalysisTaskLocalRho

//______________________________________________________________________________
//(*)(*)(*)(*)(*)(*)(*)(*)(*)(*)(*)
//        AliEN plugin variables
//(*)(*)(*)(*)(*)(*)(*)(*)(*)(*)(*)
//______________________________________________________________________________

Int_t       kTestFiles               = 1;    // Number of test files
Long64_t    nentries                 = 1234567890; // for local and proof mode, ignored in grid mode. Set to 1234567890 for all events.
Long64_t    firstentry               = 0; // for local and proof mode, ignored in grid mode

TString     kTrainName               = "jets";           // *CHANGE ME* (no blancs or special characters)
TString     kWorkDir                 = "sample";         // AliEn work dir; relative to AliEn $HOME
TString     kJobTag                  = "jet_analysis";   // *CHANGE ME*

TString     kPluginExecutableCommand = "aliroot -b -q";
Bool_t      kPluginUseProductionMode = kFALSE;         // use the plugin in production mode

TString     kPluginAPIVersion        = "V1.1x";
TString     kPluginRootVersion       = "v5-34-08-6";
TString     kPluginAliRootVersion    = "vAN-20141130";

TString     kPackage1                = "boost::v1_53_0";
TString     kPackage2                = "cgal::v4.4";
TString     kPackage3                = "fastjet::v3.0.6_1.012";

Bool_t      kPluginFastReadOption    = kFALSE;         // use xrootd tweaks
Bool_t      kPluginOverwriteMode     = kTRUE;          // overwrite existing collections

Bool_t      kSkipTerminate           = kTRUE;          // Do not call Terminate
Bool_t      kUsePAR                  = kFALSE;         // use par files for extra libs

Int_t       kGridFilesPerJob         = 25;             // Maximum number of files per job (gives size of AOD)
Int_t       kGridMaxMergeFiles       = 100;            // Number of files merged in a chunk grid run range
Int_t       kMaxInitFailed           = 10 ;            // Optionally set number of failed jobs that will trigger killing waiting sub-jobs.

Int_t       kTTL                     = 14400 ;         // Time To Live

TString     kGridOutdir              = "out";          // AliEn output directory. If blank will become output_<kTrainName>
TString     kGridDataSet             = "";             // sub working directory not to confuse different run xmls
TString     kGridExtraAliendirLevel  = "";             // sub working directory not to confuse different run xmls

TString     kAlirootMode             = "ALIROOT";     // STEERBase,ESD,AOD,ANALYSIS,ANALYSISalice (default aliroot mode)
//  alirootMode="ALIROOT";   // $ALICE_ROOT/macros/loadlibs.C
//  alirootMode="REC";       // $ALICE_ROOT/macros/loadlibsrec.C
//  alirootMode="SIM";       // $ALICE_ROOT/macros/loadlibssim.C
//  alirootMode="TRAIN";     // $ALICE_ROOT/macros/loadlibstrain.C (not working yet)
//  alirootMode="CUSTOM";    // nothing is loaded, but aliroot variables are set (not working yet)

//--------------------
//   PROOF SETTINGS
//--------------------
TString kAAF        =
//                         "asevcenc@alice-caf.cern.ch" ;
    "asevcenc@skaf.saske.sk";

Int_t   kProofReset = 0  ; Int_t   kWorkers    = 20 ; Int_t   kCores      = 8  ;
//------------------------------------------------------------------------------

//==============================================================================
// Global objects to be access by utility functions
TString     kInputDataLabel = "";

// Containers for IO file names
TString     kDataset        = "";
TString     kDatafile       = "";

// definition of variables to be used later - autodetected
TString     runPeriod       = ""; // run period (to be determined automatically form path to files; if path is not GRID like, set by hand)
TString     dataType        = ""; // analysis type, AOD, ESD or sESD (to be automatically determined below; if detection does not work, set by hand after detection)
TString     kPass           = ""; // pass string

TString     kPluginMode     = ""; // test, offline, submit, terminate, full
TString     kAnalysisMode   = ""; // local, grid, proof
TString     kInputStr       = ""; // input string

//==============================================================================

// FILES USED IN MACRO
TString     kCommonOutputFileName    = "AnalysisResults.root";

// == grid plugin files rules
TString     kGridExtraFiles          = ""; // LIBRARIES files that will be added to the input list in the JDL
TString     kGridMergeExclude        = "AliAOD.root AliAOD.Jets.root"; // Files that should not be merged
TString     kGridOutputStorages      = "disk=2"; // Make replicas on the storages

// == Lists of libraries, pars and sources to be added to the alien plugin
TString     ListPars      = "";
TString     ListLibs      = "";
TString     ListLibsExtra = "";
TString     ListSources   = "";

// Function signatures
class AliAnalysisGrid;
class AliAnalysisAlien;
class AliAnalysisManager;


//==============================================================================
//      DEBUG
Int_t           debug              =  0 ; // kFatal = 0, kError, kWarning, kInfo, kDebug, kMaxType
unsigned int    kUseSysInfo        =  0 ; // activate debugging
Int_t           kErrorIgnoreLevel  = -1 ; // takes the errror print level from .rootrc

//______________________________________________________________________________
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@     ANALYSIS STEERING VARIABLES     @@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

Bool_t         isMC                = kFALSE;          // trigger, if MC handler should be used
Bool_t         useTender           = kTRUE;           // trigger, if tender task should be used
Bool_t         doBkg               = kFALSE;          // background estimation with AliAnalysisTaskRho

UInt_t         pSel                = AliVEvent::kAny;  // used event selection for every task except for the analysis tasks

Int_t          jettype             = kCHARGEDJETS;    // 0 --> AliEmcalJetTask::kFullJet; 1 --> AliEmcalJetTask::kChargedJet; 2 --> AliEmcalJetTask::kNeutralJet

TString        kFriendChainName    = "AliAOD.VertexingHF.root";              // File name to construct friend chain (for AOD)

// acceptance cuts on jets
TString        acceptance_type     = "TPC";         // TPC, EMCAL, kUSER
UInt_t         acceptance_type_i   = -1;            // AliJetContainer enum : will be set in sync to string in "sanity checks" part

Bool_t         tracks_etaphi_cuts  = kFALSE;        // fiducial acceptance cuts on jet constituents (tracks)

Int_t          leadhadtype         = 0;             // AliJetContainer :: Int_t fLeadingHadronType;  0 = charged, 1 = neutral, 2 = both

//__________________________________________________________________________________
// Objects (branch names) used in Jet framework
TString tracksName         = "PicoTracks";          // runEmcalJetAnalysis default = PicoTracks
TString clustersName       = "EmcCaloClusters";     // runEmcalJetAnalysis default = EmcCaloClusters
TString clustersCorrName   = "CaloClustersCorr";    // runEmcalJetAnalysis default = CaloClustersCorr
TString rhoName            = "";

void runEmcalJetAnalysis2 (const char* analysis_mode = "local", const char* plugin_mode = "test", const char* input = "data.txt")
    {
    gSystem->SetFPEMask(); // because is used in reference script

    // sanity checks
    if ( jettype != kCHARGEDJETS )  { acceptance_type = "EMCAL"; }
    if ( jettype == kNEUTRALJETS )  { leadhadtype == 1; }
    if ( jettype == kFULLJETS )     { leadhadtype == 2; }

    if ( acceptance_type.EqualTo("TPC"))   { acceptance_type_i = 0; }
    else
    if ( acceptance_type.EqualTo("EMCAL")) { acceptance_type_i = 1; }
    else
        { acceptance_type_i = 2; }

    // if acceptance cut on input contituents then do not cut in acceptance of jets
    if ( tracks_etaphi_cuts ) { acceptance_type = "TPC" ; acceptance_type_i = 0; }

    LoadLibs(); // Load necessary libraries for the script and for the plugin

    kPluginMode   = plugin_mode   ; kPluginMode.ToLower();    // test, offline, submit, terminate, full
    kAnalysisMode = analysis_mode ; kAnalysisMode.ToLower();  // local, grid, proof
    kInputStr     = input;

    // if analysis is done on localhost do not use PARs
    if ( kAnalysisMode.EqualTo ("local") || kPluginMode.EqualTo ("test")  ) { kUsePAR = kFALSE; }

//__________________________________________________________________________________
    // ###   SET UP AliEn handler ### -> main analysis engine : we will use many internal tools of AliAnalysisAlien
    AliAnalysisAlien* plugin = CreateAlienHandler ( kPluginMode.Data() );

    // ###   ANALYSIS MANAGER   ###  // Make the analysis manager and connect event handlers
    AliAnalysisManager* mgr  = plugin->CreateAnalysisManager ( "histos_mgr" );

//__________________________________________________________________________________
    // prepare the environment for analysis;
    PrepareAnalysisEnvironment();

//####################################################
//#######        ANALYSIS TASKS LIST
//####################################################

  gROOT->LoadMacro("AddTasksFlavourJet.C");

  // const UInt_t uTriggerMask = AliVEvent::kMB ; /*for jets; the D mesons trigger is defined in the cut object*/
  // const TString sRunPeriod = "LHC13b", /*for track selection*/
  Bool_t tmpoadb2012flag = kFALSE; /*kTRUE for LHC12h and LHC12i*/
  if ( runPeriod.EqualTo("lhc12h") || runPeriod.EqualTo("lhc12i") ) { tmpoadb2012flag = kTRUE; }

  const Bool_t bIsMC = kFALSE;
  /*input for D mesons*/
  Double_t R = 0.4;
  const Int_t iCandType = 1; /*0 = D0, 1=Dstar...*/
  const TString sCutFile = "/data/Work/jets/testEMCalJetFramework/Trains/cutfiles/DStartoKpipiCutsEMC7ptminspiptDdep.root";  // default : "cutsHF/D0toKpiCutsppRecVtxNoPileupRejNoEMCAL.root";
  const Double_t dJetPtCut   = 5.; // default: 1.
  const Double_t dJetAreaCut = -1.;
//  const char* acctype = "TPC";
  const Bool_t bIsReco = kTRUE;
  const Bool_t bIsMap = kFALSE;
  TString sText = "";/*completes the name of the candidate task lists*/
  Bool_t triggerOnLeadingJet = kFALSE;
  const Bool_t bUseEMCalTrig = kFALSE;
  const Bool_t bIsTrain = kFALSE;

  AddTasksFlavourJet( pSel, runPeriod, tmpoadb2012flag, isMC, R, iCandType, sCutFile, dJetPtCut, dJetAreaCut, acceptance_type.Data(), isReco, isMap, sText, triggerOnLeadingJet, bUseEMCalTrig, bIsTrain);

    // enable class level debugging for these classes
    if ( debug > 3 )
        {
        mgr->AddClassDebug("AliJetContainer", 100);
        mgr->AddClassDebug("AliEmcalJetTask", 100);
        }


//#################################################################
    // Set the physics selection for all given tasks
    TObjArray* toptasks = mgr->GetTasks();

    for ( Int_t i = 0; i < toptasks->GetEntries(); ++i )
        {
        AliAnalysisTaskSE* task = dynamic_cast<AliAnalysisTaskSE*> ( toptasks->At ( i ) );
        if ( !task ) { continue; }
        if ( task->InheritsFrom ( "AliPhysicsSelectionTask" ) ) { continue; }
        ::Info ( "setPSel", "Set physics selection for %s (%s)", task->GetName(), task->ClassName() );
        task->SelectCollisionCandidates ( pSel );
        }

//==========================================
// ######       START ANALYSIS       #######
//==========================================

    if ( mgr->InitAnalysis() )
        {
        cout << "##-->> Initialising Analysis :: Status :" << endl;
        mgr->PrintStatus();

        // grmpf, aliroot error handler overwrites root
        if ( debug == 0 )      { AliLog::SetGlobalLogLevel ( AliLog::kFatal ); }
        else if ( debug == 1 ) { AliLog::SetGlobalLogLevel ( AliLog::kError ); }
        else if ( debug == 2 ) { AliLog::SetGlobalLogLevel ( AliLog::kWarning ); }
        else if ( debug == 3 ) { AliLog::SetGlobalLogLevel ( AliLog::kInfo ); }
        else if ( debug >= 4 ) { AliLog::SetGlobalLogLevel ( AliLog::kDebug ); }

        gErrorIgnoreLevel = kErrorIgnoreLevel;
        if ( gErrorIgnoreLevel > 3000 ) { AliLog::SetGlobalLogLevel ( AliLog::kFatal ); }

        // task profiling
        if ( kUseSysInfo > 0 )
            {
            TFile * fM = TFile::Open ( "manager_local.root", "RECREATE" );
            mgr->Write();
            fM->Close();

            for ( int i = 0; i < mgr->GetTopTasks()->GetEntries(); i++ ) { mgr->ProfileTask (i); }
            }

        mgr->StartAnalysis ( kAnalysisMode.Data(), nentries, firstentry );
        }
        // END of mgr->InitAnalysis()
}


//________________________________________________________________________
void SetJFAccFid( const char* taskname, TString cut = "TPC")
    {
    cut.ToLower();

    AliAnalysisManager* mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) { ::Error("EmcalJetCDF", "No analysis manager to connect to."); }

    AliEmcalJetTask* jf = dynamic_cast<AliEmcalJetTask*>(mgr->GetTask(taskname));
    if (!jf) { AliError("No jet finder in SetJFAccFid()");}

    Float radius = jf->GetRadius();

    Float_t fJetMinEta = -0.9, fJetMaxEta = 0.9 ;
    Float_t fJetMinPhi = -10., fJetMaxPhi = 10. ;

    if ( cut.EqualTo("emcal"))
        {
        fJetMinEta = -0.7   ; fJetMaxEta =  0.7 ;
        fJetMinPhi =  1.405 ; fJetMaxPhi =  3.135 ;

        fJetMinPhi += radius;
        fJetMaxPhi -= radius;
        }

    jf->SetPhiRange( fJetMinPhi, fJetMaxPhi );
    jf->SetEtaRange( fJetMinEta + radius, fJetMaxEta - radius );
    }

//______________________________________________________________________________
void PrintInfoJF ( const char* taskname )
    {
    AliAnalysisManager* mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) { ::Error("EmcalJetCDF", "No analysis manager to connect to."); }

    AliEmcalJetTask* jf = dynamic_cast<AliEmcalJetTask*>(mgr->GetTask(taskname));
    if (!jf) { AliError("No jet finder in PrintInfoJF");}

    cout << "\nJet Finder Task Name : " << jf->GetName() << endl;

    cout << "Track Eta MIN : " << jf->GetEtaMin()    << " ; Track Eta MAX : " << jf->GetEtaMax() << endl;
    cout << "JET Eta MIN : "   << jf->GetJetEtaMin() << " ; JET Eta MAX : "   << jf->GetJetEtaMax() << endl;

    cout << "Track Phi MIN : " << jf->GetPhiMin()    << " ; Track Phi MAX : " << jf->GetPhiMax() << endl;
    cout << "JET Phi MIN : "   << jf->GetJetPhiMin() << " ; JET Phi MAX : "   << jf->GetJetPhiMax() << endl;

    cout << "\n"<< endl;
    }

//______________________________________________________________________________
std::vector<TString> GetJetFinderList()
    {
    AliAnalysisManager* mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) { ::Error("EmcalJetCDF", "No analysis manager to connect to."); }

    TObjArray* tasks_list = mgr->GetTasks(); // get list of of tasks
    std::vector<TString> jf_list; // vector of strings (names of jet finder tasks)

    for ( Int_t t_idx = 0; t_idx < tasks_list->GetEntries(); ++t_idx )
        {
        AliAnalysisTaskSE* task = dynamic_cast<AliAnalysisTaskSE*> ( tasks_list->At ( t_idx ) );
        if ( !task ) { continue; }
        TString task_name = task->GetName();
        if ( task->IsA()->InheritsFrom(AliEmcalJetTask::Class()) ) { jf_list.push_back(task_name); }
        }

    return jf_list;
    }

//______________________________________________________________________________
void PrepareAnalysisEnvironment()
    {
    // get analysis manager
    AliAnalysisManager* mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) { ::Error("EmcalJetCDF::PrepareAnalysisEnvironment()", "No analysis manager to connect to."); }

    // get alien plugin
    AliAnalysisAlien* plugin =  dynamic_cast <AliAnalysisAlien*> ( mgr->GetGridHandler() );
    if ( !plugin ) { ::Error ( "EmcalJetCDF::PrepareAnalysisEnvironment()", "no alien plugin" ); return kFALSE; }

    if ( kCommonOutputFileName.Length() > 0 ) { mgr->SetCommonFileName ( kCommonOutputFileName.Data() ); }

    mgr->SetSkipTerminate ( kSkipTerminate );

//__________________________________________________________________________________
    //////////////////////////////////////////
    ////   LIBRARIES TO BE LOADED BY PLUGIN
    /////////////////////////////////////////
    ListLibs += kGridExtraFiles;

    ListLibs       = ListLibs.Strip();      if ( debug > 3 ) {  Printf ( "### ListLibs : %s", ListLibs.Data() ); }
    ListLibsExtra  = ListLibsExtra.Strip(); if ( debug > 3 ) {  Printf ( "### ListLibsExtra : %s", ListLibsExtra.Data() ); }
    ListSources    = ListSources.Strip();   if ( debug > 3 ) {  Printf ( "### ListSources : %s", ListSources.Data() ); }

    if ( ListLibs.Length() )       { plugin->SetAdditionalLibs     ( ListLibs.Data() ); }
    if ( ListLibsExtra.Length() )  { plugin->SetAdditionalRootLibs ( ListLibsExtra.Data() ); }
    if ( ListSources.Length() )    { plugin->SetAnalysisSource     ( ListSources.Data() ); }

//______________________________________________________________________________
    //******************
    //    DATA INPUT
    //******************
    // Prepare input decisions
    kInputDataLabel = "";

    std::ifstream ifs (kInputStr.Data()); // try to open as file

    if ( ifs.is_open() ) // if input is file
        {
        kDatafile = kInputStr;

        // if input data is file then analysis mode must be local or proof (if forgotten to grid, will revert to local)
        if ( kAnalysisMode.EqualTo("grid") ) { kAnalysisMode = "local" ;}

        // .txt file containing the list of files to be chained in test mode; even if analysis is PROOF (plugin is test)
        plugin->SetFileForTestMode ( kDatafile.Data() );   //fFileForTestMode
        if ( !kFriendChainName.IsNull() ) { plugin->SetFriendChainName(kFriendChainName.Data() ); }
        }
    else if ( kInputStr.IsAscii() ) // either grid (tags from InputData.C) either dataset
        {
        if ( kAnalysisMode.EqualTo("grid"))
            {
            kInputDataLabel = kInputStr ; // input field must corespond with defined tags in InputData.C macro
            gROOT->LoadMacro ( "/data/Work/jets/testEMCalJetFramework/inputdata//InputData.C" );    // Load InputData macro
            if ( !InputData(kInputDataLabel) ) { cout << "Analysis mode is GRID but no InputData.C label was recognized!! exiting..." << endl; gApplication->Terminate(); }
            if ( !kFriendChainName.IsNull() ) { plugin->SetFriendChainName(kFriendChainName.Data() ); }
            }
        else
            {
            kDataset = kInputStr; // all other conditions means kInputStr is a proof dataset name
            if ( !kDataset.BeginsWith("/") ) { cout << "Dataset is not beggining with \"/\". Check the arguments passed to script. exiting..." << endl; gApplication->Terminate();  }
            }
        }
    //++++++++++++++++++++++++++++++++++


    //   *****************************
    //         DATA TYPE SETTINGS
    //   *****************************
    // extract (if possible) the data type from input path
    TString dataPattern   = plugin->GetDataPattern();
    TString file4TestMode = plugin->GetFileForTestMode();

    if ( kPluginMode.EqualTo("test") && ( kAnalysisMode.EqualTo("local") || kAnalysisMode.EqualTo("proof") ) )
        { dataType = FindTreeName(file4TestMode); }
    else
        {
        if (dataPattern.Contains("AliAOD.root")) { dataType = "aod"; }
        if (dataPattern.Contains("AliESD.root")) { dataType = "esd"; }
        }

    if (!dataType.IsNull())
        { cout << "----->>>>>>> Data type : " << dataType.Data() << endl; }
    else
        {
        dataType = "aod";
        cout << "ERROR ----->>>>>>>   Data type IS NULL !!! ; dataType fallback to AOD type" << endl;
        Printf ("ERROR ############   Set dataType by hand in %s at line %d\n",(char*)__FILE__,__LINE__+2);
        }
    // dataType = "esd"; // Here it should be set by hand in case automatic procedure did not work

    //   *****************************
    //         PERIOD SETTINGS
    //   *****************************
    // extract (if possible) the Period from input path
    if ( kPluginMode.EqualTo("test") && ( kAnalysisMode.EqualTo("local") || kAnalysisMode.EqualTo("proof") ) )
        {
        TString data_path = GetInputDataPath (file4TestMode);
        runPeriod = GetPeriod (data_path);
        }
    else
        {
        TString griddatadir = plugin->GetGridDataDir();
        runPeriod = GetPeriod ( griddatadir );
        }

    if (!runPeriod.IsNull())
        { cout << "----->>>>>>> Period : " << runPeriod.Data() << endl; }
    else
        {
        cout << "ERROR ----->>>>>>>   PERIOD IS NULL !!!" << endl;
        Printf ("ERROR ############   Set runPeriod by hand in %s at line %d\n",(char*)__FILE__,__LINE__+2);
        }
    // runPeriod = "lhc10e"; // Here it should be set by hand in case automatic procedure did not work

    cout << "----->>>>>>> Period is MonteCarlo? : " << PeriodIsMC (runPeriod) << endl;

    //   *****************************
    //         PASS SETTINGS
    //   *****************************
    // extract (if possible) the Pass from input path
    if ( kPluginMode.EqualTo("test") && ( kAnalysisMode.EqualTo("local") || kAnalysisMode.EqualTo("proof") ) )
        {
        TString data_path = GetInputDataPath (file4TestMode);
        kPass = GetPass (data_path);
        }
    else
        { kPass = GetPass (dataPattern); }

    cout << "----->>>>>>> Pass is : " << kPass.Data() << endl;

    //<><><><><><><><><><>
    //    DEBUGGING
    //<><><><><><><><><><>
    mgr->SetDebugLevel(debug);

    // Event frequency for collecting system information
    mgr->SetNSysInfo ( kUseSysInfo );

    if ( kUseSysInfo > 0 )
        {
        mgr->RegisterExtraFile ( "syswatch.root" );

        if ( kGridMergeExclude.Length() ) { kGridMergeExclude += " "; }
        kGridMergeExclude += "syswatch.root";
        }

    //********************
    //    DATA OUTPUT
    //********************
    plugin->SetMergeExcludes  ( kGridMergeExclude );
    plugin->SetDefaultOutputs ( kTRUE );


//______________________________________________________________________________
// handlers definition
    if ( dataType.EqualTo("aod") )
        {
        gROOT->LoadMacro ( "$ALICE_ROOT/ANALYSIS/macros/train/AddAODHandler.C" );
        AliAODInputHandler* aodH = AddAODHandler();
        aodH->SetCheckStatistics ( kTRUE );
        }
    else
    if ( dataType.EqualTo("esd") || dataType.EqualTo("sesd") )
        {
        gROOT->LoadMacro ( "$ALICE_ROOT/ANALYSIS/macros/train/AddESDHandler.C" );
        AliESDInputHandler* esdH = AddESDHandler();
        }
    else
        { cout << "Data type not recognized! You have to specify ESD, AOD, or sESD!\n"; return; }

    // Create MC handler, if MC is demanded
    if ( isMC && !dataType.EqualTo("aod") )
        {
        gROOT->LoadMacro ( "$ALICE_ROOT/ANALYSIS/macros/train/AddMCHandler.C" );
        AliMCEventHandler* mcH = AddMCHandler (kTRUE);
        }

    // somehow required by LHC10d
    ((AliInputEventHandler*)mgr->GetInputEventHandler())->SetNeedField();

    return;
    }

//______________________________________________________________________________
void LoadLibs ()
    {
    TString list_fj         = "fastjet siscone siscone_spherical fastjetplugins fastjettools fastjetcontribfragile";
    TString list_root       = "Tree VMC Geom Gui XMLParser Minuit Minuit2 Proof Physics";
    TString list_alicebase  = "STEERBase ESD AOD OADB ANALYSIS CDB RAWDatabase STEER EVGEN ANALYSISalice ESDfilter CORRFW TENDER TENDERSupplies STAT";
    TString list_alicemisc1 = "RAWDatabase RAWDatarec TPCbase TPCrec ITSbase ITSrec TRDbase  TRDbase TRDrec HMPIDbase PWGPP PWGHFbase PWGDQdielectron PWGHFhfe PWGCaloTrackCorrBase TOFbase VZERObase VZEROrec";
    TString list_alicejets  = "EMCALUtils PHOSUtils EMCALraw EMCALbase EMCALrec PWGTools PWGEMCAL PWGGAEMCALTasks PWGTools PWGCFCorrelationsBase PWGCFCorrelationsDPhi JETAN FASTJETAN PWGJEEMCALJetTasks PWGJEFlavourJetTasks";

    LoadLibList (list_fj);
    LoadLibList (list_root);
    LoadLibList (list_alicebase);
    LoadLibList (list_alicemisc1);
    LoadLibList (list_alicejets);

    ::Info ( "EmcalJetCDF::LoadROOTLibs", "Load ROOT libraries:    SUCCESS" );

    // include paths
    gSystem->AddIncludePath ( "-Wno-deprecated" );
    gSystem->AddIncludePath ( "-I$. -I$ROOTSYS/include -I$CGAL_DIR/include -I$FASTJET/include -I$ALICE_ROOT/include -I$ALICE_ROOT/JETAN -I$ALICE_ROOT/EMCAL" );
//     gSystem->AddIncludePath("-I$ALICE_ROOT/PWGDQ/dielectron -I$ALICE_ROOT/PWGHF/hfe");
    }

//______________________________________________________________________________
AliAnalysisAlien* CreateAlienHandler ( const char* plugin_mode = "test" )
    {
    AliAnalysisAlien* plugin = new AliAnalysisAlien();

    if ( !plugin ) { cout << "!!! -->> alien handler could not be created <<-- !!!" << endl; return;}

    //********************   PLUGIN OPTIONS   ************************
    // exit from aliensh after submmiting job
    plugin->SetDropToShell ( kTRUE );

    // Set the run mode (can be "full", "test", "offline", "submit" or "terminate")
    plugin->SetRunMode ( plugin_mode );

    plugin->SetCheckCopy ( kFALSE );

    // min (nr,4) replicas in grid storage
    plugin->SetNumberOfReplicas(2);

    // Set the number of test files; set to kGridFilesPerJob as to evaluate the memory consumption and ttl on grid
    plugin->SetNtestFiles ( kTestFiles );

    if ( kPluginUseProductionMode ) { plugin->SetProductionMode(); }

    plugin->SetExecutableCommand ( kPluginExecutableCommand.Data() );
    plugin->SetJobTag ( kJobTag );

    // Set versions of used packages
    plugin->SetAPIVersion     ( kPluginAPIVersion );
    plugin->SetROOTVersion    ( kPluginRootVersion );
    plugin->SetAliROOTVersion ( kPluginAliRootVersion );

    // Add external packages
    plugin->AddExternalPackage ( kPackage1.Data() );
    plugin->AddExternalPackage ( kPackage2.Data() );
    plugin->AddExternalPackage ( kPackage3.Data() );

    // Use fastread option
    plugin->SetFastReadOption ( kPluginFastReadOption );

    // UseOverwrite mode
    plugin->SetOverwriteMode ( kPluginOverwriteMode );

    // Optionally set a name for the generated analysis macro (default MyAnalysis.C)
    plugin->SetAnalysisMacro ( Form ( "%s.C", kTrainName.Data() ) );

    // Optionally modify the name of the generated JDL (default analysis.jdl)
    plugin->SetJDLName ( Form ( "%s.jdl", kTrainName.Data() ) );

    // Optionally modify the executable name (default analysis.sh)
    plugin->SetExecutable ( Form ( "%s.sh", kTrainName.Data() ) );

    // Optionally set maximum number of input files/subjob (default 100, put 0 to ignore)
    plugin->SetSplitMaxInputFileNumber ( kGridFilesPerJob );

    // Optionally set maximum number of files merged in a chunk (default 100, put 0 to ignore)
    plugin->SetMaxMergeFiles ( kGridMaxMergeFiles );

    // Maximum initial consecutive subjobs accepted to fail.
    plugin->SetMaxInitFailed ( kMaxInitFailed );

    // Optionally resubmit threshold.
    // plugin->SetMasterResubmitThreshold(90);

    // Optionally set time to live
    plugin->SetTTL ( kTTL );

    // Optionally set input format (default xml-single)
    plugin->SetInputFormat("xml-single");

    // Optionally modify job price (default 1)
    plugin->SetPrice(1);

    // Number of runs per masterjob
    plugin->SetNrunsPerMaster(1);

    // Enable merging via automatic JDL
    plugin->SetMergeViaJDL(kTRUE);

    // write the output to subdirs named after run number
    plugin->SetOutputToRunNo(1);

    // AliEn directory containing the input packages
    if ( kGridDataSet.Length() > 0 ) { kWorkDir += Form ( "/%s%s", kGridDataSet.Data(), kGridExtraAliendirLevel.Data() ); }
    plugin->SetGridWorkingDir ( kWorkDir.Data() );

    // Declare alien output directory. Relative to working directory.
    if ( !kGridOutdir.Length() ) { kGridOutdir = Form ( "out_%s", kTrainName.Data() ); }
    plugin->SetGridOutputDir ( kGridOutdir );


    //-----------------------------------------------
    //           PROOF SETTINGS
    //-----------------------------------------------
    plugin->SetProofCluster  ( kAAF )        ;
    plugin->SetProofDataSet  ( kDataset )    ;
    plugin->SetProofReset    ( kProofReset ) ;
    plugin->SetNproofWorkers ( kWorkers )    ;
    // plugin->SetNproofWorkersPerSlave( kCores)  ;
    // plugin->SetRootVersionForProof ( kPluginRootVersion ) ;
    plugin->SetAliRootMode ( kAlirootMode ) ;

    // plugin->SetProofParameter(const char *pname, const char *value);

    return plugin;
    }

//______________________________________________________________________________
Bool_t LoadLibrary ( const char* module )
    {
    Int_t result = -999 ; TString mod ( module );

    if ( !mod.Length() ) { ::Error ( "AnalysisCDFjets::LoadLibrary", "Empty module name" ); return kFALSE; }

    if ( mod.EndsWith ( ".so" ) ) { mod.Remove ( mod.Index ( ".so" ) ); }

    result = gSystem->Load ( mod );

    if ( result < 0 ) { ::Error ( "EmcalJetCDF::LoadLibrary", "Could not load library %s", module ); return kFALSE; }

    ListLibs      += Form ( "%s.so ", mod.Data() );
    ListLibsExtra += Form ( "%s.so ", mod.Data() );

    return kTRUE;
    }

//______________________________________________________________________________
void LoadLibList ( const TString& list )
    {
    TObjArray *arr;
    TObjString *objstr;
    arr = list.Tokenize(" ");
    TIter next(arr);
    while ( (objstr=(TObjString*)next()) )
        {
        TString module = objstr->GetString();
        module.Prepend("lib");
        if ( !LoadLibrary (module.Data()) ) { gApplication->Terminate(); }
        }
    delete arr;
    }

//______________________________________________________________________________
Bool_t LoadPars ( const char* module )
    {
    AliAnalysisManager* mgr = AliAnalysisManager::GetAnalysisManager();
    if ( !mgr ) { ::Error ( "LoadPars", "No analysis manager to connect to." ); return kFALSE; }

    AliAnalysisAlien* plugin =  dynamic_cast <AliAnalysisAlien*> ( mgr->GetGridHandler() );
    if ( !plugin ) { ::Error ( "LoadPars", "InputData :: plugin invalid" ); return kFALSE; }

    // Load a module library in a given mode. Reports success.
    Int_t result = -999; Bool_t success = kTRUE;

    TString mod ( module );

    if ( !mod.Length() ) { ::Error ( "EmcalJetCDF::LoadPars", "Empty module name" ); return kFALSE; }

    if ( !plugin->SetupPar ( module ) ) { return kFALSE; }

    mod += ".par"; plugin->EnablePackage ( mod.Data() ); // anaPars += mod.Data();

    mod.ReplaceAll(".par",".so"); mod.Prepend("lib");
    result = gSystem->Load(mod);

    if ( result < 0 ) { cout << "Load PARs : Load library failed : " << mod.Data() << endl; return kFALSE ; }

    return success;
    }

//______________________________________________________________________________
Bool_t LoadSource ( const char* source, Bool_t rec = kFALSE )
    {
    // Load a module library in a given mode. Reports success.
    Int_t result = -1;
    TString ssource ( source );
    TString basename = gSystem->BaseName ( ssource.Data() );

    if ( !ssource.Length() ) { ::Error ( "EmcalJetCDF::LoadSource", "Empty task name" ); return kFALSE; }

    // we have a source code so compile it
    if ( ssource.EndsWith ( ".cxx" ) )
        {
        // need to copy it here otherwise the path is also used on grid...
        ssource.Remove ( ssource.Index ( ".cxx" ) );
        basename.Remove ( basename.Index ( ".cxx" ) );
        Printf ( "LoadSources:: Copying...  path %s{cxx,h}", ssource.Data() );
        gSystem->Exec ( Form ( "cp %s.cxx . ", ssource.Data() ) );
        gSystem->Exec ( Form ( "cp %s.h . ", ssource.Data() ) );

        // Path to code only needed for local compilation, in grid and proof mode the task headers are uploaded
        //     path.Remove(path.Index(gSystem->BaseName(path.Data())));
        // Printf("LoadSources:: Including path %s",path.Data());
        //  if(path.Length()>0)gROOT->ProcessLine(Form(".include %s",path.Data()));
        Printf ( "LoadSources:: Loading...  path %s", basename.Data() );

        result = gROOT->LoadMacro ( Form ( "%s.cxx++g", basename.Data() ) );

        if ( rec )
            {
            // what we want to compile
            ListSources += Form ( "%s.cxx ", basename.Data() );
            // what we need as input...
            ListLibs += Form ( "%s.cxx %s.h ", basename.Data(), basename.Data() );
            }
        }


    if ( result < 0 ) { ::Error ( "EmcalJetsCDF::LoadSources", "Could not load source %s", source ); return kFALSE; }

    return kTRUE;
    }


//______________________________________________________________________________
TString FindTreeName ( const TString& file_list ) const
    {
    TString fDataType = "";  // result
    if ( gSystem->AccessPathName ( file_list.Data() ) )
            { cout << "File not found: " << file_list.Data() << endl; return fDataType; }

    // Open the file
    ifstream in; in.open ( file_list.Data() );
    Int_t count = 0;
    TString line;

    while ( in.good() )
        {
        in >> line;
        if ( line.IsNull() || line.BeginsWith ( "#" ) ) continue;
        if ( count++ == 1 ) break; // look only over first file;

        TString file ( line );

        // STRICT ORDERING!!! If multiple tree types found last valid will be preffered
        if (IsTreeType(file,"TreeK"))      { fDataType = "kine";    }
        if (IsTreeType(file,"TE"))         { fDataType = "galice";  }
        if (IsTreeType(file,"HLTESDTree")) { fDataType = "hltesd";  }
        if (IsTreeType(file,"esdTree"))    { fDataType = "esd";     }
        if (IsTreeType(file,"aodTree"))    { fDataType = "aod";     }

        return fDataType;
        }
    in.close();
    return fDataType ;
    }

//______________________________________________________________________________
Bool_t IsTreeType ( const TString& fileInput, const TString& treeName)
    {
    TFile* f = TFile::Open (fileInput.Data());

    if ( f->IsZombie() )
        { cout << " :: Skipping un-openable file: << " << fileInput.Data()  << endl; return kFALSE; }
    else
        {
        TKey* key = f->FindKeyAny (treeName.Data());
        if (key) { f->Close(); return kTRUE;  }
        else     { f->Close(); return kFALSE; }
        }
    }

//______________________________________________________________________________
TString GetInputDataPath ( const TString& file_list)
    {
    std::string line_str;
    TString line = line_str.c_str();

    if ( gSystem->AccessPathName ( file_list.Data() ) )
        { cout << "File not found: " << file_list.Data() << endl; return line; }

    // Open the file
    ifstream in; in.open ( file_list.Data() );
    Int_t count = 0;

    while ( in.good() )
        {
        in >> line_str;
        line = line_str.c_str();
        if ( line.IsNull() || line.BeginsWith ( "#" ) ) { continue; }
        if ( count == 1 ) { break; }  // look only over first file;
        count++;
        }
    in.close();
    line = line_str.c_str();
    return line;
    }

//______________________________________________________________________________
TString GetPeriod ( const TString& file_path)
    {
    TString period = "";

    if (!file_path.IsNull())
        {
        // split string in tokens (libs)
        TObjArray* tokens_list = file_path.Tokenize("/"); //tokens_list->Compress();
        TIter next_str(tokens_list);
        TObjString* token = NULL;
        Int_t j=0;
        while ((token=(TObjString*)next_str()))
            {
            TString token_str = token->GetString(); token_str.ToLower();
            if ( token_str.Contains("lhc") ) { period = token_str; }
            }
        delete tokens_list;
        }

    return period;
    }

//______________________________________________________________________________
TString GetPass ( const TString& file_path)
    {
    TString pass = "";

    if (!file_path.IsNull())
        {
        // split string in tokens (libs)
        TObjArray* tokens_list = file_path.Tokenize("/"); //tokens_list->Compress();
        TIter next_str(tokens_list);
        TObjString* token=0;
        Int_t j=0;
        while ((token=(TObjString*)next_str()))
            {
            TString token_str = token->GetString(); token_str.ToLower();
            if ( token_str.Contains("pass") ) { pass = token_str; }
            }
        delete tokens_list;
        }

    return pass;
    }

//______________________________________________________________________________
Bool_t PeriodIsMC ( const TString& period )
    {
    if (!period.IsNull())
        {
        period.ToLower();
        if ( period.BeginsWith("lhc") && (period.Length() > 6) ) {return kTRUE;}
        }
    return kFALSE;
    }


// kate: indent-mode none; indent-width 4; replace-tabs on;
