{
  
  TChain* tree = new TChain("RecoAndSim");
//   tree->Add("output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_*.00_CRRC43.root");
//   tree->Add("output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_10.000_*.00_CRRC43.root");
  tree->Add("output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_*.00_CRRC43_-1.00.root");
//   tree->Add("output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_*.00_CRRC43_1.00.root");
  
  TH2F* histo = new TH2F ("histo", "", 40, 0, 40, 200, -2, 2);
  
  tree->Draw("best_pedestal:puFactor >> histo","","goff");
  histo->GetXaxis()->SetTitle("pileup");
  histo->GetYaxis()->SetTitle("Pedestal [GeV]");
  
  histo->Draw("colz");
  
  profileX = histo->ProfileX();
  
  gPad->SetGrid();
  
  TCanvas* cc = new TCanvas("cc", "", 800, 600);
  
  histo->Draw("AXIS");
  
  profileX->SetMarkerSize(1);
  profileX->SetMarkerStyle(20);
  profileX->SetMarkerColor(kCyan);
  profileX->SetLineColor(kCyan);
  profileX->SetLineWidth(2);
  
  profileX->Draw("PL same");
  profileX->GetXaxis()->SetTitle("pileup");
  profileX->GetYaxis()->SetTitle("Pedestal [GeV]");
  
  gPad->SetGrid();
  
  
  
  
  
  
  
  TCanvas* ccEnergy = new TCanvas("ccEnergy", "Advanced", 800, 600);
  
  
  TH2F* histoEnergy = new TH2F ("histoEnergy", "", 40, 0, 40, 500, 3, 17);
  
  tree->Draw("samplesReco[4]:puFactor >> histoEnergy","","goff");
  histoEnergy->GetXaxis()->SetTitle("pileup");
  histoEnergy->GetYaxis()->SetTitle("Energy [GeV]");
  
  histoEnergy->Draw("colz");
  
  profileX_energy = histoEnergy->ProfileX();
  
  gPad->SetGrid();
  
  TCanvas* ccEnergyProfile = new TCanvas("ccEnergyProfile", "Advanced", 800, 600);
  
  histoEnergy->Draw("colz");
  
  profileX_energy->SetMarkerSize(1);
  profileX_energy->SetMarkerStyle(23);
  profileX_energy->SetMarkerColor(kRed);
  profileX_energy->SetLineColor(kRed);
  profileX_energy->SetLineWidth(2);
  
  profileX_energy->Draw("PL same");
  profileX_energy->GetXaxis()->SetTitle("pileup");
  profileX_energy->GetYaxis()->SetTitle("Energy [GeV]");
  
  
  // Fit slices projected along Y fron bins in X [0,40] with more than -1 bins in Y filled
  histoEnergy->FitSlicesY(0,0,40,-1);
  
  histoEnergy_1->SetMarkerSize(1);
  histoEnergy_1->SetMarkerStyle(32);
  histoEnergy_1->SetMarkerColor(97);
  histoEnergy_1->SetLineColor(97);
  histoEnergy_1->SetLineWidth(2);
  
  histoEnergy_2->SetMarkerSize(1);
  histoEnergy_2->SetMarkerStyle(32);
  histoEnergy_2->SetMarkerColor(97);
  histoEnergy_2->SetLineColor(97);
  histoEnergy_2->SetLineWidth(2);
  
  histoEnergy_1->Draw("PL same");
  
  
  
  gPad->SetGrid();
  
  
  



  TCanvas* ccEnergySimple = new TCanvas("ccEnergySimple", "Simple", 800, 600);
  
  
  TH2F* histoEnergySimple = new TH2F ("histoEnergySimple", "", 40, 0, 40, 500, 3, 17);
  
  //---- 200 = iMAX_pedestals/2  --> 0 shift
  
  tree->Draw("complete_samplesReco[200][4]:puFactor >> histoEnergySimple","","goff");
  histoEnergySimple->GetXaxis()->SetTitle("pileup");
  histoEnergySimple->GetYaxis()->SetTitle("Energy [GeV]");
  
  histoEnergySimple->Draw("colz");
  
  profileX_energySimple = histoEnergySimple->ProfileX();
  
  profileX_energySimple->SetMarkerSize(1);
  profileX_energySimple->SetMarkerStyle(21);
  profileX_energySimple->SetMarkerColor(kCyan+1);
  profileX_energySimple->SetLineColor(kCyan+1);
  profileX_energySimple->SetLineWidth(2);
  
  profileX_energySimple->Draw("APL same");
  
  
  
  // Fit slices projected along Y fron bins in X [0,40] with more than -1 bins in Y filled
  histoEnergySimple->FitSlicesY(0,0,40,-1);
  
  histoEnergySimple_1->SetMarkerSize(1);
  histoEnergySimple_1->SetMarkerStyle(25);
  histoEnergySimple_1->SetMarkerColor(8);
  histoEnergySimple_1->SetLineColor(8);
  histoEnergySimple_1->SetLineWidth(2);

  histoEnergySimple_2->SetMarkerSize(1);
  histoEnergySimple_2->SetMarkerStyle(25);
  histoEnergySimple_2->SetMarkerColor(8);
  histoEnergySimple_2->SetLineColor(8);
  histoEnergySimple_2->SetLineWidth(2);
  
  histoEnergySimple_1->Draw("PL same");
  
  gPad->SetGrid();


  
  TCanvas* ccEnergyProfileSimple = new TCanvas("ccEnergyProfileSimple", "Simple vs Advanced", 1200, 1200);
  ccEnergyProfileSimple->Divide(2,2);
  
  ccEnergyProfileSimple->cd(1);
  histoEnergySimple->Draw("AXIS");
  //   histoEnergySimple->GetYaxis()->SetRangeUser(9.8, 10.4);
  
  profileX_energySimple->Draw("APL same");
  
  profileX_energy->Draw("PL same");
  
  profileX_energySimple->GetXaxis()->SetTitle("pileup");
  profileX_energySimple->GetYaxis()->SetTitle("Energy [GeV]");
   
  gPad->SetGrid();
  
  
  ccEnergyProfileSimple->cd(2);
  histoEnergySimple->Draw("AXIS");
  //   histoEnergySimple->GetYaxis()->SetRangeUser(9.8, 10.4);
  
  histoEnergySimple_1->Draw("APL same");
  
  histoEnergy_1->Draw("PL same");
  
  histoEnergySimple_1->GetXaxis()->SetTitle("pileup");
  histoEnergySimple_1->GetYaxis()->SetTitle("Energy [GeV]");
  
  
  gPad->SetGrid();
  



  ccEnergyProfileSimple->cd(4);

  histoEnergySimple_2->Draw("PL");
  
  histoEnergy_2->Draw("PL same");
  
  histoEnergySimple_2->GetXaxis()->SetTitle("pileup");
  histoEnergySimple_2->GetYaxis()->SetTitle("#sigma_{Energy} [GeV]");
  
  
  gPad->SetGrid();
  
  
}




