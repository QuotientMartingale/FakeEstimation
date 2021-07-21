void final_weight()
{    
    // Declaration of leaf types of data
    TLorentzVector *dijet_p4 = new TLorentzVector();
    TLorentzVector *jet_0_p4 = new TLorentzVector();
    TLorentzVector *jet_1_p4 = new TLorentzVector();
    Int_t ditau_coll_approx;
    Float_t ditau_coll_approx_m;
    Float_t ditau_coll_approx_x0;
    Float_t ditau_coll_approx_x1;
    Float_t ditau_cosalpha;
    Float_t ditau_deta;
    Float_t ditau_dphi;
    Float_t ditau_dr;
    Double_t ditau_higgspt;
    Int_t ditau_mmc_mlm_fit_status;
    Float_t ditau_mmc_mlm_m;
    Float_t ditau_mt_lep0_met;
    Float_t ditau_mt_lep1_met;
    TLorentzVector *ditau_p4 = new TLorentzVector();
    Float_t ditau_qxq;
    UInt_t is_dijet_centrality;
    TLorentzVector *tau_0_p4 = new TLorentzVector();
    TLorentzVector *tau_1_p4 = new TLorentzVector();
    UInt_t tau_0;
    Float_t tau_0_q;
    Float_t tau_1_q;
    UInt_t tau_0_decay_mode;
    TLorentzVector *tau_0_decay_neutral_p4;
    int tau_0_matched_pdgId;
    int tau_1_matched_pdgId;
    Float_t tau_0_ele_bdt_eff_sf;
    Float_t tau_0_ele_bdt_score;
    Float_t tau_0_ele_bdt_score_retuned;
    Float_t tau_0_ele_bdt_score_trans;
    Float_t tau_0_ele_bdt_score_trans_retuned;
    Int_t tau_0_ele_bdt_tight_retuned;
    UInt_t tau_0_jet_rnn_loose;
    UInt_t tau_0_jet_rnn_medium;
    Float_t tau_0_jet_rnn_score;
    Float_t tau_0_jet_rnn_score_trans;
    UInt_t tau_0_jet_rnn_tight;
    UInt_t tau_0_jet_rnn_veryloose;
    UInt_t tau_0_trig_HLT_tau25_medium1_tracktwo;
    UInt_t tau_0_trig_HLT_tau25_medium1_tracktwoEF;
    UInt_t tau_0_trig_HLT_tau35_medium1_tracktwo;
    UInt_t tau_0_trig_HLT_tau35_medium1_tracktwoEF;
    UInt_t tau_0_trig_trigger_matched;
    UInt_t tau_1_electron_trig_HLT_e120_lhloose;
    UInt_t tau_1_electron_trig_HLT_e140_lhloose_nod0;
    UInt_t tau_1_electron_trig_HLT_e24_lhmedium_L1EM20VH;
    UInt_t tau_1_electron_trig_HLT_e26_lhtight_nod0_ivarloose;
    UInt_t tau_1_electron_trig_HLT_e60_lhmedium;
    UInt_t tau_1_electron_trig_HLT_e60_lhmedium_nod0;
    UInt_t tau_1_electron_trig_trigger_matched;
    UInt_t tau_1_emu_trig_trigger_matched;
    Int_t tau_1_id_bad;
    Int_t tau_1_id_charge;
    Int_t tau_1_id_loose;
    Int_t tau_1_id_medium;
    Int_t tau_1_id_tight;
    Int_t tau_1_id_veryloose;
    UInt_t tau_1_iso_FCLoose;
    UInt_t tau_1_iso_FCTight;
    UInt_t tau_1_iso_FCTightTrackOnly;
    UInt_t tau_1_iso_FixedCutHighPtTrackOnly;
    UInt_t tau_1_muon_trig_HLT_mu20_iloose_L1MU15;
    UInt_t tau_1_muon_trig_HLT_mu26_ivarmedium;
    UInt_t tau_1_muon_trig_HLT_mu50;
    UInt_t tau_1_muon_trig_trigger_matched;
    Int_t event_is_bad_batman;
    TLorentzVector *met_p4 = new TLorentzVector();
    Int_t n_electrons;
    Int_t n_jets;
    Int_t n_muons;
    Int_t n_photons;
    Int_t n_pvx;
    Int_t n_taus;
    Int_t n_taus_rnn_loose;
    Int_t n_taus_rnn_medium;
    Int_t n_taus_rnn_tight;
    Int_t n_taus_rnn_veryloose;
    UInt_t NOMINAL_pileup_random_run_number;
    UInt_t truth_passedVBFFilter;
    int n_bjets_DL1r_FixedCutBEff_85;
    int NOMINAL_pileup_combined_weight;
    Float_t tau_1_NOMINAL_MuEffSF_Reco_QualMedium;
    Float_t tau_1_NOMINAL_MuEffSF_IsoFCTightTrackOnly;
    Float_t tau_1_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium;
    Float_t jet_NOMINAL_global_effSF_DL1r_FixedCutBEff_85;
    Float_t jet_NOMINAL_global_ineffSF_DL1r_FixedCutBEff_85;
    Float_t jet_NOMINAL_central_jets_global_effSF_JVT;
    Float_t jet_NOMINAL_central_jets_global_ineffSF_JVT;
    Float_t jet_NOMINAL_forward_jets_global_effSF_JVT;
    double cross_section;
    double weight_mc;
    double final_weight;
    float theory_weights_nominal;
    int dsid;

    // Arrays of DSIDs
    // Ztautau
    vector<int> ZttQCD = {344772, 344774, 344775, 344776, 344778, 344779, 344780, 344781, 344782, 364137, 364138, 364139, 364140, 364141, 364210, 364211, 364212, 364213, 364214, 364215};
    vector<int> ZttEWK = {308094};
    // Ztt = ZttQCD + ZttEWK
    vector<int> Ztt = {344772, 344774, 344775, 344776, 344778, 344779, 344780, 344781, 344782, 364137, 364138, 364139, 364140, 364141, 364210, 364211, 364212, 364213, 364214, 364215, 308094};
    // Single-Top and ttbar
    vector<int> Top = {410470, 410471, 410644, 410645, 410646, 410647, 410658, 410659, 410155, 410218, 410219, 410220, 412043, 304014};
    // Diboson
    vector<int> VV = {363355, 363356, 363357, 363358, 363359, 363489, 363494, 364250, 364253, 364254, 364255, 364288, 364289, 364290};
    // W(tau/mu/e + nu) + jets
    vector<int> W = {364156, 364157, 364158, 364159, 364160, 364161, 364162, 364163, 364164, 364165, 364166, 364167, 364168, 364169, 364170, 364171, 364172, 364173, 364174, 364175, 364176, 364177, 364178, 364179, 364180, 364181, 364182, 364183, 364184, 364185, 364186, 364187, 364188, 364189, 364190, 364191, 364192, 364193, 364194, 364195, 364196, 364197, 308096, 308097, 308098};
    // Zll + jets
    vector<int> ZllQCD = {345099, 345100, 345101, 345102, 364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113, 364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 364198, 364199, 364200, 364201, 364202, 364203, 364204, 364205, 364206, 364207, 364208, 364209};
    vector<int> ZllEWK = {308092, 308093};
    //Zll = ZllQCD + ZllEWK
    vector<int> Zll = {345099, 345100, 345101, 345102, 364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113, 364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 364198, 364199, 364200, 364201, 364202, 364203, 364204, 364205, 364206, 364207, 364208, 364209, 308092, 308093};
    vector<int> ggHWW = {345324};
    vector<int> VBFHWW = {345948};
    // other_bkg = VV + W + Zll + ggHWW + VBFHWW
    vector<int> other_bkg = {363355, 363356, 363357, 363358, 363359, 363489, 363494, 364250, 364253, 364254, 364255, 364288, 364289, 364290, 364156, 364157, 364158, 364159, 364160, 364161, 364162, 364163, 364164, 364165, 364166, 364167, 364168, 364169, 364170, 364171, 364172, 364173, 364174, 364175, 364176, 364177, 364178, 364179, 364180, 364181, 364182, 364183, 364184, 364185, 364186, 364187, 364188, 364189, 364190, 364191, 364192, 364193, 364194, 364195, 364196, 364197, 308096, 308097, 308098, 345099, 345100, 345101, 345102, 364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113, 364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 364198, 364199, 364200, 364201, 364202, 364203, 364204, 364205, 364206, 364207, 364208, 364209, 308092, 308093, 345324, 345948};
    // Signal samples
    vector<int> ggH = {345121, 345122, 345123};
    vector<int> VBFH = {346191, 346192, 346193};
    vector<int> WH = {345211, 345212};
    vector<int> ZH = {345217};
    vector<int> ttH = {346343, 346344, 346345};
    // signal_SM = ggH + VBFH + WH + ZH + ttH
    vector<int> signal_SM = {345121, 345122, 345123, 346191, 346192, 346193, 345211, 345212, 345217, 346343, 346344, 346345};

    vector<int> ggH_CPodd = {346527, 346528, 346562};
    vector<int> VBFH_CPodd = {346565, 346566, 346571};
    // signal_CPodd = ggH_CPodd + VBFH_CPodd
    vector<int> signal_CPodd = {346527, 346528, 346562, 346565, 346566, 346571};

    vector<int> ggH_unpol = {346531, 346532, 346564};
    vector<int> VBFH_unpol = {346569, 346570, 346573};
    vector<int> WH_unpol = {346909, 346912};
    vector<int> ZH_unpol = {346915};
    vector<int> ttH_unpol = {346919, 346923, 346927};
    // Signal_unpol = ggH_unpol + VBFH_unpol + WH_unpol + ZH_unpol + ttH_unpol
    vector<int> signal_unpol = {346531, 346532, 346564, 346569, 346570, 346573,
                                346909, 346912, 346915, 346919, 346923, 346927};
    vector<int> signal = {345121, 345122, 345123, 346191, 346192, 346193, 345211, 345212, 345217, 346343, 346344, 346345, 346527, 346528, 346562, 346565, 346566, 346571, 346531, 346532, 346564, 346569, 346570, 346573, 346909, 346912, 346915, 346919, 346923, 346927};

    vector<int> ggH_He7 = {600565, 600566, 600567, 600568};
    vector<int> VBFH_He7 = {600569, 600570, 600571, 600572};
    vector<int> WH_He7 = {600573, 600574};
    vector<int> ZH_He7 = {600575};

    vector<int> ttH_afii = {346343, 346344, 346345}; // NOTE this is the same with the ttH
    vector<int> ttH_afii_ME = {346443, 346444, 346445};
    vector<int> ttH_afii_PS = {346346, 346347, 346348};

    vector<int> all = {
        344772, 344774, 344775, 344776, 344778, 344779, 344780, 344781, 344782, 364137, 364138, 364139, 364140, 364141, 364210, 364211, 364212, 364213, 364214, 364215, 308094,
        410470, 410471, 410644, 410645, 410646, 410647, 410658, 410659, 410155, 410218, 410219, 410220, 412043, 304014,
        363355, 363356, 363357, 363358, 363359, 363489, 363494, 364250, 364253, 364254, 364255, 364288, 364289, 364290, 364156, 364157, 364158, 364159, 364160, 364161, 364162, 364163, 364164, 364165, 364166, 364167, 364168, 364169, 364170, 364171, 364172, 364173, 364174, 364175, 364176, 364177, 364178, 364179, 364180, 364181, 364182, 364183, 364184, 364185, 364186, 364187, 364188, 364189, 364190, 364191, 364192, 364193, 364194, 364195, 364196, 364197, 308096, 308097, 308098, 345099, 345100, 345101, 345102, 364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113, 364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 364198, 364199, 364200, 364201, 364202, 364203, 364204, 364205, 364206, 364207, 364208, 364209, 308092, 308093, 345324, 345948,
        345121, 345122, 345123, 346191, 346192, 346193, 345211, 345212, 345217, 346343, 346344, 346345,
        346527, 346528, 346562, 346565, 346566, 346571,
        346531, 346532, 346564, 346569, 346570, 346573, 346909, 346912, 346915, 346919, 346923, 346927,
        600565, 600566, 600567, 600568, 600569, 600570, 600571, 600572, 600573, 600574, 600575,
        //346443, 346444, 346445, 346346, 346347, 346348
    };

    map<string, vector<int>> process = {
        {"Top", Top},
        {"other_bkg", other_bkg},
        {"Ztt", Ztt},
        {"signal_SM", signal_SM},
        {"signal_CPodd", signal_CPodd},
        {"signal_unpol", signal_unpol},
    };

    map<string, int> year = {
        {"15", 3.22},
        {"16", 32.99},
        {"17", 44.31},
        {"18", 58.45},
    };

    vector<string> campaign = {
        //"mc16a",
        //"mc16d",
        "mc16e"};

    // note we actually add a branch to all mc files before cutting.
    string path = "../preprocessed_samples/combined_mc_samples";
    string prefix = "group.phys-higgs.Htt_lh_V03.mc16_13TeV.";

    // reading xsec data from file
    ifstream file;
    file.open("../dataset/eff_xsec.txt");
    assert(file.is_open());
    double xsec[183][2];
    for (int i = 0; i < 183; ++i)
    {
        file >> xsec[i][0] >> xsec[i][1];
    }
    file.close();
    
    double uc = 1000.0; // unit conversion factor from pb to fb. This is due to eff_xsec is in pb, but luminosity is in fb^-1.

    // setting and adding new branch into trees
    for (auto &pro : process)
    {
        for (auto &id : pro.second)
        {
            for (auto &cam : campaign)
            {
                string name = path + prefix + to_string(id) + "_" + cam + ".root";
                TFile *f = TFile::Open(name.c_str(), "update");
                TTree *t = (TTree *)f->Get("NOMINAL");
                //TTree *t = t1->CopyTree();
                //t->SetName("NOM");
                TH1D *h = (TH1D *)f->Get("h_metadata");
                TH1D *ht = (TH1D *)f->Get("h_metadata_theory_weights");

                auto branch_dsid = t->Branch("dsid", &dsid, "dsid/I");
                auto branch_final_weight = t->Branch("final_weight", &final_weight, "final_weight/D");

                t->SetBranchAddress("NOMINAL_pileup_random_run_number", &NOMINAL_pileup_random_run_number);
                t->SetBranchAddress("weight_mc", &weight_mc);
                t->SetBranchAddress("theory_weights_nominal", &theory_weights_nominal);
                t->SetBranchAddress("cross_section", &cross_section);
                t->SetBranchAddress("NOMINAL_pileup_combined_weight", &NOMINAL_pileup_combined_weight);
                t->SetBranchAddress("tau_1_NOMINAL_MuEffSF_Reco_QualMedium", &tau_1_NOMINAL_MuEffSF_Reco_QualMedium);
                t->SetBranchAddress("tau_1_NOMINAL_MuEffSF_IsoFCTightTrackOnly", &tau_1_NOMINAL_MuEffSF_IsoFCTightTrackOnly);
                t->SetBranchAddress("tau_1_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium", &tau_1_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium);
                t->SetBranchAddress("jet_NOMINAL_global_effSF_DL1r_FixedCutBEff_85", &jet_NOMINAL_global_effSF_DL1r_FixedCutBEff_85);
                t->SetBranchAddress("jet_NOMINAL_global_ineffSF_DL1r_FixedCutBEff_85", &jet_NOMINAL_global_ineffSF_DL1r_FixedCutBEff_85);
                t->SetBranchAddress("jet_NOMINAL_central_jets_global_effSF_JVT", &jet_NOMINAL_central_jets_global_effSF_JVT);
                t->SetBranchAddress("jet_NOMINAL_central_jets_global_ineffSF_JVT", &jet_NOMINAL_central_jets_global_ineffSF_JVT);
                t->SetBranchAddress("jet_NOMINAL_forward_jets_global_effSF_JVT", &jet_NOMINAL_forward_jets_global_effSF_JVT);

                double Xsec = 0.0;
                for (int i = 0; i < 183; ++i)
                {
                    if (xsec[i][0] == id) //此处 xsec[i][0] 仍为 int 型
                    {
                        Xsec = xsec[i][1];
                    }
                    //cout << "xsec = " << xsec[i][1] << endl;
                }

                cout << "looping for " << id << "..." << endl;
                double mc_sum_of_weights = h->GetBinContent(8);
                double signal_sum_of_weights = ht->GetBinContent(110);
                double signal_sum_of_weights_ggH = ht->GetBinContent(152);
                for (int i = 0; i < t->GetEntries(); ++i)
                {
                    t->GetEntry(i);
                    string y = "";

                    // if (cam == "mc16a")
                    // {
                    //    y = "15"; 
                    // }
                    if (cam == "mc16d")
                    {
                        y = "17";
                    }
                    else if (cam == "mc16e")
                    
                    {
                        y = "18";
                    }
                    // if (NOMINAL_pileup_random_run_number > 0 && NOMINAL_pileup_random_run_number <= 284484)
                    // {
                    //     y = "15";
                    // }
                    // else if (NOMINAL_pileup_random_run_number > 284484 && NOMINAL_pileup_random_run_number <= 311563)
                    // {
                    //     y = "16";
                    // }
                    // else if (NOMINAL_pileup_random_run_number > 311563 && NOMINAL_pileup_random_run_number <= 341649)
                    // {
                    //     y = "17";
                    // }
                    // else if (NOMINAL_pileup_random_run_number >= 341650)
                    // {
                    //     y = "18";
                    // }
                    else
                       continue;

                    dsid = id;
                    double SF = NOMINAL_pileup_combined_weight * tau_1_NOMINAL_MuEffSF_Reco_QualMedium * tau_1_NOMINAL_MuEffSF_IsoFCTightTrackOnly * tau_1_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium * jet_NOMINAL_global_effSF_DL1r_FixedCutBEff_85 * jet_NOMINAL_global_ineffSF_DL1r_FixedCutBEff_85 * jet_NOMINAL_central_jets_global_effSF_JVT * jet_NOMINAL_central_jets_global_ineffSF_JVT * jet_NOMINAL_forward_jets_global_effSF_JVT;
                    
                    if ((pro.first).find("signal") != string::npos)
                    {
                        if (std::find(ggH.begin(), ggH.end(), id) != ggH.end())
                        {
                            cout << "this is ggH sample." << endl; 
                            final_weight = year.at(y) * Xsec * theory_weights_nominal * SF * uc / signal_sum_of_weights_ggH;
                        }
                        else
                        {
                            cout << "this is other signal sample." << endl;
                            final_weight = year.at(y) * Xsec * theory_weights_nominal * SF * uc / signal_sum_of_weights * ;
                        }
                    }
                    else
                    {
                        final_weight = year.at(y) * Xsec * weight_mc * SF * uc / mc_sum_of_weights;
                    }
                    branch_dsid->Fill();
                    branch_final_weight->Fill();
                }
                t->Write();
            }
        }
        cout << pro.first << " processed successfully!" << endl;
    }
    cout << "done!" << endl;
}