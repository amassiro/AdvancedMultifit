
    
AdvancedMultifit
====


    g++ -o advanced.multifit.exe advanced.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`
    g++ -o simple.multifit.exe simple.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`

    
    
    ./advanced.multifit.exe   ../inputExternal/mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00.root      ../outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.1.TEST.root


    ./advanced.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_320.00_CRRC43_-1.00.root   ../outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_320.00_CRRC43_-1.00_noise.1.TEST.root

    ./advanced.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_320.00_CRRC43_0.00.root   ../outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_320.00_CRRC43_0.00_noise.1.TEST.root

    ./advanced.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_320.00_CRRC43_1.00.root   ../outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_320.00_CRRC43_1.00_noise.1.TEST.root

    
    ./advanced.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_2.00_CRRC43_0.00.root   ../outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_2.00_CRRC43_0.00_noise.1.TEST.root
    
    ./advanced.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_2.00_CRRC43_-1.00.root   ../outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_2.00_CRRC43_-1.00_noise.1.TEST.root
    
    
    
    
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_2.00_CRRC43_0.00.root   
    
    
    
    r99t plot/plotScan.C\(\"../outputExternal/advanced.multifit.mysample_1_-13.000_0.000_10_25.00_5.00_1.00_1.000_1.00_CRRC43_-1.00_noise.1.TEST.root\",0\)
    r99t plot/plotScan.C\(\"../outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_320.00_CRRC43_-1.00_noise.1.TEST.root\",0\)
    r99t plot/plotScan.C\(\"../outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_320.00_CRRC43_0.00_noise.1.TEST.root\",0\)
    r99t plot/plotScan.C\(\"../outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_320.00_CRRC43_1.00_noise.1.TEST.root\",0\)
    r99t plot/plotScan.C\(\"../outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_2.00_CRRC43_0.00_noise.1.TEST.root\",0\)
    r99t plot/plotScan.C\(\"../outputExternal/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_2.00_CRRC43_-1.00_noise.1.TEST.root\",0\)
    

    
automatic

    sh doPedestalScan.sh
    
    r99t ../plot/plotScanVsPedestal.C
    
    r99t plot/plotScan.C\(\"outputExternalStandard/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_80.00_1.000_2.00_CRRC43_-1.00.root\",0\)
    r99t plot/plotScan.C\(\"outputExternalStandard/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_5.00_1.00_1.000_160.00_CRRC43_-1.00.root\",0\)
    
    

    
    
Test for comparison:

    ./advanced.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root    \
                               outputExternalStandard/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root 

    r99t ../plot/plotPulse.C\(\"outputExternalStandard/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root\",0\)
    r99t ../plot/plot.C\(\"outputExternalStandard/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root\"\)


    ./advanced.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root  \
                               outputExternalStandard/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root

    ./advanced.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root  \
                               outputExternalStandard/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root
                               

