
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

void plot_EC_gem_compare(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f1 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_LH2_10cm_only/HallC_beamtest_LH2_moved_10cm_BeamOnTarget_7.5e11_reduce_tree.root");
	TFile *f11 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_TACH2/HallC_beamtest_LH2_moved_full_BeamOnTarget_9.8e9_reduce_tree_rate.root");
	TFile *f2 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll/HallC_bggen_LH2_beamtest_full_eAll_filenum100_1e8_nobeamline_reduce_tree.root");
	TFile *f3 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll/HallC_bggen_LH2_beamtest_full_eAll_filenum100_1e8_newbeamline_reduce_tree.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip/HallC_beamtest_bggen_LH2_pip_filenum16330_nobeamline_reduce_tree.root");
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip/output/HallC_beamtest_bggen_LH2_pip_newbeamline_filenum23450_reduce_tree_rate.root");
	TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0/HallC_beamtest_bggen_LH2_nobeamline_pi0_filenum15660_reduce_tree.root");
	TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0/HallC_beamtest_bggen_LH2_newbeamline_pi0_filenum12070_reduce_tree.root");
	TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim/HallC_beamtest_bggen_LH2_pim_filenum11250_nobeamline_reduce_tree.root");
	TFile *f9 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim/HallC_beamtest_bggen_LH2_pim_newbeamline_filenum9220_reduce_tree.root");
	TTree *tree_eAll = (TTree*) f2->Get("T");
	TTree *tree_eAll_beamline = (TTree*) f3->Get("T");
	TTree *tree_pip = (TTree*) f4->Get("T");
	TTree *tree_pip_beamline = (TTree*) f5->Get("T");
	TTree *tree_beamOnT = (TTree*) f1->Get("T");
	TTree *tree_beamOnT_beamline = (TTree*) f11->Get("T");
	TTree *tree_pi0 = (TTree*) f6->Get("T");
	TTree *tree_pi0_beamline = (TTree*) f7->Get("T");
	TTree *tree_pim = (TTree*) f8->Get("T");
	TTree *tree_pim_beamline = (TTree*) f9->Get("T");
	const int rebinfac=1;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
	tree_eAll ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX");
	tree_eAll_beamline ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_beamline(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_beamline");
	tree_pip ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pip_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip");
	tree_pip_beamline ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_beamline(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pip_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_beamline");
	tree_pi0 ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pi0(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pi0_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pi0");
	tree_pi0_beamline ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pi0_beamline(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pi0_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pi0_beamline");
	tree_pim ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pim(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pim_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pim");
	tree_pim_beamline ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pim_beamline(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pim_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pim_beamline");
	tree_beamOnT ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_beamOnT(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_beamOnT_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_beamOnT");
	tree_beamOnT_beamline ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_beamOnT_beamline(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_beamOnT_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_beamOnT_beamline");


	tree_eAll ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY");
	tree_eAll_beamline ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_beamline(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_beamline");
	tree_pip ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pip_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip");
	tree_pip_beamline ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_beamline(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pip_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_beamline");
	tree_pi0 ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pi0(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pi0_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pi0");
	tree_pi0_beamline ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pi0_beamline(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pi0_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pi0_beamline");
	tree_pim ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pim(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pim_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pim");
	tree_pim_beamline ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pim_beamline(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pim_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pim_beamline");
	tree_beamOnT ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_beamOnT(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_beamOnT_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_beamOnT");
	tree_beamOnT_beamline ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_beamOnT_beamline(50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_beamOnT_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_beamOnT_beamline");
	// 2D plots
	tree_eAll ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff(50,-10,10,50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff");
	tree_eAll_beamline ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_beamline(50,-10,10,50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_beamline_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_beamline");
	tree_pip ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_pip(50,-10,10,50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_pip_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_pip");
	tree_pip_beamline ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_pip_beamline(50,-10,10,50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_pip_beamline_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_pip_beamline");
	tree_beamOnT ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_beamOnT(50,-10,10,50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_beamOnT_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_beamOnT");
	tree_beamOnT_beamline ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_beamOnT_beamline(50,-10,10,50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_beamOnT_beamline_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_beamOnT_beamline");
	tree_pi0 ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_pi0(50,-10,10,50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_pi0_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_pi0");
	tree_pi0_beamline ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_pi0_beamline(50,-10,10,50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_pi0_beamline_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_pi0_beamline");

	tree_pim ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_pim(50,-10,10,50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_pim_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_pim");
	tree_pim_beamline ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_pim_beamline(50,-10,10,50,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_pim_beamline_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_pim_beamline");

	TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	c[0]->Divide(1,2);
	c[0]->cd(1);
	DiffX_gem_beamline_hist->SetLineColor(2); 
	DiffX_gem_beamline_hist->GetXaxis()->SetTitle("GEM00_x-GEM10_x (cm)"); 
	DiffX_gem_beamline_hist->GetYaxis()->SetTitle("event"); 
	DiffX_gem_beamline_hist->SetTitle("eAll"); 
	DiffX_gem_beamline_hist->Draw(); 
	DiffX_gem_hist->SetLineColor(1); 
	DiffX_gem_hist->Scale(DiffX_gem_beamline_hist->Integral()/DiffX_gem_hist->Integral()); 
	DiffX_gem_hist->Draw("same"); 
	TLegend *leg1 = new TLegend(0.6,0.6,0.88,0.88);
	leg1->AddEntry(DiffX_gem_hist,"without beamline","l");
	leg1->AddEntry(DiffX_gem_beamline_hist,"with beamline","l");
	leg1->SetTextSize(0.03);
	leg1->SetBorderSize(0);
	leg1->SetFillColor(0);
	leg1->Draw("text same");
	c[0]->cd(2);
	DiffY_gem_beamline_hist->SetLineColor(2); 
	DiffY_gem_beamline_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)"); 
	DiffY_gem_beamline_hist->GetYaxis()->SetTitle("event"); 
	DiffY_gem_beamline_hist->SetTitle("eAll"); 
	DiffY_gem_beamline_hist->Draw(); 
	DiffY_gem_hist->SetLineColor(1); 
	DiffY_gem_hist->Scale(DiffY_gem_beamline_hist->Integral()/DiffY_gem_hist->Integral()); 
	DiffY_gem_hist->Draw("same"); 
	leg1->Draw("text same");
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
	c[1]->Divide(1,2);
	c[1]->cd(1);
	DiffX_gem_pip_hist->SetLineColor(1); 
	DiffX_gem_pip_hist->GetXaxis()->SetTitle("GEM00_x-GEM10_x (cm)"); 
	DiffX_gem_pip_hist->SetTitle("bggen #pi^{+}"); 
	DiffX_gem_pip_hist->GetYaxis()->SetTitle("event"); 
	DiffX_gem_pip_hist->Draw(); 
	DiffX_gem_pip_beamline_hist->SetLineColor(2); 
	DiffX_gem_pip_beamline_hist->Scale(DiffX_gem_pip_hist->Integral()/DiffX_gem_pip_beamline_hist->Integral()); 
	DiffX_gem_pip_beamline_hist->Draw("same"); 
	leg1->Draw("text same");
	c[1]->cd(2);
	DiffY_gem_pip_hist->SetLineColor(1); 
	DiffY_gem_pip_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)"); 
	DiffY_gem_pip_hist->SetTitle("bggen #pi^{+}"); 
	DiffY_gem_pip_hist->GetYaxis()->SetTitle("event"); 
	DiffY_gem_pip_hist->Draw(); 
	DiffY_gem_pip_beamline_hist->SetLineColor(2); 
	DiffY_gem_pip_beamline_hist->Scale(DiffY_gem_pip_hist->Integral()/DiffY_gem_pip_beamline_hist->Integral()); 
	DiffY_gem_pip_beamline_hist->Draw("same"); 
	leg1->Draw("text same");
	c[2] = new TCanvas("c[2]","c[2]",1000,1000);
	c[2]->Divide(1,2);
	c[2]->cd(1);
	DiffX_gem_pi0_hist->SetLineColor(1); 
	DiffX_gem_pi0_hist->GetXaxis()->SetTitle("GEM00_x-GEM10_x (cm)"); 
	DiffX_gem_pi0_hist->SetTitle("bggen #pi^{0}"); 
	DiffX_gem_pi0_hist->GetYaxis()->SetTitle("event"); 
	DiffX_gem_pi0_hist->Draw(); 
	DiffX_gem_pi0_beamline_hist->SetLineColor(2); 
	DiffX_gem_pi0_beamline_hist->Scale(DiffX_gem_pi0_hist->Integral()/DiffX_gem_pi0_beamline_hist->Integral()); 
	DiffX_gem_pi0_beamline_hist->Draw("same"); 
	leg1->Draw("text same");
	c[2]->cd(2);
	DiffY_gem_pi0_hist->SetLineColor(1); 
	DiffY_gem_pi0_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)"); 
	DiffY_gem_pi0_hist->SetTitle("bggen #pi^{0}"); 
	DiffY_gem_pi0_hist->GetYaxis()->SetTitle("event"); 
	DiffY_gem_pi0_hist->Draw(); 
	DiffY_gem_pi0_beamline_hist->SetLineColor(2); 
	DiffY_gem_pi0_beamline_hist->Scale(DiffY_gem_pi0_hist->Integral()/DiffY_gem_pi0_beamline_hist->Integral()); 
	DiffY_gem_pi0_beamline_hist->Draw("same"); 
	leg1->Draw("text same");
	c[3] = new TCanvas("c[3]","c[3]",1000,1000);
	c[3]->Divide(1,2);
	c[3]->cd(1);
	DiffX_gem_pim_hist->SetLineColor(1); 
	DiffX_gem_pim_hist->GetXaxis()->SetTitle("GEM00_x-GEM10_x (cm)"); 
	DiffX_gem_pim_hist->SetTitle("bggen #pi^{-}"); 
	DiffX_gem_pim_hist->GetYaxis()->SetTitle("event"); 
	DiffX_gem_pim_hist->Draw(); 
	DiffX_gem_pim_beamline_hist->SetLineColor(2); 
	DiffX_gem_pim_beamline_hist->Scale(DiffX_gem_pim_hist->Integral()/DiffX_gem_pim_beamline_hist->Integral()); 
	DiffX_gem_pim_beamline_hist->Draw("same"); 
	leg1->Draw("text same");
	c[3]->cd(2);
	DiffY_gem_pim_hist->SetLineColor(1); 
	DiffY_gem_pim_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)"); 
	DiffY_gem_pim_hist->SetTitle("bggen #pi^{-}"); 
	DiffY_gem_pim_hist->GetYaxis()->SetTitle("event"); 
	DiffY_gem_pim_hist->Draw(); 
	DiffY_gem_pim_beamline_hist->SetLineColor(2); 
	DiffY_gem_pim_beamline_hist->Scale(DiffY_gem_pim_hist->Integral()/DiffY_gem_pim_beamline_hist->Integral()); 
	DiffY_gem_pim_beamline_hist->Draw("same"); 
	leg1->Draw("text same");
	c[4] = new TCanvas("c[4]","c[4]",1000,1000);
	c[4]->Divide(1,2);
	c[4]->cd(1);
	DiffX_gem_beamOnT_hist->SetLineColor(1); 
	DiffX_gem_beamOnT_hist->GetXaxis()->SetTitle("GEM00_x-GEM10_x (cm)"); 
	DiffX_gem_beamOnT_hist->SetTitle("beam on target"); 
	DiffX_gem_beamOnT_hist->GetYaxis()->SetTitle("event"); 
	DiffX_gem_beamOnT_hist->Draw(); 
	DiffX_gem_beamOnT_beamline_hist->SetLineColor(2); 
	DiffX_gem_beamOnT_beamline_hist->Scale(DiffX_gem_beamOnT_hist->Integral()/DiffX_gem_beamOnT_beamline_hist->Integral()); 
	DiffX_gem_beamOnT_beamline_hist->Draw("same"); 
	leg1->Draw("text same");
	c[4]->cd(2);
	DiffY_gem_beamOnT_hist->SetLineColor(1); 
	DiffY_gem_beamOnT_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)"); 
	DiffY_gem_beamOnT_hist->SetTitle("beam on target"); 
	DiffY_gem_beamOnT_hist->GetYaxis()->SetTitle("event"); 
	DiffY_gem_beamOnT_hist->Draw(); 
	DiffY_gem_beamOnT_beamline_hist->SetLineColor(2); 
	DiffY_gem_beamOnT_beamline_hist->Scale(DiffY_gem_beamOnT_hist->Integral()/DiffY_gem_beamOnT_beamline_hist->Integral()); 
	DiffY_gem_beamOnT_beamline_hist->Draw("same"); 
	leg1->Draw("text same");
	c[5] = new TCanvas("c[5]","c[5]",1000,1000);
	c[5]->Divide(2,3);
	c[5]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_hist->SetTitle("eAll");
	Diff_gem_hist->Draw("COLZ");
	c[5]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_beamline_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_beamline_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_beamline_hist->SetTitle("eAll with beamline");
	Diff_gem_beamline_hist->Draw("COLZ");
	c[5]->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_pip_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_pip_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_pip_hist->SetTitle("bggen #pi^{+}");
	Diff_gem_pip_hist->Draw("COLZ");
	c[5]->cd(4);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_pip_beamline_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_pip_beamline_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_pip_beamline_hist->SetTitle("bggen #pi^{+} with beamline");
	Diff_gem_pip_beamline_hist->Draw("COLZ");
	c[5]->cd(5);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_pi0_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_pi0_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_pi0_hist->SetTitle("bggen #pi^{0}");
	Diff_gem_pi0_hist->Draw("COLZ");
	c[5]->cd(6);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_pi0_beamline_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_pi0_beamline_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_pi0_beamline_hist->SetTitle("bggen #pi^{0} with beamline");
	Diff_gem_pi0_beamline_hist->Draw("COLZ");
	c[6] = new TCanvas("c[6]","c[6]",1000,1000);
	c[6]->Divide(2,2);
	c[6]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_pim_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_pim_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_pim_hist->SetTitle("bggen #pi^{-}");
	Diff_gem_pim_hist->Draw("COLZ");
	c[6]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_pim_beamline_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_pim_beamline_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_pim_beamline_hist->SetTitle("bggen #pi^{-} with beamline");
	Diff_gem_pim_beamline_hist->Draw("COLZ");
	c[6]->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_beamOnT_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_beamOnT_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_beamOnT_hist->SetTitle("beam on target");
	Diff_gem_beamOnT_hist->Draw("COLZ");
	c[6]->cd(4);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_beamOnT_beamline_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_beamOnT_beamline_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_beamOnT_beamline_hist->SetTitle("beam on target with beamline");
	Diff_gem_beamOnT_beamline_hist->Draw("COLZ");
	for(int a=0;a<7;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_trigger_gem_comparison.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
