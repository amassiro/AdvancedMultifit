New multifit: with Slew Rate fix
----

- slew rate fix by means of additional pulse 


Small changing in code (compare with "Standard" folder)

    simple.multifit.cc
    
    g++ -o simple.multifit.exe simple.multifit.cc PulseChiSqSNNLS.cc -std=c++11 `root-config --cflags --glibs`

    
    g++ -o CreateData.exe  CreateData.cc -std=c++11 `root-config --cflags --glibs`

    
    ./CreateData.exe    temporal_shift      number_of_events       NSAMPLES       NFREQ     nPU    signalAmplitude    sigmaNoise     puFactor  wf_name_string    pu_shift     noise-correlation    pedestal   slew-rate-distortion
    cd .. 
    ./CreateData.exe  -13        200    10     25     8         10        1         1         CRRC43     0    0.5        0.0      0.9
    ./CreateData.exe  -13        200    10     25    20         10        1       200         CRRC43     0    0.5        0.0      0.9
    
    ./CreateData.exe  -13        200    10     25    20         10        1       200         CRRC43     0    0.5        100.0      0.9
    ./CreateData.exe  -13        200    10     25    20         10        1         1         CRRC43     0    0.5        100.0      0.9

    ./CreateData.exe  -13        200    10     25     8         10        1         1         CRRC43     0    0.5        0.0      
    ./CreateData.exe  -13        200    10     25    20         10        1       200         CRRC43     0    0.5        0.0      
    
    ./CreateData.exe  -13        200    10     25    20         10        1       200         CRRC43     0    0.5        100.0    
    ./CreateData.exe  -13        200    10     25    20         10        1         1         CRRC43     0    0.5        100.0    

 
    ~~ huge pileup ~~
    
    ./CreateData.exe  -13        200    10     25     8         10        1      2000         CRRC43     0    0.5        0.0      

    cd -
    
    
    
    
    
    r99t ../plot/plotPulseInput.C\(\"../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_8.00_1.000_1.00_CRRC43_0.00.root\",0\)
    r99t ../plot/plotPulseInput.C\(\"../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_8.00_1.000_2000.00_CRRC43_0.00_slew_1.00.root\",0\)

      
       runPedestal = 0  --> fixed pedestal
       runPedestal = 1  --> dynamic pedestal
    
    
     
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_0.90.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_0.90.root_fix_pedestal_slew_rate_fix.root \
                               0 \
                               0 \
                               1 \
                               1 

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_0.90.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_0.90.root_fix_pedestal_slew_rate_NOT_fix.root \
                               0 \
                               0 \
                               1 \
                               0 
                               
    

     ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_1.00.root_fix_pedestal_slew_rate_fix.root \
                               0 \
                               0 \
                               1 \
                               1 

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_1.00.root_fix_pedestal_slew_rate_NOT_fix.root \
                               0 \
                               0 \
                               1 \
                               0 
                               
    

    
With pedestal drift
    
    
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_0.90.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_0.90.root_fix_pedestal_slew_rate_fix.root \
                               0 \
                               0 \
                               1 \
                               1 

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_0.90.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_0.90.root_fix_pedestal_slew_rate_NOT_fix.root \
                               0 \
                               0 \
                               1 \
                               0 
                               
    

     ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_1.00.root_fix_pedestal_slew_rate_fix.root \
                               0 \
                               0 \
                               1 \
                               1 

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_1.00.root_fix_pedestal_slew_rate_NOT_fix.root \
                               0 \
                               0 \
                               1 \
                               0 

                               
                               
                               
                               
                               
    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_0.90.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_0.90.root_dynamic_pedestal_slew_rate_fix.root \
                               1 \
                               0 \
                               1 \
                               1 

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_0.90.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_0.90.root_dynamic_pedestal_slew_rate_NOT_fix.root \
                               1 \
                               0 \
                               1 \
                               0 
                               
    

     ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_1.00.root_dynamic_pedestal_slew_rate_fix.root \
                               1 \
                               0 \
                               1 \
                               1 

    ./simple.multifit.exe   ../inputExternal/mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_1.00.root    \
                               output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_100.00_slew_1.00.root_dynamic_pedestal_slew_rate_NOT_fix.root \
                               1 \
                               0 \
                               1 \
                               0 
                               
    
    
    
    
    
    
    
    
    
Plots
        
    
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_0.90.root_fix_pedestal_slew_rate_fix.root\",0\)
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_0.90.root_fix_pedestal_slew_rate_NOT_fix.root\",0\)


    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_1.00.root_fix_pedestal_slew_rate_fix.root\",0\)
    r99t ../plot/plotPulse.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_1.00.root_fix_pedestal_slew_rate_NOT_fix.root\",0\)

    

    r99t ../plot/plot.C\(\"output/simple.multifit.mysample_200_-13.000_0.000_10_25.00_10.00_20.00_1.000_200.00_CRRC43_0.00_slew_1.00.root_fix_pedestal_slew_rate_NOT_fix.root\"\)
    
    
    
    
    
    
    
    
    
    
    
                                   