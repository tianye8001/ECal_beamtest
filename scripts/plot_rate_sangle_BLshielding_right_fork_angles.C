
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

void plot_rate_sangle_BLshielding_right_fork(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f5 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork_BLshielding/HallC_beamtest_BeamOnTarget_9.91e8_8deg_80uA_target_right_step_BLshielding2x4x190_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f5 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Dan/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_newCH_Dan_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e9_8deg_80uA_target_chamber_zhiwen_reduce_tree_rate_test.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork_30deg/HallC_beamtest_BeamOnTarget_5e8_8deg_80uA_target_step_right_30deg_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e9_8deg_80uA_targetonly_reduce_tree_rate.root");
	//TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e9_8deg_80uA_target_chamber_reduce_tree_rate_test.root");
	//TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_sangle/HallC_beamtest_bggen_LH2_pi0_8deg_filenum19880_newCh_reduce_tree_rate_gem.root");
	TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork_BLshielding_GEM12cmAl/HallC_beamtest_BeamOnTarget_4.22e8_8deg_80uA_target_right_step_BLshielding2x4x190_12cmAl_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_sangle/HallC_beamtest_eAll_sangle_8deg_filenum100_newCH_8GeV_reduce_tree_rate_gem.root");
	//TFile *f7 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_1cmpb/HallC_beamtest_BeamOnTarget_0.997e11_8deg_80uA_newCH_25cmPb_reduce_tree_rate_gem.root");
	TFile *f7 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield7in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y7inDZ30inBS_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_Poly_sangle/HallC_beamtest_BeamOnTarget_1e11_8deg_80uA_newCH_poly_reduce_tree_rate_gem.root");
	//TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_0.979e11_8deg_80uA_newCH_1cmAl_reduce_tree_rate_gem.root");
	//TFile *f8 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_0.96e9_8deg_80uA_reduce_tree_rate_Q2L1.root");
	TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e11_8deg_80uA_newCH_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f18 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_TGonly/HallC_beamtest_BeamOnTarget_0.95e10_8deg_80uA_target_air_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f18 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork_20deg_2inVINYL_10x10/HallC_beamtest_BeamOnTarget_4.915e8_8deg_80uA_target_step_right_fork_20deg_2inVINYL_10x10_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f18 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork_20deg_3inpoly/HallC_beamtest_BeamOnTarget_4.63e8_8deg_80uA_target_step_right_fork_20deg_3inpoly_far_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f18 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork_20deg_2inpoly/HallC_beamtest_BeamOnTarget_4.99e8_8deg_80uA_target_step_right_fork_20deg_2inpoly_reduce_tree_rate_gem_Etotcut.root");
	TFile *f18 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork_20deg_3inVINYL/HallC_beamtest_BeamOnTarget_5e8_8deg_80uA_target_step_right_fork_20deg_3inVINYL_reduce_tree_rate_gem_Etotcut.root");
	
//TFile *f18 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e11_8deg_80uA_newCH_reduce_tree_rate_gem.root");
	//TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_2.435e11_8deg_80uA_newCH_reduce_tree_rate_gem.root");
	//TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_6.005e11_8deg_80uA_newCH_reduce_tree_rate_gem.root");
	//TFile *f9 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield5in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y5inDZ70inBS_reduce_tree_rate_gem_Etotcut.root");
	TFile *f9 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork_15deg/HallC_beamtest_BeamOnTarget_9.725e8_8deg_80uA_target_step_right_15deg_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f10 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield7in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y7inDZ52inBS_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f10 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_0.81e10_8deg_80uA_nobeampipe_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f11 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield5in/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_Y5inDZ60inBS_reduce_tree_rate_gem_Etotcut.root");
	TFile *f10 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork_20deg/HallC_beamtest_BeamOnTarget_8.485e8_8deg_80uA_target_step_right_20deg_reduce_tree_rate_gem_Etotcut.root");
	//TFile *f11 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_Bshield5in_dz40in/HallC_beamtest_BeamOnTarget_1.01e10_8deg_80uA_Y5inDZ80inBS_reduce_tree_rate_gem_Etotcut.root");
	TFile *f11 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork_25deg/HallC_beamtest_BeamOnTarget_5e8_8deg_80uA_target_step_right_fork_25deg_reduce_tree_rate_gem_Etotcut.root");
	TFile *f12 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_step_less/HallC_beamtest_BeamOnTarget_9.445e8_8deg_80uA_newCH_CAD_reduce_tree_rate_gem_Etotcut.root");
	TFile *f13 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_right_fork/HallC_beamtest_BeamOnTarget_9.8e8_8deg_80uA_target_step_right_reduce_tree_rate_gem_Etotcut.root");

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
	const int rebinfac=4;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
        //tree_pip->Draw("ShowerSum>>shower_pip(4000,0,1000)","rate*(ShowerSum>0)","goff");
	//TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("SC0_Eendsum>>shower_pim(4000,0,1000)","rate*(SC0_Eendsum>8)","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        /*tree_pi0->Draw("SC0_Eendsum>>shower_pi0(4000,0,1000)","rate*( SC0_Eendsum>0)","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("SC0_Eendsum>>shower_eAll(4000,0,1000)","rate*(SC0_Eendsum>0)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("SC0_Eendsum>>shower_beam(4000,0,1000)","rate*(SC0_Eendsum>0)","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");*/
        tree_beam_more->Draw("SC0_Eendsum>>shower_beam_more(4000,0,1000)","rate*(SC0_Eendsum>8)","goff");
	TH1F *shower_beam_more_hist = (TH1F*)gROOT->FindObject("shower_beam_more");
        tree_beam_1cm->Draw("SC0_Eendsum>>shower_beam_1cm(4000,0,1000)","rate*(SC0_Eendsum>8)","goff");
	TH1F *shower_beam_1cm_hist = (TH1F*)gROOT->FindObject("shower_beam_1cm");
        tree_beam_15cm->Draw("SC0_Eendsum>>shower_beam_15cm(4000,0,1000)","rate*(SC0_Eendsum>8)","goff");
	TH1F *shower_beam_15cm_hist = (TH1F*)gROOT->FindObject("shower_beam_15cm");
        tree_beam_config2r->Draw("SC0_Eendsum>>shower_beam_config2r(4000,0,1000)","rate*(SC0_Eendsum>8)","goff");
	TH1F *shower_beam_config2r_hist = (TH1F*)gROOT->FindObject("shower_beam_config2r");
        //tree_beam->Draw("ShowerSum>>shower_SC0_SC1_beam(4000,0,1000)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	//TH1F *shower_beam_SC_cut_hist = (TH1F*)gROOT->FindObject("shower_SC0_SC1_beam");
      /*  tree_pip->Draw("Npesum>>Npesum_pip(100,0,100)","rate*(ShowerSum>0)","goff");
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
        /*tree_pip->Draw("ShowerSum>>shower_pip(4000,0,1000)","rate*(ShowerSum>4)","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("ShowerSum>>shower_pim(4000,0,1000)","rate*(ShowerSum>4)","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_pi0->Draw("ShowerSum>>shower_pi0(4000,0,1000)","rate*( ShowerSum>4)","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("ShowerSum>>shower_eAll(4000,0,1000)","rate*(ShowerSum>4)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("ShowerSum>>shower_beam(4000,0,1000)","rate*(ShowerSum>4)","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");
        tree_beam_more->Draw("ShowerSum>>shower_beam_more(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_more_hist = (TH1F*)gROOT->FindObject("shower_beam_more");
        tree_beam_1cm->Draw("ShowerSum>>shower_beam_1cm(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_1cm_hist = (TH1F*)gROOT->FindObject("shower_beam_1cm");
        tree_beam_15cm->Draw("ShowerSum>>shower_beam_15cm(4000,0,1000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_15cm_hist = (TH1F*)gROOT->FindObject("shower_beam_15cm");
        tree_beam->Draw("ShowerSum>>shower_SC0_SC1_beam(4000,0,1000)","rate*(SC0_Eendsum>4 && SC1_Eendsum>4)","goff");
	TH1F *shower_beam_SC_cut_hist = (TH1F*)gROOT->FindObject("shower_SC0_SC1_beam");*/
        //tree_pip->Draw("Npesum>>Npesum_pip(200,0,100)","rate*(ShowerSum>4)","goff");
//	TH1F *Npesum_pip_hist = (TH1F*)gROOT->FindObject("Npesum_pip");
        tree_pim->Draw("SC1_Eendsum>>Npesum_pim(200,0,100)","rate*(SC1_Eendsum>8)","goff");
	TH1F *Npesum_pim_hist = (TH1F*)gROOT->FindObject("Npesum_pim");
        tree_beam_more->Draw("SC1_Eendsum>>Npesum_beam_more(200,0,100)","rate*(SC1_Eendsum>8)","goff");
	TH1F *Npesum_beam_more_hist = (TH1F*)gROOT->FindObject("Npesum_beam_more");
        tree_beam_config2r->Draw("SC1_Eendsum>>Npesum_beam_config2r(200,0,100)","rate*(SC1_Eendsum>8)","goff");
	TH1F *Npesum_beam_config2r_hist = (TH1F*)gROOT->FindObject("Npesum_beam_config2r");
        tree_beam_1cm->Draw("SC1_Eendsum>>Npesum_beam_1cm(200,0,100)","rate*(SC1_Eendsum>8)","goff");
	TH1F *Npesum_beam_1cm_hist = (TH1F*)gROOT->FindObject("Npesum_beam_1cm");
        tree_beam_15cm->Draw("SC1_Eendsum>>Npesum_beam_15cm(200,0,100)","rate*(SC1_Eendsum>8)","goff");
	TH1F *Npesum_beam_15cm_hist = (TH1F*)gROOT->FindObject("Npesum_beam_15cm");
  /*      tree_pi0->Draw("Npesum>>Npesum_pi0(200,0,100)","rate*( ShowerSum>4)","goff");
	TH1F *Npesum_pi0_hist = (TH1F*)gROOT->FindObject("Npesum_pi0");
        tree_eAll->Draw("Npesum>>Npesum_eAll(200,0,100)","rate*(ShowerSum>4)","goff");
	TH1F *Npesum_eAll_hist = (TH1F*)gROOT->FindObject("Npesum_eAll");
        tree_beam->Draw("Npesum>>Npesum_beam(200,0,100)","rate*(ShowerSum>4)","goff");
	TH1F *Npesum_beam_hist = (TH1F*)gROOT->FindObject("Npesum_beam");*/
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
        //TH1F *eAll_clone_hist = (TH1F*)shower_eAll_hist->Clone(); 
        TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        shower_beam_config2r_hist->SetLineColor(6);
        shower_beam_config2r_hist->GetXaxis()->SetTitle("SC0 Eend");
        shower_beam_config2r_hist->GetYaxis()->SetTitle("Rate (MHz)");
        shower_beam_config2r_hist->Scale(0.000001);
        shower_beam_config2r_hist->Rebin(rebinfac);
        shower_beam_config2r_hist->GetYaxis()->SetRangeUser(1e-2,1e13);
        shower_beam_config2r_hist->Draw("HIST");
        double rate_beam_config2r= shower_beam_config2r_hist->Integral();
        /*double rate_proton= shower_beam_hist->Integral();
        shower_pip_hist->SetLineColor(2);
        shower_pip_hist->Scale(0.000001);
        shower_pip_hist->Rebin(rebinfac);
        shower_pip_hist->Draw("same HIST");
        double rate_pip= shower_pip_hist->Integral();*/
        shower_pim_hist->SetLineColor(1);
        shower_pim_hist->Scale(0.000001);
        shower_pim_hist->Rebin(rebinfac);
        shower_pim_hist->Draw("same HIST");
        double rate_pim= shower_pim_hist->Integral();
        /*shower_pi0_hist->SetLineColor(8);
        shower_pi0_hist->Scale(0.000001);
        shower_pi0_hist->Rebin(rebinfac);
        shower_pi0_hist->Draw("same HIST");
        double rate_pi0= shower_pi0_hist->Integral();
        shower_eAll_hist->SetLineColor(4);
        shower_eAll_hist->Scale(0.000001);
        shower_eAll_hist->Draw("same HIST");
        shower_eAll_hist->Rebin(rebinfac);
        double rate_eAll= shower_eAll_hist->Integral();
        eAll_clone_hist->Rebin(rebinfac);
        eAll_clone_hist->Scale(0.000001);
	eAll_clone_hist->Add(shower_pip_hist);
	eAll_clone_hist->Add(shower_pim_hist);
	eAll_clone_hist->Add(shower_pi0_hist);
        eAll_clone_hist->SetLineColor(kYellow-3);
        //eAll_clone_hist->Draw("same HIST");
        double rate_eAll_clone= eAll_clone_hist->Integral();*/
        //shower_beam_SC_cut_hist->SetLineColor(7);
        //shower_beam_SC_cut_hist->Scale(0.000001);
        //shower_beam_SC_cut_hist->Rebin(rebinfac);
       // shower_beam_SC_cut_hist->Draw("same HISt");
        shower_beam_more_hist->SetLineColor(3);
        shower_beam_more_hist->Scale(0.000001);
        shower_beam_more_hist->Rebin(rebinfac);
        shower_beam_more_hist->Draw("same HISt");
        double rate_proton_more= shower_beam_more_hist->Integral();
        shower_beam_1cm_hist->SetLineColor(7);
        shower_beam_1cm_hist->Scale(0.000001);
        shower_beam_1cm_hist->Rebin(rebinfac);
        shower_beam_1cm_hist->Draw("same HISt");
        double rate_proton_1cm= shower_beam_1cm_hist->Integral();
        shower_beam_15cm_hist->SetLineColor(kOrange+3);
        shower_beam_15cm_hist->Scale(0.000001);
        shower_beam_15cm_hist->Rebin(rebinfac);
        shower_beam_15cm_hist->Draw("same HISt");
        double rate_proton_15cm= shower_beam_15cm_hist->Integral();
  TLegend *leg8 = new TLegend(0.45,0.6,0.8,0.88);
  leg8->AddEntry(shower_beam_config2r_hist,Form("no shielding 8 deg; total rate=%f MHz",rate_beam_config2r),"l");
  leg8->AddEntry(shower_beam_more_hist,Form("no shielding 15 deg; total rate=%f MHz",rate_proton_more),"l");
  leg8->AddEntry(shower_beam_1cm_hist,Form(" no shielding 20 deg; total rate=%f MHz",rate_proton_1cm),"l");
  leg8->AddEntry(shower_beam_15cm_hist,Form("noshielding 25 deg; total rate=%f MHz",rate_proton_15cm),"l");
  leg8->AddEntry(shower_pim_hist,Form("no shielding 30 deg; total rate=%f MHz",rate_pim),"l");
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
        Npesum_beam_config2r_hist->SetLineColor(6);
        Npesum_beam_config2r_hist->GetXaxis()->SetTitle("Npe");
        Npesum_beam_config2r_hist->GetYaxis()->SetTitle("Rate (kHz)");
        Npesum_beam_config2r_hist->Scale(0.000001);
        Npesum_beam_config2r_hist->GetYaxis()->SetRangeUser(1e-2,1e9);
        Npesum_beam_config2r_hist->Draw("HIST");
        double rate_SC1_config2r= Npesum_beam_config2r_hist->Integral();
        Npesum_beam_more_hist->SetLineColor(2);
        Npesum_beam_more_hist->Scale(0.000001);
        Npesum_beam_more_hist->Draw("same HIST");
        double rate_SC1_beam_more= Npesum_beam_more_hist->Integral();
        Npesum_pim_hist->SetLineColor(1);
        Npesum_pim_hist->Scale(0.000001);
        Npesum_pim_hist->Draw("same HIST");
        double rate_SC1_pim= Npesum_pim_hist->Integral();
        Npesum_beam_1cm_hist->SetLineColor(8);
        Npesum_beam_1cm_hist->Scale(0.000001);
        Npesum_beam_1cm_hist->Draw("same HIST");
        double rate_SC1_beam_1cm= Npesum_beam_1cm_hist->Integral();
        Npesum_beam_15cm_hist->SetLineColor(4);
        Npesum_beam_15cm_hist->Scale(0.000001);
        Npesum_beam_15cm_hist->Draw("same HIST");
        double rate_SC1_beam_15cm= Npesum_beam_15cm_hist->Integral();
  TLegend *leg7 = new TLegend(0.45,0.6,0.8,0.88);
  leg7->AddEntry(Npesum_beam_config2r_hist,Form("no shielding 8 deg; total rate=%f MHz",rate_SC1_config2r),"l");
  leg7->AddEntry(Npesum_beam_more_hist,Form("no shielding 15 deg; total rate=%f MHz",rate_SC1_beam_more),"l");
  leg7->AddEntry(Npesum_beam_1cm_hist,Form("no shielding 20 deg; total rate=%f MHz",rate_SC1_beam_1cm),"l");
  leg7->AddEntry(Npesum_beam_15cm_hist,Form("no shielding 25 deg; total rate=%f MHz",rate_SC1_beam_15cm),"l");
  leg7->AddEntry(Npesum_pim_hist,Form("no shielding 30 deg; total rate=%f MHz",rate_SC1_pim),"l");
  leg7->SetTextSize(0.03);
  leg7->SetBorderSize(0);
  leg7->SetFillColor(0);
  leg7->Draw("text same");
	c[2] = new TCanvas("c[2]","c[2]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
       // GEM00_beam_hist->SetLineColor(6);
       // GEM00_beam_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
      //  GEM00_beam_hist->GetYaxis()->SetTitle("Rate (MHz)");
      //  GEM00_beam_hist->Scale(0.000001);
      //  GEM00_beam_hist->GetYaxis()->SetRangeUser(1e-2,1e9);
      //  GEM00_beam_hist->Draw("HIST");
      //  double rate_proton_gem= GEM00_beam_hist->Integral();
        GEM00_beam_config2r_hist->SetLineColor(6);
        GEM00_beam_config2r_hist->GetXaxis()->SetTitle("GEM00_x (cm)");
        GEM00_beam_config2r_hist->GetYaxis()->SetTitle("Rate (MHz)");
        GEM00_beam_config2r_hist->Scale(0.000001);
        GEM00_beam_config2r_hist->GetYaxis()->SetRangeUser(1e-2,1e9);
        GEM00_beam_config2r_hist->Draw("same HIST");
        double rate_proton_gem_config2r= GEM00_beam_config2r_hist->Integral();
        GEM00_pip_hist->SetLineColor(4);
        GEM00_pip_hist->Scale(0.000001);
        //GEM00_pip_hist->Rebin(rebinfac);
        GEM00_pip_hist->Draw("same HIST");
        double rate_pip_gem= GEM00_pip_hist->Integral();
        GEM00_pim_hist->SetLineColor(1);
        GEM00_pim_hist->Scale(0.000001);
        GEM00_pim_hist->Rebin(rebinfac);
        GEM00_pim_hist->Draw("same HIST");
        double rate_pim_gem= GEM00_pim_hist->Integral();
        GEM00_pi0_hist->SetLineColor(2);
        GEM00_pi0_hist->Scale(0.000001);
        GEM00_pi0_hist->Draw("same HIST");
        double rate_pi0_gem= GEM00_pi0_hist->Integral();
       /* GEM00_eAll_hist->SetLineColor(4);
        GEM00_eAll_hist->Scale(0.000001);
        GEM00_eAll_hist->Draw("same HIST");
        double rate_eAll_gem= GEM00_eAll_hist->Integral();*/
        GEM00_beam_more_hist->SetLineColor(3);
        GEM00_beam_more_hist->Scale(0.000001);
        GEM00_beam_more_hist->Draw("same HIST");
        double rate_proton_gem_more= GEM00_beam_more_hist->Integral();
        GEM00_beam_1cm_hist->SetLineColor(7);
        GEM00_beam_1cm_hist->Scale(0.000001);
        GEM00_beam_1cm_hist->Draw("same HIST");
        double rate_proton_gem_1cm= GEM00_beam_1cm_hist->Integral();
        GEM00_beam_15cm_hist->SetLineColor(kOrange-3);
        GEM00_beam_15cm_hist->Scale(0.000001);
        GEM00_beam_15cm_hist->Draw("same HIST");
        double rate_proton_gem_15cm= GEM00_beam_15cm_hist->Integral();
        GEM00_beam_Edep_hist->SetLineColor(kMagenta-2);
        GEM00_beam_Edep_hist->Scale(0.000001);
        GEM00_beam_Edep_hist->Draw("same HIST");
        double rate_proton_gem_Edep= GEM00_beam_Edep_hist->Integral();
        GEM00_beam_config2_hist->SetLineColor(13);
        GEM00_beam_config2_hist->Scale(0.000001);
  //      GEM00_beam_config2_hist->Draw("same HIST");
        double rate_proton_gem_config2= GEM00_beam_config2_hist->Integral();
  TLegend *leg9 = new TLegend(0.45,0.6,0.8,0.88);
 // leg9->AddEntry(GEM00_beam_hist,Form("no shielding old simu 35e^{-6} cut; total rate=%f MHz",rate_proton_gem),"l");
 // leg9->AddEntry(GEM00_beam_config2_hist,Form("no shielding step SHMS 35e^{-6} cut; total rate=%f MHz",rate_proton_gem_config2),"l");
  leg9->AddEntry(GEM00_beam_config2r_hist,Form("no shielding step HMS 35e^{-6} cut; total rate=%f MHz",rate_proton_gem_config2r),"l");
  leg9->AddEntry(GEM00_pip_hist,Form("2x4x190 in^{3} Pb shielding step HMS; total rate=%f MHz",rate_pip_gem),"l");
// leg9->AddEntry(GEM00_eAll_hist,Form("2 in Pb 7x30 in^{2}; total rate=%f MHz",rate_eAll_gem),"l");
//  leg9->AddEntry(GEM00_pi0_hist,Form("2x4x190 in^{3} Pb shielding step HMS+12cm Al; total rate=%f MHz",rate_pi0_gem),"l");
  leg9->AddEntry(GEM00_beam_more_hist,Form("no shielding step HMS 15deg; total rate=%f MHz",rate_proton_gem_more),"l");
  leg9->AddEntry(GEM00_beam_1cm_hist,Form("no shielding step HMS  20deg; total rate=%f MHz",rate_proton_gem_1cm),"l");
  leg9->AddEntry(GEM00_beam_15cm_hist,Form("no shielding step HMS  25deg; total rate=%f MHz",rate_proton_gem_15cm),"l");
  leg9->AddEntry(GEM00_pim_hist,Form("no shielding step HMS  30deg; total rate=%f MHz",rate_pim_gem),"l");
  leg9->AddEntry(GEM00_beam_Edep_hist,Form("2in 10x10 cm^{2} poly GEM00 step HMS 20deg; total rate=%f MHz",rate_proton_gem_Edep),"l");
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
