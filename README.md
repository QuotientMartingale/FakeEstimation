Fake estimation is the most important and complicate part in Htautau CP analysis.

1. Pre-process
- check the input file on cern eos: /eos/atlas/atlascerngroupdisk/phys-higgs/HSG4/SM_Htautau_R21/V03<br>
    data: /data/hadhad,lephad,leplep<br>
    mc: /mc/hadhad,lephad,leplep/mc16a, mc16d, mc16e/nom<br>
- copy the input samples in to the input  directory. If you don't have enough space or you simply don't wanna bother you can also run filename.txt to obtain names of all files and write it into a txt file. Note that if you choose this way, the prep_rocess.py below must be run on CERN server.
- run pre_process.py , which add all root files with the same dsid into a single root file.
- run cut_data_Trees.cpp anf cut_mc_Trees.cpp. This will yield two way smaller root file storing data and mc samples corrrespondingly.

2. calculating weights
- run effective_xsec.py to calculate the effective cross sections for each dsid.
- run final_weight.cpp. This will add a new branch for each dsid tree to hold final weights.
- run fill_hist.cpp or fill_hist_df,cpp, fetching all the variables you need and filling them into histograms.

3. caculating fake factors, rQCD, and isolation factors.
- run CR_fake_factor.cpp, rQCD.cpp, isofac.cpp to obtain all three factors. Note that you need to run isofac.cpp before running rQCD.cpp.
- run fake_factors.cpp to obtain the final fake factors in SR.

4. plotting
- to check whether the data and mc after selections agree with those of BOOM's result, run processRatioPlot.C to get a comparing plot for each process and region.
- to check whether the fake factors agree with those of BOOM's, run FFRatioPlot.C.
- run FakeTemplatePlot.C to get fake templates.
- run FFPlot.cpp, rQCDPlot.cpp, IsoFacPlot.cpp to get correspoding plots.
- run data_mc_fit.cpp to get the final fit plots.   