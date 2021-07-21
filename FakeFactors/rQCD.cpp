void rQCD()
{
    vector<string> process = {
        "Top",
        "other_bkg",
        "Ztt",
        "signal_SM",
    };

    vector<int> colors = {
        kMagenta,
        kOrange + 1,
        kAzure + 1,
        kRed,
    };

    map<string, vector<double>> variable = {
        {"tau_0_p4.Pt", {20, 20, 220}},
        //{"tau_1_p4.Pt", {20, 20, 220}},
        //{"tau_1_p4.Eta", {50, -2.5, 2.5}},
        //{"dphi_mettau", {35, 0, 3.5}},
        //{"ditau_dr", {25, 0, 2.5}},
        //{"mmc_mlm_m", {20, 0, 200}},
        //{"ditau_higgspt", {30, 90, 390}},
    };

    vector<string> campaign = {
        //"mc16a",
        //"mc16d",
        "mc16e",
    };

    vector<string> regions = {
        "W_lh",
        "qcd_lh",
    };

    gROOT->SetStyle("ATLAS");
    gStyle->SetErrorX(0.5);
    
    TFile *fIso = TFile::Open("Isofactors.root", "read");

    TFile *f = TFile::Open("../output/RQCDHistograms.root", "recreate");

}
