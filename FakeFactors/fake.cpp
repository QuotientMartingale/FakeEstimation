void fake()
{
    map<string, string> regions = {
        {"SR", "anti_tau"},
    };

    vector<string> variables = {
        //"tau_0_Pt",
        "tau_1_Pt",
    };
    map<string, vector<double>> bin = {
        {"tau_0_Pt", {20, 20, 220}},
        {"tau_1_Pt", {20, 20, 220}},
        {"tau_1_Eta", {50, -2.5, 2.5}},
        {"dphi_mettau", {35, 0, 3.5}},
        {"ditau_dr", {25, 0, 2.5}},
        {"mmc_mlm_m", {20, 0, 200}},
        {"ditau_higgspt", {30, 90, 390}},
    };

    TFile *f = TFile::Open("../output/CFFHistograms.root", "read");
    TH1D *hdata[regions.size()]; // data histograms  
    TH1D *hmc[regions.size()]; // mc histogrmas
    for (auto &var : variables)
    {
    int n = 0;
    for (auto &reg : regions)
    {
        string data = "data_presel_mu_1p0n_" + reg.second + "_18_" + var;
        string mc = "mc_presel_mu_1p0n_" + reg.second + "_18_" + var;
        hdata[n] = (TH1D *)f->Get(data.c_str());
        hmc[n] = (TH1D *)f->Get(mc.c_str());
        hdata[n]->Add(hmc[n], -1);
        n = n + 1;
    }

    TFile *ff = TFile::Open("../output/Combined_Fake_Factors.root", "read");
    TH1D *hF = (TH1D *)ff->Get("Combined_FF_presel_mu_1p0n_18");
    TH1D *hff = new TH1D("hff", "", 20, 20, 220);
    for (int i = 1; i < 49; ++i)
    {
        if (i == 1) hff->SetBinContent(1, 0);
        if (i == 2) hff->SetBinContent(2, hF->GetBinContent(1));
        if (i > 2) hff->SetBinContent(i, hF->GetBinContent(2));
    }

    string outFile = "../output/FakePart.root";
    TFile *f1 = TFile::Open(outFile.c_str(), "recreate");
    int m = 0;
    for (auto &reg : regions)
    {
        hdata[m]->Multiply(hff);
        string name = "Fake_presel_mu_1p0n_" + reg.first + "_18_" + var;
        hdata[m]->SetName(name.c_str());
        hdata[m]->Write();
        m = m + 1;
    }
    f1->Close();
    cout << "done!" << endl;
    }
}