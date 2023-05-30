#include <iomanip>
#include <cstdlib>
#include <iostream> 
#include <fstream> 
#include <string>

#include "TTree.h"
#include "TStyle.h"
#include "TFile.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPad.h"

using namespace std;

void compare_e_pibggen(){
  // gStyle->SetPalette(kBird);
   gStyle->SetOptStat(0);
  gStyle->SetLabelSize(0.04,"xyz"); // size of axis values
  gStyle->SetTitleSize(0.04,"xyz");   
  gStyle->SetTitleSize(0.07,"t");    
   gStyle->SetPaintTextFormat("4.1f");   

   char expname[200];
   double min_theta,max_theta,min_p,max_p;
   double min_Q2=0,max_Q2=14,min_x=0,max_x=1;   
    double rej_FA_low,rej_FA_high,rej_LA;    
//   cout << min_theta << " " << max_theta << " " << min_p << " " << max_p << " " << endl;
  
   //TFile *file_e=new TFile("/work/halla/solid/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/rate_solid_PVDIS_LD2_eDIS_1e6.root");
   // TFile *file_e=new TFile("/work/halla/solid/zwzhao/solid/solid_svn/solid/evgen/eicRate_20101102/output/rate_solid_PVDIS_LD2_eDIS_50GeV_1e6.root");

   //get pi
   TH1F *p_gen_hist=new TH1F("p_gen_hist","p_gen_hist",110,0,11);
   TH1F *p_gen_pip_hist=new TH1F("p_gen_pip_hist","p_gen_pip_hist",110,0,11);
   
   int filecount;
    filecount=100;   
//     filecount=10;    
    
   for(int i=0; i<filecount;i++){
      string filename_hPTheta_name=Form("/lustre19/expphy/volatile/halla/solid/tianye/bggen_zvertex/bggen/HallC_beamtest_LH2/pim/hallD_pion_m_LH_10k_%i.lund",i+1);
      ifstream input(filename_hPTheta_name.c_str());
      string filename_hPTheta_name_pip=Form("/lustre19/expphy/volatile/halla/solid/tianye/bggen_zvertex/bggen/HallC_beamtest_LH2/pip/hallD_pion_p_LH_10k_%i.lund",i+1);
      ifstream input_pip(filename_hPTheta_name_pip.c_str());
      //if (input.good()) {} cout << "open file " << filename_hPTheta_name << " OK" << "\r";
      //else {cout << "can't open the file" << endl; return;}

      double  header[10];
      double  particles[14];
      double  header_pip[10];
      double  particles_pip[14];

      for (int j = 0; j<10000; j++) {
	      input >> header[0] >> header[1] >> header[2] >> header[3] >> header[4] >> header[5] >> header[6] >> header[7] >> header[8] >> header[9];
	      input >> particles[0] >> particles[1] >> particles[2] >> particles[3] >> particles[4] >> particles[5] >> particles[6] >> particles[7] >> particles[8] >> particles[9] >> particles[10] >> particles[11] >> particles[12] >> particles[13];
	      input_pip >> header_pip[0] >> header_pip[1] >> header_pip[2] >> header_pip[3] >> header_pip[4] >> header_pip[5] >> header_pip[6] >> header_pip[7] >> header_pip[8] >> header_pip[9];
	      input_pip >> particles_pip[0] >> particles_pip[1] >> particles_pip[2] >> particles_pip[3] >> particles_pip[4] >> particles_pip[5] >> particles_pip[6] >> particles_pip[7] >> particles_pip[8] >> particles_pip[9] >> particles_pip[10] >> particles_pip[11] >> particles_pip[12] >> particles_pip[13];
	      
 	     // cout << header[9] << " " << particles[6] << " " << particles[7] << " " << particles[8] << endl;
	      double rate=header[9];
	      double rate_pip=header_pip[9];
	      double px=particles[6],py=particles[7],pz=particles[8];	      
	      double px_pip=particles_pip[6],py_pip=particles_pip[7],pz_pip=particles_pip[8];	      
	      double p=sqrt(px*px+py*py+pz*pz);
	      double p_pip=sqrt(px_pip*px_pip+py_pip*py_pip+pz_pip*pz_pip);
	      double theta=acos(pz/p)/3.1416*180;
	      double theta_pip=acos(pz_pip/p_pip)/3.1416*180;
	      double Q2=4*11*p*sin(theta/2/180*3.1416)*sin(theta/2/180*3.1416);
	      double x=Q2/2/0.938/(11-p);

	      double rate_rej=rate;
              //cout<<"rate="<<rate<<"p="<<p<<endl;
             // if(theta>34.5 && theta<35.5){
	      p_gen_hist->Fill(p,rate);
             // }
             // if(theta_pip>34.5 && theta_pip<35.5){
     	      p_gen_pip_hist->Fill(p_pip,rate_pip);	      
             // }
    }
    
   }
   
   cout << "pi bggen files " << filecount << endl;

    //in kHz and normalized by filecount   
   p_gen_hist->Scale(1e-3/filecount);
   p_gen_pip_hist->Scale(1e-3/filecount);
   TCanvas *cPTheta_pi = new TCanvas("cPTheta_pi","cPTheta_pi",1800,1000);
   cPTheta_pi->Divide(1,2);
   cPTheta_pi->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
   p_gen_pip_hist->SetTitle("rate (kHz);P (MeV/c);rate (kHz)");       
   p_gen_pip_hist->SetLineColor(1);
   p_gen_pip_hist->Draw("HIST");
   double rate_pip= p_gen_pip_hist->Integral();
   p_gen_hist->SetLineColor(2);
   p_gen_hist->Draw("same HIST");
   double rate_pim= p_gen_hist->Integral();
   cout<<"pip_rate="<<rate_pip<<"pim_rate="<<rate_pim<<endl;
  TLegend *leg14 = new TLegend(0.4,0.7,0.8,0.88);
  leg14->AddEntry(p_gen_hist,Form("bggen #pi^{-} ; total rate=%f kHz",rate_pim),"l");
  leg14->AddEntry(p_gen_pip_hist,Form("bggen #pi^{+} ; total rate=%f kHz",rate_pip),"l");
  leg14->SetTextSize(0.06);
  leg14->SetBorderSize(0);
  leg14->SetFillColor(0);
  leg14->Draw("text same");
   cPTheta_pi->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
 TH1F *p_gen_pip_hist_clone =(TH1F*)p_gen_pip_hist->Clone();
    p_gen_pip_hist_clone->Divide(p_gen_hist); 
    p_gen_pip_hist_clone->SetTitle("ratio;P (MeV/c);rate_#pi^{+}/rate_#pi^{-}");       
    p_gen_pip_hist_clone->Draw("HIST");   
   cPTheta_pi->SaveAs("rate_gen_comparison_pim_pip.pdf");         
}
