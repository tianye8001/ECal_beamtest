
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

void plot_EC_gem_compare_pip_angle(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_filenum19870_reduce_tree_rate.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_nobeamline_filenum19720_reduce_tree_rate.root");
	TTree *tree_pip_beamline = (TTree*) f5->Get("T");
	TTree *tree_pip_nobeam = (TTree*) f4->Get("T"); //abs(phicut) <5 deg
	const int rebinfac=1;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
	tree_pip_beamline ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_beamline(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pip_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_beamline");
	tree_pip_beamline->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_cut(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<90","goff");
	TH1F *DiffX_gem_pip_beamline_cut_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_cut");
	tree_pip_beamline->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_cut2(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<50","goff");
	TH1F *DiffX_gem_pip_beamline_cut2_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_cut2");
	tree_pip_beamline->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_cut3(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<5","goff");
	TH1F *DiffX_gem_pip_beamline_cut3_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_cut3");
	tree_pip_beamline->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_cut4(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<1","goff");
	TH1F *DiffX_gem_pip_beamline_cut4_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_cut4");

	tree_pip_nobeam ->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_nobeam(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffX_gem_pip_nobeam_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_nobeam");
	tree_pip_nobeam->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_nobeam_cut(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<90","goff");
	TH1F *DiffX_gem_pip_nobeam_cut_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_nobeam_cut");
	tree_pip_nobeam->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_nobeam_cut2(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<50","goff");
	TH1F *DiffX_gem_pip_nobeam_cut2_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_nobeam_cut2");
	tree_pip_nobeam->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_nobeam_cut3(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<5","goff");
	TH1F *DiffX_gem_pip_nobeam_cut3_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_nobeam_cut3");
	tree_pip_nobeam->Draw("(GEM00_x-GEM10_x)>>hist_gem_DiffX_pip_nobeam_cut4(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<1","goff");
	TH1F *DiffX_gem_pip_nobeam_cut4_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffX_pip_nobeam_cut4");
	// 2D plots
	tree_pip_beamline ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_beamline(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pip_beamline_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_beamline");
	tree_pip_beamline->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_cut(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<90","goff");
	TH1F *DiffY_gem_pip_beamline_cut_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_cut");
	tree_pip_beamline->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_cut2(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<50","goff");
	TH1F *DiffY_gem_pip_beamline_cut2_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_cut2");
	tree_pip_beamline->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_cut3(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<5","goff");
	TH1F *DiffY_gem_pip_beamline_cut3_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_cut3");
	tree_pip_beamline->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_cut4(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<1","goff");
	TH1F *DiffY_gem_pip_beamline_cut4_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_cut4");

	tree_pip_nobeam ->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_nobeam(25,-10,10)","GEM00_n>0 && GEM10_n>0","goff");
	TH1F *DiffY_gem_pip_nobeam_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_nobeam");
	tree_pip_nobeam->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_nobeam_cut(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<90","goff");
	TH1F *DiffY_gem_pip_nobeam_cut_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_nobeam_cut");
	tree_pip_nobeam->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_nobeam_cut2(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<50","goff");
	TH1F *DiffY_gem_pip_nobeam_cut2_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_nobeam_cut2");
	tree_pip_nobeam->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_nobeam_cut3(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<5","goff");
	TH1F *DiffY_gem_pip_nobeam_cut3_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_nobeam_cut3");
	tree_pip_nobeam->Draw("(GEM00_y-GEM10_y)>>hist_gem_DiffY_pip_nobeam_cut4(25,-10,10)","GEM00_n>0 && GEM10_n>0 && abs(TMath::ATan2(py,px)*180.0/TMath::Pi())<1","goff");
	TH1F *DiffY_gem_pip_nobeam_cut4_hist = (TH1F*)gROOT->FindObject("hist_gem_DiffY_pip_nobeam_cut4");
	TCanvas *c[10];
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	c[0]->Divide(1,2);
	c[0]->cd(1);
	DiffX_gem_pip_nobeam_hist->SetLineColor(1); 
	DiffX_gem_pip_nobeam_hist->GetXaxis()->SetTitle("GEM00_x-GEM10_x (cm)"); 
	DiffX_gem_pip_nobeam_hist->SetTitle("bggen #pi^{+}"); 
	DiffX_gem_pip_nobeam_hist->GetYaxis()->SetTitle("event"); 
	DiffX_gem_pip_nobeam_hist->Draw("HIST"); 
	DiffX_gem_pip_beamline_hist->SetLineColor(2); 
	DiffX_gem_pip_beamline_hist->Scale(DiffX_gem_pip_nobeam_hist->Integral()/DiffX_gem_pip_beamline_hist->Integral()); 
	DiffX_gem_pip_beamline_hist->Draw("same HIST"); 
	TLegend *leg1 = new TLegend(0.6,0.6,0.88,0.88);
	leg1->AddEntry(DiffX_gem_pip_nobeam_hist,"from bggen #pi^{+}, detector only","l");
	leg1->AddEntry(DiffX_gem_pip_beamline_hist,"from bggen #pi^{+}","l");
	leg1->SetTextSize(0.03);
	leg1->SetBorderSize(0);
	leg1->SetFillColor(0);
	leg1->Draw("text same");
	c[0]->cd(2);
	DiffY_gem_pip_nobeam_hist->SetLineColor(1); 
	DiffY_gem_pip_nobeam_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)"); 
	DiffY_gem_pip_nobeam_hist->SetTitle("bggen #pi^{+}"); 
	DiffY_gem_pip_nobeam_hist->GetYaxis()->SetTitle("event"); 
	DiffY_gem_pip_nobeam_hist->Draw("HIST"); 
	DiffY_gem_pip_beamline_hist->SetLineColor(2); 
	DiffY_gem_pip_beamline_hist->Scale(DiffY_gem_pip_nobeam_hist->Integral()/DiffY_gem_pip_beamline_hist->Integral()); 
	DiffY_gem_pip_beamline_hist->Draw("same HIST"); 
	leg1->Draw("text same");
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
	c[1]->Divide(1,2);
        c[1]->cd(1);
	DiffX_gem_pip_beamline_cut_hist->SetLineColor(4); 
	DiffX_gem_pip_beamline_cut_hist->GetXaxis()->SetTitle("GEM00_x-GEM10_x (cm)"); 
	DiffX_gem_pip_beamline_cut_hist->SetTitle("bggen #pi^{+}"); 
	DiffX_gem_pip_beamline_cut_hist->GetYaxis()->SetTitle("event"); 
	DiffX_gem_pip_beamline_cut_hist->Draw("HIST"); 
	DiffX_gem_pip_beamline_cut2_hist->SetLineColor(7); 
//	DiffX_gem_pip_beamline_cut2_hist->Scale(DiffX_gem_pip_beamline_cut_hist->Integral()/DiffX_gem_pip_beamline_cut2_hist->Integral()); 
	DiffX_gem_pip_beamline_cut2_hist->Draw("same HIST"); 
	DiffX_gem_pip_beamline_cut3_hist->SetLineColor(8); 
//	DiffX_gem_pip_beamline_cut3_hist->Scale(DiffX_gem_pip_beamline_cut_hist->Integral()/DiffX_gem_pip_beamline_cut3_hist->Integral()); 
	DiffX_gem_pip_beamline_cut3_hist->Draw("same HIST"); 
	DiffX_gem_pip_beamline_cut4_hist->SetLineColor(6); 
//	DiffX_gem_pip_beamline_cut4_hist->Scale(DiffX_gem_pip_beamline_cut_hist->Integral()/DiffX_gem_pip_beamline_cut4_hist->Integral()); 
	DiffX_gem_pip_beamline_cut4_hist->Draw("same HIST"); 
	TLegend *leg2 = new TLegend(0.6,0.6,0.88,0.88);
	leg2->AddEntry(DiffX_gem_pip_beamline_cut_hist,"bggen #pi^{+}, abs(#phi)<90","l");
	leg2->AddEntry(DiffX_gem_pip_beamline_cut2_hist,"bggen #pi^{+},abs(#phi)<50","l");
	leg2->AddEntry(DiffX_gem_pip_beamline_cut3_hist,"bggen #pi^{+},abs(#phi)<5","l");
	leg2->AddEntry(DiffX_gem_pip_beamline_cut4_hist,"bggen #pi^{+},abs(#phi)<1","l");
	leg2->SetTextSize(0.03);
	leg2->SetBorderSize(0);
	leg2->SetFillColor(0);
	leg2->Draw("text same");
        c[1]->cd(2);
	DiffY_gem_pip_beamline_cut_hist->SetLineColor(4); 
	DiffY_gem_pip_beamline_cut_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)"); 
	DiffY_gem_pip_beamline_cut_hist->SetTitle("bggen #pi^{+}"); 
	DiffY_gem_pip_beamline_cut_hist->GetYaxis()->SetTitle("event"); 
	DiffY_gem_pip_beamline_cut_hist->Draw("HIST"); 
	DiffY_gem_pip_beamline_cut2_hist->SetLineColor(7); 
//	DiffY_gem_pip_beamline_cut2_hist->Scale(DiffY_gem_pip_beamline_cut_hist->Integral()/DiffY_gem_pip_beamline_cut2_hist->Integral()); 
	DiffY_gem_pip_beamline_cut2_hist->Draw("same HIST"); 
	DiffY_gem_pip_beamline_cut3_hist->SetLineColor(8); 
//	DiffY_gem_pip_beamline_cut3_hist->Scale(DiffY_gem_pip_beamline_cut_hist->Integral()/DiffY_gem_pip_beamline_cut3_hist->Integral()); 
	DiffY_gem_pip_beamline_cut3_hist->Draw("same HIST"); 
	DiffY_gem_pip_beamline_cut4_hist->SetLineColor(6); 
//	DiffY_gem_pip_beamline_cut4_hist->Scale(DiffY_gem_pip_beamline_cut_hist->Integral()/DiffY_gem_pip_beamline_cut4_hist->Integral()); 
	DiffY_gem_pip_beamline_cut4_hist->Draw("same HIST"); 
	leg2->Draw("text same");
	c[2] = new TCanvas("c[2]","c[2]",1000,1000);
	c[2]->Divide(1,2);
        c[2]->cd(1);
	DiffX_gem_pip_nobeam_cut_hist->SetLineColor(4); 
	DiffX_gem_pip_nobeam_cut_hist->GetXaxis()->SetTitle("GEM00_x-GEM10_x (cm)"); 
	DiffX_gem_pip_nobeam_cut_hist->SetTitle("bggen #pi^{+}"); 
	DiffX_gem_pip_nobeam_cut_hist->GetYaxis()->SetTitle("event"); 
	DiffX_gem_pip_nobeam_cut_hist->Draw(" HIST"); 
	DiffX_gem_pip_nobeam_cut2_hist->SetLineColor(7); 
	//DiffX_gem_pip_nobeam_cut2_hist->Scale(DiffX_gem_pip_nobeam_cut_hist->Integral()/DiffX_gem_pip_nobeam_cut2_hist->Integral()); 
	DiffX_gem_pip_nobeam_cut2_hist->Draw("same HIST"); 
	DiffX_gem_pip_nobeam_cut3_hist->SetLineColor(8); 
	//DiffX_gem_pip_nobeam_cut3_hist->Scale(DiffX_gem_pip_nobeam_cut_hist->Integral()/DiffX_gem_pip_nobeam_cut3_hist->Integral()); 
	DiffX_gem_pip_nobeam_cut3_hist->Draw("same HIST"); 
	DiffX_gem_pip_nobeam_cut4_hist->SetLineColor(6); 
	//DiffX_gem_pip_nobeam_cut4_hist->Scale(DiffX_gem_pip_nobeam_cut_hist->Integral()/DiffX_gem_pip_nobeam_cut4_hist->Integral()); 
	DiffX_gem_pip_nobeam_cut4_hist->Draw("same HIST"); 
	TLegend *leg3 = new TLegend(0.6,0.6,0.88,0.88);
	leg3->AddEntry(DiffX_gem_pip_nobeam_cut_hist,"bggen #pi^{+}, abs(#phi)<90, detector only","l");
	leg3->AddEntry(DiffX_gem_pip_nobeam_cut2_hist,"bggen #pi^{+},abs(#phi)<50, detector only","l");
	leg3->AddEntry(DiffX_gem_pip_nobeam_cut3_hist,"bggen #pi^{+},abs(#phi)<5, detector only","l");
	leg3->AddEntry(DiffX_gem_pip_nobeam_cut4_hist,"bggen #pi^{+},abs(#phi)<1, detector only","l");
	leg3->SetTextSize(0.03);
	leg3->SetBorderSize(0);
	leg3->SetFillColor(0);
	leg3->Draw("text same");
        c[2]->cd(2);
	DiffY_gem_pip_nobeam_cut_hist->SetLineColor(4); 
	DiffY_gem_pip_nobeam_cut_hist->GetXaxis()->SetTitle("GEM00_y-GEM10_y (cm)"); 
	DiffY_gem_pip_nobeam_cut_hist->SetTitle("bggen #pi^{+}"); 
	DiffY_gem_pip_nobeam_cut_hist->GetYaxis()->SetTitle("event"); 
	DiffY_gem_pip_nobeam_cut_hist->Draw(" HIST"); 
	DiffY_gem_pip_nobeam_cut2_hist->SetLineColor(7); 
//	DiffY_gem_pip_nobeam_cut2_hist->Scale(DiffY_gem_pip_nobeam_cut_hist->Integral()/DiffY_gem_pip_nobeam_cut2_hist->Integral()); 
	DiffY_gem_pip_nobeam_cut2_hist->Draw("same HIST"); 
	DiffY_gem_pip_nobeam_cut3_hist->SetLineColor(8); 
//	DiffY_gem_pip_nobeam_cut3_hist->Scale(DiffY_gem_pip_nobeam_cut_hist->Integral()/DiffY_gem_pip_nobeam_cut3_hist->Integral()); 
	DiffY_gem_pip_nobeam_cut3_hist->Draw("same HIST"); 
	DiffY_gem_pip_nobeam_cut4_hist->SetLineColor(6); 
//	DiffY_gem_pip_nobeam_cut4_hist->Scale(DiffY_gem_pip_nobeam_cut_hist->Integral()/DiffY_gem_pip_nobeam_cut4_hist->Integral()); 
	DiffY_gem_pip_nobeam_cut4_hist->Draw("same HIST"); 
	leg3->Draw("text same");
	for(int a=0;a<3;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_trigger_gem_comparison_pip_cut.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
