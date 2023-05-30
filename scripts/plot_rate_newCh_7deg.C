
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

void plot_rate_newCh(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_7deg_Cfoil/HallC_beamtest_bggen_Cfoil_pip_7deg_filenum2000_10.6GeV_reduce_tree_rate_gem_Etotalcut.root");
	//TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_filenum19870_reduce_tree_rate.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_7deg_Cfoil/HallC_beamtest_bggen_Cfoil_pim_7deg_filenum2000_10.6GeV_reduce_tree_rate_gem_Etotalcut.root");
	TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_7deg_Cfoil/HallC_beamtest_bggen_Cfoil_pi0_7deg_filenum2000_10.6GeV_reduce_tree_rate_gem_Etotalcut.root");
	TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_7deg_Cfoil/HallC_beamtest_eAll_Cfoil_7deg_filenum992_4.96e7_10.6GeV_reduce_tree_rate_gem_Etotalcut_1GeV.root");
	//TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_4.986e8_7deg_80uA_5x10SC_r10m_cfoil_reduce_tree_rate_gem_Etotalcut.root");
	TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.594e9_7deg_80uA_5x10SC_r10m_cfoil_10.6GeV_reduce_tree_rate_preshower_Etotalcut_e.root");
	TFile *f9 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.594e9_7deg_80uA_5x10SC_r10m_cfoil_10.6GeV_reduce_tree_rate_preshower_Etotalcut_gamma.root");
	TFile *f10 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.594e9_7deg_80uA_5x10SC_r10m_cfoil_10.6GeV_reduce_tree_rate_Etotalcut.root");
	TFile *f11 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.594e9_7deg_80uA_5x10SC_r10m_cfoil_10.6GeV_reduce_tree_rate_preshower_Etotalcut_all.root");
//	TFile *f9 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_dummy_80uA/HallC_beamtest_BeamOnTarget_1e10_dummy_80uA_newCh_reduce_tree_rate_test.root");
	TTree *tree_pip = (TTree*) f5->Get("T");
	TTree *tree_pim = (TTree*) f4->Get("T");
	TTree *tree_pi0 = (TTree*) f6->Get("T"); //abs(phicut) <5 deg
	TTree *tree_eAll = (TTree*) f7->Get("T");
	TTree *tree_beam = (TTree*) f8->Get("T");
	TTree *tree_beam_dum = (TTree*) f9->Get("T");
	TTree *tree_beam_all = (TTree*) f10->Get("T");
	TTree *tree_beam_neutron = (TTree*) f11->Get("T");
	const int rebinfac=1;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
        tree_pip->Draw("ShowerSum>>shower_pip(300,0,1500)","rate*( ShowerSum>0)","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("ShowerSum>>shower_pim(300,0,1500)","rate*( ShowerSum>0)","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_pi0->Draw("ShowerSum>>shower_pi0(300,0,1500)","rate*( ShowerSum>0)","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("ShowerSum>>shower_eAll(300,0,1500)","rate*( ShowerSum>0 && GEM00_Edep>35e-6 && GEM10_Edep>35e-6)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("ShowerSum>>shower_beam(300,0,1500)","rate*( ShowerSum>0)","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");
        tree_beam_dum->Draw("ShowerSum>>shower_beam_dum(300,0,1500)","rate*( ShowerSum>0)","goff");
	TH1F *shower_beam_dum_hist = (TH1F*)gROOT->FindObject("shower_beam_dum");
        tree_beam_all->Draw("ShowerSum>>shower_beam_all(300,0,1500)","rate*( ShowerSum>0 && ShowerSum<600)","goff");
	TH1F *shower_beam_all_hist = (TH1F*)gROOT->FindObject("shower_beam_all");
        tree_beam_neutron->Draw("ShowerSum>>shower_beam_neutron(300,0,1500)","rate*( ShowerSum>0)","goff");
	TH1F *shower_beam_neutron_hist = (TH1F*)gROOT->FindObject("shower_beam_neutron");
       /* tree_pip->Draw("ShowerSum>>shower_pip(300,0,1500)","rate*(ShowerSum>40 )","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("ShowerSum>>shower_pim(300,0,1500)","rate*(ShowerSum>40 )","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_pi0->Draw("ShowerSum>>shower_pi0(300,0,1500)","rate*(ShowerSum>40 )","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("ShowerSum>>shower_eAll(300,0,1500)","rate*(ShowerSum>40 )","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("ShowerSum>>shower_beam(300,0,1500)","rate*(ShowerSum>40 )","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");
        tree_beam_dum->Draw("ShowerSum>>shower_beam_dum(300,0,1500)","rate*(ShowerSum>40)","goff");
        TH1F *shower_beam_dum_hist = (TH1F*)gROOT->FindObject("shower_beam_dum");*/
	TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        shower_beam_hist->SetLineColor(6);
        shower_beam_hist->GetXaxis()->SetTitle("shower_sum Eend (MeV)");
        shower_beam_hist->SetTitle("10.6 GeV 5 #muA C-foil target 7 degrees ");
        shower_beam_hist->GetYaxis()->SetTitle("Rate (kHz)");
        shower_beam_hist->Scale(0.001);
        shower_beam_hist->GetYaxis()->SetRangeUser(1e-4,1e7);
        shower_beam_hist->Draw();
        double rate_proton= shower_beam_hist->Integral();
        shower_pip_hist->SetLineColor(2);
        shower_pip_hist->Scale(0.001);
        shower_pip_hist->Draw("same HIST");
        double rate_pip= shower_pip_hist->Integral();
        shower_pim_hist->SetLineColor(1);
        shower_pim_hist->Scale(0.001);
        shower_pim_hist->Draw("same HIST");
        double rate_pim= shower_pim_hist->Integral();
        shower_pi0_hist->SetLineColor(8);
        shower_pi0_hist->Scale(0.001);
        shower_pi0_hist->Draw("same HIST");
        double rate_pi0= shower_pi0_hist->Integral();
        shower_eAll_hist->SetLineColor(4);
        shower_eAll_hist->Scale(0.001);
        shower_eAll_hist->Draw("same HIST");
        double rate_eAll= shower_eAll_hist->Integral();
        shower_beam_dum_hist->SetLineColor(7);
        shower_beam_dum_hist->Scale(0.001);
        shower_beam_dum_hist->Draw("same HIST");
        double rate_beam= shower_beam_dum_hist->Integral();
        shower_beam_all_hist->SetLineColor(kOrange-3);
        shower_beam_all_hist->Scale(0.001);
        shower_beam_all_hist->Draw("same HIST");
        double rate_beam_all= shower_beam_all_hist->Integral();
        shower_beam_neutron_hist->SetLineColor(28);
        shower_beam_neutron_hist->Scale(0.001);
        shower_beam_neutron_hist->Draw("same HIST");
        double rate_beam_neutron= shower_beam_neutron_hist->Integral();
        //shower_beam_hist->Draw("same HIST");
        shower_beam_dum_hist->Draw("same HIST");
        shower_beam_hist->Draw("same HIST");
        shower_beam_neutron_hist->Draw("same HIST");
  TLegend *leg8 = new TLegend(0.45,0.6,0.8,0.88);
  leg8->AddEntry(shower_eAll_hist,Form("eAll; total rate=%f kHz",rate_eAll),"l");
  leg8->AddEntry(shower_pim_hist,Form("bggen #pi^{-}; total rate=%f kHz",rate_pim),"l");
  leg8->AddEntry(shower_pip_hist,Form("bggen #pi^{+}; total rate=%f kHz",rate_pip),"l");
  leg8->AddEntry(shower_pi0_hist,Form("bggen #pi^{0}; total rate=%f kHz",rate_pi0),"l");
  leg8->AddEntry(shower_beam_hist,Form("e^{#pm} at prelead from BeamOnTarget C-foil full; total rate=%f kHz",rate_proton),"l");
  leg8->AddEntry(shower_beam_dum_hist,Form("#gamma at prelead from BeamOnTarget C-foil full; total rate=%f kHz",rate_beam),"l");
  leg8->AddEntry(shower_beam_all_hist,Form("all from BeamOnTarget C-foil full; total rate=%f kHz",rate_beam_all),"l");
  leg8->AddEntry(shower_beam_neutron_hist,Form("all at prelead from BeamOnTarget C-foil full; total rate=%f kHz",rate_beam_neutron),"l");
  leg8->SetTextSize(0.03);
  leg8->SetBorderSize(0);
  leg8->SetFillColor(0);
  leg8->Draw("text same");
	for(int a=0;a<1;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_comparison_threshod_rate.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
