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
#include <TLatex.h>
using namespace std;

void plot_gem_BeamOnTarget_theta(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f1 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_sangle/HallC_beamtest_eAll_sangle_8deg_filenum100_newCH_8GeV_output_gem_gammaE_prime_pL1GeV.root");
	TFile *f2 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_sangle/HallC_beamtest_eAll_sangle_8deg_filenum100_newCH_8GeV_output_gem_gammaE_prime.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_sangle/HallC_beamtest_bggen_LH2_pip_8deg_filenum19840_newCh_8GeV_output_gem_gammaE_prime.root");
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_sangle/HallC_beamtest_bggen_LH2_pim_8deg_filenum19880_newCh_8GeV_output_gem_gammaE_prime.root");
	const int rebinfac=4;
        TH1F *theta_eAll;
        TH1F *theta_eAll_tid1;
        TH1F *theta_eAll_gem2;
        TH1F *theta_eAll_gem2_tid1;
        TH1F *theta_eAll_cut;
        TH1F *theta_eAll_cut_tid1;
        TH1F *theta_eAll_cut_gem2;
        TH1F *theta_eAll_cut_gem2_tid1;
        TH1F *theta_pim;
        TH1F *theta_pim_tid1;
        TH1F *theta_pim_gem2;
        TH1F *theta_pim_gem2_tid1;
        TH1F *theta_pip;
        TH1F *theta_pip_tid1;
        TH1F *theta_pip_gem2;
        TH1F *theta_pip_gem2_tid1;
        theta_eAll = (TH1F*)f2->Get("gen_Theta_gem1");
        theta_eAll_tid1 = (TH1F*)f2->Get("gen_Theta_gem1_tid1");
        theta_eAll_gem2 = (TH1F*)f2->Get("gen_Theta_gem2");
        theta_eAll_gem2_tid1 = (TH1F*)f2->Get("gen_Theta_gem2_tid1");

        theta_eAll_cut = (TH1F*)f1->Get("gen_Theta_gem1");
        theta_eAll_cut_tid1 = (TH1F*)f1->Get("gen_Theta_gem1_tid1");
        theta_eAll_cut_gem2 = (TH1F*)f1->Get("gen_Theta_gem2");
        theta_eAll_cut_gem2_tid1 = (TH1F*)f1->Get("gen_Theta_gem2_tid1");
        theta_pim = (TH1F*)f5->Get("gen_Theta_gem1");
        theta_pim_tid1 = (TH1F*)f5->Get("gen_Theta_gem1_tid1");
        theta_pim_gem2 = (TH1F*)f5->Get("gen_Theta_gem2");
        theta_pim_gem2_tid1 = (TH1F*)f5->Get("gen_Theta_gem2_tid1");
        theta_pip = (TH1F*)f4->Get("gen_Theta_gem1");
        theta_pip_tid1 = (TH1F*)f4->Get("gen_Theta_gem1_tid1");
        theta_pip_gem2 = (TH1F*)f4->Get("gen_Theta_gem2");
        theta_pip_gem2_tid1 = (TH1F*)f4->Get("gen_Theta_gem2_tid1");
	TCanvas *c_gem[6];

	c_gem[0] = new TCanvas("c_gem[0]", "gem",1800,1000);
        c_gem[0]->Divide(1,2);
        c_gem[0]->cd(1);
	gPad->SetGridy();
	gPad->SetGridx();
	gPad->SetLogy();
        theta_eAll->SetTitle("e^{-} from eAll gem1 ");
        theta_eAll->GetYaxis()->SetTitle("Rate (kHz) ");
        theta_eAll->GetXaxis()->SetTitle("hit #theta (deg) ");
        theta_eAll->SetLineColor(1);
        theta_eAll->Scale(0.001);
        theta_eAll->Rebin(rebinfac);
        theta_eAll->GetXaxis()->SetRangeUser(0,90);	
        theta_eAll->GetYaxis()->SetRangeUser(1e-5,5e2);	
        theta_eAll->Draw("HIST");
        double rate_eAll = theta_eAll->Integral();
        theta_eAll_tid1->SetLineColor(2);
        theta_eAll_tid1->Scale(0.001);
        theta_eAll_tid1->Rebin(rebinfac);
        theta_eAll_tid1->Draw("same HIST");
        double rate_eAll_tid1 = theta_eAll_tid1->Integral();
        theta_eAll_cut_tid1->SetLineColor(4);
        theta_eAll_cut_tid1->Scale(0.001);
        theta_eAll_cut_tid1->Rebin(rebinfac);
        theta_eAll_cut_tid1->Draw("same HIST");
        double rate_eAll_cut_tid1 = theta_eAll_cut_tid1->Integral();
        theta_eAll_cut->SetLineColor(6);
        theta_eAll_cut->Scale(0.001);
        theta_eAll_cut->Rebin(rebinfac);
        theta_eAll_cut->Draw("same HIST");
        double rate_eAll_cut = theta_eAll_cut->Integral();
	TLegend *leg101 = new TLegend(0.5,0.6,0.8,0.8);
	leg101->AddEntry(theta_eAll,Form("e^{-} not from target, total rate = %f kHz",rate_eAll),"l");
	leg101->AddEntry(theta_eAll_tid1,Form("e^{-} from target, total rate= %f kHZ", rate_eAll_tid1),"l");
	leg101->AddEntry(theta_eAll_cut,Form("e^{-} not from target,p>1GeV total rate = %f kHz",rate_eAll_cut),"l");
	leg101->AddEntry(theta_eAll_cut_tid1,Form("e^{-} from target,p>1GeV total rate= %f kHZ", rate_eAll_cut_tid1),"l");
	leg101->SetTextSize(0.05);
	leg101->SetBorderSize(0);
	leg101->SetFillColor(0);
	leg101->Draw("text same");
        c_gem[0]->cd(2);
	gPad->SetGridy();
	gPad->SetGridx();
	gPad->SetLogy();
        theta_eAll_gem2->SetTitle("e^{-} from eAll gem2 ");
        theta_eAll_gem2->GetYaxis()->SetTitle("Rate (kHz) ");
        theta_eAll_gem2->GetXaxis()->SetTitle("hit #theta (deg) ");
        theta_eAll_gem2->SetLineColor(1);
        theta_eAll_gem2->Scale(0.001);
        theta_eAll_gem2->Rebin(rebinfac);
        theta_eAll_gem2->GetXaxis()->SetRangeUser(0,90);	
        theta_eAll_gem2->GetYaxis()->SetRangeUser(1e-5,5e2);	
        theta_eAll_gem2->Draw("HIST");
        double rate_eAll_gem2 = theta_eAll_gem2->Integral();
        theta_eAll_gem2_tid1->SetLineColor(2);
        theta_eAll_gem2_tid1->Scale(0.001);
        theta_eAll_gem2_tid1->Rebin(rebinfac);
        theta_eAll_gem2_tid1->Draw("same HIST");
        double rate_eAll_gem2_tid1 = theta_eAll_gem2_tid1->Integral();
        theta_eAll_cut_gem2_tid1->SetLineColor(4);
        theta_eAll_cut_gem2_tid1->Scale(0.001);
        theta_eAll_cut_gem2_tid1->Rebin(rebinfac);
        theta_eAll_cut_gem2_tid1->Draw("same HIST");
        double rate_eAll_gem2_cut_tid1 = theta_eAll_cut_gem2_tid1->Integral();
        theta_eAll_cut_gem2->SetLineColor(6);
        theta_eAll_cut_gem2->Scale(0.001);
        theta_eAll_cut_gem2->Rebin(rebinfac);
        theta_eAll_cut_gem2->Draw("same HIST");
        double rate_eAll_gem2_cut = theta_eAll_cut_gem2->Integral();
	TLegend *leg102 = new TLegend(0.5,0.6,0.8,0.8);
	leg102->AddEntry(theta_eAll_gem2,Form("e^{-} not from target, total rate = %f kHz",rate_eAll_gem2),"l");
	leg102->AddEntry(theta_eAll_gem2_tid1,Form("e^{-} from target, total rate= %f kHZ", rate_eAll_gem2_tid1),"l");
	leg102->AddEntry(theta_eAll_cut_gem2,Form("e^{-} not from target,p>1GeV total rate = %f kHz",rate_eAll_gem2_cut),"l");
	leg102->AddEntry(theta_eAll_cut_gem2_tid1,Form("e^{-} from target,p>1GeV total rate= %f kHZ", rate_eAll_gem2_cut_tid1),"l");
	leg102->SetTextSize(0.05);
	leg102->SetBorderSize(0);
	leg102->SetFillColor(0);
	leg102->Draw("text same");

	c_gem[1] = new TCanvas("c_gem[1]", "gem",1800,1000);
        c_gem[1]->Divide(1,2);
        c_gem[1]->cd(1);
	gPad->SetGridy();
	gPad->SetGridx();
	gPad->SetLogy();
        theta_pim_tid1->SetTitle("#pi^{-} from bggen #pi^{-} gem1 ");
        theta_pim_tid1->GetYaxis()->SetTitle("Rate (kHz) ");
        theta_pim_tid1->GetXaxis()->SetTitle("hit #theta (deg) ");
        theta_pim_tid1->SetLineColor(2);
        theta_pim_tid1->Scale(0.001);
        theta_pim_tid1->GetXaxis()->SetRangeUser(0,90);	
        theta_pim_tid1->GetYaxis()->SetRangeUser(1e-2,3e1);	
        theta_pim_tid1->Draw("HIST");
        double rate_pim_tid1 = theta_pim_tid1->Integral();
        theta_pim->SetLineColor(1);
        theta_pim->Scale(0.001);
        theta_pim->Draw("same HIST");
        double rate_pim = theta_pim->Integral();
	TLegend *leg111 = new TLegend(0.5,0.6,0.8,0.8);
	leg111->AddEntry(theta_pim,Form("#pi^{-} not from target, total rate = %f kHz",rate_pim),"l");
	leg111->AddEntry(theta_pim_tid1,Form("#pi^{-} from target, total rate= %f kHZ", rate_pim_tid1),"l");
	leg111->SetTextSize(0.05);
	leg111->SetBorderSize(0);
	leg111->SetFillColor(0);
	leg111->Draw("text same");
        c_gem[1]->cd(2);
	gPad->SetGridy();
	gPad->SetGridx();
	gPad->SetLogy();
        theta_pim_gem2_tid1->SetTitle("#pi^{-} from #pi^{-} gem2 ");
        theta_pim_gem2_tid1->GetYaxis()->SetTitle("Rate (kHz) ");
        theta_pim_gem2_tid1->GetXaxis()->SetTitle("hit #theta (deg) ");
        theta_pim_gem2_tid1->SetLineColor(2);
        //theta_eAll_gem2->Rebin(rebinfac);
        theta_pim_gem2_tid1->GetXaxis()->SetRangeUser(0,90);	
        theta_pim_gem2_tid1->Scale(0.001);
        theta_pim_gem2_tid1->GetYaxis()->SetRangeUser(1e-2,3e1);	
        theta_pim_gem2_tid1->Draw("HIST");
        double rate_pim_gem2_tid1 = theta_pim_gem2_tid1->Integral();
        theta_pim_gem2->SetLineColor(1);
        //theta_pim_gem2_tid1->Rebin(rebinfac);
        theta_pim_gem2->Scale(0.001);
        theta_pim_gem2->Draw("same HIST");
        double rate_pim_gem2 = theta_pim_gem2->Integral();
	TLegend *leg112 = new TLegend(0.5,0.6,0.8,0.8);
	leg112->AddEntry(theta_pim_gem2,Form("#pi^{-} not from target, total rate = %f kHz",rate_pim_gem2),"l");
	leg112->AddEntry(theta_pim_gem2_tid1,Form("#pi^{-} from target, total rate= %f kHZ", rate_pim_gem2_tid1),"l");
	leg112->SetTextSize(0.05);
	leg112->SetBorderSize(0);
	leg112->SetFillColor(0);
	leg112->Draw("text same");
	c_gem[2] = new TCanvas("c_gem[2]", "gem",1800,1000);
        c_gem[2]->Divide(1,2);
        c_gem[2]->cd(1);
	gPad->SetGridy();
	gPad->SetGridx();
	gPad->SetLogy();
        theta_pip_tid1->SetTitle("#pi^{+} from bggen #pi^{+} gem1 ");
        theta_pip_tid1->GetYaxis()->SetTitle("Rate (kHz) ");
        theta_pip_tid1->GetXaxis()->SetTitle("hit #theta (deg) ");
        theta_pip_tid1->SetLineColor(2);
        theta_pip_tid1->Scale(0.001);
        theta_pip_tid1->GetXaxis()->SetRangeUser(0,90);	
        theta_pip_tid1->GetYaxis()->SetRangeUser(1e-2,3e1);	
        theta_pip_tid1->Draw("HIST");
        double rate_pip_tid1 = theta_pip_tid1->Integral();
        theta_pip->SetLineColor(1);
        theta_pip->Scale(0.001);
        theta_pip->Draw("same HIST");
        double rate_pip = theta_pip->Integral();
	TLegend *leg111 = new TLegend(0.5,0.6,0.8,0.8);
	leg111->AddEntry(theta_pip,Form("#pi^{+} not from target, total rate = %f kHz",rate_pip),"l");
	leg111->AddEntry(theta_pip_tid1,Form("#pi^{+} from target, total rate= %f kHZ", rate_pip_tid1),"l");
	leg111->SetTextSize(0.05);
	leg111->SetBorderSize(0);
	leg111->SetFillColor(0);
	leg111->Draw("text same");
        c_gem[2]->cd(2);
	gPad->SetGridy();
	gPad->SetGridx();
	gPad->SetLogy();
        theta_pip_gem2_tid1->SetTitle("#pi^{+} from #pi^{+} gem2 ");
        theta_pip_gem2_tid1->GetYaxis()->SetTitle("Rate (kHz) ");
        theta_pip_gem2_tid1->GetXaxis()->SetTitle("hit #theta (deg) ");
        theta_pip_gem2_tid1->SetLineColor(2);
        //theta_eAll_gem2->Rebin(rebinfac);
        theta_pip_gem2_tid1->GetXaxis()->SetRangeUser(0,90);	
        theta_pip_gem2_tid1->Scale(0.001);
        theta_pip_gem2_tid1->GetYaxis()->SetRangeUser(1e-2,3e1);	
        theta_pip_gem2_tid1->Draw("HIST");
        double rate_pip_gem2_tid1 = theta_pip_gem2_tid1->Integral();
        theta_pip_gem2->SetLineColor(1);
        //theta_pim_gem2_tid1->Rebin(rebinfac);
        theta_pip_gem2->Scale(0.001);
        theta_pip_gem2->Draw("same HIST");
        double rate_pip_gem2 = theta_pip_gem2->Integral();
	TLegend *leg112 = new TLegend(0.5,0.6,0.8,0.8);
	leg112->AddEntry(theta_pip_gem2,Form("#pi^{+} not from target, total rate = %f kHz",rate_pip_gem2),"l");
	leg112->AddEntry(theta_pip_gem2_tid1,Form("#pi^{+} from target, total rate= %f kHZ", rate_pip_gem2_tid1),"l");
	leg112->SetTextSize(0.05);
	leg112->SetBorderSize(0);
	leg112->SetFillColor(0);
	leg112->Draw("text same");
 	for(int a=0;a<3;a++){
		c_gem[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_BeamOnTarget_8deg_gem1_gamma_newCh.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));
}
