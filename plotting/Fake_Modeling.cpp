void Fake_Modeling()
{
    vector<string> regions = {
        //"W_lh",
        //"qcd_lh",
        "SR",
    };

    vector<string> process = {
        "Top",
        "other_bkg",
        "Fake",
        "Ztt",
        "signal_SM",
        
    };
    vector<int> colors = {
        kOrange + 1,
        kMagenta,
        kYellow,
        kAzure + 1,
        kRed,
    };

    vector<string> variables = {
        //"tau_0_Pt",
        "tau_1_Pt",
    };

    gROOT->SetStyle("ATLAS");
    gStyle->SetErrorX(0.5);

    TFile *f = TFile::Open("../output/CFFHistograms.root", "read");
    TFile *fp = TFile::Open("../output/FakePart.root", "read");
    TH1D *hdata;
    for (auto &var : variables)
    {
    for (auto &reg : regions)
    {
        TLegend *legend = new TLegend(0.7, 0.7, 0.8, 0.9);
        gStyle->SetLegendTextSize(0.02);
        legend->SetBorderSize(0);

        double xbins[] = {20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220};
        int binNum = sizeof(xbins) / sizeof(xbins[0]) - 1;

        string data = "data_presel_mu_1p0n_" + reg + "_18_" + var;
        hdata = (TH1D *)f->Get(data.c_str());
        TH1D *hdataRebin = (TH1D *)hdata->Rebin(binNum, "hdataRebin", xbins);
        hdataRebin->SetMarkerStyle(20); 
        hdataRebin->SetMarkerColor(kBlack);
        string xTitle = var + " [GeV]";
        hdataRebin->GetXaxis()->SetTitle(xTitle.c_str());
        hdataRebin->GetYaxis()->SetTitle("Events / 10 GeV");
        legend->AddEntry(hdataRebin, "data", "PL");

        TH1D *h[process.size()];
        TH1D *hRebin[process.size()];
        THStack *hs = new THStack("mcStack", "");
        for (int i = 0; i < process.size(); ++i)
        {
            string mc = process.at(i) + "_presel_mu_1p0n_" + reg + "_18_" + var;
            TFile *f1;
            if (process.at(i) == "Fake")
                f1 = fp;
            else
                f1 = f;
            h[i] = (TH1D *)f1->Get(mc.c_str());
            string hRname = "hRebin";
            hRebin[i] = (TH1D *)h[i]->Rebin(binNum, hRname.c_str(), xbins);
            hRebin[i]->SetFillColor(colors[i]);
            hRebin[i]->SetFillStyle(1001); //实心颜色填充
            hRebin[i]->SetLineStyle(1);
            hRebin[i]->SetLineWidth(0);
            //hRebin[i]->GetXaxis()->SetTitle("Hadronic Tau p_{T} [GeV]");
            //hRebin[i]->GetYaxis()->SetTitle("Events / 10 GeV");
            hs->Add(hRebin[i]);
            legend->AddEntry(hRebin[i], (process.at(i)).c_str(), "F");
        }

        TCanvas *c = new TCanvas("", "", 900, 700);
        c->SetTicks(0, 1);
        // hs->Draw("hist");
        // hdataRebin->Draw("PE same");
        auto rp = new TRatioPlot(hs, hdataRebin);
        rp->SetH1DrawOpt("hist");
        rp->SetH2DrawOpt("PE");
        //rp->GetLowerRefGraph()->SetMaximum(2);
        //rp->GetLowerRefGraph()->SetMinimum(-2);
        //rp->GetLowerRefYaxis()->SetTitle("Data / Pred.");
        rp->Draw();
        legend->Draw();
        string savePath = "../plots/FakeModelings/";
        string plotTitle = reg + "_" + var;
        string plotSufix = ".pdf";
        string save = savePath + plotTitle + plotSufix;
        c->SaveAs(save.c_str());
        cout << "plots saved!" << endl;
    }
    }
}