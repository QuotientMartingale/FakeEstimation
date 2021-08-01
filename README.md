Fake background, due to the complexity of the tau analysis, is one of the dominant backgrounds in the lephad final state. Therefore, fake estimation is of great importance and the most complicated part in Htautau CP analysis. This repository offers a simple workflow, independent from the BOOM and HAPPy frameworks, to understand how the calculation works and how the final fake factor is obtained, and at the same time give a bunch of plots to compare with the results of BOOM's.

### 1. Pre-processing
- check the input file on cern eos: /eos/atlas/atlascerngroupdisk/phys-higgs/HSG4/SM_Htautau_R21/V03<br>
    data: /data/hadhad,lephad,leplep<br>
    mc: /mc/hadhad,lephad,leplep/mc16a, mc16d, mc16e/nom<br>
- copy the input samples in to the input directory. If you don't have enough space or you simply don't want to bother, you can also run filename.txt to obtain names of all files and write it into a txt file. Note that if you choose this way, the prep_rocess.py below must be run on CERN server.
- run pre_process.py , which add all root files with the same dsid into a single root file.
- run cut_data_Trees.cpp anf cut_mc_Trees.cpp. This will yield two smaller root file storing data and mc samples corrrespondingly. After this step you should follow the first item of section 4 -- plotting and check if your results agree with that of BOOM's.

### 2. calculating weights
- run effective_xsec.py to calculate the effective cross sections for each dsid.
- run final_weight.cpp. This will add a new branch for each dsid tree to hold final weights.
- run fill_hist.cpp or fill_hist_df,cpp, fetching all the variables you need and filling them into histograms.

### 3. caculating fake factors, rQCD, and isolation factor.
- run CR_fake_factor.cpp, rQCD.cpp, isofac.cpp to obtain all three factors. Note that you need to run isofac.cpp before running rQCD.cpp. Finishing this you should run the corrsponding ratio plot macros and the modelling macros to check your results.
- run fake_factors.cpp to obtain the final fake factors. Again, run the corresponding plotting macros in the directory plotting to check your results.

### 4. plotting
- to check whether the data and mc after selections agree with those of BOOM's result, run processRatioPlot.C to get a comparing plot for each process and region.
- to check whether the fake factors and isolation factor agree with those of BOOM's, run RatioPlot.C.
- run FakeTemplate.C to get fake templates.
- run RatioPlot.C to get the correspoding plots for FF, rQCD, IsoFac.
- run Fake_Modeling.cpp to get the final modelling plots.   