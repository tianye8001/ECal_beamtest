
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

void plot_rate_sangle_newCh(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	//TFile *f8 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_5uA_4SCsurvey_7deg_r20m_carbon_shielding/HallC_beamtest_BeamOnTarget_2e9_7degsurvey_5uA_4SC_r20m_cfoil_shielding_reduce_tree_rate_gem1_Etotalcut.root");
	TFile *f8 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_5uA_4SCsurvey_7deg_r20m_carbon/HallC_beamtest_BeamOnTarget_1e9_7degsurvey_5uA_4SC_r20m_cfoil_reduce_tree_rate_gem1_Etotalcut.root");
	//TFile *f8 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_5uA_4SCsurvey_7deg_r20m_carbon_shielding/HallC_beamtest_BeamOnTarget_2e9_7degsurvey_5uA_4SC_r20m_cfoil_shielding_reduce_tree_rate_GEM00_Etotalcut_electron.root");
	TTree *tree_beam = (TTree*) f8->Get("T");
	const int rebinfac=10;
        /*tree_beam->Draw("2*SC_A_Eendsum>>beam_SCA(1000,0,20)","rate*(2*SC_A_Eendsum>1.75)","goff");
	TH1F *SCA_beam_hist = (TH1F*)gROOT->FindObject("beam_SCA");
        tree_beam->Draw("SC_C_Eendsum>>beam_SCC(1000,0,20)","rate*(SC_C_Eendsum>1.75)","goff");
	TH1F *SCC_beam_hist = (TH1F*)gROOT->FindObject("beam_SCC");
        tree_beam->Draw("SC_D_Eendsum>>beam_SCD(1000,0,20)","rate*(SC_D_Eendsum>1.75)","goff");
	TH1F *SCD_beam_hist = (TH1F*)gROOT->FindObject("beam_SCD");
        tree_beam->Draw("LASPD_Eendsum>>beam_LASPD(1000,0,20)","rate*(LASPD_Eendsum>1.75)","goff");
	TH1F *LASPD_beam_hist = (TH1F*)gROOT->FindObject("beam_LASPD");
        tree_beam->Draw("PreShSum>>beam_preshower(1000,0,20)","rate*(PreShSum>1.75)","goff");
	TH1F *preshower_beam_hist = (TH1F*)gROOT->FindObject("beam_preshower");*/
        tree_beam->Draw("2*SC_A_Eendsum>>beam_SCA(1000,0,20)","rate","goff");
	TH1F *SCA_beam_hist = (TH1F*)gROOT->FindObject("beam_SCA");
        tree_beam->Draw("SC_C_Eendsum>>beam_SCC(1000,0,20)","rate","goff");
	TH1F *SCC_beam_hist = (TH1F*)gROOT->FindObject("beam_SCC");
        tree_beam->Draw("SC_D_Eendsum>>beam_SCD(1000,0,20)","rate","goff");
	TH1F *SCD_beam_hist = (TH1F*)gROOT->FindObject("beam_SCD");
        tree_beam->Draw("LASPD_Eendsum>>beam_LASPD(1000,0,20)","rate","goff");
	TH1F *LASPD_beam_hist = (TH1F*)gROOT->FindObject("beam_LASPD");
        tree_beam->Draw("PreShSum>>beam_preshower(1000,0,20)","rate","goff");
	TH1F *preshower_beam_hist = (TH1F*)gROOT->FindObject("beam_preshower");
        TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        LASPD_beam_hist->SetLineColor(6);
        LASPD_beam_hist->GetXaxis()->SetTitle("Edep (MeV)");
        //LASPD_beam_hist->SetTitle("e^{-} hit at the front of GEM00 from BeamOnTarget");
        LASPD_beam_hist->SetTitle("everything from BeamOnTarget");
        LASPD_beam_hist->GetYaxis()->SetTitle("Rate (MHz/cm^{2})");
        LASPD_beam_hist->Scale(1.786e-9);
        LASPD_beam_hist->Rebin(rebinfac);
        LASPD_beam_hist->GetYaxis()->SetRangeUser(1e-4,1e-1);
        LASPD_beam_hist->Draw("HISt");
        double rate_proton= LASPD_beam_hist->Integral(LASPD_beam_hist->GetXaxis()->FindBin(1.75),LASPD_beam_hist->GetXaxis()->FindBin(20))*560.;
       //double rate_proton= LASPD_beam_hist->Integral()*560.;
        SCD_beam_hist->SetLineColor(2);
        SCD_beam_hist->Scale(9.5447e-9);
        SCD_beam_hist->Rebin(rebinfac);
        SCD_beam_hist->Draw("same HIST");
        double rate_pip= SCD_beam_hist->Integral(SCD_beam_hist->GetXaxis()->FindBin(1.75),SCD_beam_hist->GetXaxis()->FindBin(20))*104.77;
        //double rate_pip= SCD_beam_hist->Integral()*104.77;
        SCC_beam_hist->SetLineColor(1);
        SCC_beam_hist->Scale(1.235e-8);
        SCC_beam_hist->Rebin(rebinfac);
        SCC_beam_hist->Draw("same HIST");
        double rate_pim= SCC_beam_hist->Integral(SCC_beam_hist->GetXaxis()->FindBin(1.75),SCC_beam_hist->GetXaxis()->FindBin(20))*81.;
       //double rate_pim= SCC_beam_hist->Integral()*81.;
        SCA_beam_hist->SetLineColor(kOrange-3);
        SCA_beam_hist->Scale(2.667e-8);
        SCA_beam_hist->Rebin(rebinfac);
        SCA_beam_hist->Draw("same HIST");
        double rate_pi0= SCA_beam_hist->Integral(SCA_beam_hist->GetXaxis()->FindBin(1.75),SCA_beam_hist->GetXaxis()->FindBin(20))*37.5;
        //double rate_pi0= SCA_beam_hist->Integral()*37.5;
        preshower_beam_hist->SetLineColor(4);
        preshower_beam_hist->Scale(4.386e-9);
        preshower_beam_hist->Rebin(rebinfac);
        preshower_beam_hist->Draw("same HIST");
        double rate_eall= preshower_beam_hist->Integral(preshower_beam_hist->GetXaxis()->FindBin(1.75),preshower_beam_hist->GetXaxis()->FindBin(20))*228.;
        //double rate_eall= preshower_beam_hist->Integral()*228.;
  TLegend *leg8 = new TLegend(0.45,0.6,0.8,0.88);
  leg8->AddEntry(SCA_beam_hist,Form("2*SC_A; 0.5 MIP cut total rate=%f MHz",rate_pi0),"l");
  leg8->AddEntry(SCC_beam_hist,Form("SC_C; 0.5 MIP cut total rate=%f MHz",rate_pim),"l");
  leg8->AddEntry(LASPD_beam_hist,Form("LASPD; 0.5 MIP cut total rate=%f MHz",rate_proton),"l");
  leg8->AddEntry(SCD_beam_hist,Form("SC_D; 0.5 MIP cut total rate=%f MHz",rate_pip),"l");
  leg8->AddEntry(preshower_beam_hist,Form("PreShower; 0.5 MIP cut total rate=%f MHz",rate_eall),"l");
  /*leg8->AddEntry(SCA_beam_hist,"2*SC_A","l");
  leg8->AddEntry(SCC_beam_hist,"SC_C","l");
  leg8->AddEntry(LASPD_beam_hist,"LASPD","l");
  leg8->AddEntry(SCD_beam_hist,"SC_D","l");
  leg8->AddEntry(preshower_beam_hist,"PreShower","l");*/
  leg8->SetTextSize(0.03);
  leg8->SetBorderSize(0);
  leg8->SetFillColor(0);
  leg8->Draw("text same");
/*	c[1] = new TCanvas("c[1]","c[1]",1000,1000);

	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        Npesum_beam_hist->SetLineColor(6);
        Npesum_beam_hist->GetXaxis()->SetTitle("Npe");
        Npesum_beam_hist->GetYaxis()->SetTitle("Rate (kHz)");
        Npesum_beam_hist->GetYaxis()->SetRangeUser(1e-2,1e9);
        Npesum_beam_hist->Draw("HIST");
        Npesum_pip_hist->SetLineColor(2);
        Npesum_pip_hist->Draw("same HIST");
        Npesum_pim_hist->SetLineColor(1);
        Npesum_pim_hist->Draw("same HIST");
        Npesum_pi0_hist->SetLineColor(8);
        Npesum_pi0_hist->Draw("same HIST");
        Npesum_eAll_hist->SetLineColor(4);
        Npesum_eAll_hist->Draw("same HIST");
        Npesum_data_hist->SetLineColor(28);
        Npesum_data_hist->Draw("same HIST");
  TLegend *leg7 = new TLegend(0.45,0.6,0.8,0.88);
  leg7->AddEntry(Npesum_eAll_hist,Form("from eAll"),"l");
  //leg7->AddEntry(Npesum_pim_hist,Form("from bggen #pi^{-}"),"l");
  leg7->AddEntry(Npesum_pim_hist,Form("from BeamOnTarget with 2cm CC center cut"),"l");
//  leg7->AddEntry(Npesum_pip_hist,Form("from bggen #pi^{+}"),"l");
  leg7->AddEntry(Npesum_pip_hist,Form("from BeamOnTarget with bad mirror"),"l");
  leg7->AddEntry(Npesum_pi0_hist,Form("from bggen #pi^{0}"),"l");
  leg7->AddEntry(Npesum_beam_hist,Form("from BeamOnTarget LH2"),"l");
  leg7->AddEntry(Npesum_data_hist,Form("data run 3564_15"),"l");
  leg7->SetTextSize(0.03);
  leg7->SetBorderSize(0);
  leg7->SetFillColor(0);
  leg7->Draw("text same");*/
	/*c[2] = new TCanvas("c[2]","c[2]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        GEM00_beam_hist->SetLineColor(6);
        GEM00_beam_hist->GetXaxis()->SetTitle("Npe");
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
        GEM00_pi0_hist->SetLineColor(8);
        GEM00_pi0_hist->Scale(0.001);
        GEM00_pi0_hist->Draw("same HIST");
        double rate_pi0_gem= GEM00_pi0_hist->Integral();
        GEM00_eAll_hist->SetLineColor(4);
        GEM00_eAll_hist->Scale(0.001);
        GEM00_eAll_hist->Draw("same HIST");
        double rate_eAll_gem= GEM00_eAll_hist->Integral();
  TLegend *leg9 = new TLegend(0.45,0.6,0.8,0.88);
  leg9->AddEntry(GEM00_eAll_hist,Form("eAll; total rate=%f kHz",rate_eAll_gem),"l");
  leg9->AddEntry(GEM00_pim_hist,Form("bggen #pi^{-}; total rate=%f kHz",rate_pim_gem),"l");
  leg9->AddEntry(GEM00_pip_hist,Form("bggen #pi^{+}; total rate=%f kHz",rate_pip_gem),"l");
  leg9->AddEntry(GEM00_pi0_hist,Form("bggen #pi^{0}; total rate=%f kHz",rate_pi0_gem),"l");
  leg9->AddEntry(GEM00_beam_hist,Form("BeamOnTarget; total rate=%f kHz",rate_proton_gem),"l");
  leg9->SetTextSize(0.03);
  leg9->SetBorderSize(0);
  leg9->SetFillColor(0);
  leg9->Draw("text same");*/
	for(int a=0;a<1;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_comparison_SCs.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
