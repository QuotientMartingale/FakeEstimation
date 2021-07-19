void FakeTemplate()
{
    vector<string> process = {
        "Top",
        "other_bkg",
        "Ztt",
        "signal_SM",
    };
    vector<string> regions = {
        "W_lh",
        "W_lh_anti_tau",
        "qcd_lh",
        "qcd_lh_anti_tau",
    };
    vector<int> colors= {
        kOrange+1,
        kMagenta,
        kAzure+1,
        kRed,
    };

    gROOT->SetStyle("ATLAS");
    gStyle->SetErrorX(0.5);

    TFile *f = TFile::Open("../output/histograms.root", "read");
    TH1D *hdata;
    for (auto &reg : regions)
    {     
        string data = "data_presel_mu_1p0n_" + reg + "_18";
        hdata = (TH1D *)f->Get(data.c_str());
        hdata->SetMarkerColor(kBlack);
        hdata->GetXaxis()->SetTitle("Leading Tau p_{T} [GeV]");
        
        TH1D *h[process.size()];
        THStack *hs = new THStack("mcStack", "");
        TLegend *legend = new TLegend(0.75, 0.7, 0.9, 0.9);
        gStyle->SetLegendTextSize(0.02);
        legend->SetBorderSize(0);
        for (int i = 0; i < process.size(); ++i)
        {
            string mc = process.at(i) + "_presel_mu_1p0n_" + reg + "_18";
            h[i] = (TH1D *)f->Get(mc.c_str());
            h[i]->SetFillColor(colors[i]);
            h[i]->SetFillStyle(1001); //实心颜色填充
            h[i]->SetLineStyle(1);
            h[i]->SetLineWidth(0);
            hs->Add(h[i]);
            legend->AddEntry(h[i], (process.at(i)).c_str(), "F");
        }

        TCanvas *c = new TCanvas("", "", 900, 700);
        float scale = 0.001;
        hdata->Scale(scale);
        hdata->Draw("P");
        hs->Draw("hist same");
        legend->Draw();
        string savePath = "../plots/FakeTemplates/";
        string plotTitle = reg;
        string plotSufix = ".pdf";
        string save = savePath + plotTitle + plotSufix;
        c->SaveAs(save.c_str());
        cout << "plots saved!" << endl;
    }
}