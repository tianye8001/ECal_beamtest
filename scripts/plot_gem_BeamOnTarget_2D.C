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

void plot_gem_BeamOnTarget_shielding_2D(){
	gStyle->SetOptStat(0);
	gStyle->SetPalette(1);
	TFile *f1 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_beamOntarget_80uA_sangle/HallC_beamtest_BeamOnTarget_1e11_8deg_80uA_newCH_output_gem_gammaE_underflow.root");
	TFile *f2 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_eAll_sangle/HallC_beamtest_eAll_sangle_8deg_filenum100_newCH_8GeV_output_gem_gammaE_underflow.root");
	TFile *f3 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pi0_sangle/HallC_beamtest_bggen_LH2_pi0_8deg_filenum19880_newCh_output_gem_gammaE_underflow.root");
	TFile *f4 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pip_sangle/HallC_beamtest_bggen_LH2_pip_8deg_filenum19840_newCh_8GeV_output_gem_gammaE_underflow.root");
	TFile *f5 = new TFile("/volatile/halla/solid/tianye/container/HallC_beamtest_bggen_LH2_pim_sangle/HallC_beamtest_bggen_LH2_pim_8deg_filenum19880_newCh_8GeV_output_gem_gammaE_underflow.root");
	TH2F *vr_vs_vz_hist;       
	TH2F *vr_vs_vz_eAll_hist;       
	TH2F *vr_vs_vz_pim_hist;       
	TH2F *vr_vs_vz_pi0_hist;       
	TH2F *vr_vs_vz_pip_hist;       
	TH2F *vz_vs_theta_hist;       
	TH2F *vz_vs_theta_gem2_hist;       

	TH2F *vr_vs_vz_gem2_hist;       
	TH2F *vr_vs_vz_eAll_gem2_hist;       
	TH2F *vr_vs_vz_pim_gem2_hist;       
	TH2F *vr_vs_vz_pi0_gem2_hist;       
	TH2F *vr_vs_vz_pip_gem2_hist;       
        vz_vs_theta_hist = (TH2F*)f1->Get("gen_Thetavz_gem1");
        vz_vs_theta_gem2_hist = (TH2F*)f1->Get("gen_Thetavz_gem2");
        vr_vs_vz_hist = (TH2F*)f1->Get("vertexZ_vs_vertexR_hist");
        vr_vs_vz_gem2_hist = (TH2F*)f1->Get("vertexZ_vs_vertexR_gem2_hist");
        vr_vs_vz_eAll_hist = (TH2F*)f2->Get("vertexZ_vs_vertexR_hist");
        vr_vs_vz_eAll_gem2_hist = (TH2F*)f2->Get("vertexZ_vs_vertexR_gem2_hist");
        vr_vs_vz_pi0_hist = (TH2F*)f3->Get("vertexZ_vs_vertexR_hist");
        vr_vs_vz_pi0_gem2_hist = (TH2F*)f3->Get("vertexZ_vs_vertexR_gem2_hist");
        vr_vs_vz_pip_hist = (TH2F*)f4->Get("vertexZ_vs_vertexR_hist");
        vr_vs_vz_pip_gem2_hist = (TH2F*)f4->Get("vertexZ_vs_vertexR_gem2_hist");
        vr_vs_vz_pim_hist = (TH2F*)f5->Get("vertexZ_vs_vertexR_hist");
        vr_vs_vz_pim_gem2_hist = (TH2F*)f5->Get("vertexZ_vs_vertexR_gem2_hist");
	TCanvas *c_gem[7];
	c_gem[5] = new TCanvas("c_gem[5]", "flux #theta",1800,1000);
	gPad->SetLogz();
        vz_vs_theta_hist->GetXaxis()->SetTitle("hit #theta (deg)");
        vz_vs_theta_hist->GetYaxis()->SetTitle("vertex Z (cm)");
        vz_vs_theta_hist->SetTitle("gem1");
        vz_vs_theta_hist->GetXaxis()->SetRangeUser(0,90);	
        vz_vs_theta_hist->Draw("COLZ");
        /*TLatex l2;
        l2.SetTextSize(0.03);
        l2.DrawLatex(40,980,"beam line from CL 0.729 m,d=7cm,dz=8 mm ");
        l2.DrawLatex(40,940,"beam line from CL 2.495 m,d=5.1cm,dz=8 mm");
        l2.DrawLatex(40,900,"beam line from CL 4.693 m,d=12.7cm,dz=8 mm ");
        l2.DrawLatex(40,860,"beam line from CL 7.954 m,d=12.7cm,dz=8 mm");
        l2.DrawLatex(40,820,"beam line from CL 8.81 m,d=27.3cm,dz=8 mm");
        l2.DrawLatex(40,780,"beam line from CL 10.81 m,d=27.3cm,dz=8 mm");*/
	c_gem[6] = new TCanvas("c_gem[6]", "flux #theta",1800,1000);
	gPad->SetLogz();
        vz_vs_theta_gem2_hist->GetXaxis()->SetTitle("hit #theta (deg)");
        vz_vs_theta_gem2_hist->GetYaxis()->SetTitle("vertex Z (cm)");
        vz_vs_theta_gem2_hist->SetTitle("gem2");
        vz_vs_theta_gem2_hist->GetXaxis()->SetRangeUser(0,90);	
        vz_vs_theta_gem2_hist->Draw("COLZ");
        /*TLatex l3;
        l3.SetTextSize(0.03);
        l3.DrawLatex(5,980,"beam line from CL 0.729 m,d=7cm,dz=8 mm ");
        l3.DrawLatex(5,940,"beam line from CL 2.495 m,d=5.1cm,dz=8 mm");
        l3.DrawLatex(5,900,"beam line from CL 4.693 m,d=12.7cm,dz=8 mm ");
        l3.DrawLatex(5,860,"beam line from CL 7.954 m,d=12.7cm,dz=8 mm");
        l3.DrawLatex(5,820,"beam line from CL 8.81 m,d=27.3cm,dz=8 mm");
        l3.DrawLatex(5,780,"beam line from CL 10.81 m,d=27.3cm,dz=8 mm");*/
	c_gem[4] = new TCanvas("c_gem[4]", "flux #theta",1800,1000);
        c_gem[4]->Divide(2,2);
        c_gem[4]->cd(1);
	gPad->SetLogz();
        vr_vs_vz_hist->SetTitle(" #gamma from BeamOnTarget gem1");	
        vr_vs_vz_hist->GetYaxis()->SetRangeUser(0,150);	
        vr_vs_vz_hist->Draw("COLZ");	
        c_gem[4]->cd(2);
	gPad->SetLogz();
        TH2F *vr_vs_vz_clone_hist = (TH2F*)vr_vs_vz_hist->Clone();  
        vr_vs_vz_clone_hist->SetTitle("#gamma from BeamOnTarget gem1 Zoom In");	
        vr_vs_vz_clone_hist->GetXaxis()->SetRangeUser(-10,100);	
        vr_vs_vz_clone_hist->GetYaxis()->SetRangeUser(0,10);	
        vr_vs_vz_clone_hist->Draw("COLZ");	
        c_gem[4]->cd(3);
	gPad->SetLogz();
        vr_vs_vz_gem2_hist->SetTitle("#gamma from BeamOnTarget gem2");	
        vr_vs_vz_gem2_hist->GetYaxis()->SetRangeUser(0,150);	
        vr_vs_vz_gem2_hist->Draw("COLZ");	
        c_gem[4]->cd(4);
	gPad->SetLogz();
        TH2F *vr_vs_vz_gem2_clone_hist = (TH2F*)vr_vs_vz_gem2_hist->Clone();  
        vr_vs_vz_gem2_clone_hist->SetTitle("#gamma from BeamOnTarget gem2 Zoom In");	
        vr_vs_vz_gem2_clone_hist->GetXaxis()->SetRangeUser(-10,100);	
        vr_vs_vz_gem2_clone_hist->GetYaxis()->SetRangeUser(0,10);	
        vr_vs_vz_gem2_clone_hist->Draw("COLZ");	
	c_gem[0] = new TCanvas("c_gem[0]", "gem",1800,1000);
        c_gem[0]->Divide(2,2);
        c_gem[0]->cd(1);
	gPad->SetLogz();
        vr_vs_vz_eAll_hist->SetTitle("#gamma from eAll gem1");	
        vr_vs_vz_eAll_hist->GetYaxis()->SetRangeUser(0,150);	
        vr_vs_vz_eAll_hist->Draw("COLZ");	
        TLatex l;
        l.SetTextSize(0.05);
        l.DrawLatex(10,130,"target -5 cm <z< 5 cm");
        c_gem[0]->cd(2);
	gPad->SetLogz();
        TH2F *vr_vs_vz_eAll_clone_hist = (TH2F*)vr_vs_vz_eAll_hist->Clone();  
        vr_vs_vz_eAll_clone_hist->SetTitle("#gamma from eAll gem1 zoom in");	
        vr_vs_vz_eAll_clone_hist->GetXaxis()->SetRangeUser(-10,100);	
        vr_vs_vz_eAll_clone_hist->GetYaxis()->SetRangeUser(0,10);	
        vr_vs_vz_eAll_clone_hist->Draw("COLZ");	
      
        c_gem[0]->cd(3);
	gPad->SetLogz();
        vr_vs_vz_eAll_gem2_hist->SetTitle("#gamma from eAll gem2");	
        vr_vs_vz_eAll_gem2_hist->GetYaxis()->SetRangeUser(0,150);	
        vr_vs_vz_eAll_gem2_hist->Draw("COLZ");	
        TLatex l1;
        l1.SetTextSize(0.04);
        l1.DrawLatex(-5,130,"beam line from CL 0.729 m,d=7cm,dz=8 mm ");
        l1.DrawLatex(-5,120,"beam line from CL 2.495 m,d=5.1cm,dz=8 mm");
        l1.DrawLatex(-5,110,"beam line from CL 4.693 m,d=12.7cm,dz=8 mm ");
        l1.DrawLatex(-5,100,"beam line from CL 7.954 m,d=12.7cm,dz=8 mm");
        l1.DrawLatex(-5,90,"beam line from CL 8.81 m,d=27.3cm,dz=8 mm");
        l1.DrawLatex(-5,80,"beam line from CL 10.81 m,d=27.3cm,dz=8 mm");
        c_gem[0]->cd(4);
	gPad->SetLogz();
        TH2F *vr_vs_vz_eAll_gem2_clone_hist = (TH2F*)vr_vs_vz_eAll_gem2_hist->Clone();  
        vr_vs_vz_eAll_gem2_clone_hist->SetTitle("#gamma from eAll gem2 zoom in ");	
        vr_vs_vz_eAll_gem2_clone_hist->GetXaxis()->SetRangeUser(-10,100);	
        vr_vs_vz_eAll_gem2_clone_hist->GetYaxis()->SetRangeUser(0,10);	
        vr_vs_vz_eAll_gem2_clone_hist->Draw("COLZ");	
	c_gem[1] = new TCanvas("c_gem[1]", "gem",1800,1000);
        c_gem[1]->Divide(2,2);
        c_gem[1]->cd(1);
	gPad->SetLogz();
        vr_vs_vz_pip_hist->SetTitle("#gamma from #pi^{+} gem1");	
        vr_vs_vz_pip_hist->GetYaxis()->SetRangeUser(0,150);	
        vr_vs_vz_pip_hist->Draw("COLZ");	
        c_gem[1]->cd(2);
	gPad->SetLogz();
        TH2F *vr_vs_vz_pip_clone_hist = (TH2F*)vr_vs_vz_pip_hist->Clone();  
        vr_vs_vz_pip_clone_hist->SetTitle("#gamma from #pi^{+} gem1 zoom in");	
        vr_vs_vz_pip_clone_hist->GetXaxis()->SetRangeUser(-10,100);	
        vr_vs_vz_pip_clone_hist->GetYaxis()->SetRangeUser(0,10);	
        vr_vs_vz_pip_clone_hist->Draw("COLZ");	
        c_gem[1]->cd(3);
	gPad->SetLogz();
        vr_vs_vz_pip_gem2_hist->SetTitle("#gamma from #pi^{+} gem2");	
        vr_vs_vz_pip_gem2_hist->GetYaxis()->SetRangeUser(0,150);	
        vr_vs_vz_pip_gem2_hist->Draw("COLZ");	
        c_gem[1]->cd(4);
	gPad->SetLogz();
        TH2F *vr_vs_vz_pip_gem2_clone_hist = (TH2F*)vr_vs_vz_pip_gem2_hist->Clone();  
        vr_vs_vz_pip_gem2_clone_hist->SetTitle("#gamma from #pi^{+} gem2 zoom in ");	
        vr_vs_vz_pip_gem2_clone_hist->GetXaxis()->SetRangeUser(-10,100);	
        vr_vs_vz_pip_gem2_clone_hist->GetYaxis()->SetRangeUser(0,10);	
        vr_vs_vz_pip_gem2_clone_hist->Draw("COLZ");	
	c_gem[2] = new TCanvas("c_gem[2]", "gem",1800,1000);
        c_gem[2]->Divide(2,2);
        c_gem[2]->cd(1);
	gPad->SetLogz();
        vr_vs_vz_pi0_hist->SetTitle("#gamma from #pi^{0} gem1");	
        vr_vs_vz_pi0_hist->GetYaxis()->SetRangeUser(0,150);	
        vr_vs_vz_pi0_hist->Draw("COLZ");	
        c_gem[2]->cd(2);
	gPad->SetLogz();
        TH2F *vr_vs_vz_pi0_clone_hist = (TH2F*)vr_vs_vz_pip_hist->Clone();  
        vr_vs_vz_pi0_clone_hist->SetTitle("#gamma from #pi^{0} gem1 zoom in");	
        vr_vs_vz_pi0_clone_hist->GetXaxis()->SetRangeUser(-10,100);	
        vr_vs_vz_pi0_clone_hist->GetYaxis()->SetRangeUser(0,10);	
        vr_vs_vz_pi0_clone_hist->Draw("COLZ");	
        c_gem[2]->cd(3);
	gPad->SetLogz();
        vr_vs_vz_pi0_gem2_hist->SetTitle("#gamma from #pi^{0} gem2");	
        vr_vs_vz_pi0_gem2_hist->GetYaxis()->SetRangeUser(0,150);	
        vr_vs_vz_pi0_gem2_hist->Draw("COLZ");	
        c_gem[2]->cd(4);
	gPad->SetLogz();
        TH2F *vr_vs_vz_pi0_gem2_clone_hist = (TH2F*)vr_vs_vz_pi0_gem2_hist->Clone();  
        vr_vs_vz_pi0_gem2_clone_hist->SetTitle("#gamma from #pi^{0} gem2 zoom in ");	
        vr_vs_vz_pi0_gem2_clone_hist->GetXaxis()->SetRangeUser(-10,100);	
        vr_vs_vz_pi0_gem2_clone_hist->GetYaxis()->SetRangeUser(0,10);	
        vr_vs_vz_pi0_gem2_clone_hist->Draw("COLZ");	
	c_gem[3] = new TCanvas("c_gem[3]", "gem",1800,1000);
        c_gem[3]->Divide(2,2);
        c_gem[3]->cd(1);
	gPad->SetLogz();
        vr_vs_vz_pim_hist->SetTitle("#gamma from #pi^{-} gem1");	
        vr_vs_vz_pim_hist->GetYaxis()->SetRangeUser(0,150);	
        vr_vs_vz_pim_hist->Draw("COLZ");	
        c_gem[3]->cd(2);
	gPad->SetLogz();
        TH2F *vr_vs_vz_pim_clone_hist = (TH2F*)vr_vs_vz_pim_hist->Clone();  
        vr_vs_vz_pim_clone_hist->SetTitle("#gamma from #pi^{-} gem1 zoom in");	
        vr_vs_vz_pim_clone_hist->GetXaxis()->SetRangeUser(-10,100);	
        vr_vs_vz_pim_clone_hist->GetYaxis()->SetRangeUser(0,10);	
        vr_vs_vz_pim_clone_hist->Draw("COLZ");	
        c_gem[3]->cd(3);
	gPad->SetLogz();
        vr_vs_vz_pim_gem2_hist->SetTitle("#gamma from #pi^{-} gem2");	
        vr_vs_vz_pim_gem2_hist->GetYaxis()->SetRangeUser(0,150);	
        vr_vs_vz_pim_gem2_hist->Draw("COLZ");	
        c_gem[3]->cd(4);
	gPad->SetLogz();
        TH2F *vr_vs_vz_pim_gem2_clone_hist = (TH2F*)vr_vs_vz_pim_gem2_hist->Clone();  
        vr_vs_vz_pim_gem2_clone_hist->SetTitle("#gamma from #pi^{-} gem2 zoom in ");	
        vr_vs_vz_pim_gem2_clone_hist->GetXaxis()->SetRangeUser(-10,100);	
        vr_vs_vz_pim_gem2_clone_hist->GetYaxis()->SetRangeUser(0,10);	
        vr_vs_vz_pim_gem2_clone_hist->Draw("COLZ");	
 	for(int a=5;a<7;a++){
		c_gem[a]->SaveAs(Form("c%d.pdf",a));
	}
	gSystem->Exec("pdfunite ./c*.pdf ./HallC_BeamOnTarget_8deg_gem1_gamma_newCh.pdf");
	gSystem->Exec(Form("rm -rf ./c*.pdf"));
}
