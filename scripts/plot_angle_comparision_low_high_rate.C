
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

void plot_angle_comparision_low_high_rate(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_filenum19870_reduce_tree_rate.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_nobeamline_filenum19720_reduce_tree_rate.root");
	TFile *f6 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_sangle/HallC_beamtest_bggen_LH2_pip_sangle_filenum9520_8deg_reduce_tree_rate.root");
	TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_sangle/HallC_beamtest_bggen_LH2_pip_sangle_filenum9530_nobeamline_8deg_reduce_tree_rate.root");
	TTree *tree_langle = (TTree*) f5->Get("T");
	TTree *tree_sangle = (TTree*) f6->Get("T");
	TTree *tree_langle_nobeam = (TTree*) f4->Get("T"); //abs(phicut) <5 deg
	TTree *tree_sangle_nobeam = (TTree*) f7->Get("T");
	const int rebinfac=1;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
        tree_langle_nobeam->Draw("TMath::ACos(pz/sqrt(px*px+py*py+pz*pz))*180.0/TMath::Pi()>>hist_theta_nobeam(200,0,100)","GEM00_n>0 && GEM10_n>0");
	TH1F *theta_pip_nobeam_hist = (TH1F*)gROOT->FindObject("hist_theta_nobeam");
        tree_langle->Draw("TMath::ACos(pz/sqrt(px*px+py*py+pz*pz))*180.0/TMath::Pi()>>hist_theta(200,0,100)","GEM00_n>0 && GEM10_n>0");
	TH1F *theta_pip_hist = (TH1F*)gROOT->FindObject("hist_theta");
        tree_sangle->Draw("TMath::ACos(pz/sqrt(px*px+py*py+pz*pz))*180.0/TMath::Pi()>>hist_theta_sangle(200,0,100)","GEM00_n>0 && GEM10_n>0");
	TH1F *theta_pip_sangle_hist = (TH1F*)gROOT->FindObject("hist_theta_sangle");
        tree_sangle_nobeam->Draw("TMath::ACos(pz/sqrt(px*px+py*py+pz*pz))*180.0/TMath::Pi()>>hist_theta_sangle_nobeam(200,0,100)","GEM00_n>0 && GEM10_n>0");
	TH1F *theta_pip_sangle_nobeam_hist = (TH1F*)gROOT->FindObject("hist_theta_sangle_nobeam");
// phi angle
        tree_langle_nobeam->Draw("TMath::ATan2(py,px)*180.0/TMath::Pi()>>hist_phi_nobeam(400,-50,50)","GEM00_n>0 && GEM10_n>0");
	TH1F *phi_pip_nobeam_hist = (TH1F*)gROOT->FindObject("hist_phi_nobeam");
        tree_langle->Draw("TMath::ATan2(py,px)*180.0/TMath::Pi()>>hist_phi(400,-50,50)","GEM00_n>0 && GEM10_n>0");
	TH1F *phi_pip_hist = (TH1F*)gROOT->FindObject("hist_phi");
        tree_sangle->Draw("TMath::ATan2(py,px)*180.0/TMath::Pi()>>hist_phi_sangle(400,-50,50)","GEM00_n>0 && GEM10_n>0");
	TH1F *phi_pip_sangle_hist = (TH1F*)gROOT->FindObject("hist_phi_sangle");
        tree_sangle_nobeam->Draw("TMath::ATan2(py,px)*180.0/TMath::Pi()>>hist_phi_sangle_nobeam(400,-50,50)","GEM00_n>0 && GEM10_n>0");
	TH1F *phi_pip_sangle_nobeam_hist = (TH1F*)gROOT->FindObject("hist_phi_sangle_nobeam");
	TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        phi_pip_nobeam_hist->SetLineColor(1);
        phi_pip_nobeam_hist->GetXaxis()->SetTitle("#phi deg");
        phi_pip_nobeam_hist->GetYaxis()->SetTitle("Event");
        phi_pip_nobeam_hist->Draw();
        phi_pip_hist->SetLineColor(2);
	phi_pip_hist->Scale(phi_pip_nobeam_hist->Integral()/phi_pip_hist->Integral()); 
        phi_pip_hist->Draw("same");
        phi_pip_sangle_hist->SetLineColor(6);
	phi_pip_sangle_hist->Scale(phi_pip_nobeam_hist->Integral()/phi_pip_sangle_hist->Integral()); 
        phi_pip_sangle_hist->Draw("same");
        phi_pip_sangle_nobeam_hist->SetLineColor(4);
	phi_pip_sangle_nobeam_hist->Scale(phi_pip_nobeam_hist->Integral()/phi_pip_sangle_nobeam_hist->Integral()); 
        phi_pip_sangle_nobeam_hist->Draw("same");
	TLegend *leg4 = new TLegend(0.12,0.6,0.4,0.88);
	leg4->AddEntry(phi_pip_hist,"bggen #pi^{+}, @ 82 deg","l");
	leg4->AddEntry(phi_pip_sangle_hist,"bggen #pi^{+}, @ 8 deg","l");
	leg4->AddEntry(phi_pip_sangle_nobeam_hist,"#splitline{bggen #pi^{+}, @ 8 deg}{no TarCh and beamline}","l");
	leg4->AddEntry(phi_pip_nobeam_hist,"#splitline{bggen #pi^{+}, @ 82 deg}{no TarCh and beamline}","l");
	leg4->SetTextSize(0.03);
	leg4->SetBorderSize(0);
	leg4->SetFillColor(0);
	leg4->Draw("text same");
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        theta_pip_nobeam_hist->SetLineColor(1);
        theta_pip_nobeam_hist->GetXaxis()->SetTitle("#theta deg");
        theta_pip_nobeam_hist->GetYaxis()->SetTitle("Event");
        theta_pip_nobeam_hist->Draw();
        theta_pip_hist->SetLineColor(2);
	theta_pip_hist->Scale(theta_pip_nobeam_hist->Integral()/theta_pip_hist->Integral()); 
        theta_pip_hist->Draw("same");
        theta_pip_sangle_hist->SetLineColor(6);
	theta_pip_sangle_hist->Scale(theta_pip_nobeam_hist->Integral()/theta_pip_sangle_hist->Integral()); 
        theta_pip_sangle_hist->Draw("same");
        theta_pip_sangle_nobeam_hist->SetLineColor(4);
	theta_pip_sangle_nobeam_hist->Scale(theta_pip_nobeam_hist->Integral()/theta_pip_sangle_nobeam_hist->Integral()); 
        theta_pip_sangle_nobeam_hist->Draw("same");
	TLegend *leg5 = new TLegend(0.32,0.6,0.62,0.88);
	leg5->AddEntry(theta_pip_hist,"bggen #pi^{+}, @ 82 deg","l");
	leg5->AddEntry(theta_pip_sangle_hist,"bggen #pi^{+}, @ 8 deg","l");
	leg5->AddEntry(theta_pip_sangle_nobeam_hist,"#splitline{bggen #pi^{+}, @ 8 deg}{no TarCh and beamline}","l");
	leg5->AddEntry(theta_pip_nobeam_hist,"#splitline{bggen #pi^{+}, @ 82 deg}{no TarCh and beamline}","l");
	leg5->SetTextSize(0.03);
	leg5->SetBorderSize(0);
	leg5->SetFillColor(0);
	leg5->Draw("text same");
	for(int a=0;a<2;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_comparison_pip_angle_8deg_82deg.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
