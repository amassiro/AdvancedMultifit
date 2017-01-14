//
// MultiFit amplitude reconstruction
// To run:
//     g++ -o advanced.multifit.exe advanced.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`
//

#include <iostream>
#include "PulseChiSqSNNLS.h"
#include "Pulse.h"

#include "TTree.h"
#include "TF1.h"
#include "TProfile.h"
#include "TH2.h"
#include "TFile.h"




Pulse pSh;

FullSampleVector fullpulse(FullSampleVector::Zero());
FullSampleMatrix fullpulsecov(FullSampleMatrix::Zero());
SampleMatrix noisecor(SampleMatrix::Zero());
BXVector activeBX;
SampleVector amplitudes(SampleVector::Zero());



void init() {
  
    
  // intime sample is [2]
  double pulseShapeTemplate[NSAMPLES+2];
  for(int i=0; i<(NSAMPLES+2); i++){
//     double x = double( IDSTART + NFREQ * (i + 3) - WFLENGTH / 2);
//     double x = double( IDSTART + NFREQ * (i + 3) - 500 / 2); //----> 500 ns is fixed!  
    double x = double( IDSTART + NFREQ * (i + 3) + NFREQ - 500 / 2); //----> 500 ns is fixed!  
    pulseShapeTemplate[i] = pSh.fShape(x);
    std::cout << " >>  pulseShapeTemplate[" << i << "] " <<  pulseShapeTemplate[i] << " at x = " << x << std::endl;
  }
  //  for(int i=0; i<(NSAMPLES+2); i++) pulseShapeTemplate[i] /= pulseShapeTemplate[2];
  for (int i=0; i<(NSAMPLES+2); ++i) fullpulse(i+7) = pulseShapeTemplate[i];
  
  
  double EBCorrNoiseMatrixG12[10] = {
    1.00000, 0.71073, 0.55721, 0.46089, 0.40449,
    0.35931, 0.33924, 0.32439, 0.31581, 0.30481 };
    
  for (int i=0; i<NSAMPLES; ++i) {
    for (int j=0; j<NSAMPLES; ++j) {
      int vidx = std::abs(j-i);
//       noisecor(i,j) = pSh.corr(vidx);
      noisecor(i,j) = EBCorrNoiseMatrixG12[vidx];
    
    }
  }
  
  int activeBXs[] = { -5, -4, -3, -2, -1,  0,  1,  2,  3,  4 };
  activeBX.resize(10);
  for (unsigned int ibx=0; ibx<10; ++ibx) {
    activeBX.coeffRef(ibx) = activeBXs[ibx];
  } 
  //  activeBX.resize(1);
  //  activeBX.coeffRef(0) = 0;
  
  
  
  //   http://cmslxr.fnal.gov/source/RecoLocalCalo/EcalRecProducers/plugins/EcalUncalibRecHitWorkerMultiFit.cc
  for (int i=0; i<(NSAMPLES+2); i++) {
    for (int j=0; j<(NSAMPLES+2); j++) {
      fullpulsecov(i+7, j+7) = pSh.cholesky(i,j);
    }
  }
  
//   for(int i=0; i<EcalPulseShape::TEMPLATESAMPLES;i++)
//     0289         for(int j=0; j<EcalPulseShape::TEMPLATESAMPLES;j++)
//     0290           fullpulsecov(i+7,j+7) = aPulseCov->covval[i][j];
//   0291      
//   
//   
//   
  
  
  
}






//---- transform the pulse into an histogram              - type is "reco = 1" or "sim = 0"
TH1F* CreateHistoShape( SampleVector& sam, int itime, int type) {
  TString name = Form ("h_%d_%d",type, itime);
  TH1F* temphist = new TH1F(name.Data(),"",sam.rows(),0,sam.rows());
  
  for (int i=0; i<sam.rows(); i++) {
    temphist->SetBinContent(i+1, sam[i]);
  }
  
  return temphist;
}


//---- transform the pulse into an histogram              - type is "reco = 1" or "sim = 0"
TH1F* CreateHistoAmplitudes( const PulseVector& sam, int itime, int type) {
  TString name = Form ("hAmpl_%d_%d",type, itime);
  TH1F* temphist = new TH1F(name.Data(),"",sam.rows(),0,sam.rows());
  
  for (int i=0; i<sam.rows(); i++) {
    temphist->SetBinContent(i+1, sam[i]);
  }
  
  return temphist;
}




void run(std::string inputFile, std::string outFile, float NOISESCALE) {
  
  
  init();
  
  std::cout << " run ..." << std::endl;
  
  float pedestal_shift = 0.;
  
  
  float return_chi2 = -99;
  float best_pedestal = 0;
  float best_chi2 = 0;
  
  
  std::cout << " WFLENGTH = " << WFLENGTH << std::endl;
  std::cout << " NFREQ    = " << NFREQ << std::endl;
  
  
    
  // intime sample is [2]
  //  double pulseShapeTemplate[NSAMPLES+2];
  std::vector<double> pulseShapeTemplate;
  
  for(int i=0; i<(NSAMPLES+2); i++){
//     double x = double( IDSTART + NFREQ * (i + 3) - WFLENGTH / 2);
//     double x = double( IDSTART + NFREQ * (i + 3) - 500 / 2); //----> 500 ns is fixed!  
//     double x = double( IDSTART + NFREQ * (i + 3) + NFREQ - 500 / 2); //----> 500 ns is fixed!  
    double x = double( IDSTART + NFREQ * (i + 3) - 500 / 2); //----> 500 ns is fixed!  
    pulseShapeTemplate.push_back( pSh.fShape(x));
  }
     
  int totalNumberOfBxActive = int(NSAMPLES * NFREQ) / 25; 
  
  std::vector<int> activeBXs_std;
  for (unsigned int ibx=0; ibx<totalNumberOfBxActive; ++ibx) {
    
    activeBXs_std.push_back( ibx * int(25 /NFREQ) - 5 * int(25 /NFREQ) ); //----> -5 BX are active w.r.t. 0 BX
    
  }
  
  
  std::cout << " inputFile = " << inputFile << std::endl;
  TFile *file2 = new TFile(inputFile.c_str());
  
  std::vector<double>* samples = new std::vector<double>;
  double amplitudeTruth;
  TTree *tree = (TTree*) file2->Get("Samples");
  tree->SetBranchAddress("amplitudeTruth",      &amplitudeTruth);
  tree->SetBranchAddress("samples",             &samples);
  
  float sigmaNoise; // = 0.044;
  tree->SetBranchAddress("sigmaNoise",             &sigmaNoise);
  
  int nentries = tree->GetEntries();
  
  std::cout << " nentries = " << nentries << std::endl;
  std::cout << " NSAMPLES = " << NSAMPLES << std::endl;
  
  TFile *fout;
  
  std::vector<TH1F*> v_pulses;
  std::vector<TH1F*> v_amplitudes_reco;
  
  std::cout << " outFile = " << outFile << std::endl;
  fout = new TFile(outFile.c_str(),"recreate");
  
  fout->cd();
  TTree* newtree = (TTree*) tree->CloneTree(0); //("RecoAndSim");
  newtree->SetName("RecoAndSim");
  
  std::vector <double> samplesReco;
  std::vector < std::vector<double> > complete_samplesReco;
  std::vector <double> complete_chi2;
  std::vector <double> complete_pedestal;
  
  int ipulseintime = 0;
  newtree->Branch("chi2",   &return_chi2, "chi2/F");
  newtree->Branch("samplesReco",   &samplesReco);
  newtree->Branch("ipulseintime",  ipulseintime,  "ipulseintime/I");
  newtree->Branch("activeBXs",     &activeBXs_std);
  newtree->Branch("pulseShapeTemplate",   &pulseShapeTemplate);
  
  newtree->Branch("complete_samplesReco",   &complete_samplesReco);
  newtree->Branch("complete_chi2",          &complete_chi2);
  newtree->Branch("complete_pedestal",          &complete_pedestal);
  newtree->Branch("best_pedestal",   &best_pedestal, "best_pedestal/F");
  newtree->Branch("best_chi2",   &best_chi2, "best_chi2/F");
  
  std::cout << " pulseShapeTemplate.size () = " << pulseShapeTemplate.size() << std::endl;
  
  
  for (unsigned int ibx=0; ibx<totalNumberOfBxActive; ++ibx) {
    samplesReco.push_back(0.);
  }
  
  
  v_amplitudes_reco.clear();
  
  //---- create the multifit
  PulseChiSqSNNLS pulsefunc;
  
  
  fout->cd();
  
  double pedval = 0.;
  double pedrms = 1.0;
  
  if (sigmaNoise == 0) pedrms = 0.00044*NOISESCALE;
  else                 pedrms = sigmaNoise*NOISESCALE;
  
  
  
  for(int ievt=0; ievt<nentries; ++ievt){
    
    if (!(ievt%10)) {
      std::cout << " ievt = " << ievt << " :: " << nentries << std::endl;
    }
    
    tree->GetEntry(ievt);
    
    complete_chi2.clear();
    complete_pedestal.clear();
    complete_samplesReco.clear();
    
    best_pedestal = 0.;
    return_chi2 = -99.;
    best_chi2 = -99.;
    
    
    //---- find best pedestal value
    //     std::map<int, float> map_ped_chi2;
    
    //---- loop over pedestal shift
    int iMAX_pedestals = 400;
//     int iMAX_pedestals = 1;
    for (int iPed=0; iPed<iMAX_pedestals; iPed++) {
      //     -2, -1.99, ... 0, 0.01, ... 1.99, 2.0
      pedestal_shift = -2 + iPed*0.01;
//       pedestal_shift = 0 + iPed*0.01;
      
      
      for(int i=0; i<NSAMPLES; i++){
        amplitudes[i] = samples->at(i) - pedestal_shift;
      }
      
//       std::cout << " amplitudes = " << amplitudes << std::endl;
      
      
      // --- why have you disabled this!?!?!??!
      // because otherwise it crashes!
      pulsefunc.disableErrorCalculation();
      
      bool status = pulsefunc.DoFit( amplitudes, noisecor, pedrms, activeBX, fullpulse, fullpulsecov );
      double chisq = pulsefunc.ChiSq();
      return_chi2 = chisq;
      
      ipulseintime = 0;
      for (unsigned int ipulse=0; ipulse<pulsefunc.BXs().rows(); ++ipulse) {
        if (pulsefunc.BXs().coeff(ipulse) == 0) {
          ipulseintime = ipulse;
          break;
        }
      }
      
//       std::cout << " ipulseintime = " << ipulseintime << std::endl;
//       std::cout << " pulsefunc.X() = " << (pulsefunc.X()) << std::endl;
      
//       std::cout << " status = " << status << std::endl;
      
      double aMax = status ? pulsefunc.X()[ipulseintime] : 0.;
      
//       std::cout << " aMax = " << aMax << " return_chi2 = " << return_chi2 << std::endl;
      
      for (unsigned int ipulse=0; ipulse<pulsefunc.BXs().rows(); ++ipulse) {
        if (status) {
//           std::cout << "   [iPed] = " << iPed <<  "   >> (int(pulsefunc.BXs().coeff(ipulse))) * NFREQ/25 + 5 = " << (int(pulsefunc.BXs().coeff(ipulse))) * NFREQ/25 + 5 << " ---> " <<   pulsefunc.X()[ ipulse ]  << std::endl;
          samplesReco[ (int(pulsefunc.BXs().coeff(ipulse))) * NFREQ/25 + 5] = pulsefunc.X()[ ipulse ];
        }
        else {
          samplesReco[ipulse] = -1;
        }
      }
      
      complete_samplesReco.push_back (samplesReco);
      complete_chi2.push_back(return_chi2);
      complete_pedestal.push_back(pedestal_shift);
      
      if (best_chi2 != -99) {
        if (best_chi2 > return_chi2) {
          best_chi2 = return_chi2;
          best_pedestal = pedestal_shift;          
        }
      }
      else {
        best_chi2 = return_chi2;
        best_pedestal = pedestal_shift;
      }
      
    }
    
  
    
    
    
    
    //---- refit with best pedestal
    
    pedestal_shift = best_pedestal;
    
    for(int i=0; i<NSAMPLES; i++){
      amplitudes[i] = samples->at(i) - pedestal_shift;
    }
    
//     double pedval = 0.;
//     double pedrms = 1.0;
    
    bool status = pulsefunc.DoFit( amplitudes, noisecor, pedrms, activeBX, fullpulse, fullpulsecov );
    double chisq = pulsefunc.ChiSq();
    return_chi2 = chisq;
    //   std::cout << " Example7 :: return_chi2 = " << return_chi2 << std::endl;
    
    ipulseintime = 0;
    for (unsigned int ipulse=0; ipulse<pulsefunc.BXs().rows(); ++ipulse) {
      if (pulsefunc.BXs().coeff(ipulse)==0) {
        ipulseintime = ipulse;
        break;
      }
    }
    
    double aMax = status ? pulsefunc.X()[ipulseintime] : 0.;
    
    for (unsigned int ipulse=0; ipulse<pulsefunc.BXs().rows(); ++ipulse) {
      if (status) {        
        samplesReco[ (int(pulsefunc.BXs().coeff(ipulse))) * NFREQ/25 + 5] = pulsefunc.X()[ ipulse ];
      }
      else {
        samplesReco[ipulse] = -1;
      }
    }
    
    newtree->Fill();
    
    //     chi2_scan_graph.Write();
    
  }
  
  fout->cd();
  newtree->Write();
  fout->Close();
  
}






# ifndef __CINT__

int main(int argc, char** argv) {
  
  std::string inputFile = "data/samples_signal_10GeV_pu_0.root";
  if (argc>=2) {
    inputFile = argv[1];
  }
  
  std::string outFile = "output.root";
  if (argc>=3) {
    outFile = argv[2];
  }
  std::cout << " outFile = " << outFile << std::endl;
  
  
  
  float NOISESCALE = 1;
  if (argc>=4) {
    NOISESCALE = atof(argv[3]);
  }
  std::cout << " NOISESCALE = " << NOISESCALE << std::endl;
    
  run(inputFile, outFile, NOISESCALE);
  
  std::cout << " outFile = " << outFile << std::endl;
  
  return 0;
}

# endif


