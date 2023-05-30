
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
	TFile *f1 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.0976e9_7deg_5uA_5x10SC_r20m_cfoil_reduce_tree_rate_gem1_Etotalcut_debug.root");
	TFile *f2 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_5uA_4SCsurvey_7deg_r20m_carbon/HallC_beamtest_BeamOnTarget_1e9_7degsurvey_5uA_4SC_r20m_cfoil_reduce_tree_rate_gem1_Etotalcut_debug.root");
	TFile *f3 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_5uA_4SCsurvey_7deg_r20m_carbon_shielding/HallC_beamtest_BeamOnTarget_2e9_7degsurvey_5uA_4SC_r20m_cfoil_shielding_reduce_tree_rate_gem1_Etotalcut.root");
	TTree *tree_nosh = (TTree*) f1->Get("T");
	TTree *tree_new = (TTree*) f2->Get("T");
	TTree *tree_new_sh = (TTree*) f3->Get("T"); //abs(phicut) <5 deg
	const int rebinfac=1;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
        tree_nosh->Draw("SC0_Eendsum>>SC0_hist(200,0,10)","rate","goff");
	TH1F *SC0_nosh_hist = (TH1F*)gROOT->FindObject("SC0_hist");
        tree_new->Draw("SC_A_Eendsum>>SCA_hist(200,0,10)","rate","goff");
	TH1F *SC0_new_hist = (TH1F*)gROOT->FindObject("SCA_hist");
        tree_new_sh->Draw("SC_A_Eendsum>>SCA_sh_hist(200,0,10)","rate","goff");
	TH1F *SC0_new_sh_hist = (TH1F*)gROOT->FindObject("SCA_sh_hist");
	TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        SC0_new_sh_hist->SetLineColor(1);
        SC0_new_sh_hist->GetXaxis()->SetTitle("SC_A Eend (MeV)");
        SC0_new_sh_hist->SetTitle("10.6 GeV 5 #muA C-foil target 7 degrees ");
        SC0_new_sh_hist->GetYaxis()->SetTitle("Rate (kHz)");
        SC0_new_sh_hist->Scale(0.001);
        //SC0_new_sh_hist->GetYaxis()->SetRangeUser(1e-4,1e7);
        SC0_new_sh_hist->Draw();
        double rate_SCA_sh= SC0_new_sh_hist->Integral();
        SC0_new_hist->SetLineColor(2);
        SC0_new_hist->Scale(0.001);
        SC0_new_hist->Draw("same HIST");
        double rate_SCA= SC0_new_hist->Integral();
        SC0_nosh_hist->SetLineColor(4);
        SC0_nosh_hist->Scale(0.001);
        SC0_nosh_hist->Draw("same HIST");
        double rate_SC0= SC0_nosh_hist->Integral();
  TLegend *leg8 = new TLegend(0.45,0.6,0.8,0.88);
  leg8->AddEntry(SC0_new_sh_hist,Form("new with Pb shielding; total rate=%f kHz",rate_SCA_sh),"l");
  leg8->AddEntry(SC0_new_hist,Form("new without pb shielding; total rate=%f kHz",rate_SCA),"l");
  leg8->AddEntry(SC0_nosh_hist,Form("old; total rate=%f kHz",rate_SC0),"l");
  leg8->SetTextSize(0.03);
  leg8->SetBorderSize(0);
  leg8->SetFillColor(0);
  leg8->Draw("text same");
	for(int a=0;a<1;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_simulation_debug.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
