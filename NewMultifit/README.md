New multifit
----

- small changes in code
- inflation of covariance matrix
- handling of gain ratio


Small changing in code (compare with "Standard" folder)

    simple.multifit.cc
    
    g++ -o simple.multifit.exe simple.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`

    
    ./CreateData.exe    temporal_shift      number_of_events       NSAMPLES       NFREQ     nPU    signalAmplitude    sigmaNoise     puFactor  wf_name_string    pu_shift     noise-correlation    pedestal
    cd ..
    ./CreateData.exe  -13        200    10     25     8         10        1         1         CRRC43     0    0.5        0.0
    ./CreateData.exe  -13        200    10     25    20         10        1       200         CRRC43     0    0.5        0.0
    cd -
    
    
    
    r99t ../plot/plotPulseInput.C\(\"../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_8.00_1.000_1.00_CRRC43_0.00.root\",0\)


    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_8.00_1.000_1.00_CRRC43_0.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_8.00_1.000_1.00_CRRC43_0.00.root 

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root 

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_dynamic_pedestal.root \
                               1
                               
    
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_8.00_1.000_1.00_CRRC43_0.00.root\",0\)

    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root\",0\)

    
    




                                   