New multifit: with Slew Rate fix
----

- slew rate fix by means of additional pulse 


Small changing in code (compare with "Standard" folder)

    simple.multifit.cc
    
    g++ -o simple.multifit.exe simple.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`

    
    ./CreateData.exe    temporal_shift      number_of_events       NSAMPLES       NFREQ     nPU    signalAmplitude    sigmaNoise     puFactor  wf_name_string    pu_shift     noise-correlation    pedestal
    cd ..
    ./CreateData.exe  -13        200    10     25     8         10        1         1         CRRC43     0    0.5        0.0
    ./CreateData.exe  -13        200    10     25    20         10        1       200         CRRC43     0    0.5        0.0
    
    ./CreateData.exe  -13        200    10     25    20         10        1       200         CRRC43     0    0.5        1.0
    ./CreateData.exe  -13        200    10     25    20         10        1         1         CRRC43     0    0.5        1.0
    
    cd -
    
    
    
    r99t ../plot/plotPulseInput.C\(\"../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_8.00_1.000_1.00_CRRC43_0.00.root\",0\)


    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_8.00_1.000_1.00_CRRC43_0.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_8.00_1.000_1.00_CRRC43_0.00.root 

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root 

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_dynamic_pedestal.root \
                               1
    
    
       runPedestal = 0  --> fixed pedestal
       runPedestal = 1  --> dynamic pedestal
    
    
    
    
    
    
    
    
    
    
    
    
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_8.00_1.000_1.00_CRRC43_0.00.root\",0\)

    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root\",0\)
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_dynamic_pedestal.root\",0\)

    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_dynamic_pedestal.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root\"\)

    r99t ../plot/plot.C\(\"../Standard/outputExternalStandard/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00.root\"\)



    
    
    ---- with a positive pedestal shift ----
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_dynamic_pedestal.root \
                               1
    
    
    
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_dynamic_pedestal.root\"\)
    r99t ../plot/plot.C\(\"../Standard/outputExternalStandard/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root\"\)

 

 
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_CorrelatedNoise_1.root  \
                               0    \
                               1

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_CorrelatedNoise_2.root   \
                               0    \
                               2
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_CorrelatedNoise_10.root   \
                               0    \
                               10
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_CorrelatedNoise_20.root   \
                               0    \
                               20
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_CorrelatedNoise_100.root   \
                               0    \
                               100
    
    
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_CorrelatedNoise_1.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_CorrelatedNoise_2.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_CorrelatedNoise_10.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_CorrelatedNoise_20.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_1.00_CRRC43_1.00_CorrelatedNoise_100.root\"\)
 
 
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_dynamic_pedestal.root \
                               1
 
 
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_1.root  \
                               0    \
                               1

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_2.root   \
                               0    \
                               2
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_10.root   \
                               0    \
                               10
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_20.root   \
                               0    \
                               20
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_100.root   \
                               0    \
                               100
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_1000.root   \
                               0    \
                               1000
    
    
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_20.NoiseReduction_0.1.root   \
                               0    \
                               20   \
                               0.1
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_20.NoiseReduction_0.01.root   \
                               0    \
                               20   \
                               0.01
    
    
    
    
 
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_dynamic_pedestal.root\"\)

    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_1.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_2.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_10.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_20.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_100.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_1000.root\"\)
    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_20.NoiseReduction_0.1.root\"\)

    
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_100.root\",0\)
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_1000.root\",0\)
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_dynamic_pedestal.root\",0\)
    r99t ../plot/plotPulse.C\(\"../Standard/outputExternalStandard/advanced.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00.root\",0\)
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_20.NoiseReduction_0.1.root\",0\)
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_1.00_CorrelatedNoise_20.NoiseReduction_0.01.root\",0\)
    
    
    
                                   