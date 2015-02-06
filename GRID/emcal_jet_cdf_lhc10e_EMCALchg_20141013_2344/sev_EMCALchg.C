const char *anatype = "AOD";

void sev_EMCALchg()
{
// Analysis using AOD data
// Automatically generated analysis steering macro executed in grid subjobs

   TStopwatch timer;
   timer.Start();

// connect to AliEn and make the chain
   if (!TGrid::Connect("alien://")) return;
// Set temporary merging directory to current one
   gSystem->Setenv("TMPDIR", gSystem->pwd());

// Set temporary compilation directory to current one
   gSystem->SetBuildDir(gSystem->pwd(), kTRUE);

// Reset existing include path and add current directory first in the search
   gSystem->SetIncludePath("-I.");
// Add aditional libraries
   gSystem->Load("libCGAL.so");
   gSystem->Load("libfastjet.so");
   gSystem->Load("libsiscone.so");
   gSystem->Load("libsiscone_spherical.so");
   gSystem->Load("libfastjetplugins.so");
   gSystem->Load("libfastjettools.so");
   gSystem->Load("libfastjetcontribfragile.so");
   gSystem->Load("libTree.so");
   gSystem->Load("libVMC.so");
   gSystem->Load("libGeom.so");
   gSystem->Load("libGui.so");
   gSystem->Load("libXMLParser.so");
   gSystem->Load("libMinuit.so");
   gSystem->Load("libMinuit2.so");
   gSystem->Load("libProof.so");
   gSystem->Load("libPhysics.so");
   gSystem->Load("libSTEERBase.so");
   gSystem->Load("libESD.so");
   gSystem->Load("libAOD.so");
   gSystem->Load("libOADB.so");
   gSystem->Load("libANALYSIS.so");
   gSystem->Load("libCDB.so");
   gSystem->Load("libRAWDatabase.so");
   gSystem->Load("libSTEER.so");
   gSystem->Load("libEVGEN.so");
   gSystem->Load("libANALYSISalice.so");
   gSystem->Load("libESDfilter.so");
   gSystem->Load("libCORRFW.so");
   gSystem->Load("libTENDER.so");
   gSystem->Load("libTENDERSupplies.so");
   gSystem->Load("libSTAT.so");
   gSystem->Load("libRAWDatabase.so");
   gSystem->Load("libRAWDatarec.so");
   gSystem->Load("libTPCbase.so");
   gSystem->Load("libTPCrec.so");
   gSystem->Load("libITSbase.so");
   gSystem->Load("libITSrec.so");
   gSystem->Load("libTRDbase.so");
   gSystem->Load("libTRDbase.so");
   gSystem->Load("libTRDrec.so");
   gSystem->Load("libHMPIDbase.so");
   gSystem->Load("libPWGPP.so");
   gSystem->Load("libPWGHFbase.so");
   gSystem->Load("libPWGDQdielectron.so");
   gSystem->Load("libPWGHFhfe.so");
   gSystem->Load("libPWGCaloTrackCorrBase.so");
   gSystem->Load("libTOFbase.so");
   gSystem->Load("libVZERObase.so");
   gSystem->Load("libVZEROrec.so");
   gSystem->Load("libEMCALUtils.so");
   gSystem->Load("libPHOSUtils.so");
   gSystem->Load("libEMCALraw.so");
   gSystem->Load("libEMCALbase.so");
   gSystem->Load("libEMCALrec.so");
   gSystem->Load("libPWGTools.so");
   gSystem->Load("libPWGEMCAL.so");
   gSystem->Load("libPWGGAEMCALTasks.so");
   gSystem->Load("libPWGTools.so");
   gSystem->Load("libPWGCFCorrelationsBase.so");
   gSystem->Load("libPWGCFCorrelationsDPhi.so");
   gSystem->Load("libJETAN.so");
   gSystem->Load("libFASTJETAN.so");
   gSystem->Load("libPWGJEEMCALJetTasks.so");
// Load analysis framework libraries
   gSystem->Load("libANALYSIS");
   gSystem->Load("libOADB");
   gSystem->Load("libANALYSISalice");
   gSystem->Load("libCORRFW");

// include path
   TString intPath = gInterpreter->GetIncludePath();
   TObjArray *listpaths = intPath.Tokenize(" ");
   TIter nextpath(listpaths);
   TObjString *pname;
   while ((pname=(TObjString*)nextpath())) {
      TString current = pname->GetName();
      if (current.Contains("AliRoot") || current.Contains("ALICE_ROOT")) continue;
      gSystem->AddIncludePath(current);
   }
   if (listpaths) delete listpaths;
   gROOT->ProcessLine(".include $ALICE_ROOT/include");
   printf("Include path: %s\n", gSystem->GetIncludePath());

// Add aditional AliRoot libraries
   gSystem->Load("libCGAL.so");
   gSystem->Load("libfastjet.so");
   gSystem->Load("libsiscone.so");
   gSystem->Load("libsiscone_spherical.so");
   gSystem->Load("libfastjetplugins.so");
   gSystem->Load("libfastjettools.so");
   gSystem->Load("libfastjetcontribfragile.so");
   gSystem->Load("libTree.so");
   gSystem->Load("libVMC.so");
   gSystem->Load("libGeom.so");
   gSystem->Load("libGui.so");
   gSystem->Load("libXMLParser.so");
   gSystem->Load("libMinuit.so");
   gSystem->Load("libMinuit2.so");
   gSystem->Load("libProof.so");
   gSystem->Load("libPhysics.so");
   gSystem->Load("libSTEERBase.so");
   gSystem->Load("libESD.so");
   gSystem->Load("libAOD.so");
   gSystem->Load("libOADB.so");
   gSystem->Load("libANALYSIS.so");
   gSystem->Load("libCDB.so");
   gSystem->Load("libRAWDatabase.so");
   gSystem->Load("libSTEER.so");
   gSystem->Load("libEVGEN.so");
   gSystem->Load("libANALYSISalice.so");
   gSystem->Load("libESDfilter.so");
   gSystem->Load("libCORRFW.so");
   gSystem->Load("libTENDER.so");
   gSystem->Load("libTENDERSupplies.so");
   gSystem->Load("libSTAT.so");
   gSystem->Load("libRAWDatabase.so");
   gSystem->Load("libRAWDatarec.so");
   gSystem->Load("libTPCbase.so");
   gSystem->Load("libTPCrec.so");
   gSystem->Load("libITSbase.so");
   gSystem->Load("libITSrec.so");
   gSystem->Load("libTRDbase.so");
   gSystem->Load("libTRDbase.so");
   gSystem->Load("libTRDrec.so");
   gSystem->Load("libHMPIDbase.so");
   gSystem->Load("libPWGPP.so");
   gSystem->Load("libPWGHFbase.so");
   gSystem->Load("libPWGDQdielectron.so");
   gSystem->Load("libPWGHFhfe.so");
   gSystem->Load("libPWGCaloTrackCorrBase.so");
   gSystem->Load("libTOFbase.so");
   gSystem->Load("libVZERObase.so");
   gSystem->Load("libVZEROrec.so");
   gSystem->Load("libEMCALUtils.so");
   gSystem->Load("libPHOSUtils.so");
   gSystem->Load("libEMCALraw.so");
   gSystem->Load("libEMCALbase.so");
   gSystem->Load("libEMCALrec.so");
   gSystem->Load("libPWGTools.so");
   gSystem->Load("libPWGEMCAL.so");
   gSystem->Load("libPWGGAEMCALTasks.so");
   gSystem->Load("libPWGTools.so");
   gSystem->Load("libPWGCFCorrelationsBase.so");
   gSystem->Load("libPWGCFCorrelationsDPhi.so");
   gSystem->Load("libJETAN.so");
   gSystem->Load("libFASTJETAN.so");
   gSystem->Load("libPWGJEEMCALJetTasks.so");

// analysis source to be compiled at runtime (if any)
   gROOT->ProcessLine(".L AliAnalysisTaskEmcalJetCDF.cxx+g");

// read the analysis manager from file
   AliAnalysisManager *mgr = AliAnalysisAlien::LoadAnalysisManager("sev_EMCALchg.root");
   if (!mgr) return;
   mgr->PrintStatus();
   AliLog::SetGlobalLogLevel(AliLog::kError);
   TChain *chain = CreateChain("wn.xml", anatype);

   mgr->StartAnalysis("localfile", chain);
   timer.Stop();
   timer.Print();
}

//________________________________________________________________________________
TChain* CreateChain(const char *xmlfile, const char *type="ESD")
{
// Create a chain using url's from xml file
   TString filename;
   Int_t run = 0;
   TString treename = type;
   treename.ToLower();
   treename += "Tree";
   printf("***************************************\n");
   printf("    Getting chain of trees %s\n", treename.Data());
   printf("***************************************\n");
   TAlienCollection *coll = TAlienCollection::Open(xmlfile);
   if (!coll) {
      ::Error("CreateChain", "Cannot create an AliEn collection from %s", xmlfile);
      return NULL;
   }
   AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
   TChain *chain = new TChain(treename);
   coll->Reset();
   while (coll->Next()) {
      filename = coll->GetTURL();
      if (mgr) {
         Int_t nrun = AliAnalysisManager::GetRunFromAlienPath(filename);
         if (nrun && nrun != run) {
            printf("### Run number detected from chain: %d\n", nrun);
            mgr->SetRunFromPath(nrun);
            run = nrun;
         }
      }
      chain->Add(filename);
   }
   if (!chain->GetNtrees()) {
      ::Error("CreateChain", "No tree found from collection %s", xmlfile);
      return NULL;
   }
   return chain;
}

