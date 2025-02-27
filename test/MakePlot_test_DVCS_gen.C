#include <iostream>
using namespace std;

void Global_setting();
void format_Line(TAttLine *line, Style_t style, Color_t color, Width_t width);
void format_Mark(TAttMarker *mark, Style_t style, Color_t color, Size_t msize);
void format_Legend(TLegend *legend);

void MakePlot_test_DVCS_gen(int version)
{
    // Make plots for comparison

    Global_setting();

    TFile *infile = TFile::Open(Form("test_DVCS_gen_Vz_version%d.root", version));

    TH1F *h_Vx = (TH1F*)infile->Get("h_Vx");
    TH1F *h_Vy = (TH1F*)infile->Get("h_Vy");
    TH1F *h_Vz = (TH1F*)infile->Get("h_Vz"); h_Vz->Rebin(5);

    TH1F *h_Vx_ELossCorr = (TH1F*)infile->Get("h_Vx_ELossCorr");
    TH1F *h_Vy_ELossCorr = (TH1F*)infile->Get("h_Vy_ELossCorr");
    TH1F *h_Vz_ELossCorr = (TH1F*)infile->Get("h_Vz_ELossCorr"); h_Vz_ELossCorr->Rebin(5);

    TH1F *h_Vx_computeE = (TH1F*)infile->Get("h_Vx_computeE");
    TH1F *h_Vy_computeE = (TH1F*)infile->Get("h_Vy_computeE");
    TH1F *h_Vz_computeE = (TH1F*)infile->Get("h_Vz_computeE"); h_Vz_computeE->Rebin(5);
    TH2F *hh_eth_ephi_computeE = (TH2F*)infile->Get("hh_data_HMSangle_computeE");

    TH1F *h_Vx_HMScut = (TH1F*)infile->Get("h_Vx_HMScut");
    TH1F *h_Vy_HMScut = (TH1F*)infile->Get("h_Vy_HMScut");
    TH1F *h_Vz_HMScut = (TH1F*)infile->Get("h_Vz_HMScut"); h_Vz_HMScut->Rebin(5);
    TH2F *hh_eth_ephi_HMScut = (TH2F*)infile->Get("hh_data_HMSangle_HMScut");

    TH1F *h_Vx_HMScut_NPScut = (TH1F*)infile->Get("h_Vx_HMScut_NPScut");
    TH1F *h_Vy_HMScut_NPScut = (TH1F*)infile->Get("h_Vy_HMScut_NPScut");
    TH1F *h_Vz_HMScut_NPScut = (TH1F*)infile->Get("h_Vz_HMScut_NPScut"); h_Vz_HMScut_NPScut->Rebin(5);
    TH2F *hh_eth_ephi_HMScut_NPScut = (TH2F*)infile->Get("hh_data_HMSangle_HMScut_NPScut");

    h_Vz->Scale(1/h_Vz->Integral());
    h_Vz_ELossCorr->Scale(1/h_Vz_ELossCorr->Integral());
    h_Vz_computeE->Scale(1/h_Vz_computeE->Integral());
    h_Vz_HMScut->Scale(1/h_Vz_HMScut->Integral());
    h_Vz_HMScut_NPScut->Scale(1/h_Vz_HMScut_NPScut->Integral());

    TLegend *leg_z = new TLegend(0.25, 0.60, 0.55, 0.90);
    leg_z->SetHeader("#bf{Generated vertex Z}");
    leg_z->AddEntry(h_Vz, "No cuts", "l");
    leg_z->AddEntry(h_Vz_ELossCorr, "After energy loss corrections (brfore vertex)", "l");
    leg_z->AddEntry(h_Vz_computeE, "After generating scattered electrons", "l");
    leg_z->AddEntry(h_Vz_HMScut, "Acceptance cut on HMS side");
    leg_z->AddEntry(h_Vz_HMScut_NPScut, "Acceptance cut on HMS and calorimeter side");

    TCanvas *c = new TCanvas("c", "", 1000, 1000);
    c->SetLogz();
    h_Vz->GetYaxis()->SetRangeUser(0.99*h_Vz->GetMaximum(), 1.021*h_Vz->GetMaximum());

    format_Line(h_Vz, 1, kBlack, 3);
    h_Vz->Draw("hist");
    format_Line(h_Vz_ELossCorr, 1, kRed, 3);
    h_Vz_ELossCorr->Draw("hist same");
    format_Line(h_Vz_computeE, 1, kGreen+2, 3);
    h_Vz_computeE->Draw("hist same");
    format_Line(h_Vz_HMScut, 1, kBlue, 3);
    h_Vz_HMScut->Draw("hist same");
    format_Line(h_Vz_HMScut_NPScut, 1, kViolet, 3);
    h_Vz_HMScut_NPScut->Draw("hist same");
    format_Legend(leg_z);
    leg_z->Draw();
    if(version == 2) c->SaveAs("Vz_with_only_rasters.png");
    if(version == 3) c->SaveAs("Vz_with_rasters_beamoffset.png");
}

// Useful function for drawing
void Global_setting() // global settings
{
    TGaxis::SetMaxDigits(3);
    gStyle->SetOptStat(0);
    gStyle->SetPadLeftMargin(0.13);
    gStyle->SetPadRightMargin(0.13);
    gStyle->SetLineWidth(3);
    gStyle->SetFrameLineWidth(3);
}

void format_Line(TAttLine *line, Style_t style, Color_t color, Width_t width) // Format of Line
{
    line->SetLineStyle(style);
    line->SetLineColor(color);
    line->SetLineWidth(width);
}

void format_Mark(TAttMarker *mark, Style_t style, Color_t color, Size_t msize) // Format of Marker
{
    mark->SetMarkerStyle(style);
    mark->SetMarkerColor(color);
    mark->SetMarkerSize(msize);
}

void format_Legend(TLegend *legend)  // Format of Legend
{
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetFillColor(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
}