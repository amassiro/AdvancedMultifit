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




void run(std::string inputFile, std::string outFile, int NSAMPLES, float NFREQ) {
  
  std::cout << " run ..." << std::endl;
  
//   float time_shift = 13. + 25; //---- default is 13
  float time_shift = 13. ; //---- default is 13
  float pedestal_shift = 0.;
  
  
  float return_chi2 = -99;
  float best_pedestal = 0;
  float best_chi2 = 0;
  
  //----
  float IDSTART = 6*25 + time_shift;
  
  int WFLENGTH = 500*4; //---- step 1/4 ns in waveform
  
  if (( IDSTART + NSAMPLES * NFREQ ) > 500 ) {
    WFLENGTH = (IDSTART + NSAMPLES * NFREQ)*4 + 100;
  }
  
  std::cout << " WFLENGTH = " << WFLENGTH << std::endl;
  std::cout << " NFREQ    = " << NFREQ << std::endl;
  
  
  Pulse pSh;
  pSh.SetNSAMPLES (NSAMPLES);
  pSh.SetNFREQ (NFREQ);
  pSh.SetWFLENGTH(WFLENGTH);
  pSh.SetIDSTART(IDSTART);
  
  pSh.Init();
  
  std::cout << " pSh ready " << std::endl;
  
  
  FullSampleVector fullpulse;
  FullSampleMatrix fullpulsecov;
  SampleMatrix noisecor;
  BXVector activeBX;
  SampleVector amplitudes;
  
  fullpulse.resize(2*NSAMPLES,1);   fullpulse.setZero(); // (Eigen::Matrix<double,2*NSAMPLES,1>::Zero());
  fullpulsecov.resize(2*NSAMPLES,2*NSAMPLES); fullpulsecov.setZero(); // (Eigen::Matrix<double,2*NSAMPLES,2*NSAMPLES>::Zero());
  noisecor.resize(NSAMPLES,NSAMPLES); noisecor.setZero(); // (Eigen::Matrix<double,NSAMPLES,NSAMPLES>::Zero());
  activeBX.resize(Eigen::NoChange,1);
  amplitudes.resize(NSAMPLES,1); amplitudes.setZero(); // (SampleVector::Zero());
  
  std::cout << " default ready " << std::endl;
  
  
  // intime sample is [2]
  //  double pulseShapeTemplate[NSAMPLES+2];
  std::vector<double> pulseShapeTemplate;
  
  for(int i=0; i<(NSAMPLES+7*int(25 /NFREQ)); i++) {
    
    double x;
    
    x = double( IDSTART + NFREQ * i + 3*25. - 500 / 2. );  //----> 500 ns is fixed!  
//     x = double( IDSTART + NFREQ * i + 4*25. - 500 / 2. );  //----> 500 ns is fixed!  
    
    pulseShapeTemplate.push_back( pSh.fShape(x));
    
    //   std::cout << " [" << i << "::" << (NSAMPLES+2*25 /NFREQ) << "] --> pSh.fShape(" << x << ") = " << pSh.fShape(x) << " ---> " << pSh.fShape(x) * NFREQ/25. << std::endl;
  }
  
  for (int i=1; i<(NSAMPLES + 2*int(25 /NFREQ)); i++) {
    
    fullpulse(i + 6 * int(25 /NFREQ)) = pulseShapeTemplate[i];
//     fullpulse(i + 7 * int(25 /NFREQ)) = pulseShapeTemplate[i];
  }
  
  //---- correlation
  for (int i=0; i<NSAMPLES; ++i) {
    for (int j=0; j<NSAMPLES; ++j) {
      int vidx = std::abs(j-i);
      noisecor(i,j) = pSh.corr(vidx);
    }
  }
  
  std::cout << " noise ready " << std::endl;
  
  //----  collision every 25 ns -> this is fixed number
  //----                       number of sampls * frequence in ns / 25 ns
  if ( round((NSAMPLES * NFREQ) / 25.) != (NSAMPLES * NFREQ) / 25 ) {
    std::cout << " Attention please! How do you think multifit can fit a pulse in the middle between collisions!?!?!?!?" << std::endl;
  }
  
  int totalNumberOfBxActive = int(NSAMPLES * NFREQ) / 25; 
  //  std::cout << " totalNumberOfBxActive = " << totalNumberOfBxActive << std::endl;
  
  std::vector<int> activeBXs;
  for (unsigned int ibx=0; ibx<totalNumberOfBxActive; ++ibx) {
    
//     activeBXs.push_back( ibx * int(25 /NFREQ) - 4 * int(25 /NFREQ) ); //----> -5 BX are active w.r.t. 0 BX
    activeBXs.push_back( ibx * int(25 /NFREQ) - 5 * int(25 /NFREQ) ); //----> -5 BX are active w.r.t. 0 BX
    
    //   std::cout << " activeBXs[" << ibx << "] = " << activeBXs[ibx] << std::endl;
  }
  
  activeBX.resize(totalNumberOfBxActive);
  for (unsigned int ibx=0; ibx<totalNumberOfBxActive; ++ibx) {
    activeBX.coeffRef(ibx) = activeBXs[ibx];
  } 
  
  std::cout << " end init " << std::endl;
  
  
  
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
  newtree->Branch("activeBXs",     &activeBXs);
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
  pulsefunc.setNSAMPLES(NSAMPLES);
  pulsefunc.setNFREQ(NFREQ);
  pulsefunc.Init(); //---- initialization, needed
  
  fout->cd();
  
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
    for (int iPed=0; iPed<iMAX_pedestals; iPed++) {
      //     -2, -1.99, ... 0, 0.01, ... 1.99, 2.0
      pedestal_shift = -2 + iPed*0.01;
      
      
      for(int i=0; i<NSAMPLES; i++){
        amplitudes[i] = samples->at(i) - pedestal_shift;
      }
      
      double pedval = 0.;
      double pedrms = 1.0;
      
//       if (sigmaNoise == 0) pedrms = 0.01;
//       else                 pedrms = sigmaNoise / 0.044;
        
      if (sigmaNoise == 0) pedrms = 0.00044;
      else                 pedrms = sigmaNoise;
      
      // --- why have you disabled this!?!?!??!
      //   pulsefunc.disableErrorCalculation();
      
      bool status = pulsefunc.DoFit( amplitudes, noisecor, pedrms, activeBX, fullpulse, fullpulsecov );
      double chisq = pulsefunc.ChiSq();
      return_chi2 = chisq;
      //   std::cout << " Example7 :: return_chi2 = " << return_chi2 << std::endl;
      
      ipulseintime = 0;
      for (unsigned int ipulse=0; ipulse<pulsefunc.BXs()->rows(); ++ipulse) {
        if ( ((int(pulsefunc.BXs()->coeff(ipulse))) * NFREQ/25 + 5) == 0) {
          ipulseintime = ipulse;
          break;
        }
      }
      
      double aMax = status ? (*(pulsefunc.X()))[ipulseintime] : 0.;
      
      for (unsigned int ipulse=0; ipulse<pulsefunc.BXs()->rows(); ++ipulse) {
        if (status) {
          samplesReco[ (int(pulsefunc.BXs()->coeff(ipulse))) * NFREQ/25 + 5] = (*(pulsefunc.X()))[ ipulse ];
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
      
//       map_ped_chi2 [iPed] = return_chi2; 
    }
    
    
//     TGraph chi2_scan_graph;
//     for (int i=0; i<iMAX_pedestals; i++) {
//       chi2_scan_graph.SetPoint(i, complete_pedestal.at(i), complete_chi2.at(i));
//     }
//     
//     TF1 fitParabola ("fitParabola", "[1] * (x-[0])*(x-[0]) + [2]");
//     
//     chi2_scan_graph.Fit("fitParabola");
//     best_pedestal = fitParabola.GetParameter(0);
//     return_chi2 = fitParabola.GetParameter(2);
    
    
    
    
    
    //---- refit with best pedestal
    
    pedestal_shift = best_pedestal;
    
    for(int i=0; i<NSAMPLES; i++){
      amplitudes[i] = samples->at(i) - pedestal_shift;
    }
    
    double pedval = 0.;
    double pedrms = 1.0;
    
    bool status = pulsefunc.DoFit( amplitudes, noisecor, pedrms, activeBX, fullpulse, fullpulsecov );
    double chisq = pulsefunc.ChiSq();
    return_chi2 = chisq;
    //   std::cout << " Example7 :: return_chi2 = " << return_chi2 << std::endl;
    
    ipulseintime = 0;
    for (unsigned int ipulse=0; ipulse<pulsefunc.BXs()->rows(); ++ipulse) {
      if ( ((int(pulsefunc.BXs()->coeff(ipulse))) * NFREQ/25 + 5) == 0) {
        ipulseintime = ipulse;
        break;
      }
    }
    
    double aMax = status ? (*(pulsefunc.X()))[ipulseintime] : 0.;
    
    for (unsigned int ipulse=0; ipulse<pulsefunc.BXs()->rows(); ++ipulse) {
      if (status) {
        samplesReco[ (int(pulsefunc.BXs()->coeff(ipulse))) * NFREQ/25 + 5] = (*(pulsefunc.X()))[ ipulse ];
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
  
  //---- number of samples per impulse
  int NSAMPLES = 10;
  if (argc>=4) {
    NSAMPLES = atoi(argv[3]);
  }
  std::cout << " NSAMPLES = " << NSAMPLES << std::endl;
  
  //---- number of samples per impulse
  float NFREQ = 25;
  if (argc>=5) {
    NFREQ = atof(argv[4]);
  }
  std::cout << " NFREQ = " << NFREQ << std::endl;
  
  
  //---- time shift
  //  float time_shift = 0;
  //  if (argc>=6) {
  //    time_shift = atof(argv[5]);
  //  }
  //  std::cout << " time_shift = " << time_shift << std::endl;
  // 
  //  //---- pedestal shift
  //  float pedestal_shift = 0;
  //  if (argc>=7) {
  //    pedestal_shift = atof(argv[6]);
  //  }
  //  std::cout << " pedestal_shift = " << pedestal_shift << std::endl;
  //  
  //  
  
  run(inputFile, outFile, NSAMPLES, NFREQ);
  
  std::cout << " outFile = " << outFile << std::endl;
  
  return 0;
}

# endif


