//
// MultiFit amplitude reconstruction
// To run:
// > g++ -o Example06 Example06.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`
// > ./Example06
//

#include <iostream>
#include "PulseChiSqSNNLS.h"
#include "Pulse.h"

#include "TTree.h"
#include "TF1.h"
#include "TProfile.h"
#include "TH2.h"
#include "TFile.h"

using namespace std;

Pulse pSh;

FullSampleVector fullpulse(FullSampleVector::Zero());
FullSampleMatrix fullpulsecov(FullSampleMatrix::Zero());
SampleMatrix noisecor(SampleMatrix::Zero());
SampleMatrix noisecov(SampleMatrix::Zero());
BXVector activeBX;
SampleVector amplitudes(SampleVector::Zero());

SampleGainVector gainsPedestal;
SampleGainVector badSamples = SampleGainVector::Zero();


//---- runPedestal = 0 (fix pedestal) or 1 (dynamic pedestal)

void init(int runPedestal, float addPedestalUncertainty, float reduceNoise) {
  
  // intime sample is [2]
  double pulseShapeTemplate[NSAMPLES+2];
  for(int i=0; i<(NSAMPLES+2); i++){
    
    double x = double( IDSTART + NFREQ * (i + 3) + NFREQ - 500 / 2); //----> 500 ns is fixed!  
    
    pulseShapeTemplate[i] = pSh.fShape(x);
    std::cout << " >>  pulseShapeTemplate[" << i << "] " <<  pulseShapeTemplate[i] << " at x = " << x << std::endl;
    
  }
  //  for(int i=0; i<(NSAMPLES+2); i++) pulseShapeTemplate[i] /= pulseShapeTemplate[2];
  for (int i=0; i<(NSAMPLES+2); ++i) fullpulse(i+7) = pulseShapeTemplate[i];
  
  
  //---- reduction of the EXPECTED noise
  double pedrms = 1.0 * reduceNoise;
  
  double EBCorrNoiseMatrixG12[10] = {
    1.00000, 0.71073, 0.55721, 0.46089, 0.40449,
    0.35931, 0.33924, 0.32439, 0.31581, 0.30481 };
  
  for (int i=0; i<NSAMPLES; ++i) {
    for (int j=0; j<NSAMPLES; ++j) {
      int vidx = std::abs(j-i);
//       noisecor(i,j) = pSh.corr(vidx);
      noisecor(i,j) = EBCorrNoiseMatrixG12[vidx];
      noisecov(i,j) = noisecor(i,j) * pedrms;
    }
  }
  
  //---- sum the squared of uncertainty in all elements of the matrix: fully correlated noise!
  if (addPedestalUncertainty > 0) {    
    noisecov += (addPedestalUncertainty*addPedestalUncertainty*SampleMatrix::Ones());
  }
  
  
  
  
  for (int iSample = 0; iSample<NSAMPLES; iSample++) { 
    if (runPedestal == 1) gainsPedestal[iSample] = 0;   //---- G12
    else                  gainsPedestal[iSample] = -1;  //---- fixed pedestal
  }
  
  
  int activeBXs[] = { -5, -4, -3, -2, -1,  0,  1,  2,  3,  4 };
  activeBX.resize(10);
  for (unsigned int ibx=0; ibx<10; ++ibx) {
    activeBX.coeffRef(ibx) = activeBXs[ibx];
  } 
  //  activeBX.resize(1);
  //  activeBX.coeffRef(0) = 0;
}



void run(std::string inputFile, std::string outFile, int fixslewrate)
{
  
  TFile *file2 = new TFile(inputFile.c_str());
  
  
  std::vector<double>* samples = new std::vector<double>;
  double amplitudeTruth;
  TTree *tree = (TTree*)file2->Get("Samples");
  tree->SetBranchAddress("amplitudeTruth",      &amplitudeTruth);
  tree->SetBranchAddress("samples",             &samples);
  int nentries = tree->GetEntries();
  
  
  
  
  TFile *fout;
  
  float time_shift = 13. ; //---- default is 13
  float pedestal_shift = 0.;
  
  
  float return_chi2 = -99;
  float best_pedestal = 0;
  float best_chi2 = 0;
  
  
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

  int totalNumberOfBxActive = 10;
  
  std::vector<int> activeBXs_std;
  for (unsigned int ibx=0; ibx<totalNumberOfBxActive; ++ibx) {  
    activeBXs_std.push_back( ibx * int(25 /NFREQ) - 5 * int(25 /NFREQ) ); //----> -5 BX are active w.r.t. 0 BX
    
  }

  std::vector<double> pulseShapeTemplate;  
  for(int i=0; i<(NSAMPLES+2); i++){
//     double x = double( IDSTART + NFREQ * (i + 3) + NFREQ - 500 / 2); //----> 500 ns is fixed!  
    double x = double( IDSTART + NFREQ * (i + 3) - 500 / 2); //----> 500 ns is fixed!  
    pulseShapeTemplate.push_back( pSh.fShape(x));
  }
  
  
  newtree->Branch("activeBXs",     &activeBXs_std);
  newtree->Branch("pulseShapeTemplate",   &pulseShapeTemplate);
  
  newtree->Branch("complete_samplesReco",   &complete_samplesReco);
  newtree->Branch("complete_chi2",          &complete_chi2);
  newtree->Branch("complete_pedestal",          &complete_pedestal);
  newtree->Branch("best_pedestal",   &best_pedestal, "best_pedestal/F");
  newtree->Branch("best_chi2",   &best_chi2, "best_chi2/F");
  
  for (unsigned int ibx=0; ibx<totalNumberOfBxActive; ++ibx) {
    samplesReco.push_back(0.);
  }
  
  
  v_amplitudes_reco.clear();
  
  
  
  

  
  
  // special handling for gain switch, where sample before maximum is potentially affected by slew rate limitation
  // optionally apply a stricter criteria, assuming slew rate limit is only reached in case where maximum sample has gain switched but previous sample has not
  // option 1: use simple max-sample algorithm
  
  // ---> not implemented here
  
  // option2: A floating negative single-sample offset is added to the fit
  // such that the affected sample is treated only as a lower limit for the true amplitude
  
  int iSampleMax = 5;
  
  if (fixslewrate) {
    badSamples[iSampleMax-1] = 1;
  }
  
  
  
      
      
      
      
      
      
  
  
  
  
  for(int ievt=0; ievt<nentries; ++ievt){
    tree->GetEntry(ievt);
    for(int i=0; i<NSAMPLES; i++){
      amplitudes[i] = samples->at(i);
    }
    
    double pedval = 0.;
    PulseChiSqSNNLS pulsefunc;
    
    pulsefunc.disableErrorCalculation();
//     bool status = pulsefunc.DoFit (amplitudes,noisecor,pedrms,activeBX,fullpulse,fullpulsecov);
    bool status = pulsefunc.DoFit (amplitudes,noisecov,activeBX,fullpulse,fullpulsecov,gainsPedestal,badSamples);
    
    
    double chisq = pulsefunc.ChiSq();
    return_chi2 = chisq;
    
    unsigned int ipulseintime = 0;
    for (unsigned int ipulse=0; ipulse<pulsefunc.BXs().rows(); ++ipulse) {
      if (pulsefunc.BXs().coeff(ipulse)==0) {
        ipulseintime = ipulse;
        break;
      }
    }
    double aMax = status ? pulsefunc.X()[ipulseintime] : 0.;
    //  double aErr = status ? pulsefunc.Errors()[ipulseintime] : 0.;
   
    
    
    for (unsigned int ipulse=0; ipulse<pulsefunc.BXs().rows() ; ++ipulse) {
      if (status) { 
//         std::cout << "  (int(pulsefunc.BXs().coeff(ipulse))) = " <<  (int(pulsefunc.BXs().coeff(ipulse))) << " :: ipulse " << ipulse << " :: " << pulsefunc.BXs().rows() << " ----> " << pulsefunc.X()[ ipulse ] << std::endl;
        if ((int(pulsefunc.BXs().coeff(ipulse))) + 5 < NSAMPLES) samplesReco[ (int(pulsefunc.BXs().coeff(ipulse))) + 5] = pulsefunc.X()[ ipulse ];
        else best_pedestal = pulsefunc.X()[ ipulse ] ;
      }
      else {
        samplesReco[ipulse] = -1;
      }
    }
//     std::cout << std::endl;
    
//     std::cout << " best_pedestal = " << best_pedestal << std::endl;
    
    newtree->Fill();
        
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
  
  int runPedestal = 0;
  if (argc>=4) {
    runPedestal = atoi(argv[3]);
    std::cout << " runPedestal = " << runPedestal << std::endl;
  }
  
  float addPedestalUncertainty = 0;
  if (argc>=5) {
    addPedestalUncertainty = atof(argv[4]);
    std::cout << " addPedestalUncertainty = " << addPedestalUncertainty << std::endl;
  }
  
  float reduceNoise = 1.;
  if (argc>=6) {
    reduceNoise = atof(argv[5]);
    std::cout << " reduceNoise = " << reduceNoise << std::endl;
  }
  
  int fixslewrate = 0;
  if (argc>=7) {
    fixslewrate = atoi(argv[6]);
    std::cout << " fixslewrate = " << fixslewrate << std::endl;
  }
  
  
  init(runPedestal, addPedestalUncertainty, reduceNoise);
  run(inputFile, outFile, fixslewrate);

  
}
# endif


