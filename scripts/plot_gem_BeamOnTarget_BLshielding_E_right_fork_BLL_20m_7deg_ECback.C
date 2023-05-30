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
	//TFile *f1 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.594e9_7deg_80uA_5x10SC_r10m_cfoil_10.6GeV_output_ec_electronE_pzcut.root");
	TFile *f1 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.0976e9_7deg_5uA_5x10SC_r20m_cfoil_output_ec_electronE_pzcut.root");
	//TFile *f11 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.594e9_7deg_80uA_5x10SC_r10m_cfoil_10.6GeV_output_ec_pionE_pzcut.root");
	TFile *f11 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.0976e9_7deg_5uA_5x10SC_r20m_cfoil_output_ec_pionE_pzcut.root");
	//TFile *f21 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.594e9_7deg_80uA_5x10SC_r10m_cfoil_10.6GeV_output_ec_gammaE_pzcut.root");
	TFile *f21 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_5x10SC_7deg_r10m_carbon/HallC_beamtest_BeamOnTarget_2.0976e9_7deg_5uA_5x10SC_r20m_cfoil_output_ec_gammaE_pzcut.root");
	TFile *f22 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle_4SC_7deg_r20m_carbon_ECshielding/HallC_beamtest_BeamOnTarget_1e9_7deg_5uA_4SC_r20m_cfoil_ECshielding_output_ec_gammaE_pzcut.root");
	TFile *f3 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_7deg_Cfoil/HallC_beamtest_bggen_Cfoil_pim_7deg_filenum2000_10.6GeV_output_ec_electronE_pzcut_prime.root");
	TFile *f2 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_7deg_Cfoil/HallC_beamtest_eAll_Cfoil_7deg_filenum992_4.96e7_10.6GeV_output_ec_electronE_prime_pL100MeV.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_7deg_Cfoil/HallC_beamtest_bggen_Cfoil_pip_7deg_filenum2000_10.6GeV_output_ec_electronE_pzcut_prime.root");
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_7deg_Cfoil/HallC_beamtest_bggen_Cfoil_pi0_7deg_filenum2000_10.6GeV_output_ec_electronE_pzcut.root");
	TH1F *hhit_ECend_E_beam;
	TH1F *hhit_ECend_E_beam_pion;
	TH1F *hhit_ECend_E_beam_gamma;
	TH1F *hhit_ECend_E_beam_gamma_pb;
	TH1F *hhit_ECend_E_eAll;
	TH1F *hhit_ECend_E_pim;
	TH1F *hhit_ECend_E_pip;
	TH1F *hhit_ECend_E_pi0;
	TH1F *hhit_ECend_E_gamma_beam;
	TH1F *hhit_ECend_E_gamma_pi0;
        hhit_ECend_E_beam = (TH1F*)f1->Get("hit_ECend_E");
        hhit_ECend_E_beam_pion = (TH1F*)f11->Get("hit_ECend_E");
        hhit_ECend_E_beam_gamma = (TH1F*)f21->Get("hit_ECend_E");
        hhit_ECend_E_beam_gamma_pb = (TH1F*)f22->Get("hit_ECend_E");
        hhit_ECend_E_eAll = (TH1F*)f2->Get("hit_ECend_E_tid1");
        hhit_ECend_E_pim= (TH1F*)f3->Get("hit_ECend_E_tid1");
        hhit_ECend_E_pip= (TH1F*)f4->Get("hit_ECend_E_tid1");
        hhit_ECend_E_pi0= (TH1F*)f5->Get("hit_ECend_E");
	TCanvas *c_gem[10];
	c_gem[0] = new TCanvas("c_gem[0]", "flux E",1800,1000);
	gPad->SetLogy();
	gPad->SetGridy();
	gPad->SetGridx();
	hhit_ECend_E_beam->SetLineColor(1);
	hhit_ECend_E_beam->GetYaxis()->SetTitle("rate (kHz)");
	hhit_ECend_E_beam->SetTitle("particles on ECal back virtual plane 10x10 cm^{2}");
        hhit_ECend_E_beam->Scale(0.001);
        hhit_ECend_E_beam->GetYaxis()->SetRangeUser(1e-4,1e7);	
	hhit_ECend_E_beam->Draw("HIST");
        double rate_E_beam= hhit_ECend_E_beam->Integral();
	hhit_ECend_E_eAll->SetLineColor(28);
        hhit_ECend_E_eAll->Scale(0.001);
	hhit_ECend_E_eAll->Draw("same HIST");
        double rate_E_eAll= hhit_ECend_E_eAll->Integral();
	hhit_ECend_E_pim->SetLineColor(4);
        hhit_ECend_E_pim->Scale(0.001);
	hhit_ECend_E_pim->Draw("same HIST");
        double rate_E_pim= hhit_ECend_E_pim->Integral();
	hhit_ECend_E_pip->SetLineColor(6);
        hhit_ECend_E_pip->Scale(0.001);
	hhit_ECend_E_pip->Draw("same HIST");
        double rate_E_pip= hhit_ECend_E_pip->Integral();
	hhit_ECend_E_pi0->SetLineColor(kOrange-3);
        hhit_ECend_E_pi0->Scale(0.001);
	hhit_ECend_E_pi0->Draw("same HIST");
        double rate_E_pi0= hhit_ECend_E_pi0->Integral();
	hhit_ECend_E_beam_pion->SetLineColor(8);
        hhit_ECend_E_beam_pion->Scale(0.001);
	hhit_ECend_E_beam_pion->Draw("same HIST");
        double rate_E_beam_pion= hhit_ECend_E_beam_pion->Integral();
	hhit_ECend_E_beam_gamma->SetLineColor(7);
        hhit_ECend_E_beam_gamma->Scale(0.001);
	hhit_ECend_E_beam_gamma->Draw("same HIST");
        double rate_E_beam_gamma= hhit_ECend_E_beam_gamma->Integral();
	hhit_ECend_E_beam_gamma_pb->SetLineColor(2);
        hhit_ECend_E_beam_gamma_pb->Scale(0.001);
	hhit_ECend_E_beam_gamma_pb->Draw("same HIST");
        double rate_E_beam_gamma_pb= hhit_ECend_E_beam_gamma_pb->Integral();
	TLegend *leg31 = new TLegend(0.12,0.6,0.5,0.88);
	leg31->AddEntry(hhit_ECend_E_beam,Form(" e^{-} from BeamOnTarget, C-foil 7 deg; rate=%f kHz",rate_E_beam),"l");
	leg31->AddEntry(hhit_ECend_E_beam_pion,Form("#pi^{#pm} from BeamOnTarget, C-foil 7 deg; rate=%f kHz",rate_E_beam_pion),"l");
	leg31->AddEntry(hhit_ECend_E_beam_gamma,Form("#gamma from BeamOnTarget, C-foil 7 deg; rate=%f kHz",rate_E_beam_gamma),"l");
	leg31->AddEntry(hhit_ECend_E_beam_gamma_pb,Form("#gamma from BeamOnTarget+ECal shielding, C-foil 7 deg; rate=%f kHz",rate_E_beam_gamma_pb),"l");
	leg31->AddEntry(hhit_ECend_E_eAll,Form("e^{-} from C-foil target, eAll 7 deg; rate=%f kHz",rate_E_eAll),"l");
	leg31->AddEntry(hhit_ECend_E_pim,Form("#pi^{-} from C-foil target, bggen #pi^{-} 7 deg; rate=%f kHz",rate_E_pim),"l");
	leg31->AddEntry(hhit_ECend_E_pip,Form("#pi^{+} from C-foil target, bggen #pi^{+} 7 deg; rate=%f kHz",rate_E_pip),"l");
	leg31->AddEntry(hhit_ECend_E_pi0,Form("e^{-} from #gamma, bggen #pi^{0} C-foil 7 deg; rate=%f kHz",rate_E_pi0),"l");
	leg31->SetTextSize(0.035);
	leg31->SetBorderSize(0);
	leg31->SetFillColor(0);
	leg31->Draw("text same");
 	for(int a=0;a<1;a++){
		c_gem[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_Espectrum_full_scattering_4deg.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));
}
