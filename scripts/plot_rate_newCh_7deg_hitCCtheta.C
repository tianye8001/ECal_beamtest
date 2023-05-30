
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
	TFile *f7 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.594e9_7deg_80uA_5x10SC_r10m_cfoil_10.6GeV_reduce_tree_rate_CC_Etotalcut_e.root");
	TTree *tree_eAll = (TTree*) f7->Get("T");
	const int rebinfac=1;
	/*	int ndata = tree_eAll->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g1 = new TGraph(ndata, tree_eAll->GetV2(),tree_eAll->GetV1());
		int ndata2 = tree_eAll_beamline->Draw("(GEM00_x-GEM10_x):(GEM00_y-GEM10_y)",
		"GEM00_n>0 && GEM10_n>0","");
		TGraph* g2 = new TGraph(ndata2, tree_eAll_beamline->GetV2(),tree_eAll_beamline->GetV1());
		*/
       /* tree_pip->Draw("ShowerSum>>shower_pip(200,0,1200)","rate*( ShowerSum>0)","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_pim->Draw("ShowerSum>>shower_pim(200,0,1200)","rate*( ShowerSum>0)","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_pi0->Draw("ShowerSum>>shower_pi0(200,0,1200)","rate*( ShowerSum>0)","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("ShowerSum>>shower_eAll(200,0,1200)","rate*( ShowerSum>0 && GEM00_Edep>35e-6 && GEM10_Edep>35e-6)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_beam->Draw("ShowerSum>>shower_beam(200,0,1200)","rate*( ShowerSum>0)","goff");
	TH1F *shower_beam_hist = (TH1F*)gROOT->FindObject("shower_beam");*/
  //      tree_beam_dum->Draw("ShowerSum>>shower_beam_dum(600,0,1200)","rate*( ShowerSum>0)","goff");
//	TH1F *shower_beam_dum_hist = (TH1F*)gROOT->FindObject("shower_beam_dum");
        tree_eAll->Draw("Npesum>>shower_pip(30,0.5,30.5)","rate*(abs(GEM00_x)<2 && abs(GEM10_x)<2 && ShowerSum>900)","goff");
	TH1F *shower_pip_hist = (TH1F*)gROOT->FindObject("shower_pip");
        tree_eAll->Draw("Npesum>>shower_pim(30,0.5,30.5)","rate*(abs(GEM00_x)<2 && abs(GEM00_y)<2 )","goff");
	TH1F *shower_pim_hist = (TH1F*)gROOT->FindObject("shower_pim");
        tree_eAll->Draw("Npesum>>shower_pi0(30,0.5,30.5)","rate*(ShowerSum>800 )","goff");
	TH1F *shower_pi0_hist = (TH1F*)gROOT->FindObject("shower_pi0");
        tree_eAll->Draw("Npesum>>shower_eAll(30,0.5,30.5)","rate*(ShowerSum>1100)","goff");
	TH1F *shower_eAll_hist = (TH1F*)gROOT->FindObject("shower_eAll");
        tree_eAll->Draw("PreShP:PreShtheta>>shower_beam(360,0,180,500,0,250)","rate","goff");
	TH2F *shower_beam_hist = (TH2F*)gROOT->FindObject("shower_beam");
        tree_eAll->Draw("Npesum>>shower_all(30,0.5,30.5)","rate*(Npesum>0)","goff");
	TH1F *shower_all_hist = (TH1F*)gROOT->FindObject("shower_all");
       /* tree_beam_dum->Draw("ShowerSum>>shower_beam_dum(200,0,1200)","rate*(ShowerSum>600 && Shower_t>5.8)","goff");
        TH1F *shower_beam_dum_hist = (TH1F*)gROOT->FindObject("shower_beam_dum");*/
        tree_eAll->Draw("PreShtheta>>theta_pip(360,0.5,180.5)","rate*(PreShP>150 && PreShP<250)","goff");
	TH1F *theta_pip_hist = (TH1F*)gROOT->FindObject("theta_pip");
        tree_eAll->Draw("PreShtheta>>theta_pim(360,0.5,180.5)","rate*(PreShP>180 && PreShP<220)","goff");
	TH1F *theta_pim_hist = (TH1F*)gROOT->FindObject("theta_pim");
        tree_eAll->Draw("PreShtheta>>theta_pi0(360,0.5,180.5)","rate*(ShowerSum>800)","goff");
	TH1F *theta_pi0_hist = (TH1F*)gROOT->FindObject("theta_pi0");
        tree_eAll->Draw("PreShtheta>>theta_eAll(360,0.5,180.5)","rate*(ShowerSum>1100)","goff");
	TH1F *theta_eAll_hist = (TH1F*)gROOT->FindObject("theta_eAll");
        tree_eAll->Draw("PreShtheta>>theta_beam(360,0.5,180.5)","rate","goff");
	TH1F *theta_beam_hist = (TH1F*)gROOT->FindObject("theta_beam");
        tree_eAll->Draw("PreShtheta>>theta_all(360,0.5,180.5)","rate*(PreShtheta>0)","goff");
	TH1F *theta_all_hist = (TH1F*)gROOT->FindObject("theta_all");
	TCanvas *c[10];
	c[1] = new TCanvas("c[1]","c[1]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
        shower_beam_hist->GetXaxis()->SetTitle("CC_hit #theta (deg)");
        shower_beam_hist->SetTitle("5uA 10.6 GeV e^{-} hit on C-foil target at 7 degrees");
        shower_beam_hist->GetYaxis()->SetTitle("CC_hit p (GeV/c)");
        shower_beam_hist->Draw("COLZ");
        /*shower_pi0_hist->SetLineColor(kOrange-3);
        shower_pi0_hist->Scale(0.001);
        shower_pi0_hist->SetLineWidth(2);
        shower_pi0_hist->Draw("same HIST");
        double rate_pi0= shower_pi0_hist->Integral();
        shower_eAll_hist->SetLineColor(4);
        shower_eAll_hist->Scale(0.001);
        shower_eAll_hist->SetLineWidth(2);
        shower_eAll_hist->Draw("same HIST");
        double rate_eAll= shower_eAll_hist->Integral();
        shower_pip_hist->Draw("same HIST");
        shower_all_hist->SetLineColor(kGreen+2);
        shower_all_hist->Scale(0.001);
        shower_all_hist->SetLineWidth(2);
        shower_all_hist->Draw("same HIST");
        double rate_all= shower_all_hist->Integral();*/
  //      shower_beam_dum_hist->SetLineColor(7);
   //     shower_beam_dum_hist->Scale(0.001);
        //shower_beam_dum_hist->Draw("same HIST");
   //     double rate_beam= shower_beam_dum_hist->Integral();
  //leg8->AddEntry(shower_all_hist,Form("Npe >0 cut; total rate=%f kHz",rate_all),"l");
  //leg8->AddEntry(shower_beam_hist,Form("Shower Edep >800 MeV cut; total rate=%f kHz",rate_proton),"l");
  //leg8->AddEntry(shower_eAll_hist,Form("Shower Edep >1100 MeV cut; rate=%f kHz",rate_eAll),"l");
  //leg8->AddEntry(shower_pim_hist,Form("abs(GEM00_x)<2 && abs(GEM00_y)<2; total rate=%f kHz",rate_pim),"l");
  //leg8->AddEntry(shower_pi0_hist,Form("abs(GEM10_x)<2 && abs(GEM10_y)<2; total rate=%f kHz",rate_pi0),"l");
  //leg8->AddEntry(shower_pip_hist,Form("#splitline{abs(GEM00_x)<2 && abs(GEM10_x)<2}{ && ShowerSum>800; total rate=%f kHz}",rate_pip),"l");
  //leg8->AddEntry(shower_beam_dum_hist,Form("BeamOnTarget dummy; total rate=%f kHz",rate_beam),"l");
	c[0] = new TCanvas("c[0]","c[0]",1000,1000);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogy();
        theta_pip_hist->SetLineColor(2);
        theta_pip_hist->GetXaxis()->SetTitle("hit #theta_{Cer}");
        theta_pip_hist->SetTitle(" e^{-} from target hit on Cer  ");
        theta_pip_hist->GetYaxis()->SetTitle("Rate (kHz)");
        theta_pip_hist->Scale(0.001);
       // theta_beam_hist->GetYaxis()->SetRangeUser(1e-4,1e1);
       // theta_beam_hist->GetXaxis()->SetRangeUser(0,15);
        theta_pip_hist->SetLineWidth(1.5);
        theta_pip_hist->Draw();
        double rate_proton_theta= theta_pip_hist->Integral();
      //  theta_pip_hist->SetLineColor(2);
     //   theta_pip_hist->SetLineWidth(1.5);
    //    theta_pip_hist->Scale(0.001);
   //     theta_pip_hist->Draw("same HIST");
    //    double rate_pip_theta= theta_pip_hist->Integral();
        theta_pim_hist->SetLineColor(4);
        theta_pim_hist->Scale(0.001);
        theta_pim_hist->SetLineWidth(1.5);
 //       theta_pim_hist->Draw("same HIST");
        double rate_pim_theta= theta_pim_hist->Integral();
        /*theta_pi0_hist->SetLineColor(kOrange-3);
        theta_pi0_hist->Scale(0.001);
        theta_pi0_hist->SetLineWidth(1.5);
        theta_pi0_hist->Draw("same HIST");
        double rate_pi0_theta= theta_pi0_hist->Integral();
        theta_eAll_hist->SetLineColor(4);
        theta_eAll_hist->Scale(0.001);
        theta_eAll_hist->SetLineWidth(1.5);
        theta_eAll_hist->Draw("same HIST");
        double rate_eAll_theta= theta_eAll_hist->Integral();
        theta_pip_hist->Draw("same HIST");
        theta_all_hist->SetLineColor(kGreen+2);
        theta_all_hist->Scale(0.001);
        theta_all_hist->SetLineWidth(1.5);
        theta_all_hist->Draw("same HIST");
        double rate_all_theta= theta_all_hist->Integral();*/
  TLegend *leg18 = new TLegend(0.2,0.7,0.6,0.88);
 // leg18->AddEntry(theta_all_hist,Form("#theta_{Cer} >0 cut; total rate=%f kHz",rate_all_theta),"l");
 // leg18->AddEntry(theta_beam_hist,Form("e^{#pm}; total rate=%f kHz",rate_proton_theta),"l");
 // leg18->AddEntry(theta_eAll_hist,Form("Shower Edep >1100 MeV cut; rate=%f kHz",rate_eAll_theta),"l");
 // leg18->AddEntry(theta_pim_hist,Form("e^{#pm} p>180 MeV & p<220 MeV; total rate=%f kHz",rate_pim_theta),"l");
 // leg18->AddEntry(theta_pi0_hist,Form("Shower Edep >800 MeV cut; total rate=%f kHz",rate_pi0_theta),"l");
  leg18->AddEntry(theta_pip_hist,Form("e^{#pm} p>150 MeV & p<250 MeV; total rate=%f kHz",rate_proton_theta),"l");
  //leg8->AddEntry(shower_beam_dum_hist,Form("BeamOnTarget dummy; total rate=%f kHz",rate_beam),"l");
  leg18->SetTextSize(0.03);
  leg18->SetBorderSize(0);
  leg18->SetFillColor(0);
  leg18->Draw("text same");
	for(int a=0;a<2;a++){
		c[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_Npe_rate_7deg.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
