void FakeTemplate()
{
    vector<string> regions = {
        "SR",
        "anti_tau",
        "W_lh",
        "W_lh_anti_tau",
        "qcd_lh",
        "qcd_lh_anti_tau",
    };
    vector<string> process = {
        "Top",
        "other_bkg",
        "Ztt",
        "signal_SM",
    };
    vector<int> colors= {
        kOrange+1,
        kMagenta,
        kAzure+1,
        kRed,
    };

    gROOT->SetStyle("ATLAS");
    gStyle->SetErrorX(0.5);

    TFile *f = TFile::Open("../output/FFHistograms.root", "read");
    TH1D *hdata;
    for (auto &reg : regions)
    {     
        TLegend *legend = new TLegend(0.75, 0.7, 0.9, 0.9);
        gStyle->SetLegendTextSize(0.02);
        legend->SetBorderSize(0);

        double xbins[] = {20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220};
        int binNum = sizeof(xbins) / sizeof(xbins[0]) - 1;

        string data = "data_presel_mu_1p0n_" + reg + "_18";
        hdata = (TH1D *)f->Get(data.c_str());
        TH1D *hdataRebin = (TH1D *)hdata->Rebin(binNum, "hdataRebin", xbins);
        hdataRebin->SetMarkerStyle(20);
        hdataRebin->SetMarkerColor(kBlack);
        hdataRebin->GetXaxis()->SetTitle("Hadronic Tau p_{T} [GeV]");
        hdataRebin->GetYaxis()->SetTitle("Events / 10 GeV");
        legend->AddEntry(hdataRebin, "data", "PL");
        
        TH1D *h[process.size()];
        TH1D *hRebin[process.size()];
        THStack *hs = new THStack("mcStack", "");
        for (int i = 0; i < process.size(); ++i)
        {
            string mc = process.at(i) + "_presel_mu_1p0n_" + reg + "_18";
            h[i] = (TH1D *)f->Get(mc.c_str());
            string hRname = "hRebin";
            hRebin[i] = (TH1D *)h[i]->Rebin(binNum, hRname.c_str(), xbins);
            hRebin[i]->SetFillColor(colors[i]);
            hRebin[i]->SetFillStyle(1001); //实心颜色填充
            hRebin[i]->SetLineStyle(1);
            hRebin[i]->SetLineWidth(0);
            hs->Add(hRebin[i]);
            legend->AddEntry(hRebin[i], (process.at(i)).c_str(), "F");
        }

        TCanvas *c = new TCanvas("", "", 900, 700);
        hdataRebin->Draw("PE");
        hs->Draw("same");
        legend->Draw();
        string savePath = "../plots/FakeTemplates/";
        string plotTitle = reg;
        string plotSufix = ".pdf";
        string save = savePath + plotTitle + plotSufix;
        c->SaveAs(save.c_str());
        cout << "plots saved!" << endl;
    }
}