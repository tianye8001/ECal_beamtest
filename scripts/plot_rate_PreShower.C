
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
	//TFile *f1 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_even_e_18deg_2/HallC_beamtest_even_e_18deg_filenumber11_reduce_tree_rate_gem1_Etotalcut_40uA_Q2100MeV.root");
	//TFile *f2 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_even_gamma_18deg_2/HallC_beamtest_even_gamma_18deg_filenum11_reduce_tree_rate_gem1_Etotalcut_40uA_Q2100MeV.root");
	TFile *f1 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_even_e_18deg_2/HallC_beamtest_even_e_18deg_filenumber101_leftcenter_reduce_tree_rate_gem1_Etotalcut_40uA_Q2100MeV.root");
	TFile *f2 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_even_gamma_18deg_2/HallC_beamtest_even_gamma_18deg_filenum101_leftcenter_reduce_tree_rate_gem1_Etotalcut_40uA_Q2100MeV.root");
	TTree *tree_e = (TTree*) f1->Get("T");
	TTree *tree_gamma = (TTree*) f2->Get("T");
	const int rebinfac=1;
        TCut pCut1 = "ShowerSum>450 && Shower_l/ShowerSum>0.85";
        tree_e->Draw("ShowerSum>>ShSum_e(1000,0,1000)","Shower_l/ShowerSum>0.85","goff");
	TH1F *ShowerSum_e_hist = (TH1F*)gROOT->FindObject("ShSum_e");
        tree_gamma->Draw("ShowerSum>>ShSum_gamma(1000,0,1000)","Shower_l/ShowerSum>0.85","goff");
	TH1F *ShowerSum_gamma_hist = (TH1F*)gROOT->FindObject("ShSum_gamma");
        tree_e->Draw("Shower_r>>Shr_e(1000,0,1000)","Shower_l/ShowerSum>0.85","goff");
	TH1F *ShowerR_e_hist = (TH1F*)gROOT->FindObject("Shr_e");
        tree_gamma->Draw("Shower_r>>Shr_gamma(1000,0,1000)","Shower_l/ShowerSum>0.85","goff");
	TH1F *ShowerR_gamma_hist = (TH1F*)gROOT->FindObject("Shr_gamma");
        tree_e->Draw("Shower_l>>Shl_e(1000,0,1000)","Shower_l/ShowerSum>0.85","goff");
	TH1F *ShowerL_e_hist = (TH1F*)gROOT->FindObject("Shl_e");
        tree_gamma->Draw("Shower_l>>Shl_gamma(1000,0,1000)","Shower_l/ShowerSum>0.85","goff");
	TH1F *ShowerL_gamma_hist = (TH1F*)gROOT->FindObject("Shl_gamma");
        tree_e->Draw("Shower_t>>Sht_e(1000,0,1000)","Shower_l/ShowerSum>0.85","goff");
	TH1F *ShowerT_e_hist = (TH1F*)gROOT->FindObject("Sht_e");
        tree_gamma->Draw("Shower_t>>Sht_gamma(1000,0,1000)","Shower_l/ShowerSum>0.85","goff");
	TH1F *ShowerT_gamma_hist = (TH1F*)gROOT->FindObject("Sht_gamma");
        tree_e->Draw("PreShSum>>PreSum_e_cut(1500,0,150)",pCut1,"goff");
	TH1F *PreShSum_e_cut_hist = (TH1F*)gROOT->FindObject("PreSum_e_cut");
        tree_gamma->Draw("ShowerSum>>PreSum_gamma_cut(1500,0,150)",pCut1,"goff");
	TH1F *PreShSum_gamma_cut_hist = (TH1F*)gROOT->FindObject("PreSum_gamma_cut");
        TCanvas *c[10];
        tree_e->Draw("PreShSum>>PreSum_e(1500,0,150)","","goff");
	TH1F *PreShSum_e_hist = (TH1F*)gROOT->FindObject("PreSum_e");
        tree_gamma->Draw("PreShSum>>PreSum_gamma(1500,0,150)","","goff");
	TH1F *PreShSum_gamma_hist = (TH1F*)gROOT->FindObject("PreSum_gamma");
        tree_e->Draw("PreSh_r>>Prer_e(800,0,80)","","goff");
	TH1F *PreShR_e_hist = (TH1F*)gROOT->FindObject("Prer_e");
        tree_gamma->Draw("PreSh_r>>Prer_gamma(800,0,80)","","goff");
	TH1F *PreShR_gamma_hist = (TH1F*)gROOT->FindObject("Prer_gamma");
        tree_e->Draw("PreSh_l>>Prel_e(800,0,80)","","goff");
	TH1F *PreShL_e_hist = (TH1F*)gROOT->FindObject("Prel_e");
        tree_gamma->Draw("PreSh_l>>Prel_gamma(800,0,80)","","goff");
	TH1F *PreShL_gamma_hist = (TH1F*)gROOT->FindObject("Prel_gamma");
        tree_e->Draw("PreSh_t>>Pret_e(800,0,80)","","goff");
	TH1F *PreShT_e_hist = (TH1F*)gROOT->FindObject("Pret_e");
        tree_gamma->Draw("PreSh_t>>Pret_gamma(800,0,80)","","goff");
	TH1F *PreShT_gamma_hist = (TH1F*)gROOT->FindObject("Pret_gamma");
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
        c[0]->Divide(2,2);
        c[0]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        ShowerSum_e_hist->SetLineColor(6);
        ShowerSum_e_hist->GetXaxis()->SetTitle("Edep (MeV)");
        ShowerSum_e_hist->SetTitle("5GeV e^{-} at ShowerowerSum");
        ShowerSum_e_hist->GetYaxis()->SetTitle("Event");
        ShowerSum_e_hist->GetYaxis()->SetRangeUser(1e-2,1e5);
        ShowerSum_e_hist->Rebin(rebinfac);
        ShowerSum_e_hist->Draw("HIST");
        ShowerSum_gamma_hist->SetLineColor(1);
        ShowerSum_gamma_hist->GetXaxis()->SetTitle("Edep (MeV)");
        ShowerSum_gamma_hist->SetTitle("5GeV #gamma at ShowerowerSum");
        ShowerSum_gamma_hist->GetYaxis()->SetTitle("Event");
        ShowerSum_gamma_hist->Rebin(rebinfac);
        ShowerSum_gamma_hist->Scale(ShowerSum_e_hist->Integral()/ShowerSum_gamma_hist->Integral());
        ShowerSum_gamma_hist->Draw("HIST same");
  TLegend *leg8 = new TLegend(0.15,0.7,0.4,0.88);
  leg8->AddEntry(ShowerSum_e_hist,"5GeV e^{-} in front of Showerower Shower_l/ShowerSum>0.85","l");
  leg8->AddEntry(ShowerSum_gamma_hist,"5GeV #gamma in front of Showerower Shower_l/ShowerSum>0.85","l");
  leg8->SetTextSize(0.03);
  leg8->SetBorderSize(0);
  leg8->SetFillColor(0);
  leg8->Draw("text same");
        c[0]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        ShowerL_e_hist->SetLineColor(6);
        ShowerL_e_hist->GetXaxis()->SetTitle("Edep (MeV)");
        ShowerL_e_hist->SetTitle("5GeV e^{-} at ShowerowerL");
        ShowerL_e_hist->GetYaxis()->SetTitle("Event");
        ShowerL_e_hist->GetYaxis()->SetRangeUser(1e-2,1e5);
        ShowerL_e_hist->Rebin(rebinfac);
        ShowerL_e_hist->Draw("HIST");
        ShowerL_gamma_hist->SetLineColor(1);
        ShowerL_gamma_hist->GetXaxis()->SetTitle("Edep (MeV)");
        ShowerL_gamma_hist->SetTitle("5GeV #gamma at ShowerowerL");
        ShowerL_gamma_hist->Scale(ShowerSum_e_hist->Integral()/ShowerL_gamma_hist->Integral());
        ShowerL_gamma_hist->GetYaxis()->SetTitle("Event");
        ShowerL_gamma_hist->Rebin(rebinfac);
        ShowerL_gamma_hist->Draw("HIST same");
  TLegend *leg18 = new TLegend(0.15,0.7,0.55,0.88);
  leg18->AddEntry(PreShL_e_hist,"5GeV e^{-} in front of PreShower Shower_l/ShowerSum>0.85","l");
  leg18->AddEntry(PreShL_gamma_hist,"5GeV #gamma in front of PreShower Shower_l/ShowerSum>0.85","l");
  leg18->SetTextSize(0.03);
  leg18->SetBorderSize(0);
  leg18->SetFillColor(0);
  leg18->Draw("text same");
  leg18->Draw("text same");
        c[0]->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        ShowerR_e_hist->SetLineColor(6);
        ShowerR_e_hist->GetXaxis()->SetTitle("Edep (MeV)");
        ShowerR_e_hist->SetTitle("5GeV e^{-} at ShowerowerR");
        ShowerR_e_hist->GetYaxis()->SetTitle("Event");
        ShowerR_e_hist->GetYaxis()->SetRangeUser(1e-2,1e5);
        ShowerR_e_hist->Rebin(rebinfac);
        ShowerR_e_hist->Draw("HIST");
        ShowerR_gamma_hist->SetLineColor(1);
        ShowerR_gamma_hist->GetXaxis()->SetTitle("Edep (MeV)");
        ShowerR_gamma_hist->SetTitle("5GeV #gamma at ShowerowerR");
        ShowerR_gamma_hist->Scale(ShowerSum_e_hist->Integral()/ShowerR_gamma_hist->Integral());
        ShowerR_gamma_hist->GetYaxis()->SetTitle("Event");
        ShowerR_gamma_hist->Rebin(rebinfac);
        ShowerR_gamma_hist->Draw("HIST same");
  leg18->Draw("text same");
        c[0]->cd(4);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        ShowerT_e_hist->SetLineColor(6);
        ShowerT_e_hist->GetXaxis()->SetTitle("Edep (MeV)");
        ShowerT_e_hist->SetTitle("5GeV e^{-} at ShowerowerT");
        ShowerT_e_hist->GetYaxis()->SetTitle("Event");
        ShowerT_e_hist->GetYaxis()->SetRangeUser(1e-2,1e5);
        ShowerT_e_hist->Rebin(rebinfac);
        ShowerT_e_hist->Draw("HIST");
        ShowerT_gamma_hist->SetLineColor(1);
        ShowerT_gamma_hist->GetXaxis()->SetTitle("Edep (MeV)");
        ShowerT_gamma_hist->SetTitle("5GeV #gamma at ShowerowerT");
        ShowerT_gamma_hist->GetYaxis()->SetTitle("Event");
        ShowerT_gamma_hist->Scale(ShowerSum_e_hist->Integral()/ShowerT_gamma_hist->Integral());
        ShowerT_gamma_hist->Rebin(rebinfac);
        ShowerT_gamma_hist->Draw("HIST same");
  leg18->Draw("text same");
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
        c[1]->Divide(2,2);
        c[1]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        PreShSum_e_hist->SetLineColor(6);
        PreShSum_e_hist->GetXaxis()->SetTitle("Edep (MeV)");
        PreShSum_e_hist->SetTitle("5GeV e^{-} at PreShowerSum");
        PreShSum_e_hist->GetYaxis()->SetTitle("Event");
        PreShSum_e_hist->GetYaxis()->SetRangeUser(1e-2,1e5);
        PreShSum_e_hist->Rebin(rebinfac);
        PreShSum_e_hist->Draw("HIST");
        PreShSum_gamma_hist->SetLineColor(1);
        PreShSum_gamma_hist->Rebin(rebinfac);
        PreShSum_gamma_hist->Scale(PreShSum_e_hist->Integral()/PreShSum_gamma_hist->Integral());
        PreShSum_gamma_hist->Draw("HIST same");
        PreShSum_gamma_cut_hist->SetLineColor(2);
        PreShSum_gamma_cut_hist->Rebin(rebinfac);
        //PreShSum_gamma_cut_hist->Draw("HIST same");
        PreShSum_e_cut_hist->SetLineColor(4);
        PreShSum_e_cut_hist->Rebin(rebinfac);
        //PreShSum_e_cut_hist->Draw("HIST same");
  TLegend *leg9 = new TLegend(0.15,0.7,0.55,0.88);
  leg9->AddEntry(PreShSum_e_hist,"5GeV e^{-} in front of PreShower Shower_l/ShowerSum>0.85","l");
  leg9->AddEntry(PreShSum_gamma_hist,"5GeV #gamma in front of PreShower Shower_l/ShowerSum>0.85","l");
  leg9->SetTextSize(0.03);
  leg9->SetBorderSize(0);
  leg9->SetFillColor(0);
  leg9->Draw("text same");
        c[1]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        PreShL_e_hist->SetLineColor(6);
        PreShL_e_hist->GetXaxis()->SetTitle("Edep (MeV)");
        PreShL_e_hist->SetTitle("5GeV e^{-} at PreShowerL");
        PreShL_e_hist->GetYaxis()->SetTitle("Event");
        PreShL_e_hist->GetYaxis()->SetRangeUser(1e-2,1e5);
        PreShL_e_hist->Rebin(rebinfac);
        PreShL_e_hist->Draw("HIST");
        PreShL_gamma_hist->SetLineColor(1);
        PreShL_gamma_hist->GetXaxis()->SetTitle("Edep (MeV)");
        PreShL_gamma_hist->SetTitle("5GeV #gamma at PreShowerL");
        PreShL_gamma_hist->Scale(PreShSum_e_hist->Integral()/PreShL_gamma_hist->Integral());
        PreShL_gamma_hist->GetYaxis()->SetTitle("Event");
        PreShL_gamma_hist->Rebin(rebinfac);
        PreShL_gamma_hist->Draw("HIST same");
  leg9->Draw("text same");
        c[1]->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        PreShR_e_hist->SetLineColor(6);
        PreShR_e_hist->GetXaxis()->SetTitle("Edep (MeV)");
        PreShR_e_hist->SetTitle("5GeV e^{-} at PreShowerR");
        PreShR_e_hist->GetYaxis()->SetTitle("Event");
        PreShR_e_hist->GetYaxis()->SetRangeUser(1e-2,1e5);
        PreShR_e_hist->Rebin(rebinfac);
        PreShR_e_hist->Draw("HIST");
        PreShR_gamma_hist->SetLineColor(1);
        PreShR_gamma_hist->GetXaxis()->SetTitle("Edep (MeV)");
        PreShR_gamma_hist->SetTitle("5GeV #gamma at PreShowerR");
        PreShR_gamma_hist->Scale(PreShSum_e_hist->Integral()/PreShR_gamma_hist->Integral());
        PreShR_gamma_hist->GetYaxis()->SetTitle("Event");
        PreShR_gamma_hist->Rebin(rebinfac);
        PreShR_gamma_hist->Draw("HIST same");
  leg9->Draw("text same");
        c[1]->cd(4);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        PreShT_e_hist->SetLineColor(6);
        PreShT_e_hist->GetXaxis()->SetTitle("Edep (MeV)");
        PreShT_e_hist->SetTitle("5GeV e^{-} at PreShowerT");
        PreShT_e_hist->GetYaxis()->SetTitle("Event");
        PreShT_e_hist->GetYaxis()->SetRangeUser(1e-2,1e5);
        PreShT_e_hist->Rebin(rebinfac);
        PreShT_e_hist->Draw("HIST");
        PreShT_gamma_hist->SetLineColor(1);
        PreShT_gamma_hist->GetXaxis()->SetTitle("Edep (MeV)");
        PreShT_gamma_hist->SetTitle("5GeV #gamma at PreShowerT");
        PreShT_gamma_hist->GetYaxis()->SetTitle("Event");
        PreShT_gamma_hist->Scale(PreShSum_e_hist->Integral()/PreShT_gamma_hist->Integral());
        PreShT_gamma_hist->Rebin(rebinfac);
        PreShT_gamma_hist->Draw("HIST same");
  leg9->Draw("text same");
	for(int a=0;a<2;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./Sim_5GeV_e_gamma_comparison.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
