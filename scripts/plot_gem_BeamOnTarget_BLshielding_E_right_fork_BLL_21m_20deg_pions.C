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

void plot_gem_BeamOnTarget_BLshielding_E_right_fork_debug(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f7 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_20deg_LD_21m/HallC_beamtest_bggen_LD2_pim_20deg_filenum19430_21m_shielding_output_preshower_theta_rate.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_20deg_LD_21m/HallC_beamtest_bggen_LD2_pi0_20deg_filenum33520_21m_shielding_output_preshower_theta_rate.root");
	TFile *f14 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_20deg_LD_21m/HallC_beamtest_bggen_LD2_pip_20deg_filenum40090_21m_shielding_output_preshower_theta_rate.root");
	TFile *f17 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_20deg_LD_21m/HallC_beamtest_bggen_LD2_pim_20deg_filenum19430_21m_shielding_output_preshower_theta_rate_tid1.root");
	const int rebinfac=1;
	TH1F *hprocid_gem1;       
	TH1F *hpf_gem1;
	TH1F *hE_gem1;
	TH1F *hpf_gem1_1cmAl;
	TH1F *hE_gem1_1inpoly;
	TH1F *hhit_Egem1_procID[11];
	TH1F *hhit_Egem1;
	TH1F *hhit_Egem1_gamma;
	TH1F *hhit_Egem1_electron;
	TH1F *hhit_Egem1_other;
	TH1F *hhit_Egem1_pi0;
	TH1F *hhit_Edepgem1_procID[11];
	TH1F *hhit_Edepgem1;
	TH1F *hhit_Edepgem1_gamma;
	TH1F *hhit_Edepgem1_other;
	TH1F *hhit_Edepgem1_pi0;
	TH1F *hhit_Edepgem12_electron_noTB;
	TH1F *hhit_Edepgem12_electron;
	TH1F *hhit_Edepgem12_electron_test;
	TH1F *hhit_Egem1_electron_noTB;
	TH1F *hhit_Edepgem1_electron_1cmAl;
	TH1F *hhit_Edepgem1_electron_1inpoly;
	TH1F *hhit_Edepgem1_electron_25cm;
	TH1F *hhit_Edepgem1_electron_35cm;
	TH1F *hhit_Edepgem1_electron_35cmL;
	TH1F *hhit_Edepgem1_electron_45cm;
	TH1F *hhit_Edepgem1_electron_55cm;
	TH1F *hhit_Edepgem1_electron_noTB;
	TH1F *hhit_Edepgem1_electron_noB;
	TH1F *hhit_Edepgem1_electron;

	TH1F *hhit_Edepgem2_electron_noTB;
	TH1F *hhit_Edepgem2_electron_noB;
	TH1F *hhit_Edepgem2_electron;
	TH1F *hhit_Egem2_electron;
	TH1F *hhit_Egem2_electron_noTB;
	TH1F *hhit_Edepgem2_electron_1cmAl;
	TH1F *hhit_Edepgem2_electron_1inpoly;
	TH1F *hhit_Edepgem2_electron_25cm;
	TH1F *hhit_Edepgem2_electron_35cm;
	TH1F *hhit_Edepgem2_electron_35cmL;
	TH1F *hhit_Edepgem2_electron_45cm;
	TH1F *hhit_Edepgem2_electron_55cm;

	TH1F *hhit_theta_noTB;
	TH1F *hhit_theta_noB;
	TH1F *hhit_theta;
	TH1F *hhit_theta_1cmAl;
	TH1F *hhit_theta_1inpoly;
	TH1F *hhit_theta_25cm;
	TH1F *hhit_theta_25cm_electron;
	TH1F *hhit_theta_35cm;
	TH1F *hhit_theta_35cmL;
	TH1F *hhit_theta_45cm;
	TH1F *hhit_theta_45cm_electron;
	TH1F *hhit_theta_55cm_electron;
	TH1F *hhit_theta_55cm;
	TH1F *hhit_theta_gem2_noTB;
	TH1F *hhit_theta_gem2_noB;
	TH1F *hhit_theta_gem2;
	TH1F *hhit_theta_1cmAl_gem2;
	TH1F *hhit_theta_1inpoly_gem2;
	TH1F *hhit_theta_25cm_gem2;
	TH1F *hhit_theta_25cm_gem2_electron;
	TH1F *hhit_theta_35cm_gem2;
	TH1F *hhit_theta_35cmL_gem2;
	TH1F *hhit_theta_45cm_gem2;
	TH1F *hhit_theta_45cm_gem2_electron;
	TH1F *hhit_theta_55cm_gem2_electron;
	TH1F *hhit_theta_55cm_gem2;
	TH1F *hhit_Edepgem1_gamma_noTB;
	TH1F *hhit_Edepgem1_gamma_noB;
	TH1F *hhit_Edepgem1_gamma;
	TH1F *hhit_Egem1_gamma_noTB;
	TH1F *hhit_Edepgem1_gamma_1cmAl;
	TH1F *hhit_Edepgem1_gamma_1inpoly;
	TH1F *hhit_Edepgem1_gamma_35cm;
	TH1F *hhit_Edepgem1_gamma_45cm;
	TH1F *hhit_Edepgem1_gamma_55cm;
	TH1F *hhit_Edepgem1_gamma_25cm;
	TH1F *hhit_Edepgem1_gamma_15deg;
	TH1F *hhit_Edepgem1_gamma_20degv;
	TH1F *hhit_Edepgem2_gamma_15deg;
	TH1F *hhit_Edepgem2_gamma_20degv;

	TH1F *hhit_Edepgem2_gamma_noTB;
	TH1F *hhit_Edepgem2_gamma_noB;
	TH1F *hhit_Edepgem2_gamma;
	TH1F *hhit_Egem2_gamma;
	TH1F *hhit_Egem2_gamma_noTB;
	TH1F *hhit_Edepgem2_gamma_1cmAl;
	TH1F *hhit_Edepgem2_gamma_1inpoly;
	TH1F *hhit_Edepgem2_gamma_35cm;
	TH1F *hhit_Edepgem2_gamma_25cm;
	TH1F *hhit_Edepgem2_gamma_45cm;
	TH1F *hhit_Edepgem2_gamma_55cm;
	TH1F *hhit_theta_noTB_electron;
	TH1F *hhit_theta_noB_electron;
	TH1F *hhit_theta_electron;
	TH1F *hhit_theta_1cmAl_electron;
	TH1F *hhit_theta_1inpoly_electron;
	TH1F *hhit_theta_35cm_electron;
	TH1F *hhit_theta_gem2_noTB_electron;
	TH1F *hhit_theta_gem2_noB_electron;
	TH1F *hhit_theta_gem2_electron;
	TH1F *hhit_theta_1cmAl_gem2_electron;
	TH1F *hhit_theta_1inpoly_gem2_electron;
	TH1F *hhit_theta_35cm_gem2_electron;
	TH1F *hhit_Edepgem1_Moller_noTB;
	TH1F *hhit_Edepgem1_Moller_noB;
	TH1F *hhit_Edepgem1_Moller;
	TH1F *hhit_Edepgem1_Moller_1cmAl;
	TH1F *hhit_Edepgem1_Moller_1inpoly;
	TH1F *hhit_Edepgem1_Moller_35cm;
	TH1F *hhit_Edepgem1_compton_noTB;
	TH1F *hhit_Edepgem1_compton_noB;
	TH1F *hhit_Edepgem1_compton;
	TH1F *hhit_Edepgem1_compton_1cmAl;
	TH1F *hhit_Edepgem1_compton_1inpoly;
	TH1F *hhit_Edepgem1_compton_35cm;
	TH2F *hhit_mvz_vs_theta_pim;
	TH2F *hhit_mvz_vs_theta_pimtid1;
	TH2F *hhit_mvz_vs_theta_pi0;
	TH2F *hhit_mvz_vs_theta_pip;
	TH2F *hhit_mvz_vs_mr_pim;
	TH2F *hhit_mvz_vs_mr_pimtid1;
	TH2F *hhit_mvz_vs_mr_pi0;
	TH2F *hhit_mvz_vs_mr_pip;
	TH2F *hhit_mvz_vs_E_pim;
	TH2F *hhit_mvz_vs_E_pimtid1;
	TH2F *hhit_mvz_vs_E_pi0;
	TH2F *hhit_mvz_vs_E_pip;

	TH2F *hhit_p_vs_theta_pim;
	TH2F *hhit_p_vs_theta_pimtid1;
	TH2F *hhit_p_vs_theta_pi0;
	TH2F *hhit_p_vs_theta_pip;
	TH2F *hhit_p_vs_theta_gem2_pim;
	TH2F *hhit_p_vs_theta_gem2_pimtid1;
	TH2F *hhit_p_vs_theta_gem2_pi0;
	TH2F *hhit_p_vs_theta_gem2_pip;
	TH2F *hhit_mvz_vs_theta_gem2_pim;
	TH2F *hhit_mvz_vs_theta_gem2_pimtid1;
	TH2F *hhit_mvz_vs_theta_gem2_pi0;
	TH2F *hhit_mvz_vs_theta_gem2_pip;
	TH2F *hhit_mvz_vs_mr_gem2_pim;
	TH2F *hhit_mvz_vs_mr_gem2_pimtid1;
	TH2F *hhit_mvz_vs_mr_gem2_pi0;
	TH2F *hhit_mvz_vs_mr_gem2_pip;
	TH2F *hhit_mvz_vs_E_gem2_pim;
	TH2F *hhit_mvz_vs_E_gem2_pimtid1;
	TH2F *hhit_mvz_vs_E_gem2_pi0;
	TH2F *hhit_mvz_vs_E_gem2_pip;
        hhit_mvz_vs_theta_pim = (TH2F*)f7->Get("vertexmZ_vs_theta_hist");
        hhit_mvz_vs_theta_pi0 = (TH2F*)f4->Get("vertexmZ_vs_theta_hist");
        hhit_mvz_vs_theta_pip = (TH2F*)f14->Get("vertexmZ_vs_theta_hist");
        hhit_mvz_vs_theta_pimtid1 = (TH2F*)f17->Get("vertexmZ_vs_theta_hist");

        hhit_p_vs_theta_pim = (TH2F*)f7->Get("gen_ThetaP_gem1");
        hhit_p_vs_theta_pi0 = (TH2F*)f4->Get("gen_ThetaP_gem1");
        hhit_p_vs_theta_pip = (TH2F*)f14->Get("gen_ThetaP_gem1");
        hhit_p_vs_theta_pimtid1 = (TH2F*)f17->Get("gen_ThetaP_gem1");
       
        hhit_mvz_vs_E_pim = (TH2F*)f7->Get("vertexmZ_vs_E_hist");
        hhit_mvz_vs_E_pi0 = (TH2F*)f4->Get("vertexmZ_vs_E_hist");
        hhit_mvz_vs_E_pip = (TH2F*)f14->Get("vertexmZ_vs_E_hist");
        hhit_mvz_vs_E_pimtid1 = (TH2F*)f17->Get("vertexmZ_vs_E_hist");

        hhit_mvz_vs_mr_pim = (TH2F*)f7->Get("vertexmZ_vs_vertexmR_hist");
        hhit_mvz_vs_mr_pi0 = (TH2F*)f4->Get("vertexmZ_vs_vertexmR_hist");
        hhit_mvz_vs_mr_pip = (TH2F*)f14->Get("vertexmZ_vs_vertexmR_hist");
        hhit_mvz_vs_mr_pimtid1 = (TH2F*)f17->Get("vertexmZ_vs_vertexmR_hist");

        hhit_Edepgem1_electron_25cm = (TH1F*)f4->Get("hit_Egem1");
        hhit_Edepgem1_electron_45cm = (TH1F*)f7->Get("hit_Egem1");

        hhit_Edepgem1_gamma_45cm = (TH1F*)f17->Get("hit_Egem1");
        hhit_Edepgem1_gamma_25cm = (TH1F*)f14->Get("hit_Egem1");
        hhit_theta_25cm = (TH1F*)f4->Get("gen_Theta_gem1");
        hhit_theta_25cm_electron = (TH1F*)f14->Get("gen_Theta_gem1");
        hhit_theta_45cm = (TH1F*)f7->Get("gen_Theta_gem1");
        hhit_theta_45cm_electron = (TH1F*)f17->Get("gen_Theta_gem1");

        hhit_Edepgem2_electron_25cm = (TH1F*)f4->Get("hit_Egem2");
        hhit_Edepgem2_electron_45cm = (TH1F*)f7->Get("hit_Egem2");
        hhit_Edepgem2_gamma_45cm = (TH1F*)f17->Get("hit_Egem2");
        hhit_Edepgem2_gamma_25cm = (TH1F*)f14->Get("hit_Egem2");
        hhit_theta_25cm_gem2 = (TH1F*)f4->Get("gen_Theta_gem2");
        hhit_theta_25cm_gem2_electron = (TH1F*)f14->Get("gen_Theta_gem2");
        hhit_theta_45cm_gem2 = (TH1F*)f7->Get("gen_Theta_gem2");
        hhit_theta_45cm_gem2_electron = (TH1F*)f17->Get("gen_Theta_gem2");
        hhit_mvz_vs_theta_gem2_pim = (TH2F*)f7->Get("vertexmZ_vs_theta_gem2_hist");
        hhit_mvz_vs_theta_gem2_pi0 = (TH2F*)f4->Get("vertexmZ_vs_theta_gem2_hist");
        hhit_mvz_vs_theta_gem2_pip = (TH2F*)f14->Get("vertexmZ_vs_theta_gem2_hist");
        hhit_mvz_vs_theta_gem2_pimtid1 = (TH2F*)f17->Get("vertexmZ_vs_theta_gem2_hist");

        hhit_p_vs_theta_gem2_pim = (TH2F*)f7->Get("gen_ThetaP_gem2");
        hhit_p_vs_theta_gem2_pi0 = (TH2F*)f4->Get("gen_ThetaP_gem2");
        hhit_p_vs_theta_gem2_pip = (TH2F*)f14->Get("gen_ThetaP_gem2");
        hhit_p_vs_theta_gem2_pimtid1 = (TH2F*)f17->Get("gen_ThetaP_gem2");
       
        hhit_mvz_vs_E_gem2_pim = (TH2F*)f7->Get("vertexmZ_vs_E_gem2_hist");
        hhit_mvz_vs_E_gem2_pi0 = (TH2F*)f4->Get("vertexmZ_vs_E_gem2_hist");
        hhit_mvz_vs_E_gem2_pip = (TH2F*)f14->Get("vertexmZ_vs_E_gem2_hist");
        hhit_mvz_vs_E_gem2_pimtid1 = (TH2F*)f17->Get("vertexmZ_vs_E_gem2_hist");

        hhit_mvz_vs_mr_gem2_pim = (TH2F*)f7->Get("vertexmZ_vs_vertexmR_gem2_hist");
        hhit_mvz_vs_mr_gem2_pi0 = (TH2F*)f4->Get("vertexmZ_vs_vertexmR_gem2_hist");
        hhit_mvz_vs_mr_gem2_pip = (TH2F*)f14->Get("vertexmZ_vs_vertexmR_gem2_hist");
        hhit_mvz_vs_mr_gem2_pimtid1 = (TH2F*)f17->Get("vertexmZ_vs_vertexmR_gem2_hist");
	TCanvas *c_gem[10];
	c_gem[0] = new TCanvas("c_gem[0]", "flux #theta",1800,1000);
	gPad->SetLogy();
	gPad->SetGridy();
	gPad->SetGridx();
        //hhit_theta_noTB->SetLineColor(6);	
/*        hhit_theta_noTB->GetYaxis()->SetTitle("rate (MHz/cm2)");	
        hhit_theta_noTB->GetXaxis()->SetTitle("hit #theta");	
        hhit_theta_noTB->SetTitle("#gamma in front of gem1");	
        hhit_theta_noTB->GetXaxis()->SetRangeUser(0,95);	
        hhit_theta_noTB->Scale(1e-6);
        hhit_theta_noTB->GetYaxis()->SetRangeUser(1e-3,1e6);	
       // hhit_theta->Draw("HISt");	
        hhit_theta_noTB->SetLineColor(kGreen+1);	
       // hhit_theta_noTB->Scale(1e-6);
        hhit_theta_noTB->Draw("HISt");	
        hhit_theta_noB->SetLineColor(6);	
        hhit_theta_noB->Scale(1e-6);
        hhit_theta_noB->Draw("same HISt");	
        hhit_theta_1cmAl->SetLineColor(4);	
        hhit_theta_1cmAl->Scale(1e-6);
        hhit_theta_1cmAl->Draw("same HISt");	
        hhit_theta_1inpoly->SetLineColor(1);	
        hhit_theta_1inpoly->Scale(1e-6);
        hhit_theta_1inpoly->Draw("same HISt");	
        double rate_theta_linpoly= hhit_theta_1inpoly->Integral();
        hhit_theta_35cm->SetLineColor(2);	
        hhit_theta_35cm->Scale(1e-6);
        hhit_theta_35cm->Draw("same HISt");	
        hhit_theta_1inpoly->Draw("same HISt");*/	
        hhit_theta_45cm->SetLineColor(1);	
        hhit_theta_45cm->GetYaxis()->SetTitle("rate (Hz)");	
        hhit_theta_45cm->GetXaxis()->SetTitle("hit #theta");	
        hhit_theta_45cm->SetTitle("in front of GEM00");	
       // hhit_theta_45cm->Scale(1e-6);
        hhit_theta_45cm->Rebin(rebinfac);
        hhit_theta_45cm->GetYaxis()->SetRangeUser(1e-3,1e2);	
        hhit_theta_45cm->GetXaxis()->SetRangeUser(0,95);	
        hhit_theta_45cm->Draw("HIST");	
        hhit_theta_25cm->SetLineColor(2);	
       // hhit_theta_25cm->Scale(1e-6);
        hhit_theta_25cm->Rebin(rebinfac);
        hhit_theta_25cm->Draw("same HIST");	
        hhit_theta_25cm_electron->SetLineColor(4);	
      //  hhit_theta_25cm_electron->Scale(1e-6);
        hhit_theta_25cm_electron->Rebin(rebinfac);
        hhit_theta_25cm_electron->Draw("same HIST");	
        hhit_theta_45cm_electron->SetLineColor(6);	
      //  hhit_theta_45cm_electron->Scale(1e-6);
        hhit_theta_45cm_electron->Rebin(rebinfac);
        hhit_theta_45cm_electron->Draw("same HIST");	
	TLegend *leg1 = new TLegend(0.45,0.7,0.8,0.9);
	leg1->AddEntry(hhit_theta_45cm,"from #pi^{-}","l");
	leg1->AddEntry(hhit_theta_25cm,"from #pi^{o}","l");
	leg1->AddEntry(hhit_theta_25cm_electron,"from #pi^{+}","l");
	leg1->AddEntry(hhit_theta_45cm_electron,"from #pi^{-} tid==1","l");
	leg1->SetTextSize(0.035);
	leg1->SetBorderSize(0);
	leg1->SetFillColor(0);
	leg1->Draw("text same");

	c_gem[1] = new TCanvas("c_gem[1]", "flux #theta",1800,1000);
	gPad->SetLogy();
	gPad->SetGridy();
	gPad->SetGridx();
        hhit_theta_45cm_gem2->SetLineColor(1);	
        hhit_theta_45cm_gem2->GetYaxis()->SetTitle("rate (Hz)");	
        hhit_theta_45cm_gem2->GetXaxis()->SetTitle("hit #theta");	
        hhit_theta_45cm_gem2->SetTitle("in front of the preshower ");	
      //  hhit_theta_45cm_gem2->Scale(1e-6);
        hhit_theta_45cm_gem2->Rebin(rebinfac);
        hhit_theta_45cm_gem2->GetYaxis()->SetRangeUser(1e-3,1e2);	
        hhit_theta_45cm_gem2->GetXaxis()->SetRangeUser(0,95);	
        hhit_theta_45cm_gem2->Draw("HIST");	
        hhit_theta_25cm_gem2->SetLineColor(2);	
      //  hhit_theta_25cm_gem2->Scale(1e-6);
        hhit_theta_25cm_gem2->Rebin(rebinfac);
        hhit_theta_25cm_gem2->Draw("same HIST");	
        hhit_theta_25cm_gem2_electron->SetLineColor(4);	
       // hhit_theta_25cm_gem2_electron->Scale(1e-6);
        hhit_theta_25cm_gem2_electron->Rebin(rebinfac);
        hhit_theta_25cm_gem2_electron->Draw("same HIST");	
        hhit_theta_45cm_gem2_electron->SetLineColor(6);	
      //  hhit_theta_45cm_gem2_electron->Scale(1e-6);
        hhit_theta_45cm_gem2_electron->Rebin(rebinfac);
        hhit_theta_45cm_gem2_electron->Draw("same HIST");	
	TLegend *leg01 = new TLegend(0.45,0.7,0.8,0.9);
	leg01->AddEntry(hhit_theta_45cm_gem2,"from #pi^{-}","l");
	leg01->AddEntry(hhit_theta_25cm_gem2,"from #pi^{o}","l");
	leg01->AddEntry(hhit_theta_25cm_gem2_electron,"from #pi^{+}","l");
	leg01->AddEntry(hhit_theta_45cm_gem2_electron,"from #pi^{-} tid==1","l");
	leg01->SetTextSize(0.035);
	leg01->SetBorderSize(0);
	leg01->SetFillColor(0);
	leg01->Draw("text same");

	c_gem[2] = new TCanvas("c_gem[2]", "GEM00",1800,1000);
        c_gem[2]->Divide(2,2);
        c_gem[2]->cd(1);
        hhit_mvz_vs_theta_pim->SetTitle("from #pi^{-} at GEM00");
        hhit_mvz_vs_theta_pim->Draw("COLZ");
        c_gem[2]->cd(2);
        hhit_mvz_vs_theta_pi0->SetTitle("from #pi^{0} at GEM00");
        hhit_mvz_vs_theta_pi0->Draw("COLZ");
        c_gem[2]->cd(3);
        hhit_mvz_vs_theta_pip->SetTitle("from #pi^{+} at GEM00");
        hhit_mvz_vs_theta_pip->Draw("COLZ");
        c_gem[2]->cd(4);
        hhit_mvz_vs_theta_pimtid1->SetTitle("from #pi^{-} tid==1 at GEM00");
        hhit_mvz_vs_theta_pimtid1->Draw("COLZ");
	c_gem[3] = new TCanvas("c_gem[3]", "preshower",1800,1000);
        c_gem[3]->Divide(2,2);
        c_gem[3]->cd(1);
        hhit_mvz_vs_theta_gem2_pim->SetTitle(" from #pi^{-} at preshower");
        hhit_mvz_vs_theta_gem2_pim->Draw("COLZ");
        c_gem[3]->cd(2);
        hhit_mvz_vs_theta_gem2_pi0->SetTitle("from #pi^{0} at preshower");
        hhit_mvz_vs_theta_gem2_pi0->Draw("COLZ");
        c_gem[3]->cd(3);
        hhit_mvz_vs_theta_gem2_pip->SetTitle(" from #pi^{+} at preshower");
        hhit_mvz_vs_theta_gem2_pip->Draw("COLZ");
        c_gem[3]->cd(4);
        hhit_mvz_vs_theta_gem2_pimtid1->SetTitle("from #pi^{-} tid==1 at preshower");
        hhit_mvz_vs_theta_gem2_pimtid1->Draw("COLZ");
	c_gem[4] = new TCanvas("c_gem[4]", "GEM00",1800,1000);
        c_gem[4]->Divide(2,2);
        c_gem[4]->cd(1);
        hhit_mvz_vs_E_pim->SetTitle("from #pi^{-} at GEM00");
        hhit_mvz_vs_E_pim->Draw("COLZ");
        c_gem[4]->cd(2);
        hhit_mvz_vs_E_pi0->SetTitle("from #pi^{0} at GEM00");
        hhit_mvz_vs_E_pi0->Draw("COLZ");
        c_gem[4]->cd(3);
        hhit_mvz_vs_E_pip->SetTitle("from #pi^{+} at GEM00");
        hhit_mvz_vs_E_pip->Draw("COLZ");
        c_gem[4]->cd(4);
        hhit_mvz_vs_E_pimtid1->SetTitle("from #pi^{-} tid==1 at GEM00");
        hhit_mvz_vs_E_pimtid1->Draw("COLZ");
	c_gem[5] = new TCanvas("c_gem[5]", "preshower",1800,1000);
        c_gem[5]->Divide(2,2);
        c_gem[5]->cd(1);
        hhit_mvz_vs_E_gem2_pim->SetTitle(" from #pi^{-} at preshower");
        hhit_mvz_vs_E_gem2_pim->Draw("COLZ");
        c_gem[5]->cd(2);
        hhit_mvz_vs_E_gem2_pi0->SetTitle("from #pi^{0} at preshower");
        hhit_mvz_vs_E_gem2_pi0->Draw("COLZ");
        c_gem[5]->cd(3);
        hhit_mvz_vs_E_gem2_pip->SetTitle(" from #pi^{+} at preshower");
        hhit_mvz_vs_E_gem2_pip->Draw("COLZ");
        c_gem[5]->cd(4);
        hhit_mvz_vs_E_gem2_pimtid1->SetTitle("from #pi^{-} tid==1 at preshower");
        hhit_mvz_vs_E_gem2_pimtid1->Draw("COLZ");
	c_gem[6] = new TCanvas("c_gem[6]", "GEM00",1800,1000);
        c_gem[6]->Divide(2,2);
        c_gem[6]->cd(1);
        hhit_p_vs_theta_pim->SetTitle("from #pi^{-} at GEM00");
        hhit_p_vs_theta_pim->Draw("COLZ");
        c_gem[6]->cd(2);
        hhit_p_vs_theta_pi0->SetTitle("from #pi^{0} at GEM00");
        hhit_p_vs_theta_pi0->Draw("COLZ");
        c_gem[6]->cd(3);
        hhit_p_vs_theta_pip->SetTitle("from #pi^{+} at GEM00");
        hhit_p_vs_theta_pip->Draw("COLZ");
        c_gem[6]->cd(4);
        hhit_p_vs_theta_pimtid1->SetTitle("from #pi^{-} tid==1 at GEM00");
        hhit_p_vs_theta_pimtid1->Draw("COLZ");
	c_gem[7] = new TCanvas("c_gem[7]", "preshower",1800,1000);
        c_gem[7]->Divide(2,2);
        c_gem[7]->cd(1);
        hhit_p_vs_theta_gem2_pim->SetTitle(" from #pi^{-} at preshower");
        hhit_p_vs_theta_gem2_pim->Draw("COLZ");
        c_gem[7]->cd(2);
        hhit_p_vs_theta_gem2_pi0->SetTitle("from #pi^{0} at preshower");
        hhit_p_vs_theta_gem2_pi0->Draw("COLZ");
        c_gem[7]->cd(3);
        hhit_p_vs_theta_gem2_pip->SetTitle(" from #pi^{+} at preshower");
        hhit_p_vs_theta_gem2_pip->Draw("COLZ");
        c_gem[7]->cd(4);
        hhit_p_vs_theta_gem2_pimtid1->SetTitle("from #pi^{-} tid==1 at preshower");
        hhit_p_vs_theta_gem2_pimtid1->Draw("COLZ");
 	for(int a=0;a<8;a++){
		c_gem[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_Espectrum_full_scattering_20deg_theta.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));
}
