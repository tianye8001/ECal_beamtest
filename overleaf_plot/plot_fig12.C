
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

void plot_fig12(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f1 = new TFile("/w/halla-scshelf2102/solid/tianye/solid_simulation/solid/subsystem/ec/analysis/ecal_HallDpip_all_cluster_noTimeWindow_normalized_rate_2023_pipbkg_Eend_11GeV.root");
	TFile *f5 = new TFile("/w/halla-scshelf2102/solid/tianye/solid_simulation/solid/subsystem/ec/analysis/ecal_HallDpi0_all_cluster_noTimeWindow_normalized_rate_2023_pi0bkg_Eend_11GeV.root");
	TFile *f6 = new TFile("/w/halla-scshelf2102/solid/tianye/solid_simulation/solid/subsystem/ec/analysis/ecal_HallDpim_all_cluster_noTimeWindow_normalized_rate_2023_pimbkg_Eend_11GeV.root");
	TFile *f16 = new TFile("/w/halla-scshelf2102/solid/tianye/solid_simulation/solid/subsystem/ec/analysis/ecal_pimbkg_eAll_trigger_Eend_pL1800_11GeV_2023_Q2L2X30p1600.root");
	TFile *f17 = new TFile("/w/halla-scshelf2102/solid/tianye/solid_simulation/solid/subsystem/ec/analysis/ecal_BeamonTargetEM_all_cluster_noTimeWindow_normalized_rate_Eend.root");
	TFile *f2 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_18deg_LD_21m_30degcut_poly/HallC_beamtest_bggen_LH2_pip_18deg_LD_21m_30degcut_poly_filenum200730_reduce_tree_rate_40uA_Npe_resolution_new.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_18deg_LD_21m_30degcut_poly/HallC_beamtest_bggen_LH2_pim_18deg_LD_21m_30degcut_poly_filenum127210_reduce_tree_rate_40uA_Npe_resolution_new.root");
        TFile *f3 = new TFile("/volatile/halla/solid/tianye/ecal_beamtest_hallc/18deg/GEMROOTFILE_narrow/beamtest_level1_4778_4779_10uA_pedestal_7files.root");
	TFile *f13 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/ecal_beamtest_hallc/18deg/GEMROOTFILE_TS253_320ns/beamtest_level1_4770_4787.root");
	TFile *f23 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/ecal_beamtest_hallc/18deg/GEMROOTFILE_narrow/beamtest_level1_4780_1.root");
	TFile *f33 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/ecal_beamtest_hallc/18deg/GEMROOTFILE_T1020/beamtest_level1_4770_4787_nobeamtrip.root");
        TFile *f7 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_60uA_sangle_4SC_18deg_LD2_r20m_shielding_30x30x2.54cm3_EMonly/HallC_beamtest_beamOntarget_60uA_sangle_4SC_18deg_LD2_r20m_shielding_30x30x2.54cm3_EMonly_filenum9482_9.482e9_reduce_tree_rate_resolution_10MeV_Eend.root");
        TFile *f8 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_18deg_LD_21m_30degcut_poly/HallC_beamtest_bggen_LH2_pi0_18deg_LD_21m_30degcut_poly_filenum169930_reduce_tree_rate_40uA_Npe_resolution_new.root");
        TFile *f18 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_1520deg_LD2_20m_30x30x2.5cm3_poly_beamline/HallC_beamtest_eAll_1520deg_LD2_20m_30x30x2.5cm3_poly_beamline_filenum9991_reduce_tree_rate_resolution_10MeV_test.root");

	TTree *tree_SC1_electron = (TTree*) f2->Get("T");
	TTree *tree_pim = (TTree*) f4->Get("T");
	TTree *tree_BT = (TTree*) f7->Get("T");
	TTree *tree_data = (TTree*) f3->Get("T");
	TTree *tree_pi0 = (TTree*) f8->Get("T");
	TTree *tree_eAll = (TTree*) f18->Get("T");
	TTree *tree_data_45uA = (TTree*) f13->Get("T");
	TTree *tree_data_10uA = (TTree*) f23->Get("T");
	TTree *tree_data_accidental = (TTree*) f33->Get("T");
	const int rebinfac=2;
	const int rebinfac1=1;
        tree_SC1_electron->Draw("Shower_l>>shower_left(8000,0,8000)","rate*(Shower_l>0)","goff");
	TH1F *ShowerL_hist = (TH1F*)gROOT->FindObject("shower_left");
        tree_SC1_electron->Draw("Shower_r>>shower_right(8000,0,8000)","rate","goff");
	TH1F *ShowerR_hist = (TH1F*)gROOT->FindObject("shower_right");
        tree_SC1_electron->Draw("Shower_t>>shower_top(8000,0,8000)","rate","goff");
	TH1F *ShowerT_hist = (TH1F*)gROOT->FindObject("shower_top");
        tree_SC1_electron->Draw("Shower_t>>shower_sum(8000,0,8000)","rate*(Shower_t>0)","goff");
	TH1F *ShowerSum_hist = (TH1F*)gROOT->FindObject("shower_sum");
        tree_pim->Draw("Shower_t>>shower_sum_pim(8000,0,8000)","rate*(Shower_t>0)","goff");
	TH1F *ShowerSum_pim_hist = (TH1F*)gROOT->FindObject("shower_sum_pim");
        tree_BT->Draw("Shower_t>>shower_sum_BT(8000,0,8000)","rate*(Shower_t>0)","goff");
	TH1F *ShowerSum_BT_hist = (TH1F*)gROOT->FindObject("shower_sum_BT");
        tree_pi0->Draw("Shower_t>>shower_sum_pi0(8000,0,8000)","rate*(Shower_t>0)","goff");
	TH1F *ShowerSum_pi0_hist = (TH1F*)gROOT->FindObject("shower_sum_pi0");
        tree_eAll->Draw("Shower_t>>shower_sum_eAll(8000,0,8000)","rate*(Shower_t>0)","goff");
        //tree_eAll->Draw("ShowerSum>>shower_sum_eAll(8000,0,8000)","rate*(SC_D_Eendsum>2 && SC_A_Eendsum>1.26 && PreShSum>1.5 && PreShSum<7)","goff");
	TH1F *ShowerSum_eAll_hist = (TH1F*)gROOT->FindObject("shower_sum_eAll");
        TH1F * ShowerL_total_hist= new TH1F("ShowerL_total_hist","ShowerL_total_hist",8000,0,8000);
        TH1F * ShowerR_total_hist= new TH1F("ShowerR_total_hist","ShowerR_total_hist",8000,0,8000);
        TH1F * ShowerT_total_hist= new TH1F("ShowerT_total_hist","ShowerT_total_hist",8000,0,8000);
        TH1F * ShowerSum_total_hist= new TH1F("ShowerSum_total_hist","ShowerSum_total_hist",8000,0,8000);
        TH1F * ShowerL_total_solid_hist= new TH1F("ShowerL_total_solid_hist","ShowerL_total_solid_hist",8000,0,8000);
        TH1F * ShowerR_total_solid_hist= new TH1F("ShowerR_total_solid_hist","ShowerR_total_solid_hist",8000,0,8000);
        TH1F * ShowerT_total_solid_hist= new TH1F("ShowerT_total_solid_hist","ShowerT_total_solid_hist",8000,0,8000);
        TH1F * ShowerSum_total_solid_hist= new TH1F("ShowerSum_total_solid_hist","ShowerSum_total_solid_hist",8000,0,8000);
        TH1F * ShowerL_total_solid_nobkg_hist= new TH1F("ShowerL_total_solid_nobkg_hist","ShowerL_total_solid_nobkg_hist",8000,0,8000);
        TH1F * ShowerR_total_solid_nobkg_hist= new TH1F("ShowerR_total_solid_nobkg_hist","ShowerR_total_solid_nobkg_hist",8000,0,8000);
        TH1F * ShowerT_total_solid_nobkg_hist= new TH1F("ShowerT_total_solid_nobkg_hist","ShowerT_total_solid_nobkg_hist",8000,0,8000);
        TH1F * ShowerSum_total_solid_nobkg_hist= new TH1F("ShowerSum_total_solid_nobkg_hist","ShowerSum_total_solid_nobkg_hist",8000,0,8000);
        tree_data->Draw("Shower_l>>shower_left_data(8000,0,8000)","TrigType==4 && Shower_l/ShowerSum>0.8","goff");
	TH1F *ShowerL_data_hist = (TH1F*)gROOT->FindObject("shower_left_data");
        tree_data->Draw("Shower_r>>shower_right_data(8000,0,8000)","(TrigType==4 && Shower_r/ShowerSum>0.8)","goff");
	TH1F *ShowerR_data_hist = (TH1F*)gROOT->FindObject("shower_right_data");
        tree_data->Draw("Shower_t>>shower_top_data(8000,0,8000)","(TrigType==4 && Shower_t/ShowerSum>0.8)","goff");
	TH1F *ShowerT_data_hist = (TH1F*)gROOT->FindObject("shower_top_data");
       /* tree_data->Draw("1.124e-01*(Shower_t*0.9226+Shower_r*0.9525+Shower_l)>>shower_sum_data(8000,0,8000)","TrigType==4 && SC_A>2000 && SC_D>2000 && PreShSum>150 && PreShSum<600","goff");
	TH1F *ShowerSum_data_hist = (TH1F*)gROOT->FindObject("shower_sum_data");
        tree_data_45uA->Draw("0.056*(Shower_t*0.9226+Shower_r*0.9525+Shower_l)>>shower_sum_data_45uA(8000,0,8000)","TrigType==4&& SC_A>2000 && SC_D>2000 && PreShSum>150 && PreShSum<600","goff");*/
        //tree_data->Draw("1.124e-01*(Shower_t*0.9226+Shower_r*0.9525+Shower_l)>>shower_sum_data(8000,0,8000)","TrigType==4 ","goff");
        tree_data->Draw("(Shower_t)*0.1>>shower_sum_data(8000,0,8000)","0.18011240*(TrigType==8&& (Shower_t)>0)","goff");//4*(pow(2,6)+1)/1428.92235 
	TH1F *ShowerSum_data_hist = (TH1F*)gROOT->FindObject("shower_sum_data");
        //tree_data_45uA->Draw("0.069*(Shower_t)>>shower_sum_data_45uA(8000,0,8000)","5.91*(TrigType==253 && (Shower_t)>0) ","goff");//5.91*2.25
        tree_data_45uA->Draw("0.069*(Shower_t)>>shower_sum_data_45uA(8000,0,8000)","7.385*(TrigType==253 && (Shower_t+Shower_r+Shower_l)>0) ","goff");//320ns 4./(1692515*320.0e-9)
        //tree_data_45uA->Draw("0.075*(Shower_r)>>shower_sum_data_45uA(8000,0,8000)","5.91*(TrigType==253 && (Shower_r)>0) ","goff");//5.91*2.25
	TH1F *ShowerSum_data_45uA_hist = (TH1F*)gROOT->FindObject("shower_sum_data_45uA");
        tree_data_10uA->Draw("0.1*(Shower_t)>>shower_sum_data_10uA(8000,0,8000)","0.013836*(TrigType==8 && (Shower_t)>0) ","goff");//PS4==0; T=289.09728 //40uA
	TH1F *ShowerSum_data_10uA_hist = (TH1F*)gROOT->FindObject("shower_sum_data_10uA");
        //tree_data_accidental->Draw("0.1*(Shower_t)>>shower_sum_data_acc(8000,0,8000)","4.7292324*(Shower_t>0) ","goff");//10-20 bins: T=(40e-9*Ntotal_with (Shower_t+Shower_r+Shower_l)>0) //40uA
        tree_data_accidental->Draw("0.11*(Shower_t)>>shower_sum_data_acc(8000,0,8000)","10.7*((Shower_t+Shower_r+Shower_l)>0) ","goff");//10-20 bins: T=(40e-9*Ntotal_with (Shower_t+Shower_r+Shower_l)>0) //40uA
        //tree_data_accidental->Draw("0.1*(Shower_t)>>shower_sum_data_acc(8000,0,8000)","10.7*(Shower_t>0) ","goff");//10-20 bins: T=(40e-9*Ntotal_with (Shower_t+Shower_r+Shower_l)>0) //40uA
	TH1F *ShowerSum_data_accidental_hist = (TH1F*)gROOT->FindObject("shower_sum_data_acc");
        TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        ShowerSum_pim_hist->SetLineColor(2);
        ShowerSum_pim_hist->SetTitle("Shower_t ");
        ShowerSum_pim_hist->GetXaxis()->SetTitle("Shower_t Edep (MeV)");
        ShowerSum_pim_hist->GetYaxis()->SetTitle("Rate_Hz");
        ShowerSum_pim_hist->Scale(0.667);
       // ShowerR_hist->Rebin(rebinfac);
        ShowerSum_pim_hist->Rebin(rebinfac);
        ShowerSum_pim_hist->GetYaxis()->SetRangeUser(1e-2,1e8);
        ShowerSum_pim_hist->GetXaxis()->SetRangeUser(0,500);
        //ShowerSum_pim_hist->SetLineStyle(2);
        //ShowerSum_pim_hist->SetLineWidth(2);
        TH1F *ShowerSum_clone_hist = (TH1F*)ShowerSum_pim_hist->Clone();  
        ShowerSum_pim_hist->Draw("HIST");
        ShowerSum_hist->SetLineColor(28);
        ShowerSum_hist->Scale(0.667);
        ShowerSum_hist->Rebin(rebinfac);
      //  ShowerSum_hist->SetLineStyle(2);
      //  ShowerSum_hist->SetLineWidth(2);
        TH1F *ShowerSum_pip_clone_hist = (TH1F*)ShowerSum_hist->Clone();  
        //ShowerSum_hist->Draw("same HIST");
        ShowerSum_pi0_hist->SetLineColor(38);
        ShowerSum_pi0_hist->Scale(0.667);
        ShowerSum_pi0_hist->Rebin(rebinfac);
      //  ShowerSum_pi0_hist->SetLineStyle(2);
      //  ShowerSum_pi0_hist->SetLineWidth(2);
        TH1F *ShowerSum_pi0_clone_hist = (TH1F*)ShowerSum_pi0_hist->Clone();  
        ShowerSum_pi0_hist->Draw("same HIST");
        ShowerSum_eAll_hist->SetLineColor(4);
        ShowerSum_eAll_hist->Rebin(rebinfac);
      //  ShowerSum_eAll_hist->SetLineStyle(2);
      //  ShowerSum_eAll_hist->SetLineWidth(2);
        TH1F *ShowerSum_eAll_clone_hist = (TH1F*)ShowerSum_eAll_hist->Clone();  
      //  ShowerSum_eAll_hist->Draw("same HIST");
        ShowerSum_BT_hist->SetLineColor(1);
      //  ShowerSum_BT_hist->SetLineStyle(2);
      //  ShowerSum_BT_hist->SetLineWidth(2);
        ShowerSum_BT_hist->Rebin(rebinfac);
        TH1F *ShowerSum_BT_clone_hist = (TH1F*)ShowerSum_BT_hist->Clone();  
        ShowerSum_BT_hist->Draw("same HIST");
        TH1F *ShowerSum_pim_clone_hist = (TH1F*)ShowerSum_pim_hist->Clone();  
        TH1F *ShowerSum_pim_clone2_hist = (TH1F*)ShowerSum_pim_hist->Clone();  
        ShowerSum_pim_clone_hist->GetXaxis()->SetRangeUser(0,500);
        ShowerSum_pim_clone_hist->SetTitle("Shower_t ");
        ShowerSum_pim_clone_hist->GetXaxis()->SetTitle("Shower_t Edep (MeV)");
        ShowerSum_pim_clone_hist->GetYaxis()->SetTitle("Rate_Hz");
        ShowerSum_pim_clone_hist->Add(ShowerSum_hist,1);
        ShowerSum_pim_clone_hist->Add(ShowerSum_BT_hist,1);
        ShowerSum_pim_clone_hist->Add(ShowerSum_pi0_hist,1);
        ShowerSum_pim_clone_hist->Add(ShowerSum_eAll_hist,1);
        ShowerSum_pim_clone_hist->SetLineColor(6);
        ShowerSum_pim_clone_hist->Draw("same HIST");
        TH1F *ShowerSum_all_clone_hist = (TH1F*)ShowerSum_pim_clone_hist->Clone();  
        /*histo_edep_Sh_radius_pim_shower_11[0]->SetLineColor(1);
        histo_edep_Sh_radius_pim_shower_11[0]->Scale();
        histo_edep_Sh_radius_pim_shower_11[0]->Draw("same HIST");
        histo_edep_Sh_radius_pip_shower_11[0]->SetLineColor(2);
        histo_edep_Sh_radius_pip_shower_11[0]->Scale();
        histo_edep_Sh_radius_pip_shower_11[0]->Draw("same HIST");
        histo_edep_Sh_radius_pi0_shower_11[0]->SetLineColor(38);
        histo_edep_Sh_radius_pi0_shower_11[0]->Scale();
        histo_edep_Sh_radius_pi0_shower_11[0]->Draw("same HIST");
        histo_edep_Sh_radius_eAll_shower_11[0]->SetLineColor(4);
        histo_edep_Sh_radius_eAll_shower_11[0]->Scale();
        histo_edep_Sh_radius_eAll_shower_11[0]->Draw("same HIST");
        histo_edep_Sh_radius_BT_shower_11[0]->SetLineColor(28);
        histo_edep_Sh_radius_BT_shower_11[0]->Scale();
        histo_edep_Sh_radius_BT_shower_11[0]->Draw("same HIST");*/
        //histo_edep_Sh_radius_pim_nobkg_shower_11[0]->SetLineColor(2);
        //histo_edep_Sh_radius_pim_nobkg_shower_11[0]->Draw("same HIST");
        ShowerSum_data_hist->SetLineColor(kOrange-3);
        //ShowerSum_data_hist->Scale(65*10/164.398);
        ShowerSum_data_hist->Rebin(rebinfac);
        ShowerSum_data_hist->Draw("same HIST");
        ShowerSum_data_45uA_hist->SetLineColor(kGreen-3);
        //ShowerSum_data_45uA_hist->Scale(129/260.43340);
        ShowerSum_data_45uA_hist->Rebin(rebinfac);
        ShowerSum_data_45uA_hist->Draw("same HIST");
        ShowerSum_data_10uA_hist->SetLineColor(7);
        ShowerSum_data_10uA_hist->Rebin(rebinfac);
        ShowerSum_data_10uA_hist->Draw("same HIST");
        ShowerSum_data_accidental_hist->SetLineColor(9);
        ShowerSum_data_accidental_hist->Rebin(rebinfac);
        ShowerSum_data_accidental_hist->Draw("same HIST");
        /*ShowerR_data_hist->SetLineColor(kGreen-3);
        ShowerR_data_hist->Draw("same HIST");
        ShowerT_data_hist->SetLineColor(2);
        ShowerT_data_hist->Draw("same HIST");*/
        TLegend *leg21 = new TLegend(0.25,0.7,0.75,0.85);
       // leg21->AddEntry(ShowerSum_hist,"beam test simulation #pi^{+} ","l");
        leg21->AddEntry(ShowerSum_pim_hist,"beam test simulation #pi^{-} ","l");
        leg21->AddEntry(ShowerSum_pi0_hist,"beam test simulation #pi^{0} ","l");
       // leg21->AddEntry(ShowerSum_eAll_hist,"beam test simulation eAll ","l");
        leg21->AddEntry(ShowerSum_BT_hist,"beam test simulation BeamOnTarget EM ","l");
        leg21->AddEntry(ShowerSum_pim_clone_hist,"beam test simulation eAll+#pi^{0}+#pi^{+}+#pi^{-}+BeamOnTarget EM ","l");
        leg21->AddEntry(ShowerSum_data_hist,"beam test TS4=15mV run 4779 10uA*4 ","l");
        leg21->AddEntry(ShowerSum_data_10uA_hist,"beam test TS4=120mV run 4780 10uA*4 ","l");
        leg21->AddEntry(ShowerSum_data_45uA_hist,"beam test random triggered 10uA*4","l");
        leg21->AddEntry(ShowerSum_data_accidental_hist,"beam test accidental 10uA*4","l");
        //leg21->AddEntry(histo_edep_Sh_radius_pim_shower_11[0],"solid simulation #pi^{+} 1.1 m <R< 1.3 m","l");
        //leg21->AddEntry(histo_edep_Sh_radius_pip_shower_11[0],"solid simulation #pi^{-} 1.1 m <R< 1.3 m","l");
        //leg21->AddEntry(histo_edep_Sh_radius_pi0_shower_11[0],"solid simulation #pi^{0} 1.1 m <R< 1.3 m","l");
        //leg21->AddEntry(histo_edep_Sh_radius_eAll_shower_11[0],"solid simulation eAll 1.1 m <R< 1.3 m","l");
        //leg21->AddEntry(histo_edep_Sh_radius_BT_shower_11[0],"solid simulation BeamOnTarget 1.1 m <R< 1.3 m","l");
       // leg21->AddEntry(histo_edep_Sh_radius_pim_nobkg_shower_11[0],"no pileup solid simulation #pi^{-} ","l");
        leg21->SetTextSize(0.035);
        leg21->SetBorderSize(0);
        leg21->SetFillColor(0);
        leg21->Draw("text same");

}
