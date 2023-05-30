#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include <sstream>
#include <iostream>
void structure_fit_txt_costheta1(int WbinN=0)
{
 const int cot=1;
//const int WbinN=7;
gStyle->SetOptStat(0);
  //gStyle->SetOptFit(101);
  gStyle->SetLabelSize(0.065,"xy");
  gStyle->SetTitleSize(0.25,"t");
  gStyle->SetLabelFont(62,"xy");
//gSystem->Load("libMathMore");
ofstream outfile1(Form("structureL%d_W%d.txt",cot,WbinN));
ofstream outfile2(Form("structureTT%d_W%d.txt",cot,WbinN));
ofstream outfile3(Form("structureLT%d_W%d.txt",cot,WbinN));
ofstream outfile4(Form("structureL%d_quasi_W%d.txt",cot,WbinN));
ofstream outfile5(Form("structureTT%d_quasi_W%d.txt",cot,WbinN));
ofstream outfile6(Form("structureLT%d_quasi_W%d.txt",cot,WbinN));
    
ifstream infile4(Form("corss_section_fitparameters_ongoing_largebinQ1_newloop_e1erunynewboost_simpifid_quasifree_newboost_W%d.txt",WbinN));
ifstream infile5(Form("corss_section_fitparameters_ongoing_largebinQ2_newloop_e1erunynewboost_simpifid_quasifree_newboost_W%d.txt",WbinN));
ifstream infile6(Form("corss_section_fitparameters_ongoing_largebinQ3_newloop_e1erunynewboost_simpifid_quasifree_newboost_W%d.txt",WbinN));
ifstream infile10(Form("corss_section_fitparameters_ongoing_largebinQ1_newloop_e1erunynewboost_simpifid_exclusive_newboost_W%d.txt",WbinN));
ifstream infile11(Form("corss_section_fitparameters_ongoing_largebinQ2_newloop_e1erunynewboost_simpifid_exclusive_newboost_W%d.txt",WbinN));
ifstream infile12(Form("corss_section_fitparameters_ongoing_largebinQ3_newloop_e1erunynewboost_simpifid_exclusive_newboost_W%d.txt",WbinN));

ifstream infile13(Form("../analye1e/e1e_pass1_rootfile/pass1_data/systamtic_err/simu_data/corss_section_legendre_largebinQ1_testmore1_w%d.txt",WbinN));
ifstream infile14(Form("../analye1e/e1e_pass1_rootfile/pass1_data/systamtic_err/simu_data/corss_section_legendre_largebinQ2_testmore1_w%d.txt",WbinN));
ifstream infile15(Form("../analye1e/e1e_pass1_rootfile/pass1_data/systamtic_err/simu_data/corss_section_legendre_largebinQ3_testmore1_w%d.txt",WbinN));

TFile *f9 = new TFile("/Users/yetian/analye1e/e1e_pass1_rootfile/pass1_data/CM_ppi_plot_exclusive.root");
TFile *f10 = new TFile("/Users/yetian/analye1e/e1e_pass1_rootfile/pass1_data/CM_ppi_plot_quasifree.root");
ostringstream sstr;
ostringstream sstr1;
ostringstream sstr2;
double *parA,*parA_error,*parB,*parB_error,*parC,*parC_error,*parA_quasi,*parA_quasi_error,*parB_quasi,*parB_quasi_error, *parC_quasi, *parC_quasi_error;
double *parA_l3,*parA_l3_error,*parB_l3,*parB_l3_error,*parC_l3,*parC_l3_error,*parA_l3_quasi,*parA_l3_quasi_error,*parB_l3_quasi,*parB_l3_quasi_error, *parC_l3_quasi, *parC_l3_quasi_error;
double theta5_Q3[9]={-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9};
double sintheta_Q3[9]={0};
double sintheta_sqrQ3[9]={0};

double theta5_error_Q3[9];
double theta_Q3[9]={-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9};
double theta_error_Q3[9];
double thetamore_Q3[9]={-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9};
double thetamore_error_Q3[9];
double theta_maid_Q3[9]={-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9};
double theta_error_maid_Q3[9];

double theta5[10]={-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9};
double theta5_error[10];
double sintheta5[9]={0};
double sintheta5_sqr[9]={0};
double theta[10]={-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9};
double theta_error[10];
double thetamore[10]={-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9};
double thetamore_error[10];
double theta_maid[10]={-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9};
double theta_error_maid[10];
char name[20];
double mp = 0.939565;
/*double epilo_Q1=0.872;
double epilo_Q2=0.816;
double epilo_Q3=0.752;*/
   double val_W = 1.1125+0.025*(WbinN-1);                              
   double val_Q1 = 0.5;
   double mu1 = (val_Q1+val_W*val_W-mp*mp)/(2*mp);
   double Eout1= 2.039-mu1;
   double epilo_Q1 = 1/(1+2*(val_Q1+mu1*mu1)/(4*2.039*Eout1-val_Q1));
   double val_Q2 = 0.7;
   double mu2 = (val_Q2+val_W*val_W-mp*mp)/(2*mp);
   double Eout2= 2.039-mu2;
   double epilo_Q2 = 1/(1+2*(val_Q2+mu2*mu2)/(4*2.039*Eout2-val_Q2));
   double val_Q3 = 0.9;
   double mu3 = (val_Q3+val_W*val_W-mp*mp)/(2*mp);
   double Eout3= 2.039-mu3;
   double epilo_Q3 = 1/(1+2*(val_Q3+mu3*mu3)/(4*2.039*Eout3-val_Q3));
   //double kgamma= (val_W*val_W-mp*mp)/(2*val_W);
   double kgamma=1 ;
TF1 *func;
TF1 *func2;
TF1 *func3;
TF1 *func4;
TF1 *func5;
TF1 *func6;
TF1 *func7;
TF1 *func8;
TF1 *func9;
TH1F *sigmaL_cros;
TH1F *sigmaTT_cros;
TH1F *sigmaTL_cros;

TH1F *sigmaL_cros_Lee_Q2;
TH1F *sigmaTT_cros_Lee_Q2;
TH1F *sigmaTL_cros_Lee_Q2;
TH1F *sigmaL_cros_Lee_Q3;
TH1F *sigmaTT_cros_Lee_Q3;
TH1F *sigmaTL_cros_Lee_Q3;
TH1F *CMppi_Q1_exclusive_hist[12];
TH1F *CMppi_Q1_quasifree_hist[12];
TH1F *CMppi_Q2_exclusive_hist[12];
TH1F *CMppi_Q2_quasifree_hist[12];
TH1F *CMppi_Q3_exclusive_hist[12];
TH1F *CMppi_Q3_quasifree_hist[12];
TH1F *sigmaL_crossaid;
TH1F *sigmaTT_crossaid;
TH1F *sigmaTL_crossaid;
TH1F *sigmaL_cros_Q2;
TH1F *sigmaTT_cros_Q2;
TH1F *sigmaTL_cros_Q2;
TH1F *sigmaL_cros_Q2said;
TH1F *sigmaTT_cros_Q2said;
TH1F *sigmaTL_cros_Q2said;
TH1F *sigmaL_cros_Q3;
TH1F *sigmaTT_cros_Q3;
TH1F *sigmaTL_cros_Q3;
TH1F *sigmaL_cros_Q3said;
TH1F *sigmaTT_cros_Q3said;
TH1F *sigmaTL_cros_Q3said;
sstr<<"W="<<1.1125+0.025*(WbinN-1)<<"GeV, Q^{2}=0.5"<<"GeV^{2}";
sstr1<<"W="<<1.1125+0.025*(WbinN-1)<<"GeV, Q^{2}=0.7"<<"GeV^{2}";
sstr2<<"W="<<1.1125+0.025*(WbinN-1)<<"GeV, Q^{2}=0.9"<<"GeV^{2}";
    double mean_ppi_Q1[11]={0};
    double mean_ppi_Q2[11]={0};
    double mean_ppi_Q3[11]={0};
    double mean_ppi_quasi_Q1[11]={0};
    double mean_ppi_quasi_Q2[11]={0};
    double mean_ppi_quasi_Q3[11]={0};
    
    for(int m=1;m<12;m++){
    CMppi_Q1_exclusive_hist[m]= (TH1F*)f9->Get(Form("CMppi_Wbin%d_Q2bin1_costheta%d",WbinN,m));
    CMppi_Q1_exclusive_hist[m]->SetTitle(sstr.str().c_str());
    CMppi_Q2_exclusive_hist[m]= (TH1F*)f9->Get(Form("CMppi_Wbin%d_Q2bin2_costheta%d",WbinN,m));
    CMppi_Q2_exclusive_hist[m]->SetTitle(sstr1.str().c_str());
    CMppi_Q3_exclusive_hist[m]= (TH1F*)f9->Get(Form("CMppi_Wbin%d_Q2bin3_costheta%d",WbinN,m));
    CMppi_Q3_exclusive_hist[m]->SetTitle(sstr2.str().c_str());
    CMppi_Q1_quasifree_hist[m]= (TH1F*)f10->Get(Form("CMppi_Wbin%d_Q2bin1_costheta%d",WbinN,m));
    CMppi_Q1_quasifree_hist[m]->SetTitle(sstr.str().c_str());
    CMppi_Q2_quasifree_hist[m]= (TH1F*)f10->Get(Form("CMppi_Wbin%d_Q2bin2_costheta%d",WbinN,m));
    CMppi_Q2_quasifree_hist[m]->SetTitle(sstr1.str().c_str());
    CMppi_Q3_quasifree_hist[m]= (TH1F*)f10->Get(Form("CMppi_Wbin%d_Q2bin3_costheta%d",WbinN,m));
    CMppi_Q3_quasifree_hist[m]->SetTitle(sstr2.str().c_str());
    /*mean_ppi_Q1[m-1]=CMppi_Q1_exclusive_hist[m]->GetMean();
    mean_ppi_Q2[m-1]=CMppi_Q2_exclusive_hist[m]->GetMean();
    mean_ppi_Q3[m-1]=CMppi_Q3_exclusive_hist[m]->GetMean();
    mean_ppi_quasi_Q1[m-1]=CMppi_Q1_quasifree_hist[m]->GetMean();
    mean_ppi_quasi_Q2[m-1]=CMppi_Q2_quasifree_hist[m]->GetMean();
    mean_ppi_quasi_Q3[m-1]=CMppi_Q3_quasifree_hist[m]->GetMean();
        cout<<"m="<<m-1<<"mean_ppi_Q1="<<mean_ppi_Q1[m-1]<<"mean_ppi_Q2="<<mean_ppi_Q2[m-1]<<"mean_ppi_Q3="<<mean_ppi_Q3[m-1]<<endl;
    cout<<"m="<<m-1<<"mean_ppi_quasi_Q1="<<mean_ppi_quasi_Q1[m-1]<<"mean_ppi_quasi_Q2="<<mean_ppi_quasi_Q2[m-1]<<"mean_ppi_quasi_Q3="<<mean_ppi_quasi_Q3[m-1]<<endl;
    */
    mean_ppi_Q1[m-1]=1;
    mean_ppi_Q2[m-1]=1;
    mean_ppi_Q3[m-1]=1;
    mean_ppi_quasi_Q1[m-1]=1;
    mean_ppi_quasi_Q2[m-1]=1;
    mean_ppi_quasi_Q3[m-1]=1;
        
    }

  sstr.str("");
  sstr1.str("");
  sstr2.str("");
double par0[10],par1[10],par2[10];
double par_error0[10],par_error1[10],par_error2[10];
double par_Q2_0[9],par_Q2_1[9],par_Q2_2[9];
double par_Q2_error0[9],par_Q2_error1[9],par_Q2_error2[9];
double par_Q3_0[9],par_Q3_1[9],par_Q3_2[9];
double par_Q3_error0[9],par_Q3_error1[9],par_Q3_error2[9];


double par0_maid[10],par1_maid[10],par2_maid[10];
double par_error0_maid[10],par_error1_maid[10],par_error2_maid[10];
double par_Q2_0_maid[9],par_Q2_1_maid[9],par_Q2_2_maid[9];
double par_Q2_error0_maid[9],par_Q2_error1_maid[9],par_Q2_error2_maid[9];
double par_Q3_0_maid[9],par_Q3_1_maid[9],par_Q3_2_maid[9];
double par_Q3_error0_maid[9],par_Q3_error1_maid[9],par_Q3_error2_maid[9];
double par_maid[10];
double par_maid_Q3[9];
double sys_sigmaL_Q1[10],sys_sigmaL_Q2[9],sys_sigmaL_Q3[9];
double sys_sigmaLT_Q1[10],sys_sigmaLT_Q2[9],sys_sigmaLT_Q3[9];
double sys_sigmaTT_Q1[10],sys_sigmaTT_Q2[9],sys_sigmaTT_Q3[9];

double syserr_sigmaL_Q1[10],syserr_sigmaL_Q2[9],syserr_sigmaL_Q3[9];
double syserr_sigmaLT_Q1[10],syserr_sigmaLT_Q2[9],syserr_sigmaLT_Q3[9];
double syserr_sigmaTT_Q1[10],syserr_sigmaTT_Q2[9],syserr_sigmaTT_Q3[9];
double sigmaL_maid_Q1[10],sigmaL_maid_Q2[9],sigmaL_maid_Q3[9];
double sigmaL_Q1[10],sigmaL_Q2[9],sigmaL_Q3[9];
double sigmaL_Q1_err[10],sigmaL_Q2_err[9],sigmaL_Q3_err[9];
double sigmaL_quasi_Q1[10],sigmaL_quasi_Q2[9],sigmaL_quasi_Q3[9];
double sigmaL_quasi_Q1_err[10],sigmaL_quasi_Q2_err[9],sigmaL_quasi_Q3_err[9];
double syserr_sigmaLerr[10];
double syserr_sigmaLerr_Q3[9];
for(int i=0;i<9;i++)
{theta_error_Q3[i]=0;
syserr_sigmaLerr_Q3[i]=0;
theta_error_maid_Q3[i]=0;
par_maid_Q3[i]=0;
theta5_error_Q3[i]=0;
thetamore_error_Q3[i]=0;
sintheta_Q3[i]=sqrt(1-pow(theta5_Q3[i],2));
sintheta_sqrQ3[i]=1-pow(theta5_Q3[i],2);
//cout<<"sintheta_Q3="<<sintheta_Q3[i]<<"theta_sqrt="<<sintheta_sqrQ3[i]<<endl;
}
for(int i=0;i<10;i++)
{theta_error[i]=0;
syserr_sigmaLerr[i]=0;
theta_error_maid[i]=0;
par_maid[i]=0;
theta5_error[i]=0;
thetamore_error[i]=0;
sintheta5[i]=sqrt(1-pow(theta5[i],2));
sintheta5_sqr[i]=1-pow(theta5[i],2);
//cout<<"sintheta5="<<sintheta5[i]<<"theta5_sqrt="<<sintheta5_sqr[i]<<endl;
}
double par0_noR[10],par1_noR[10],par2_noR[10];
double par_error0_noR[10],par_error1_noR[10],par_error2_noR[10];
double par_Q2_0_noR[9],par_Q2_1_noR[9],par_Q2_2_noR[9];
double par_Q2_error0_noR[9],par_Q2_error1_noR[9],par_Q2_error2_noR[9];
double par_Q3_0_noR[9],par_Q3_1_noR[9],par_Q3_2_noR[9];
double par_Q3_error0_noR[9],par_Q3_error1_noR[9],par_Q3_error2_noR[9];

double par0_prfid[10],par1_prfid[10],par2_prfid[10];
double par_error0_prfid[10],par_error1_prfid[10],par_error2_prfid[10];
double par_Q2_0_prfid[9],par_Q2_1_prfid[9],par_Q2_2_prfid[9];
double par_Q2_error0_prfid[9],par_Q2_error1_prfid[9],par_Q2_error2_prfid[9];
double par_Q3_0_prfid[9],par_Q3_1_prfid[9],par_Q3_2_prfid[9];
double par_Q3_error0_prfid[9],par_Q3_error1_prfid[9],par_Q3_error2_prfid[9];


double t5_par0[10],t5_par1[10],t5_par2[10];
double t5_par_error0[10],t5_par_error1[10],t5_par_error2[10];
double t5_par_Q2_0[9],t5_par_Q2_1[9],t5_par_Q2_2[9];
double t5_par_Q2_error0[9],t5_par_Q2_error1[9],t5_par_Q2_error2[9];
double t5_par_Q3_0[9],t5_par_Q3_1[9],t5_par_Q3_2[9];
double t5_par_Q3_error0[9],t5_par_Q3_error1[9],t5_par_Q3_error2[9];

double sigmaTT[10],sigmaTT_error[10],sigmaTT_Q2[9],sigmaTT_Q3[9],sigmaTT_Q2_error[9],sigmaTT_Q3_error[9];
double sigmaLT[10],sigmaLT_error[10],sigmaLT_Q2[9],sigmaLT_Q3[9],sigmaLT_Q2_error[9],sigmaLT_Q3_error[9];

double sigmaTT_noR[10],sigmaTT_error_noR[10],sigmaTT_Q2_noR[9],sigmaTT_Q3_noR[9],sigmaTT_Q2_error_noR[9],sigmaTT_Q3_error_noR[9];
double sigmaLT_noR[10],sigmaLT_error_noR[10],sigmaLT_Q2_noR[9],sigmaLT_Q3_noR[9],sigmaLT_Q2_error_noR[9],sigmaLT_Q3_error_noR[9];

double sigmaTT_prfid[10],sigmaTT_error_prfid[10],sigmaTT_Q2_prfid[9],sigmaTT_Q3_prfid[9],sigmaTT_Q2_error_prfid[9],sigmaTT_Q3_error_prfid[9];
double sigmaLT_prfid[10],sigmaLT_error_prfid[10],sigmaLT_Q2_prfid[9],sigmaLT_Q3_prfid[9],sigmaLT_Q2_error_prfid[9],sigmaLT_Q3_error_prfid[9];

double sigmaTT_maid[10],sigmaTT_error_maid[10],sigmaTT_Q2_maid[9],sigmaTT_Q3_maid[9],sigmaTT_Q2_error_maid[9],sigmaTT_Q3_error_maid[9];
double sigmaLT_maid[10],sigmaLT_error_maid[10],sigmaLT_Q2_maid[9],sigmaLT_Q3_maid[9],sigmaLT_Q2_error_maid[9],sigmaLT_Q3_error_maid[9];

double sigmaTT5[10],sigmaTT_error5[10],sigmaTT_Q25[9],sigmaTT_Q35[9],sigmaTT_Q2_error5[9],sigmaTT_Q3_error5[9];
double sigmaLT5[10],sigmaLT_error5[10],sigmaLT_Q25[9],sigmaLT_Q35[9],sigmaLT_Q2_error5[9],sigmaLT_Q3_error5[9];
for(int i=0;i<10;i++)
{
infile10>>par0_prfid[i]>>par_error0_prfid[i]>>par1_prfid[i]>>par_error1_prfid[i]>>par2_prfid[i]>>par_error2_prfid[i];
infile4>>t5_par0[i]>>t5_par_error0[i]>>t5_par1[i]>>t5_par_error1[i]>>t5_par2[i]>>t5_par_error2[i];
infile13>>sys_sigmaL_Q1[i]>>sys_sigmaLT_Q1[i]>>sys_sigmaTT_Q1[i];
}

for(int i=0;i<9;i++){
infile11>>par_Q2_0_prfid[i]>>par_Q2_error0_prfid[i]>>par_Q2_1_prfid[i]>>par_Q2_error1_prfid[i]>>par_Q2_2_prfid[i]>>par_Q2_error2_prfid[i];
infile5>>t5_par_Q2_0[i]>>t5_par_Q2_error0[i]>>t5_par_Q2_1[i]>>t5_par_Q2_error1[i]>>t5_par_Q2_2[i]>>t5_par_Q2_error2[i];
infile12>>par_Q3_0_prfid[i]>>par_Q3_error0_prfid[i]>>par_Q3_1_prfid[i]>>par_Q3_error1_prfid[i]>>par_Q3_2_prfid[i]>>par_Q3_error2_prfid[i];;
infile6>>t5_par_Q3_0[i]>>t5_par_Q3_error0[i]>>t5_par_Q3_1[i]>>t5_par_Q3_error1[i]>>t5_par_Q3_2[i]>>t5_par_Q3_error2[i];
infile14>>sys_sigmaL_Q2[i]>>sys_sigmaLT_Q2[i]>>sys_sigmaTT_Q2[i];
infile15>>sys_sigmaL_Q3[i]>>sys_sigmaLT_Q3[i]>>sys_sigmaTT_Q3[i];
}
double dL_sum=0.0;
double dLT_sum=0.0;
double dTT_sum=0.0;
double dL_val=0.0;
double dLT_val=0.0;
double dTT_val=0.0;

double dL_sumQ2=0.0;
double dLT_sumQ2=0.0;
double dTT_sumQ2=0.0;
double dL_valQ2=0.0;
double dLT_valQ2=0.0;
double dTT_valQ2=0.0;

double dL_sumQ3=0.0;
double dLT_sumQ3=0.0;
double dTT_sumQ3=0.0;
double dL_valQ3=0.0;
double dLT_valQ3=0.0;
double dTT_valQ3=0.0;
for(int i=0;i<10;i++){
dL_val=sys_sigmaL_Q1[i];
dLT_val=sys_sigmaLT_Q1[i];
dTT_val=sys_sigmaTT_Q1[i];
dL_sum +=dL_val;
dLT_sum +=dLT_val;
dTT_sum +=dTT_val;


dL_valQ2=sys_sigmaL_Q2[i];
dLT_valQ2=sys_sigmaLT_Q2[i];
dTT_valQ2=sys_sigmaTT_Q2[i];
dL_sumQ2 +=dL_valQ2;
dLT_sumQ2 +=dLT_valQ2;
dTT_sumQ2 +=dTT_valQ2;

dL_valQ3=sys_sigmaL_Q3[i];
dLT_valQ3=sys_sigmaLT_Q3[i];
dTT_valQ3=sys_sigmaTT_Q3[i];
dL_sumQ3 +=dL_valQ3;
dLT_sumQ3 +=dLT_valQ3;
dTT_sumQ3 +=dTT_valQ3;

sigmaTT_prfid[i]=(par2_prfid[i]*kgamma)/(sintheta5_sqr[i]*epilo_Q1*mean_ppi_Q1[i]);
sigmaTT_error_prfid[i]=(par_error2_prfid[i]*kgamma)/(sintheta5_sqr[i]*epilo_Q1*mean_ppi_Q1[i]);
cout<<"par2="<<par2_prfid[i]<<"kgamma="<<kgamma<<"sintheta5_sqr="<<sintheta5_sqr[i]<<"epilo="<<epilo_Q1<<"mean_ppi="<<mean_ppi_Q1[i]<<"sigmaTT_prfid="<<sigmaTT_prfid[i]<<endl;
    
sigmaLT_prfid[i]=(par1_prfid[i]*kgamma)/(TMath::Sqrt(2*epilo_Q1*(1+epilo_Q1))*sintheta5[i]*mean_ppi_Q1[i]);
sigmaLT_error_prfid[i]=(par_error1_prfid[i]*kgamma)/(TMath::Sqrt(2*epilo_Q1*(1+epilo_Q1))*sintheta5[i]*mean_ppi_Q1[i]);
cout<<"sintheta5="<<sintheta5[i]<<"sintheta5_sqr="<<sintheta5_sqr[i]<<endl;
sigmaL_Q1[i]=par0_prfid[i]*kgamma/mean_ppi_Q1[i];
sigmaL_Q1_err[i]=par_error0_prfid[i]*kgamma/mean_ppi_Q1[i];
syserr_sigmaL_Q1[i]=sys_sigmaL_Q1[i]*TMath::Abs(sigmaL_Q1[i]);
syserr_sigmaLT_Q1[i]=sys_sigmaLT_Q1[i]*TMath::Abs(sigmaLT_prfid[i]);
syserr_sigmaTT_Q1[i]=sys_sigmaTT_Q1[i]*TMath::Abs(sigmaTT_prfid[i]);

sigmaTT5[i]=(t5_par2[i]*kgamma)/(epilo_Q1*sintheta5_sqr[i]*mean_ppi_quasi_Q1[i]);
sigmaTT_error5[i]=(t5_par_error2[i]*kgamma)/(epilo_Q1*sintheta5_sqr[i]*mean_ppi_quasi_Q1[i]);

sigmaLT5[i]=(t5_par1[i]*kgamma)/(TMath::Sqrt(2*epilo_Q1*(1+epilo_Q1))*sintheta5[i]*mean_ppi_quasi_Q1[i]);
sigmaLT_error5[i]=(t5_par_error1[i]*kgamma)/(TMath::Sqrt(2*epilo_Q1*(1+epilo_Q1))*sintheta5[i]*mean_ppi_quasi_Q1[i]);
sigmaL_quasi_Q1[i]=t5_par0[i]*kgamma/mean_ppi_Q1[i];
sigmaL_quasi_Q1_err[i]=t5_par_error0[i]*kgamma/mean_ppi_Q1[i];
    
}
double average_dL= dL_sum/10.0;
double average_dLT= dLT_sum/10.0;
double average_dTT= dTT_sum/10.0;

double average_dLQ2= dL_sumQ2/10.0;
double average_dLTQ2= dLT_sumQ2/10.0;
double average_dTTQ2= dTT_sumQ2/10.0;

double average_dLQ3= dL_sumQ3/10.0;
double average_dLTQ3= dLT_sumQ3/10.0;
double average_dTTQ3= dTT_sumQ3/10.0;
cout<<"average_dL="<<average_dL<<"average_dLT="<<average_dLT<<"average_dTT="<<average_dTT<<endl;
cout<<"average_dLQ2="<<average_dLQ2<<"average_dLTQ2="<<average_dLTQ2<<"average_dTTQ2="<<average_dTTQ2<<endl;
cout<<"average_dLQ3="<<average_dLQ3<<"average_dLTQ3="<<average_dLTQ3<<"average_dTTQ3="<<average_dTTQ3<<endl;
for(int i=0;i<9;i++){
sigmaTT_Q2_prfid[i]=(par_Q2_2_prfid[i]*kgamma)/(epilo_Q2*sintheta_sqrQ3[i]*mean_ppi_Q2[i]);
sigmaTT_Q2_error_prfid[i]=(par_Q2_error2_prfid[i]*kgamma)/(epilo_Q2*sintheta_sqrQ3[i]*mean_ppi_Q2[i]);
sigmaLT_Q2_prfid[i]=(par_Q2_1_prfid[i]*kgamma)/(TMath::Sqrt(2*epilo_Q2*(1+epilo_Q2))*sintheta_Q3[i]*mean_ppi_Q2[i]);
sigmaLT_Q2_error_prfid[i]=(par_Q2_error1_prfid[i]*kgamma)/(TMath::Sqrt(2*epilo_Q2*(1+epilo_Q2))*sintheta_Q3[i]*mean_ppi_Q2[i]);
sigmaLT_Q25[i]=t5_par_Q2_1[i]/(TMath::Sqrt(2*epilo_Q2*(1+epilo_Q1))*sintheta_Q3[i]);
sigmaLT_Q2_error5[i]=t5_par_Q2_error1[i]/(TMath::Sqrt(2*epilo_Q2*(1+epilo_Q2))*sintheta_Q3[i]);
sigmaTT_Q25[i]=(t5_par_Q2_2[i]*kgamma)/(epilo_Q2*sintheta_sqrQ3[i]*mean_ppi_quasi_Q2[i]);
sigmaTT_Q2_error5[i]=(t5_par_Q2_error2[i]*kgamma)/(epilo_Q2*sintheta_sqrQ3[i]*mean_ppi_quasi_Q2[i]);
sigmaL_quasi_Q2[i]=t5_par_Q2_0[i]*kgamma/mean_ppi_Q2[i];
sigmaL_quasi_Q2_err[i]=t5_par_Q2_error0[i]*kgamma/mean_ppi_Q2[i];
    
sigmaLT_Q3_prfid[i]=(par_Q3_1_prfid[i]*kgamma)/(TMath::Sqrt(2*epilo_Q3*(1+epilo_Q3))*sintheta_Q3[i]*mean_ppi_Q3[i]);
sigmaLT_Q3_error_prfid[i]=(par_Q3_error1_prfid[i]*kgamma)/(TMath::Sqrt(2*epilo_Q3*(1+epilo_Q3))*sintheta_Q3[i]*mean_ppi_Q3[i]);
sigmaTT_Q3_prfid[i]=(par_Q3_2_prfid[i]*kgamma)/(epilo_Q3*sintheta_sqrQ3[i]*mean_ppi_Q3[i]);
sigmaTT_Q3_error_prfid[i]=(par_Q3_error2_prfid[i]*kgamma)/(epilo_Q3*sintheta_sqrQ3[i]*mean_ppi_Q3[i]);
sigmaL_Q2[i]=par_Q2_0_prfid[i]*kgamma/mean_ppi_Q2[i];
sigmaL_Q2_err[i]=par_Q2_error0_prfid[i]*kgamma/mean_ppi_Q2[i];
syserr_sigmaL_Q2[i]=sys_sigmaL_Q2[i]*TMath::Abs(sigmaL_Q2[i]);
syserr_sigmaTT_Q2[i]=sys_sigmaTT_Q2[i]*TMath::Abs(sigmaTT_Q2_prfid[i]);
syserr_sigmaLT_Q2[i]=sys_sigmaLT_Q2[i]*TMath::Abs(sigmaLT_Q2_prfid[i]);
syserr_sigmaLT_Q3[i]=sys_sigmaLT_Q3[i]*TMath::Abs(sigmaLT_Q3_prfid[i]);
syserr_sigmaTT_Q3[i]=sys_sigmaTT_Q3[i]*TMath::Abs(sigmaTT_Q3_prfid[i]);
sigmaL_Q3[i]=par_Q3_0_prfid[i]*kgamma/mean_ppi_Q3[i];
sigmaL_Q3_err[i]=par_Q2_error0_prfid[i]*kgamma/mean_ppi_Q3[i];
    
syserr_sigmaL_Q3[i]=sys_sigmaL_Q3[i]*TMath::Abs(sigmaL_Q3[i]);
sigmaL_quasi_Q3[i]=t5_par_Q3_0[i]*kgamma/mean_ppi_Q3[i];
sigmaL_quasi_Q3_err[i]=t5_par_Q3_error0[i]*kgamma/mean_ppi_Q3[i];
sigmaTT_Q35[i]=(t5_par_Q3_2[i]*kgamma)/(epilo_Q3*sintheta_sqrQ3[i]*mean_ppi_quasi_Q3[i]);
sigmaTT_Q3_error5[i]=(t5_par_Q3_error2[i]*kgamma)/(epilo_Q3*sintheta_sqrQ3[i]*mean_ppi_quasi_Q3[i]);
sigmaLT_Q35[i]=(t5_par_Q3_1[i]*kgamma)/(TMath::Sqrt(2*epilo_Q3*(1+epilo_Q3))*sintheta_Q3[i]*mean_ppi_quasi_Q3[i]);
sigmaLT_Q3_error5[i]=(t5_par_Q3_error1[i]*kgamma)/(TMath::Sqrt(2*epilo_Q3*(1+epilo_Q3))*sintheta_Q3[i]*mean_ppi_quasi_Q3[i]);
}

cout<<"par2="<<-7.1089*epilo_Q1<<"par2[6]"<<-2.946/(TMath::Sqrt(2*epilo_Q1*(1+epilo_Q1)))<<endl;
TGraphErrors *grL_sys_Q1=new TGraphErrors(10,thetamore,syserr_sigmaL_Q1,thetamore_error,syserr_sigmaLerr);
TGraphErrors *grL_sys_Q2=new TGraphErrors(9,thetamore_Q3,syserr_sigmaL_Q2,thetamore_error_Q3,syserr_sigmaLerr);
TGraphErrors *grL_sys_Q3=new TGraphErrors(9,thetamore_Q3,syserr_sigmaL_Q3,thetamore_error_Q3,syserr_sigmaLerr_Q3);

TGraphErrors *grLT_sys_Q1=new TGraphErrors(10,thetamore,syserr_sigmaLT_Q1,thetamore_error,syserr_sigmaLerr);
TGraphErrors *grLT_sys_Q2=new TGraphErrors(9,thetamore_Q3,syserr_sigmaLT_Q2,thetamore_error_Q3,syserr_sigmaLerr);
TGraphErrors *grLT_sys_Q3=new TGraphErrors(9,thetamore_Q3,syserr_sigmaLT_Q3,thetamore_error_Q3,syserr_sigmaLerr_Q3);

TGraphErrors *grTT_sys_Q1=new TGraphErrors(10,thetamore,syserr_sigmaTT_Q1,thetamore_error,syserr_sigmaLerr);
TGraphErrors *grTT_sys_Q2=new TGraphErrors(9,thetamore_Q3,syserr_sigmaTT_Q2,thetamore_error_Q3,syserr_sigmaLerr);
TGraphErrors *grTT_sys_Q3=new TGraphErrors(9,thetamore_Q3,syserr_sigmaTT_Q3,thetamore_error_Q3,syserr_sigmaLerr_Q3);


TGraphErrors *gr0_prfid=new TGraphErrors(10,theta,sigmaL_Q1,theta_error,sigmaL_Q1_err);
TGraphErrors *gr0_Q2_prfid=new TGraphErrors(9,theta_Q3,sigmaL_Q2,theta_error_Q3,sigmaL_Q2_err);
TGraphErrors *gr0_Q3_prfid=new TGraphErrors(9,theta_Q3,sigmaL_Q3,theta_error_Q3,sigmaL_Q1_err);

TGraphErrors *gr5=new TGraphErrors(10,theta5,sigmaL_quasi_Q1,theta5_error,sigmaL_quasi_Q1_err);
TGraphErrors *gr5_Q2=new TGraphErrors(9,theta5_Q3,sigmaL_quasi_Q2,theta5_error_Q3,sigmaL_quasi_Q2_err);
TGraphErrors *gr5_Q3=new TGraphErrors(9,theta5_Q3,sigmaL_quasi_Q3,theta5_error_Q3,sigmaL_quasi_Q3_err);


TGraphErrors *gr1_prfid=new TGraphErrors(10,theta,sigmaTT_prfid,theta_error,sigmaTT_error_prfid);
TGraphErrors *gr1_Q2_prfid=new TGraphErrors(9,theta_Q3,sigmaTT_Q2_prfid,theta_error_Q3,sigmaTT_Q2_error_prfid);
TGraphErrors *gr1_Q3_prfid=new TGraphErrors(9,theta_Q3,sigmaTT_Q3_prfid,theta_error_Q3,sigmaTT_Q3_error_prfid);

//gr1_maid->Print();

TGraphErrors *gr6=new TGraphErrors(10,theta5,sigmaTT5,theta5_error,sigmaTT_error5);
TGraphErrors *gr6_Q2=new TGraphErrors(9,theta5_Q3,sigmaTT_Q25,theta5_error_Q3,sigmaTT_Q2_error5);
TGraphErrors *gr6_Q3=new TGraphErrors(9,theta5_Q3,sigmaTT_Q35,theta5_error_Q3,sigmaTT_Q3_error5);

TGraphErrors *gr2_prfid=new TGraphErrors(10,thetamore,sigmaLT_prfid,thetamore_error,sigmaLT_error_prfid);
TGraphErrors *gr2_Q2_prfid=new TGraphErrors(9,thetamore_Q3,sigmaLT_Q2_prfid,thetamore_error_Q3,sigmaLT_Q2_error_prfid);
TGraphErrors *gr2_Q3_prfid=new TGraphErrors(9,thetamore_Q3,sigmaLT_Q3_prfid,thetamore_error_Q3,sigmaLT_Q3_error_prfid);

TGraphErrors *gr7=new TGraphErrors(10,theta5,sigmaLT5,theta5_error,sigmaLT_error5);
TGraphErrors *gr7_Q2=new TGraphErrors(9,theta5_Q3,sigmaLT_Q25,theta5_error_Q3,sigmaLT_Q2_error5);
TGraphErrors *gr7_Q3=new TGraphErrors(9,theta5_Q3,sigmaLT_Q35,theta5_error_Q3,sigmaLT_Q3_error5);
gr1_prfid->Print();
    
int a=0;
for(int k=0;k<10;k++){

  if(t5_par0[k]==0){
   //cout<<"gr0->RemovePoint("<<j<<");"<<endl;
   gr5->RemovePoint(k-a);
   gr0_prfid->RemovePoint(k-a);
   grL_sys_Q1->RemovePoint(k-a);
   gr6->RemovePoint(k-a);
   gr1_prfid->RemovePoint(k-a);
   grTT_sys_Q1->RemovePoint(k-a);
   gr7->RemovePoint(k-a);
   gr2_prfid->RemovePoint(k-a);
   grLT_sys_Q1->RemovePoint(k-a);
   a=a+1;
   }
}

int b=0;
int d=0;
for(int k=0;k<9;k++){
  if(t5_par_Q2_0[k]==0 ){
   //cout<<"gr0->RemovePoint("<<j<<");"<<endl;
   gr5_Q2->RemovePoint(k-b);
   gr0_Q2_prfid->RemovePoint(k-b);
   grL_sys_Q2->RemovePoint(k-b);
   gr6_Q2->RemovePoint(k-b);
   gr1_Q2_prfid->RemovePoint(k-b);
   grTT_sys_Q2->RemovePoint(k-b);
   gr7_Q2->RemovePoint(k-b);
   gr2_Q2_prfid->RemovePoint(k-b);
   grLT_sys_Q2->RemovePoint(k-b);
   b=b+1;
   }
  if(t5_par_Q3_0[k]==0){
   //cout<<"gr0->RemovePoint("<<j<<");"<<endl;
   gr5_Q3->RemovePoint(k-d);
   gr0_Q3_prfid->RemovePoint(k-d);
   grL_sys_Q3->RemovePoint(k-d);
   gr6_Q3->RemovePoint(k-d);
   gr1_Q3_prfid->RemovePoint(k-d);
   grTT_sys_Q3->RemovePoint(k-d);
   gr7_Q3->RemovePoint(k-d);
   gr2_Q3_prfid->RemovePoint(k-d);
   grLT_sys_Q3->RemovePoint(k-d);
   d=d+1;
   }
}

func0 = new TF1("func0","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)",-0.9,0.9);
func3 = new TF1("func3","[0]+[1]*x+[2]*0.5*(3*x*x-1)",-0.9,0.9);
func2 = new TF1("func2","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)",-0.9,0.9);
func = new TF1("func","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)+[5]*(1.0/8.0)*(63*x*x*x*x*x-70*x*x*x+15*x)+[6]*(1.0/16.0)*(231*x*x*x*x*x*x-315*x*x*x*x+105*x*x-5)",-0.9,0.9);
//func4 = new TF1("func4","[0]",-0.9,0.9);
func4 = new TF1("func4","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)",-0.9,0.9);
//func5 = new TF1("func5","[0]+[1]*x",-0.9,0.9);
func5 = new TF1("func5","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)+[5]*(1.0/8.0)*(63*x*x*x*x*x-70*x*x*x+15*x)",-0.9,0.9);
func6 = new TF1("func6","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)",-0.9,0.9);
func7 = new TF1("func7","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)+[5]*(1.0/8.0)*(63*x*x*x*x*x-70*x*x*x+15*x)",-0.9,0.9);
func8 = new TF1("func8","[0]+[1]*x+[2]*0.5*(3*x*x-1)",-0.9,0.9);
func9 = new TF1("func9","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)",-0.9,0.9);
func10 = new TF1("func10","[0]+[1]*x+[2]*0.5*(3*x*x-1)",-0.9,0.9);
func11 = new TF1("func11","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)",-0.9,0.9);
func12 = new TF1("func12","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)",-0.9,0.9);
func13 = new TF1("func13","[0]+[1]*x+[2]*0.5*(3*x*x-1)",-0.9,0.9);
func14 = new TF1("func14","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)",-0.9,0.9);
func15 = new TF1("func15","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)",-0.9,0.9);
func16 = new TF1("func16","[0]+[1]*x+[2]*0.5*(3*x*x-1)",-0.9,0.9);
func17 = new TF1("func17","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)",-0.9,0.9);
//func24 = new TF1("func24","[0]",-0.9,0.9); //l=1 sigmaTT
func25 = new TF1("func25","[0]+[1]*x",-0.9,0.9); //l=2 sigmatL
//func20 = new TF1("func20","[0]+[1]*x+[2]*0.5*(3*x*x-1)",-0.9,0.9); //l=1 sigmaT+sigmaL
func20 = new TF1("func20","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)+[5]*(1.0/8.0)*(63*x*x*x*x*x-70*x*x*x+15*x)+[6]*(1.0/16.0)*(231*x*x*x*x*x*x-315*x*x*x*x+105*x*x-5)",-0.9,0.9);
func24 = new TF1("func24","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)",-0.9,0.9);
func25 = new TF1("func25","[0]+[1]*x+[2]*0.5*(3*x*x-1)+[3]*0.5*(5*x*x*x-3*x)+[4]*(1.0/8.0)*(35*x*x*x*x-30*x*x+3)+[5]*(1.0/8.0)*(63*x*x*x*x*x-70*x*x*x+15*x)",-0.9,0.9);
    
    
func->SetLineColor(1);
func2->SetLineColor(2);
func3->SetLineColor(7);
func4->SetLineColor(1);
func8->SetLineColor(2);

func9->SetLineColor(1);
func5->SetLineColor(1);
    func->SetLineStyle(7);
    func5->SetLineStyle(7);
    func4->SetLineStyle(7);
    func6->SetLineColor(2);
func7->SetLineColor(7);
func0->SetLineColor(7);
func10->SetLineColor(kGreen+1);
func11->SetLineColor(kGreen+1);
func12->SetLineColor(kGreen+1);
//func10->SetLineStyle(7);
//func11->SetLineStyle(7);
//func12->SetLineStyle(7);
func13->SetLineColor(1);;
func14->SetLineColor(1);
func15->SetLineColor(1);
func16->SetLineColor(1);
func17->SetLineColor(1);

func20->SetLineColor(kGreen+1);
func25->SetLineColor(kGreen+1);
func24->SetLineColor(kGreen+1);
func20->SetLineStyle(7);
func25->SetLineStyle(7);
func24->SetLineStyle(7);
    
TCanvas *c=new TCanvas("c","c",1200,900);
c->Divide(1,3);
 //Wbin5, Q1, sigmaL+EsigmaT
c->cd(1);
gr0_prfid->GetXaxis()->SetTitle("cos#theta");
gr0_prfid->GetYaxis()->SetTitle("#sigma_{T}+#epsilon#sigma_{L}");
//gr0_prfid->RemovePoint(0);
gr0_prfid->SetMarkerStyle(20);
gr0_prfid->SetMarkerSize(1.4);
gr0_prfid->SetMarkerColor(1);
gr0_prfid->Fit("func15","R+");//l=2
gr0_prfid->Fit("func","R+");
gr0_prfid->Draw("Ap");
//gr5->RemovePoint(0);
gr5->SetMarkerStyle(21);
gr5->SetMarkerSize(1.4);
gr5->SetMarkerColor(kGreen+1);
gr5->Fit("func11","R+");//l=2
gr5->Fit("func20","R+");
gr5->Draw(" same p");
grL_sys_Q1->RemovePoint(0);
grL_sys_Q1->Draw("sameB1");
parA=func15->GetParameters();
parA_error=func15->GetParErrors();
parA_quasi=func11->GetParameters();
parA_quasi_error=func11->GetParErrors();
parA_l3=func->GetParameters();
parA_l3_error=func->GetParErrors();
parA_l3_quasi=func20->GetParameters();
parA_l3_quasi_error=func20->GetParErrors();
    
outfile1<<setw(20)<<setiosflags(ios::left)<<val_W<<setw(20)<<setiosflags(ios::left)<<sigmaL_Q1[cot]
<<setw(20)<<setiosflags(ios::left)<<sigmaL_Q1_err[cot]<<setw(20)<<setiosflags(ios::left)<<syserr_sigmaL_Q1[cot]<<endl;

outfile4<<setw(20)<<setiosflags(ios::left)<<val_W<<setw(20)<<setiosflags(ios::left)<<sigmaL_quasi_Q1[cot]
<<setw(20)<<setiosflags(ios::left)<<sigmaL_quasi_Q1_err[cot]<<setw(20)<<setiosflags(ios::left)<<syserr_sigmaL_Q1[cot]<<endl;
//Wbin5, Q2, sigmaL+EsigmaT
/*c->cd(2);
gr0_Q2_prfid->SetMarkerStyle(20);
gr0_Q2_prfid->SetMarkerSize(1.4);
gr0_Q2_prfid->SetMarkerColor(1);
gr0_Q2_prfid->Fit("func15","R+");
gr0_Q2_prfid->Fit("func","R+");
gr0_Q2_prfid->Draw("Ap");
    
gr5_Q2->SetMarkerStyle(21);
gr5_Q2->SetMarkerSize(1.4);
gr5_Q2->SetMarkerColor(kGreen+1);
gr5_Q2->Draw(" same p");
gr5_Q2->Fit("func11","R+");
gr5_Q2->Fit("func20","R+");
grL_sys_Q2->Draw("sameB1");

//Wbin5, Q3, sigmaL+EsigmaT
c->cd(3);
gr0_Q3_prfid->SetMarkerStyle(20);
gr0_Q3_prfid->SetMarkerSize(1.4);
gr0_Q3_prfid->SetMarkerColor(1);
gr0_Q3_prfid->Fit("func15","R+");
gr0_Q3_prfid->Fit("func","R+");
gr0_Q3_prfid->Draw("Ap");
gr5_Q3->SetMarkerStyle(21);
gr5_Q3->SetMarkerSize(1.4);
gr5_Q3->SetMarkerColor(kGreen+1);
gr5_Q3->Draw("same p");
gr5_Q3->Fit("func11","R+");
gr5_Q2->Fit("func20","R+");
grL_sys_Q3->Draw("sameB1");

  TLegend *leg1 = new TLegend(0.6,0.4,0.8,0.8);

  leg1->AddEntry(gr0_Q3_prfid,"exclusive","p");
  leg1->AddEntry(gr5_Q3,"quasi-free ","p");

   leg1->AddEntry(func15,"l=2","l"); 
  //leg1->AddEntry(func9,"l=2","l");
  leg1->AddEntry(func11,"l=2","l");
  leg1->AddEntry(func,"l=1","l");
  leg1->AddEntry(func20,"l=1","l");
    
  leg1->SetTextSize(0.05);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->Draw("text same");*/
    
//Wbin5, Q1, sigmaTT
c->cd(2);
gr1_prfid->GetYaxis()->SetTitle("#sigma_{TT}");
gr1_prfid->GetXaxis()->SetTitle("cos#theta");
//gr1_prfid->RemovePoint(0);
gr1_prfid->SetMarkerStyle(20);
gr1_prfid->SetMarkerSize(1.4);
gr1_prfid->SetMarkerColor(1);
gr1_prfid->Fit("func16","R+");//l=2
gr1_prfid->Fit("func4","R+");
gr1_prfid->Draw("Ap");
//gr6->RemovePoint(0);
gr6->SetMarkerStyle(21);
gr6->SetMarkerSize(1.4);
gr6->SetMarkerColor(kGreen+1);
gr6->Fit("func10","R");//l=2
gr6->Fit("func24","R+");
gr6->Draw("same p");
grTT_sys_Q1->RemovePoint(0);
grTT_sys_Q1->Draw("sameB");
    parB=func16->GetParameters();
    parB_error=func16->GetParErrors();
    parB_quasi=func10->GetParameters();
    parB_quasi_error=func10->GetParErrors();
    parB_l3=func4->GetParameters();
    parB_l3_error=func4->GetParErrors();
    parB_l3_quasi=func24->GetParameters();
    parB_l3_quasi_error=func24->GetParErrors();
    
outfile2<<setw(20)<<setiosflags(ios::left)<<val_W<<setw(20)<<setiosflags(ios::left)<<sigmaTT_prfid[cot]
<<setw(20)<<setiosflags(ios::left)<<sigmaTT_error_prfid[cot]<<setw(20)<<setiosflags(ios::left)<<syserr_sigmaTT_Q1[cot]<<endl;
    
outfile5<<setw(20)<<setiosflags(ios::left)<<val_W<<setw(20)<<setiosflags(ios::left)<<sigmaTT5[cot]
<<setw(20)<<setiosflags(ios::left)<<sigmaTT_error5[cot]<<setw(20)<<setiosflags(ios::left)<<syserr_sigmaTT_Q1[cot]<<endl;

    
//Wbin5, Q2, sigmaTT
/*c->cd(5);
gr1_Q2_prfid->SetMarkerStyle(20);
gr1_Q2_prfid->SetMarkerSize(1.4);
gr1_Q2_prfid->SetMarkerColor(1);
gr1_Q2_prfid->Fit("func16","R+");
gr1_Q2_prfid->Fit("func4","R+");
gr1_Q2_prfid->Draw("Ap");

gr6_Q2->SetMarkerStyle(21);
gr6_Q2->SetMarkerSize(1.4);
gr6_Q2->SetMarkerColor(kGreen+1);
gr6_Q2->Fit("func10","R+");
gr6_Q2->Fit("func24","R+");
gr6_Q2->Draw("same p");
grTT_sys_Q2->Draw("sameB");

    
//Wbin5, Q3, sigmaTT
c->cd(6);

gr1_Q3_prfid->SetMarkerStyle(20);
gr1_Q3_prfid->SetMarkerSize(1.4);
gr1_Q3_prfid->SetMarkerColor(1);
gr1_Q3_prfid->Fit("func16","R+");
gr1_Q3_prfid->Fit("func4","R+");
gr1_Q3_prfid->Draw("Ap");
gr6_Q3->SetMarkerStyle(21);
gr6_Q3->SetMarkerSize(1.4);
gr6_Q3->SetMarkerColor(kGreen+1);
gr6_Q3->Fit("func10","R+");
gr6_Q3->Fit("func24","R+");
gr6_Q3->Draw("same p");
grTT_sys_Q3->Draw("sameB");*/
//Wbin5, Q1, sigmaTL
c->cd(3);
gr2_prfid->GetYaxis()->SetTitle("#sigma_{LT}");
gr2_prfid->GetXaxis()->SetTitle("cos#theta");
//gr2_prfid->RemovePoint(0);
gr2_prfid->SetMarkerStyle(20);
gr2_prfid->SetMarkerSize(1.4);
gr2_prfid->SetMarkerColor(1);
gr2_prfid->Fit("func17","R");//l=2
gr2_prfid->Fit("func5","R+");
gr2_prfid->Draw("Ap");
//gr7->RemovePoint(0);
gr7->SetMarkerStyle(21);
gr7->SetMarkerSize(1.4);
gr7->SetMarkerColor(kGreen+1);
gr7->Fit("func12","R+");//l=2
gr7->Draw("same p");
gr7->Fit("func25","R+");

grLT_sys_Q1->RemovePoint(0);
grLT_sys_Q1->Draw("sameB");
parC=func17->GetParameters();
parC_error=func17->GetParErrors();
parC_quasi=func12->GetParameters();
parC_quasi_error=func12->GetParErrors();
parC_l3=func5->GetParameters();
parC_l3_error=func5->GetParErrors();
parC_l3_quasi=func25->GetParameters();
parC_l3_quasi_error=func25->GetParErrors();
    
outfile3<<setw(20)<<setiosflags(ios::left)<<val_W<<setw(20)<<setiosflags(ios::left)<<sigmaLT_prfid[cot]
<<setw(20)<<setiosflags(ios::left)<<sigmaLT_error_prfid[cot]<<setw(20)<<setiosflags(ios::left)<<syserr_sigmaLT_Q1[cot]<<endl;
    
outfile6<<setw(20)<<setiosflags(ios::left)<<val_W<<setw(20)<<setiosflags(ios::left)<<sigmaLT5[cot]
<<setw(20)<<setiosflags(ios::left)<<sigmaLT_error5[cot]<<setw(20)<<setiosflags(ios::left)<<syserr_sigmaLT_Q1[cot]<<endl;

    //gr_test4->Draw("same p");
    
//Wbin5, Q2, sigmaTT
/*c->cd(8);
gr2_Q2_prfid->SetMarkerStyle(20);
gr2_Q2_prfid->SetMarkerSize(1.4);
gr2_Q2_prfid->SetMarkerColor(1);
gr2_Q2_prfid->Fit("func17","R");
gr2_Q2_prfid->Fit("func5","R+");
gr2_Q2_prfid->Draw("Ap");
gr7_Q2->SetMarkerStyle(21);
gr7_Q2->SetMarkerSize(1.4);
gr7_Q2->SetMarkerColor(kGreen+1);
gr7_Q2->Fit("func12","R+");
gr7_Q2->Draw("same p");
gr7_Q2->Fit("func25","R+");
grLT_sys_Q2->Draw("sameB");
    
//Wbin5, Q3, sigmaTL
    
c->cd(9);
gr2_Q3_prfid->SetMarkerStyle(20);
gr2_Q3_prfid->SetMarkerSize(1.4);
gr2_Q3_prfid->SetMarkerColor(1);
gr2_Q3_prfid->Fit("func17","R");
gr2_Q3_prfid->Fit("func5","R+");
gr2_Q3_prfid->Draw(" Ap");
gr7_Q3->SetMarkerStyle(21);
gr7_Q3->SetMarkerSize(1.4);
gr7_Q3->SetMarkerColor(kGreen+1);
gr7_Q3->Fit("func12","R+");
gr7_Q3->Draw("same p");
gr7_Q3->Fit("func25","R+");

grLT_sys_Q3->Draw("sameB");*/

//gr0->Fit(func,"R");

}
