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

void cutflow()
{
    // TDirectory::AddDirectory(kFALSE);
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
    double scaled_final_weight;
    float theory_weights_nominal;
    int dsid;

    vector<string> regions = {
        "SR",
        "anti_tau",
    };

    map<string, vector<double>> variable = {
        {"tau_0_pt", {20, 20, 220}},
        {"tau_1_pt", {20, 20, 220}},
        {"ditau_dr", {25, 0, 2.5}},
        {"ditau_deta", {20, 0, 2}},
        {"ditau_dphi", {13, 0, 2.6}},
        {"mmc_mlm_m", {20, 0, 200}},
        {"ditau_higgspt", {30, 90, 390}},
    };

    vector<string> campaign = {
        //"mc16a",
        //"mc16d",
        "mc16e",
    };
    gROOT->SetStyle("ATLAS");
    gStyle->SetErrorX(0.5);

    //string Path = "../preprocessed_samples/combined_mc_samples/";
    string Path = "/eos/user/g/guojun/test/mc/mc16e/";
    string Prefix = "group.phys-higgs.Htt_lh_V03.mc16_13TeV.";
    string Suffix = "_mc16e.root";
    string id = "308094";
    string Name = Path + Prefix + id + Suffix;
    TFile *f = TFile::Open(Name.c_str());
    TTree *t = (TTree *)f->Get("NOMINAL");
    t->SetBranchAddress("NOMINAL_pileup_random_run_number", &NOMINAL_pileup_random_run_number);
    t->SetBranchAddress("event_is_bad_batman", &event_is_bad_batman);
    t->SetBranchAddress("n_pvx", &n_pvx);
    t->SetBranchAddress("n_electrons", &n_electrons);
    t->SetBranchAddress("n_muons", &n_muons);
    t->SetBranchAddress("n_taus", &n_taus);
    t->SetBranchAddress("n_jets", &n_jets);
    t->SetBranchAddress("n_taus_rnn_medium", &n_taus_rnn_medium);
    t->SetBranchAddress("ditau_p4", &ditau_p4);
    t->SetBranchAddress("ditau_qxq", &ditau_qxq);
    t->SetBranchAddress("ditau_mt_lep1_met", &ditau_mt_lep1_met);
    t->SetBranchAddress("ditau_coll_approx_x0", &ditau_coll_approx_x0);
    t->SetBranchAddress("ditau_coll_approx_x1", &ditau_coll_approx_x1);
    t->SetBranchAddress("ditau_dr", &ditau_dr);
    t->SetBranchAddress("ditau_deta", &ditau_deta);
    t->SetBranchAddress("ditau_dphi", &ditau_dphi);
    t->SetBranchAddress("ditau_higgspt", &ditau_higgspt);
    t->SetBranchAddress("ditau_mmc_mlm_m", &ditau_mmc_mlm_m);
    t->SetBranchAddress("ditau_mmc_mlm_fit_status", &ditau_mmc_mlm_fit_status);
    t->SetBranchAddress("tau_0_p4", &tau_0_p4);
    t->SetBranchAddress("tau_0_q", &tau_0_q);
    t->SetBranchAddress("tau_0_jet_rnn_medium", &tau_0_jet_rnn_medium);
    t->SetBranchAddress("tau_0_jet_rnn_score_trans", &tau_0_jet_rnn_score_trans);
    t->SetBranchAddress("tau_0_matched_pdgId", &tau_0_matched_pdgId);
    t->SetBranchAddress("tau_1_matched_pdgId", &tau_1_matched_pdgId);
    t->SetBranchAddress("tau_0_decay_mode", &tau_0_decay_mode);
    t->SetBranchAddress("tau_0_ele_bdt_score_trans_retuned", &tau_0_ele_bdt_score_trans_retuned);
    t->SetBranchAddress("tau_1_p4", &tau_1_p4);
    t->SetBranchAddress("tau_1_id_medium", &tau_1_id_medium);
    t->SetBranchAddress("tau_1_iso_FCLoose", &tau_1_iso_FCLoose);
    t->SetBranchAddress("tau_1_iso_FCTightTrackOnly", &tau_1_iso_FCTightTrackOnly);
    t->SetBranchAddress("tau_1_electron_trig_HLT_e24_lhmedium_L1EM20VH", &tau_1_electron_trig_HLT_e24_lhmedium_L1EM20VH);
    t->SetBranchAddress("tau_1_electron_trig_HLT_e60_lhmedium", &tau_1_electron_trig_HLT_e60_lhmedium);
    t->SetBranchAddress("tau_1_electron_trig_HLT_e120_lhloose", &tau_1_electron_trig_HLT_e120_lhloose);
    t->SetBranchAddress("tau_1_electron_trig_HLT_e26_lhtight_nod0_ivarloose", &tau_1_electron_trig_HLT_e26_lhtight_nod0_ivarloose);
    t->SetBranchAddress("tau_1_electron_trig_HLT_e60_lhmedium_nod0", &tau_1_electron_trig_HLT_e60_lhmedium_nod0);
    t->SetBranchAddress("tau_1_electron_trig_HLT_e140_lhloose_nod0", &tau_1_electron_trig_HLT_e140_lhloose_nod0);
    t->SetBranchAddress("tau_1_muon_trig_HLT_mu20_iloose_L1MU15", &tau_1_muon_trig_HLT_mu20_iloose_L1MU15);
    t->SetBranchAddress("tau_1_muon_trig_HLT_mu50", &tau_1_muon_trig_HLT_mu50);
    t->SetBranchAddress("tau_1_muon_trig_HLT_mu26_ivarmedium", &tau_1_muon_trig_HLT_mu26_ivarmedium);
    t->SetBranchAddress("dijet_p4", &dijet_p4);
    t->SetBranchAddress("jet_0_p4", &jet_0_p4);
    t->SetBranchAddress("jet_1_p4", &jet_1_p4);
    t->SetBranchAddress("met_p4", &met_p4);
    t->SetBranchAddress("truth_passedVBFFilter", &truth_passedVBFFilter);
    t->SetBranchAddress("n_bjets_DL1r_FixedCutBEff_85", &n_bjets_DL1r_FixedCutBEff_85);
    t->SetBranchAddress("is_dijet_centrality", &is_dijet_centrality);
    t->SetBranchAddress("weight_mc", &weight_mc);
    t->SetBranchAddress("NOMINAL_pileup_combined_weight", &NOMINAL_pileup_combined_weight);
    t->SetBranchAddress("tau_1_NOMINAL_MuEffSF_Reco_QualMedium", &tau_1_NOMINAL_MuEffSF_Reco_QualMedium);
    t->SetBranchAddress("tau_1_NOMINAL_MuEffSF_IsoFCTightTrackOnly", &tau_1_NOMINAL_MuEffSF_IsoFCTightTrackOnly);
    t->SetBranchAddress("tau_1_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium", &tau_1_NOMINAL_MuEffSF_HLT_mu26_ivarmedium_OR_HLT_mu50_QualMedium);
    t->SetBranchAddress("jet_NOMINAL_global_effSF_DL1r_FixedCutBEff_85", &jet_NOMINAL_global_effSF_DL1r_FixedCutBEff_85);
    t->SetBranchAddress("jet_NOMINAL_global_ineffSF_DL1r_FixedCutBEff_85", &jet_NOMINAL_global_ineffSF_DL1r_FixedCutBEff_85);
    t->SetBranchAddress("jet_NOMINAL_central_jets_global_effSF_JVT", &jet_NOMINAL_central_jets_global_effSF_JVT);
    t->SetBranchAddress("jet_NOMINAL_central_jets_global_ineffSF_JVT", &jet_NOMINAL_central_jets_global_ineffSF_JVT);
    t->SetBranchAddress("jet_NOMINAL_forward_jets_global_effSF_JVT", &jet_NOMINAL_forward_jets_global_effSF_JVT);
    t->SetBranchAddress("scaled_final_weight", &scaled_final_weight);

    vector<double> flow(26, 0);
    long Ent = t->GetEntries();
    long Int = 
    flow[0] = Ent;

    double flag1 = 1;
    double step1 = 0.02;
    clock_t start1, finish1;
    start1 = clock();
    cout << "start cutflow" << endl;

    double lumi = 58450;
    double eff_xsec = 0.63347;
    TH1D *hm = (TH1D *)f->Get("h_metadata");
    double mc_sum_of_weights = hm->GetBinContent(8);
    for (int i = 0; i < Ent; ++i)
    {
        t->GetEntry(i);
        double per = (double)i / (double)Ent;
        if (per >= step1 * flag1)
        {
            ++flag1;
            cout << floor(100 * per) << "%"
                 << " of tree has been looped..." << endl;
        }

        double weight = 1000 * scaled_final_weight;
        //double weight = final_weight;
        double weight = 1.0;

        int n = 1;
        if (!(NOMINAL_pileup_random_run_number >= 341650)) continue;
        flow.at(n) = flow.at(n) + weight;
        if (!(n_pvx >= 1)) continue;
        flow.at(n+1) = flow.at(n+1) + weight;
        if (!(event_is_bad_batman == 0)) continue;
        flow.at(n+2) = flow.at(n+2) + weight;
        if (!(truth_passedVBFFilter == 0)) continue;
        flow.at(n+3) = flow.at(n+3) + weight;
        if (!((abs(tau_0_matched_pdgId) < 7 || tau_0_matched_pdgId == 21) == 0)) continue;
        flow.at(n+4) = flow.at(n+4) + weight;
        if (!(n_electrons == 0 && n_muons == 1 && n_taus == 1)) continue;
        flow.at(n+5) = flow.at(n+5) + weight;
        if (!(n_taus_rnn_medium == 1)) continue;
        flow.at(n+6) = flow.at(n+6) + weight;
        if (!(tau_0_p4->Pt() > 30)) continue;
        flow.at(n+7) = flow.at(n+7) + weight;
        if (!(abs(tau_0_q) == 1)) continue;
        flow.at(n+8) = flow.at(n+8) + weight;
        if (!(abs(tau_0_p4->Eta()) < 2.4)) continue;
        flow.at(n+9) = flow.at(n+9) + weight;
        if (!(tau_0_jet_rnn_medium == 1)) continue;
        flow.at(n+10) = flow.at(n+10) + weight;
        if (!(tau_1_p4->Pt() > 27.3)) continue;
        flow.at(n+11) = flow.at(n+11) + weight; 
        if (!(tau_1_id_medium == 1)) continue;
        flow.at(n+12) = flow.at(n+12) + weight;
        if (!(tau_1_iso_FCTightTrackOnly == 1)) continue;
        flow.at(n+13) = flow.at(n+13) + weight;
        if (!(n_bjets_DL1r_FixedCutBEff_85 == 0)) continue;
        flow.at(n+14) = flow.at(n+14) + weight;
        if (!(tau_0_decay_mode == 0)) continue;
        flow.at(n+15) = flow.at(n+15) + weight;
        if (!(tau_1_muon_trig_HLT_mu26_ivarmedium || tau_1_muon_trig_HLT_mu50)) continue;
        flow.at(n+16) = flow.at(n+16) + weight;
        if (!(ditau_qxq == -1)) continue;
        flow.at(n+17) = flow.at(n+17) + weight;
        if (!(ditau_mt_lep1_met < 70)) continue;
        flow.at(n+18) = flow.at(n+18) + weight;       
        if (!(jet_0_p4->Pt() >= 40)) continue;
        flow.at(n+19) = flow.at(n+19) + weight;
        if (!(met_p4->Pt() > 20)) continue;
        flow.at(n+20) = flow.at(n+20) + weight;
        if (!(ditau_coll_approx_x0 > 0.1 && ditau_coll_approx_x1 > 0.1)) continue;
        flow.at(n+21) = flow.at(n+21) + weight;
        if (!(ditau_coll_approx_x0 < 1.4 && ditau_coll_approx_x1 < 1.2)) continue;
        flow.at(n+22) = flow.at(n+22) + weight;
        if (!(ditau_dr < 2.5 && fabs(ditau_deta) < 1.5)) continue;
        flow.at(n+23) = flow.at(n+23) + weight;
        if (!(ditau_mmc_mlm_fit_status == 1)) continue;
        flow.at(n+24) = flow.at(n+24) + weight;
        
        //if (!(tau_0_jet_rnn_medium == 0 && n_taus_rnn_medium == 0 && tau_0_jet_rnn_score_trans > 0.01)) //anti_atu
        //    continue;
        // flow.at() = flow.at() + weight;
    }
    finish1 = clock();
    double runtime1 = double(finish1 - start1) / CLOCKS_PER_SEC;
    cout << "looping success!" << endl;
    cout << "time: " << runtime1 << endl;

    const char *cut[26] = {
        "total_entries",
        "mc16e_18",
        "npv",
        "event_is_bad_batman",
        "truth_passedVBFFilter",
        "LeadTau_NotAjet",
        "count_mutau",
        "one_medium_tau",
        "tau_pt_cut",
        "tau_charge",
        "tau_eta",
        "tau_medium_id",
        "mu_pt_lh",
        "sublead_lepton_id",
        "sublead_lepton_iso",
        //"BVeto",
        "l_1p0n",
        "trig_mh_slt_16",
        "OS",   
        "transverse_mass", 
        "lead_jet",
        "met_cut",
        "x0x1_low",
        "x0x1_high",
        "ditau_dr_lh",
        "mmc_status",  
        "preselection",
        //"BVeto",
        //"2jets",
        //

    };

    TH1D *h = new TH1D();
    h->SetName("cutflow");
    for (int i = 0; i < 26; ++i)
    {
        h->SetBinContent(i+1, flow.at(i));
        h->GetXaxis()->SetBinLabel(i+1, cut[i]);
    }
    h->GetYaxis()->SetTitle("Events Number");
    double y = h->GetMaximum() * 1.5;
    h->GetYaxis()->SetRangeUser(0, y);
    h->SetMarkerStyle(20);
    h->SetMarkerColor(kBlack);

    // TCanvas *c = new TCanvas("", "", 900, 700);
    // h->Draw("hist");
    // string savePath = "./";
    // string plotTitle = "cutflow";
    // string plotSufix = ".pdf";
    // string save = savePath + plotTitle + plotSufix;
    // c->SaveAs(save.c_str());
    // cout << "plots saved!" << endl;

    TFile *fh = TFile::Open("cutflow.root", "recreate");
    h->Write();

    cout << "cut" << "\t\t\t" << "sel__mu_1p0n__single-mu__preselection__SR__18" << endl;
    cout << "---------------------" << "\t" << "---------------------------------------------" << endl;
    for (int i = 0; i < 26; ++i)
    {
        cout << std::left << setw(21) << cut[i] << "\t" << std::right << setw(5) << flow.at(i) << endl;
    }
}