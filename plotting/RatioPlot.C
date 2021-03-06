void RatioPlot()
{
    vector<string> project = {
        //"FF",
        //"ISO",
        "rQCD",
    };
    for (auto &p : project)
    {
        if (p == "FF")
        {
            map<string, string> regions = {
                {"W_lh", "WCR"},
                {"qcd_lh", "QCDCR"},
            };

            gStyle->SetOptStat(0);

            for (auto &reg : regions)
            {
                auto c1 = new TCanvas("c1", "");
                c1->SetLogx();
                TLegend *legend = new TLegend(0.7, 0.7, 0.8, 0.9);
                gStyle->SetLegendTextSize(0.02);
                legend->SetBorderSize(0);

                string fileName = "../output/FakeFactors.root";
                //string fileName = "../mc_histograms.root";
                string BfileName = "../dataset/FFs_lephad.root";
                TFile *f = TFile::Open(fileName.c_str());
                TFile *fB = TFile::Open(BfileName.c_str());

                //string hName = "hist_" + pro.first + "_" + reg.first;
                string hName = "FF_" + reg.first + "_presel_mu_1p0n_18";
                TH1D *h = (TH1D *)f->Get(hName.c_str());
                h->SetMarkerStyle(20);
                h->SetMarkerColor(kBlack);
                h->GetXaxis()->SetTitle("Hadronic Tau p_{T} [GeV]");
                h->GetYaxis()->SetTitle("FF values");
                string myleg = "my FF";
                legend->AddEntry(h, myleg.c_str(), "P");
                cout << "my hist:" << h->GetEntries() << endl;
                string BhName = "FF_" + reg.second + "_Presel_All_Comb_SLT_1p0n";
                TH1D *hB = (TH1D *)fB->Get(BhName.c_str());
                hB->SetLineColor(kAzure + 1);
                string boomsleg = "BOOM's FF";
                legend->AddEntry(hB, boomsleg.c_str(), "L");
                cout << "boom hist:" << hB->GetEntries() << endl;

                auto rp = new TRatioPlot(h, hB);
                rp->SetH1DrawOpt("P");
                rp->SetH2DrawOpt("hist");
                //rp->GetLowerRefGraph()->SetMaximum(2);
                //rp->GetLowerRefGraph()->SetMinimum(-2);
                c1->SetTicks(0, 1);
                rp->Draw();
                //rp->GetLowYaxis()->SetNdivisions(505);
                legend->Draw();
                string plotName = "../plots/RatioPlots/FF_" + reg.first + "_ratio.pdf";
                c1->SaveAs(plotName.c_str());
            }
        }
    
        if (p == "Iso")
        {

            gStyle->SetOptStat(0);

            auto c1 = new TCanvas("c1", "");
            c1->SetLogx();
            TLegend *legend = new TLegend(0.7, 0.7, 0.8, 0.9);
            gStyle->SetLegendTextSize(0.02);
            legend->SetBorderSize(0);

            string fileName = "../output/IsoFactors.root";
            //string fileName = "../mc_histograms.root";
            string BfileName = "../dataset/IsoFactor_lephad.root";
            TFile *f = TFile::Open(fileName.c_str());
            TFile *fB = TFile::Open(BfileName.c_str());

            //string hName = "hist_" + pro.first + "_" + reg.first;
            string hName = "Iso_Factor_presel_mu_1p0n_18";
            TH1D *h = (TH1D *)f->Get(hName.c_str());
            h->SetMarkerStyle(20);
            h->SetMarkerColor(kBlack);
            h->GetXaxis()->SetTitle("Leptonic Tau p_{T} [GeV]");
            h->GetYaxis()->SetTitle("IsoFactor values");
            string myleg = "my IsoFactor";
            legend->AddEntry(h, myleg.c_str(), "P");
            cout << "my hist:" << h->GetEntries() << endl;
            string BhName = "Iso_Factor_Presel_All_Comb_SLT_1p0n";
            TH1D *hB = (TH1D *)fB->Get(BhName.c_str());
            hB->SetLineColor(kAzure + 1);
            string boomsleg = "BOOM's IsoFactor";
            legend->AddEntry(hB, boomsleg.c_str(), "L");
            cout << "boom hist:" << hB->GetEntries() << endl;

            auto rp = new TRatioPlot(h, hB);
            rp->SetH1DrawOpt("P");
            rp->SetH2DrawOpt("hist");
            //rp->GetLowerRefGraph()->SetMaximum(2);
            //rp->GetLowerRefGraph()->SetMinimum(-2);
            c1->SetTicks(0, 1);
            rp->Draw();
            //rp->GetLowYaxis()->SetNdivisions(505);
            legend->Draw();
            string plotName = "../plots/RatioPlots/Iso_ratio.pdf";
            c1->SaveAs(plotName.c_str());
        }

        if (p == "rQCD")
        {
            gStyle->SetOptStat(0);

            auto c1 = new TCanvas("c1", "");
            c1->SetLogx();
            TLegend *legend = new TLegend(0.7, 0.7, 0.8, 0.9);
            gStyle->SetLegendTextSize(0.02);
            legend->SetBorderSize(0);

            string fileName = "../output/rQCD.root";
            //string fileName = "../mc_histograms.root";
            string BfileName = "../dataset/RQCDs_lephad_1p0n.root";
            TFile *f = TFile::Open(fileName.c_str());
            TFile *fB = TFile::Open(BfileName.c_str());

            //string hName = "hist_" + pro.first + "_" + reg.first;
            string hName = "rQCD_presel_mu_1p0n_18";
            TH1D *h = (TH1D *)f->Get(hName.c_str());
            h->SetMarkerStyle(20);
            h->SetMarkerColor(kBlack);
            h->GetXaxis()->SetTitle("Hadronic Tau p_{T} [GeV]");
            h->GetYaxis()->SetTitle("rQCD values");
            string myleg = "my rQCD";
            legend->AddEntry(h, myleg.c_str(), "P");
            cout << "my hist:" << h->GetEntries() << endl;
            string BhName = "RQCD_Presel_All_Comb_SLT_1p0n";
            TH1D *hB = (TH1D *)fB->Get(BhName.c_str());
            hB->SetLineColor(kAzure + 1);
            string boomsleg = "BOOM's rQCD";
            legend->AddEntry(hB, boomsleg.c_str(), "L");
            cout << "boom hist:" << hB->GetEntries() << endl;

            auto rp = new TRatioPlot(h, hB);
            rp->SetH1DrawOpt("P");
            rp->SetH2DrawOpt("hist");
            //rp->GetLowerRefGraph()->SetMaximum(2);
            //rp->GetLowerRefGraph()->SetMinimum(-2);
            c1->SetTicks(0, 1);
            rp->Draw();
            //rp->GetLowYaxis()->SetNdivisions(505);
            legend->Draw();
            string plotName = "../plots/RatioPlots/rQCD_ratio.pdf";
            c1->SaveAs(plotName.c_str());
        }
    }
}
