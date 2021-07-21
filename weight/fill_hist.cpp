/*
This macro intends to fill histograms using the trees after cutting and weighting for later convenience.
Usually for the last 2 regions we only need to check tau_1_pt, but for the first 7, we use tau_0_pt.
So please run this macro with only one variable activated per time and activate the corresponding regions.
Of course you can also make your own choice of the variables and regions. But you'd better change the output root file's name so that they don't get mixed up.
*/

void fill_hist()
{
    vector<string> process = {
        "Top",
        "other_bkg",
        "Ztt",
        "signal_SM",
    };

    vector<string> regions = {
        //"SR",
        "anti_tau",
        //"W_lh",
        //"W_lh_anti_tau",
        //"qcd_lh",
        //"qcd_lh_anti_tau",
        //"qcd_lh_anti_tau_truth_lep",
        //"iso_fact_lh_same_sign_anti_tau_num",
        //"iso_fact_lh_same_sign_anti_tau_den"
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
    TLorentzVector *tau_0_p4 = new TLorentzVector();
    TLorentzVector *tau_1_p4 = new TLorentzVector();
    float dphi_mettau, ditau_dr, ditau_mmc_mlm_m;
    double tau_0_pt, tau_1_pt, ditau_higgspt, scaled_final_weight;
    map<string, double*> variables = {
        {"tau_0_Pt", &tau_0_pt},
        //{"tau_1_Pt", &tau_1_pt},
        //{"tau_1_Eta", tau_1_p4->Eta()},
        //{"dphi_mettau", dphi_mettau},
        //{"ditau_dr", ditau_dr},
        //{"ditau_mmc_mlm_m", ditau_mmc_mlm_m},
        //{"ditau_higgspt", ditau_higgspt},
    };

    //TFile *fdata = TFile::Open("../preprocessed_samples/data_Trees.root");
    //TFile *fmc = TFile::Open("../preprocessed_samples/mc_Trees.root");
    TFile *fdata = TFile::Open("../../data_Trees.root");
    TFile *fmc = TFile::Open("../../mc_Trees.root");

    TTree *tdata[regions.size()];
    TTree *tmc[regions.size()][process.size()];
    TH1D *hdata[regions.size()];
    TH1D *hmc[regions.size()];
    TH1D *h[regions.size()][process.size()];
    //int v = 0; variable index
    for (auto &var : variables)
    {   
        int m = 0; // region index
        for (auto &reg : regions)
        {
            string data = "data_presel_mu_1p0n_" + reg + "_18";
            tdata[m] = (TTree *)fdata->Get(data.c_str());

            tdata[m]->SetBranchAddress("tau_0_p4", &tau_0_p4);
            tdata[m]->SetBranchAddress("tau_1_p4", &tau_1_p4);
            tdata[m]->SetBranchAddress("dphi_mettau", &dphi_mettau);
            tdata[m]->SetBranchAddress("ditau_dr", &ditau_dr);
            tdata[m]->SetBranchAddress("ditau_mmc_mlm_m", &ditau_mmc_mlm_m);
            tdata[m]->SetBranchAddress("ditau_higgspt", &ditau_higgspt);

            int  n = 0; //process index
            for (auto &pro : process)
            {
                string mc = pro + "_presel_mu_1p0n_" + reg + "_18";
                tmc[m][n] = (TTree *)fmc->Get(mc.c_str());

                tmc[m][n]->SetBranchAddress("tau_0_p4", &tau_0_p4);
                tmc[m][n]->SetBranchAddress("tau_1_p4", &tau_1_p4);
                tmc[m][n]->SetBranchAddress("dphi_mettau", &dphi_mettau);
                tmc[m][n]->SetBranchAddress("ditau_dr", &ditau_dr);
                tmc[m][n]->SetBranchAddress("ditau_mmc_mlm_m", &ditau_mmc_mlm_m);
                tmc[m][n]->SetBranchAddress("ditau_higgspt", &ditau_higgspt);
                tmc[m][n]->SetBranchAddress("scaled_final_weight", &scaled_final_weight);
                 n = n + 1;
            }
            m = m + 1;
        }
    }
    cout << "\n";
    cout << "branch setting done!" << endl;
    cout << "\n";

    for (auto &var : variables)
    {
        int bins = bin.at(var.first)[0];
        int xmin = bin.at(var.first)[1];
        int xmax = bin.at(var.first)[2];
        string xaxis = var.first;

        int m = 0; //region index
        cout << "\n";
        cout << "start filling histograms for variable " << var.first << endl;
        cout << "\n";
        for (auto &reg : regions)
        {
            // data 
            string data = "data_presel_mu_1p0n_" + reg + "_18";
            hdata[m] = new TH1D(data.c_str(), "", bins, xmin, xmax);
            hdata[m]->GetXaxis()->SetTitle(xaxis.c_str());
            hdata[m]->GetYaxis()->SetTitle("Events / 10 GeV");
            cout << "\n";
            cout << "----- " << reg << " regions -----" << endl;
            cout << "\n";
            cout << "start looping processes for data" << endl;
            cout << "filling data pass id in " + reg + " region..." << endl;
            for (int i = 0; i < tdata[m]->GetEntries(); ++i)
            {
                tdata[m]->GetEntry(i);
                tau_0_pt = tau_0_p4->Pt();
                tau_1_pt = tau_1_p4->Pt();
                hdata[m]->Fill(*(var.second));
                //hdata[m]->Fill(tau_1_p4->Pt());
            } 

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
                h[m][n] = new TH1D(hname.c_str(), "", bins, xmin, xmax);
                h[m][n]->GetXaxis()->SetTitle(xaxis.c_str());
                h[m][n]->GetYaxis()->SetTitle("Events / 10 GeV");
            
                int mcEnt = tmc[m][n]->GetEntries();
                Ent = Ent + mcEnt;
                cout << reg << " " << pro << " pass id has " << mcEnt << " entries" << endl;
                for (int i = 0; i < mcEnt; ++i)
                {
                    tmc[m][n]->GetEntry(i);
                    tau_0_pt = tau_0_p4->Pt();
                    tau_1_pt = tau_1_p4->Pt();
                    //h[m][n]->Fill(var.second, final_weight);
                    h[m][n]->Fill(*(var.second), scaled_final_weight*1000);// the factor 1000 comes from the miscalculation of the weights due to a unit conversion from pb to fb.
                    //h[m][n]->Fill(tau_1_p4->Pt(), scaled_final_weight*1000);
                }
                hmc[m]->Add(h[m][n]);

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
            h[i][j]->Write();
            h[i][j]->Write();
        }
    }
    f->Close();
    cout << "done!" << endl;
}
