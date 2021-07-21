void processRatioPlot()
{
   map<string, string> process = {
       {"data", "Data"},
       {"Top", "Top"},
       {"other_bkg", "Others_Bkg"},
       {"Ztt", "Ztt"},
       {"signal_SM", "Signal_SM"},
   };

   map<string, string> regions = {
       {"SR", "SR"},
       {"anti_tau", "anti_tau"},
       {"W_lh", "WCR"},
       {"W_lh_anti_tau", "WCR_anti_tau"},
       {"qcd_lh", "QCDCR"},
       {"qcd_lh_anti_tau", "QCDCR_anti_tau"},
   };

   gStyle->SetOptStat(0);

   for (auto &reg : regions)
   {
      for (auto &pro : process)
      {
         auto c1 = new TCanvas("c1", "");
         TLegend *legend = new TLegend(0.7, 0.7, 0.8, 0.9);
         gStyle->SetLegendTextSize(0.02);
         legend->SetBorderSize(0);

         string fileName = "../output/FFHistograms.root";
         string BfileName = "../dataset/RawData.root";
         TFile *f = TFile::Open(fileName.c_str());
         TFile *fB = TFile::Open(BfileName.c_str());

         //string hName = "hist_" + pro.first + "_" + reg.first;
         string hName = pro.first + "_presel_mu_1p0n_" + reg.first + "_18";
         TH1D *h = (TH1D *)f->Get(hName.c_str());
         h->SetMarkerStyle(20);
         h->SetMarkerColor(kBlack);
         h->GetXaxis()->SetTitle("Hadronic Tau p_{T} [GeV]");
         h->GetYaxis()->SetTitle("Events / 10 GeV");
         string myleg = "my " + pro.first;
         legend->AddEntry(h, myleg.c_str(), "P");
         cout << "my hist:" << h->GetEntries() << endl;
         string BhName = "Raw_" + pro.second + "_" + reg.second + "_Presel_1p0n";
         TH1D *hB = (TH1D *)fB->Get(BhName.c_str());
         string boomsleg = "BOOM's " + pro.first;
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
         string plotName = "../plots/ProcessRatioPlots/" + pro.first + "_" + reg.first + "_ratio.pdf";
         c1->SaveAs(plotName.c_str());
      }
   }
}
