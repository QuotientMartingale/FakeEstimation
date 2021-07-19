void cuts()
{
    // cuts
    //categories
    string cut_presel = "(n_pvx >= 1) && (event_is_bad_batman == 0) && (truth_passedVBFFilter == 0) && (tau_0_p4->Pt() > 30) && (abs(tau_0_q) == 1) && (abs(tau_0_p4->Eta()) < 2.4) && (tau_1_id_medium == 1) && (n_bjets_DL1r_FixedCutBEff_85 == 0) && (jet_0_p4->Pt() >= 40) && (met_p4->Pt() > 20) && (ditau_coll_approx_x0 > 0.1) && (ditau_coll_approx_x1 > 0.1) && (ditau_coll_approx_x0 < 1.4) && (ditau_coll_approx_x1 < 1.2) && (ditau_dr < 2.5) && (fabs(ditau_deta) < 1.5) && (ditau_mmc_mlm_fit_status == 1)";
    string cut_vbf = "(jet_1_p4->Pt() > 30) && (dijet_p4->M() > 400) && (fabs(jet_0_p4->Eta() - jet_1_p4->Eta()) > 3) && (jet_0_p4->Eta() * jet_1_p4->Eta() < 0) && (is_dijet_centrality == 1)";
    string cut_boost = "(!((jet_1_p4->Pt() > 30) && (dijet_p4->M() > 400) && (fabs(jet_0_p4->Eta() - jet_1_p4->Eta()) > 3) && (jet_0_p4->Eta() * jet_1_p4->Eta() < 0) && (is_dijet_centrality == 1)) && (ditau_higgspt > 100))"; 
    //ZCR
    string cut_ZSR = "(ditau_mmc_mlm_m > 110) && (ditau_mmc_mlm_m < 150)";
    string cut_ZCR = "(ditau_mmc_mlm_m > 60) && (ditau_mmc_mlm_m < 110)"; 
    // years
    string cut_year_15 = "(NOMINAL_pileup_random_run_number > 0) && (NOMINAL_pileup_random_run_number <= 284484)";
    string cut_year_16 = "(NOMINAL_pileup_random_run_number > 284484) && (NOMINAL_pileup_random_run_number <= 311563)";
    string cut_year_17 = "(NOMINAL_pileup_random_run_number > 311563) && (NOMINAL_pileup_random_run_number <= 341649)";
    string cut_year_18 = "(NOMINAL_pileup_random_run_number >= 341650)";
    // decay_modes
    string cut_1p0n = "(tau_0_decay_mode == 0)";
    string cut_1p1n = "(tau_0_decay_mode == 1)";
    string cut_1pXn = "(tau_0_decay_mode == 2)";
    string cut_3p0n = "(tau_0_decay_mode == 4)";
    string cut_3pXn = "(tau_0_decay_mode == 5)";
    // triggers
    string cut_single_e = "(n_electrons == 1) && (n_muons == 0) && (n_taus == 1)";
    string cut_single_mu = "(n_electrons == 0) && (n_muons == 1) && (n_taus == 1)";
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
    string cut_tau = "(tau_0_jet_rnn_medium == 1) && (n_taus_rnn_medium == 1)";
    string cut_anti_tau = "(tau_0_jet_rnn_medium == 0) && (n_taus_rnn_medium == 0) && (tau_0_jet_rnn_score_trans > 0.01)";
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
}