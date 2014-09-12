AliAnalysisTaskEmcalJetCDF* AddTaskEmcalJetCDF(
  const char* ntracks            = "Tracks",
  const char* nclusters          = "CaloClusters",
  const char* njets              = "Jets",
  const char* nrho               = "Rho",
  Double_t    jetradius          = 0.2,
  Double_t    jetptcut           = 1.,
  Double_t    jetareacut         = 0.001,
  const char* type               = "TPC",
  Int_t       leadhadtype        = 0,                 // AliJetContainer :: Int_t fLeadingHadronType;  0 = charged, 1 = neutral, 2 = both
  const char* taskname           = "JetCDF"
)
{
    // Get the pointer to the existing analysis manager via the static access method.
    //==============================================================================
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) { ::Error("AddTaskEmcalJetCDF", "No analysis manager to connect to.");  return NULL; }

    // Check the analysis type using the event handlers connected to the analysis manager.
    //==============================================================================
    if (!mgr->GetInputEventHandler()) { ::Error("AddTaskEmcalJetCDF", "This task requires an input event handler"); return NULL; }

    //-------------------------------------------------------
    // Init the task and do settings
    //-------------------------------------------------------

    TString name(taskname); TString tracks (ntracks);
    TString clusters (nclusters); TString jets (njets);  TString rho (nrho);
    TString stype (type);

    if (jetptcut < 1. ) { jetptcut = 1.; }
    TString jetstr = "jpt" + (ULong_t)(jetptcut*1000);

    if ( !jets.IsNull() )  { name += "_" + jets; }
    name += "_" + jetstr;
    if ( !rho.IsNull()  )  { name += "_" + rho; }
    if ( !stype.IsNull() ) { name += "_" + stype; }

    cout << "CDF Jet task name : " << name.Data() << endl;

    AliAnalysisTaskEmcalJetCDF* jetTask = new AliAnalysisTaskEmcalJetCDF(name);

    AliParticleContainer* trackCont  = jetTask->AddParticleContainer(ntracks);
    trackCont->SetClassName("AliVTrack");

    AliClusterContainer* clusterCont = jetTask->AddClusterContainer(nclusters);
    clusterCont->SetClassName("AliVCluster");

    AliJetContainer* jetCont = jetTask->AddJetContainer(njets,stype,jetradius);
    if ( jetCont )
        {
        jetCont->SetRhoName(nrho);
        jetCont->ConnectParticleContainer(trackCont);
        jetCont->ConnectClusterContainer(clusterCont);
        jetCont->SetPercAreaCut(jetareacut);
        jetCont->SetJetPtCut(jetptcut);
        jetCont->SetLeadingHadronType(leadhadtype); // Int_t fLeadingHadronType;  0 = charged, 1 = neutral, 2 = both
        jetCont->SetZLeadingCut(0.9999,0.9999);
        }

    //-------------------------------------------------------
    // Final settings, pass to manager and set the containers
    //-------------------------------------------------------
    mgr->AddTask(jetTask);

    TString contname(name); contname += "_histos";
    // Create containers for input/output
    AliAnalysisDataContainer *cinput1  = mgr->GetCommonInputContainer()  ;
    AliAnalysisDataContainer *coutput1 = mgr->CreateContainer ( contname.Data(), TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s", AliAnalysisManager::GetCommonFileName()) );

    mgr->ConnectInput  (jetTask, 0,  cinput1 );
    mgr->ConnectOutput (jetTask, 1, coutput1 );

    return jetTask;
}

AliAnalysisTaskEmcalJetCDF* AddTaskEmcalJetCDF ( AliEmcalJetTask* jetFinderTask,
    Double_t     jetptcut     = 1.,
    Double_t     jetareacut   = 0.001,
    const char*  type         = "TPC",   // EMCAL, TPC
    Int_t        leadhadtype  = 0,         // AliJetContainer :: Int_t fLeadingHadronType;  0 = charged, 1 = neutral, 2 = both
    const char*  taskname     = "JetCDF" )
{
    const char* ntracks            = jetFinderTask->GetTracksName();
    const char* nclusters          = jetFinderTask->GetClusName();
    const char* njets              = jetFinderTask->GetJetsName();
    const char* nrho               = jetFinderTask->GetRhoName();
    Double_t    jetradius          = jetFinderTask->GetRadius();

return AddTaskEmcalJetCDF ( ntracks , nclusters, njets, nrho, jetradius, jetptcut, jetareacut, type, leadhadtype, taskname);

}

