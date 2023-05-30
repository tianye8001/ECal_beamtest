
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

void plot_EC_gem_compare_pip(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f1 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_6090deg/HallC_beamtest_bggen_LH2_pip_filenum17790_reduce_tree_rate.root");
	TFile *f2 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_phicut/HallC_beamtest_bggen_LH2_pip_phi5cut_filenum19890_reduce_tree_rate.root");
	TFile *f3 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_phicut_55/HallC_beamtest_bggen_LH2_pip_phicut_filenum3630_reduce_tree_rate.root");
	//TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip/output/HallC_beamtest_bggen_LH2_pip_newbeamline_filenum23450_reduce_tree_rate.root");
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_filenum19870_reduce_tree_rate.root");
	//TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip/HallC_beamtest_bggen_LH2_pip_filenum14050_nobeamline_reduce_tree_rate.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_nobeamline_filenum19720_reduce_tree_rate.root");
	TFile *f6 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_nobeamline_filenum19720_output_gem.root");
	TFile *f7 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_filenum19870_output_gem.root");
        TH1F *hit_PID_orig_gem1_nobeam= (TH1F*)f6->Get("hit_PID_orig_detector4");
        TH1F *hit_PID_gem1_nobeam= (TH1F*)f6->Get("hit_PID_detector4");
        TH1F *hit_PID_orig_gem2_nobeam= (TH1F*)f6->Get("hit_PID_orig_detector5");
        TH1F *hit_PID_gem2_nobeam= (TH1F*)f6->Get("hit_PID_detector5");
        TH1F *hit_PID_orig_gem1= (TH1F*)f7->Get("hit_PID_orig_detector4");
        TH1F *hit_PID_gem1= (TH1F*)f7->Get("hit_PID_detector4");
        TH1F *hit_PID_orig_gem2= (TH1F*)f7->Get("hit_PID_orig_detector5");
        TH1F *hit_PID_gem2= (TH1F*)f7->Get("hit_PID_detector5");
	TTree *tree_pip = (TTree*) f2->Get("T"); //abs(phicut) <5 deg
	TTree *tree_pip_beamline = (TTree*) f5->Get("T");
	TTree *tree_pi0 = (TTree*) f1->Get("T");// 60 deg <theta<90 deg abs(phi)<5deg
	TTree *tree_pip_phicut = (TTree*) f3->Get("T"); //abs(phicut) <5 deg
	TTree *tree_pip_nobeam = (TTree*) f4->Get("T"); //abs(phicut) <5 deg
	const int rebinfac=1;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
        tree_pip_nobeam->Draw("TMath::ACos(pz/sqrt(px*px+py*py+pz*pz))*180.0/TMath::Pi()>>hist_theta_nobeam(200,0,100)","GEM00_n>0 && GEM10_n>0");
	TH1F *theta_pip_nobeam_hist = (TH1F*)gROOT->FindObject("hist_theta_nobeam");
        tree_pip->Draw("TMath::ACos(pz/sqrt(px*px+py*py+pz*pz))*180.0/TMath::Pi()>>hist_theta(200,0,100)","GEM00_n>0 && GEM10_n>0");
	TH1F *theta_pip_hist = (TH1F*)gROOT->FindObject("hist_theta");
        tree_pi0->Draw("TMath::ACos(pz/sqrt(px*px+py*py+pz*pz))*180.0/TMath::Pi()>>hist_theta_thetacut(200,0,100)","GEM00_n>0 && GEM10_n>0");
	TH1F *theta_pip_thetacut_hist = (TH1F*)gROOT->FindObject("hist_theta_thetacut");
        tree_pip_beamline->Draw("TMath::ACos(pz/sqrt(px*px+py*py+pz*pz))*180.0/TMath::Pi()>>hist_theta_beamline(200,0,100)","GEM00_n>0 && GEM10_n>0");
	TH1F *theta_pip_beamline_hist = (TH1F*)gROOT->FindObject("hist_theta_beamline");
        tree_pip_phicut->Draw("TMath::ACos(pz/sqrt(px*px+py*py+pz*pz))*180.0/TMath::Pi()>>hist_theta_phicut(200,0,100)","GEM00_n>0 && GEM10_n>0");
	TH1F *theta_pip_phicut_hist = (TH1F*)gROOT->FindObject("hist_theta_phicut");

// phi angle
        tree_pip_nobeam->Draw("TMath::ATan2(py,px)*180.0/TMath::Pi()>>hist_phi_nobeam(400,-50,50)","GEM00_n>0 && GEM10_n>0");
	TH1F *phi_pip_nobeam_hist = (TH1F*)gROOT->FindObject("hist_phi_nobeam");
        tree_pip->Draw("TMath::ATan2(py,px)*180.0/TMath::Pi()>>hist_phi(400,-50,50)","GEM00_n>0 && GEM10_n>0");
	TH1F *phi_pip_hist = (TH1F*)gROOT->FindObject("hist_phi");
        tree_pi0->Draw("TMath::ATan2(py,px)*180.0/TMath::Pi()>>hist_phi_thetacut(400,-50,50)","GEM00_n>0 && GEM10_n>0");
	TH1F *phi_pip_thetacut_hist = (TH1F*)gROOT->FindObject("hist_phi_thetacut");
        tree_pip_beamline->Draw("TMath::ATan2(py,px)*180.0/TMath::Pi()>>hist_phi_beamline(400,-50,50)","GEM00_n>0 && GEM10_n>0");
	TH1F *phi_pip_beamline_hist = (TH1F*)gROOT->FindObject("hist_phi_beamline");
        tree_pip_phicut->Draw("TMath::ATan2(py,px)*180.0/TMath::Pi()>>hist_phi_phicut(400,-50,50)","GEM00_n>0 && GEM10_n>0");
	TH1F *phi_pip_phicut_hist = (TH1F*)gROOT->FindObject("hist_phi_phicut");
	tree_pip ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pip_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip");
	tree_pip_beamline ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_beamline(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pip_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_beamline");
	tree_pi0 ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pi0(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pi0_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pi0");
	tree_pip ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_cut(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>0","goff");
	TH1F *DiffX_gem_pip_cut_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_cut");
	tree_pi0 ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pi0_cut(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>0","goff");
	TH1F *DiffX_gem_pi0_cut_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pi0_cut");
	tree_pip ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_cut2(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>5","goff");
	TH1F *DiffX_gem_pip_cut2_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_cut2");
	tree_pi0 ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pi0_cut2(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>5","goff");
	TH1F *DiffX_gem_pi0_cut2_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pi0_cut2");
	tree_pip ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_cut3(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>10","goff");
	TH1F *DiffX_gem_pip_cut3_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_cut3");
	tree_pi0 ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pi0_cut3(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>10","goff");
	TH1F *DiffX_gem_pi0_cut3_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pi0_cut3");
	tree_pip_phicut ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_phicut(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pip_phicut_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_phicut");

	tree_pip ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pip_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip");
	tree_pip_beamline ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_beamline(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pip_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_beamline");
	tree_pi0 ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pi0(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pi0_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pi0");
	tree_pip ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_cut(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>0","goff");
	TH1F *DiffY_gem_pip_cut_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_cut");
	tree_pip ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_cut2(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>5","goff");
	TH1F *DiffY_gem_pip_cut2_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_cut2");
	tree_pip ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_cut3(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>10","goff");
	TH1F *DiffY_gem_pip_cut3_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_cut3");
	tree_pi0 ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pi0_cut(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>0","goff");
	TH1F *DiffY_gem_pi0_cut_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pi0_cut");
	tree_pi0 ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pi0_cut2(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>5","goff");
	TH1F *DiffY_gem_pi0_cut2_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pi0_cut2");
	tree_pi0 ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pi0_cut3(25,-10,10)","GEM00_n>0 && GEM10_n>0 && PreSh_t>10","goff");
	TH1F *DiffY_gem_pi0_cut3_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pi0_cut3");
	tree_pip_phicut ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_phicut(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pip_phicut_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_phicut");
	// 2D plots
	tree_pip ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_pip(25,-10,10,25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_pip_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_pip");
	tree_pip_beamline ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_pip_beamline(25,-10,10,25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_pip_beamline_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_pip_beamline");
	tree_pi0 ->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)>>hist_gem_Diff_pi0(25,-10,10,25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH2F *Diff_gem_pi0_hist = (TH2F*)gROOT->FindObject("hist_gem_Diff_pi0");

	tree_pip ->Draw("PreSh_t>>hist_gem_presh_pip(200,0,100)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *PreSh_gem_pip_hist = (TH1F*)gROOT->FindObject("hist_gem_presh_pip");
	tree_pip_beamline ->Draw("PreSh_t>>hist_gem_presh_pip_beamline(200,0,100)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *PreSh_gem_pip_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_presh_pip_beamline");
	tree_pi0 ->Draw("PreSh_t>>hist_gem_presh_pi0(200,0,100)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *PreSh_gem_pi0_hist = (TH1F*)gROOT->FindObject("hist_gem_presh_pi0");
	TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	c[0]->Divide(1,2);
	c[0]->cd(1);
	DiffX_gem_pip_hist->SetLineColor(1); 
	DiffX_gem_pip_hist->GetXaxis()->SetTitle("GEM00_x-GEM10_x (cm)"); 
	DiffX_gem_pip_hist->SetTitle("bggen #pi^{+}"); 
	DiffX_gem_pip_hist->GetYaxis()->SetTitle("event"); 
	DiffX_gem_pip_hist->Draw(); 
	DiffX_gem_pip_beamline_hist->SetLineColor(2); 
	DiffX_gem_pip_beamline_hist->Scale(DiffX_gem_pip_hist->Integral()/DiffX_gem_pip_beamline_hist->Integral()); 
	DiffX_gem_pip_beamline_hist->Draw("same"); 
	DiffX_gem_pi0_hist->SetLineColor(4); 
	DiffX_gem_pi0_hist->Scale(DiffX_gem_pip_hist->Integral()/DiffX_gem_pi0_hist->Integral()); 
	DiffX_gem_pi0_hist->Draw("same"); 
	DiffX_gem_pip_phicut_hist->SetLineColor(6); 
	DiffX_gem_pip_phicut_hist->Scale(DiffX_gem_pip_hist->Integral()/DiffX_gem_pip_phicut_hist->Integral()); 
	DiffX_gem_pip_phicut_hist->Draw("same"); 
	TLegend *leg1 = new TLegend(0.6,0.6,0.88,0.88);
	leg1->AddEntry(DiffX_gem_pip_hist,"bggen #pi^{+}, #theta <90 deg and abs(#phi)<5","l");
	leg1->AddEntry(DiffX_gem_pip_phicut_hist,"bggen #pi^{+}, #theta <90 deg and abs(#phi)<55","l");
	leg1->AddEntry(DiffX_gem_pip_beamline_hist,"bggen #pi^{+}, #theta <90 deg","l");
	leg1->AddEntry(DiffX_gem_pi0_hist,"bggen #pi^{+}, 60deg <#theta <90 deg and abs(#phi)<5","l");
	leg1->SetTextSize(0.03);
	leg1->SetBorderSize(0);
	leg1->SetFillColor(0);
	leg1->Draw("text same");
	c[0]->cd(2);
	DiffY_gem_pip_hist->SetLineColor(1); 
	DiffY_gem_pip_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)"); 
	DiffY_gem_pip_hist->SetTitle("bggen #pi^{+}"); 
	DiffY_gem_pip_hist->GetYaxis()->SetTitle("event"); 
	DiffY_gem_pip_hist->Draw(); 
	DiffY_gem_pip_beamline_hist->SetLineColor(2); 
	DiffY_gem_pip_beamline_hist->Scale(DiffY_gem_pip_hist->Integral()/DiffY_gem_pip_beamline_hist->Integral()); 
	DiffY_gem_pip_beamline_hist->Draw("same"); 
	DiffY_gem_pi0_hist->SetLineColor(4); 
	DiffY_gem_pi0_hist->Scale(DiffY_gem_pip_hist->Integral()/DiffY_gem_pi0_hist->Integral()); 
	DiffY_gem_pi0_hist->Draw("same"); 
	DiffY_gem_pip_phicut_hist->SetLineColor(6); 
	DiffY_gem_pip_phicut_hist->Scale(DiffY_gem_pip_hist->Integral()/DiffY_gem_pip_phicut_hist->Integral()); 
	DiffY_gem_pip_phicut_hist->Draw("same"); 
	leg1->Draw("text same");
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
	c[1]->Divide(2,2);
	c[1]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_pip_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_pip_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_pip_hist->SetTitle("bggen #pi^{+}");
	Diff_gem_pip_hist->Draw("COLZ");
	c[1]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_pip_beamline_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_pip_beamline_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_pip_beamline_hist->SetTitle("bggen #pi^{+} with beamline");
	Diff_gem_pip_beamline_hist->Draw("COLZ");
	c[1]->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	Diff_gem_pi0_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)");
	Diff_gem_pi0_hist->GetYaxis()->SetTitle("GEM00_x-GEM10_x (cm)");
	Diff_gem_pi0_hist->SetTitle("bggen #pi^{0}");
	Diff_gem_pi0_hist->Draw("COLZ");
	c[2] = new TCanvas("c[2]","c[2]",1000,1000);
	c[2]->Divide(1,2);
        c[2]->cd(1);
	DiffX_gem_pip_cut_hist->SetLineColor(1); 
	DiffX_gem_pip_cut_hist->GetXaxis()->SetTitle("GEM00_x-GEM10_x (cm)"); 
	DiffX_gem_pip_cut_hist->SetTitle("bggen #pi^{+}"); 
	DiffX_gem_pip_cut_hist->GetYaxis()->SetTitle("event"); 
	DiffX_gem_pip_cut_hist->Draw(); 
	DiffX_gem_pi0_cut_hist->SetLineColor(2); 
	DiffX_gem_pi0_cut_hist->Scale(DiffX_gem_pip_cut_hist->Integral()/DiffX_gem_pi0_cut_hist->Integral()); 
	DiffX_gem_pi0_cut_hist->Draw("same"); 
	DiffX_gem_pi0_cut2_hist->SetLineColor(4); 
	DiffX_gem_pi0_cut2_hist->Scale(DiffX_gem_pip_cut_hist->Integral()/DiffX_gem_pi0_cut2_hist->Integral()); 
	DiffX_gem_pi0_cut2_hist->Draw("same"); 
	DiffX_gem_pi0_cut3_hist->SetLineColor(6); 
	DiffX_gem_pi0_cut3_hist->Scale(DiffX_gem_pip_cut_hist->Integral()/DiffX_gem_pi0_cut3_hist->Integral()); 
	DiffX_gem_pi0_cut3_hist->Draw("same"); 
	DiffX_gem_pip_cut2_hist->SetLineColor(7); 
	DiffX_gem_pip_cut2_hist->Scale(DiffX_gem_pip_cut_hist->Integral()/DiffX_gem_pip_cut2_hist->Integral()); 
	DiffX_gem_pip_cut2_hist->Draw("same"); 
	DiffX_gem_pip_cut3_hist->SetLineColor(8); 
	DiffX_gem_pip_cut3_hist->Scale(DiffX_gem_pip_cut_hist->Integral()/DiffX_gem_pip_cut3_hist->Integral()); 
	DiffX_gem_pip_cut3_hist->Draw("same"); 
	TLegend *leg2 = new TLegend(0.6,0.6,0.88,0.88);
	leg2->AddEntry(DiffX_gem_pip_cut_hist,"bggen #pi^{+}, #theta <90 deg, abs(#phi)<5,PreSh_t>0 MeV","l");
	leg2->AddEntry(DiffX_gem_pip_cut2_hist,"bggen #pi^{+}, #theta <90 deg, abs(#phi)<5,PreSh_t>5 MeV ","l");
	leg2->AddEntry(DiffX_gem_pip_cut3_hist,"bggen #pi^{+}, #theta <90 deg, abs(#phi)<5,PreSh_t>10 MeV","l");
	leg2->AddEntry(DiffX_gem_pi0_cut_hist,"bggen #pi^{+}, 60deg <#theta <90 deg and abs(#phi)<5 PreSh_t>0 MeV","l");
	leg2->AddEntry(DiffX_gem_pi0_cut2_hist,"bggen #pi^{+}, 60deg <#theta <90 deg and abs(#phi)<5 PreSh_t>5 MeV","l");
	leg2->AddEntry(DiffX_gem_pi0_cut3_hist,"bggen #pi^{+}, 60deg <#theta <90 deg and abs(#phi)<5 PreSh_t>10 MeV","l");
	leg2->SetTextSize(0.03);
	leg2->SetBorderSize(0);
	leg2->SetFillColor(0);
	leg2->Draw("text same");
        c[2]->cd(2);
	DiffY_gem_pip_cut_hist->SetLineColor(1); 
	DiffY_gem_pip_cut_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)"); 
	DiffY_gem_pip_cut_hist->SetTitle("bggen #pi^{+}"); 
	DiffY_gem_pip_cut_hist->GetYaxis()->SetTitle("event"); 
	DiffY_gem_pip_cut_hist->Draw(); 
	DiffY_gem_pi0_cut_hist->SetLineColor(2); 
	DiffY_gem_pi0_cut_hist->Scale(DiffY_gem_pip_cut_hist->Integral()/DiffY_gem_pi0_cut_hist->Integral()); 
	DiffY_gem_pi0_cut_hist->Draw("same"); 
	DiffY_gem_pi0_cut2_hist->SetLineColor(4); 
	DiffY_gem_pi0_cut2_hist->Scale(DiffY_gem_pip_cut_hist->Integral()/DiffY_gem_pi0_cut2_hist->Integral()); 
	DiffY_gem_pi0_cut2_hist->Draw("same"); 
	DiffY_gem_pi0_cut3_hist->SetLineColor(6); 
	DiffY_gem_pi0_cut3_hist->Scale(DiffY_gem_pip_cut_hist->Integral()/DiffY_gem_pi0_cut3_hist->Integral()); 
	DiffY_gem_pi0_cut3_hist->Draw("same"); 
	DiffY_gem_pip_cut2_hist->SetLineColor(7); 
	DiffY_gem_pip_cut2_hist->Scale(DiffY_gem_pip_cut_hist->Integral()/DiffY_gem_pip_cut2_hist->Integral()); 
	DiffY_gem_pip_cut2_hist->Draw("same"); 
	DiffY_gem_pip_cut3_hist->SetLineColor(8); 
	DiffY_gem_pip_cut3_hist->Scale(DiffY_gem_pip_cut_hist->Integral()/DiffY_gem_pip_cut3_hist->Integral()); 
	DiffY_gem_pip_cut3_hist->Draw("same"); 
	leg2->Draw("text same");
	c[3] = new TCanvas("c[3]","c[3]",1000,1000);
	gPad->SetLogy();
        PreSh_gem_pip_hist->SetLineColor(1);
	PreSh_gem_pip_hist->GetXaxis()->SetTitle("preshower_depE (MeV)"); 
	PreSh_gem_pip_hist->SetTitle("bggen #pi^{+}"); 
	PreSh_gem_pip_hist->GetYaxis()->SetTitle("event"); 
        PreSh_gem_pip_hist->Draw();
        PreSh_gem_pip_beamline_hist->SetLineColor(2);
        PreSh_gem_pip_beamline_hist->Draw("same");
        PreSh_gem_pi0_hist->SetLineColor(4);
        PreSh_gem_pi0_hist->Draw("same");
	TLegend *leg3 = new TLegend(0.6,0.6,0.85,0.88);
	leg3->AddEntry(PreSh_gem_pi0_hist,"bggen #pi^{+}, #theta <90 deg, abs(#phi)<5","l");
	leg3->AddEntry(PreSh_gem_pip_hist,"bggen #pi^{+}, 60deg <#theta <90 deg and abs(#phi)<5","l");
	leg3->AddEntry(PreSh_gem_pip_beamline_hist,"bggen #pi^{+},#theta <90 deg","l");
	leg3->SetTextSize(0.03);
	leg3->SetBorderSize(0);
	leg3->SetFillColor(0);
	leg3->Draw("text same");
	c[4] = new TCanvas("c[4]","c[4]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        phi_pip_nobeam_hist->SetLineColor(1);
        phi_pip_nobeam_hist->GetXaxis()->SetTitle("#phi deg");
        phi_pip_nobeam_hist->GetYaxis()->SetTitle("Event");
        phi_pip_nobeam_hist->Draw();
        phi_pip_hist->SetLineColor(2);
	phi_pip_hist->Scale(phi_pip_nobeam_hist->Integral()/phi_pip_hist->Integral()); 
        phi_pip_hist->Draw("same");
        phi_pip_beamline_hist->SetLineColor(4);
	phi_pip_beamline_hist->Scale(phi_pip_nobeam_hist->Integral()/phi_pip_beamline_hist->Integral()); 
        phi_pip_beamline_hist->Draw("same");
        phi_pip_thetacut_hist->SetLineColor(6);
	phi_pip_thetacut_hist->Scale(phi_pip_nobeam_hist->Integral()/phi_pip_thetacut_hist->Integral()); 
        phi_pip_thetacut_hist->Draw("same");
        phi_pip_phicut_hist->SetLineColor(7);
	phi_pip_phicut_hist->Scale(phi_pip_nobeam_hist->Integral()/phi_pip_phicut_hist->Integral()); 
        phi_pip_phicut_hist->Draw("same");
	TLegend *leg4 = new TLegend(0.12,0.6,0.4,0.88);
	leg4->AddEntry(phi_pip_hist,"bggen #pi^{+}, #theta <90 deg, abs(#phi)<5","l");
	leg4->AddEntry(phi_pip_phicut_hist,"bggen #pi^{+}, #theta <90 deg, abs(#phi)<55","l");
	leg4->AddEntry(phi_pip_thetacut_hist,"bggen #pi^{+}, 60deg <#theta <90 deg and abs(#phi)<5","l");
	leg4->AddEntry(phi_pip_beamline_hist,"bggen #pi^{+},#theta <90 deg","l");
	leg4->AddEntry(phi_pip_nobeam_hist,"bggen #pi^{+},#theta <90 deg nobeamline","l");
	leg4->SetTextSize(0.03);
	leg4->SetBorderSize(0);
	leg4->SetFillColor(0);
	leg4->Draw("text same");
	c[5] = new TCanvas("c[5]","c[5]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        theta_pip_nobeam_hist->SetLineColor(1);
        theta_pip_nobeam_hist->GetXaxis()->SetTitle("#theta deg");
        theta_pip_nobeam_hist->GetYaxis()->SetTitle("Event");
        theta_pip_nobeam_hist->Draw();
        theta_pip_hist->SetLineColor(2);
	theta_pip_hist->Scale(theta_pip_nobeam_hist->Integral()/theta_pip_hist->Integral()); 
        theta_pip_hist->Draw("same");
        theta_pip_beamline_hist->SetLineColor(4);
	theta_pip_beamline_hist->Scale(theta_pip_nobeam_hist->Integral()/theta_pip_beamline_hist->Integral()); 
        theta_pip_beamline_hist->Draw("same");
        theta_pip_thetacut_hist->SetLineColor(6);
	theta_pip_thetacut_hist->Scale(theta_pip_nobeam_hist->Integral()/theta_pip_thetacut_hist->Integral()); 
        theta_pip_thetacut_hist->Draw("same");
        theta_pip_phicut_hist->SetLineColor(7);
	theta_pip_phicut_hist->Scale(theta_pip_nobeam_hist->Integral()/theta_pip_phicut_hist->Integral()); 
        theta_pip_phicut_hist->Draw("same");
	leg4->Draw("text same");
	c[6] = new TCanvas("c[6]","c[6]",1000,1000);
        c[6]->Divide(1,2);
        c[6]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        hit_PID_gem1_nobeam->SetLineColor(2);
        hit_PID_gem1_nobeam->GetXaxis()->SetTitle("PID");
        hit_PID_gem1_nobeam->GetYaxis()->SetTitle("rate (Hz)");
        hit_PID_gem1_nobeam->SetLineColor(2);
        hit_PID_gem1_nobeam->Draw("HIST");
        hit_PID_orig_gem1_nobeam->SetLineColor(1);
        hit_PID_orig_gem1_nobeam->Draw("same HIST");
        hit_PID_gem1->SetLineColor(4);
        hit_PID_gem1->Draw("same HIST");
        hit_PID_orig_gem1->SetLineColor(6);
        hit_PID_orig_gem1->Draw("same HIST");
	TLegend *leg5 = new TLegend(0.12,0.6,0.4,0.88);
	leg5->AddEntry(hit_PID_gem1_nobeam,"from bggen #pi^{+},detector only","l");
	leg5->AddEntry(hit_PID_orig_gem1_nobeam,"tid=1 from from bggen #pi^{+},detector only","l");
	leg5->AddEntry(hit_PID_gem1,"from bggen #pi^{+}","l");
	leg5->AddEntry(hit_PID_orig_gem1,"tid=1 from from bggen #pi^{+}","l");
	leg5->SetTextSize(0.03);
	leg5->SetBorderSize(0);
	leg5->SetFillColor(0);
	leg5->Draw("text same");
        c[6]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        hit_PID_gem2_nobeam->SetLineColor(2);
        hit_PID_gem2_nobeam->GetXaxis()->SetTitle("PID");
        hit_PID_gem2_nobeam->GetYaxis()->SetTitle("rate (Hz)");
        hit_PID_gem2_nobeam->Draw("HIST");
        hit_PID_orig_gem2_nobeam->SetLineColor(1);
        hit_PID_orig_gem2_nobeam->Draw("same HIST");
        hit_PID_gem2->SetLineColor(4);
        hit_PID_gem2->Draw("same HIST");
        hit_PID_orig_gem2->SetLineColor(6);
        hit_PID_orig_gem2->Draw("same HIST");
	leg5->Draw("text same");
	for(int a=4;a<7;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_trigger_gem_comparison_pip.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
