
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

void plot_rate_sangle(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_sangle/HallC_beamtest_bggen_LH2_pip_sangle_filenum9520_8deg_reduce_tree_rate.root");
	//TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e9_8deg_80uA_target_chamber_zhiwen_reduce_tree_rate_test.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_sangle/HallC_beamtest_bggen_LH2_pim_8deg_filenum10270_reduce_tree_rate.root");
	//TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e9_8deg_80uA_targetonly_reduce_tree_rate.root");
	//TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e9_8deg_80uA_target_chamber_reduce_tree_rate_test.root");
	TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_sangle/HallC_beamtest_bggen_LH2_pi0_8deg_filenum11840_reduce_tree_rate.root");
	TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_sangle/HallC_beamtest_eAll_sangle_8deg_filenum100_output_Nphe_Q2cut_001GeV.root");
	TFile *f8 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_0.96e9_8deg_80uA_reduce_tree_rate_Q2L1.root");
	//TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e9_8deg_80uA_target_chamber_zhiwen_reduce_tree_rate_test.root");
	TTree *tree_pip = (TTree*) f5->Get("T");
	TTree *tree_pim = (TTree*) f4->Get("T");
	TTree *tree_pi0 = (TTree*) f6->Get("T"); //abs(phicut) <5 deg
	TTree *tree_eAll = (TTree*) f7->Get("T");
	TTree *tree_beam = (TTree*) f8->Get("T");
	const int rebinfac=4;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
        tree_pip->Draw("ShowerSum>>shower_pip(4000,0,2000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("ShowerSum>>shower_pim(4000,0,2000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_pi0->Draw("ShowerSum>>shower_pi0(4000,0,2000)","rate*( ShowerSum>0)","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("ShowerSum>>shower_eAll(4000,0,2000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("ShowerSum>>shower_beam(4000,0,2000)","rate*(ShowerSum>0)","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");
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
        /*tree_pip->Draw("ShowerSum>>shower_pip(4000,0,2000)","rate*(ShowerSum>600)","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("ShowerSum>>shower_pim(4000,0,2000)","rate*(ShowerSum>600)","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_pi0->Draw("ShowerSum>>shower_pi0(4000,0,2000)","rate*( ShowerSum>600)","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("ShowerSum>>shower_eAll(4000,0,2000)","rate*(ShowerSum>600)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("ShowerSum>>shower_beam(4000,0,2000)","rate*(ShowerSum>600)","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");
        tree_pip->Draw("Npesum>>Npesum_pip(100,0,100)","rate*(ShowerSum>600)","goff");
	TH1F *Npesum_pip_hist = (TH1F*)gROOT->FindObject("Npesum_pip");
        tree_pim->Draw("Npesum>>Npesum_pim(100,0,100)","rate*(ShowerSum>600)","goff");
	TH1F *Npesum_pim_hist = (TH1F*)gROOT->FindObject("Npesum_pim");
        tree_pi0->Draw("Npesum>>Npesum_pi0(100,0,100)","rate*( ShowerSum>600)","goff");
	TH1F *Npesum_pi0_hist = (TH1F*)gROOT->FindObject("Npesum_pi0");
        tree_eAll->Draw("Npesum>>Npesum_eAll(100,0,100)","rate*(ShowerSum>600)","goff");
	TH1F *Npesum_eAll_hist = (TH1F*)gROOT->FindObject("Npesum_eAll");
        tree_beam->Draw("Npesum>>Npesum_beam(100,0,100)","rate*(ShowerSum>600)","goff");
	TH1F *Npesum_beam_hist = (TH1F*)gROOT->FindObject("Npesum_beam");*/
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
        shower_eAll_hist->Draw("same HIST");
        shower_eAll_hist->Rebin(rebinfac);
        double rate_eAll= shower_eAll_hist->Integral();
  TLegend *leg8 = new TLegend(0.45,0.6,0.8,0.88);
  leg8->AddEntry(shower_eAll_hist,Form("eAll*1000; total rate=%f Hz",rate_eAll),"l");
  leg8->AddEntry(shower_pim_hist,Form("bggen #pi^{-}; total rate=%f kHz",rate_pim),"l");
  leg8->AddEntry(shower_pip_hist,Form("bggen #pi^{+}; total rate=%f kHz",rate_pip),"l");
  leg8->AddEntry(shower_pi0_hist,Form("bggen #pi^{0}; total rate=%f kHz",rate_pi0),"l");
  leg8->AddEntry(shower_beam_hist,Form("BeamOnTarget; total rate=%f kHz",rate_proton),"l");
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
        Npesum_eAll_hist->Draw("same HIST");
  TLegend *leg7 = new TLegend(0.45,0.6,0.8,0.88);
  leg7->AddEntry(Npesum_eAll_hist,Form("from eAll*1000"),"l");
  leg7->AddEntry(Npesum_pim_hist,Form("from bggen #pi^{-}"),"l");
  leg7->AddEntry(Npesum_pip_hist,Form("from bggen #pi^{+}"),"l");
  leg7->AddEntry(Npesum_pi0_hist,Form("from bggen #pi^{0}"),"l");
  leg7->AddEntry(Npesum_beam_hist,Form("from BeamOnTarget LH2"),"l");
  leg7->SetTextSize(0.03);
  leg7->SetBorderSize(0);
  leg7->SetFillColor(0);
  leg7->Draw("text same");
	for(int a=0;a<2;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_comparison_threshod_rate.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
