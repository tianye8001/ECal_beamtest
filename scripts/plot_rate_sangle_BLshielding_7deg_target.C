
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
	TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_5uA_4SCsurvey_7deg_r20m_dummy_shielding/HallC_beamtest_BeamOnTarget_8.855e7_7degsurvey_5uA_4SC_r20m_dummy_shielding_reduce_tree_rate_gem1_Etotalcut_40uA_Q2100MeV.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_5uA_4SCsurvey_7deg_r20m_3He_shielding/HallC_beamtest_BeamOnTarget_9.89e7_7degsurvey_5uA_4SC_r20m_3He_shielding_reduce_tree_rate_gem1_Etotalcut_40uA_Q2100MeV.root");
	//TFile *f9 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_5uA_4SCsurvey_7deg_r20m_carbon_shielding/HallC_beamtest_BeamOnTarget_8.61e7_7degsurvey_5uA_4SC_r20m_cfoil_shielding_reduce_tree_rate_gem1_Etotalcut_40uA_Q2100MeV.root");
	TFile *f9 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_5uA_4SCsurvey_7deg_r20m_dummyCarbon_shielding/HallC_beamtest_BeamOnTarget_9.435e7_7degsurvey_5uA_4SC_r20m_dummyCarbon_shielding_reduce_tree_rate_gem1_Etotalcut_40uA_Q2100MeV.root");

	TTree *tree_He = (TTree*) f4->Get("T");
	TTree *tree_Al = (TTree*) f8->Get("T");
	TTree *tree_C = (TTree*) f9->Get("T");
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
        tree_Al->Draw("ShowerSum>>shower_pim(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_Al_hist = (TH1F*)gROOT->FindObject("shower_pim");
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
        tree_Al->Draw("Npesum>>Npesum_pim(100,0,100)","rate*(ShowerSum>0)","goff");
	TH1F *Npesum_Al_hist = (TH1F*)gROOT->FindObject("Npesum_pim");
        tree_pi0->Draw("Npesum>>Npesum_pi0(100,0,100)","rate*( ShowerSum>0)","goff");
	TH1F *Npesum_pi0_hist = (TH1F*)gROOT->FindObject("Npesum_pi0");
        tree_eAll->Draw("Npesum>>Npesum_eAll(100,0,100)","rate*(ShowerSum>0)","goff");
	TH1F *Npesum_eAll_hist = (TH1F*)gROOT->FindObject("Npesum_eAll");
        tree_beam->Draw("Npesum>>Npesum_beam(100,0,100)","rate*(ShowerSum>0)","goff");
	TH1F *Npesum_beam_hist = (TH1F*)gROOT->FindObject("Npesum_beam");
        tree_pip->Draw("GEM10_x>>GEM00_pip(256,-5.12,5.12)","rate","goff");
	TH1F *GEM00_pip_hist = (TH1F*)gROOT->FindObject("GEM00_pip");
        tree_Al->Draw("GEM10_x>>GEM00_pim(256,-5.12,5.12)","rate","goff");
	TH1F *GEM00_Al_hist = (TH1F*)gROOT->FindObject("GEM00_pim");
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
        tree_Al->Draw("SC_A_Eendsum>>SCA_Al(60,0,15)","rate*(SC_A_Eendsum>0)","goff");
	TH1F *SCA_Al_hist = (TH1F*)gROOT->FindObject("SCA_Al");
        tree_He->Draw("SC_A_Eendsum>>SCA_He(60,0,15)","rate*(SC_A_Eendsum>0)","goff");
	TH1F *SCA_He_hist = (TH1F*)gROOT->FindObject("SCA_He");
        tree_C->Draw("SC_A_Eendsum>>SCA_C(60,0,15)","rate*(SC_A_Eendsum>0)","goff");
	TH1F *SCA_C_hist = (TH1F*)gROOT->FindObject("SCA_C");


        tree_Al->Draw("SC_D_Eendsum>>SCD_Al(60,0,15)","rate*(SC_D_Eendsum>0)","goff");
	TH1F *SCD_Al_hist = (TH1F*)gROOT->FindObject("SCD_Al");
        tree_He->Draw("SC_D_Eendsum>>SCD_He(60,0,15)","rate*(SC_D_Eendsum>0)","goff");
	TH1F *SCD_He_hist = (TH1F*)gROOT->FindObject("SCD_He");
        tree_C->Draw("SC_D_Eendsum>>SCD_C(60,0,15)","rate*(SC_D_Eendsum>0)","goff");
	TH1F *SCD_C_hist = (TH1F*)gROOT->FindObject("SCD_C");

        tree_Al->Draw("SC_B_Eendsum>>SCB_Al(60,0,15)","rate*(SC_B_Eendsum>1.1)","goff");
	TH1F *SCB_Al_hist = (TH1F*)gROOT->FindObject("SCB_Al");
        tree_He->Draw("SC_B_Eendsum>>SCB_He(60,0,15)","rate*(SC_B_Eendsum>1.1)","goff");
	TH1F *SCB_He_hist = (TH1F*)gROOT->FindObject("SCB_He");
        tree_C->Draw("SC_B_Eendsum>>SCB_C(60,0,15)","rate*(SC_B_Eendsum>1.1)","goff");
	TH1F *SCB_C_hist = (TH1F*)gROOT->FindObject("SCB_C");

        tree_Al->Draw("LASPD_Eendsum>>LASPD_Al(60,0,15)","rate*(LASPD_Eendsum>0)","goff");
	TH1F *LASPD_Al_hist = (TH1F*)gROOT->FindObject("LASPD_Al");
        tree_He->Draw("LASPD_Eendsum>>LASPD_He(60,0,15)","rate*(LASPD_Eendsum>0)","goff");
	TH1F *LASPD_He_hist = (TH1F*)gROOT->FindObject("LASPD_He");
        tree_C->Draw("LASPD_Eendsum>>LASPD_C(60,0,15)","rate*(LASPD_Eendsum>0)","goff");
	TH1F *LASPD_C_hist = (TH1F*)gROOT->FindObject("LASPD_C");

        tree_Al->Draw("ShowerSum>>Shower_Al(100,0,50)","rate*(ShowerSum>0)","goff");
	TH1F *Shower_Al_hist = (TH1F*)gROOT->FindObject("Shower_Al");
        tree_He->Draw("ShowerSum>>Shower_He(100,0,50)","rate*(ShowerSum>0)","goff");
	TH1F *Shower_He_hist = (TH1F*)gROOT->FindObject("Shower_He");
        tree_C->Draw("ShowerSum>>Shower_C(100,0,50)","rate*(ShowerSum>0)","goff");
	TH1F *Shower_C_hist = (TH1F*)gROOT->FindObject("Shower_C");

        tree_Al->Draw("PreShSum>>PreShower_Al(60,0,30)","rate*(PreShSum>0)","goff");
	TH1F *PreShower_Al_hist = (TH1F*)gROOT->FindObject("PreShower_Al");
        tree_He->Draw("PreShSum>>PreShower_He(60,0,30)","rate*(PreShSum>0)","goff");
	TH1F *PreShower_He_hist = (TH1F*)gROOT->FindObject("PreShower_He");
        tree_C->Draw("PreShSum>>PreShower_C(60,0,30)","rate*(PreShSum>0)","goff");
	TH1F *PreShower_C_hist = (TH1F*)gROOT->FindObject("PreShower_C");



        TCanvas *c[10];
	c[2] = new TCanvas("c[2]","c[2]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        SCA_He_hist->SetLineColor(6);
        SCA_He_hist->GetXaxis()->SetTitle("SC_A_Edep (MeV)");
        SCA_He_hist->GetYaxis()->SetTitle("Rate (MHz)");
        SCA_He_hist->Scale(0.000001);
        SCA_He_hist->GetYaxis()->SetRangeUser(1e-5,1e3);
        SCA_He_hist->Draw("HIST");
        double rate_proton_SCA= SCA_He_hist->Integral();
        SCA_Al_hist->SetLineColor(1);
        SCA_Al_hist->Scale(0.000001);
        SCA_Al_hist->Draw("same HIST");
        double rate_Al_SCA= SCA_Al_hist->Integral();
        SCA_C_hist->SetLineColor(2);
        SCA_C_hist->Scale(0.000001);
        SCA_C_hist->Draw("same HIST");
        double rate_C_SCA= SCA_C_hist->Integral();
  TLegend *leg29 = new TLegend(0.3,0.6,0.8,0.88);
  leg29->AddEntry(SCA_He_hist,Form("2uA 3He target ; total rate=%f MHz",rate_proton_SCA),"l");
  leg29->AddEntry(SCA_Al_hist,Form("2uA dummy target; total rate=%f MHz",rate_Al_SCA),"l");
  leg29->AddEntry(SCA_C_hist,Form("5uA C-foil target; total rate=%f MHz",rate_C_SCA),"l");
  leg29->SetTextSize(0.03);
  leg29->SetBorderSize(0);
  leg29->SetFillColor(0);
  leg29->Draw("text same");
	c[3] = new TCanvas("c[3]","c[3]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        SCD_He_hist->SetLineColor(6);
        SCD_He_hist->GetXaxis()->SetTitle("SC_D_Edep (MeV)");
        SCD_He_hist->GetYaxis()->SetTitle("Rate (MHz)");
        SCD_He_hist->Scale(0.000001);
        SCD_He_hist->GetYaxis()->SetRangeUser(1e-5,5e3);
        SCD_He_hist->Draw("HIST");
        double rate_proton_SCD= SCD_He_hist->Integral();
        SCD_Al_hist->SetLineColor(1);
        SCD_Al_hist->Scale(0.000001);
        SCD_Al_hist->Draw("same HIST");
        double rate_Al_SCD= SCD_Al_hist->Integral();
        SCD_C_hist->SetLineColor(2);
        SCD_C_hist->Scale(0.000001);
        SCD_C_hist->Draw("same HIST");
        double rate_C_SCD= SCD_C_hist->Integral();
  TLegend *leg39 = new TLegend(0.3,0.6,0.8,0.88);
  leg39->AddEntry(SCD_He_hist,Form("2uA 3He target ; total rate=%f MHz",rate_proton_SCD),"l");
  leg39->AddEntry(SCD_Al_hist,Form("2uA dummy target ; total rate=%f MHz",rate_Al_SCD),"l");
  leg39->AddEntry(SCD_C_hist,Form("5uA C-foil target ; total rate=%f MHz",rate_C_SCD),"l");
  leg39->SetTextSize(0.03);
  leg39->SetBorderSize(0);
  leg39->SetFillColor(0);
  leg39->Draw("text same");
	c[4] = new TCanvas("c[4]","c[4]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        SCB_He_hist->SetLineColor(6);
        SCB_He_hist->GetXaxis()->SetTitle("SC_B_Edep (MeV)");
        SCB_He_hist->GetYaxis()->SetTitle("Rate (MHz)");
        SCB_He_hist->Scale(0.000001);
        SCB_He_hist->GetYaxis()->SetRangeUser(1e-5,1e3);
        SCB_He_hist->Draw("HIST");
        double rate_proton_SCB= SCB_He_hist->Integral();
        SCB_Al_hist->SetLineColor(1);
        SCB_Al_hist->Scale(0.000001);
        SCB_Al_hist->Draw("same HIST");
        double rate_Al_SCB= SCB_Al_hist->Integral();
        SCB_C_hist->SetLineColor(2);
        SCB_C_hist->Scale(0.000001);
        SCB_C_hist->Draw("same HIST");
        double rate_C_SCB= SCB_C_hist->Integral();
  TLegend *leg49 = new TLegend(0.3,0.6,0.8,0.88);
  leg49->AddEntry(SCB_He_hist,Form("2uA 3He target ; total rate=%f MHz",rate_proton_SCB),"l");
  leg49->AddEntry(SCB_Al_hist,Form("2uA dummy target; total rate=%f MHz",rate_Al_SCB),"l");
  leg49->AddEntry(SCB_C_hist,Form("5uA C-foil target; total rate=%f MHz",rate_C_SCB),"l");
  leg49->SetTextSize(0.03);
  leg49->SetBorderSize(0);
  leg49->SetFillColor(0);
  leg49->Draw("text same");
	c[5] = new TCanvas("c[5]","c[5]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        LASPD_He_hist->SetLineColor(6);
        LASPD_He_hist->GetXaxis()->SetTitle("LASPD_Edep (MeV)");
        LASPD_He_hist->GetYaxis()->SetTitle("Rate (MHz)");
        LASPD_He_hist->Scale(0.000001);
        LASPD_He_hist->GetYaxis()->SetRangeUser(1e-5,3e4);
        LASPD_He_hist->Draw("HIST");
        double rate_proton_LASPD= LASPD_He_hist->Integral();
        LASPD_Al_hist->SetLineColor(1);
        LASPD_Al_hist->Scale(0.000001);
        LASPD_Al_hist->Draw("same HIST");
        double rate_Al_LASPD= LASPD_Al_hist->Integral();
        LASPD_C_hist->SetLineColor(2);
        LASPD_C_hist->Scale(0.000001);
        LASPD_C_hist->Draw("same HIST");
        double rate_C_LASPD= LASPD_C_hist->Integral();
  TLegend *leg59 = new TLegend(0.3,0.6,0.8,0.88);
  leg59->AddEntry(LASPD_He_hist,Form("2uA 3He target ; total rate=%f MHz",rate_proton_LASPD),"l");
  leg59->AddEntry(LASPD_Al_hist,Form("2uA dummy target ; total rate=%f MHz",rate_Al_LASPD),"l");
  leg59->AddEntry(LASPD_C_hist,Form("5uA C-foil target ; total rate=%f MHz",rate_C_LASPD),"l");
  leg59->SetTextSize(0.03);
  leg59->SetBorderSize(0);
  leg59->SetFillColor(0);
  leg59->Draw("text same");
	c[6] = new TCanvas("c[6]","c[6]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        Shower_He_hist->SetLineColor(6);
        Shower_He_hist->GetXaxis()->SetTitle("ShowerSum_Edep (MeV)");
        Shower_He_hist->GetYaxis()->SetTitle("Rate (MHz)");
        Shower_He_hist->Scale(0.000001);
        Shower_He_hist->GetYaxis()->SetRangeUser(1e-5,1e3);
        Shower_He_hist->Draw("HIST");
        double rate_proton_Shower= Shower_He_hist->GetEntries();
        Shower_Al_hist->SetLineColor(1);
        Shower_Al_hist->Scale(0.000001);
        Shower_Al_hist->Draw("same HIST");
        double rate_Al_Shower= Shower_Al_hist->GetEntries();
        Shower_C_hist->SetLineColor(2);
        Shower_C_hist->Scale(0.000001);
        Shower_C_hist->Draw("same HIST");
        double rate_C_Shower= Shower_C_hist->GetEntries();
  TLegend *leg69 = new TLegend(0.3,0.6,0.8,0.88);
  leg69->AddEntry(Shower_He_hist,Form("2uA 3He target ; total rate=%f MHz",rate_proton_Shower),"l");
  leg69->AddEntry(Shower_Al_hist,Form("2uA dummy target ; total rate=%f MHz",rate_Al_Shower),"l");
  leg69->AddEntry(Shower_C_hist,Form("5uA C-foil target ; total rate=%f MHz",rate_C_Shower),"l");
  leg69->SetTextSize(0.03);
  leg69->SetBorderSize(0);
  leg69->SetFillColor(0);
  leg69->Draw("text same");
	c[7] = new TCanvas("c[7]","c[7]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        PreShower_He_hist->SetLineColor(6);
        PreShower_He_hist->GetXaxis()->SetTitle("PreShSum_Edep (MeV)");
        PreShower_He_hist->GetYaxis()->SetTitle("Rate (MHz)");
        PreShower_He_hist->Scale(0.000001);
        PreShower_He_hist->GetYaxis()->SetRangeUser(1e-5,1e3);
        PreShower_He_hist->Draw("HIST");
        double rate_proton_PreShower= PreShower_He_hist->GetEntries();
        PreShower_Al_hist->SetLineColor(1);
        PreShower_Al_hist->Scale(0.000001);
        PreShower_Al_hist->Draw("same HIST");
        double rate_Al_PreShower= PreShower_Al_hist->GetEntries();
        PreShower_C_hist->SetLineColor(2);
        PreShower_C_hist->Scale(0.000001);
        PreShower_C_hist->Draw("same HIST");
        double rate_C_PreShower= PreShower_C_hist->GetEntries();
  TLegend *leg79 = new TLegend(0.3,0.6,0.8,0.88);
  leg79->AddEntry(PreShower_He_hist,Form("2uA 3He target ; total rate=%f MHz",rate_proton_PreShower),"l");
  leg79->AddEntry(PreShower_Al_hist,Form("2uA dummy target ; total rate=%f MHz",rate_Al_PreShower),"l");
  leg79->AddEntry(PreShower_C_hist,Form("5uA C-foil target ; total rate=%f MHz",rate_C_PreShower),"l");
  leg79->SetTextSize(0.03);
  leg79->SetBorderSize(0);
  leg79->SetFillColor(0);
  leg79->Draw("text same");
	for(int a=2;a<8;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_comparison_photon_7deg_targets.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
