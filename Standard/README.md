
    
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
    
