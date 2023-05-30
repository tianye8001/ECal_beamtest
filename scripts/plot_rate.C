
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

void plot_rate(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_filenum19870_reduce_tree_rate.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_80uA/HallC_beamtest_bggen_LH2_pim_80uA_filenum19880_reduce_tree_rate.root");
	TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_80uA/HallC_beamtest_bggen_LH2_pi0_80uA_filenum19880_reduce_tree_rate.root");
	TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_80uA/HallC_beamtest_eAll_80uA_filenum99_reduce_tree_rate.root");
	TFile *f8 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_TACH_80uA/HallC_beamtest_BeamOnTarget_1.884e10_80uA_reduce_tree_rate.root");
	TFile *f9 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_dummy_80uA/HallC_beamtest_BeamOnTarget_1.984e10_dummy_80uA_reduce_tree_rate.root");
	TTree *tree_pip = (TTree*) f5->Get("T");
	TTree *tree_pim = (TTree*) f4->Get("T");
	TTree *tree_pi0 = (TTree*) f6->Get("T"); //abs(phicut) <5 deg
	TTree *tree_eAll = (TTree*) f7->Get("T");
	TTree *tree_beam = (TTree*) f8->Get("T");
	TTree *tree_beam_dum = (TTree*) f9->Get("T");
	const int rebinfac=1;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
  /*      tree_pip->Draw("Shower_t>>shower_pip(400,0,200)","rate*(PreSh_t>0 && Shower_t>0)","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("Shower_t>>shower_pim(400,0,200)","rate*(PreSh_t>0 && Shower_t>0)","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_pi0->Draw("Shower_t>>shower_pi0(400,0,200)","rate*(PreSh_t>0 && Shower_t>0)","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("Shower_t>>shower_eAll(400,0,200)","rate*(PreSh_t>0 && Shower_t>0)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("Shower_t>>shower_beam(400,0,200)","rate*(PreSh_t>0 && Shower_t>0)","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");
        tree_beam_dum->Draw("Shower_t>>shower_beam_dum(400,0,200)","rate*(PreSh_t>0 && Shower_t>0)","goff");
	TH1F *shower_beam_dum_hist = (TH1F*)gROOT->FindObject("shower_beam_dum");*/
        tree_pip->Draw("Shower_t>>shower_pip(400,0,200)","rate*(PreSh_t>3.46 && Shower_t>5.8)","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("Shower_t>>shower_pim(400,0,200)","rate*(PreSh_t>3.46 && Shower_t>5.8)","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_pi0->Draw("Shower_t>>shower_pi0(400,0,200)","rate*(PreSh_t>3.46 && Shower_t>5.8)","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("Shower_t>>shower_eAll(400,0,200)","rate*(PreSh_t>3.46 && Shower_t>5.8)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("Shower_t>>shower_beam(400,0,200)","rate*(PreSh_t>3.46 && Shower_t>5.8)","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");
        tree_beam_dum->Draw("Shower_t>>shower_beam_dum(400,0,200)","rate*(PreSh_t>3.46 && Shower_t>5.8)","goff");
        TH1F *shower_beam_dum_hist = (TH1F*)gROOT->FindObject("shower_beam_dum");
	TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        shower_beam_hist->SetLineColor(6);
        shower_beam_hist->GetXaxis()->SetTitle("shower_t Eend (MeV)");
        shower_beam_hist->GetYaxis()->SetTitle("Rate (Hz)");
        shower_beam_hist->Scale(0.001);
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
        shower_eAll_hist->Draw("same HIST");
        double rate_eAll= shower_eAll_hist->Integral();
        shower_beam_dum_hist->SetLineColor(7);
        shower_beam_dum_hist->Scale(0.001);
        shower_beam_dum_hist->Draw("same HIST");
        double rate_beam= shower_beam_dum_hist->Integral();
  TLegend *leg8 = new TLegend(0.45,0.6,0.8,0.88);
  leg8->AddEntry(shower_eAll_hist,Form("eAll*1000; total rate=%f Hz",rate_eAll),"l");
  leg8->AddEntry(shower_pim_hist,Form("bggen #pi^{-}; total rate=%f kHz",rate_pim),"l");
  leg8->AddEntry(shower_pip_hist,Form("bggen #pi^{+}; total rate=%f kHz",rate_pip),"l");
  leg8->AddEntry(shower_pi0_hist,Form("bggen #pi^{0}; total rate=%f kHz",rate_pi0),"l");
  leg8->AddEntry(shower_beam_hist,Form("BeamOnTarget LH2; total rate=%f kHz",rate_proton),"l");
  leg8->AddEntry(shower_beam_dum_hist,Form("BeamOnTarget dummy; total rate=%f kHz",rate_beam),"l");
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
