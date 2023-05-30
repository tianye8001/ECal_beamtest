
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

void plot_rate_Cer_newCh_7deg(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f1 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_18deg_LD_21m_30degcut_poly/HallC_beamtest_bggen_LH2_pi0_18deg_LD_21m_30degcut_poly_filenum19000_reduce_tree_rate_gem1_Etotalcut_40uA_Q210MeV.root");
	TFile *f2 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_18deg_LD_21m_30degcut_poly/HallC_beamtest_bggen_LH2_pip_18deg_LD_21m_30degcut_poly_filenum33740_reduce_tree_rate_gem1_Etotalcut_40uA_Q210MeV.root");
	TFile *f3 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_18deg_LD_21m_30degcut_poly/HallC_beamtest_bggen_LH2_pim_18deg_LD_21m_30degcut_poly_filenum29270_reduce_tree_rate_gem1_Etotalcut_40uA_Q210MeV.root");
	TTree *tree_beam = (TTree*) f1->Get("T");
	TTree *tree_beam_pip = (TTree*) f2->Get("T");
	TTree *tree_beam_pim = (TTree*) f3->Get("T");
	const int rebinfac=5;
	const int rebinfac1=1;

        tree_beam->Draw("PreShSum>>preshower_beam(100,0,100)","rate*(ShowerSum>200 && ShowerSum<300)","goff");
	TH1F *preshower_beam_hist = (TH1F*)gROOT->FindObject("preshower_beam");
        tree_beam->Draw("PreShSum>>preshower_beam_cut(100,0,100)","rate*(ShowerSum>200 && ShowerSum<300 && LASPD_Eendsum==0)","goff");
	TH1F *preshower_beam_cut_hist = (TH1F*)gROOT->FindObject("preshower_beam_cut");
        tree_beam->Draw("PreSh_r>>preshowerR_beam(100,0,100)","rate*(Shower_r>200 && Shower_r<300)","goff");
	TH1F *preshowerR_beam_hist = (TH1F*)gROOT->FindObject("preshowerR_beam");
        tree_beam->Draw("PreSh_r>>preshowerR_beam_cut(100,0,100)","rate*(Shower_r>200 && Shower_r<300 && LASPD_Eendsum==0)","goff");
	TH1F *preshowerR_beam_cut_hist = (TH1F*)gROOT->FindObject("preshowerR_beam_cut");
        tree_beam->Draw("PreSh_l>>preshowerL_beam(100,0,100)","rate*(PreSh_l>0 &&Shower_l>92 && Shower_l<300)","goff");
	TH1F *preshowerL_beam_hist = (TH1F*)gROOT->FindObject("preshowerL_beam");
        tree_beam->Draw("PreSh_l>>preshowerL_beam_cut(100,0,100)","rate*(PreSh_l>0 &&Shower_l>92 && Shower_l<300 && LASPD_Eendsum==0)","goff");
	TH1F *preshowerL_beam_cut_hist = (TH1F*)gROOT->FindObject("preshowerL_beam_cut");
        tree_beam->Draw("PreSh_t>>preshowerT_beam(100,0,100)","rate*(PreSh_l>0 &&Shower_t>92 && Shower_t<300)","goff");
	TH1F *preshowerT_beam_hist = (TH1F*)gROOT->FindObject("preshowerT_beam");
        tree_beam->Draw("PreSh_t>>preshowerT_beam_cut(100,0,100)","rate*(PreSh_l>0 &&Shower_t>92 && Shower_t<300 && LASPD_Eendsum==0)","goff");
	TH1F *preshowerT_beam_cut_hist = (TH1F*)gROOT->FindObject("preshowerT_beam_cut");
        tree_beam_pip->Draw("PreSh_l>>preshowerL_beam_pip(100,0,100)","rate*(PreSh_l>0 &&Shower_l>92 && Shower_l<300)","goff");
	TH1F *preshowerL_beam_pip_hist = (TH1F*)gROOT->FindObject("preshowerL_beam_pip");
        tree_beam_pip->Draw("PreSh_l>>preshowerL_beam_cut_pip(100,0,100)","rate*(PreSh_l>0 &&Shower_l>92 && Shower_l<300 && LASPD_Eendsum==0)","goff");
	TH1F *preshowerL_beam_cut_pip_hist = (TH1F*)gROOT->FindObject("preshowerL_beam_cut_pip");
        tree_beam_pim->Draw("PreSh_l>>preshowerL_beam_pim(100,0,100)","rate*(PreSh_l>0 &&Shower_l>92 && Shower_l<300)","goff");
	TH1F *preshowerL_beam_pim_hist = (TH1F*)gROOT->FindObject("preshowerL_beam_pim");
        tree_beam_pim->Draw("PreSh_l>>preshowerL_beam_cut_pim(100,0,100)","rate*(PreSh_l>0 && Shower_l>92 && Shower_l<300 && LASPD_Eendsum==0)","goff");
	TH1F *preshowerL_beam_cut_pim_hist = (TH1F*)gROOT->FindObject("preshowerL_beam_cut_pim");
        TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
        c[0]->Divide(1,2);
        c[0]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        preshowerR_beam_hist->SetLineColor(1);
        preshowerR_beam_hist->GetXaxis()->SetTitle("preshower_r Edep (MeV)");
        preshowerR_beam_hist->GetYaxis()->SetTitle("Rate_kHz");
        preshowerR_beam_hist->Scale(0.001);
        preshowerR_beam_hist->GetYaxis()->SetRangeUser(1e-10,1e2);
        preshowerR_beam_hist->Draw("HIST");
        double rate_R= preshowerR_beam_hist->Integral();
        preshowerR_beam_cut_hist->SetLineColor(2);
        preshowerR_beam_cut_hist->Scale(0.001);
        preshowerR_beam_cut_hist->Draw("HIST same");
        double rate_R_cut= preshowerR_beam_cut_hist->Integral();
        double ratio_rateR= rate_R_cut/rate_R;
  TLegend *leg28 = new TLegend(0.55,0.7,0.75,0.88);
  leg28->AddEntry(preshowerR_beam_hist,"from #pi^{0}; 92<Shower_r<300","l");
  leg28->AddEntry(preshowerR_beam_cut_hist,"from #pi^{0}; 92<Shower_r<300 LASPD==0","l");
  leg28->SetTextSize(0.03);
  leg28->SetBorderSize(0);
  leg28->SetFillColor(0);
  leg28->Draw("text same");
        c[0]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
    TH1F *PreShSum_right_cut_copy_hist = (TH1F*)preshowerR_beam_cut_hist->Clone("PreShSum_right_cut_copy_hist");
        PreShSum_right_cut_copy_hist->Divide(preshowerR_beam_hist);
        PreShSum_right_cut_copy_hist->GetXaxis()->SetTitle("PreSh_r");
        PreShSum_right_cut_copy_hist->GetYaxis()->SetTitle("Ratio");
        PreShSum_right_cut_copy_hist->GetYaxis()->SetRangeUser(0,1.05);
        PreShSum_right_cut_copy_hist->Draw();
  TLegend *leg8 = new TLegend(0.45,0.7,0.75,0.88);
  leg8->AddEntry(PreShSum_right_cut_copy_hist,Form("from #pi^{0} ratio=%f",ratio_rateR),"l");
  leg8->SetTextSize(0.03);
  leg8->SetBorderSize(0);
  leg8->SetFillColor(0);
  leg8->Draw("text same");
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
        c[1]->Divide(2,2);
        c[1]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	//gPad->SetLogy();
        preshowerL_beam_hist->SetLineColor(1);
        preshowerL_beam_hist->GetXaxis()->SetTitle("preshower_l Edep (MeV)");
        preshowerL_beam_hist->GetYaxis()->SetTitle("Rate_Hz");
        //preshowerL_beam_hist->Scale(0.001);
        preshowerL_beam_hist->GetYaxis()->SetRangeUser(0,600);
        preshowerL_beam_hist->Draw("HIST");
        double rate_L= preshowerL_beam_hist->Integral();
        preshowerL_beam_cut_hist->SetLineColor(2);
        //preshowerL_beam_cut_hist->Scale(0.001);
        preshowerL_beam_cut_hist->Draw("HIST same");
        double rate_L_cut= preshowerL_beam_cut_hist->Integral();
        double ratio_rateL= rate_L_cut/rate_L;
        preshowerL_beam_cut_pip_hist->SetLineColor(4);
        //preshowerL_beam_cut_pip_hist->Scale(0.001);
        preshowerL_beam_cut_pip_hist->Draw("HIST same");
        preshowerL_beam_pip_hist->SetLineColor(6);
       // preshowerL_beam_pip_hist->Scale(0.001);
        preshowerL_beam_pip_hist->Draw("HIST same");
        double rate_L_pip= preshowerL_beam_pip_hist->Integral();
        double rate_L_pip_cut= preshowerL_beam_cut_pip_hist->Integral();
        double ratio_rateL_pip= rate_L_pip_cut/rate_L_pip;
        preshowerL_beam_cut_pim_hist->SetLineColor(kOrange-3);
       // preshowerL_beam_cut_pim_hist->Scale(0.001);
        preshowerL_beam_cut_pim_hist->Draw("HIST same");
        preshowerL_beam_pim_hist->SetLineColor(28);
       // preshowerL_beam_pim_hist->Scale(0.001);
        preshowerL_beam_pim_hist->Draw("HIST same");
        double rate_L_pim= preshowerL_beam_pim_hist->Integral();
        double rate_L_pim_cut= preshowerL_beam_cut_pim_hist->Integral();
        double ratio_rateL_pim= rate_L_pim_cut/rate_L_pim;
  TLegend *leg29 = new TLegend(0.55,0.7,0.75,0.88);
  leg29->AddEntry(preshowerL_beam_hist,"from #pi^{0}; 91<Shower_l<200","l");
  leg29->AddEntry(preshowerL_beam_cut_hist,"from #pi^{0}; 91<Shower_l<200 LASPD==0","l");
  leg29->AddEntry(preshowerL_beam_pip_hist,"from #pi^{+}; 91<Shower_l<200","l");
  leg29->AddEntry(preshowerL_beam_cut_pip_hist,"from #pi^{+}; 91<Shower_l<200 LASPD==0","l");
  leg29->AddEntry(preshowerL_beam_pim_hist,"from #pi^{-}; 91<Shower_l<200","l");
  leg29->AddEntry(preshowerL_beam_cut_pim_hist,"from #pi^{-}; 91<Shower_l<200 LASPD==0","l");
  leg29->SetTextSize(0.03);
  leg29->SetBorderSize(0);
  leg29->SetFillColor(0);
  leg29->Draw("text same");
        c[1]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
    TH1F *PreShSum_left_cut_copy_hist = (TH1F*)preshowerL_beam_cut_hist->Clone("PreShSum_left_cut_copy_hist");
        PreShSum_left_cut_copy_hist->Divide(preshowerL_beam_hist);
        PreShSum_left_cut_copy_hist->GetXaxis()->SetTitle("PreSh_l");
        PreShSum_left_cut_copy_hist->GetYaxis()->SetTitle("Ratio");
        PreShSum_left_cut_copy_hist->GetYaxis()->SetRangeUser(1e-2,1.5e0);
        PreShSum_left_cut_copy_hist->Draw();
    TH1F *PreShSum_left_cut_pip_copy_hist = (TH1F*)preshowerL_beam_cut_pip_hist->Clone("PreShSum_left_cut_pip_copy_hist");
        PreShSum_left_cut_pip_copy_hist->Divide(preshowerL_beam_pip_hist);
        PreShSum_left_cut_pip_copy_hist->GetXaxis()->SetTitle("PreSh_l");
        PreShSum_left_cut_pip_copy_hist->GetYaxis()->SetTitle("Ratio");
        PreShSum_left_cut_pip_copy_hist->GetYaxis()->SetRangeUser(1e-2,1.5e0);
        PreShSum_left_cut_pip_copy_hist->Draw("same");
    TH1F *PreShSum_left_cut_pim_copy_hist = (TH1F*)preshowerL_beam_cut_pim_hist->Clone("PreShSum_left_cut_pim_copy_hist");
        PreShSum_left_cut_pim_copy_hist->Divide(preshowerL_beam_pim_hist);
        PreShSum_left_cut_pim_copy_hist->GetXaxis()->SetTitle("PreSh_l");
        PreShSum_left_cut_pim_copy_hist->GetYaxis()->SetTitle("Ratio");
        PreShSum_left_cut_pim_copy_hist->GetYaxis()->SetRangeUser(1e-2,1.5e0);
        PreShSum_left_cut_pim_copy_hist->Draw("same");
  TLegend *leg81 = new TLegend(0.45,0.7,0.75,0.88);
  leg81->AddEntry(PreShSum_left_cut_copy_hist,Form("from #pi^{0} ratio=%f",ratio_rateL),"l");
  leg81->AddEntry(PreShSum_left_cut_pip_copy_hist,Form("from #pi^{+} ratio=%f",ratio_rateL_pip),"l");
  leg81->AddEntry(PreShSum_left_cut_pim_copy_hist,Form("from #pi^{-} ratio=%f",ratio_rateL_pim),"l");
  leg81->SetTextSize(0.03);
  leg81->SetBorderSize(0);
  leg81->SetFillColor(0);
  leg81->Draw("text same");
        c[1]->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
    TH1F *PreShSum_left_cut_pip_copy1_hist = (TH1F*)preshowerL_beam_pip_hist->Clone("PreShSum_left_cut_pip_copy1_hist");
        PreShSum_left_cut_pip_copy1_hist->Divide(preshowerL_beam_hist);
        PreShSum_left_cut_pip_copy1_hist->GetXaxis()->SetTitle("PreSh_l");
        PreShSum_left_cut_pip_copy1_hist->GetYaxis()->SetTitle("Ratio");
        PreShSum_left_cut_pip_copy1_hist->GetYaxis()->SetRangeUser(1e-2,1.5e0);
        PreShSum_left_cut_pip_copy1_hist->Draw();
    TH1F *PreShSum_left_cut_pim_copy1_hist = (TH1F*)preshowerL_beam_pim_hist->Clone("PreShSum_left_cut_pim_copy1_hist");
        PreShSum_left_cut_pim_copy1_hist->Divide(preshowerL_beam_hist);
        PreShSum_left_cut_pim_copy1_hist->GetXaxis()->SetTitle("PreSh_l");
        PreShSum_left_cut_pim_copy1_hist->GetYaxis()->SetTitle("Ratio");
        PreShSum_left_cut_pim_copy1_hist->GetYaxis()->SetRangeUser(1e-2,1.5e0);
        PreShSum_left_cut_pim_copy1_hist->Draw("same");
  TLegend *leg81 = new TLegend(0.45,0.7,0.75,0.88);
  leg81->AddEntry(PreShSum_left_cut_pip_copy1_hist,"ratio of #pi^{+}/#pi^{0}","l");
  leg81->AddEntry(PreShSum_left_cut_pim_copy1_hist,"ratio of #pi^{-}/#pi^{0}","l");
  leg81->SetTextSize(0.03);
  leg81->SetBorderSize(0);
  leg81->SetFillColor(0);
  leg81->Draw("text same");
	c[2] = new TCanvas("c[2]","c[2]",1000,1000);
        c[2]->Divide(1,2);
        c[2]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        preshowerT_beam_hist->SetLineColor(1);
        preshowerT_beam_hist->GetXaxis()->SetTitle("preshower_t Edep (MeV)");
        preshowerT_beam_hist->GetYaxis()->SetTitle("Rate_kHz");
        preshowerT_beam_hist->Scale(0.001);
        preshowerT_beam_hist->GetYaxis()->SetRangeUser(1e-10,1e2);
        preshowerT_beam_hist->Draw("HIST");
        double rate_T= preshowerT_beam_hist->Integral();
        preshowerT_beam_cut_hist->SetLineColor(2);
        preshowerT_beam_cut_hist->Scale(0.001);
        preshowerT_beam_cut_hist->Draw("HIST same");
        double rate_T_cut= preshowerT_beam_cut_hist->Integral();
        double ratio_rateT= rate_T_cut/rate_T;
  TLegend *leg2 = new TLegend(0.55,0.7,0.75,0.88);
  leg2->AddEntry(preshowerT_beam_hist,"from #pi^{0}; 91<Shower_t<300","l");
  leg2->AddEntry(preshowerT_beam_cut_hist,"from #pi^{0}; 91<Shower_t<300 LASPD==0","l");
  leg2->SetTextSize(0.03);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  leg2->Draw("text same");
        c[2]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
    TH1F *PreShSum_top_cut_copy_hist = (TH1F*)preshowerT_beam_cut_hist->Clone("PreShSum_top_cut_copy_hist");
        PreShSum_top_cut_copy_hist->Divide(preshowerT_beam_hist);
        PreShSum_top_cut_copy_hist->GetXaxis()->SetTitle("PreSh_r");
        PreShSum_top_cut_copy_hist->GetYaxis()->SetTitle("Ratio");
        PreShSum_top_cut_copy_hist->GetYaxis()->SetRangeUser(0,1.05);
        PreShSum_top_cut_copy_hist->Draw();
  TLegend *leg82 = new TLegend(0.45,0.7,0.75,0.88);
  leg82->AddEntry(PreShSum_top_cut_copy_hist,Form("from #pi^{0} ratio=%f",ratio_rateT),"l");
  leg82->SetTextSize(0.03);
  leg82->SetBorderSize(0);
  leg82->SetFillColor(0);
  leg82->Draw("text same");
	c[3] = new TCanvas("c[3]","c[3]",1000,1000);
        c[3]->Divide(1,2);
        c[3]->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        preshower_beam_hist->SetLineColor(1);
        preshower_beam_hist->GetXaxis()->SetTitle("preshowersum Edep (MeV)");
        preshower_beam_hist->GetYaxis()->SetTitle("Rate_kHz");
        preshower_beam_hist->Scale(0.001);
        preshower_beam_hist->GetYaxis()->SetRangeUser(1e-10,1e2);
        preshower_beam_hist->Draw("HIST");
        double rate= preshower_beam_hist->Integral();
        preshower_beam_cut_hist->SetLineColor(2);
        preshower_beam_cut_hist->Scale(0.001);
        preshower_beam_cut_hist->Draw("HIST same");
        double rate_cut= preshower_beam_cut_hist->Integral();
        double ratio_rate= rate_cut/rate;
  TLegend *leg21 = new TLegend(0.55,0.7,0.75,0.88);
  leg21->AddEntry(preshower_beam_hist,"from #pi^{0}; 91<Shower_sum<300","l");
  leg21->AddEntry(preshower_beam_cut_hist,"from #pi^{0}; 91<Shower_sum<300 LASPD==0","l");
  leg21->SetTextSize(0.03);
  leg21->SetBorderSize(0);
  leg21->SetFillColor(0);
  leg21->Draw("text same");
        c[3]->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
    TH1F *PreShSum_cut_copy_hist = (TH1F*)preshower_beam_cut_hist->Clone("PreShSum_cut_copy_hist");
        PreShSum_cut_copy_hist->Divide(preshower_beam_hist);
        PreShSum_cut_copy_hist->GetXaxis()->SetTitle("PreSh_sum");
        PreShSum_cut_copy_hist->GetYaxis()->SetTitle("Ratio");
        PreShSum_cut_copy_hist->GetYaxis()->SetRangeUser(0,1.05);
        PreShSum_cut_copy_hist->Draw();
  TLegend *leg83 = new TLegend(0.45,0.7,0.75,0.88);
  leg83->AddEntry(PreShSum_cut_copy_hist,Form("from #pi^{0} ratio=%f",ratio_rate),"l");
  leg83->SetTextSize(0.03);
  leg83->SetBorderSize(0);
  leg83->SetFillColor(0);
  leg83->Draw("text same");
	for(int a=0;a<4;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./Simulated_40uA_LASPD_rejection.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
