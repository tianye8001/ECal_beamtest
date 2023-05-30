
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

void plot_beamtest_80uA_8deg_82deg_pi0(){
gStyle->SetOptStat(0);
gStyle->SetPalette(1);
  TFile *f1 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_80uA/HallC_beamtest_bggen_LH2_pi0_80uA_filenum19880_output_Nphe_pi0.root");
  TFile *f2 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_sangle/HallC_beamtest_bggen_LH2_pi0_8deg_filenum11840_output_Nphe_pi0.root");
const int rebinfac=2;
const int rebinfac1=1;
TH1F *EC_shower_pim;
TH1F *EC_shower_pip;
TH1F *EC_preshower_pim;
TH1F *EC_preshower_pip;
TH1F *sc1_pim;
TH1F *sc2_pim;
TH1F *sc1_pip;
TH1F *sc2_pip;
TH1F *hhit_E_pim[9];
TH1F *hhit_p_pim[9];
TH1F *hhit_Edep_pim[9];		  	
TH1F *hhit_E_pip[9];
TH1F *hhit_p_pip[9];
TH1F *hhit_Edep_pip[9];		  	
TH1F *hhit_Edepspd2_pim;
TH1F *hhit_Edepspd2_pip;
TH1F *hhit_Edepspd1_pim;
TH1F *hhit_Edepspd1_pip;
TH2F *hit_R_vs_vz_pim[9];
TH2F *hit_R_vs_vz_pip[9];

 hhit_Edepspd2_pim = (TH1F*)f1->Get("hit_Edepspd2_trigger3");
 hhit_Edepspd2_pip = (TH1F*)f2->Get("hit_Edepspd2_trigger3");
 hhit_Edepspd1_pim = (TH1F*)f1->Get("hit_Edepspd1_trigger3");
 hhit_Edepspd1_pip = (TH1F*)f2->Get("hit_Edepspd1_trigger3");
 EC_shower_pim = (TH1F*)f1->Get("ec_Eend_shower_trigger3");
 EC_shower_pip = (TH1F*)f2->Get("ec_Eend_shower_trigger3");
 EC_preshower_pim = (TH1F*)f1->Get("ec_Eend_preshower_trigger3");
 EC_preshower_pip = (TH1F*)f2->Get("ec_Eend_preshower_trigger3");
 sc1_pim = (TH1F*)f1->Get("hit_Edepsc1_trigger3");
 sc2_pim = (TH1F*)f2->Get("hit_Edepsc2_trigger3");
 sc1_pip = (TH1F*)f1->Get("hit_Edepsc1_trigger3");
 sc2_pip = (TH1F*)f2->Get("hit_Edepsc2_trigger3");
 for(int k=0;k<9;k++){
 hhit_E_pim[k] = (TH1F*)f1->Get(Form("hit_E_cutr_%d",k));
 hhit_p_pim[k] = (TH1F*)f1->Get(Form("hit_momentum_cutr_%d",k));
// hhit_Edep_pim[k] = (TH1F*)f1->Get(Form("hit_Edep_%d",k));
 hhit_E_pip[k] = (TH1F*)f2->Get(Form("hit_E_cutr_%d",k));
 hhit_p_pip[k] = (TH1F*)f2->Get(Form("hit_momentum_cutr_%d",k));
// hhit_Edep_pip[k] = (TH1F*)f2->Get(Form("hit_Edep_%d",k));
 hit_R_vs_vz_pim[k]= (TH2F*)f1->Get(Form("hit_R_vs_vz_cutr_%d",k));
 hit_R_vs_vz_pip[k]= (TH2F*)f2->Get(Form("hit_R_vs_vz_cutr_%d",k));
 }
/* for(int k=0;k<9;k++){
 hhit_E_cut_eAll[k] = (TH1F*)f13->Get(Form("hit_E_cut_%d",k));
 hhit_p_cut_eAll[k] = (TH1F*)f13->Get(Form("hit_momentum_cut_%d",k));
 hhit_E_eAll[k] = (TH1F*)f13->Get(Form("hit_E_%d",k));
 hhit_p_eAll[k] = (TH1F*)f13->Get(Form("hit_momentum_%d",k));
 hhit_E_cut_eAll_nob[k] = (TH1F*)f3->Get(Form("hit_E_cut_%d",k));
 hhit_p_cut_eAll_nob[k] = (TH1F*)f3->Get(Form("hit_momentum_cut_%d",k));
 hhit_E_eAll_nob[k] = (TH1F*)f3->Get(Form("hit_E_%d",k));
 hhit_p_eAll_nob[k] = (TH1F*)f3->Get(Form("hit_momentum_%d",k));
 hit_R_vs_vz_eAll_nob[k]= (TH2F*)f3->Get(Form("hit_R_vs_vz_%d",k));
 hit_R_vs_vz_eAll[k]= (TH2F*)f13->Get(Form("hit_R_vs_vz_%d",k));
 hhit_Edep_eAll[k] = (TH1F*)f13->Get(Form("hit_Edep_%d",k));
 hhit_E_proton[k] = (TH1F*)f7->Get(Form("hit_E_%d",k));
 hhit_p_proton[k] = (TH1F*)f7->Get(Form("hit_momentum_%d",k));
 hhit_E_proton_nob[k] = (TH1F*)f17->Get(Form("hit_E_%d",k));
 hhit_p_proton_nob[k] = (TH1F*)f17->Get(Form("hit_momentum_%d",k));
 hhit_E_pi0[k] = (TH1F*)f10->Get(Form("hit_E_%d",k));
 hhit_p_pi0[k] = (TH1F*)f10->Get(Form("hit_momentum_%d",k));
 hhit_E_pi0_nob[k] = (TH1F*)f20->Get(Form("hit_E_%d",k));
 hhit_p_pi0_nob[k] = (TH1F*)f20->Get(Form("hit_momentum_%d",k));
 hit_R_vs_vz_proton_nob[k]= (TH2F*)f17->Get(Form("hit_R_vs_vz_%d",k));
 hit_R_vs_vz_proton[k]= (TH2F*)f7->Get(Form("hit_R_vs_vz_%d",k));
 hhit_Edep_proton[k] = (TH1F*)f7->Get(Form("hit_Edep_%d",k));
 hhit_E_pim_LD[k] = (TH1F*)f8->Get(Form("hit_E_%d",k));
 hhit_p_pim_LD[k] = (TH1F*)f8->Get(Form("hit_momentum_%d",k));
 hhit_E_pim_LD_nob[k] = (TH1F*)f18->Get(Form("hit_E_%d",k));
 hhit_p_pim_LD_nob[k] = (TH1F*)f18->Get(Form("hit_momentum_%d",k));
 hhit_Edep_pim_LD[k] = (TH1F*)f8->Get(Form("hit_Edep_%d",k));
 hhit_E_pim_cut_LD[k] = (TH1F*)f8->Get(Form("hit_E_cut_%d",k));
 hhit_p_pim_cut_LD[k] = (TH1F*)f8->Get(Form("hit_momentum_cut_%d",k));
 hhit_E_pim_cut_LD_nob[k] = (TH1F*)f18->Get(Form("hit_E_cut_%d",k));
 hhit_p_pim_cut_LD_nob[k] = (TH1F*)f18->Get(Form("hit_momentum_cut_%d",k));
 hit_R_vs_vz_pim_nob[k]= (TH2F*)f18->Get(Form("hit_R_vs_vz_%d",k));
 hit_R_vs_vz_pim[k]= (TH2F*)f8->Get(Form("hit_R_vs_vz_%d",k));
 hhit_E_pip_LD[k] = (TH1F*)f9->Get(Form("hit_E_%d",k));
 hhit_p_pip_LD[k] = (TH1F*)f9->Get(Form("hit_momentum_%d",k));
 hhit_E_pip_LD_nob[k] = (TH1F*)f19->Get(Form("hit_E_%d",k));
 hhit_p_pip_LD_nob[k] = (TH1F*)f19->Get(Form("hit_momentum_%d",k));
 hhit_Edep_pip_LD[k] = (TH1F*)f9->Get(Form("hit_Edep_%d",k));
 hhit_E_pip_cut_LD[k] = (TH1F*)f9->Get(Form("hit_E_cut_%d",k));
 hhit_p_pip_cut_LD[k] = (TH1F*)f9->Get(Form("hit_momentum_cut_%d",k));
 hhit_E_pip_cut_LD_nob[k] = (TH1F*)f19->Get(Form("hit_E_cut_%d",k));
 hhit_p_pip_cut_LD_nob[k] = (TH1F*)f19->Get(Form("hit_momentum_cut_%d",k));
 hit_R_vs_vz_pip_nob[k]= (TH2F*)f19->Get(Form("hit_R_vs_vz_%d",k));
 hit_R_vs_vz_pip[k]= (TH2F*)f9->Get(Form("hit_R_vs_vz_%d",k));
 hit_R_vs_vz_pi0_nob[k]= (TH2F*)f20->Get(Form("hit_R_vs_vz_%d",k));
 hit_R_vs_vz_pi0[k]= (TH2F*)f10->Get(Form("hit_R_vs_vz_%d",k));
 hhit_E_proton_cut[k] = (TH1F*)f7->Get(Form("hit_E_cut_%d",k));
 hhit_p_proton_cut[k] = (TH1F*)f7->Get(Form("hit_momentum_cut_%d",k));
 hhit_E_proton_cut_nob[k] = (TH1F*)f17->Get(Form("hit_E_cut_%d",k));
 hhit_p_proton_cut_nob[k] = (TH1F*)f17->Get(Form("hit_momentum_cut_%d",k));
 hhit_E_pi0_cut[k] = (TH1F*)f10->Get(Form("hit_E_cut_%d",k));
 hhit_p_pi0_cut[k] = (TH1F*)f10->Get(Form("hit_momentum_cut_%d",k));
 hhit_E_pi0_cut_nob[k] = (TH1F*)f20->Get(Form("hit_E_cut_%d",k));
 hhit_p_pi0_cut_nob[k] = (TH1F*)f20->Get(Form("hit_momentum_cut_%d",k));
 hhit_pid_pip_LD_nob[k] = (TH1F*)f29->Get(Form("hit_pid_%d",k));
 hhit_pid_pim_LD_nob[k] = (TH1F*)f28->Get(Form("hit_pid_%d",k));
 hhit_pid_proton_LD_nob[k] = (TH1F*)f27->Get(Form("hit_pid_%d",k));
 hhit_mpid_pip_LD_nob[k] = (TH1F*)f29->Get(Form("hit_mpid_%d",k));
 hhit_mpid_pim_LD_nob[k] = (TH1F*)f28->Get(Form("hit_mpid_%d",k));
 hhit_mpid_proton_LD_nob[k] = (TH1F*)f27->Get(Form("hit_mpid_%d",k));
 hhit_procID_pip_LD_nob[k] = (TH1F*)f29->Get(Form("hit_procID_%d",k));
 hhit_procID_pim_LD_nob[k] = (TH1F*)f28->Get(Form("hit_procID_%d",k));
 hhit_procID_proton_LD_nob[k] = (TH1F*)f27->Get(Form("hit_procID_%d",k));
 hhit_E_pi0_cute[k] = (TH1F*)f10->Get(Form("hit_E_cute_%d",k));
 hhit_p_pi0_cute[k] = (TH1F*)f10->Get(Form("hit_momentum_cute_%d",k));
 hhit_E_pi0_cute_nob[k] = (TH1F*)f20->Get(Form("hit_E_cute_%d",k));
 hhit_p_pi0_cute_nob[k] = (TH1F*)f20->Get(Form("hit_momentum_cute_%d",k));
 hhit_E_pi0_cutr[k] = (TH1F*)f10->Get(Form("hit_E_cutr_%d",k));
 hhit_p_pi0_cutr[k] = (TH1F*)f10->Get(Form("hit_momentum_cutr_%d",k));
 hhit_E_pi0_cutr_nob[k] = (TH1F*)f20->Get(Form("hit_E_cutr_%d",k));
 hhit_p_pi0_cutr_nob[k] = (TH1F*)f20->Get(Form("hit_momentum_cutr_%d",k));
 }*/
 TCanvas *c[17];
 c[0] = new TCanvas("c[0]","c[0]",1000,1000);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogy();
 EC_shower_pip->Scale(0.001);
 EC_shower_pip->Rebin(rebinfac);
// EC_shower_pip->GetYaxis()->SetRangeUser(1e-3,1e9);
 //EC_shower_pip->GetXaxis()->SetRangeUser(0,100);
 EC_shower_pip->GetYaxis()->SetTitle("rate (kHz)");
 EC_shower_pip->SetLineColor(2);
 EC_shower_pip->SetTitle("shower Edep");
 EC_shower_pip->Draw("HIST");
double rate_pip= EC_shower_pip->Integral();
 EC_shower_pim->Scale(0.001);
 EC_shower_pim->Rebin(rebinfac);
 EC_shower_pim->SetLineColor(1);
 EC_shower_pim->Draw(" same HIST");
double rate_pim= EC_shower_pim->Integral();
  TLegend *leg8 = new TLegend(0.45,0.6,0.8,0.88);
  leg8->AddEntry(EC_shower_pim,Form("#gamma from bggen #pi^{0}; 82.2 deg",rate_pim),"l");
  leg8->AddEntry(EC_shower_pip,Form("#gamma from bggen #pi^{0}; 8 deg",rate_pip),"l");
  leg8->SetTextSize(0.03);
  leg8->SetBorderSize(0);
  leg8->SetFillColor(0);
  leg8->Draw("text same");
 c[1] = new TCanvas("c[1]","c[1]",1000,800);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
 EC_preshower_pim->Scale(0.001);
 EC_preshower_pim->Rebin(rebinfac1);
 EC_preshower_pim->GetYaxis()->SetRangeUser(1e-3,1e2);
// EC_preshower_pim->GetXaxis()->SetRangeUser(0,50);
 EC_preshower_pim->GetYaxis()->SetTitle("rate (kHz)");
 EC_preshower_pim->SetTitle("preshower Edep");
 EC_preshower_pim->SetLineColor(1);
 EC_preshower_pim->Draw(" HIST");
double rate_pim_pre= EC_preshower_pim->Integral();
 EC_preshower_pip->Scale(0.001);
 EC_preshower_pip->SetLineColor(2);
 EC_preshower_pip->Rebin(rebinfac1);
 EC_preshower_pip->Draw(" same HIST");
double rate_pip_pre= EC_preshower_pip->Integral();
  TLegend *leg1 = new TLegend(0.45,0.6,0.8,0.88);
  leg1->AddEntry(EC_preshower_pim,Form("#gamma from bggen #pi^{0}; 82.2 deg",rate_pim_pre),"l");
  leg1->AddEntry(EC_preshower_pip,Form("#gamma from bggen #pi^{0}; 8 deg",rate_pip_pre),"l");
  leg1->SetTextSize(0.03);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->Draw("text same");
 c[2] = new TCanvas("c[2]","c[2]",1000,1000);
 c[2]->Divide(3,3);
 for(int j=0;j<9;j++){
 c[2]->cd(j+1);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
 hhit_p_pip[j]->GetYaxis()->SetTitle("rate (kHz)");
 hhit_p_pip[j]->GetXaxis()->SetTitle("#gamma momentum (GeV/c)");
 hhit_p_pip[j]->GetYaxis()->SetRangeUser(1e0,5e4);
 hhit_p_pip[j]->GetXaxis()->SetRangeUser(0,8);
 hhit_p_pip[j]->SetLineColor(2);
 hhit_p_pip[j]->Draw("HIST");
 hhit_p_pim[j]->SetLineColor(1);
 hhit_p_pim[j]->Draw("same HIST");
 }
 c[2]->cd(1);
  leg1->Draw("text same");

 c[3] = new TCanvas("c[3]","c[3]",1000,1000);
 c[3]->Divide(3,3);
 for(int j=0;j<9;j++){
 c[3]->cd(j+1);
  gPad->SetGridx();
  gPad->SetGridy();
//  gPad->SetLogy();
  hit_R_vs_vz_pip[j]->GetYaxis()->SetTitle("rate (kHz)");
  hit_R_vs_vz_pip[j]->GetXaxis()->SetTitle("#gamma momentum (GeV/c)");
  hit_R_vs_vz_pip[j]->GetYaxis()->SetRangeUser(0,3);
 // hit_R_vs_vz_pip[j]->GetXaxis()->SetRangeUser(-10,10);
 // hit_R_vs_vz_pip[j]->SetLineColor(2);
  hit_R_vs_vz_pip[j]->Draw("COLZ");
 }

 c[5] = new TCanvas("c[5]","c[5]",1000,1000);
 c[5]->Divide(1,2);
 c[5]->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
 sc1_pim->SetLineColor(1);
 sc1_pim->GetYaxis()->SetTitle("rate (kHz)");
 sc1_pim->SetTitle("SC0 triggered");
 sc1_pim->GetXaxis()->SetTitle("Edep (MeV)");
 sc1_pim->GetXaxis()->SetRangeUser(0,100);
 sc1_pim->GetYaxis()->SetRangeUser(1e-2,1e3);
 sc1_pim->Scale(0.001);
 sc1_pim->Draw("HIST");
 double rate_pim_sc1= sc1_pim->Integral(sc1_pim->GetXaxis()->FindBin(0),sc1_pim->GetXaxis()->FindBin(100));
 sc1_pip->SetLineColor(2);
 sc1_pip->Scale(0.001);
 sc1_pip->Draw("same HIST");
 double rate_pip_sc1= sc1_pip->Integral(sc1_pip->GetXaxis()->FindBin(0),sc1_pip->GetXaxis()->FindBin(100));
  TLegend *leg21 = new TLegend(0.45,0.4,0.8,0.68);
  leg1->Draw("text same");
 c[5]->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
 sc2_pim->SetLineColor(1);
 sc2_pim->GetYaxis()->SetTitle("rate (kHz)");
 sc2_pim->SetTitle("SC1 triggered");
 sc2_pim->GetXaxis()->SetTitle("Edep (MeV)");
 sc2_pim->GetXaxis()->SetRangeUser(0,100);
 sc2_pim->GetYaxis()->SetRangeUser(1e-2,1e3);
 sc2_pim->Scale(0.001);
 sc2_pim->Draw("HIST");
 double rate_pim_sc2= sc2_pim->Integral();
 sc2_pip->SetLineColor(2);
 sc2_pip->Scale(0.001);
 sc2_pip->Draw("same HIST");
 leg1->Draw("text same");
 c[4] = new TCanvas("c[4]","c[4]",1000,1000);
 c[4]->Divide(1,2);
 c[4]->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  hhit_Edepspd1_pim->SetLineColor(1);
  hhit_Edepspd1_pim->GetYaxis()->SetRangeUser(1e-3,1e8);
  hhit_Edepspd1_pim->SetTitle(" SPD ShowerSum trigger");
  hhit_Edepspd1_pim->Scale(0.001);
  hhit_Edepspd1_pim->Draw("HIST");
 double rate_pim_spd1= hhit_Edepspd1_pim->Integral();
  hhit_Edepspd1_pip->SetLineColor(2);
  hhit_Edepspd1_pip->GetYaxis()->SetRangeUser(1e-3,1e8);
  hhit_Edepspd1_pip->Scale(0.001);
  hhit_Edepspd1_pip->Draw("same HIST");
 double rate_pip_spd1= hhit_Edepspd1_pip->Integral();
  TLegend *leg13 = new TLegend(0.45,0.6,0.8,0.88);
  leg1->Draw("text same");
  c[4]->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  hhit_Edepspd2_pim->SetLineColor(1);
  hhit_Edepspd2_pim->GetYaxis()->SetRangeUser(1e-3,1e8);
  hhit_Edepspd2_pim->SetTitle(" LASPD ShowerSum trigger");
  hhit_Edepspd2_pim->Scale(0.001);
  hhit_Edepspd2_pim->Draw("HIST");
 double rate_pim_spd2= hhit_Edepspd2_pim->Integral();
  hhit_Edepspd2_pip->SetLineColor(2);
  hhit_Edepspd2_pip->GetYaxis()->SetRangeUser(1e-3,1e8);
  hhit_Edepspd2_pip->Scale(0.001);
  hhit_Edepspd2_pip->Draw("same HIST");
 double rate_pip_spd2= hhit_Edepspd2_pip->Integral();
  leg1->Draw("text same");
 for(int a=0;a<6;a++){
    c[a]->SaveAs(Form("c%d.pdf",a));
    }
             gSystem->Exec("pdfunite ./c*.pdf ./HallC_pi0_gamma_82_8_deg.pdf");
             gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
