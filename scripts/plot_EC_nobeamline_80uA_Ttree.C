
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

void plot_EC_nobeamline_80uA_Ttree(){
gStyle->SetOptStat(0);
gStyle->SetPalette(1);
  TFile *f13 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_80uA/HallC_beamtest_eAll_80uA_filenum99_nobeamline_reduce_tree_rate.root");
TFile *f7 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_TGonly/HallC_beamtest_BeamOnTarget_3.974e11_nobeamline_reduce_tree_rate.root");
TFile *f8 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_80uA/HallC_beamtest_bggen_LH2_pim_80uA_filenum19880_nobeamline_reduce_tree_rate.root");
TFile *f9 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_80uA/HallC_beamtest_bggen_LH2_pip_80uA_nobeamline_filenum19720_reduce_tree_rate.root");
TFile *f10 = new TFile("/lustre19/expphy/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_80uA/HallC_beamtest_bggen_LH2_pi0_80uA_filenum19590_nobeamline_reduce_tree_rate.root");
 TTree *tree_pip = (TTree*) f9->Get("T");
 TTree *tree_pi0 = (TTree*) f10->Get("T");
 TTree *tree_pim = (TTree*) f8->Get("T");
 TTree *tree_BeamOn = (TTree*) f7->Get("T");
 TTree *tree_eAll = (TTree*) f13->Get("T");
//trigger1
	tree_pip->Draw("ShowerSum>>shower_pip_trigger1(200,0,200)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *EC_shower_pip_trigger1 = (TH1F*)gROOT->FindObject("shower_pip_trigger1");
	tree_pim->Draw("ShowerSum>>shower_pim_trigger1(200,0,200)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *EC_shower_pim_trigger1 = (TH1F*)gROOT->FindObject("shower_pim_trigger1");
	tree_pi0->Draw("ShowerSum>>shower_pi0_trigger1(200,0,200)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *EC_shower_pi0_trigger1 = (TH1F*)gROOT->FindObject("shower_pi0_trigger1");
	tree_eAll->Draw("ShowerSum>>shower_eAll_trigger1(200,0,200)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *EC_shower_eAll_trigger1 = (TH1F*)gROOT->FindObject("shower_eAll_trigger1");
	tree_BeamOn->Draw("ShowerSum>>shower_proton_trigger1(200,0,200)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *EC_shower_proton_trigger1 = (TH1F*)gROOT->FindObject("shower_proton_trigger1");
//preshower

	tree_pip->Draw("PreShSum>>preshower_pip_trigger1(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *EC_preshower_pip_trigger1 = (TH1F*)gROOT->FindObject("preshower_pip_trigger1");
	tree_pim->Draw("PreShSum>>preshower_pim_trigger1(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *EC_preshower_pim_trigger1 = (TH1F*)gROOT->FindObject("preshower_pim_trigger1");
	tree_pi0->Draw("PreShSum>>preshower_pi0_trigger1(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *EC_preshower_pi0_trigger1 = (TH1F*)gROOT->FindObject("preshower_pi0_trigger1");
	tree_eAll->Draw("PreShSum>>preshower_eAll_trigger1(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *EC_preshower_eAll_trigger1 = (TH1F*)gROOT->FindObject("preshower_eAll_trigger1");
	tree_BeamOn->Draw("PreShSum>>preshower_proton_trigger1(200,0,100)","rate*(SC0_Eendsum>0 && SC1_Eendsum>0)","goff");
	TH1F *EC_preshower_proton_trigger1 = (TH1F*)gROOT->FindObject("preshower_proton_trigger1");
//trigger2
	tree_pip->Draw("ShowerSum>>shower_pip_trigger2(200,0,200)","rate*(Shower_t>0 && PreSh_t>0)","goff");
	TH1F *EC_shower_pip_trigger2 = (TH1F*)gROOT->FindObject("shower_pip_trigger2");
	tree_pim->Draw("ShowerSum>>shower_pim_trigger2(200,0,200)","rate*(Shower_t>0 && PreSh_t>0)","goff");
	TH1F *EC_shower_pim_trigger2 = (TH1F*)gROOT->FindObject("shower_pim_trigger2");
	tree_pi0->Draw("ShowerSum>>shower_pi0_trigger2(200,0,200)","rate*(Shower_t>0 && PreSh_t>0)","goff");
	TH1F *EC_shower_pi0_trigger2 = (TH1F*)gROOT->FindObject("shower_pi0_trigger2");
	tree_eAll->Draw("ShowerSum>>shower_eAll_trigger2(200,0,200)","rate*(Shower_t>0 && PreSh_t>0)","goff");
	TH1F *EC_shower_eAll_trigger2 = (TH1F*)gROOT->FindObject("shower_eAll_trigger2");
	tree_BeamOn->Draw("ShowerSum>>shower_proton_trigger2(200,0,200)","rate*(Shower_t>0 && PreSh_t>0)","goff");
	TH1F *EC_shower_proton_trigger2 = (TH1F*)gROOT->FindObject("shower_proton_trigger2");

	tree_pip->Draw("PreShSum>>preshower_pip_trigger2(200,0,100)","rate*(Shower_t>0 && PreSh_t>0)","goff");
	TH1F *EC_preshower_pip_trigger2 = (TH1F*)gROOT->FindObject("preshower_pip_trigger2");
	tree_pim->Draw("PreShSum>>preshower_pim_trigger2(200,0,100)","rate*(Shower_t>0 && PreSh_t>0)","goff");
	TH1F *EC_preshower_pim_trigger2 = (TH1F*)gROOT->FindObject("preshower_pim_trigger2");
	tree_pi0->Draw("PreShSum>>preshower_pi0_trigger2(200,0,100)","rate*(Shower_t>0 && PreSh_t>0)","goff");
	TH1F *EC_preshower_pi0_trigger2 = (TH1F*)gROOT->FindObject("preshower_pi0_trigger2");
	tree_eAll->Draw("PreShSum>>preshower_eAll_trigger2(200,0,100)","rate*(Shower_t>0 && PreSh_t>0)","goff");
	TH1F *EC_preshower_eAll_trigger2 = (TH1F*)gROOT->FindObject("preshower_eAll_trigger2");
	tree_BeamOn->Draw("PreShSum>>preshower_proton_trigger2(200,0,100)","rate*(Shower_t>0 && PreSh_t>0)","goff");
	TH1F *EC_preshower_proton_trigger2 = (TH1F*)gROOT->FindObject("preshower_proton_trigger2");

const int rebinfac=2;
 const int binmin=21;
 TCanvas *c[17];
 c[0] = new TCanvas("c[0]","c[0]",1000,1000);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogy();
 EC_shower_proton_trigger2->Scale(0.001);
 EC_shower_proton_trigger2->GetYaxis()->SetTitle("rate (kHz)");
 EC_shower_proton_trigger2->GetYaxis()->SetRangeUser(1e-3,1e3);
 EC_shower_proton_trigger2->SetTitle("shower Edep");
 EC_shower_proton_trigger2->SetLineColor(6);
 EC_shower_proton_trigger2->Rebin(rebinfac);
 EC_shower_proton_trigger2->Draw(" HIST");
double rate_proton= EC_shower_proton_trigger2->Integral(EC_shower_proton_trigger2->GetXaxis()->FindBin(binmin),EC_shower_proton_trigger2->GetXaxis()->FindBin(200));
 EC_shower_pip_trigger2->Scale(0.001);
 EC_shower_pip_trigger2->Rebin(rebinfac);
// EC_shower_pip->GetYaxis()->SetRangeUser(1e-3,1e9);
 //EC_shower_pip->GetXaxis()->SetRangeUser(0,100);
 EC_shower_pip_trigger2->GetYaxis()->SetTitle("rate (kHz)");
 EC_shower_pip_trigger2->SetLineColor(2);
 EC_shower_pip_trigger2->SetTitle("shower Edep");
 EC_shower_pip_trigger2->Draw("same HIST");
double rate_pip= EC_shower_pip_trigger2->Integral(EC_shower_pip_trigger2->GetXaxis()->FindBin(binmin),EC_shower_pip_trigger2->GetXaxis()->FindBin(200));
 EC_shower_pim_trigger2->Scale(0.001);
 EC_shower_pim_trigger2->Rebin(rebinfac);
 EC_shower_pim_trigger2->SetLineColor(1);
 EC_shower_pim_trigger2->Draw(" same HIST");
double rate_pim= EC_shower_pim_trigger2->Integral(EC_shower_pim_trigger2->GetXaxis()->FindBin(binmin),EC_shower_pim_trigger2->GetXaxis()->FindBin(200));
 EC_shower_pi0_trigger2->Scale(0.001);
 EC_shower_pi0_trigger2->Rebin(rebinfac);
 EC_shower_pi0_trigger2->SetLineColor(kGreen+3);
 EC_shower_pi0_trigger2->Draw(" same HIST");
double rate_pi0= EC_shower_pi0_trigger2->Integral(EC_shower_pi0_trigger2->GetXaxis()->FindBin(binmin),EC_shower_pi0_trigger2->GetXaxis()->FindBin(200));
 EC_shower_eAll_trigger2->SetLineColor(4);
 EC_shower_eAll_trigger2->Rebin(rebinfac);
 EC_shower_eAll_trigger2->Draw(" same HIST");
double rate_eAll= EC_shower_eAll_trigger2->Integral(EC_shower_eAll_trigger2->GetXaxis()->FindBin(binmin),EC_shower_eAll_trigger2->GetXaxis()->FindBin(200));
  TLegend *leg8 = new TLegend(0.45,0.6,0.8,0.88);
  leg8->AddEntry(EC_shower_eAll_trigger2,Form("eAll*1000; total rate=%f Hz",rate_eAll),"l");
//  leg8->AddEntry(EC_shower_eDIS,"eDIS*1000","l");
  leg8->AddEntry(EC_shower_pim_trigger2,Form("bggen #pi^{-}; total rate=%f kHz",rate_pim),"l");
  leg8->AddEntry(EC_shower_pip_trigger2,Form("bggen #pi^{+}; total rate=%f kHz",rate_pip),"l");
  leg8->AddEntry(EC_shower_pi0_trigger2,Form("bggen #pi^{0}; total rate=%f kHz",rate_pi0),"l");
  leg8->AddEntry(EC_shower_proton_trigger2,Form("BeamOnTarget; total rate=%f kHz",rate_proton),"l");
  leg8->SetTextSize(0.03);
  leg8->SetBorderSize(0);
  leg8->SetFillColor(0);
  leg8->Draw("text same");
  cout<<"rate eAll="<<rate_eAll<<"  "<<"rate_pim="<<rate_pim<<"  "<<"rate_pip="<<rate_pip<<endl;
 c[1] = new TCanvas("c[1]","c[1]",1000,800);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
 EC_preshower_proton_trigger2->SetLineColor(6);
 EC_preshower_proton_trigger2->Scale(0.001);
 EC_preshower_proton_trigger2->Rebin(rebinfac);
 EC_preshower_proton_trigger2->GetYaxis()->SetRangeUser(1e-3,1e3);
// EC_preshower_proton->GetXaxis()->SetRangeUser(0,50);
 EC_preshower_proton_trigger2->GetYaxis()->SetTitle("rate (kHz)");
 EC_preshower_proton_trigger2->SetTitle("preshower Edep");
 EC_preshower_proton_trigger2->Draw("HIST");
double rate_proton_pre= EC_preshower_proton_trigger2->Integral(EC_preshower_proton_trigger2->GetXaxis()->FindBin(binmin),EC_preshower_proton_trigger2->GetXaxis()->FindBin(200));
 EC_preshower_pim_trigger2->Scale(0.001);
 EC_preshower_pim_trigger2->SetLineColor(1);
 EC_preshower_pim_trigger2->Rebin(rebinfac);
 EC_preshower_pim_trigger2->Draw("same HIST");
double rate_pim_pre= EC_preshower_pim_trigger2->Integral(EC_preshower_pim_trigger2->GetXaxis()->FindBin(binmin),EC_preshower_pim_trigger2->GetXaxis()->FindBin(200));
 EC_preshower_pi0_trigger2->Scale(0.001);
 EC_preshower_pi0_trigger2->SetLineColor(kGreen+3);
 EC_preshower_pi0_trigger2->Rebin(rebinfac);
 EC_preshower_pi0_trigger2->Draw("same HIST");
double rate_pi0_pre= EC_preshower_pi0_trigger2->Integral(EC_preshower_pi0_trigger2->GetXaxis()->FindBin(binmin),EC_preshower_pi0_trigger2->GetXaxis()->FindBin(200));
 EC_preshower_eAll_trigger2->SetLineColor(4);
// EC_preshower_eAll->Scale(1000);
 EC_preshower_eAll_trigger2->Rebin(rebinfac);
 EC_preshower_eAll_trigger2->Draw(" same HIST");
double rate_eAll_pre= EC_preshower_eAll_trigger2->Integral(EC_preshower_eAll_trigger2->GetXaxis()->FindBin(binmin),EC_preshower_eAll_trigger2->GetXaxis()->FindBin(200));
 EC_preshower_pip_trigger2->Scale(0.001);
 EC_preshower_pip_trigger2->SetLineColor(2);
 EC_preshower_pip_trigger2->Rebin(rebinfac);
 EC_preshower_pip_trigger2->Draw(" same HIST");
double rate_pip_pre= EC_preshower_pip_trigger2->Integral(EC_preshower_pip_trigger2->GetXaxis()->FindBin(binmin),EC_preshower_pip_trigger2->GetXaxis()->FindBin(200));
  TLegend *leg1 = new TLegend(0.45,0.6,0.8,0.88);
  leg1->AddEntry(EC_preshower_eAll_trigger2,Form("eAll*1000; total rate=%f Hz",rate_eAll_pre),"l");
  leg1->AddEntry(EC_preshower_proton_trigger2,Form("BeamOnTarget; total rate=%f kHz",rate_proton_pre),"l");
  leg1->AddEntry(EC_preshower_pim_trigger2,Form("bggen #pi^{-}; total rate=%f kHz",rate_pim_pre),"l");
  leg1->AddEntry(EC_preshower_pip_trigger2,Form("bggen #pi^{+}; total rate=%f kHz",rate_pip_pre),"l");
  leg1->AddEntry(EC_preshower_pi0_trigger2,Form("bggen #pi^{0}; total rate=%f kHz",rate_pi0_pre),"l");
  leg1->SetTextSize(0.03);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->Draw("text same");
 c[2] = new TCanvas("c[2]","c[2]",1000,1000);
 c[2]->Divide(1,2);
 c[2]->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
/* sc1_proton->SetLineColor(6);
 sc1_proton->Scale(0.001);
 sc1_proton->GetYaxis()->SetTitle("rate (kHz)");
 sc1_proton->SetTitle("SC0 triggered");
 sc1_proton->GetXaxis()->SetTitle("Edep (MeV)");
 sc1_proton->GetXaxis()->SetRangeUser(0,100);
 sc1_proton->GetYaxis()->SetRangeUser(1e-2,1e3);
 sc1_proton->Rebin(rebinfac);
 sc1_proton->Draw("HIST");
 double rate_proton_sc1= sc1_proton->Integral(sc1_proton->GetXaxis()->FindBin(binmin),sc1_proton->GetXaxis()->FindBin(100));
 sc1_pim->SetLineColor(1);
 sc1_pim->Scale(0.001);
 sc1_pim->Rebin(rebinfac);
 sc1_pim->Draw("same HIST");
 double rate_pim_sc1= sc1_pim->Integral(sc1_pim->GetXaxis()->FindBin(binmin),sc1_pim->GetXaxis()->FindBin(100));
 sc1_eAll->SetLineColor(4);
 //sc1_eAll->Scale(1000);
 sc1_eAll->Rebin(rebinfac);
 sc1_eAll->Draw("same HIST");
 double rate_eAll_sc1= sc1_eAll->Integral();
 sc1_pip->SetLineColor(2);
 sc1_pip->Scale(0.001);
 sc1_pip->Rebin(rebinfac);
 sc1_pip->Draw("same HIST");
 double rate_pip_sc1= sc1_pip->Integral(sc1_pip->GetXaxis()->FindBin(binmin),sc1_pip->GetXaxis()->FindBin(100));
 sc1_pi0->SetLineColor(kGreen+3);
 sc1_pi0->Scale(0.001);
 sc1_pi0->Rebin(rebinfac);
 sc1_pi0->Draw("same HIST");
 double rate_pi0_sc1= sc1_pi0->Integral(sc1_pi0->GetXaxis()->FindBin(binmin),sc1_pi0->GetXaxis()->FindBin(100));
  TLegend *leg21 = new TLegend(0.45,0.4,0.8,0.68);
  leg21->AddEntry(sc1_eAll,Form("eAll*1000; total rate=%f Hz",rate_eAll_sc1),"l");
  leg21->AddEntry(sc1_pim,Form("bggen #pi^{-}; total rate=%f kHz",rate_pim_sc1),"l");
  leg21->AddEntry(sc1_pip,Form("bggen #pi^{+}; total rate=%f kHz",rate_pip_sc1),"l");
  leg21->AddEntry(sc1_pi0,Form("bggen #pi^{0}; total rate=%f kHz",rate_pi0_sc1),"l");
  leg21->AddEntry(sc1_proton,Form("BeamOnTarget; total rate=%f kHz",rate_proton_sc1),"l");
  leg21->SetTextSize(0.05);
  leg21->SetBorderSize(0);
  leg21->SetFillColor(0);
  leg21->Draw("text same");
 c[2]->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
 sc2_proton->SetLineColor(6);
 sc2_proton->Scale(0.001);
 sc2_proton->SetTitle("SC1 triggered");
 sc2_proton->GetXaxis()->SetTitle("Edep (MeV)");
 sc2_proton->GetYaxis()->SetTitle("rate (kHz)");
 sc2_proton->GetYaxis()->SetRangeUser(1e-2,1e3);
 sc2_proton->GetXaxis()->SetRangeUser(0,100);
 sc2_proton->Rebin(rebinfac);
 sc2_proton->Draw("HIST");
 double rate_pip_sc2= sc2_pip->Integral();
 sc2_pim->SetLineColor(1);
 sc2_pim->Scale(0.001);
 sc2_pim->Rebin(rebinfac);
 sc2_pim->Draw("same HIST");
 double rate_pim_sc2= sc2_pim->Integral();
 sc2_eAll->SetLineColor(4);
 sc2_eAll->Rebin(rebinfac);
 sc2_eAll->Draw("same HIST");
 double rate_eAll_sc2= sc2_eAll->Integral();
 sc2_pip->SetLineColor(2);
 sc2_pip->Scale(0.001);
 sc2_pip->Rebin(rebinfac);
 sc2_pip->Draw("same HIST");
 sc2_pi0->SetLineColor(kGreen+3);
 sc2_pi0->Scale(0.001);
 sc2_pi0->Rebin(rebinfac);
 sc2_pi0->Draw("same HIST");
 double rate_pi0_sc2= sc2_pi0->Integral();
 leg21->Draw("text same");
  cout<<"rate eAll_S2="<<rate_eAll_sc2<<"rate eAll_S1="<<rate_eAll_sc1<<"  "<<"rate_pim_s1="<<rate_pim_sc1<<"  "<<"rate_pim_s2="<<rate_pim_sc2<<"rate_pip_s1="<<rate_pip_sc1<<"rate_pip_s2="<<rate_pip_sc2<<endl;
 c[3] = new TCanvas("c[3]","c[3]",1000,1000);
 c[3]->Divide(1,2);
 c[3]->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  hhit_Edepspd1_proton->SetLineColor(6);
  hhit_Edepspd1_proton->Scale(0.001);
  hhit_Edepspd1_proton->GetYaxis()->SetRangeUser(1e-3,1e6);
  hhit_Edepspd1_proton->SetTitle("SPD, SC0 and SC1 trigger");
  hhit_Edepspd1_proton->Rebin(rebinfac);
  hhit_Edepspd1_proton->Draw("HIST");
 double rate_proton_spd1= hhit_Edepspd1_proton->Integral();
  hhit_Edepspd1_pim->SetLineColor(1);
  hhit_Edepspd1_pim->GetYaxis()->SetRangeUser(1e-3,1e6);
  hhit_Edepspd1_pim->Scale(0.001);
  hhit_Edepspd1_pim->Rebin(rebinfac);
  hhit_Edepspd1_pim->Draw("same HIST");
 double rate_pim_spd1= hhit_Edepspd1_pim->Integral();
  hhit_Edepspd1_pi0->SetLineColor(kGreen+3);
  hhit_Edepspd1_pi0->GetYaxis()->SetRangeUser(1e-3,1e6);
  hhit_Edepspd1_pi0->Scale(0.001);
  hhit_Edepspd1_pi0->Rebin(rebinfac);
  hhit_Edepspd1_pi0->Draw("same HIST");
 double rate_pi0_spd1= hhit_Edepspd1_pi0->Integral();
  hhit_Edepspd1_pip->SetLineColor(2);
  hhit_Edepspd1_pip->GetYaxis()->SetRangeUser(1e-3,1e6);
  hhit_Edepspd1_pip->Scale(0.001);
  hhit_Edepspd1_pip->Rebin(rebinfac);
  hhit_Edepspd1_pip->Draw("same HIST");
 double rate_pip_spd1= hhit_Edepspd1_pip->Integral();
  hhit_Edepspd1_eAll->SetLineColor(4);
  hhit_Edepspd1_eAll->GetYaxis()->SetRangeUser(1e-3,1e6);
  hhit_Edepspd1_eAll->Rebin(rebinfac);
  hhit_Edepspd1_eAll->Draw("same HIST");
 double rate_eAll_spd1= hhit_Edepspd1_eAll->Integral();
  TLegend *leg13 = new TLegend(0.45,0.6,0.8,0.88);
  leg13->AddEntry(hhit_Edepspd1_eAll,Form("eAll*1000; total rate=%f Hz",rate_eAll_spd1),"l");
  leg13->AddEntry(hhit_Edepspd1_proton,Form("BeamOnTarget; total rate=%f kHz",rate_proton_spd1),"l");
  leg13->AddEntry(hhit_Edepspd1_pim,Form("bggen #pi^{-}; total rate=%f kHz",rate_pim_spd1),"l");
  leg13->AddEntry(hhit_Edepspd1_pip,Form("bggen #pi^{+}; total rate=%f kHz",rate_pip_spd1),"l");
  leg13->AddEntry(hhit_Edepspd1_pi0,Form("bggen #pi^{0}; total rate=%f kHz",rate_pi0_spd1),"l");
  leg13->SetTextSize(0.06);
  leg13->SetBorderSize(0);
  leg13->SetFillColor(0);
  leg13->Draw("text same");
  c[3]->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  hhit_Edepspd2_proton->SetLineColor(6);
  hhit_Edepspd2_proton->Scale(0.001);
  hhit_Edepspd2_proton->GetYaxis()->SetRangeUser(1e-3,1e6);
  hhit_Edepspd2_proton->SetTitle("LASPD, SC0 and SC1 trigger");
  hhit_Edepspd2_proton->Rebin(rebinfac);
  hhit_Edepspd2_proton->Draw("HIST");
 double rate_proton_spd2= hhit_Edepspd2_proton->Integral();
  hhit_Edepspd2_pim->SetLineColor(1);
  hhit_Edepspd2_pim->GetYaxis()->SetRangeUser(1e-3,1e6);
  hhit_Edepspd2_pim->Scale(0.001);
  hhit_Edepspd2_pim->Rebin(rebinfac);
  hhit_Edepspd2_pim->Draw("same HIST");
 double rate_pim_spd2= hhit_Edepspd2_pim->Integral();
  hhit_Edepspd2_pi0->SetLineColor(kGreen+3);
  hhit_Edepspd2_pi0->GetYaxis()->SetRangeUser(1e-3,1e6);
  hhit_Edepspd2_pi0->Scale(0.001);
  hhit_Edepspd2_pi0->Rebin(rebinfac);
  hhit_Edepspd2_pi0->Draw("same HIST");
 double rate_pi0_spd2= hhit_Edepspd2_pi0->Integral();
  hhit_Edepspd2_pip->SetLineColor(2);
  hhit_Edepspd2_pip->GetYaxis()->SetRangeUser(1e-3,1e6);
  hhit_Edepspd2_pip->Scale(0.001);
  hhit_Edepspd2_pip->Rebin(rebinfac);
  hhit_Edepspd2_pip->Draw("same HIST");
 double rate_pip_spd2= hhit_Edepspd2_pip->Integral();
  hhit_Edepspd2_eAll->SetLineColor(4);
  hhit_Edepspd2_eAll->GetYaxis()->SetRangeUser(1e-3,1e6);
  hhit_Edepspd2_eAll->Rebin(rebinfac);
  hhit_Edepspd2_eAll->Draw("same HIST");
 double rate_eAll_spd2= hhit_Edepspd2_eAll->Integral();
  TLegend *leg14 = new TLegend(0.45,0.6,0.8,0.88);
  leg14->AddEntry(hhit_Edepspd2_eAll,Form("eAll*1000; total rate=%f Hz",rate_eAll_spd2),"l");
  leg14->AddEntry(hhit_Edepspd2_proton,Form("BeamOnTarget; total rate=%f kHz",rate_proton_spd2),"l");
  leg14->AddEntry(hhit_Edepspd2_pim,Form("bggen #pi^{-}; total rate=%f kHz",rate_pim_spd2),"l");
  leg14->AddEntry(hhit_Edepspd2_pip,Form("bggen #pi^{+}; total rate=%f kHz",rate_pip_spd2),"l");
  leg14->AddEntry(hhit_Edepspd2_pi0,Form("bggen #pi^{0}; total rate=%f kHz",rate_pi0_spd2),"l");
  leg14->SetTextSize(0.06);
  leg14->SetBorderSize(0);
  leg14->SetFillColor(0);
  leg14->Draw("text same");*/
 for(int a=0;a<2;a++){
    c[a]->SaveAs(Form("c%d.pdf",a));
    }
             gSystem->Exec("pdfunite ./c*.pdf ./HallC_trigger_rate_comparison_BeamOnTarget.pdf");
             gSystem->Exec(Form("rm -rf ./c*.pdf"));

}
