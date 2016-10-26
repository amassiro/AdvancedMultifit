AdvancedMultifit
====

Based on https://github.com/cms-eb-upgrade/vfe-toymc


Create data
====

    g++ -o CreateData.exe  CreateData.cc -std=c++11 `root-config --cflags --glibs`

    ./CreateData.exe     
    ./CreateData.exe    temporal_shift      number_of_events       NSAMPLES       NFREQ     nPU    signalAmplitude    sigmaNoise     puFactor  wf_name_string    pu_shift     noise-correlation    pedestal

    
    
    ./CreateData.exe  -13        11    10     25     0     10    0         0      CRRC43     0    0.5       0
    
    
Fit
====

    g++ -o simple.multifit.exe simple.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`

                   input     output    NSAMPLES   NFREQ    time-shift (13 has to go for 0)      pedestal-shift
    ./simple.multifit.exe   input/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root       output/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root         10            25        13        0.0

    
    
Plot
====

    r99t  plot/plotPulseInput.C\(\"input/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root\"\)
    r99t  plot/plot.C\(\"output/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root\"\)
    r99t plot/plotPulse.C\(\"output/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root\",2\)
    r99t plot/plotPulse.C\(\"output/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root\",1\)

    

    
    
AdvancedMultifit
====


    g++ -o advanced.multifit.exe advanced.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`

    ./advanced.multifit.exe   input/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root       output/advanced.multifit.mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43.root         10            25    
    
    
Plot scan

    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_11_-13.000_0.000_10_25.00_10.00_0.00_10.000_0.00_CRRC43.root\",1\)
    
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_11_-13.000_0.000_10_25.00_10.00_0.00_10.000_0.00_CRRC43.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_0.00_18.000_0.00_CRRC43.root\",1\)

    
    
    sh doNoiseScan.sh
    
    r99t plot/plotScanVsNoise.C
    
    
    sh doPUScan.sh
    
    r99t plot/plotScanVsPU.C
    
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_19.00_CRRC43.root\",1\)
    
    