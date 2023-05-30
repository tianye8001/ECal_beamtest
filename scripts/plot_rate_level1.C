
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

void plot_rate_level1(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f1 = new TFile("/work/halla/solid/jixie/ecal_beamtest_hallc/highrate/highrate_20230127/beamtest_level1_4094_0.root");
	TTree *tree_beam = (TTree*) f1->Get("T");
	const int rebinfac=1;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
        tree_beam->Draw("ShowerSum>>showersum(1000,0,70000)","TrigType==8","goff");
        TH1F *shower_sum_hist = (TH1F*)gROOT->FindObject("showersum");
        tree_beam->Draw("Shower_r>>shower_r(1000,0,70000)","TrigType==8","goff");
        TH1F *shower_r_hist = (TH1F*)gROOT->FindObject("shower_r");
        tree_beam->Draw("Shower_l>>shower_l(1000,0,70000)","TrigType==8","goff");
        TH1F *shower_l_hist = (TH1F*)gROOT->FindObject("shower_l");
        tree_beam->Draw("Shower_t>>shower_t(1000,0,70000)","TrigType==8","goff");
        TH1F *shower_t_hist = (TH1F*)gROOT->FindObject("shower_t");
        tree_beam->Draw("PreShSum>>preshowersum(1000,0,10000)","TrigType==8 &&ShowerSum>40000","goff");
        TH1F *preshower_sum_hist = (TH1F*)gROOT->FindObject("preshowersum");
        tree_beam->Draw("PreSh_r>>preshower_r(1000,0,10000)","TrigType==8&& ShowerSum>40000","goff");
        TH1F *preshower_r_hist = (TH1F*)gROOT->FindObject("preshower_r");
        tree_beam->Draw("PreSh_l>>preshower_l(1000,0,10000)","TrigType==8&& ShowerSum>40000","goff");
        TH1F *preshower_l_hist = (TH1F*)gROOT->FindObject("preshower_l");
        tree_beam->Draw("PreSh_l>>preshower_l_total(1000,0,10000)","TrigType==8","goff");
        TH1F *preshower_l_total_hist = (TH1F*)gROOT->FindObject("preshower_l_total");
        tree_beam->Draw("PreSh_t>>preshower_t(1000,0,10000)","TrigType==8&& ShowerSum>40000","goff");
        TH1F *preshower_t_hist = (TH1F*)gROOT->FindObject("preshower_t");
        tree_beam->Draw("SC_D>>SC_D_cut(1000,0,10000)","TrigType==8&& PreSh_r>3000","goff");
        TH1F *SC_D_cut_hist = (TH1F*)gROOT->FindObject("SC_D_cut");
        tree_beam->Draw("SC_D>>SC_D(1000,0,10000)","TrigType==8","goff");
        TH1F *SC_D_hist = (TH1F*)gROOT->FindObject("SC_D");
        tree_beam->Draw("SC_A>>SC_A_cut(1000,0,10000)","TrigType==8&& PreSh_r>3000","goff");
        TH1F *SC_A_cut_hist = (TH1F*)gROOT->FindObject("SC_A_cut");
        tree_beam->Draw("SC_A>>SC_A(1000,0,10000)","TrigType==8","goff");
        TH1F *SC_A_hist = (TH1F*)gROOT->FindObject("SC_A");
        tree_beam->Draw("SC_C>>SC_C(1000,0,10000)","TrigType==8","goff");
        TH1F *SC_C_hist = (TH1F*)gROOT->FindObject("SC_C");
        tree_beam->Draw("SC_C>>SC_C_cut(1000,0,10000)","TrigType==8 && PreSh_r>3000","goff");
        TH1F *SC_C_cut_hist = (TH1F*)gROOT->FindObject("SC_C_cut");
        tree_beam->Draw("LASPD_t>>LASPDt_cut(1000,0,10000)","TrigType==8&& PreSh_r>3000","goff");
        TH1F *LASPD_T_cut_hist = (TH1F*)gROOT->FindObject("LASPDt_cut");
        tree_beam->Draw("LASPD_b>>LASPDb_cut(1000,0,10000)","TrigType==8&& PreSh_r>3000","goff");
        TH1F *LASPD_B_cut_hist = (TH1F*)gROOT->FindObject("LASPDb_cut");
        tree_beam->Draw("SC_B>>SC_B(1000,0,6000)","TrigType==8","goff");
        TH1F *SC_B_hist = (TH1F*)gROOT->FindObject("SC_B");
        tree_beam->Draw("SC_B>>SC_B_cut(1000,0,6000)","TrigType==8 && ShowerSum>30000","goff");
        TH1F *SC_B_cut_hist = (TH1F*)gROOT->FindObject("SC_B_cut");
        tree_beam->Draw("LASPD_t>>LASPDt(1000,0,10000)","TrigType==8","goff");
        TH1F *LASPD_T_hist = (TH1F*)gROOT->FindObject("LASPDt");
        tree_beam->Draw("LASPD_b>>LASPDb(1000,0,10000)","TrigType==8","goff");
        TH1F *LASPD_B_hist = (TH1F*)gROOT->FindObject("LASPDb");
	TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
        c[0]->Divide(2,2);
        c[0]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        shower_sum_hist->SetLineColor(1);
        shower_sum_hist->GetXaxis()->SetTitle("ShowerSum (ADC)");
        shower_sum_hist->GetYaxis()->SetTitle("Events");
        shower_sum_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        shower_sum_hist->Draw();
        shower_r_hist->Draw("same HIST");
        shower_l_hist->Draw("same HIST");
        shower_t_hist->Draw("same HIST");
        c[0]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        shower_r_hist->SetLineColor(6);
        shower_r_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        shower_r_hist->Draw("HIST");
        c[0]->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        shower_l_hist->SetLineColor(2);
        shower_l_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        shower_l_hist->Draw(" HIST");
        c[0]->cd(4);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        shower_t_hist->SetLineColor(4);
        shower_t_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        shower_t_hist->Draw(" HIST");
        c[0]->cd(1);
  TLegend *leg8 = new TLegend(0.45,0.6,0.8,0.88);
  leg8->AddEntry(shower_sum_hist,"ShowerSum","l");
  leg8->AddEntry(shower_r_hist,"Shower_right","l");
  leg8->AddEntry(shower_l_hist,"Shower_left","l");
  leg8->AddEntry(shower_t_hist,"Shower_top","l");
  leg8->SetTextSize(0.03);
  leg8->SetBorderSize(0);
  leg8->SetFillColor(0);
  leg8->Draw("text same");
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
        c[1]->Divide(2,2);
        c[1]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        preshower_sum_hist->SetLineColor(1);
        preshower_sum_hist->GetXaxis()->SetTitle("ShowerSum (ADC)");
        preshower_sum_hist->GetYaxis()->SetTitle("Events");
        preshower_sum_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        preshower_sum_hist->Draw();
        preshower_r_hist->Draw("same HIST");
        preshower_l_hist->Draw("same HIST");
        preshower_t_hist->Draw("same HIST");
        c[1]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        preshower_r_hist->SetLineColor(6);
        preshower_r_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        preshower_r_hist->Draw("HIST");
        c[1]->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        preshower_l_hist->SetLineColor(2);
        preshower_l_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        preshower_l_hist->Draw(" HIST");
        c[1]->cd(4);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        preshower_t_hist->SetLineColor(4);
        preshower_t_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        preshower_t_hist->Draw(" HIST");
        c[1]->cd(1);
  TLegend *leg18 = new TLegend(0.45,0.6,0.8,0.88);
  leg18->AddEntry(preshower_sum_hist,"preShowerSum","l");
  leg18->AddEntry(preshower_r_hist,"preShower_right","l");
  leg18->AddEntry(preshower_l_hist,"preShower_left","l");
  leg18->AddEntry(preshower_t_hist,"preShower_top","l");
  leg18->SetTextSize(0.03);
  leg18->SetBorderSize(0);
  leg18->SetFillColor(0);
  leg18->Draw("text same");
	c[2] = new TCanvas("c[2]","c[2]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        SC_D_hist->SetLineColor(1);
        SC_D_hist->GetXaxis()->SetTitle("SC_D (ADC)");
        SC_D_hist->GetYaxis()->SetTitle("Events");
        SC_D_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        SC_D_hist->Draw();
        SC_D_cut_hist->SetLineColor(2);
        SC_D_cut_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        SC_D_cut_hist->Draw("same HIST");
        /*SC_A_hist->SetLineColor(4);
        SC_A_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        SC_A_hist->Draw("same HIST");
        LASPD_T_hist->SetLineColor(6);
        LASPD_T_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        LASPD_T_hist->Draw("same HIST");
        LASPD_B_hist->SetLineColor(2);
        LASPD_B_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        LASPD_B_hist->Draw("same HIST")*/;
  TLegend *leg28 = new TLegend(0.35,0.6,0.8,0.88);
  leg28->AddEntry(SC_D_cut_hist,"SC_D triggered with PreSh_r>3000 cut","l");
  leg28->AddEntry(SC_D_hist,"SC_D triggered","l");
  leg28->SetTextSize(0.03);
  leg28->SetBorderSize(0);
  leg28->SetFillColor(0);
  leg28->Draw("text same");

	c[3] = new TCanvas("c[3]","c[3]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        SC_B_hist->SetLineColor(1);
        SC_B_hist->GetXaxis()->SetTitle("SC_B (ADC)");
        SC_B_hist->GetYaxis()->SetTitle("Events");
        SC_B_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        SC_B_hist->Draw();
        SC_B_cut_hist->SetLineColor(2);
        SC_B_cut_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        SC_B_cut_hist->Draw("same HIST");
  TLegend *leg38 = new TLegend(0.35,0.6,0.8,0.88);
  leg38->AddEntry(SC_B_cut_hist,"SC_B TS4 triggered with PreSh_r>3000 cut","l");
  leg38->AddEntry(SC_B_hist,"SC_B TS4 triggered","l");
  leg38->SetTextSize(0.03);
  leg38->SetBorderSize(0);
  leg38->SetFillColor(0);
  leg38->Draw("text same");
	c[4] = new TCanvas("c[4]","c[4]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        SC_D_hist->SetLineColor(1);
        SC_D_hist->GetXaxis()->SetTitle("SC_D (ADC)");
        SC_D_hist->GetYaxis()->SetTitle("Events");
        SC_D_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        SC_D_hist->Draw();
        SC_C_hist->SetLineColor(2);
        SC_C_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        SC_C_hist->Draw("same HIST");
        SC_A_hist->SetLineColor(4);
        SC_A_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        SC_A_hist->Draw("same HIST");
        SC_B_hist->SetLineColor(kOrange-3);
        SC_B_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        SC_B_hist->Draw("same HIST");
        LASPD_T_hist->SetLineColor(6);
        LASPD_T_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        LASPD_T_hist->Draw("same HIST");
        LASPD_B_hist->SetLineColor(8);
        LASPD_B_hist->GetYaxis()->SetRangeUser(1e0,1e5);
        LASPD_B_hist->Draw("same HIST");
        preshower_l_total_hist->SetLineColor(7);
        preshower_l_total_hist->GetYaxis()->SetRangeUser(1e0,1e5);
       // preshower_l_total_hist->Draw("same HIST");
  TLegend *leg48 = new TLegend(0.35,0.6,0.8,0.88);
  leg48->AddEntry(SC_A_hist,"SC_A triggered","l");
  leg48->AddEntry(SC_C_hist,"SC_C triggered","l");
  leg48->AddEntry(LASPD_T_hist,"LASPD_top triggered","l");
  leg48->AddEntry(LASPD_B_hist,"LASPD_bottom triggered","l");
  leg48->AddEntry(SC_D_hist,"SC_D triggered","l");
  //leg48->AddEntry(preshower_l_total_hist,"preshower_left","l");
  leg48->AddEntry(SC_B_hist,"SC_B triggered","l");
  leg48->SetTextSize(0.03);
  leg48->SetBorderSize(0);
  leg48->SetFillColor(0);
  leg48->Draw("text same");
	for(int a=4;a<5;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_data_run4094_SCB.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
