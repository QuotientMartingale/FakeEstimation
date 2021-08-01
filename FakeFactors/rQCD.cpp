void rQCD()
{
    gROOT->SetStyle("ATLAS");
    gStyle->SetErrorX(0.5);

    cout << "" << endl;
    TFile *fnum = TFile::Open("../output/rQCDHistograms.root", "read");
    TFile *fden = TFile::Open("../output/FFHistograms.root", "read");
    string dataNum = "data_presel_mu_1p0n_qcd_lh_anti_tau_truth_lep_18";
    string mcNum = "mc_presel_mu_1p0n_qcd_lh_anti_tau_truth_lep_18";
    string dataDen = "data_presel_mu_1p0n_anti_tau_18";
    string mcDen = "mc_presel_mu_1p0n_anti_tau_18";
    TH1D *hdataNum = (TH1D *)fnum->Get(dataNum.c_str());
    TH1D *hdataDen = (TH1D *)fden->Get(dataDen.c_str());
    TH1D *hmcNum = (TH1D *)fnum->Get(mcNum.c_str());
    TH1D *hmcDen = (TH1D *)fden->Get(mcDen.c_str());
    cout << hdataNum->Integral() << " : " << hdataDen->Integral() << endl;
    cout << hmcNum->Integral() << " : " << hmcDen->Integral() << endl;
    hdataNum->Add(hmcNum, -1);
    hdataDen->Add(hmcDen, -1);
    cout << hdataNum->Integral() << " : " << hdataDen->Integral() << endl;
    double xbins[] = {30, 40, 500};
    int binNum = sizeof(xbins) / sizeof(xbins[0]) - 1;
    TH1D *hnumRebin = (TH1D *)hdataNum->Rebin(binNum, "hRebin", xbins);
    TH1D *hdenRebin = (TH1D *)hdataDen->Rebin(binNum, "hRebin", xbins);
    TH1D *Iso;
    Iso = (TH1D *)hnumRebin->Clone();
    Iso->Divide(hdenRebin);
    cout << Iso->GetEntries() << endl;
    TFile *f1 = TFile::Open("../output/rQCD.root", "recreate");
    string hIso = "rQCD_presel_mu_1p0n_18";
    Iso->SetName(hIso.c_str());
    Iso->GetXaxis()->SetTitle("Hadronic Tau p_{T} [GeV]");
    Iso->GetYaxis()->SetTitle("rQCD values");
    Iso->Write();
    TCanvas *c;
    c = new TCanvas("", "", 900, 700);
    c->SetLogx();
    Iso->Draw("E");
    //legend->Draw();
    string savePath = "../plots/rQCDs/";
    string plotTitle = "rQCD_presel_mu_1p0n_18";
    string plotSufix = ".pdf";
    string save = savePath + plotTitle + plotSufix;
    c->SaveAs(save.c_str());

    cout << "plots saved!" << endl;
}