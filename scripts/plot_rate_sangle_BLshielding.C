
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
	TFile *f5 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield4in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y4inDZ30inBS_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f5 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Dan/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_newCH_Dan_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e9_8deg_80uA_target_chamber_zhiwen_reduce_tree_rate_test.root");
	TFile *f4 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield5in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y5inDZ30inBS_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e9_8deg_80uA_targetonly_reduce_tree_rate.root");
	//TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e9_8deg_80uA_target_chamber_reduce_tree_rate_test.root");
	//TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_sangle/HallC_beamtest_bggen_LH2_pi0_8deg_filenum19880_newCh_reduce_tree_rate_gem.root");
	TFile *f6 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield5in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y5inDZ60inBS_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_sangle/HallC_beamtest_eAll_sangle_8deg_filenum100_newCH_8GeV_reduce_tree_rate_gem.root");
	//TFile *f7 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_1cmpb/HallC_beamtest_BeamOnTarget_0.997e11_8deg_80uA_newCH_25cmPb_reduce_tree_rate_gem.root");
	TFile *f7 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield7in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y7inDZ30inBS_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_Poly_sangle/HallC_beamtest_BeamOnTarget_1e11_8deg_80uA_newCH_poly_reduce_tree_rate_gem.root");
	//TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_0.979e11_8deg_80uA_newCH_1cmAl_reduce_tree_rate_gem.root");
	//TFile *f8 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_0.96e9_8deg_80uA_reduce_tree_rate_Q2L1.root");
	TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e11_8deg_80uA_newCH_reduce_tree_rate_gem_Etotcut.root");
	TFile *f18 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e11_8deg_80uA_newCH_reduce_tree_rate_gem.root");
	//TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_2.435e11_8deg_80uA_newCH_reduce_tree_rate_gem.root");
	//TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_6.005e11_8deg_80uA_newCH_reduce_tree_rate_gem.root");
	TFile *f9 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield5in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y5inDZ70inBS_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f10 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield7in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y7inDZ52inBS_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f10 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_0.81e10_8deg_80uA_nobeampipe_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f11 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield5in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y5inDZ60inBS_reduce_tree_rate_gem_Etotcut.root");
	TFile *f10 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield5in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y5inX4inDZ60inBS_reduce_tree_rate_gem_Etotcut.root");
	TFile *f11 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield5in_dz40in/HallC_beamtest_BeamOnTarget_1.01e10_8deg_80uA_Y5inDZ80inBS_reduce_tree_rate_gem_Etotcut.root");
	TFile *f12 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_config2/HallC_beamtest_BeamOnTarget_1e11_8deg_80uA_newCH_config2_reduce_tree_rate_gem_Etotcut.root");
	TFile *f13 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_config2_right/HallC_beamtest_BeamOnTarget_1e11_8deg_80uA_newCH_config2_right_reduce_tree_rate_gem_Etotcut.root");

	TTree *tree_pip = (TTree*) f5->Get("T");
	TTree *tree_pim = (TTree*) f4->Get("T");
	TTree *tree_pi0 = (TTree*) f6->Get("T"); //abs(phicut) <5 deg
	TTree *tree_eAll = (TTree*) f7->Get("T");
	TTree *tree_beam = (TTree*) f8->Get("T");
	TTree *tree_beam_Edep = (TTree*) f18->Get("T");
	TTree *tree_beam_more = (TTree*) f9->Get("T");
	TTree *tree_beam_1cm = (TTree*) f10->Get("T");
	TTree *tree_beam_15cm = (TTree*) f11->Get("T");
	TTree *tree_beam_config2 = (TTree*) f12->Get("T");
	TTree *tree_beam_config2r = (TTree*) f13->Get("T");
	const int rebinfac=2;
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
        tree_pip->Draw("ShowerSum>>shower_pip(4000,0,1000)","rate*(ShowerSum>4)","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("ShowerSum>>shower_pim(4000,0,1000)","rate*(ShowerSum>4)","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_pi0->Draw("ShowerSum>>shower_pi0(4000,0,1000)","rate*( ShowerSum>4)","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("ShowerSum>>shower_eAll(4000,0,1000)","rate*(ShowerSum>4)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("ShowerSum>>shower_beam(4000,0,1000)","rate*(ShowerSum>4)","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");
        /*tree_beam_more->Draw("ShowerSum>>shower_beam_more(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_more_hist = (TH1F*)gROOT->FindObject("shower_beam_more");
        tree_beam_1cm->Draw("ShowerSum>>shower_beam_1cm(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_1cm_hist = (TH1F*)gROOT->FindObject("shower_beam_1cm");
        tree_beam_15cm->Draw("ShowerSum>>shower_beam_15cm(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_15cm_hist = (TH1F*)gROOT->FindObject("shower_beam_15cm");
        tree_beam->Draw("ShowerSum>>shower_SC0_SC1_beam(4000,0,1000)","rate*(SC0_Eendsum>4 && SC1_Eendsum>4)","goff");
	TH1F *shower_beam_SC_cut_hist = (TH1F*)gROOT->FindObject("shower_SC0_SC1_beam");*/
        tree_pip->Draw("Npesum>>Npesum_pip(200,0,100)","rate*(ShowerSum>4)","goff");
	TH1F *Npesum_pip_hist = (TH1F*)gROOT->FindObject("Npesum_pip");
        tree_pim->Draw("Npesum>>Npesum_pim(200,0,100)","rate*(ShowerSum>4)","goff");
	TH1F *Npesum_pim_hist = (TH1F*)gROOT->FindObject("Npesum_pim");
        tree_pi0->Draw("Npesum>>Npesum_pi0(200,0,100)","rate*( ShowerSum>4)","goff");
	TH1F *Npesum_pi0_hist = (TH1F*)gROOT->FindObject("Npesum_pi0");
        tree_eAll->Draw("Npesum>>Npesum_eAll(200,0,100)","rate*(ShowerSum>4)","goff");
	TH1F *Npesum_eAll_hist = (TH1F*)gROOT->FindObject("Npesum_eAll");
        tree_beam->Draw("Npesum>>Npesum_beam(200,0,100)","rate*(ShowerSum>4)","goff");
	TH1F *Npesum_beam_hist = (TH1F*)gROOT->FindObject("Npesum_beam");
        tree_pip->Draw("GEM00_x>>GEM00_pip(256,-5.12,5.12)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_pip_hist = (TH1F*)gROOT->FindObject("GEM00_pip");
        tree_pim->Draw("GEM00_x>>GEM00_pim(256,-5.12,5.12)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_pim_hist = (TH1F*)gROOT->FindObject("GEM00_pim");
        tree_pi0->Draw("GEM00_x>>GEM00_pi0(256,-5.12,5.12)","rate*( GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_pi0_hist = (TH1F*)gROOT->FindObject("GEM00_pi0");
        tree_eAll->Draw("GEM00_x>>GEM00_eAll(256,-5.12,5.12)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_eAll_hist = (TH1F*)gROOT->FindObject("GEM00_eAll");
        tree_beam->Draw("GEM00_x>>GEM00_beam(256,-5.12,5.12)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_beam_hist = (TH1F*)gROOT->FindObject("GEM00_beam");
        tree_beam_Edep->Draw("GEM00_x>>GEM00_beam_Edep(256,-5.12,5.12)","rate*(GEM00_Edep>0)","goff");
	TH1F *GEM00_beam_Edep_hist = (TH1F*)gROOT->FindObject("GEM00_beam_Edep");
        tree_beam_more->Draw("GEM00_x>>GEM00_beam_more(256,-5.12,5.12)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_beam_more_hist = (TH1F*)gROOT->FindObject("GEM00_beam_more");
        tree_beam_1cm->Draw("GEM00_x>>GEM00_beam_1cm(256,-5.12,5.12)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_beam_1cm_hist = (TH1F*)gROOT->FindObject("GEM00_beam_1cm");
        tree_beam_15cm->Draw("GEM00_x>>GEM00_beam_15cm(256,-5.12,5.12)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_beam_15cm_hist = (TH1F*)gROOT->FindObject("GEM00_beam_15cm");
        tree_beam_config2->Draw("GEM00_x>>GEM00_beam_config2(256,-5.12,5.12)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_beam_config2_hist = (TH1F*)gROOT->FindObject("GEM00_beam_config2");
        tree_beam_config2r->Draw("GEM00_x>>GEM00_beam_config2r(256,-5.12,5.12)","rate*(GEM00_Edep>35e-6)","goff");
	TH1F *GEM00_beam_config2r_hist = (TH1F*)gROOT->FindObject("GEM00_beam_config2r");
        TH1F *eAll_clone_hist = (TH1F*)shower_eAll_hist->Clone(); 
        TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        shower_beam_hist->SetLineColor(6);
        shower_beam_hist->GetXaxis()->SetTitle("ShowerSum Eend (MeV)");
        shower_beam_hist->GetYaxis()->SetTitle("Rate (kHz)");
        shower_beam_hist->Scale(0.001);
        shower_beam_hist->Rebin(rebinfac);
        shower_beam_hist->GetYaxis()->SetRangeUser(1e-2,1e13);
        shower_beam_hist->Draw("HISt");
        double rate_proton= shower_beam_hist->Integral();
        shower_pip_hist->SetLineColor(2);
        shower_pip_hist->Scale(0.001);
        shower_pip_hist->Rebin(rebinfac);
        shower_pip_hist->Draw("same HIST");
        double rate_pip= shower_pip_hist->Integral();
        shower_pim_hist->SetLineColor(1);
        shower_pim_hist->Scale(0.001);
        shower_pim_hist->Rebin(rebinfac);
        shower_pim_hist->Draw("same HIST");
        double rate_pim= shower_pim_hist->Integral();
        shower_pi0_hist->SetLineColor(8);
        shower_pi0_hist->Scale(0.001);
        shower_pi0_hist->Rebin(rebinfac);
        shower_pi0_hist->Draw("same HIST");
        double rate_pi0= shower_pi0_hist->Integral();
        shower_eAll_hist->SetLineColor(4);
        shower_eAll_hist->Scale(0.001);
        shower_eAll_hist->Draw("same HIST");
        shower_eAll_hist->Rebin(rebinfac);
        double rate_eAll= shower_eAll_hist->Integral();
        eAll_clone_hist->Rebin(rebinfac);
        eAll_clone_hist->Scale(0.001);
	eAll_clone_hist->Add(shower_pip_hist);
	eAll_clone_hist->Add(shower_pim_hist);
	eAll_clone_hist->Add(shower_pi0_hist);
        eAll_clone_hist->SetLineColor(kYellow-3);
        //eAll_clone_hist->Draw("same HIST");
        double rate_eAll_clone= eAll_clone_hist->Integral();
        //shower_beam_SC_cut_hist->SetLineColor(7);
        //shower_beam_SC_cut_hist->Scale(0.001);
        //shower_beam_SC_cut_hist->Rebin(rebinfac);
       // shower_beam_SC_cut_hist->Draw("same HISt");
        /*shower_beam_more_hist->SetLineColor(3);
        shower_beam_more_hist->Scale(0.001);
        shower_beam_more_hist->Rebin(rebinfac);
        shower_beam_more_hist->Draw("same HISt");
        double rate_proton_more= shower_beam_more_hist->Integral();
        shower_beam_1cm_hist->SetLineColor(7);
        shower_beam_1cm_hist->Scale(0.001);
        shower_beam_1cm_hist->Rebin(rebinfac);
        shower_beam_1cm_hist->Draw("same HISt");
        double rate_proton_1cm= shower_beam_1cm_hist->Integral();
        shower_beam_15cm_hist->SetLineColor(kOrange+3);
        shower_beam_15cm_hist->Scale(0.001);
        shower_beam_15cm_hist->Rebin(rebinfac);
        shower_beam_15cm_hist->Draw("same HISt");
        double rate_proton_15cm= shower_beam_15cm_hist->Integral();*/
  TLegend *leg8 = new TLegend(0.45,0.6,0.8,0.88);
//  leg8->AddEntry(shower_beam_1cm_hist,Form("1 cm shielding; total rate=%f kHz",rate_proton_1cm),"l");
 // leg8->AddEntry(shower_beam_15cm_hist,Form("1.5 cm shielding; total rate=%f kHz",rate_proton_15cm),"l");
  leg8->AddEntry(shower_beam_hist,Form("no shielding; total rate=%f kHz",rate_proton),"l");
  leg8->AddEntry(shower_pip_hist,Form("2.5 cm shielding; total rate=%f kHz",rate_pip),"l");
  leg8->AddEntry(shower_eAll_hist,Form("3.5 cm shielding; total rate=%f kHz",rate_eAll),"l");
  leg8->AddEntry(shower_pi0_hist,Form("3.5 cm shielding+12x12 cm^{2}; total rate=%f kHz",rate_pi0),"l");
  leg8->AddEntry(shower_pim_hist,Form("4.5 cm shielding; total rate=%f kHz",rate_pim),"l");
//  leg8->AddEntry(shower_beam_more_hist,Form("5.5cm shielding; total rate=%f kHz",rate_proton_more),"l");
//  leg8->AddEntry(shower_beam_SC_cut_hist,"BeamOnTarget with SC cut; ","l");
//  leg8->AddEntry(eAll_clone_hist,Form("eAll+pions; total rate=%f kHz",rate_eAll_clone),"l");
  leg8->SetTextSize(0.03);
  leg8->SetBorderSize(0);
  leg8->SetFillColor(0);
  leg8->Draw("text same");
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        Npesum_beam_hist->SetLineColor(6);
        Npesum_beam_hist->GetXaxis()->SetTitle("Npe");
        Npesum_beam_hist->GetYaxis()->SetTitle("Rate (kHz)");
        Npesum_beam_hist->Scale(0.001);
        Npesum_beam_hist->GetYaxis()->SetRangeUser(1e-2,1e9);
        Npesum_beam_hist->Draw("HIST");
        Npesum_pip_hist->SetLineColor(2);
        Npesum_pip_hist->Scale(0.001);
        Npesum_pip_hist->Draw("same HIST");
        Npesum_pim_hist->SetLineColor(1);
        Npesum_pim_hist->Scale(0.001);
        Npesum_pim_hist->Draw("same HIST");
        Npesum_pi0_hist->SetLineColor(8);
        Npesum_pi0_hist->Scale(0.001);
        Npesum_pi0_hist->Draw("same HIST");
        Npesum_eAll_hist->SetLineColor(4);
        Npesum_eAll_hist->Scale(0.001);
        Npesum_eAll_hist->Draw("same HIST");
  TLegend *leg7 = new TLegend(0.45,0.6,0.8,0.88);
  leg7->AddEntry(Npesum_eAll_hist,Form("from eAll"),"l");
  leg7->AddEntry(Npesum_pim_hist,Form("from bggen #pi^{-}"),"l");
  leg7->AddEntry(Npesum_pip_hist,Form("from bggen #pi^{+}"),"l");
  leg7->AddEntry(Npesum_pi0_hist,Form("from bggen #pi^{0}"),"l");
  leg7->AddEntry(Npesum_beam_hist,Form("from BeamOnTarget LH2"),"l");
  leg7->SetTextSize(0.03);
  leg7->SetBorderSize(0);
  leg7->SetFillColor(0);
  leg7->Draw("text same");
	c[2] = new TCanvas("c[2]","c[2]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        GEM00_beam_hist->SetLineColor(6);
        GEM00_beam_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
        GEM00_beam_hist->GetYaxis()->SetTitle("Rate (kHz)");
        GEM00_beam_hist->Scale(0.001);
        GEM00_beam_hist->GetYaxis()->SetRangeUser(1e-2,1e9);
        GEM00_beam_hist->Draw("HIST");
        double rate_proton_gem= GEM00_beam_hist->Integral();
        GEM00_pip_hist->SetLineColor(2);
        GEM00_pip_hist->Scale(0.001);
        GEM00_pip_hist->Draw("same HIST");
        double rate_pip_gem= GEM00_pip_hist->Integral();
        GEM00_pim_hist->SetLineColor(1);
        GEM00_pim_hist->Scale(0.001);
        GEM00_pim_hist->Draw("same HIST");
        double rate_pim_gem= GEM00_pim_hist->Integral();
        GEM00_pi0_hist->SetLineColor(30);
        GEM00_pi0_hist->Scale(0.001);
        GEM00_pi0_hist->Draw("same HIST");
        double rate_pi0_gem= GEM00_pi0_hist->Integral();
        GEM00_eAll_hist->SetLineColor(4);
        GEM00_eAll_hist->Scale(0.001);
        GEM00_eAll_hist->Draw("same HIST");
        double rate_eAll_gem= GEM00_eAll_hist->Integral();
        GEM00_beam_more_hist->SetLineColor(3);
        GEM00_beam_more_hist->Scale(0.001);
        GEM00_beam_more_hist->Draw("same HIST");
        double rate_proton_gem_more= GEM00_beam_more_hist->Integral();
        GEM00_beam_1cm_hist->SetLineColor(7);
        GEM00_beam_1cm_hist->Scale(0.001);
        GEM00_beam_1cm_hist->Draw("same HIST");
        double rate_proton_gem_1cm= GEM00_beam_1cm_hist->Integral();
        GEM00_beam_15cm_hist->SetLineColor(kOrange-3);
        GEM00_beam_15cm_hist->Scale(0.001);
        GEM00_beam_15cm_hist->Draw("same HIST");
        double rate_proton_gem_15cm= GEM00_beam_15cm_hist->Integral();
        GEM00_beam_Edep_hist->SetLineColor(kMagenta-2);
        GEM00_beam_Edep_hist->Scale(0.001);
        GEM00_beam_Edep_hist->Draw("same HIST");
        double rate_proton_gem_Edep= GEM00_beam_Edep_hist->Integral();
        GEM00_beam_config2_hist->SetLineColor(13);
        GEM00_beam_config2_hist->Scale(0.001);
        GEM00_beam_config2_hist->Draw("same HIST");
        double rate_proton_gem_config2= GEM00_beam_config2_hist->Integral();
        GEM00_beam_config2r_hist->SetLineColor(28);
        GEM00_beam_config2r_hist->Scale(0.001);
        GEM00_beam_config2r_hist->Draw("same HIST");
        double rate_proton_gem_config2r= GEM00_beam_config2r_hist->Integral();
  TLegend *leg9 = new TLegend(0.45,0.6,0.8,0.88);
  leg9->AddEntry(GEM00_beam_hist,Form("no shielding 35e^{-6} cut; total rate=%f kHz",rate_proton_gem),"l");
  leg9->AddEntry(GEM00_beam_config2_hist,Form("no shielding config2 35e^{-6} cut; total rate=%f kHz",rate_proton_gem_config2),"l");
  leg9->AddEntry(GEM00_beam_config2r_hist,Form("no shielding config2r 35e^{-6} cut; total rate=%f kHz",rate_proton_gem_config2r),"l");
  leg9->AddEntry(GEM00_beam_Edep_hist,Form("no shielding ; total rate=%f kHz",rate_proton_gem_Edep),"l");
  leg9->AddEntry(GEM00_pip_hist,Form("2 in Pb 4x30 in^{2}; total rate=%f kHz",rate_pip_gem),"l");
  leg9->AddEntry(GEM00_pim_hist,Form("2 in Pb 5x30 in^{2}; total rate=%f kHz",rate_pim_gem),"l");
  leg9->AddEntry(GEM00_eAll_hist,Form("2 in Pb 7x30 in^{2}; total rate=%f kHz",rate_eAll_gem),"l");
  leg9->AddEntry(GEM00_pi0_hist,Form("2 in Pb 5x60 in^{2}; total rate=%f kHz",rate_pi0_gem),"l");
  leg9->AddEntry(GEM00_beam_1cm_hist,Form("4 in Pb  5x60 in^{2}; total rate=%f kHz",rate_proton_gem_1cm),"l");
  leg9->AddEntry(GEM00_beam_more_hist,Form("2 in Pb 5x70 in^{2}; total rate=%f kHz",rate_proton_gem_more),"l");
  leg9->AddEntry(GEM00_beam_15cm_hist,Form("2 in Pb 5x80 in^{2}; total rate=%f kHz",rate_proton_gem_15cm),"l");
  leg9->SetTextSize(0.03);
  leg9->SetBorderSize(0);
  leg9->SetFillColor(0);
  leg9->Draw("text same");
	for(int a=0;a<3;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_comparison_BLshielding.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
