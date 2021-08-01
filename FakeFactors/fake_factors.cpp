void fake_factors()
{
    TFile *ff = TFile::Open("../output/FakeFactors.root", "read");
    TFile *fR = TFile::Open("../output/rQCD.root", "read");
    TH1D *hw = (TH1D *)ff->Get("FF_W_lh_presel_mu_1p0n_18"); // W_lh ff
    TH1D *hq = (TH1D *)ff->Get("FF_qcd_lh_presel_mu_1p0n_18"); // qcd_lh_ff
    TH1D *hr = (TH1D *)fR->Get("rQCD_presel_mu_1p0n_18"); // rqcd

    int nbins = 2;
    double edges[3] = {30, 40, 500};
    TH1D *h1 = new TH1D("h1", "", nbins, edges); // histogram of value 1
    h1->SetBinContent(1,1);
    h1->SetBinContent(2,1);

    h1->Add(hr,-1);
    TH1D *h1_r;
    h1_r = h1; // 1-rqcd
    hq->Multiply(hr);
    hw->Multiply(h1_r);
    hq->Add(hw);
    TH1D *hFF;
    hFF = hq;
    hFF->SetName("Combined_FF_presel_mu_1p0n_18");
    TFile *f = TFile::Open("../output/Combined_Fake_Factors.root", "recreate");
    hFF->Write();

    gROOT->SetStyle("ATLAS");
    gStyle->SetErrorX(0.5);
    TCanvas *c;
    c = new TCanvas("", "", 900, 700);
    c->SetLogx();
    hFF->Draw("E");
    h1->Draw("same");
    //legend->Draw();
    string savePath = "../plots/FakeFactors/";
    string plotTitle = "FF_Comb_presel_mu_1p0n_18";
    string plotSufix = ".pdf";
    string save = savePath + plotTitle + plotSufix;
    c->SaveAs(save.c_str());

    cout << "plots saved!" << endl;
}