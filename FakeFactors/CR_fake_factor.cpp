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

void CR_fake_factor()
{
    vector<string> process = {
        "Top",
        "other_bkg",
        "Ztt",
        "signal_SM",
    };

    vector<int> colors = {
        kMagenta,
        kOrange + 1,
        kAzure + 1,
        kRed,
    };

    map<string, vector<double>> variable = {
        {"tau_0_p4.Pt", {20, 20, 220}},
        {"tau_1_p4.Pt", {20, 20, 220}},
        {"tau_1_p4.Eta", {50, -2.5, 2.5}},
        {"dphi_mettau", {35, 0, 3.5}},
        //{"ditau_dr", {25, 0, 2.5}},
        //{"mmc_mlm_m", {20, 0, 200}},
        //{"ditau_higgspt", {30, 90, 390}},
    };

    vector<string> campaign = {
        //"mc16a",
        //"mc16d",
        "mc16e",
    };

    vector<string> regions = {
        "W_lh",
        "qcd_lh",
    };

    gROOT->SetStyle("ATLAS");
    gStyle->SetErrorX(0.5);

    cout << "" << endl;
    TFile *f = TFile::Open("../output/histograms.root", "read");
    TH1D *FF[regions.size()];
    int n = 0;
    for (auto reg : regions)
    {
        string dataNum = "data_presel_mu_1p0n_" + reg + "_18";
        string mcNum = "mc_presel_mu_1p0n_" + reg + "_18";
        string dataDen = "data_presel_mu_1p0n_" + reg + "_anti_tau_18";
        string mcDen = "mc_presel_mu_1p0n_" + reg + "_anti_tau_18";
        TH1D *hdataNum = (TH1D *)f->Get(dataNum.c_str());
        TH1D *hdataDen = (TH1D *)f->Get(dataDen.c_str());
        TH1D *hmcNum = (TH1D *)f->Get(mcNum.c_str());
        TH1D *hmcDen = (TH1D *)f->Get(mcDen.c_str());
        cout << hdataNum->Integral() << " : " << hdataDen->Integral() << endl;
        cout << hmcNum->Integral() << " : " << hmcDen->Integral() << endl;
        hdataNum->Add(hmcNum, -1);
        hdataDen->Add(hmcDen, -1);
        cout << hdataNum->Integral() << " : " << hdataDen->Integral() << endl;
        double xbins[] = {30, 40, 500};
        int binNum = sizeof(xbins) / sizeof(xbins[0]) - 1;
        TH1D *hnumRebin = (TH1D *)hdataNum->Rebin(binNum, "hRebin", xbins);
        TH1D *hdenRebin = (TH1D *)hdataDen->Rebin(binNum, "hRebin", xbins);
        FF[n] = (TH1D *)hnumRebin->Clone();
        FF[n]->Divide(hdenRebin);
        cout << FF[n]->GetEntries() << endl;
        n = n + 1;
    }

    TFile *f1 = TFile::Open("../output/FakeFactors.root", "recreate");
    for (int i = 0; i < regions.size(); ++i)
    {
        string hFF = "FF_" + regions.at(i) + "_presel_mu_1p0n_18";
        FF[i]->SetName(hFF.c_str());
        FF[i]->Write();
    }
    TCanvas *c[regions.size()];
    for (int i = 0; i < regions.size(); ++i)
    {
        c[i] = new TCanvas("", "", 900, 700);
        FF[i]->Draw("E");
        //legend->Draw();
        string savePath = "../plots/FakeFactors/";
        string plotTitle = "FF_" + regions.at(i) + "_presel_mu_1p0n_18";
        string plotSufix = ".pdf";
        string save = savePath + plotTitle + plotSufix;
        c[i]->SaveAs(save.c_str());
    }

    cout << "plots saved!" << endl;
}