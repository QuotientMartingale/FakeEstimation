Fake estimation is the most important and complicate part in Htautau CP analysis.

1. Pre-process
1.1 check the input file on cern eos: /eos/atlas/atlascerngroupdisk/phys-higgs/HSG4/SM_Htautau_R21/V03
    data: /data/hadhad,lephad,leplep
    mc: /mc/hadhad,lephad,leplep/mc16a, mc16d, mc16e/nom
1.2 copy the input samples in to the input  directory. If you don't have enough space or you simply don't wanna bother you can also run filename.txt to obtain names of all files and write it into a txt file. Note that if you choose this way, the prep_rocess.py below must be run on CERN server.
1.3 run pre_process.py , which add all root files with the same dsid into a single root file.
1.4 run cut_data_Trees.cpp anf cut_mc_Trees.cpp. This will yield two way smaller root file storing data and mc samples corrrespondingly.

2. calculating weights
2.1 run effective_xsec.py to calculate the effective cross sections for each dsid.
2.2 run final_weight.cpp. This will add a new branch for each dsid tree to hold final weights.
2.3 run fill_hist.cpp, fetching all the variables you need and filling them into histograms.

3. caculating fake factors, rQCD, and isolation factors.
3.1 run CR_fake_factor.cpp, rQCD.cpp, isofac.cpp to obtain all three factors.
3.2 run fake_factors.cpp to obtain the final fake factors in SR.

4. plotting
4.1 to check whether the data and mc after selections agree with those of BOOM's result, run processRatioPlot.C to get a comparing plot for each process and region.
4.2 to check whether the fake factors agree with those of BOOM's, run FFRatioPlot.C.
4.3 run FakeTemplatePlot.C to get fake templates.
4.4 run FFPlot.cpp, rQCDPlot.cpp, IsoFacPlot.cpp to get correspoding plots.
4.5 run data_mc_fit.cpp to get the final fit plots.   