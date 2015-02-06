static  int      myDarkRed     = TColor::GetColor(128,0,0);
static  int      myDarkGreen   = TColor::GetColor(0,128,0);
static  int      myDarkBlue    = TColor::GetColor(0,0,128);

void fig_template(Int_t rWrite = 0, Int_t rPerformance = 0){

  myOptions();
  gROOT->ForceStyle();

  TDatime now;
  int iDate = now.GetDate();
  int iYear=iDate/10000;
  int iMonth=(iDate%10000)/100;
  int iDay=iDate%100;
  char* cMonth[12]={"Jan","Feb","Mar","Apr","May","Jun",
		    "Jul","Aug","Sep","Oct","Nov","Dec"};
  char cStamp1[25],cStamp2[25];
  sprintf(cStamp1,"%i %s %i",iDay, cMonth[iMonth-1], iYear);
  sprintf(cStamp2,"%i/%.2d/%i",iDay, iMonth, iYear);


  TCanvas *myCan = new TCanvas("myCan",cStamp1);
  myCan->Draw();
  myCan->cd();

  TPad *myPad = new TPad("myPad", "The pad",0,0,1,1);
  myPadSetUp(myPad,0.15,0.04,0.04,0.15);
  myPad->Draw();
  myPad->cd();

  TH1F *myBlankHisto = new TH1F("myBlankHisto","Blank Histogram",20,0,10);
  myBlankHisto->SetMaximum(100);
  myBlankHisto->SetYTitle("Title&units e.g. (Counts per 100 MeV/c)");
  myBlankHisto->SetXTitle("Title&units e.g. (GeV/c)");
  myBlankHisto->SetNdivisions(505,"y");
  myBlankHisto->Draw();

  TLatex *system = new TLatex(0.3,0.92,"e.g. pp or Pb-Pb events at #sqrt{s_{NN}} = 2.76 TeV");
  system->SetNDC();
  //  system->SetTextFont(42);
  system->SetTextSize(0.04);
  system->SetTextColor(myDarkRed);
  system->Draw();

  TLegend *myLegend = new TLegend(0.6,0.7,0.9,0.8);
  myLegendSetUp(myLegend,0.04);
  myLegend->AddEntry(myBlankHisto,"legend with units","");
  myLegend->AddEntry(myBlankHisto,"e.g. p_{T}>300 MeV/c","");
  myLegend->Draw();

  if (rPerformance){
    TLatex *alice = new TLatex(0.75,0.34,"Performance");
    alice->SetNDC();
    alice->SetTextColor(myDarkRed);
    //    alice->SetTextFont(42);
    alice->SetTextSize(0.05);
    alice->SetLineWidth(2);
    alice->Draw();

    TText *date = new TText(0.78,0.28,cStamp2);
    date->SetNDC();
    date->SetTextFont(42);
    date->SetTextSize(0.04);
    date->Draw();

    //Acquire canvas proportions 
    Double_t AliLogo_LowX = 0.77;
    Double_t AliLogo_LowY = 0.37;
    Double_t AliLogo_Height = 0.22;
    //ALICE logo is a png file that is 821x798 pixels->should be wider than a square
    Double_t AliLogo_Width  = (821./798.) * AliLogo_Height * gPad->GetWh() / gPad->GetWw();
    
    TPad *myPadLogo = new TPad("myPadLogo", "Pad for ALICE Logo",AliLogo_LowX,AliLogo_LowY,AliLogo_LowX+AliLogo_Width,AliLogo_LowY+AliLogo_Height);
    //    myPadLogo->SetFillColor(2); // color to first figure out where is the pad then comment !
    myPadSetUp(myPadLogo,0,0,0,0);
    //myPadLogo->SetFixedAspectRatio(1);
    myPadLogo->Draw();
    myPadLogo->cd();
    TASImage *myAliceLogo = new TASImage("alice_logo_transparent.png");
    myAliceLogo->Draw();
  }
  if (rWrite == 1)  myCan->SaveAs("fig_template.eps");
  if (rWrite == 2)  myCan->SaveAs("fig_template.png");
}

void myLegendSetUp(TLegend *currentLegend=0,float currentTextSize=0.07){
  currentLegend->SetTextFont(42);
  currentLegend->SetBorderSize(0);
  currentLegend->SetFillStyle(0);
  currentLegend->SetFillColor(0);
  currentLegend->SetMargin(0.25);
  currentLegend->SetTextSize(currentTextSize);
  currentLegend->SetEntrySeparation(0.5);
  return;
}

void myPadSetUp(TPad *currentPad, float currentLeft=0.11, float currentTop=0.04, float currentRight=0.04, float currentBottom=0.15){
  currentPad->SetLeftMargin(currentLeft);
  currentPad->SetTopMargin(currentTop);
  currentPad->SetRightMargin(currentRight);
  currentPad->SetBottomMargin(currentBottom);
  return;
}

void myGraphSetUp(TGraphErrors *currentGraph=0, Float_t currentMarkerSize = 1.0,
		  int currentMarkerStyle=20, int currentMarkerColor=0,
		  int currentLineStyle=1, int currentLineColor=0){
  currentGraph->SetMarkerSize(currentMarkerSize);
  currentGraph->SetMarkerStyle(currentMarkerStyle);
  currentGraph->SetMarkerColor(currentMarkerColor);
  currentGraph->SetLineStyle(currentLineStyle);
  currentGraph->SetLineColor(currentLineColor);
  return;
}

void myOptions(Int_t lStat=0){
  // Set gStyle
  int font = 42;
  // From plain
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(10);
  gStyle->SetCanvasColor(10);
  gStyle->SetTitleFillColor(10);
  gStyle->SetTitleBorderSize(1);
  gStyle->SetStatColor(10);
  gStyle->SetStatBorderSize(1);
  gStyle->SetLegendBorderSize(1);
  //
  gStyle->SetDrawBorder(0);
  gStyle->SetTextFont(font);
  gStyle->SetStatFont(font);
  gStyle->SetStatFontSize(0.05);
  gStyle->SetStatX(0.97);
  gStyle->SetStatY(0.98);
  gStyle->SetStatH(0.03);
  gStyle->SetStatW(0.3);
  gStyle->SetTickLength(0.02,"y");
  gStyle->SetEndErrorSize(3);
  gStyle->SetLabelSize(0.05,"xyz");
  gStyle->SetLabelFont(font,"xyz"); 
  gStyle->SetLabelOffset(0.01,"xyz");
  gStyle->SetTitleFont(font,"xyz");  
  gStyle->SetTitleOffset(1.0,"xyz");  
  gStyle->SetTitleSize(0.06,"xyz");  
  gStyle->SetMarkerSize(1); 
  gStyle->SetPalette(1,0); 
  if (lStat){
    gStyle->SetOptTitle(1);
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(1111);
    }
  else {
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
  }
}
