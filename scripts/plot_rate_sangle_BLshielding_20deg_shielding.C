
#include <iostream> 
#include <fstream>
#include <cmath> 
#include <math.h> 
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TPaveText.h>
#include <TText.h>
#include <TSystem.h>
#include <TArc.h>
#include <TLegend.h>

using namespace std;

void plot_rate_sangle_BLshielding(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	//TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_60uA_sangle_4SC_20deg_LD2_r20m_beamshield/HallC_beamtest_BeamOnTarget_5.828e8_60uA_4SCs_20deg_r20m_LD2_beamshield_reduce_tree_rate_gem1_Etotalcut_debug.root");
	//TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_60uA_sangle_4SC_20deg_LD2_r20m_shielding/HallC_beamtest_BeamOnTarget_1.9918e9_60uA_4SCs_20deg_r20m_LD2_shielding_reduce_tree_rate_gem1_Etotalcut_Q2cut100MeV.root");
	//TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_60uA_sangle_4SC_20deg_LD2_r20m/HallC_beamtest_BeamOnTarget_9.945e8_60uA_4SCs_20deg_r20m_LD2_reduce_tree_rate_gem1_Etotalcut_Q2cut100MeV.root");
	//TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_60uA_sangle_4SC_20deg_LD2_r20m_shielding_30x30x1cm3/HallC_beamtest_BeamOnTarget_9.951e8_60uA_4SCs_20deg_r20m_LD2_shielding_30x30x1cm3_reduce_tree_rate_gem1_Etotalcut_Q2100MeV.root");
	//TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_60uA_sangle_4SC_20deg_LD2_r20m_shielding_30x30cm2_1inch/HallC_beamtest_BeamOnTarget_4.861e8_60uA_4SCs_20deg_r20m_LD2_shielding_30x30cm2_1inch_reduce_tree_rate_gem1_Etotalcut_debug.root");
	//TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_60uA_sangle_4SC_20deg_LD2_r20m_shielding_20x20x1cm3/HallC_beamtest_BeamOnTarget_9.479e8_60uA_4SCs_20deg_r20m_LD2_shielding_20x20x1cm3_reduce_tree_rate_gem1_Etotalcut_Q2cut100MeV.root");
	//TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_60uA_sangle_4SC_20deg_LD2_r20m_shielding_30x30cm2_1inch/HallC_beamtest_BeamOnTarget_1.9885e9_60uA_4SCs_20deg_r20m_LD2_shielding_30x30x2.54cm3_reduce_tree_rate_gem1_Etotalcut_40uA.root");
	TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_60uA_sangle_4SC_18deg_LD2_r20m_shielding_30x30x2.54cm3_poly/HallC_beamtest_BeamOnTarget_1.9974e9_60uA_4SCs_18deg_r20m_LD2_shielding_30x30x2.54cm3_reduce_tree_rate_gem1_Etotalcut_40uA_Q2100MeV.root");
	//TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_60uA_sangle_4SC_20deg_LD2_r20m_shielding_30x30cm2_1inch/HallC_beamtest_BeamOnTarget_1.9885e9_60uA_4SCs_20deg_r20m_LD2_shielding_30x30x2.54cm3_reduce_tree_rate_gem1_Etotalcut_40uA.root");
	TFile *f4 = new TFile("/cache/halla/solid/sim/solid_gemc/ec_pro_JLAB_VERSION_2.5/pass1/HallC_beamtest_BeamOnTarget_5.5906e9_60uA_4SCs_18deg_r20m_LD2_30x30x2.54cm3_polyshielding.root");

	TTree *tree_pim = (TTree*) f4->Get("T");
	TTree *tree_beam = (TTree*) f8->Get("T");
	const int rebinfac=4;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
        /*tree_pip->Draw("ShowerSum>>shower_pip(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("ShowerSum>>shower_pim(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_pi0->Draw("ShowerSum>>shower_pi0(4000,0,1000)","rate*( ShowerSum>0)","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("ShowerSum>>shower_eAll(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("ShowerSum>>shower_beam(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");
        tree_beam_more->Draw("ShowerSum>>shower_beam_more(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_more_hist = (TH1F*)gROOT->FindObject("shower_beam_more");
        tree_beam_1cm->Draw("ShowerSum>>shower_beam_1cm(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_1cm_hist = (TH1F*)gROOT->FindObject("shower_beam_1cm");
        tree_beam_15cm->Draw("ShowerSum>>shower_beam_15cm(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_15cm_hist = (TH1F*)gROOT->FindObject("shower_beam_15cm");
        //tree_beam->Draw("ShowerSum>>shower_SC0_SC1_beam(4000,0,1000)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	//TH1F *shower_beam_SC_cut_hist = (TH1F*)gROOT->FindObject("shower_SC0_SC1_beam");
        tree_pip->Draw("Npesum>>Npesum_pip(100,0,100)","rate*(ShowerSum>0)","goff");
	TH1F *Npesum_pip_hist = (TH1F*)gROOT->FindObject("Npesum_pip");
        tree_pim->Draw("Npesum>>Npesum_pim(100,0,100)","rate*(ShowerSum>0)","goff");
	TH1F *Npesum_pim_hist = (TH1F*)gROOT->FindObject("Npesum_pim");
        tree_pi0->Draw("Npesum>>Npesum_pi0(100,0,100)","rate*( ShowerSum>0)","goff");
	TH1F *Npesum_pi0_hist = (TH1F*)gROOT->FindObject("Npesum_pi0");
        tree_eAll->Draw("Npesum>>Npesum_eAll(100,0,100)","rate*(ShowerSum>0)","goff");
	TH1F *Npesum_eAll_hist = (TH1F*)gROOT->FindObject("Npesum_eAll");
        tree_beam->Draw("Npesum>>Npesum_beam(100,0,100)","rate*(ShowerSum>0)","goff");
	TH1F *Npesum_beam_hist = (TH1F*)gROOT->FindObject("Npesum_beam");
        tree_pip->Draw("GEM10_x>>GEM00_pip(256,-5.12,5.12)","rate","goff");
	TH1F *GEM00_pip_hist = (TH1F*)gROOT->FindObject("GEM00_pip");
        tree_pim->Draw("GEM10_x>>GEM00_pim(256,-5.12,5.12)","rate","goff");
	TH1F *GEM00_pim_hist = (TH1F*)gROOT->FindObject("GEM00_pim");
        tree_pi0->Draw("GEM10_x>>GEM00_pi0(256,-5.12,5.12)","rate","goff");
	TH1F *GEM00_pi0_hist = (TH1F*)gROOT->FindObject("GEM00_pi0");
        tree_eAll->Draw("GEM10_x>>GEM00_eAll(256,-5.12,5.12)","rate","goff");
	TH1F *GEM00_eAll_hist = (TH1F*)gROOT->FindObject("GEM00_eAll");
        tree_beam->Draw("GEM10_x>>GEM00_beam(256,-5.12,5.12)","rate","goff");
	TH1F *GEM00_beam_hist = (TH1F*)gROOT->FindObject("GEM00_beam");
        tree_beam_more->Draw("GEM10_x>>GEM00_beam_more(256,-5.12,5.12)","rate","goff");
	TH1F *GEM00_beam_more_hist = (TH1F*)gROOT->FindObject("GEM00_beam_more");
        tree_beam_1cm->Draw("GEM10_x>>GEM00_beam_1cm(256,-5.12,5.12)","rate","goff");
	TH1F *GEM00_beam_1cm_hist = (TH1F*)gROOT->FindObject("GEM00_beam_1cm");
        tree_beam_15cm->Draw("GEM10_x>>GEM00_beam_15cm(256,-5.12,5.12)","rate","goff");
	TH1F *GEM00_beam_15cm_hist = (TH1F*)gROOT->FindObject("GEM00_beam_15cm");*/
        tree_pim->Draw("GEM00_x>>GEM00_pim(256,6,6)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_pim_hist = (TH1F*)gROOT->FindObject("GEM00_pim");
        tree_beam->Draw("GEM00_x>>GEM00_beam(256,6,6)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_beam_hist = (TH1F*)gROOT->FindObject("GEM00_beam");
        tree_pim->Draw("GEM10_x>>GEM10_pim(256,6,6)","rate*(GEM10_Edep>35e-6)","goff");
	TH1F *GEM10_pim_hist = (TH1F*)gROOT->FindObject("GEM10_pim");
        tree_beam->Draw("GEM10_x>>GEM10_beam(256,6,6)","rate*(GEM10_Edep>35e-6)","goff");
	TH1F *GEM10_beam_hist = (TH1F*)gROOT->FindObject("GEM10_beam");
        tree_pim->Draw("SC_A_Eendsum>>SCA_pim(1000,0,100)","rate*(SC_A_Eendsum>0.99)","goff");
	TH1F *SCA_pim_hist = (TH1F*)gROOT->FindObject("SCA_pim");
        tree_beam->Draw("SC_A_Eendsum>>SCA_beam(1000,0,100)","rate*(SC_A_Eendsum>0.99)","goff");
	TH1F *SCA_beam_hist = (TH1F*)gROOT->FindObject("SCA_beam");
        tree_pim->Draw("SC_D_Eendsum>>SCD_pim(1000,0,100)","rate*(SC_D_Eendsum>1.75)","goff");
	TH1F *SCD_pim_hist = (TH1F*)gROOT->FindObject("SCD_pim");
        tree_beam->Draw("SC_D_Eendsum>>SCD_beam(1000,0,100)","rate*(SC_D_Eendsum>1.75)","goff");
	TH1F *SCD_beam_hist = (TH1F*)gROOT->FindObject("SCD_beam");
        tree_pim->Draw("SC_B_Eendsum>>SCB_pim(1000,0,100)","rate*(SC_B_Eendsum>0.99)","goff");
	TH1F *SCB_pim_hist = (TH1F*)gROOT->FindObject("SCB_pim");
        tree_beam->Draw("SC_B_Eendsum>>SCB_beam(1000,0,100)","rate*(SC_B_Eendsum>0.99)","goff");
	TH1F *SCB_beam_hist = (TH1F*)gROOT->FindObject("SCB_beam");
        tree_pim->Draw("LASPD_Eendsum>>LASPD_pim(1000,0,100)","rate*(LASPD_Eendsum>1.75)","goff");
	TH1F *LASPD_pim_hist = (TH1F*)gROOT->FindObject("LASPD_pim");
        tree_beam->Draw("LASPD_Eendsum>>LASPD_beam(1000,0,100)","rate*(LASPD_Eendsum>1.75)","goff");
	TH1F *LASPD_beam_hist = (TH1F*)gROOT->FindObject("LASPD_beam");
        tree_pim->Draw("ShowerSum>>Shower_pim(1000,0,2000)","rate*(ShowerSum>20)","goff");
	TH1F *Shower_pim_hist = (TH1F*)gROOT->FindObject("Shower_pim");
        tree_beam->Draw("ShowerSum>>Shower_beam(1000,0,2000)","rate*(ShowerSum>20)","goff");
	TH1F *Shower_beam_hist = (TH1F*)gROOT->FindObject("Shower_beam");
        tree_pim->Draw("PreShSum>>PreShower_pim(500,0,150)","rate*(PreShSum>1.75)","goff");
	TH1F *PreShower_pim_hist = (TH1F*)gROOT->FindObject("PreShower_pim");
        tree_beam->Draw("PreShSum>>PreShower_beam(500,0,150)","rate*(PreShSum>1.75)","goff");
	TH1F *PreShower_beam_hist = (TH1F*)gROOT->FindObject("PreShower_beam");
        TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        GEM00_beam_hist->SetLineColor(6);
        GEM00_beam_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
        GEM00_beam_hist->GetYaxis()->SetTitle("Rate (MHz/cm^{2})");
        GEM00_beam_hist->Scale(0.00000001);
        GEM00_beam_hist->GetYaxis()->SetRangeUser(1e-5,1e1);
        GEM00_beam_hist->Draw("HIST");
        double rate_proton_gem= GEM00_beam_hist->Integral();
        GEM00_pim_hist->SetLineColor(1);
        GEM00_pim_hist->Scale(0.00000001);
        GEM00_pim_hist->Draw("same HIST");
        double rate_pim_gem= GEM00_pim_hist->Integral();
  TLegend *leg9 = new TLegend(0.15,0.6,0.6,0.88);
  leg9->AddEntry(GEM00_beam_hist,Form("60uA LD2 target ; total rate=%f MHz/cm^{2}",rate_proton_gem),"l");
  leg9->AddEntry(GEM00_pim_hist,Form("60uA LD2 target shielding; total rate=%f MHz/cm^{2}",rate_pim_gem),"l");
  leg9->SetTextSize(0.03);
  leg9->SetBorderSize(0);
  leg9->SetFillColor(0);
  leg9->Draw("text same");
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        GEM10_beam_hist->SetLineColor(6);
        GEM10_beam_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
        GEM10_beam_hist->GetYaxis()->SetTitle("Rate (MHz/cm^{2})");
        GEM10_beam_hist->Scale(0.00000001);
        GEM10_beam_hist->GetYaxis()->SetRangeUser(1e-5,1e1);
        GEM10_beam_hist->Draw("HIST");
        double rate_proton_gem10= GEM10_beam_hist->Integral();
        GEM10_pim_hist->SetLineColor(1);
        GEM10_pim_hist->Scale(0.00000001);
        GEM10_pim_hist->Draw("same HIST");
        double rate_pim_gem10= GEM10_pim_hist->Integral();
  TLegend *leg19 = new TLegend(0.15,0.6,0.6,0.88);
  leg19->AddEntry(GEM10_beam_hist,Form("60uA LD2 target no shielding; total rate=%f MHz/cm^{2}",rate_proton_gem10),"l");
  leg19->AddEntry(GEM10_pim_hist,Form("60uA LD2 target 7-feet beamline shielding; total rate=%f MHz/cm^{2}",rate_pim_gem10),"l");
  leg19->SetTextSize(0.03);
  leg19->SetBorderSize(0);
  leg19->SetFillColor(0);
  leg19->Draw("text same");
	c[2] = new TCanvas("c[2]","c[2]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        SCA_beam_hist->SetLineColor(6);
        SCA_beam_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
        SCA_beam_hist->GetYaxis()->SetTitle("Rate (MHz/cm^{2})");
        SCA_beam_hist->Scale(0.000001);
        SCA_beam_hist->GetYaxis()->SetRangeUser(1e-5,1e1);
        SCA_beam_hist->Draw("HIST");
        double rate_proton_SCA= SCA_beam_hist->Integral();
        SCA_pim_hist->SetLineColor(1);
        SCA_pim_hist->Scale(0.000001);
        SCA_pim_hist->Draw("same HIST");
        double rate_pim_SCA= SCA_pim_hist->Integral();
  TLegend *leg29 = new TLegend(0.15,0.6,0.6,0.88);
  leg29->AddEntry(SCA_beam_hist,Form("60uA LD2 target no shielding; total rate=%f MHz/cm^{2}",rate_proton_SCA),"l");
  leg29->AddEntry(SCA_pim_hist,Form("60uA LD2 target 7-feet beamline shielding; total rate=%f MHz/cm^{2}",rate_pim_SCA),"l");
  leg29->SetTextSize(0.03);
  leg29->SetBorderSize(0);
  leg29->SetFillColor(0);
  leg29->Draw("text same");
	c[3] = new TCanvas("c[3]","c[3]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        SCD_beam_hist->SetLineColor(6);
        SCD_beam_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
        SCD_beam_hist->GetYaxis()->SetTitle("Rate (MHz/cm^{2})");
        SCD_beam_hist->Scale(0.000001);
        SCD_beam_hist->GetYaxis()->SetRangeUser(1e-5,1e1);
        SCD_beam_hist->Draw("HIST");
        double rate_proton_SCD= SCD_beam_hist->Integral();
        SCD_pim_hist->SetLineColor(1);
        SCD_pim_hist->Scale(0.000001);
        SCD_pim_hist->Draw("same HIST");
        double rate_pim_SCD= SCD_pim_hist->Integral();
  TLegend *leg39 = new TLegend(0.15,0.6,0.6,0.88);
  leg39->AddEntry(SCD_beam_hist,Form("60uA LD2 target no shielding; total rate=%f MHz/cm^{2}",rate_proton_SCD),"l");
  leg39->AddEntry(SCD_pim_hist,Form("60uA LD2 target 7-feet beamline shielding; total rate=%f MHz/cm^{2}",rate_pim_SCD),"l");
  leg39->SetTextSize(0.03);
  leg39->SetBorderSize(0);
  leg39->SetFillColor(0);
  leg39->Draw("text same");
	c[4] = new TCanvas("c[4]","c[4]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        SCB_beam_hist->SetLineColor(6);
        SCB_beam_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
        SCB_beam_hist->GetYaxis()->SetTitle("Rate (MHz/cm^{2})");
        SCB_beam_hist->Scale(0.000001);
        SCB_beam_hist->GetYaxis()->SetRangeUser(1e-5,1e1);
        SCB_beam_hist->Draw("HIST");
        double rate_proton_SCB= SCB_beam_hist->Integral();
        SCB_pim_hist->SetLineColor(1);
        SCB_pim_hist->Scale(0.000001);
        SCB_pim_hist->Draw("same HIST");
        double rate_pim_SCB= SCB_pim_hist->Integral();
  TLegend *leg49 = new TLegend(0.15,0.6,0.6,0.88);
  leg49->AddEntry(SCB_beam_hist,Form("60uA LD2 target no shielding; total rate=%f MHz/cm^{2}",rate_proton_SCB),"l");
  leg49->AddEntry(SCB_pim_hist,Form("60uA LD2 target 7-feet beamline shielding; total rate=%f MHz/cm^{2}",rate_pim_SCB),"l");
  leg49->SetTextSize(0.03);
  leg49->SetBorderSize(0);
  leg49->SetFillColor(0);
  leg49->Draw("text same");
	c[5] = new TCanvas("c[5]","c[5]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        LASPD_beam_hist->SetLineColor(6);
        LASPD_beam_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
        LASPD_beam_hist->GetYaxis()->SetTitle("Rate (MHz/cm^{2})");
        LASPD_beam_hist->Scale(0.000001);
        LASPD_beam_hist->GetYaxis()->SetRangeUser(1e-5,1e1);
        LASPD_beam_hist->Draw("HIST");
        double rate_proton_LASPD= LASPD_beam_hist->Integral();
        LASPD_pim_hist->SetLineColor(1);
        LASPD_pim_hist->Scale(0.000001);
        LASPD_pim_hist->Draw("same HIST");
        double rate_pim_LASPD= LASPD_pim_hist->Integral();
  TLegend *leg59 = new TLegend(0.15,0.6,0.6,0.88);
  leg59->AddEntry(LASPD_beam_hist,Form("60uA LD2 target no shielding; total rate=%f MHz/cm^{2}",rate_proton_LASPD),"l");
  leg59->AddEntry(LASPD_pim_hist,Form("60uA LD2 target 7-feet beamline shielding; total rate=%f MHz/cm^{2}",rate_pim_LASPD),"l");
  leg59->SetTextSize(0.03);
  leg59->SetBorderSize(0);
  leg59->SetFillColor(0);
  leg59->Draw("text same");
	c[6] = new TCanvas("c[6]","c[6]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        Shower_beam_hist->SetLineColor(6);
        Shower_beam_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
        Shower_beam_hist->GetYaxis()->SetTitle("Rate (MHz/cm^{2})");
        Shower_beam_hist->Scale(0.000001);
        Shower_beam_hist->GetYaxis()->SetRangeUser(1e-5,1e1);
        Shower_beam_hist->Draw("HIST");
        double rate_proton_Shower= Shower_beam_hist->GetEntries();
        Shower_pim_hist->SetLineColor(1);
        Shower_pim_hist->Scale(0.000001);
        Shower_pim_hist->Draw("same HIST");
        double rate_pim_Shower= Shower_pim_hist->GetEntries();
  TLegend *leg69 = new TLegend(0.15,0.6,0.6,0.88);
  leg69->AddEntry(Shower_beam_hist,Form("60uA LD2 target no shielding; total rate=%f MHz/cm^{2}",rate_proton_Shower),"l");
  leg69->AddEntry(Shower_pim_hist,Form("60uA LD2 target 7-feet beamline shielding; total rate=%f MHz/cm^{2}",rate_pim_Shower),"l");
  leg69->SetTextSize(0.03);
  leg69->SetBorderSize(0);
  leg69->SetFillColor(0);
  leg69->Draw("text same");
	c[7] = new TCanvas("c[7]","c[7]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        PreShower_beam_hist->SetLineColor(6);
        PreShower_beam_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
        PreShower_beam_hist->GetYaxis()->SetTitle("Rate (MHz/cm^{2})");
        PreShower_beam_hist->Scale(0.000001);
        PreShower_beam_hist->GetYaxis()->SetRangeUser(1e-5,1e1);
        PreShower_beam_hist->Draw("HIST");
        double rate_proton_PreShower= PreShower_beam_hist->GetEntries();
        PreShower_pim_hist->SetLineColor(1);
        PreShower_pim_hist->Scale(0.000001);
        PreShower_pim_hist->Draw("same HIST");
        double rate_pim_PreShower= PreShower_pim_hist->GetEntries();
  TLegend *leg79 = new TLegend(0.15,0.6,0.6,0.88);
  leg79->AddEntry(PreShower_beam_hist,Form("60uA LD2 target no shielding; total rate=%f MHz/cm^{2}",rate_proton_PreShower),"l");
  leg79->AddEntry(PreShower_pim_hist,Form("60uA LD2 target 7-feet beamline shielding; total rate=%f MHz/cm^{2}",rate_pim_PreShower),"l");
  leg79->SetTextSize(0.03);
  leg79->SetBorderSize(0);
  leg79->SetFillColor(0);
  leg79->Draw("text same");
	for(int a=0;a<8;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_comparison_gem1shielding_20deg.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
