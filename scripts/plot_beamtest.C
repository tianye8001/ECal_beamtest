
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

void plot_beamtest(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f11 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_TACH_40uA/HallC_beamtest_beamOntarget_TACH_80uA_filenum1992_reduce_tree_rate.root");
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_filenum19870_reduce_tree_rate.root");
	TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_80uA/HallC_beamtest_bggen_LH2_pi0_80uA_filenum19880_reduce_tree_rate.root");
	TFile *f9 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_80uA/HallC_beamtest_bggen_LH2_pim_80uA_filenum19880_reduce_tree_rate.root");
	//	TTree *tree_eAll = (TTree*) f2->Get("T");
	//	TTree *tree_eAll_beamline = (TTree*) f3->Get("T");
	//	TTree *tree_pip = (TTree*) f4->Get("T");
	TTree *tree_pip_beamline = (TTree*) f5->Get("T");
	//	TTree *tree_beamOnT = (TTree*) f1->Get("T");
	TTree *tree_beamOnT_beamline = (TTree*) f11->Get("T");
	//	TTree *tree_pi0 = (TTree*) f6->Get("T");
	TTree *tree_pi0_beamline = (TTree*) f7->Get("T");
	//	TTree *tree_pim = (TTree*) f8->Get("T");
	TTree *tree_pim_beamline = (TTree*) f9->Get("T");
	const int rebinfac=1;
//pi0
	tree_pi0_beamline ->Draw("SC0_Eendsum>>hist_SC0_pi0_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SC0_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_pi0_sum");
	tree_pi0_beamline ->Draw("SC0_Eendsum>>hist_SC0_pi0_sum_shower(200,0,100)","rate*(SC0_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SC0_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_pi0_sum_shower");
	tree_pi0_beamline ->Draw("SC1_Eendsum>>hist_SC1_pi0_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SC1_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SC1_pi0_sum");
	tree_pi0_beamline ->Draw("SC1_Eendsum>>hist_SC1_pi0_sum_shower(200,0,100)","rate*(SC1_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SC1_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SC1_pi0_sum_shower");
	tree_pi0_beamline ->Draw("LASPD_Eendsum>>hist_LASPD_pi0_sum(100,0,50)","rate*(LASPD_Eendsum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *LASPD_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_LASPD_pi0_sum");
	tree_pi0_beamline ->Draw("LASPD_Eendsum>>hist_LASPD_pi0_sum_shower(100,0,50)","rate*(LASPD_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *LASPD_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_LASPD_pi0_sum_shower");
	tree_pi0_beamline ->Draw("SPD_Eendsum>>hist_SPD_pi0_sum(100,0,50)","rate*(SPD_Eendsum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SPD_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SPD_pi0_sum");
	tree_pi0_beamline ->Draw("SPD_Eendsum>>hist_SPD_pi0_sum_shower(100,0,50)","rate*(SPD_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SPD_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SPD_pi0_sum_shower");

	tree_pi0_beamline ->Draw("PreShSum>>hist_preshower_pi0_sum(100,0,50)","rate*(PreShSum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshower_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pi0_sum");
	tree_pi0_beamline ->Draw("PreShSum>>hist_preshower_pi0_shower_sum(100,0,50)","rate*(ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshower_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pi0_shower_sum");
	tree_pi0_beamline ->Draw("PreSh_t>>hist_preshower_pi0_sumt(100,0,50)","rate*(PreSh_t>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowert_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pi0_sumt");
	tree_pi0_beamline ->Draw("PreSh_t>>hist_preshower_pi0_shower_sumt(100,0,50)","rate*(PreSh_t>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowert_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pi0_shower_sumt");
      //right preshower
	tree_pi0_beamline ->Draw("PreSh_r>>hist_preshower_pi0_sumr(100,0,50)","rate*(PreSh_r>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowerr_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pi0_sumr");
	tree_pi0_beamline ->Draw("PreSh_r>>hist_preshower_pi0_shower_sumr(100,0,50)","rate*(PreSh_r>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowerr_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pi0_shower_sumr");
      //left preshower
	tree_pi0_beamline ->Draw("PreSh_l>>hist_preshower_pi0_suml(100,0,50)","rate*(PreSh_l>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowerl_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pi0_suml");
	tree_pi0_beamline ->Draw("PreSh_l>>hist_preshower_pi0_shower_suml(100,0,50)","rate*(PreSh_l>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowerl_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pi0_shower_suml");
// shower
	tree_pi0_beamline ->Draw("ShowerSum>>hist_shower_pi0_sum(200,0,100)","rate*(ShowerSum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *shower_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pi0_sum");
	tree_pi0_beamline ->Draw("ShowerSum>>hist_shower_pi0_shower_sum(200,0,100)","rate*(ShowerSum>0 && PreShSum>0)","goff");
	TH1F *shower_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pi0_shower_sum");
	tree_pi0_beamline ->Draw("Shower_t>>hist_shower_pi0_sumt(200,0,100)","rate*(Shower_t>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showert_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pi0_sumt");
	tree_pi0_beamline ->Draw("Shower_t>>hist_shower_pi0_shower_sumt(200,0,100)","rate*(Shower_t>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showert_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pi0_shower_sumt");
      //right shower
	tree_pi0_beamline ->Draw("Shower_r>>hist_shower_pi0_sumr(200,0,100)","rate*(Shower_r>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showerr_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pi0_sumr");
	tree_pi0_beamline ->Draw("Shower_r>>hist_shower_pi0_shower_sumr(200,0,100)","rate*(Shower_r>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showerr_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pi0_shower_sumr");
      //left shower
	tree_pi0_beamline ->Draw("Shower_l>>hist_shower_pi0_suml(200,0,100)","rate*(Shower_l>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showerl_pi0_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pi0_suml");
	tree_pi0_beamline ->Draw("Shower_l>>hist_shower_pi0_shower_suml(200,0,100)","rate*(Shower_l>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showerl_pi0_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pi0_shower_suml");




//pim
	tree_pim_beamline ->Draw("SC0_Eendsum>>hist_SC0_pim_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SC0_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_pim_sum");
	tree_pim_beamline ->Draw("SC0_Eendsum>>hist_SC0_pim_sum_shower(200,0,100)","rate*(SC0_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SC0_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_pim_sum_shower");
	tree_pim_beamline ->Draw("SC1_Eendsum>>hist_SC1_pim_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SC1_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SC1_pim_sum");
	tree_pim_beamline ->Draw("SC1_Eendsum>>hist_SC1_pim_sum_shower(200,0,100)","rate*(SC1_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SC1_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SC1_pim_sum_shower");
	tree_pim_beamline ->Draw("LASPD_Eendsum>>hist_LASPD_pim_sum(100,0,50)","rate*(LASPD_Eendsum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *LASPD_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_LASPD_pim_sum");
	tree_pim_beamline ->Draw("LASPD_Eendsum>>hist_LASPD_pim_sum_shower(100,0,50)","rate*(LASPD_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *LASPD_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_LASPD_pim_sum_shower");
	tree_pim_beamline ->Draw("SPD_Eendsum>>hist_SPD_pim_sum(100,0,50)","rate*(SPD_Eendsum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SPD_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SPD_pim_sum");
	tree_pim_beamline ->Draw("SPD_Eendsum>>hist_SPD_pim_sum_shower(100,0,50)","rate*(SPD_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SPD_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SPD_pim_sum_shower");

	tree_pim_beamline ->Draw("PreShSum>>hist_preshower_pim_sum(100,0,50)","rate*(PreShSum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshower_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pim_sum");
	tree_pim_beamline ->Draw("PreShSum>>hist_preshower_pim_shower_sum(100,0,50)","rate*(ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshower_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pim_shower_sum");
	tree_pim_beamline ->Draw("PreSh_t>>hist_preshower_pim_sumt(100,0,50)","rate*(PreSh_t>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowert_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pim_sumt");
	tree_pim_beamline ->Draw("PreSh_t>>hist_preshower_pim_shower_sumt(100,0,50)","rate*(PreSh_t>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowert_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pim_shower_sumt");
      //right preshower
	tree_pim_beamline ->Draw("PreSh_r>>hist_preshower_pim_sumr(100,0,50)","rate*(PreSh_r>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowerr_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pim_sumr");
	tree_pim_beamline ->Draw("PreSh_r>>hist_preshower_pim_shower_sumr(100,0,50)","rate*(PreSh_r>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowerr_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pim_shower_sumr");
      //left preshower
	tree_pim_beamline ->Draw("PreSh_l>>hist_preshower_pim_suml(100,0,50)","rate*(PreSh_l>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowerl_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pim_suml");
	tree_pim_beamline ->Draw("PreSh_l>>hist_preshower_pim_shower_suml(100,0,50)","rate*(PreSh_l>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowerl_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pim_shower_suml");
// shower
	tree_pim_beamline ->Draw("ShowerSum>>hist_shower_pim_sum(200,0,100)","rate*(ShowerSum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *shower_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pim_sum");
	tree_pim_beamline ->Draw("ShowerSum>>hist_shower_pim_shower_sum(200,0,100)","rate*(ShowerSum>0 && PreShSum>0)","goff");
	TH1F *shower_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pim_shower_sum");
	tree_pim_beamline ->Draw("Shower_t>>hist_shower_pim_sumt(200,0,100)","rate*(Shower_t>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showert_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pim_sumt");
	tree_pim_beamline ->Draw("Shower_t>>hist_shower_pim_shower_sumt(200,0,100)","rate*(Shower_t>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showert_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pim_shower_sumt");
      //right shower
	tree_pim_beamline ->Draw("Shower_r>>hist_shower_pim_sumr(200,0,100)","rate*(Shower_r>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showerr_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pim_sumr");
	tree_pim_beamline ->Draw("Shower_r>>hist_shower_pim_shower_sumr(200,0,100)","rate*(Shower_r>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showerr_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pim_shower_sumr");
      //left shower
	tree_pim_beamline ->Draw("Shower_l>>hist_shower_pim_suml(200,0,100)","rate*(Shower_l>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showerl_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pim_suml");
	tree_pim_beamline ->Draw("Shower_l>>hist_shower_pim_shower_suml(200,0,100)","rate*(Shower_l>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showerl_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pim_shower_suml");
      //Npe sum
	tree_pim_beamline ->Draw("Npesum>>hist_Npe_pim(30,0,30)","rate*(Npesum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *Npe_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_Npe_pim");
	tree_pim_beamline ->Draw("Npesum>>hist_Npe_pim_shower(30,0,30)","rate*(Npesum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *Npe_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_Npe_pim_shower");
      //GEM X
	tree_pim_beamline ->Draw("GEM00_x>>hist_GEM00X_pim(50,-10,10)","rate*(GEM00_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM00X_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00X_pim");
	tree_pim_beamline ->Draw("GEM00_x>>hist_GEM00X_pim_shower(50,-10,10)","rate*(GEM00_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM00X_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00X_pim_shower");
      //GEM Y
	tree_pim_beamline ->Draw("GEM00_y>>hist_GEM00Y_pim(50,-10,10)","rate*(GEM00_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM00Y_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00Y_pim");
	tree_pim_beamline ->Draw("GEM00_y>>hist_GEM00Y_pim_shower(50,-10,10)","rate*(GEM00_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM00Y_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00Y_pim_shower");
      //GEM10 X
	tree_pim_beamline ->Draw("GEM10_x>>hist_GEM10X_pim(50,-10,10)","rate*(GEM10_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM10X_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10X_pim");
	tree_pim_beamline ->Draw("GEM10_x>>hist_GEM10X_pim_shower(50,-10,10)","rate*(GEM10_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM10X_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10X_pim_shower");
      //GEM10 Y
	tree_pim_beamline ->Draw("GEM10_y>>hist_GEM10Y_pim(50,-10,10)","rate*(GEM10_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM10Y_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10Y_pim");
	tree_pim_beamline ->Draw("GEM10_y>>hist_GEM10Y_pim_shower(50,-10,10)","rate*(GEM10_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM10Y_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10Y_pim_shower");

// pip
	tree_pip_beamline ->Draw("SC0_Eendsum>>hist_SC0_pip_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SC0_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_pip_sum");
	tree_pip_beamline ->Draw("SC0_Eendsum>>hist_SC0_pip_sum_shower(200,0,100)","rate*(SC0_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SC0_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_pip_sum_shower");
	tree_pip_beamline ->Draw("SC1_Eendsum>>hist_SC1_pip_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SC1_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SC1_pip_sum");
	tree_pip_beamline ->Draw("SC1_Eendsum>>hist_SC1_pip_sum_shower(200,0,100)","rate*(SC1_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SC1_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SC1_pip_sum_shower");
	tree_pip_beamline ->Draw("LASPD_Eendsum>>hist_LASPD_pip_sum(100,0,50)","rate*(LASPD_Eendsum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *LASPD_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_LASPD_pip_sum");
	tree_pip_beamline ->Draw("LASPD_Eendsum>>hist_LASPD_pip_sum_shower(100,0,50)","rate*(LASPD_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *LASPD_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_LASPD_pip_sum_shower");
	tree_pip_beamline ->Draw("SPD_Eendsum>>hist_SPD_pip_sum(100,0,50)","rate*(SPD_Eendsum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SPD_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SPD_pip_sum");
	tree_pip_beamline ->Draw("SPD_Eendsum>>hist_SPD_pip_sum_shower(100,0,50)","rate*(SPD_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SPD_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SPD_pip_sum_shower");

	tree_pip_beamline ->Draw("PreShSum>>hist_preshower_pip_sum(100,0,50)","rate*(PreShSum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshower_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pip_sum");
	tree_pip_beamline ->Draw("PreShSum>>hist_preshower_pip_shower_sum(100,0,50)","rate*(ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshower_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pip_shower_sum");
	tree_pip_beamline ->Draw("PreSh_t>>hist_preshower_pip_sumt(100,0,50)","rate*(PreSh_t>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowert_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pip_sumt");
	tree_pip_beamline ->Draw("PreSh_t>>hist_preshower_pip_shower_sumt(100,0,50)","rate*(PreSh_t>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowert_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pip_shower_sumt");
      //right preshower
	tree_pip_beamline ->Draw("PreSh_r>>hist_preshower_pip_sumr(100,0,50)","rate*(PreSh_r>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowerr_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pip_sumr");
	tree_pip_beamline ->Draw("PreSh_r>>hist_preshower_pip_shower_sumr(100,0,50)","rate*(PreSh_r>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowerr_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pip_shower_sumr");
      //left preshower
	tree_pip_beamline ->Draw("PreSh_l>>hist_preshower_pip_suml(100,0,50)","rate*(PreSh_l>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowerl_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pip_suml");
	tree_pip_beamline ->Draw("PreSh_l>>hist_preshower_pip_shower_suml(100,0,50)","rate*(PreSh_l>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowerl_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_pip_shower_suml");
// shower
	tree_pip_beamline ->Draw("ShowerSum>>hist_shower_pip_sum(200,0,100)","rate*(ShowerSum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *shower_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pip_sum");
	tree_pip_beamline ->Draw("ShowerSum>>hist_shower_pip_shower_sum(200,0,100)","rate*(ShowerSum>0 && PreShSum>0)","goff");
	TH1F *shower_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pip_shower_sum");
	tree_pip_beamline ->Draw("Shower_t>>hist_shower_pip_sumt(200,0,100)","rate*(Shower_t>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showert_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pip_sumt");
	tree_pip_beamline ->Draw("Shower_t>>hist_shower_pip_shower_sumt(200,0,100)","rate*(Shower_t>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showert_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pip_shower_sumt");
      //right shower
	tree_pip_beamline ->Draw("Shower_r>>hist_shower_pip_sumr(200,0,100)","rate*(Shower_r>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showerr_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pip_sumr");
	tree_pip_beamline ->Draw("Shower_r>>hist_shower_pip_shower_sumr(200,0,100)","rate*(Shower_r>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showerr_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pip_shower_sumr");
      //left shower
	tree_pip_beamline ->Draw("Shower_l>>hist_shower_pip_suml(200,0,100)","rate*(Shower_l>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showerl_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pip_suml");
	tree_pip_beamline ->Draw("Shower_l>>hist_shower_pip_shower_suml(200,0,100)","rate*(Shower_l>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showerl_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_pip_shower_suml");
      //Npe sum
	tree_pip_beamline ->Draw("Npesum>>hist_Npe_pip(30,0,30)","rate*(Npesum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *Npe_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_Npe_pip");
	tree_pip_beamline ->Draw("Npesum>>hist_Npe_pip_shower(30,0,30)","rate*(Npesum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *Npe_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_Npe_pip_shower");
      //GEM X
	tree_pip_beamline ->Draw("GEM00_x>>hist_GEM00X_pip(50,-10,10)","rate*(GEM00_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM00X_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00X_pip");
	tree_pip_beamline ->Draw("GEM00_x>>hist_GEM00X_pip_shower(50,-10,10)","rate*(GEM00_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM00X_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00X_pip_shower");
      //GEM Y
	tree_pip_beamline ->Draw("GEM00_y>>hist_GEM00Y_pip(50,-10,10)","rate*(GEM00_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM00Y_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00Y_pip");
	tree_pip_beamline ->Draw("GEM00_y>>hist_GEM00Y_pip_shower(50,-10,10)","rate*(GEM00_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM00Y_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00Y_pip_shower");
      //GEM10 X
	tree_pip_beamline ->Draw("GEM10_x>>hist_GEM10X_pip(50,-10,10)","rate*(GEM10_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM10X_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10X_pip");
	tree_pip_beamline ->Draw("GEM10_x>>hist_GEM10X_pip_shower(50,-10,10)","rate*(GEM10_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM10X_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10X_pip_shower");
      //GEM10 Y
	tree_pip_beamline ->Draw("GEM10_y>>hist_GEM10Y_pip(50,-10,10)","rate*(GEM10_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM10Y_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10Y_pip");
	tree_pip_beamline ->Draw("GEM10_y>>hist_GEM10Y_pip_shower(50,-10,10)","rate*(GEM10_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM10Y_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10Y_pip_shower");
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
	tree_beamOnT_beamline ->Draw("SC0_Eendsum>>hist_SC0_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SC0_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_sum");
	tree_beamOnT_beamline ->Draw("SC0_Eendsum>>hist_SC0_sum_shower(200,0,100)","rate*(SC0_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SC0_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_sum_shower");
	tree_beamOnT_beamline ->Draw("SC1_Eendsum>>hist_SC1_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SC1_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SC1_sum");
	tree_beamOnT_beamline ->Draw("SC1_Eendsum>>hist_SC1_sum_shower(200,0,100)","rate*(SC1_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SC1_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SC1_sum_shower");
	tree_beamOnT_beamline ->Draw("LASPD_Eendsum>>hist_LASPD_sum(100,0,50)","rate*(LASPD_Eendsum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *LASPD_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_LASPD_sum");
	tree_beamOnT_beamline ->Draw("LASPD_Eendsum>>hist_LASPD_sum_shower(100,0,50)","rate*(LASPD_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *LASPD_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_LASPD_sum_shower");
	tree_beamOnT_beamline ->Draw("SPD_Eendsum>>hist_SPD_sum(100,0,50)","rate*(SPD_Eendsum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SPD_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SPD_sum");
	tree_beamOnT_beamline ->Draw("SPD_Eendsum>>hist_SPD_sum_shower(100,0,50)","rate*(SPD_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SPD_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SPD_sum_shower");

	tree_beamOnT_beamline ->Draw("PreShSum>>hist_preshower_sum(100,0,50)","rate*(PreShSum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshower_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_sum");
	tree_beamOnT_beamline ->Draw("PreShSum>>hist_preshower_shower_sum(100,0,50)","rate*(ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshower_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_shower_sum");
	tree_beamOnT_beamline ->Draw("PreSh_t>>hist_preshower_sumt(100,0,50)","rate*(PreSh_t>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowert_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_sumt");
	tree_beamOnT_beamline ->Draw("PreSh_t>>hist_preshower_shower_sumt(100,0,50)","rate*(PreSh_t>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowert_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_shower_sumt");
      //right preshower
	tree_beamOnT_beamline ->Draw("PreSh_r>>hist_preshower_sumr(100,0,50)","rate*(PreSh_r>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowerr_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_sumr");
	tree_beamOnT_beamline ->Draw("PreSh_r>>hist_preshower_shower_sumr(100,0,50)","rate*(PreSh_r>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowerr_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_shower_sumr");
      //left preshower
	tree_beamOnT_beamline ->Draw("PreSh_l>>hist_preshower_suml(100,0,50)","rate*(PreSh_l>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *preshowerl_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_suml");
	tree_beamOnT_beamline ->Draw("PreSh_l>>hist_preshower_shower_suml(100,0,50)","rate*(PreSh_l>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *preshowerl_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_preshower_shower_suml");
// shower
	tree_beamOnT_beamline ->Draw("ShowerSum>>hist_shower_sum(200,0,100)","rate*(ShowerSum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *shower_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_sum");
	tree_beamOnT_beamline ->Draw("ShowerSum>>hist_shower_shower_sum(200,0,100)","rate*(ShowerSum>0 && PreShSum>0)","goff");
	TH1F *shower_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_shower_sum");
	tree_beamOnT_beamline ->Draw("Shower_t>>hist_shower_sumt(200,0,100)","rate*(Shower_t>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showert_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_sumt");
	tree_beamOnT_beamline ->Draw("Shower_t>>hist_shower_shower_sumt(200,0,100)","rate*(Shower_t>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showert_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_shower_sumt");
      //right shower
	tree_beamOnT_beamline ->Draw("Shower_r>>hist_shower_sumr(200,0,100)","rate*(Shower_r>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showerr_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_sumr");
	tree_beamOnT_beamline ->Draw("Shower_r>>hist_shower_shower_sumr(200,0,100)","rate*(Shower_r>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showerr_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_shower_sumr");
      //left shower
	tree_beamOnT_beamline ->Draw("Shower_l>>hist_shower_suml(200,0,100)","rate*(Shower_l>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *showerl_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_suml");
	tree_beamOnT_beamline ->Draw("Shower_l>>hist_shower_shower_suml(200,0,100)","rate*(Shower_l>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *showerl_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_shower_shower_suml");
      //Npe sum
	tree_beamOnT_beamline ->Draw("Npesum>>hist_Npe(30,0,30)","rate*(Npesum>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *Npe_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_Npe");
	tree_beamOnT_beamline ->Draw("Npesum>>hist_Npe_shower(30,0,30)","rate*(Npesum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *Npe_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_Npe_shower");
      //GEM X
	tree_beamOnT_beamline ->Draw("GEM00_x>>hist_GEM00X(50,-10,10)","rate*(GEM00_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM00X_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00X");
	tree_beamOnT_beamline ->Draw("GEM00_x>>hist_GEM00X_shower(50,-10,10)","rate*(GEM00_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM00X_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00X_shower");
      //GEM Y
	tree_beamOnT_beamline ->Draw("GEM00_y>>hist_GEM00Y(50,-10,10)","rate*(GEM00_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM00Y_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00Y");
	tree_beamOnT_beamline ->Draw("GEM00_y>>hist_GEM00Y_shower(50,-10,10)","rate*(GEM00_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM00Y_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM00Y_shower");
      //GEM10 X
	tree_beamOnT_beamline ->Draw("GEM10_x>>hist_GEM10X(50,-10,10)","rate*(GEM10_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM10X_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10X");
	tree_beamOnT_beamline ->Draw("GEM10_x>>hist_GEM10X_shower(50,-10,10)","rate*(GEM10_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM10X_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10X_shower");
      //GEM10 Y
	tree_beamOnT_beamline ->Draw("GEM10_y>>hist_GEM10Y(50,-10,10)","rate*(GEM10_n>0 && SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *GEM10Y_beamonT_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10Y");
	tree_beamOnT_beamline ->Draw("GEM10_y>>hist_GEM10Y_shower(50,-10,10)","rate*(GEM10_n>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *GEM10Y_beamonT_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_GEM10Y_shower");
	TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	SC0_beamonT_SCtrigger_hist->SetLineColor(1); 
	SC0_beamonT_SCtrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	SC0_beamonT_SCtrigger_hist->GetXaxis()->SetTitle("SC0 depE (MeV)"); 
	SC0_beamonT_SCtrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	SC0_beamonT_SCtrigger_hist->SetTitle("SC0 Deposit Eend"); 
	SC0_beamonT_SCtrigger_hist->Draw(); 
	SC0_beamonT_showertrigger_hist->SetLineColor(2); 
	SC0_pip_showertrigger_hist->SetLineColor(4); 
	SC0_pip_showertrigger_hist->Draw("same"); 
	SC0_pip_SCtrigger_hist->SetLineColor(6); 
	SC0_pip_SCtrigger_hist->Draw("same"); 
	SC0_pim_showertrigger_hist->SetLineColor(7); 
	SC0_pim_showertrigger_hist->Draw("same"); 
	SC0_pim_SCtrigger_hist->SetLineColor(8); 
	SC0_pim_SCtrigger_hist->Draw("same"); 
	SC0_pi0_showertrigger_hist->SetLineColor(43); 
	SC0_pi0_showertrigger_hist->Draw("same"); 
	SC0_pi0_SCtrigger_hist->SetLineColor(9); 
	SC0_pi0_SCtrigger_hist->Draw("same"); 
	SC0_beamonT_showertrigger_hist->Draw("same"); 
	TLegend *leg1 = new TLegend(0.3,0.6,0.6,0.88);
	leg1->AddEntry(SC0_beamonT_SCtrigger_hist,"BeamOnTarget,SC0_E>0 && SC1_E>0 ","l");
	leg1->AddEntry(SC0_beamonT_showertrigger_hist,"BeamOnTarget,Shower>0 && PreSh>0","l");
	leg1->AddEntry(SC0_pip_showertrigger_hist,"bggen #pi^{+},Shower>0 && PreSh>0","l");
	leg1->AddEntry(SC0_pim_showertrigger_hist,"bggen #pi^{-},Shower>0 && PreSh>0","l");
	leg1->AddEntry(SC0_pi0_showertrigger_hist,"bggen #pi^{0},Shower>0 && PreSh>0","l");
	leg1->AddEntry(SC0_pip_SCtrigger_hist,"bggen #pi^{+},SC0_E>0 && SC1_E>0","l");
	leg1->AddEntry(SC0_pim_SCtrigger_hist,"bggen #pi^{-},SC0_E>0 && SC1_E>0","l");
	leg1->AddEntry(SC0_pi0_SCtrigger_hist,"bggen #pi^{0},SC0_E>0 && SC1_E>0","l");
	leg1->SetTextSize(0.03);
	leg1->SetBorderSize(0);
	leg1->SetFillColor(0);
	leg1->Draw("text same");
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	SC1_beamonT_SCtrigger_hist->SetLineColor(1); 
	SC1_beamonT_SCtrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	SC1_beamonT_SCtrigger_hist->GetXaxis()->SetTitle("SC1 depE (MeV)"); 
	SC1_beamonT_SCtrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	SC1_beamonT_SCtrigger_hist->SetTitle("SC1 Deposit Eend"); 
	SC1_beamonT_SCtrigger_hist->Draw(); 
	SC1_beamonT_showertrigger_hist->SetLineColor(2); 
	SC1_pip_showertrigger_hist->SetLineColor(4); 
	SC1_pip_showertrigger_hist->Draw("same"); 
	SC1_pip_SCtrigger_hist->SetLineColor(6); 
	SC1_pip_SCtrigger_hist->Draw("same"); 
	SC1_pim_showertrigger_hist->SetLineColor(7); 
	SC1_pim_showertrigger_hist->Draw("same"); 
	SC1_pim_SCtrigger_hist->SetLineColor(8); 
	SC1_pim_SCtrigger_hist->Draw("same"); 
	SC1_pi0_showertrigger_hist->SetLineColor(43); 
	SC1_pi0_showertrigger_hist->Draw("same"); 
	SC1_pi0_SCtrigger_hist->SetLineColor(9); 
	SC1_pi0_SCtrigger_hist->Draw("same"); 
	SC1_beamonT_showertrigger_hist->Draw("same"); 
	leg1->Draw("text same");
	c[2] = new TCanvas("c[2]","c[2]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	LASPD_beamonT_SCtrigger_hist->SetLineColor(1); 
	LASPD_beamonT_SCtrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	LASPD_beamonT_SCtrigger_hist->GetXaxis()->SetTitle("LASPD depE (MeV)"); 
	LASPD_beamonT_SCtrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	LASPD_beamonT_SCtrigger_hist->SetTitle("LASPD Deposit Eend"); 
	LASPD_beamonT_SCtrigger_hist->Draw(); 
	LASPD_beamonT_showertrigger_hist->SetLineColor(2); 
	LASPD_pip_showertrigger_hist->SetLineColor(4); 
	LASPD_pip_showertrigger_hist->Draw("same"); 
	LASPD_pip_SCtrigger_hist->SetLineColor(6); 
	LASPD_pip_SCtrigger_hist->Draw("same"); 
	LASPD_pim_showertrigger_hist->SetLineColor(7); 
	LASPD_pim_showertrigger_hist->Draw("same"); 
	LASPD_pim_SCtrigger_hist->SetLineColor(8); 
	LASPD_pim_SCtrigger_hist->Draw("same"); 
	LASPD_pi0_showertrigger_hist->SetLineColor(43); 
	LASPD_pi0_showertrigger_hist->Draw("same"); 
	LASPD_pi0_SCtrigger_hist->SetLineColor(9); 
	LASPD_pi0_SCtrigger_hist->Draw("same"); 
	LASPD_beamonT_showertrigger_hist->Draw("same"); 
	leg1->Draw("text same");
	c[3] = new TCanvas("c[3]","c[3]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	SPD_beamonT_SCtrigger_hist->SetLineColor(1); 
	SPD_beamonT_SCtrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	SPD_beamonT_SCtrigger_hist->GetXaxis()->SetTitle("SPD depE (MeV)"); 
	SPD_beamonT_SCtrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	SPD_beamonT_SCtrigger_hist->SetTitle("SPD Deposit Eend"); 
	SPD_beamonT_SCtrigger_hist->Draw(); 
	SPD_beamonT_showertrigger_hist->SetLineColor(2); 
	SPD_pip_showertrigger_hist->SetLineColor(4); 
	SPD_pip_showertrigger_hist->Draw("same"); 
	SPD_pip_SCtrigger_hist->SetLineColor(6); 
	SPD_pip_SCtrigger_hist->Draw("same"); 
	SPD_pim_showertrigger_hist->SetLineColor(7); 
	SPD_pim_showertrigger_hist->Draw("same"); 
	SPD_pim_SCtrigger_hist->SetLineColor(8); 
	SPD_pim_SCtrigger_hist->Draw("same"); 
	SPD_pi0_showertrigger_hist->SetLineColor(43); 
	SPD_pi0_showertrigger_hist->Draw("same"); 
	SPD_pi0_SCtrigger_hist->SetLineColor(9); 
	SPD_pi0_SCtrigger_hist->Draw("same"); 
	SPD_beamonT_showertrigger_hist->Draw("same"); 
	leg1->Draw("text same");
	c[4] = new TCanvas("c[4]","c[4]",1000,1000);
        c[4]->Divide(2,2);
        c[4]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	preshower_beamonT_showertrigger_hist->SetLineColor(2); 
	preshower_beamonT_showertrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	preshower_beamonT_showertrigger_hist->GetXaxis()->SetTitle("preshower depE (MeV)"); 
	preshower_beamonT_showertrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	preshower_beamonT_showertrigger_hist->SetTitle("preshower Deposit Eend"); 
	preshower_beamonT_showertrigger_hist->Draw(); 
	preshower_beamonT_SCtrigger_hist->SetLineColor(1); 
	preshower_beamonT_SCtrigger_hist->Draw("same"); 
	preshower_pip_showertrigger_hist->SetLineColor(4); 
	preshower_pip_showertrigger_hist->Draw("same"); 
	preshower_pip_SCtrigger_hist->SetLineColor(6); 
	preshower_pip_SCtrigger_hist->Draw("same"); 
	preshower_pim_showertrigger_hist->SetLineColor(7); 
	preshower_pim_showertrigger_hist->Draw("same"); 
	preshower_pim_SCtrigger_hist->SetLineColor(8); 
	preshower_pim_SCtrigger_hist->Draw("same"); 
	preshower_pi0_showertrigger_hist->SetLineColor(43); 
	preshower_pi0_showertrigger_hist->Draw("same"); 
	preshower_pi0_SCtrigger_hist->SetLineColor(9); 
	preshower_pi0_SCtrigger_hist->Draw("same"); 
	leg1->Draw("text same");
        c[4]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	preshowert_beamonT_showertrigger_hist->SetLineColor(2); 
	preshowert_beamonT_showertrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	preshowert_beamonT_showertrigger_hist->GetXaxis()->SetTitle("preshower depE (MeV)"); 
	preshowert_beamonT_showertrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	preshowert_beamonT_showertrigger_hist->SetTitle("top preshower Deposit Eend"); 
	preshowert_beamonT_showertrigger_hist->Draw(); 
	preshowert_beamonT_SCtrigger_hist->SetLineColor(1); 
	preshowert_beamonT_SCtrigger_hist->Draw("same"); 
	preshowert_pip_showertrigger_hist->SetLineColor(4); 
	preshowert_pip_showertrigger_hist->Draw("same"); 
	preshowert_pip_SCtrigger_hist->SetLineColor(6); 
	preshowert_pip_SCtrigger_hist->Draw("same"); 
	preshowert_pim_showertrigger_hist->SetLineColor(7); 
	preshowert_pim_showertrigger_hist->Draw("same"); 
	preshowert_pim_SCtrigger_hist->SetLineColor(8); 
	preshowert_pim_SCtrigger_hist->Draw("same"); 
	preshowert_pi0_showertrigger_hist->SetLineColor(43); 
	preshowert_pi0_showertrigger_hist->Draw("same"); 
	preshowert_pi0_SCtrigger_hist->SetLineColor(9); 
	preshowert_pi0_SCtrigger_hist->Draw("same"); 
	leg1->Draw("text same");
        c[4]->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	preshowerr_beamonT_showertrigger_hist->SetLineColor(2); 
	preshowerr_beamonT_showertrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	preshowerr_beamonT_showertrigger_hist->GetXaxis()->SetTitle("preshower depE (MeV)"); 
	preshowerr_beamonT_showertrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	preshowerr_beamonT_showertrigger_hist->SetTitle("right preshower Deposit Eend"); 
	preshowerr_beamonT_showertrigger_hist->Draw(); 
	preshowerr_beamonT_SCtrigger_hist->SetLineColor(1); 
	preshowerr_beamonT_SCtrigger_hist->Draw("same"); 
	preshowerr_pip_showertrigger_hist->SetLineColor(4); 
	preshowerr_pip_showertrigger_hist->Draw("same"); 
	preshowerr_pip_SCtrigger_hist->SetLineColor(6); 
	preshowerr_pip_SCtrigger_hist->Draw("same"); 
	preshowerr_pim_showertrigger_hist->SetLineColor(7); 
	preshowerr_pim_showertrigger_hist->Draw("same"); 
	preshowerr_pim_SCtrigger_hist->SetLineColor(8); 
	preshowerr_pim_SCtrigger_hist->Draw("same"); 
	preshowerr_pi0_showertrigger_hist->SetLineColor(43); 
	preshowerr_pi0_showertrigger_hist->Draw("same"); 
	preshowerr_pi0_SCtrigger_hist->SetLineColor(9); 
	preshowerr_pi0_SCtrigger_hist->Draw("same"); 
	leg1->Draw("text same");
        c[4]->cd(4);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	preshowerl_beamonT_showertrigger_hist->SetLineColor(2); 
	preshowerl_beamonT_showertrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	preshowerl_beamonT_showertrigger_hist->GetXaxis()->SetTitle("preshower depE (MeV)"); 
	preshowerl_beamonT_showertrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	preshowerl_beamonT_showertrigger_hist->SetTitle("left preshower Deposit Eend"); 
	preshowerl_beamonT_showertrigger_hist->Draw(); 
	preshowerl_beamonT_SCtrigger_hist->SetLineColor(1); 
	preshowerl_beamonT_SCtrigger_hist->Draw("same"); 
	preshowerl_pip_showertrigger_hist->SetLineColor(4); 
	preshowerl_pip_showertrigger_hist->Draw("same"); 
	preshowerl_pip_SCtrigger_hist->SetLineColor(6); 
	preshowerl_pip_SCtrigger_hist->Draw("same"); 
	preshowerl_pim_showertrigger_hist->SetLineColor(7); 
	preshowerl_pim_showertrigger_hist->Draw("same"); 
	preshowerl_pim_SCtrigger_hist->SetLineColor(8); 
	preshowerl_pim_SCtrigger_hist->Draw("same"); 
	preshowerl_pi0_showertrigger_hist->SetLineColor(43); 
	preshowerl_pi0_showertrigger_hist->Draw("same"); 
	preshowerl_pi0_SCtrigger_hist->SetLineColor(9); 
	preshowerl_pi0_SCtrigger_hist->Draw("same"); 
	leg1->Draw("text same");
	c[5] = new TCanvas("c[5]","c[5]",1000,1000);
        c[5]->Divide(2,2);
        c[5]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	shower_beamonT_showertrigger_hist->SetLineColor(2); 
	shower_beamonT_showertrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	shower_beamonT_showertrigger_hist->GetXaxis()->SetTitle("shower depE (MeV)"); 
	shower_beamonT_showertrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	shower_beamonT_showertrigger_hist->SetTitle("shower Deposit Eend"); 
	shower_beamonT_showertrigger_hist->Draw(); 
	shower_beamonT_SCtrigger_hist->SetLineColor(1); 
	shower_beamonT_SCtrigger_hist->Draw("same"); 
	shower_pip_showertrigger_hist->SetLineColor(4); 
	shower_pip_showertrigger_hist->Draw("same"); 
	shower_pip_SCtrigger_hist->SetLineColor(6); 
	shower_pip_SCtrigger_hist->Draw("same"); 
	shower_pim_showertrigger_hist->SetLineColor(7); 
	shower_pim_showertrigger_hist->Draw("same"); 
	shower_pim_SCtrigger_hist->SetLineColor(8); 
	shower_pim_SCtrigger_hist->Draw("same"); 
	shower_pi0_showertrigger_hist->SetLineColor(43); 
	shower_pi0_showertrigger_hist->Draw("same"); 
	shower_pi0_SCtrigger_hist->SetLineColor(9); 
	shower_pi0_SCtrigger_hist->Draw("same"); 
	leg1->Draw("text same");
        c[5]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	showert_beamonT_showertrigger_hist->SetLineColor(2); 
	showert_beamonT_showertrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	showert_beamonT_showertrigger_hist->GetXaxis()->SetTitle("shower depE (MeV)"); 
	showert_beamonT_showertrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	showert_beamonT_showertrigger_hist->SetTitle("top shower Deposit Eend"); 
	showert_beamonT_showertrigger_hist->Draw(); 
	showert_beamonT_SCtrigger_hist->SetLineColor(1); 
	showert_beamonT_SCtrigger_hist->Draw("same"); 
	showert_pip_showertrigger_hist->SetLineColor(4); 
	showert_pip_showertrigger_hist->Draw("same"); 
	showert_pip_SCtrigger_hist->SetLineColor(6); 
	showert_pip_SCtrigger_hist->Draw("same"); 
	showert_pim_showertrigger_hist->SetLineColor(7); 
	showert_pim_showertrigger_hist->Draw("same"); 
	showert_pim_SCtrigger_hist->SetLineColor(8); 
	showert_pim_SCtrigger_hist->Draw("same"); 
	showert_pi0_showertrigger_hist->SetLineColor(43); 
	showert_pi0_showertrigger_hist->Draw("same"); 
	showert_pi0_SCtrigger_hist->SetLineColor(9); 
	showert_pi0_SCtrigger_hist->Draw("same"); 
	leg1->Draw("text same");
        c[5]->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	showerr_beamonT_showertrigger_hist->SetLineColor(2); 
	showerr_beamonT_showertrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	showerr_beamonT_showertrigger_hist->GetXaxis()->SetTitle("shower depE (MeV)"); 
	showerr_beamonT_showertrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	showerr_beamonT_showertrigger_hist->SetTitle("right shower Deposit Eend"); 
	showerr_beamonT_showertrigger_hist->Draw(); 
	showerr_beamonT_SCtrigger_hist->SetLineColor(1); 
	showerr_beamonT_SCtrigger_hist->Draw("same"); 
	showerr_pip_showertrigger_hist->SetLineColor(4); 
	showerr_pip_showertrigger_hist->Draw("same"); 
	showerr_pip_SCtrigger_hist->SetLineColor(6); 
	showerr_pip_SCtrigger_hist->Draw("same"); 
	showerr_pim_showertrigger_hist->SetLineColor(7); 
	showerr_pim_showertrigger_hist->Draw("same"); 
	showerr_pim_SCtrigger_hist->SetLineColor(8); 
	showerr_pim_SCtrigger_hist->Draw("same"); 
	showerr_pi0_showertrigger_hist->SetLineColor(43); 
	showerr_pi0_showertrigger_hist->Draw("same"); 
	showerr_pi0_SCtrigger_hist->SetLineColor(9); 
	showerr_pi0_SCtrigger_hist->Draw("same"); 
	leg1->Draw("text same");
        c[5]->cd(4);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	showerl_beamonT_showertrigger_hist->SetLineColor(2); 
	showerl_beamonT_showertrigger_hist->GetYaxis()->SetRangeUser(1e0,1e10); 
	showerl_beamonT_showertrigger_hist->GetXaxis()->SetTitle("shower depE (MeV)"); 
	showerl_beamonT_showertrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	showerl_beamonT_showertrigger_hist->SetTitle("left shower Deposit Eend"); 
	showerl_beamonT_showertrigger_hist->Draw(); 
	showerl_beamonT_SCtrigger_hist->SetLineColor(1); 
	showerl_beamonT_SCtrigger_hist->Draw("same"); 
	showerl_pip_showertrigger_hist->SetLineColor(4); 
	showerl_pip_showertrigger_hist->Draw("same"); 
	showerl_pip_SCtrigger_hist->SetLineColor(6); 
	showerl_pip_SCtrigger_hist->Draw("same"); 
	showerl_pim_showertrigger_hist->SetLineColor(7); 
	showerl_pim_showertrigger_hist->Draw("same"); 
	showerl_pim_SCtrigger_hist->SetLineColor(8); 
	showerl_pim_SCtrigger_hist->Draw("same"); 
	showerl_pi0_showertrigger_hist->SetLineColor(43); 
	showerl_pi0_showertrigger_hist->Draw("same"); 
	showerl_pi0_SCtrigger_hist->SetLineColor(9); 
	showerl_pi0_SCtrigger_hist->Draw("same"); 
	leg1->Draw("text same");
	c[6] = new TCanvas("c[6]","c[6]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	Npe_beamonT_SCtrigger_hist->SetLineColor(1); 
	Npe_beamonT_SCtrigger_hist->GetYaxis()->SetRangeUser(1e0,1e7); 
	Npe_beamonT_SCtrigger_hist->GetXaxis()->SetTitle("Nphe (MeV)"); 
	Npe_beamonT_SCtrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	Npe_beamonT_SCtrigger_hist->SetTitle("Nphe"); 
	Npe_beamonT_SCtrigger_hist->Draw(); 
	Npe_beamonT_showertrigger_hist->SetLineColor(2); 
	Npe_beamonT_showertrigger_hist->Draw("same"); 
//	leg1->Draw("text same");
	c[7] = new TCanvas("c[7]","c[7]",1000,1000);
        c[7]->Divide(1,2);
        c[7]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	GEM00X_beamonT_SCtrigger_hist->SetLineColor(1); 
	GEM00X_beamonT_SCtrigger_hist->GetYaxis()->SetRangeUser(1e0,1e9); 
	GEM00X_beamonT_SCtrigger_hist->GetXaxis()->SetTitle("GEM00_X (cm)"); 
	GEM00X_beamonT_SCtrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	GEM00X_beamonT_SCtrigger_hist->SetTitle("GEM00"); 
	GEM00X_beamonT_SCtrigger_hist->Draw(); 
        GEM00X_beamonT_showertrigger_hist->SetLineColor(2); 
	GEM00X_beamonT_showertrigger_hist->Draw("same"); 
//	leg1->Draw("text same");
        c[7]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	GEM00Y_beamonT_SCtrigger_hist->SetLineColor(1); 
	GEM00Y_beamonT_SCtrigger_hist->GetYaxis()->SetRangeUser(1e0,1e9); 
	GEM00Y_beamonT_SCtrigger_hist->GetXaxis()->SetTitle("GEM00_Y (cm)"); 
	GEM00Y_beamonT_SCtrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	GEM00Y_beamonT_SCtrigger_hist->SetTitle("GEM00"); 
	GEM00Y_beamonT_SCtrigger_hist->Draw(); 
        GEM00Y_beamonT_showertrigger_hist->SetLineColor(2); 
	GEM00Y_beamonT_showertrigger_hist->Draw("same"); 
//	leg1->Draw("text same");
	c[8] = new TCanvas("c[8]","c[8]",1000,1000);
        c[8]->Divide(1,2);
        c[8]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	GEM10X_beamonT_SCtrigger_hist->SetLineColor(1); 
	GEM10X_beamonT_SCtrigger_hist->GetYaxis()->SetRangeUser(1e0,1e9); 
	GEM10X_beamonT_SCtrigger_hist->GetXaxis()->SetTitle("GEM10_X (cm)"); 
	GEM10X_beamonT_SCtrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	GEM10X_beamonT_SCtrigger_hist->SetTitle("GEM10"); 
	GEM10X_beamonT_SCtrigger_hist->Draw(); 
        GEM10X_beamonT_showertrigger_hist->SetLineColor(2); 
	GEM10X_beamonT_showertrigger_hist->Draw("same"); 
//	leg1->Draw("text same");
        c[8]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
	GEM10Y_beamonT_SCtrigger_hist->SetLineColor(1); 
	GEM10Y_beamonT_SCtrigger_hist->GetYaxis()->SetRangeUser(1e0,1e9); 
	GEM10Y_beamonT_SCtrigger_hist->GetXaxis()->SetTitle("GEM10_Y (cm)"); 
	GEM10Y_beamonT_SCtrigger_hist->GetYaxis()->SetTitle("rate (Hz)"); 
	GEM10Y_beamonT_SCtrigger_hist->SetTitle("GEM10"); 
	GEM10Y_beamonT_SCtrigger_hist->Draw(); 
        GEM10Y_beamonT_showertrigger_hist->SetLineColor(2); 
	GEM10Y_beamonT_showertrigger_hist->Draw("same"); 
//	leg1->Draw("text same");
	for(int a=0;a<9;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_trigger_beamtest_comparison_all.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
