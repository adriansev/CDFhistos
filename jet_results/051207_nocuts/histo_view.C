{
   // Get histograms from file
   TFile *file = TFile::Open("hresults.root");
   if (!file) {
      Error("FinishRun", "No output file histos.root");
      return;
   }
   TCanvas *c1 = new TCanvas("c1","Pt",10,10,600,600);
   c1->SetFillColor(10);
   c1->SetHighLightColor(10);

   TCanvas *c2 = new TCanvas("c2","Pt",10,10,600,600);
   c2->SetFillColor(10);
   c2->SetHighLightColor(10);

   TCanvas *c3 = new TCanvas("c3","Pt",10,10,600,600);
   c3->SetFillColor(10);
   c3->SetHighLightColor(10);

   TCanvas *c4 = new TCanvas("c4","Pt",10,10,600,600);
   c4->SetFillColor(10);
   c4->SetHighLightColor(10);

   TCanvas *c5 = new TCanvas("c5","Pt",10,10,600,600);
   c5->SetFillColor(10);
   c5->SetHighLightColor(10);

   TCanvas *c6 = new TCanvas("c6","Pt",10,10,600,600);
   c6->SetFillColor(10);
   c6->SetHighLightColor(10);

   TCanvas *c7 = new TCanvas("c7","Pt",10,10,600,600);
   c7->SetFillColor(10);
   c7->SetHighLightColor(10);



   TH1F *h1 = (TH1F*)file->Get("histo1");
   TH1F *h2 = (TH1F*)file->Get("histo2");
   TProfile *h3 = (TProfile*)file->Get("histo3");
   TH1F *h4 = (TH1F*)file->Get("histo4");
   TProfile *h5 = (TProfile*)file->Get("histo5");
   TH1F *h6 = (TH1F*)file->Get("histo6");


   if (h1) {
      c1->cd();
      h1->Sumw2();
      h1->Scale(1./1300000);
      c1->SetLogy();
      h1->DrawCopy("E");
   }
   if (h2) {
      c2->cd();
      h2->Sumw2();
      h2->Scale(1./1300000);
      h2->DrawCopy("");
   }
   if (h3) {
      c3->cd(); //->SetLogy();
      h3->DrawCopy(); //"E");
   }
   if (h4) {
      c4->cd()->SetLogy();
      h4->DrawCopy();//"E");
   }

   if (h5) {
      c5->cd(); //->SetLogy();
      h5->DrawCopy();//"E");
   }

   if (h6) {
      c6->cd(); 
      h6->Sumw2();
      h6->Scale(1./1300000);
      c6->SetLogy();
      h6->DrawCopy();//"E");
   }






































}
