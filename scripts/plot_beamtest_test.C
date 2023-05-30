
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

void plot_beamtest_test(){
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




//pim
	tree_pim_beamline ->Draw("SC0_Eendsum>>hist_SC0_pim_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SC0_pim_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_pim_sum");
	tree_pim_beamline ->Draw("SC0_Eendsum>>hist_SC0_pim_sum_shower(200,0,100)","rate*(SC0_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SC0_pim_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_pim_sum_shower");
	tree_pim_beamline ->Draw("SC1_Eendsum>>hist_SC1_pim_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");

// pip
	tree_pip_beamline ->Draw("SC0_Eendsum>>hist_SC0_pip_sum(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *SC0_pip_SCtrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_pip_sum");
	tree_pip_beamline ->Draw("SC0_Eendsum>>hist_SC0_pip_sum_shower(200,0,100)","rate*(SC0_Eendsum>0 && ShowerSum>0 && PreShSum>0)","goff");
	TH1F *SC0_pip_showertrigger_hist = (TH1F*)gROOT->FindObject("hist_SC0_pip_sum_shower");
      //left preshower
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
	for(int a=0;a<9;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_trigger_beamtest_comparison.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
