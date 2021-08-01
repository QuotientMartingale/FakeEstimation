#include "TROOT.h"
#include "TChain.h"
#include "THStack.h"
#include "TH1.h"
#include "TCanvas.h"
#include "iostream"
#include "TTree.h"
#include "TLegend.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
using namespace std;

void cut_mc_Trees()
{
    //TDirectory::AddDirectory(kFALSE);
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
    double weight_mc;
    double final_weight;
    double scaled_final_weight;
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
    vector<int> signal_unpol = {
        346531, 346532, 346564, 346569, 346570, 346573,
        //346909, 346912, 346915, 346919, 346923, 346927
    };

    vector<int> ggH_He7 = {600565, 600566, 600567, 600568};
    vector<int> VBFH_He7 = {600569, 600570, 600571, 600572};
    vector<int> WH_He7 = {600573, 600574};
    vector<int> ZH_He7 = {600575};

    vector<int> ttH_afii = {346343, 346344, 346345};
    vector<int> ttH_afii_ME = {346443, 346444, 346445};
    vector<int> ttH_afii_PS = {346346, 346347, 346348};

    vector<int> all = {
        344772, 344774, 344775, 344776, 344778, 344779, 344780, 344781, 344782, 364137, 364138, 364139, 364140, 364141, 364210, 364211, 364212, 364213, 364214, 364215, 308094, 410470, 410471, 410644, 410645, 410646, 410647, 410658, 410659, 410155, 410218, 410219, 410220, 412043, 304014, 363355, 363356, 363357, 363358, 363359, 363489, 363494, 364250, 364253, 364254, 364255, 364288, 364289, 364290, 364156, 364157, 364158, 364159, 364160, 364161, 364162, 364163, 364164, 364165, 364166, 364167, 364168, 364169, 364170, 364171, 364172, 364173, 364174, 364175, 364176, 364177, 364178, 364179, 364180, 364181, 364182, 364183, 364184, 364185, 364186, 364187, 364188, 364189, 364190, 364191, 364192, 364193, 364194, 364195, 364196, 364197, 308096, 308097, 308098, 345099, 345100, 345101, 345102, 364100, 364101, 364102, 364103, 364104, 364105, 364106, 364107, 364108, 364109, 364110, 364111, 364112, 364113, 364114, 364115, 364116, 364117, 364118, 364119, 364120, 364121, 364122, 364123, 364124, 364125, 364126, 364127, 364198, 364199, 364200, 364201, 364202, 364203, 364204, 364205, 364206, 364207, 364208, 364209, 308092, 308093, 345324, 345948, 345121, 345122, 345123, 346191, 346192, 346193, 345211, 345212, 345217, 346343, 346344, 346345, 346527, 346528, 346562, 346565, 346566, 346571, 346531, 346532, 346564, 346569, 346570, 346573, 346909, 346912, 346915, 346919, 346923, 346927, 600565, 600566, 600567, 600568, 600569, 600570, 600571, 600572, 600573, 600574, 600575,
        //346343, 346344, 346345, 346443, 346444, 346445, 346346, 346347, 346348
    };

    map<string, vector<int>> process = {
        //{"Top", Top},
        //{"other_bkg", other_bkg},
        //{"Ztt", Ztt},
        {"signal_SM", signal_SM},
        //{"signal_CPodd", signal_CPodd},
        //{"signal_unpol", signal_unpol},
    };

    vector<string> years = {
        //"15",
        //"16",
        //"17",
        "18",
    };

    string channels[] = {
        // // lephad
        // "e_1p0n", "e_1p1n", "e_1pXn", "e_3p0n", "e_3pXn",
        // "mu_1p0n", "mu_1p1n", "mu_1pXn", "mu_3p0n", "mu_3pXn",
        "1p0n", "1p1n", "1pXn", "3p0n", "3pXn",
        // hadhad
        // "1p0n_1p0n", "1p1n_1p1n", "1pXn_1pXn", "3p0n_3p0n", "3pXn_3pXn", "1p0n_1p1n", "1p1n_1p0n", "1p0n_1pXn", "1pXn_1p0n", "1p1n_1pXn", "1pXn_1p1n",
        // "3p0n_3pXn", "3pXn_3p0n", "1p0n_3p0n", "3p0n_1p0n", "1p0n_3pXn", "3pXn_1p0n","1p1n_3p0n", "3p0n_1p1n", "1p1n_3pXn", "3pXn_1p1n", "1pXn_3p0n", "3p0n_1pXn", "1pXn_3pXn", "3pXn_1pXn",
    };

    vector<string> triggers = {
        //"di_had",
        //"single_e",
        "single_mu",
        //"lephad",
    };

    vector<string> categories = {
        "preselection",
        //"VBF",
        //"VBF_sr",
        //"VBF_zcr",
        //"Boost",
        //"Boost_sr",
        //"Boost_zcr"
    };

    vector<string> ctrl = {
        "presel",
        //"sr",
        //"zcr",
    };

    vector<string> regions = {
        "SR",
        //"anti_tau",
        //"same_sign",
        //"same_sign_anti_tau",
        //"same_sign_SR",
        // // used for lh closure test
        // "same_sign_anti_tau_lh",
        // // Top
        // "top",
        // "top_anti_tau",
        // // lephad WCR
        "W_lh",
        //"W_lh_same_sign",
        //"W_lh_anti_tau",
        //"W_lh_same_sign_anti_tau",
        // "W_lh_hhfake",
        // "W_lh_anti_tau_hhfake",
        // "W_lh_anti_tau_lnm_hhfake",
        // // lephad qcd CR
        //"qcd_test",
        "qcd_lh",
        //"qcd_lh_same_sign",
        //"qcd_lh_anti_tau",
        //"qcd_lh_same_sign_anti_tau",
        //"qcd_lh_truth_lep",
        // "qcd_lh_anti_tau_truth_lep",
        // "qcd_lh_same_sign_anti_tau_truth_lep",
        // // iso factor OS region
        //"iso_fact_lh_num",
        //"iso_fact_lh_den",
        //"iso_fact_lh_os_anti_tau_num",
        //"iso_fact_lh_os_anti_tau_den",
        // // Iso factor SS region
        //"iso_fact_lh_same_sign_anti_tau_num",
        //"iso_fact_lh_same_sign_anti_tau_den",
    };

    vector<string> tau = {
        "tau",
        "anti_tau",
    };
    vector<string> sign = {
        "os",
        "same_sign",
    };

    //生成与 process 一样多的 chain, 此时无需管顺序，每个都直接 SetBranchAdress 即可
    TChain *mcChain[process.size()];
    for (int i = 0; i < process.size(); ++i)
    {
        mcChain[i] = new TChain("NOMINAL");

        //set branch
        mcChain[i]->SetBranchAddress("NOMINAL_pileup_random_run_number", &NOMINAL_pileup_random_run_number);
        mcChain[i]->SetBranchAddress("event_is_bad_batman", &event_is_bad_batman);
        mcChain[i]->SetBranchAddress("n_pvx", &n_pvx);
        mcChain[i]->SetBranchAddress("n_electrons", &n_electrons);
        mcChain[i]->SetBranchAddress("n_muons", &n_muons);
        mcChain[i]->SetBranchAddress("n_taus", &n_taus);
        mcChain[i]->SetBranchAddress("n_jets", &n_jets);
        mcChain[i]->SetBranchAddress("n_taus_rnn_medium", &n_taus_rnn_medium);
        mcChain[i]->SetBranchAddress("ditau_p4", &ditau_p4);
        mcChain[i]->SetBranchAddress("ditau_qxq", &ditau_qxq);
        mcChain[i]->SetBranchAddress("ditau_mt_lep1_met", &ditau_mt_lep1_met);
        mcChain[i]->SetBranchAddress("ditau_coll_approx_x0", &ditau_coll_approx_x0);
        mcChain[i]->SetBranchAddress("ditau_coll_approx_x1", &ditau_coll_approx_x1);
        mcChain[i]->SetBranchAddress("ditau_dr", &ditau_dr);
        mcChain[i]->SetBranchAddress("ditau_deta", &ditau_deta);
        mcChain[i]->SetBranchAddress("ditau_dphi", &ditau_dphi);
        mcChain[i]->SetBranchAddress("ditau_higgspt", &ditau_higgspt);
        mcChain[i]->SetBranchAddress("ditau_mmc_mlm_m", &ditau_mmc_mlm_m);
        mcChain[i]->SetBranchAddress("ditau_mmc_mlm_fit_status", &ditau_mmc_mlm_fit_status);
        mcChain[i]->SetBranchAddress("tau_0_p4", &tau_0_p4);
        mcChain[i]->SetBranchAddress("tau_0_q", &tau_0_q);
        mcChain[i]->SetBranchAddress("tau_0_jet_rnn_medium", &tau_0_jet_rnn_medium);
        mcChain[i]->SetBranchAddress("tau_0_jet_rnn_score_trans", &tau_0_jet_rnn_score_trans);
        mcChain[i]->SetBranchAddress("tau_0_matched_pdgId", &tau_0_matched_pdgId);
        mcChain[i]->SetBranchAddress("tau_1_matched_pdgId", &tau_1_matched_pdgId);
        mcChain[i]->SetBranchAddress("tau_0_decay_mode", &tau_0_decay_mode);
        mcChain[i]->SetBranchAddress("tau_0_ele_bdt_score_trans_retuned", &tau_0_ele_bdt_score_trans_retuned);
        mcChain[i]->SetBranchAddress("tau_1_p4", &tau_1_p4);
        mcChain[i]->SetBranchAddress("tau_1_id_medium", &tau_1_id_medium);
        mcChain[i]->SetBranchAddress("tau_1_iso_FCLoose", &tau_1_iso_FCLoose);
        mcChain[i]->SetBranchAddress("tau_1_iso_FCTightTrackOnly", &tau_1_iso_FCTightTrackOnly);
        mcChain[i]->SetBranchAddress("tau_1_electron_trig_HLT_e24_lhmedium_L1EM20VH", &tau_1_electron_trig_HLT_e24_lhmedium_L1EM20VH);
        mcChain[i]->SetBranchAddress("tau_1_electron_trig_HLT_e60_lhmedium", &tau_1_electron_trig_HLT_e60_lhmedium);
        mcChain[i]->SetBranchAddress("tau_1_electron_trig_HLT_e120_lhloose", &tau_1_electron_trig_HLT_e120_lhloose);
        mcChain[i]->SetBranchAddress("tau_1_electron_trig_HLT_e26_lhtight_nod0_ivarloose", &tau_1_electron_trig_HLT_e26_lhtight_nod0_ivarloose);
        mcChain[i]->SetBranchAddress("tau_1_electron_trig_HLT_e60_lhmedium_nod0", &tau_1_electron_trig_HLT_e60_lhmedium_nod0);
        mcChain[i]->SetBranchAddress("tau_1_electron_trig_HLT_e140_lhloose_nod0", &tau_1_electron_trig_HLT_e140_lhloose_nod0);
        mcChain[i]->SetBranchAddress("tau_1_muon_trig_HLT_mu20_iloose_L1MU15", &tau_1_muon_trig_HLT_mu20_iloose_L1MU15);
        mcChain[i]->SetBranchAddress("tau_1_muon_trig_HLT_mu50", &tau_1_muon_trig_HLT_mu50);
        mcChain[i]->SetBranchAddress("tau_1_muon_trig_HLT_mu26_ivarmedium", &tau_1_muon_trig_HLT_mu26_ivarmedium);
        mcChain[i]->SetBranchAddress("dijet_p4", &dijet_p4);
        mcChain[i]->SetBranchAddress("jet_0_p4", &jet_0_p4);
        mcChain[i]->SetBranchAddress("jet_1_p4", &jet_1_p4);
        mcChain[i]->SetBranchAddress("met_p4", &met_p4);
        mcChain[i]->SetBranchAddress("truth_passedVBFFilter", &truth_passedVBFFilter);
        mcChain[i]->SetBranchAddress("n_bjets_DL1r_FixedCutBEff_85", &n_bjets_DL1r_FixedCutBEff_85);
        mcChain[i]->SetBranchAddress("is_dijet_centrality", &is_dijet_centrality);
        mcChain[i]->SetBranchAddress("weight_mc", &weight_mc);
        mcChain[i]->SetBranchAddress("cross_section", &cross_section);
        mcChain[i]->SetBranchAddress("final_weight", &final_weight);
        mcChain[i]->SetBranchAddress("scaled_final_weight", &scaled_final_weight);
        mcChain[i]->SetBranchAddress("dsid", &dsid);
    }

    // if you duplicate input samples in the input_samples directory, use the following path, otherwise use your own path.
    string mcPath = "../preprocessed_samples/combined_mc_samples";
    string mcPrefix = "group.phys-higgs.Htt_lh_V03.mc16_13TeV.";
    vector<string> proNames;
    int n = 0;
    for (auto &pro : process)
    {
        proNames.push_back(pro.first);
        for (auto &id : pro.second)
        {
            string mcName = mcPath + mcPrefix + to_string(id) + "_mc16e.root";
            mcChain[n]->Add(mcName.c_str());
        }
        n = n + 1;
    }

    cout << "Chain adding success!" << endl;

    // cuts
    //categories
    string cut_presel = "(n_pvx >= 1) && (event_is_bad_batman == 0) && (truth_passedVBFFilter == 0) && (tau_0_p4->Pt() > 30) && (abs(tau_0_q) == 1) && (abs(tau_0_p4->Eta()) < 2.4) && (tau_1_id_medium == 1) && (n_bjets_DL1r_FixedCutBEff_85 == 0) && (jet_0_p4->Pt() >= 40) && (met_p4->Pt() > 20) && (ditau_coll_approx_x0 > 0.1 && ditau_coll_approx_x1 > 0.1) && (ditau_coll_approx_x0 < 1.4 && ditau_coll_approx_x1 < 1.2) && (ditau_dr < 2.5 && fabs(ditau_deta) < 1.5) && (ditau_mmc_mlm_fit_status == 1)";
    string cut_vbf = "(jet_1_p4->Pt() > 30 && dijet_p4->M() > 400 && fabs(jet_0_p4->Eta() - jet_1_p4->Eta()) > 3 && jet_0_p4->Eta() * jet_1_p4->Eta() < 0 && is_dijet_centrality == 1)";
    string cut_boost = "(!((jet_1_p4->Pt() > 30 && dijet_p4->M() > 400 && fabs(jet_0_p4->Eta() - jet_1_p4->Eta()) > 3 && jet_0_p4->Eta() * jet_1_p4->Eta() < 0 && is_dijet_centrality == 1)) && (ditau_higgspt > 100))";
    string cut_VH = "dijet_p4->M() > 60 && dijet_p4->M() < 120";
    //ZCR
    string cut_ZSR = "(ditau_mmc_mlm_m > 110 && ditau_mmc_mlm_m < 150)";
    string cut_ZCR = "(ditau_mmc_mlm_m > 60 && ditau_mmc_mlm_m < 110)";
    // years
    string cut_year_15 = "(NOMINAL_pileup_random_run_number > 0 && NOMINAL_pileup_random_run_number <= 284484)";
    string cut_year_16 = "(NOMINAL_pileup_random_run_number > 284484 && NOMINAL_pileup_random_run_number <= 311563)";
    string cut_year_17 = "(NOMINAL_pileup_random_run_number > 311563 && NOMINAL_pileup_random_run_number <= 341649)";
    string cut_year_18 = "(NOMINAL_pileup_random_run_number >= 341650)";
    // decay_modes
    string cut_1p0n = "(tau_0_decay_mode == 0)";
    string cut_1p1n = "(tau_0_decay_mode == 1)";
    string cut_1pXn = "(tau_0_decay_mode == 2)";
    string cut_3p0n = "(tau_0_decay_mode == 4)";
    string cut_3pXn = "(tau_0_decay_mode == 5)";
    // triggers
    string cut_single_e = "(n_electrons == 1 && n_muons == 0 && n_taus == 1)";
    string cut_single_mu = "(n_electrons == 0 && n_muons == 1 && n_taus == 1)";
    string cut_trigger_e_15 = "(tau_1_electron_trig_HLT_e24_lhmedium_L1EM20VH || tau_1_electron_trig_HLT_e60_lhmedium || tau_1_electron_trig_HLT_e120_lhloose)";
    string cut_trigger_e_161718 = "(tau_1_electron_trig_HLT_e26_lhtight_nod0_ivarloose || tau_1_electron_trig_HLT_e60_lhmedium_nod0 || tau_1_electron_trig_HLT_e140_lhloose_nod0)";
    string cut_trigger_mu_15 = "(tau_1_muon_trig_HLT_mu20_iloose_L1MU15 || tau_1_muon_trig_HLT_mu50)";
    string cut_trigger_mu_161718 = "(tau_1_muon_trig_HLT_mu26_ivarmedium || tau_1_muon_trig_HLT_mu50)";
    // tau_0_pt
    string cut_tau_1_pt_e_15 = "(tau_1_p4->Pt() > 25)";
    string cut_tau_1_pt_e_161718 = "(tau_1_p4->Pt() > 27)";
    string cut_tau_1_pt_mu_15 = "(tau_1_p4->Pt() > 21)";
    string cut_tau_1_pt_mu_161718 = "(tau_1_p4->Pt() > 27.3)";
    // truth selection
    string cut_true_tau = "((abs(tau_0_matched_pdgId) < 7 || tau_0_matched_pdgId == 21) == 0)";
    string cut_true_e = "(abs(tau_1_matched_pdgId)==11)";
    string cut_true_mu = "(abs(tau_1_matched_pdgId)==13)";
    //tau_id
    string cut_tau = "(tau_0_jet_rnn_medium == 1 && n_taus_rnn_medium == 1)";
    string cut_anti_tau = "(tau_0_jet_rnn_medium == 0 && n_taus_rnn_medium == 0 && tau_0_jet_rnn_score_trans > 0.01)";
    // tau_sign
    string cut_os = "(ditau_qxq == -1)";
    string cut_same_sign = "(ditau_qxq == 1)";
    // control regions
    string cut_WSR = "(ditau_mt_lep1_met < 70)";
    string cut_WCR = "(ditau_mt_lep1_met > 70)";
    string cut_e_QCDSR = "(tau_1_iso_FCLoose == 1)";
    string cut_e_QCDCR = "(tau_1_iso_FCLoose != 1)";
    string cut_mu_QCDSR = "(tau_1_iso_FCTightTrackOnly == 1)";
    string cut_mu_QCDCR = "(tau_1_iso_FCTightTrackOnly != 1)";
    //string cut_topSR = "(n_bjets_DL1r_FixedCutBEff_85==0) && (ditau_mt_lep1_met > 70)";
    //string cut_topCR = "(n_bjets_DL1r_FixedCutBEff_85>0) && (ditau_mt_lep1_met > 40)";

    cout << "\n";
    cout << "---------- mc Tree selection program ----------" << endl;
    cout << "\n";

    for (int p = 0; p < process.size(); ++p) //此处并非循环process, 实际是循环chain
    {
        cout << "----- Processing " << proNames[p] << " -----" << endl;
        cout << "\n";
        string chainName = proNames[p] + "_Chain";

        cout << "Calculating entries of " << chainName << "..." << endl;
        clock_t start1, finish1;
        start1 = clock();
        int ent = mcChain[p]->GetEntries();
        finish1 = clock();
        double runtime1 = double(finish1 - start1) / CLOCKS_PER_SEC;
        cout << chainName << " has " << ent << " entries." << endl;
        cout << "calculation time: " << runtime1 << "s." << endl;
        cout << "\n";
        cout << "Start copying " << chainName << "..." << endl;
        clock_t start2, finish2;
        start2 = clock();

        TTree *t_presel = mcChain[p]->CopyTree(cut_presel.c_str());
        cout << "preselection done!" << endl;

        // SR
        string t1_cut;
        t1_cut = Form("%s && %s && %s && %s && %s && %s && %s && %s && %s && %s", cut_1p0n.c_str(), cut_tau.c_str(), cut_os.c_str(), cut_year_18.c_str(), cut_single_mu.c_str(), cut_trigger_mu_161718.c_str(), cut_tau_1_pt_mu_161718.c_str(), cut_WSR.c_str(), cut_mu_QCDSR.c_str(), cut_true_tau.c_str());
        //t1_cut = "tau_0_p4.Pt()>90";
        TTree *t1 = t_presel->CopyTree(t1_cut.c_str());
        string t1Name = proNames.at(p) + "_presel_mu_1p0n_SR_18";
        t1->SetName(t1Name.c_str());
        cout << proNames.at(p) << " chain SR copied." << endl;
        // anti_tau
        string t2_cut;
        t2_cut = Form("%s && %s && %s && %s && %s && %s && %s && %s && %s && %s", cut_1p0n.c_str(), cut_anti_tau.c_str(), cut_os.c_str(), cut_year_18.c_str(), cut_single_mu.c_str(), cut_trigger_mu_161718.c_str(), cut_tau_1_pt_mu_161718.c_str(), cut_WSR.c_str(), cut_mu_QCDSR.c_str(), cut_true_tau.c_str());
        TTree *t2 = t_presel->CopyTree(t2_cut.c_str());
        string t2Name = proNames.at(p) + "_presel_mu_1p0n_anti_tau_18";
        t2->SetName(t2Name.c_str());
        cout << proNames.at(p) << " chain anti_tau copied." << endl;
        // W_lh
        string t3_cut;
        t3_cut = Form("%s && %s && %s && %s && %s && %s && %s && %s && %s && %s", cut_1p0n.c_str(), cut_tau.c_str(), cut_os.c_str(), cut_year_18.c_str(), cut_single_mu.c_str(), cut_trigger_mu_161718.c_str(), cut_tau_1_pt_mu_161718.c_str(), cut_WCR.c_str(), cut_mu_QCDSR.c_str(), cut_true_tau.c_str());
        TTree *t3 = t_presel->CopyTree(t3_cut.c_str());
        string t3Name = proNames.at(p) + "_presel_mu_1p0n_W_lh_18";
        t3->SetName(t3Name.c_str());
        cout << proNames.at(p) << " chain W_lh copied." << endl;
        // W_lh_anti_tau
        string t4_cut;
        t4_cut = Form("%s && %s && %s && %s && %s && %s && %s && %s && %s && %s", cut_1p0n.c_str(), cut_anti_tau.c_str(), cut_os.c_str(), cut_year_18.c_str(), cut_single_mu.c_str(), cut_trigger_mu_161718.c_str(), cut_tau_1_pt_mu_161718.c_str(), cut_WCR.c_str(), cut_mu_QCDSR.c_str(), cut_true_tau.c_str());
        TTree *t4 = t_presel->CopyTree(t4_cut.c_str());
        string t4Name = proNames.at(p) + "_presel_mu_1p0n_W_lh_anti_tau_18";
        t4->SetName(t4Name.c_str());
        cout << proNames.at(p) << " chain W_lh_anti_tau copied." << endl;
        // qcd_lh
        string t5_cut;
        t5_cut = Form("%s && %s && %s && %s && %s && %s && %s && %s && %s && %s", cut_1p0n.c_str(), cut_tau.c_str(), cut_os.c_str(), cut_year_18.c_str(), cut_single_mu.c_str(), cut_trigger_mu_161718.c_str(), cut_tau_1_pt_mu_161718.c_str(), cut_WSR.c_str(), cut_mu_QCDCR.c_str(), cut_true_tau.c_str());
        TTree *t5 = t_presel->CopyTree(t5_cut.c_str());
        string t5Name = proNames.at(p) + "_presel_mu_1p0n_qcd_lh_18";
        t5->SetName(t5Name.c_str());
        cout << proNames.at(p) << " chain qcd_lh copied." << endl;
        // qcd_lh_anti_tau
        string t6_cut;
        t6_cut = Form("%s && %s && %s && %s && %s && %s && %s && %s && %s && %s", cut_1p0n.c_str(), cut_anti_tau.c_str(), cut_os.c_str(), cut_year_18.c_str(), cut_single_mu.c_str(), cut_trigger_mu_161718.c_str(), cut_tau_1_pt_mu_161718.c_str(), cut_WSR.c_str(), cut_mu_QCDCR.c_str(), cut_true_tau.c_str());
        TTree *t6 = t_presel->CopyTree(t6_cut.c_str());
        string t6Name = proNames.at(p) + "_presel_mu_1p0n_qcd_lh_anti_tau_18";
        t6->SetName(t6Name.c_str());
        cout << proNames.at(p) << " chain qcd_lh_anti_tau copied." << endl;
        // qcd_lh_anti_tau_truth_lep
        string t7_cut;
        t7_cut = Form("%s && %s && %s && %s && %s && %s && %s && %s && %s && %s && %s", cut_1p0n.c_str(), cut_anti_tau.c_str(), cut_os.c_str(), cut_year_18.c_str(), cut_single_mu.c_str(), cut_trigger_mu_161718.c_str(), cut_tau_1_pt_mu_161718.c_str(), cut_WSR.c_str(), cut_mu_QCDCR.c_str(), cut_true_mu.c_str(), cut_true_tau.c_str());
        TTree *t7 = t_presel->CopyTree(t7_cut.c_str());
        string t7Name = proNames.at(p) + "_presel_mu_1p0n_qcd_lh_anti_tau_truth_lep_18";
        t7->SetName(t7Name.c_str());
        cout << proNames.at(p) << " chain qcd_lh_anti_tau_truth_lep copied." << endl;
        // iso_fact_lh_same_sign_anti_tau_num
        string t8_cut;
        t8_cut = Form("%s && %s && %s && %s && %s && %s && %s && %s && %s && %s", cut_1p0n.c_str(), cut_anti_tau.c_str(), cut_same_sign.c_str(), cut_year_18.c_str(), cut_single_mu.c_str(), cut_trigger_mu_161718.c_str(), cut_tau_1_pt_mu_161718.c_str(), cut_WSR.c_str(), cut_mu_QCDSR.c_str(), cut_true_mu.c_str());
        TTree *t8 = t_presel->CopyTree(t8_cut.c_str());
        string t8Name = proNames.at(p) + "_presel_mu_1p0n_iso_fact_lh_same_sign_anti_tau_num_18";
        t8->SetName(t8Name.c_str());
        cout << proNames.at(p) << " chain iso_fact_lh_same_sign_anti_tau_num copied." << endl;
        // iso_fact_lh_same_sign_anti_tau_den
        string t9_cut;
        t9_cut = Form("%s && %s && %s && %s && %s && %s && %s && %s && %s && %s", cut_1p0n.c_str(), cut_anti_tau.c_str(), cut_same_sign.c_str(), cut_year_18.c_str(), cut_single_mu.c_str(), cut_trigger_mu_161718.c_str(), cut_tau_1_pt_mu_161718.c_str(), cut_WSR.c_str(), cut_mu_QCDCR.c_str(), cut_true_mu.c_str());
        TTree *t9 = t_presel->CopyTree(t9_cut.c_str());
        string t9Name = proNames.at(p) + "_presel_mu_1p0n_iso_fact_lh_same_sign_anti_tau_den_18";
        t9->SetName(t9Name.c_str());
        cout << proNames.at(p) << " chain iso_fact_lh_same_sign_anti_tau_den copied." << endl;

        finish2 = clock();
        double runtime2 = double(finish2 - start2) / CLOCKS_PER_SEC;
        cout << "copying done." << endl;
        cout << "time: " << runtime2 << "s." << endl;
        cout << "\n";

        string fileName = "../preprocessed_samples/mc_Trees.root";
        TFile *f = TFile::Open(fileName.c_str(), "recreate");
        t1->Write();
        t2->Write();
        t3->Write();
        t4->Write();
        t5->Write();
        t6->Write();
        t7->Write();
        t8->Write();
        t9->Write();
        f->Close();
        cout << "processing done!" << endl;
    }
}