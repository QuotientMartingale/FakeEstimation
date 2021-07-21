/*
This is another histogram filling macro using the dataframe.
*/

void fill_hist_df()
{
    vector<string> process = {
        "Top",
        "other_bkg",
        "Ztt",
        "signal_SM",
    };

    vector<string> regions = {
        "SR",
        "anti_tau",
        "W_lh",
        "W_lh_anti_tau",
        "qcd_lh",
        "qcd_lh_anti_tau",
        //"qcd_lh_anti_tau_truth_lep",
        //"iso_fact_lh_same_sign_anti_tau_num",
        //"iso_fact_lh_same_sign_anti_tau_den"
    };

    map<string, vector<double>> bin = {
        {"tau_0_p4", {20, 20, 220}},
        {"tau_1_p4", {20, 20, 220}},
        {"tau_1_Eta", {50, -2.5, 2.5}},
        {"dphi_mettau", {35, 0, 3.5}},
        {"ditau_dr", {25, 0, 2.5}},
        {"mmc_mlm_m", {20, 0, 200}},
        {"ditau_higgspt", {30, 90, 390}},
    };
    TLorentzVector *tau_0_p4 = new TLorentzVector();
    TLorentzVector *tau_1_p4 = new TLorentzVector();
    float dphi_mettau, ditau_dr, ditau_mmc_mlm_m;
    double tau_0_pt, tau_1_pt, ditau_higgspt, scaled_final_weight;
    vector<string> variables = {
        "tau_0_p4",
        //"tau_1_p4",
        //{"tau_1_Eta", tau_1_p4->Eta()},
        //{"dphi_mettau", dphi_mettau},
        //{"ditau_dr", ditau_dr},
        //{"ditau_mmc_mlm_m", ditau_mmc_mlm_m},
        //{"ditau_higgspt", ditau_higgspt},
    };

    TTree *tdata[regions.size()];
    TTree *tmc[regions.size()][process.size()];
    TH1D *hdata[regions.size()];
    TH1D *hmc[regions.size()];
    TH1D *hist[regions.size()][process.size()];

    for (auto &var : variables)
    {
        int bins = bin.at(var)[0];
        int xmin = bin.at(var)[1];
        int xmax = bin.at(var)[2];
        string xaxis = var;

        int m = 0; //region index
        cout << "\n";
        cout << "start filling histograms for variable " << var << endl;
        cout << "\n";
        for (auto &reg : regions)
        {
            // data 
            string data = "data_presel_mu_1p0n_" + reg + "_18";
            cout << "\n";
            cout << "----- " << reg << " regions -----" << endl;
            cout << "\n";
            cout << "start looping processes for data" << endl;
            cout << "filling data pass id in " + reg + " region..." << endl;
            TH1D *h = new TH1D(data.c_str(), "", bins, xmin, xmax);
            ROOT::RDataFrame d(data.c_str(), "../../data_Trees.root");
            d.Foreach([&h](TLorentzVector x) {h->Fill(x.Pt());},{var.c_str()});
            h->GetXaxis()->SetTitle(xaxis.c_str());
            h->GetYaxis()->SetTitle("Events / 10 GeV");
            hdata[m] = h;

            // mc
            string mc = "mc_presel_mu_1p0n_" + reg + "_18";
            hmc[m] = new TH1D(mc.c_str(), "", bins, xmin, xmax);
            hmc[m]->GetXaxis()->SetTitle(xaxis.c_str());
            hmc[m]->GetYaxis()->SetTitle("Events / 10 GeV");
            int n = 0; //process index
            int Ent = 0;
            cout << "\n";
            cout << "start looping processes for mc" << endl;
            for (auto &pro : process)
            {
                cout << "looping " + pro + "..." << endl;
            
                string hname = pro + "_presel_mu_1p0n_" + reg + "_18";
                TH1D *g = new TH1D(hname.c_str(), "", bins, xmin, xmax);
                ROOT::RDataFrame dmc(hname.c_str(), "../../mc_Trees.root");
                dmc.Foreach([&g](TLorentzVector x, double w) {g->Fill(x.Pt(), 1000*w);},{var.c_str(), "scaled_final_weight"});
                g->GetXaxis()->SetTitle(xaxis.c_str());
                g->GetYaxis()->SetTitle("Events / 10 GeV");
                hist[m][n] = g;
                hmc[m]->Add(hist[m][n]);

                n = n + 1;
            }
            cout << "\n";
            cout << reg << " filling success!" << endl;  
            cout << "total mc histogram in " << reg << " region has " << hmc[m]->GetEntries() << endl;
            cout << "The sum of each mc process in " << reg << " is " << Ent << endl;
            cout << "\n";
            m = m + 1;
        }
    }

    TFile *f = TFile::Open("../output/Histograms.root", "recreate");
    //TFile *f = TFile::Open("../output/IsoHistograms.root", "recreate");
    for (int i = 0; i < regions.size(); ++i)
    {
        hdata[i]->Write();
        hmc[i]->Write();
        for (int j = 0; j < process.size(); ++j)
        {
            hist[i][j]->Write();
            hist[i][j]->Write();
        }
    }
    f->Close();
    cout << "done!" << endl;
}
