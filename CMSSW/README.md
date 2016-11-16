Instructions in CMSSW
====

Where:

    /afs/cern.ch/work/a/amassiro/ECAL/LocalReco/CMSSW_8_0_20/src
    
    
Download

    cmsrel CMSSW_8_0_20
    cd CMSSW_8_0_20/src/
    cmsenv
    git cms-init
    git cms-addpkg RecoLocalCalo/EcalRecAlgos

    git checkout -b myDevelopmentGRfix
    
    git fetch --all
    git push my-cmssw remotes/official-cmssw/CMSSW_8_0_X:refs/heads/CMSSW_8_0_X    
    
    
    git commit -m "test"  RecoLocalCalo/EcalRecAlgos/src/EcalUncalibRecHitMultiFitAlgo.cc
    git push my-cmssw myDevelopmentGRfix
    
check in :

    https://github.com/amassiro/cmssw/blob/myDevelopmentGRfix/RecoLocalCalo/EcalRecAlgos/src/EcalUncalibRecHitMultiFitAlgo.cc


Modify rechit:

    git cms-addpkg DataFormats/EcalRecHit


    
Test

    cmsRun runReco.py outputFile=test.root inputFiles=/store/user/peruzzi/DoubleEG/crab_pickEvents/161114_161345/0000/pickevents_338.root
     
     