//---- plot output of multifit

void plotScan (std::string nameInputFile = "output.root", int nEvent = 10){
  
  
  float pedestal = 0;
  
  Color_t* color = new Color_t [200];
  color[0] = kAzure; //kRed ;
  color[1] = kAzure + 10 ;
  color[2] = kYellow + 2 ;
  color[3] = kGreen ;
  color[4] = kGreen + 4 ;
  color[5] = kBlue ;
  color[6] = kCyan ;
  color[7] = kPink + 1 ;
  color[8] = kBlack ;
  color[9] = kYellow + 4 ;
  for (int i=0; i<30; i++) {
    color[i+10] = kBlue + i;
  }
  
  
  TFile *file = new TFile(nameInputFile.c_str());
  
  TTree* tree = (TTree*) file->Get("RecoAndSim");
  
  int    nWF;
  std::vector<double>* pulse_signal    = new std::vector<double>;
  std::vector<double>* samplesReco = new std::vector<double>;
  std::vector<double>* samples     = new std::vector<double>;
  std::vector<double>* samples_noise = new std::vector<double>;
  std::vector<int>*    activeBXs   = new std::vector<int>;
  std::vector<double>* pulseShapeTemplate     = new std::vector<double>;
  
  float NFREQ;
  
  float best_pedestal;
  float return_chi2;
  std::vector <double>* complete_chi2   = new std::vector<double>;
  std::vector <double>* complete_pedestal   = new std::vector<double>;
  std::vector < std::vector<double> >* complete_samplesReco   = new std::vector< std::vector <double> >;
  
  tree->SetBranchAddress("complete_chi2",          &complete_chi2);
  tree->SetBranchAddress("complete_pedestal",      &complete_pedestal);
  tree->SetBranchAddress("complete_samplesReco",   &complete_samplesReco);
  tree->SetBranchAddress("best_pedestal",   &best_pedestal);
  tree->SetBranchAddress("chi2",   &return_chi2);
  
  tree->SetBranchAddress("nWF",      &nWF);
  tree->SetBranchAddress("pulse_signal", &pulse_signal);
  tree->SetBranchAddress("samplesReco", &samplesReco);
  tree->SetBranchAddress("samples",   &samples);
  tree->SetBranchAddress("samples_noise",   &samples_noise);
  tree->SetBranchAddress("activeBXs", &activeBXs);
  tree->SetBranchAddress("nFreq",   &NFREQ);
  tree->SetBranchAddress("pulseShapeTemplate",   &pulseShapeTemplate);
  
  
  tree->GetEntry(nEvent);
  std::cout << " NFREQ = " << NFREQ << std::endl;
  
  TCanvas* ccpulse_signal = new TCanvas ("ccpulse_signal","",800,600);
  TGraph *gr = new TGraph();
  for(int i=0; i<nWF; i++){
    gr->SetPoint(i, i, pulse_signal->at(i));
  }
  gr->Draw("AL");
  gr->SetLineColor(kMagenta);
  gr->SetLineWidth(2);
  gr->GetXaxis()->SetTitle("time [ns]");
  
  
  
  TCanvas* ccReco = new TCanvas ("ccReco","",800,600);
  ccReco->SetRightMargin(0.3);
  TGraph *grReco = new TGraph();
  for(int i=0; i<samplesReco->size(); i++){
    std::cout << " i, activeBXs->at(i), samplesReco->at(i) = " << i << "::" << samplesReco->size() << " -> " << activeBXs->at(i) << " , " << samplesReco->at(i) << std::endl;
    grReco->SetPoint(i, activeBXs->at(i), samplesReco->at(i));
  }
  grReco->SetMarkerSize(2);
  grReco->SetMarkerStyle(22);
  grReco->SetMarkerColor(kBlue);
  grReco->Draw("ALP");
  grReco->GetXaxis()->SetTitle("BX");
  
  
  TCanvas* ccPulse = new TCanvas ("ccPulse","",800,600);
  
  TGraph *grPulse_noise = new TGraph();
  for(int i=0; i<samples->size(); i++){
    grPulse_noise->SetPoint(i, i * NFREQ , samples_noise->at(i));
  }
  grPulse_noise->SetMarkerSize(1.5);
  grPulse_noise->SetMarkerStyle(21);
  grPulse_noise->SetMarkerColor(kGray);
  grPulse_noise->SetLineColor(kGray);
  grPulse_noise->SetLineStyle(3);
  
  
  
  TGraph *grPulse = new TGraph();
  for(int i=0; i<samples->size(); i++){
    grPulse->SetPoint(i, i * NFREQ , samples->at(i));
  }
  grPulse->SetMarkerSize(2);
  grPulse->SetMarkerStyle(21);
  grPulse->SetMarkerColor(kRed);
  grPulse->Draw("ALP");
  grPulse->GetXaxis()->SetTitle("time [ns]");
  
  std::cout << " end " << std::endl;
  
  
  TCanvas* ccPulseAndReco = new TCanvas ("ccPulseAndReco","",800,600);
  TGraph *grPulseRecoAll = new TGraph();
  TGraph *grPulseReco[samplesReco->size()];
  std::cout << " samplesReco->size() = " << samplesReco->size() << std::endl;
  std::cout << " activeBXs->size() = " << activeBXs->size() << std::endl;
  std::cout << " pulseShapeTemplate->size() = " << pulseShapeTemplate->size() << std::endl;
  std::cout << " samples->size() = " << samples->size() << std::endl;
  
  TLegend* leg = new TLegend(0.91,0.10,0.99,0.90);
  
  std::vector<float> totalRecoSpectrum;
  for(int i=0; i<samples->size(); i++){
    totalRecoSpectrum.push_back(0);
  }
  
  
  //  for(int iBx=0; iBx<3; iBx++){
  for(int iBx=0; iBx<samplesReco->size(); iBx++){
    std::cout << " iBx = " << iBx << " :: " << samplesReco->size() << std::endl;
    std::cout << " Energy = " << samplesReco->at(iBx) << std::endl;
    grPulseReco[iBx] = new TGraph();
    for(int i=0; i<samples->size(); i++){
      //    std::cout << "  >> i = " << i << std::endl;
      grPulseReco[iBx]->SetPoint(i, i * NFREQ + activeBXs->at(iBx)*NFREQ + 2 * 25, pulseShapeTemplate->at(i) * samplesReco->at(iBx));
      
      int iReco = (i * NFREQ + activeBXs->at(iBx)*NFREQ + 2 * 25) / NFREQ;
      if ( iReco >= 0 && iReco <samples->size() ) {
        totalRecoSpectrum.at(iReco) += pulseShapeTemplate->at(i) * samplesReco->at(iBx);
      } 
      
    }
    grPulseReco[iBx]->SetMarkerColor(color[iBx]);
    grPulseReco[iBx]->SetLineColor(color[iBx]);
    grPulseReco[iBx]->SetMarkerSize(1);
    grPulseReco[iBx]->SetMarkerStyle(21+iBx);
    TString nameHistoTitle = Form ("BX %d", activeBXs->at(iBx));
    leg->AddEntry(grPulseReco[iBx],nameHistoTitle.Data(),"p");
  }
  
  for(int i=0; i<samples->size(); i++){
    totalRecoSpectrum.at(i) += best_pedestal;
  }
    
  grPulse->Draw("ALP");
  //  for(int iBx=0; iBx<3; iBx++){
  for(int iBx=0; iBx<samplesReco->size(); iBx++){
    grPulseReco[iBx]->Draw("PL");
  }
  
  for(int i=0; i<samples->size(); i++){
    grPulseRecoAll->SetPoint(i, i * NFREQ, totalRecoSpectrum.at(i));
  }
  
  grPulseRecoAll->SetMarkerColor(kMagenta);
  grPulseRecoAll->SetLineColor(kMagenta);
  grPulseRecoAll->SetLineStyle(1);
  grPulseRecoAll->SetMarkerSize(2);
  grPulseRecoAll->SetMarkerStyle(24);
  grPulseRecoAll->Draw("PL");
  grPulse->GetXaxis()->SetTitle("time [ns]");
  
  grPulse_noise->Draw("PL");
  
  leg->Draw();
  
  
  std::cout << " done " << std::endl;
  
  std::cout << " complete_pedestal = " << complete_pedestal->size() << std::endl;
  std::cout << " complete_chi2 = " << complete_chi2->size() << std::endl;
  
  TCanvas* ccScan = new TCanvas ("ccScan", "", 800, 600);
  
  TGraph* chi2_scan_graph =  new TGraph();
  for (int i=0; i<complete_pedestal->size(); i++) {
    chi2_scan_graph->SetPoint(i, complete_pedestal->at(i), complete_chi2->at(i));
  }
  
  TF1* fitParabola = new TF1("fitParabola", "[1] * (x-[0])*(x-[0]) + [2]", -0.5, 0.5);
  
  chi2_scan_graph->Fit("fitParabola", "R");
  
  std::cout << " best_pedestal = " << best_pedestal << std::endl;
  std::cout << " best_pedestal[fit] = " << fitParabola->GetParameter(0) << std::endl;
  
  std::cout << " return_chi2 = " << return_chi2 << std::endl;
  std::cout << " return_chi2[fit] = " << fitParabola->GetParameter(2) << std::endl;
  
  chi2_scan_graph->SetMarkerColor(kMagenta);
  chi2_scan_graph->SetLineColor(kMagenta);
  chi2_scan_graph->SetLineStyle(2);
  chi2_scan_graph->SetMarkerSize(2);
  chi2_scan_graph->SetMarkerStyle(25);
  chi2_scan_graph->Draw("APL");
  chi2_scan_graph->GetXaxis()->SetTitle("pedestal [GeV]");
  chi2_scan_graph->GetYaxis()->SetTitle("#chi^{2}");
  
  ccScan->SetGrid();
  
  
  
  
  
  TCanvas* ccPedestals = new TCanvas ("ccPedestals", "", 800, 600);
  
  TH1F* histo_pedestal = new TH1F("histo_pedestal", "fitted pedestal", 100, -2, 2);
  tree->Draw("best_pedestal >> histo_pedestal", "", "goff");
  
  histo_pedestal->SetLineColor(kBlue);
  histo_pedestal->SetFillColor(kBlue);
  histo_pedestal->SetFillStyle(3001);
  histo_pedestal->Draw();
  histo_pedestal->GetXaxis()->SetTitle("time [ns]");
  
  
  ccPedestals->SetGrid();
  
  
  
  
  
  
  
  
  TCanvas* ccSimple = new TCanvas ("ccSimple", "Simple", 800, 600);
  
  TGraph *simple_grPulseRecoAll = new TGraph();
  TGraph *simple_grPulseReco[samplesReco->size()];
 
  std::vector<float> simple_totalRecoSpectrum;
  for(int i=0; i<samples->size(); i++){
    simple_totalRecoSpectrum.push_back(0);
  }
  
  
  //  for(int iBx=0; iBx<3; iBx++){
  for(int iBx=0; iBx<samplesReco->size(); iBx++){
    std::cout << " iBx = " << iBx << " :: " << samplesReco->size() << std::endl;
    std::cout << " Energy = " << (complete_samplesReco->at( complete_pedestal->size()/2 )).at(iBx) << std::endl;
    simple_grPulseReco[iBx] = new TGraph();
    for(int i=0; i<samples->size(); i++){
      //    std::cout << "  >> i = " << i << std::endl;
      simple_grPulseReco[iBx]->SetPoint(i, i * NFREQ + activeBXs->at(iBx)*NFREQ + 2 * 25, pulseShapeTemplate->at(i) * (complete_samplesReco->at( complete_pedestal->size()/2 )).at(iBx));
      
      int iReco = (i * NFREQ + activeBXs->at(iBx)*NFREQ + 2 * 25) / NFREQ;
      if ( iReco >= 0 && iReco <samples->size() ) {
        simple_totalRecoSpectrum.at(iReco) += pulseShapeTemplate->at(i) * (complete_samplesReco->at( complete_pedestal->size()/2 )).at(iBx);
      } 
      
    }
    simple_grPulseReco[iBx]->SetMarkerColor(color[iBx]);
    simple_grPulseReco[iBx]->SetLineColor(color[iBx]);
    simple_grPulseReco[iBx]->SetMarkerSize(1);
    simple_grPulseReco[iBx]->SetMarkerStyle(21+iBx);
    TString nameHistoTitle = Form ("BX %d", activeBXs->at(iBx));
    leg->AddEntry(simple_grPulseReco[iBx],nameHistoTitle.Data(),"p");
  }
  
  for(int i=0; i<samples->size(); i++){
    simple_totalRecoSpectrum.at(i) += 0;
  }
  
  grPulse->Draw("ALP");
  //  for(int iBx=0; iBx<3; iBx++){
  for(int iBx=0; iBx<samplesReco->size(); iBx++){
    simple_grPulseReco[iBx]->Draw("PL");
  }
  
  for(int i=0; i<samples->size(); i++){
    simple_grPulseRecoAll->SetPoint(i, i * NFREQ, simple_totalRecoSpectrum.at(i));
  }
  
  simple_grPulseRecoAll->SetMarkerColor(kMagenta);
  simple_grPulseRecoAll->SetLineColor(kMagenta);
  simple_grPulseRecoAll->SetLineStyle(1);
  simple_grPulseRecoAll->SetMarkerSize(2);
  simple_grPulseRecoAll->SetMarkerStyle(24);
  simple_grPulseRecoAll->Draw("PL");
  
  grPulse->GetXaxis()->SetTitle("time [ns]");
  grPulse_noise->Draw("PL");
  
  leg->Draw();
  
  ccPedestals->SetGrid();
  
  
}






