AdvancedMultifit
====

Based on https://github.com/cms-eb-upgrade/vfe-toymc


Create data
====

    g++ -o CreateData.exe  CreateData.cc -std=c++11 `root-config --cflags --glibs`

    ./CreateData.exe     
    ./CreateData.exe    temporal_shift      number_of_events       NSAMPLES       NFREQ     nPU    signalAmplitude    sigmaNoise     puFactor  wf_name_string    pu_shift     noise-correlation    pedestal

    
    
    ./CreateData.exe  -13        11    10     25     0     10    0         0      CRRC43     0    0.5       0
    ./CreateData.exe  -13        1     10     25     0     10    0         0      CRRC43     0    0.5       0
    
    
Fit
====

    g++ -o simple.multifit.exe simple.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`

                   input     output    NSAMPLES   NFREQ    time-shift (13 has to go for 0)      pedestal-shift
    ./simple.multifit.exe   input/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root       output/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root         10            25        13        0.0

    ./simple.multifit.exe   inputExternal/mysample_1_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root       output/mysample_1_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root   10            25        13        0.0

    
    
    
    
Plot
====

    r99t  plot/plotPulseInput.C\(\"input/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root\"\)
    r99t  plot/plotPulseInput.C\(\"input/mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_0.00_CRRC43_-1.00.root\"\)
    
    r99t  plot/plot.C\(\"output/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root\"\)
    r99t plot/plotPulse.C\(\"output/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root\",2\)
    r99t plot/plotPulse.C\(\"output/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root\",1\)

    

    
    
AdvancedMultifit
====


    g++ -o advanced.multifit.exe advanced.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`

    ./advanced.multifit.exe   input/mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root       output/advanced.multifit.mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43.root         10            25    
    ./advanced.multifit.exe    inputExternal/mysample_1_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root   output/mysample_1_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root         10            25    
    
    
Plot scan

    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_11_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_11_-13.000_0.000_10_25.00_10.00_0.00_10.000_0.00_CRRC43.root\",1\)
    
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_11_-13.000_0.000_10_25.00_10.00_0.00_10.000_0.00_CRRC43.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_0.00_18.000_0.00_CRRC43.root\",1\)

    
    r99t plot/plotScan.C\(\"output/mysample_1_-13.000_0.000_10_25.00_10.00_0.00_0.000_0.00_CRRC43_0.00.root\",0\)
    
    
    
    sh doNoiseScan.sh
    
    r99t plot/plotScanVsNoise.C
    
    
    sh doPUScan.sh
    
    r99t plot/plotScanVsPU.C
    
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_19.00_CRRC43.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_39.00_CRRC43.root\",1\)
    
    
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_10.000_39.00_CRRC43.root\",1\)
    
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_40.00_CRRC43_-1.00.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_0.00_CRRC43_-1.00.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_10.00_CRRC43_-1.00.root\",1\)
    
    
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_1.000_19.00_CRRC43.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_1.000_0.00_CRRC43.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_1.000_30.00_CRRC43.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_0.00_CRRC43.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_20.00_CRRC43.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_23.00_CRRC43_-1.00.root\",1\)
    r99t plot/plotScan.C\(\"output/advanced.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_80.00_0.000_3.00_CRRC43_-1.00.root\",1\)
    
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_80.00_0.000_3.00_CRRC43_-1.00.root\",1\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_0.000_3.00_CRRC43_-1.00.root\",1\)
    
    
    
    
    
    sh doPedestalScan.sh
    
    r99t plot/plotScanVsPedestal.C
    
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_0.000_20.00_CRRC43_-1.00.root\",1\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_0.000_20.00_CRRC43_-0.90.root\",1\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_0.000_20.00_CRRC43_-0.80.root\",1\)
    
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_10.00_CRRC43_-1.00.root\",1\)
    
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_2.00_CRRC43_1.00.root\",1\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_2.00_CRRC43_-1.00.root\",1\)
    
    
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_0.000_1.00_CRRC43_-1.00.root\",1\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_0.000_30.00_CRRC43_-1.00.root\",1\)
    
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_0.000_20.00_CRRC43_-1.00.root\",1\)
    
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_0.000_20.00_CRRC43_-1.00.root\",23\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_0.000_10.00_CRRC43_-1.00.root\",23\)

    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_160.00_CRRC43_-1.00.root\",23\)

    
    
    //---- test noise parameter
    
    ./CreateData.exe  -13        1    10     25     1         5        1         1         CRRC43     0    0.5       -1.0
    ./advanced.multifit.exe   inputExternal/mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00.root      outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.0.001.root          10            25         0.001
    ./advanced.multifit.exe   inputExternal/mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00.root      outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.0.1.root          10            25         0.1
    ./advanced.multifit.exe   inputExternal/mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00.root      outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.1.root          10            25         1
    ./advanced.multifit.exe   inputExternal/mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00.root      outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.2.root          10            25         2
    ./advanced.multifit.exe   inputExternal/mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00.root      outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.5.root          10            25         5
    ./advanced.multifit.exe   inputExternal/mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00.root      outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.10.root         10            25         10
    ./advanced.multifit.exe   inputExternal/mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00.root      outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.100.root        10            25         100
    ./advanced.multifit.exe   inputExternal/mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00.root      outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.1000.root       10            25         1000

    
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.0.001.root\",0\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.0.1.root\",0\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.1.root\",0\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.2.root\",0\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.5.root\",0\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.10.root\",0\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.100.root\",0\)
    r99t plot/plotScan.C\(\"outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.1000.root\",0\)
    
    

    
    