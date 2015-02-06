void sev_EMCALchg_merge(const char *dir, Int_t stage=0)
{
// Automatically generated merging macro executed in grid subjobs

   TStopwatch timer;
   timer.Start();

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

// Analysis source to be compiled at runtime (if any)
   gROOT->ProcessLine(".L AliAnalysisTaskEmcalJetCDF.cxx+g");

// Connect to AliEn
   if (!TGrid::Connect("alien://")) return;
// Set temporary merging directory to current one
   gSystem->Setenv("TMPDIR", gSystem->pwd());

// Set temporary compilation directory to current one
   gSystem->SetBuildDir(gSystem->pwd(), kTRUE);

   TString outputDir = dir;
   TString outputFiles = "EventStat_temp.root,AnalysisResults.root,CDFanalysis.root";
   TString mergeExcludes = "AliAOD.root AliAOD.Jets.root ";
   TObjArray *list = outputFiles.Tokenize(",");
   TIter *iter = new TIter(list);
   TObjString *str;
   TString outputFile;
   Bool_t merged = kTRUE;
   AliAnalysisManager *mgr = AliAnalysisAlien::LoadAnalysisManager("sev_EMCALchg.root");
   if (!mgr) {
      printf("ERROR: Analysis manager could not be extracted from file ");
      return;
   }
   while((str=(TObjString*)iter->Next())) {
      outputFile = str->GetString();
      if (outputFile.Contains("*")) continue;
      Int_t index = outputFile.Index("@");
      if (index > 0) outputFile.Remove(index);
      // Skip already merged outputs
      if (!gSystem->AccessPathName(outputFile)) {
         printf("Output file <%s> found. Not merging again.\n",outputFile.Data());
         continue;
      }
      if (mergeExcludes.Contains(outputFile.Data())) continue;
      merged = AliAnalysisAlien::MergeOutput(outputFile, outputDir, 100, stage);
      if (!merged) {
         printf("ERROR: Cannot merge %s\n", outputFile.Data());
         return;
      }
   }
   // all outputs merged, validate
   ofstream out;
   out.open("outputs_valid", ios::out);
   out.close();
   // read the analysis manager from file
   if (!outputDir.Contains("Stage")) return;
   mgr->SetRunFromPath(mgr->GetRunFromAlienPath(dir));
   mgr->SetSkipTerminate(kFALSE);
   mgr->PrintStatus();
   AliLog::SetGlobalLogLevel(AliLog::kError);
   TTree *tree = NULL;
   mgr->StartAnalysis("gridterminate", tree);
}

