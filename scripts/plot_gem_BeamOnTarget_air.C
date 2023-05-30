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

void plot_gem_BeamOnTarget_air(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f1 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_TGonly_kryptonite2/HallC_beamtest_BeamOnTarget_5.59e8_8deg_80uA_air_kryptonite2_output_gem_gammaE_pzcut.root");
	//TFile *f1 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_2.435e11_8deg_80uA_newCH_output_gem_electron.root");
	//TFile *f2 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_sangle/HallC_beamtest_eAll_sangle_8deg_filenum100_newCH_output_gem_gamma.root");
	TFile *f2 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_TGonly_kryptonite2/HallC_beamtest_BeamOnTarget_5.59e8_8deg_80uA_air_kryptonite2_output_gem_electronE_pzcut.root");
	TFile *f3 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_TGonly_kryptonite2/HallC_beamtest_BeamOnTarget_5.59e8_8deg_80uA_air_kryptonite2_output_gem_gammaE_pzcut_vzcut.root");
	TFile *f4 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_TGonly_kryptonite2/HallC_beamtest_BeamOnTarget_5.59e8_8deg_80uA_air_kryptonite2_output_gem_electronE_pzcut_vzcut.root");
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_vacuum_nospd/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_target_vacuum_nospd_output_gem_gammaE_pzcut.root");
	TFile *f6 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_vacuum_nospd/HallC_beamtest_BeamOnTarget_1e10_8deg_80uA_target_vacuum_nospd_output_gem_electronE_pzcut_vzcut.root");
	TH1F *hprocid_gem1;       
	TH1F *hpf_gem1;
	TH1F *hE_gem1;
	TH1F *hE_gem1_cut;
	TH1F *hpf_gem1_1cmAl;
	TH1F *hpf_gem1_1cmAl_cut;
	TH1F *hE_gem1_1inpoly;
	TH1F *hhit_Egem1_procID[11];
	TH1F *hhit_Egem1_procID_electron[11];
	TH1F *hhit_Egem2_procID[11];
	TH1F *hhit_Egem1;
	TH1F *hhit_Egem1_gamma;
	TH1F *hhit_Egem1_electron;
	TH1F *hhit_Egem1_other;
	TH1F *hhit_Egem1_pi0;
	TH1F *hhit_Edepgem1_procID[11];
	TH1F *hhit_Edepgem2_procID[11];
	TH1F *hhit_Edepgem1;
	TH1F *hhit_Edepgem1_gamma;
	TH1F *hhit_Edepgem1_electron;
	TH1F *hhit_Edepgem1_other;
	TH1F *hhit_Edepgem1_pi0;
	TH1F *hhit_Edepgem1_electron_1cmAl;
	TH1F *hhit_Edepgem1_electron_1inpoly;
        TH2F *vertexZ_vs_vertexR_hist;
        TH2F *vertexZ_vs_vertexR_gem2_hist;
        TH2F *vertexX_vs_vertexY_hist;
        TH2F *vertexX_vs_vertexY_gem2_hist;
        TH2F *vertexZ_vs_vertexR_electron_hist;
        TH2F *vertexZ_vs_vertexR_nospd_hist;
        TH2F *vertexZ_vs_vertexR_nospd_electron_hist;
        TH2F *vertexZ_vs_E_hist;
        TH2F *vertexZ_vs_E_electron_hist;
	TH1F *hhit_theta_gem1;
	TH1F *hhit_theta_electron_gem1;
        hprocid_gem1 = (TH1F*)f1->Get("procid_gem1");
        hpf_gem1 = (TH1F*)f1->Get("hpf_gem1");
        hhit_theta_gem1 = (TH1F*)f1->Get("gen_Theta_gem1");
        hhit_theta_electron_gem1 = (TH1F*)f2->Get("gen_Theta_gem1");
        hhit_theta_cut_gem1 = (TH1F*)f3->Get("gen_Theta_gem1");
        hhit_theta_cut_electron_gem1 = (TH1F*)f4->Get("gen_Theta_gem1");
        vertexZ_vs_vertexR_hist = (TH2F*)f1->Get("vertexZ_vs_vertexR_hist");
        vertexZ_vs_vertexR_gem2_hist = (TH2F*)f1->Get("vertexZ_vs_vertexR_gem2_hist");
        vertexX_vs_vertexY_hist = (TH2F*)f1->Get("vertexX_vs_vertexY_hist");
        vertexX_vs_vertexY_gem2_hist = (TH2F*)f1->Get("vertexX_vs_vertexY_gem2_hist");
        vertexZ_vs_vertexR_electron_hist = (TH2F*)f2->Get("vertexZ_vs_vertexR_hist");
        vertexZ_vs_vertexR_nospd_hist = (TH2F*)f5->Get("vertexZ_vs_vertexR_hist");
        vertexZ_vs_vertexR_nospd_electron_hist = (TH2F*)f6->Get("vertexZ_vs_vertexR_hist");
        vertexZ_vs_E_hist = (TH2F*)f1->Get("vertexZ_vs_E_hist");
        vertexZ_vs_E_electron_hist = (TH2F*)f2->Get("vertexZ_vs_E_hist");
        hE_gem1 = (TH1F*)f1->Get("hE_gem1");
        hE_gem1_cut = (TH1F*)f3->Get("hE_gem1");
        hhit_Egem1 = (TH1F*)f1->Get("hit_Egem1");
        hhit_Egem1_electron = (TH1F*)f2->Get("hit_Egem1");
        hhit_Egem1_gamma = (TH1F*)f1->Get("hit_Egem1_gamma");
        hhit_Egem1_pi0 = (TH1F*)f1->Get("hit_Egem1_pi0");
        hhit_Egem1_other = (TH1F*)f1->Get("hit_Egem1_other");
        hhit_Edepgem1 = (TH1F*)f1->Get("hit_Edepgem1");
        hhit_Edepgem1_electron = (TH1F*)f2->Get("hit_Edepgem1");
        hhit_Edepgem1_gamma = (TH1F*)f1->Get("hit_Edepgem1_gamma");
        hhit_Edepgem1_pi0 = (TH1F*)f1->Get("hit_Edepgem1_pi0");
        hhit_Edepgem1_other = (TH1F*)f1->Get("hit_Edepgem1_other");
        hhit_Edepgem1_electron_1cmAl = (TH1F*)f2->Get("hit_Edepgem1_electron");
        hhit_Edepgem1_electron_1inpoly = (TH1F*)f3->Get("hit_Edepgem1_electron");
        hpf_gem1_1cmAl = (TH1F*)f2->Get("hpf_gem1");
        hE_gem1_1cmAl = (TH1F*)f2->Get("hE_gem1");
        hE_gem1_1cmAl_cut = (TH1F*)f4->Get("hE_gem1");
        hpf_gem1_1inpoly = (TH1F*)f3->Get("hpf_gem1");
        hE_gem1_1inpoly = (TH1F*)f3->Get("hE_gem1");
	for(int k=0;k<11;k++){
		hhit_Edepgem1_procID[k]=(TH1F*)f1->Get(Form("hit_Edepgem1_procID%d",k));
		hhit_Edepgem2_procID[k]=(TH1F*)f1->Get(Form("hit_Edepgem2_procID%d",k));
		hhit_Egem1_procID[k]=(TH1F*)f1->Get(Form("hit_Egem1_procID%d",k));
		hhit_Egem1_procID_electron[k]=(TH1F*)f2->Get(Form("hit_Egem1_procID%d",k));
		hhit_Egem2_procID[k]=(TH1F*)f1->Get(Form("hit_Egem2_procID%d",k));
        }
	TCanvas *c_gem[6];
	/*	c_gem[0] = new TCanvas("c_gem[0]", "gem1",1800,1000);
		c_gem[0]->Divide(3,2);
		c_gem[0]->cd(1);
		gPad->SetLogy();
		vertex_Z_hist->SetTitle("vertex Z");
		vertex_Z_hist->Draw("HIST");
		c_gem[0]->cd(2);
		gPad->SetLogy();
		gPad->SetLogx();
		vertex_R_hist->SetTitle("vertex R");
		vertex_R_hist->Draw("HIST");
		c_gem[0]->cd(3);
		gPad->SetLogy();
		vertexZ_vs_vertexR_hist->Draw("COLZ");
		c_gem[0]->cd(4);
		hit_Z_hist->SetTitle("hit Z");
		hit_Z_hist->Draw("HIST");
		c_gem[0]->cd(5);
		hit_R_hist->SetTitle("hit R");
		hit_R_hist->Draw("HIST");
		c_gem[0]->cd(6);
		hitZ_vs_hitR_hist->Draw("COLZ");
		c_gem[1] = new TCanvas("c_gem[1]", "vertexz",1800,1000);
		c_gem[1]->Divide(2,2);
		c_gem[1]->cd(1);
		gPad->SetLogy();
		vertexZ_vs_E_hist->Draw("COLZ");
		vertexZ_vs_E_hist->SetTitle("all process");
		c_gem[1]->cd(2);
		mvertexZ_vs_E_cut_hist->SetMarkerColor(2);
		mvertexZ_vs_E_hist->SetTitle("e ionization");
		mvertexZ_vs_E_hist->Draw("COLZ");
		mvertexZ_vs_E_cut_hist->Draw("same");
		TLegend *leg = new TLegend(0.6,0.4,0.85,0.8);
		leg->AddEntry(mvertexZ_vs_E_hist,"all process","p");
		leg->AddEntry(mvertexZ_vs_E_cut_hist,"decay","p");
		leg->SetTextSize(0.05);
		leg->SetBorderSize(0);
		leg->SetFillColor(0);
		leg->Draw("text same");
		c_gem[1]->cd(3);
		vertexZ_vs_vertexR_cut_hist->GetYaxis()->SetRangeUser(0,5);
		vertexZ_vs_vertexR_cut_hist->GetXaxis()->SetRangeUser(-40,200);
		vertexZ_vs_vertexR_cut_hist->Draw("COLZ");*/
	c_gem[4] = new TCanvas("c_gem[4]", "gem1",1800,1000);
        c_gem[4]->Divide(2,2);
        c_gem[4]->cd(1);
	gPad->SetGridy();
	gPad->SetGridx();
	gPad->SetLogz();
        vertexZ_vs_vertexR_gem2_hist->SetTitle("#gamma gem2");
        vertexZ_vs_vertexR_gem2_hist->Draw("COLZ");
        vertexZ_vs_vertexR_gem2_hist->GetYaxis()->SetRangeUser(0,220);
        vertexZ_vs_vertexR_hist->SetMarkerColor(1);
        //vertexZ_vs_vertexR_hist->Draw("same");
        c_gem[4]->cd(2);
	gPad->SetGridy();
	gPad->SetGridx();
	gPad->SetLogz();
        vertexZ_vs_vertexR_hist->SetTitle("#gamma gem1");
        vertexZ_vs_vertexR_hist->GetYaxis()->SetRangeUser(0,220);
        vertexZ_vs_vertexR_hist->Draw("COLZ");
        c_gem[4]->cd(3);
	gPad->SetGridy();
	gPad->SetGridx();
	gPad->SetLogz();
        vertexX_vs_vertexY_gem2_hist->SetTitle("#gamma gem2");
        vertexX_vs_vertexY_gem2_hist->Draw("COLZ");
        vertexX_vs_vertexY_gem2_hist->GetYaxis()->SetRangeUser(-20,30);
        vertexX_vs_vertexY_hist->SetMarkerColor(1);
        //vertexZ_vs_vertexR_hist->Draw("same");
        c_gem[4]->cd(4);
	gPad->SetGridy();
	gPad->SetGridx();
	gPad->SetLogz();
        vertexX_vs_vertexY_hist->SetTitle("#gamma gem1");
        vertexX_vs_vertexY_hist->GetYaxis()->SetRangeUser(-20,30);
        vertexX_vs_vertexY_hist->Draw("COLZ");
/*	gPad->SetLogy();
	hprocid_gem1->GetYaxis()->SetRangeUser(1e0,1e10);
	hprocid_gem1->Draw("HIST");
	TLatex latex;
	latex.SetTextSize(0.03);
	latex.SetTextAlign(13);  //align at top
	latex.DrawLatex(70,9e5,"1:e  ionization");

	TLatex latex1;
	latex1.SetTextSize(0.03);
	latex1.SetTextAlign(13);  //align at top
	latex1.DrawLatex(70,5.0e5,"2:  compton scattering");

	TLatex latex2;
	latex2.SetTextSize(0.03);
	latex2.SetTextAlign(13);  //align at top
	latex2.DrawLatex(70,2e5,"3:  e bremsstrahlung");

	TLatex latex3;
	latex3.SetTextSize(0.03);
	latex3.SetTextAlign(13);  //align at top
	latex3.DrawLatex(70,7e4,"4:  photo electric effect");

	TLatex latex4;
	latex4.SetTextSize(0.03);
	latex4.SetTextAlign(13);  //align at top
	latex4.DrawLatex(70,3e4,"5:  gamma conversion");

	TLatex latex6;
	latex6.SetTextSize(0.03);
	latex6.SetTextAlign(13);  //align at top
	latex6.DrawLatex(70,7e3,"6:  e^{+} Annihilation");
	TLatex latex7;
	latex7.SetTextSize(0.03);
	latex7.SetTextAlign(13);  //align at top
	latex7.DrawLatex(70,3e3,"7:  photon-Muclear");*/

	c_gem[5] = new TCanvas("c_gem[5]", "gem1",1800,1000);
	gPad->SetLogy();
	gPad->SetGridy();
	gPad->SetGridx();
	//hpf_gem1->SetLineColor(1);
	//hpf_gem1->Draw("HIST");
	hE_gem1->SetLineColor(1);
	hE_gem1->GetYaxis()->SetRangeUser(1e0,1e10);
	hE_gem1->Draw("HIST ");
	hE_gem1_1cmAl->SetLineColor(4);
	hE_gem1_1cmAl->Draw("same HIST");
	hE_gem1_1cmAl_cut->SetLineColor(2);
	hE_gem1_1cmAl_cut->Draw("same HIST");
	hE_gem1_cut->SetLineColor(6);
	hE_gem1_cut->Draw("same HIST");
	//hE_gem1_1inpoly->SetLineColor(2);
//	hE_gem1_1inpoly->Draw("same HIST");
	TLegend *leg11 = new TLegend(0.45,0.67,0.65,0.85);
	leg11->AddEntry(hE_gem1,"#gamma hit on gem1","l");
	leg11->AddEntry(hE_gem1_1cmAl,"e^{-} hit on gem1","l");
	leg11->AddEntry(hE_gem1_cut,"#gamma from target hit on gem1","l");
	leg11->AddEntry(hE_gem1_1cmAl_cut,"e^{-} from target hit on gem1","l");
	leg11->SetTextSize(0.05);
	leg11->SetBorderSize(0);
	leg11->SetFillColor(0);
	leg11->Draw("text same");

	c_gem[2] = new TCanvas("c_gem[2]", "flux",1800,1000);
	gPad->SetLogy();
	gPad->SetGridy();
	gPad->SetGridx();
	hhit_Egem1_procID[1]->SetLineColor(1);
	hhit_Egem1_procID[1]->GetYaxis()->SetRangeUser(1e0,1e10);
	hhit_Egem1_procID[1]->SetTitle("#gamma hit on gem1");
	hhit_Egem1_procID[1]->Draw("HIST");
	for(int n=2;n<8;n++){
		hhit_Egem1_procID[n]->SetLineColor(n);
		hhit_Egem1_procID[n]->Draw("same HIST");
	}
	hhit_Egem1_procID[8]->SetLineColor(28);
	hhit_Egem1_procID[8]->Draw("same HIST");
	TLegend *leg12 = new TLegend(0.7,0.6,0.85,0.9);
	leg12->AddEntry(hhit_Egem1_procID[1],"e ionization","l");
	leg12->AddEntry(hhit_Egem1_procID[2],"compton scattering","l");
	leg12->AddEntry(hhit_Egem1_procID[3],"e bremsstrahlung","l");
	leg12->AddEntry(hhit_Egem1_procID[4],"photo electric effect","l");
	leg12->AddEntry(hhit_Egem1_procID[5],"gama conversion","l");
	leg12->AddEntry(hhit_Egem1_procID[6],"e^{+} Annihilation","l");
	leg12->AddEntry(hhit_Egem1_procID[7],"photon-nuclear","l");
	leg12->AddEntry(hhit_Egem1_procID[8],"electron-nuclear","l");
	leg12->SetTextSize(0.035);
	leg12->SetBorderSize(0);
	leg12->SetFillColor(0);
	leg12->Draw("text same");
	c_gem[3] = new TCanvas("c_gem[3]", "flux",1800,1000);
	gPad->SetLogy();
	gPad->SetGridy();
	gPad->SetGridx();
/*	hhit_Egem1_pi0->SetLineColor(2);
	hhit_Egem1_pi0->Draw("same HIST");
	hhit_Egem1_gamma->SetLineColor(7);
	hhit_Egem1_gamma->Draw("same HIST");*/
	hhit_Egem1_electron->SetLineColor(2);
	hhit_Egem1_electron->SetTitle("flux on virtual plane");
	hhit_Egem1_electron->GetYaxis()->SetRangeUser(1e0,1e10);
	hhit_Egem1_electron->Draw("HIST");
	hhit_Egem1->SetLineColor(1);
	hhit_Egem1->Draw("same HIST");
/*	hhit_Egem1_other->SetLineColor(6);
	hhit_Egem1_other->Draw("same HIST");*/
	TLegend *leg1 = new TLegend(0.61,0.8,0.88,0.88);
	leg1->AddEntry(hhit_Egem1,"photon hit on gem1","l");
//	leg1->AddEntry(hhit_Egem1_pi0,"mpid=#pi^{0}","l");
//	leg1->AddEntry(hhit_Egem1_gamma,"mpid=22","l");
	leg1->AddEntry(hhit_Egem1_electron,"e^{-} hit on gem1","l");
//	leg1->AddEntry(hhit_Egem1_other,"other","l");
	leg1->SetTextSize(0.05);
	leg1->SetBorderSize(0);
	leg1->SetFillColor(0);
	leg1->Draw("text same");
	c_gem[1] = new TCanvas("c_gem[1]", "gem1_depositE",1800,1000);
	gPad->SetLogy();
	gPad->SetGridy();
	gPad->SetGridx();
	hhit_Egem1_procID_electron[1]->SetLineColor(1);
	hhit_Egem1_procID_electron[1]->SetTitle("e^{-} hit on gem1");
	hhit_Egem1_procID_electron[1]->GetYaxis()->SetRangeUser(1e0,1e10);
	hhit_Egem1_procID_electron[1]->Draw("HIST");
	for(int n=2;n<8;n++){
		hhit_Egem1_procID_electron[n]->SetLineColor(n);
		hhit_Egem1_procID_electron[n]->Draw("same HIST");
	}
	hhit_Egem1_procID_electron[8]->SetLineColor(28);
	hhit_Egem1_procID_electron[8]->Draw("same HIST");
	TLegend *leg121 = new TLegend(0.12,0.4,0.35,0.7);
	leg121->AddEntry(hhit_Egem1_procID_electron[1],"e ionization","l");
	leg121->AddEntry(hhit_Egem1_procID_electron[2],"compton scattering","l");
	leg121->AddEntry(hhit_Egem1_procID_electron[3],"e bremsstrahlung","l");
	leg121->AddEntry(hhit_Egem1_procID_electron[4],"photo electric effect","l");
	leg121->AddEntry(hhit_Egem1_procID_electron[5],"gama conversion","l");
	leg121->AddEntry(hhit_Egem1_procID_electron[6],"e^{+} Annihilation","l");
	leg121->AddEntry(hhit_Egem1_procID_electron[7],"photon-nuclear","l");
	leg121->AddEntry(hhit_Egem1_procID_electron[8],"electron-nuclear","l");
	leg121->SetTextSize(0.05);
	leg121->SetBorderSize(0);
	leg121->SetFillColor(0);
	leg121->Draw("text same");


	c_gem[0] = new TCanvas("c_gem[0]", "gem1_theta",1800,1000);
	gPad->SetLogy();
	gPad->SetGridy();
	gPad->SetGridx();
        hhit_theta_electron_gem1->SetTitle("hit #theta (deg)");
        hhit_theta_electron_gem1->GetXaxis()->SetTitle("hit #theta (deg)");
        hhit_theta_electron_gem1->GetYaxis()->SetTitle("Rate (Hz)");
	hhit_theta_electron_gem1->GetYaxis()->SetRangeUser(1e0,1e10);
        hhit_theta_electron_gem1->SetLineColor(2);
        hhit_theta_electron_gem1->GetXaxis()->SetRangeUser(0,100);
        hhit_theta_electron_gem1->Draw("HIST");
        hhit_theta_gem1->SetLineColor(1);
        hhit_theta_gem1->Draw("same HIST");
        hhit_theta_cut_gem1->SetLineColor(4);
        hhit_theta_cut_gem1->Draw("same HIST");
        hhit_theta_cut_electron_gem1->SetLineColor(6);
        hhit_theta_cut_electron_gem1->Draw("same HIST");
	TLegend *leg111 = new TLegend(0.5,0.75,0.85,0.88);
	leg111->AddEntry(hhit_theta_electron_gem1,"e^{-} hit gem1","l");
	leg111->AddEntry(hhit_theta_cut_electron_gem1,"e^{-} from target hit gem1","l");
	leg111->AddEntry(hhit_theta_gem1,"#gamma hit gem1","l");
	leg111->AddEntry(hhit_theta_cut_gem1,"#gamma from target hit gem1","l");
	leg111->SetTextSize(0.05);
	leg111->SetBorderSize(0);
	leg111->SetFillColor(0);
	leg111->Draw("text same");
	for(int a=0;a<6;a++){
		c_gem[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_BeamOnTarget_8deg_gem1_gamma_TGonly.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));
}
