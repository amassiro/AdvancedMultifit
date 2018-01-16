Multifit and noise
----

- check the effect of the noise on multifit
- from RMS noise to noise spectrum


Similar to Standard code.

Generation:

    
    CreateData.cc
    
    g++ -o CreateData.exe  CreateData.cc -std=c++11 `root-config --cflags --glibs`

    
    ./CreateData.exe    temporal_shift      number_of_events       NSAMPLES       NFREQ     nPU    signalAmplitude    sigmaNoise     puFactor  wf_name_string    pu_shift     noise-correlation    pedestal  
    
    ./CreateData.exe  -13        100    10     25     0         10        1         0         CRRC43     0    0.5        0.0      1.0
    
    ./CreateData.exe  -13        100    10     25     0          0        1         0         CRRC43     0    0.5        0.0      1.0
    ./CreateData.exe  -13        1000   10     25     0          0        1         0         CRRC43     0    0.5        0.0      1.0
    
    
    r99t ../plot/plotPulseInput.C\(\"inputExternal/mysample_100_-13.000_0.000_10_25.00_0.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00.root\",0\)
    r99t ../plot/plotPulseInput.C\(\"inputExternal/mysample_100_-13.000_0.000_10_25.00_10.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00.root\",0\)

    

Fit:

    
    
    simple.multifit.cc
    
    g++ -o simple.multifit.exe simple.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`
    
     
                               
    ./simple.multifit.exe   inputExternal/mysample_100_-13.000_0.000_10_25.00_0.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00.root  \
                            output/simple.multifit.mysample_100_-13.000_0.000_10_25.00_0.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00_fix_pedestal.root   \
                               0 \
                               0 \
                               1 \
                               0 

    ./simple.multifit.exe   inputExternal/mysample_1000_-13.000_0.000_10_25.00_0.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00.root  \
                            output/simple.multifit.mysample_1000_-13.000_0.000_10_25.00_0.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00_fix_pedestal.root   \
                               0 \
                               0 \
                               1 \
                               0 

                               
                               
    ./simple.multifit.exe   inputExternal/mysample_100_-13.000_0.000_10_25.00_10.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00.root  \
                            output/simple.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00_fix_pedestal.root   \
                               0 \
                               0 \
                               1 \
                               0 


                               
    
Plots
        
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_100_-13.000_0.000_10_25.00_0.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00_fix_pedestal.root\",0\)
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00_fix_pedestal.root\",0\)

    

    r99t plot.C\(\"output/simple.multifit.mysample_100_-13.000_0.000_10_25.00_0.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00_fix_pedestal.root\"\)
    r99t plot.C\(\"output/simple.multifit.mysample_1000_-13.000_0.000_10_25.00_0.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00_fix_pedestal.root\"\)
    
    r99t plot.C\(\"output/simple.multifit.mysample_100_-13.000_0.000_10_25.00_10.00_0.00_1.000_0.00_CRRC43_0.00_slew_1.00_fix_pedestal.root\"\)
    
    
    
    
    
    
    
    
    
    
    
                                   