#include <iostream> 
#include <fstream>
#include <cmath> 
#include "math.h" 
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMinuit.h"
#include "TPaveText.h"
#include "TText.h"
#include "TSystem.h"
#include "TArc.h"
#include "TString.h"
#include <vector>
#include "TRandom3.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TFile.h"
#include "TLatex.h"
#include "TLegend.h"

using namespace std;

#include "analysis_tree_solid_hgc.C"
#include "analysis_tree_solid_ec.C"
#include "analysis_tree_solid_spdsurvey.C"
#include "analysis_tree_solid_gemsurvey.C"

// some numbers to be hard coded 
// make sure they are correct while using this script
//################################################################################################################################################## 
// const double filenum=50; //file numbers while running GEMC in order to be correct for normalization
const int loop_time=1;   //electron to be 1, pion to be many times to take advantage of statistics, pion has low efficiency on EC
const int add_norm=1; // additional normalization factor

//distance between two ec cluster to have coincidance trigger
// const double threshold_distance=0;
// const double threshold_distance=0.1;
const double threshold_distance=32.5; 

const int with_background_on_lgc=0;     //0: no background on lgc, 1: yes background on lgc

//trigger threshold
// lgc 
const double PEthresh_lgc=2; //lgc pe threshold for each pmt
const double PMTthresh_lgc=2; //lgc pmt threshold, at least 2pmts are fired in each sector

// hgc 
// const double PEthresh_hgc=2; //hgc pe threshold for each pmt
// const double PMTthresh_hgc=2; //hgc pmt threshold, at least 2pmts are fired in each sector
const double PEthresh_hgc=1; //hgc pe threshold for each pmt
const double PMTthresh_hgc=2; //hgc pmt threshold, at least 2pmts are fired in each sector

//spd 
// const double trigger_threshold_spd_FA=0.35;         //in MeV
const double trigger_threshold_spd_FA=0.5;         //in MeV
const double trigger_threshold_spd_LA=1.5;         //in MeV
//mrpc threshold
const double mrpc_block_threshold_FA=5;  //how many layers are required to be fired

//occupancy threshold
double occ_threshold_lgc=0,occ_threshold_hgc=0; //in N_p.e.
double occ_threshold_spd_FA=trigger_threshold_spd_FA/5.,occ_threshold_spd_LA=trigger_threshold_spd_LA/5.; //in MeV
double occ_threshold_ec_preshower=0.4,occ_threshold_ec_shower=6; //in MeV

// double occ_threshold_lgc=1,occ_threshold_hgc=1; //in N_p.e.
// // double occ_threshold_spd_FA=trigger_threshold_spd_FA/2.,occ_threshold_spd_LA=trigger_threshold_spd_LA/2.; //in MeV
// double occ_threshold_spd_FA=0.5,occ_threshold_spd_LA=3.; 
// double occ_threshold_ec_preshower=0.8,occ_threshold_ec_shower=12; //in MeV

//EC radius cut for physics result
double rout_cut_FA_phys=220;
double rin_cut_FA_phys=105;
double rout_cut_LA_phys=127;
double rin_cut_LA_phys=83; 
//EC radius cut for trigger
double rout_cut_FA_trigger=235;
double rin_cut_FA_trigger=105;
double rout_cut_LA_trigger=140; 
double rin_cut_LA_trigger=80;

bool Is_debug=false;

const double DEG=180./3.1415926;   //rad to degree

//#####################################################################################################################################################

int analysis_gem_survey_difftheta_tid1_eAll(string inputfile_name,string runmode="trigger",bool Is_new=true){

	// gStyle->SetOptStat(11111111);
	gStyle->SetOptStat("ioue");
	// gStyle->SetOptStat(0);

	gStyle->SetPalette(1);

	Bool_t Fillecal=kFALSE;  
	Bool_t Fillgem=kFALSE;  
	double rout_cut_FA=0,rin_cut_FA=0,rout_cut_LA=0,rin_cut_LA=0;
	if (runmode=="phys"){
		cout << "runmode: phys" << endl;  
		rout_cut_FA=rout_cut_FA_phys;
		rin_cut_FA=rin_cut_FA_phys;
		rout_cut_LA=rout_cut_LA_phys;
		rin_cut_LA=rin_cut_LA_phys;   
	}else if(runmode=="trigger"){
		cout << "runmode: trigger" << endl;
		rout_cut_FA=rout_cut_FA_trigger;
		rin_cut_FA=rin_cut_FA_trigger;
		rout_cut_LA=rout_cut_LA_trigger;
		rin_cut_LA=rin_cut_LA_trigger;   
	}
	else {cout << "need to know runmode: phys or trigger" << endl; return 0;}

	bool Is_singlefile=false;
	bool Is_pi0=false;
	string filemode;
	double event_actual=1;
	if (inputfile_name.find("BeamOnTargetEM",0) != string::npos) {
		filemode="BeamOnTargetEM";
		cout << "this is a BeamOnTargetEM file" << endl;  

		event_actual=atof(inputfile_name.substr(inputfile_name.find("BeamOnTargetEM",0)+15,inputfile_name.find("_")).c_str());
		cout << "event_actual " << event_actual <<  endl;  
	}
	else if (inputfile_name.find("BeamOnTarget",0) != string::npos) {
		filemode="BeamOnTarget";
		cout << "this is a BeamOnTarget file" << endl;  

		event_actual=atof(inputfile_name.substr(inputfile_name.find("BeamOnTarget",0)+13,inputfile_name.find("_")).c_str());
		cout << "event_actual " << event_actual <<  endl;  
	}
	else if (inputfile_name.find("even",0) != string::npos) {
		filemode="even";
		cout << "this is a evenly distributed file" << endl;  
	}
	else {
		filemode="rate";  
		cout << "this is rate dependent file" << endl;  
	}

	if (event_actual<1) {cout << "wrong event_actual" << endl; return 0;}

	double filenum=1;
	if (inputfile_name.find("_filenum",0) != string::npos) {
		filenum=atof(inputfile_name.substr(inputfile_name.find("_filenum")+8,inputfile_name.find("_")).c_str());
		cout << "filenum " << filenum << " for addtional normalization, YOU Need to Make Sure It's CORRECT!" <<  endl;
	}
	else {
		if (filemode=="rate"){
			cout << "this file is rate dependent, but has no filenum, something is wrong" << endl;  
			return 0;
		}
		else{
			cout << "this file has no filenum, please check if you need filenum for addtional normalization" << endl;      
		}
	}

	// bool Is_He3=false,Is_C=false,Is_NOtarget=false;
	// if(inputfile_name.find("_He3_",0) != string::npos) {
	//   Is_He3=true;
	//   cout << "He3 setup" << endl;  
	// }
	// else if(inputfile_name.find("_C_",0) != string::npos) {
	//   Is_C=true;
	//   cout << "C setup" << endl;  
	// }
	// else if(inputfile_name.find("_NOtarget",0) != string::npos) {
	//   Is_NOtarget=true;
	//   cout << "NOtarget setup" << endl;  
	// }
	// else {
	//     cout << "Not He3 or C or NOtarget" << endl;    
	//     return 0;
	// }

	//Cherenkov sensor for 30 sectors
	const int ch_lgc=270;
	// const int ch_hgc=480;    	//pmt readout
	// const int ch_hgc=1920;	//quad readout
	const int ch_hgc=16;	//quad readout
	// const int ch_hgc=30720;		//pixel readout

	const int sensor_hgc = 16;
	const int sensor_trans_hgc = sqrt(sensor_hgc);		

	Float_t npe_lgc[ch_lgc],npe_hgc[ch_hgc];
	Float_t npe_lgc_total=0,npe_lgc_total_trigged=0;
	Float_t npe_hgc_total=0,npe_hgc_total_trigged=0;

	// char mlpfile_lgc_name[200];
	// sprintf(mlpfile_lgc_name, "%s_mlp_lgc.root",inputfile_name.substr(0,inputfile_name.rfind(".")).c_str());
	// TFile *mlpfile_lgc=new TFile(mlpfile_lgc_name, "recreate");
	// TTree *mlptree_lgc = new TTree("lgc", "npe");
	// for(int i=0;i<ch_lgc;i++) mlptree_lgc->Branch(Form("npe_lgc%i",i), &npe_lgc[i], Form("npe_lgc%i/F",i));
	// mlptree_lgc->Branch("npe_lgc_total", &npe_lgc_total, "npe_lgc_total/F");
	// 
	// char mlpfile_hgc_name[200];
	// sprintf(mlpfile_hgc_name, "%s_mlp_hgc.root",inputfile_name.substr(0,inputfile_name.rfind(".")).c_str());
	// TFile *mlpfile_hgc=new TFile(mlpfile_hgc_name, "recreate");
	// TTree *mlptree_hgc = new TTree("hgc", "npe");
	// for(int i=0;i<ch_hgc;i++) mlptree_hgc->Branch(Form("npe_hgc%i",i), &npe_hgc[i], Form("npe_hgc%i/F",i));
	// mlptree_hgc->Branch("npe_hgc_total", &npe_hgc_total, "npe_hgc_total/F");

	TFile *file=new TFile(inputfile_name.c_str());

	// 	TString background_inputfile_name="parametrized_lgc.root";      //h_pe is here	
	// 	TFile *background_file=new TFile(background_inputfile_name);
	// 	TH1F *h_pe=(TH1F*)background_file->Get("h_pe");

	std::size_t found = inputfile_name.rfind("cache");
	if (found!=std::string::npos)  inputfile_name.replace(found,5,"work");

	char the_filename[500];
	sprintf(the_filename, "%s",inputfile_name.substr(0,inputfile_name.rfind(".")).c_str());

	char outputfile_name[200];
	//sprintf(outputfile_name, "LD2_pim_output.root",the_filename);
	sprintf(outputfile_name, "%s_output_preshower_difftheta_rate_tid1_EL5GeV_finerbin_more.root",the_filename);
	TFile *outputfile=new TFile(outputfile_name, "recreate");
	//TFile *outputfile=new TFile("LD2_eAll_output.root", "recreate");

	// prepare for outputs
	// define histograms, output txt files etc...

	// 	TH1F *hpe_hgc=new TH1F("pe_hgc","pe;sensor;",sensor_hgc,0,sensor_hgc);
	// 	TH1F *hhit_hgc=new TH1F("hit_hgc","hit;sensor;N_{p.e.} rate(Hz)",sensor_hgc,0,sensor_hgc);
	// 	TH1F *hocc_hgc=new TH1F("occ_hgc","occupancy;sensor;rate(Hz)",sensor_hgc,0,sensor_hgc);
	// 	
	// 	TH2F *hpe_hgc_2D=new TH2F("pe_hgc_2D","pe;sensor_lx;sensor_ly",sensor_trans_hgc,0,sensor_trans_hgc,sensor_trans_hgc,0,sensor_trans_hgc);	
	// 	TH2F *hhit_hgc_2D=new TH2F("hit_hgc_2D","hit,N_{p.e.} rate(Hz);sensor_lx;sensor_ly",sensor_trans_hgc,0,sensor_trans_hgc,sensor_trans_hgc,0,sensor_trans_hgc);
	// 	TH2F *hocc_hgc_2D=new TH2F("occ_hgc_2D","occupancy,rate(Hz);sensor_lx;sensor_ly",sensor_trans_hgc,0,sensor_trans_hgc,sensor_trans_hgc,0,sensor_trans_hgc);

	TH1F *hpe_hgc[4],*hhit_hgc[4],*hocc_hgc[4];
	TH2F *hpe_hgc_2D[4],*hhit_hgc_2D[4],*hocc_hgc_2D[4];	
	for(int i=0;i<4;i++){
		char hstname[200]; 	  
		sprintf(hstname,"pe_hgc_%i",i);	  
		hpe_hgc[i]=new TH1F(hstname,"N_{p.e.};sensor;",sensor_hgc,0,sensor_hgc);
		sprintf(hstname,"hit_hgc_%i",i);	  
		hhit_hgc[i]=new TH1F(hstname,"N_{p.e.}*rate(Hz);sensor;N_{p.e.} rate(Hz)",sensor_hgc,0,sensor_hgc);
		sprintf(hstname,"occ_hgc_%i",i);	  
		hocc_hgc[i]=new TH1F(hstname,"rate(Hz);sensor; rate(Hz)",sensor_hgc,0,sensor_hgc);

		sprintf(hstname,"pe_hgc_2D_%i",i);	  	  
		hpe_hgc_2D[i]=new TH2F(hstname,"N_{p.e.};sensor_lx;sensor_ly",sensor_trans_hgc,0,sensor_trans_hgc,sensor_trans_hgc,0,sensor_trans_hgc);	
		sprintf(hstname,"hit_hgc_2D_%i",i);	  	  
		hhit_hgc_2D[i]=new TH2F(hstname,"N_{p.e.}*rate(Hz);sensor_lx;sensor_ly",sensor_trans_hgc,0,sensor_trans_hgc,sensor_trans_hgc,0,sensor_trans_hgc);
		sprintf(hstname,"occ_hgc_2D_%i",i);	  	  
		hocc_hgc_2D[i]=new TH2F(hstname,"rate(Hz);sensor_lx;sensor_ly",sensor_trans_hgc,0,sensor_trans_hgc,sensor_trans_hgc,0,sensor_trans_hgc);
	}

	// 	TH1F *htime_photon[2];
	// 	htime_photon[0]=new TH1F("time_photon_0","time",400,0,1000);
	// 	htime_photon[1]=new TH1F("time_photon_1","time",400,0,1000);	
	TH1F *htime_photon=new TH1F("time_photon","time_photon;t (ns)",100,0,100);

	TH1F *hmotherP=new TH1F("motherP","mother particle rate (Hz);P (GeV);",5500,0,11);

	TH1F *hmother_procid=new TH1F("mother_procid","mother_procid",150,-0.5,149.5);

	TH1F *hmother_tid=new TH1F("mother_tid","mother_tid",100,0,100);	
	TH1F *hmother_pid=new TH1F("mother_pid","mother_pid",200,-100,100);
	TH1F *hmother_vz=new TH1F("mother_vz","mother particle rate (Hz);vz (cm);",1300,-100,1200);	
	TH2F *hmother_vzvx=new TH2F("mother_vzvx","mother particle rate (Hz);vz (cm); vx (cm)",1300,-100,1200,1000,-20,20);		

	TH1F *hgrandma_tid=new TH1F("grandma_tid","grandma_tid",100,0,100);	
	TH1F *hgrandma_pid=new TH1F("grandma_pid","grandma_pid",200,-100,100);
	TH1F *hgrandma_vz=new TH1F("grandma_vz","grandma particle rate (Hz);vz (cm);",1300,-100,1200);	
	TH2F *hgrandma_vzvx=new TH2F("grandma_vzvx","grandma particle rate (Hz);vz (cm); vx (cm)",1300,-100,1200,1000,-20,20);	


	TH1F *hnpe_hgc_count[2],*hnpe_hgc[2];
	TH1F *hnpe_sensor_hgc_count[2][sensor_hgc],*hnpe_sensor_hgc[2][sensor_hgc];		
	TH2F *hnpe_nsensor_hgc_count[2],*hnpe_nsensor_hgc[2];	
	for(int j=0;j<2;j++){	
		hnpe_hgc_count[j]=new TH1F(Form("npe_hgc_count_%i",j),";Npe;count",100,0,100);		
		hnpe_hgc[j]=new TH1F(Form("npe_hgc_%i",j),";Npe;rate(Hz)",100,0,100);
		hnpe_nsensor_hgc_count[j]=new TH2F(Form("npe_nsensor_hgc_count_%i",j),";Npe;Nsensor",100,0,100,sensor_hgc+1,-0.5,sensor_hgc+0.5);
		hnpe_nsensor_hgc[j]=new TH2F(Form("npe_nsensor_hgc_%i",j),";Npe;Nsensor",100,0,100,sensor_hgc,0.5,sensor_hgc+0.5);
		for(int i=0;i<sensor_hgc;i++){	
			hnpe_sensor_hgc_count[j][i]=new TH1F(Form("npe_sensor_hgc_count_%i_%i",j,i),";Npe;count",30,0,30);		
			hnpe_sensor_hgc[j][i]=new TH1F(Form("npe_sensor_hgc_%i_%i",j,i),";Npe;rate(Hz)",30,0,30);
		}	  
	}

	TH1F *hnpe_hgc_cut[sensor_hgc][2];
	for(int i=0;i<sensor_hgc;i++){
		for(int j=0;j<2;j++){	
			char hstname[200]; 
			sprintf(hstname,"npe_hgc_cut_%i_%i",i,j);
			hnpe_hgc_cut[i][j]=new TH1F(hstname,";Npe;rate(Hz)",200,0,200);
		}	  
	}	

	TH1F *hnpe_hgc_mom[10],*hnpe_hgc_mom_theta[10][10];
	for(int i=0;i<10;i++){
		char hstname[200]; 
		sprintf(hstname,"npe_hgc_mom_%i",i);
		hnpe_hgc_mom[i]=new TH1F(hstname,";Npe;count",200,0,200);
		for(int j=0;j<10;j++){
			sprintf(hstname,"npe_hgc_mom_theta_%i_%i",i,j);
			hnpe_hgc_mom_theta[i][j]=new TH1F(hstname,";Npe;count",200,0,200);
		}	  
	}

	TH2F *hvertex_rz=new TH2F("hvertex_rz","hvertex_rz",1800,-400,500,600,0,300);

	TH2F *hgen_ThetaP=new TH2F("gen_ThetaP","generated events;vertex #theta (deg);vertex P (GeV)",100,0,50,110,0,11);  
	TH2F *hgen_ThetaPhi=new TH2F("gen_ThetaPhi","generated events;vertex #theta (deg);vertex #phi (deg)",100,0,50,360,-180,180);     
	TH2F *hgen_PhiP=new TH2F("gen_PhiP","generated events;vertex #phi (deg);vertex P (GeV)",360,-180,180,110,0,11);	

	//TH3F *hgen_ThetaPhiP=new TH3F("gen_ThetaPhiP","gen_ThetaPhiP",50,0,50,180,-180,180,55,0,11);   

	TH2F *hgen_ThetaP_gem2=new TH2F("gen_ThetaP_gem2","flux events; #theta (deg); log10(E) (MeV)",360,0,180,140,-3,4);  
	TH2F *hgen_ThetaPhi_gem2=new TH2F("gen_ThetaPhi_gem2","flux events; #theta (deg); #phi (deg)",360,0,180,360,-180,180);     
	//TH1F *hgen_Theta_gem2=new TH1F("gen_Theta_gem2","flux events; #theta (deg); #phi (deg)",9000,0,90);     
	TH1F *hgen_Theta_gem2=new TH1F("gen_Theta_gem2","flux events; #theta (deg); #phi (deg)",2000,-10,10);     
	TH2F *hgen_PhiP_gem2=new TH2F("gen_PhiP_gem2","flux events; #phi (deg); P (GeV)",360,-180,180,1000,0,1000);	
	TH2F *hgen_Thetavz_gem2=new TH2F("gen_Thetavz_gem2","flux events; #theta (deg); #phi (deg)",360,0,180,2080,-40,1000);     

	//TH3F *hgen_ThetaPhiP_gem2=new TH3F("gen_ThetaPhiP_gem2","gen_ThetaPhiP",180,0,180,180,-180,180,500,0,1000);   
	TH2F *hgen_ThetaP_gem1=new TH2F("gen_ThetaP_gem1","flux events; #theta (deg); log10(E) (MeV)",360,0,180,140,-3,4);  
	TH2F *hgen_ThetaPhi_gem1=new TH2F("gen_ThetaPhi_gem1","flux events; #theta (deg); #phi (deg)",360,0,180,360,-180,180);     
	//TH1F *hgen_Theta_gem1=new TH1F("gen_Theta_gem1","flux events;vertex #theta (deg); #phi (deg)",9000,0,90);     
	TH1F *hgen_Theta_gem1=new TH1F("gen_Theta_gem1","flux events;vertex #theta (deg); #phi (deg)",2000,-10,10);     
	TH2F *hgen_PhiP_gem1=new TH2F("gen_PhiP_gem1","flux events;vertex #phi (deg); P (GeV)",360,-180,180,1000,0,1000);	
	TH2F *hgen_Thetavz_gem1=new TH2F("gen_Thetavz_gem1","flux events; #theta (deg); #phi (deg)",360,0,180,2080,-40,1000);     

	//TH3F *hgen_ThetaPhiP_gem1=new TH3F("gen_ThetaPhiP_gem1","gen_ThetaPhiP",180,0,180,180,-180,180,500,0,1000);   
	const int n=12;
	string detname[n]={"sc_front","sc_back","ec_front","ec_back","gem1","gem2","cc_win"};
	TH1F *hhit_vz[n];
	TH2F *hhit_xy[n],*hhit_xy_orig[n],*hhit_PhiR[n];
	TH1F *hhit_PID_orig[n], *hhit_PID[n];
	TH1F *hhit_E[n],*hhit_E_mip[n],*hhit_E_photonele[n],*hhit_E_ele[n],*hhit_Edep[n];		  	
	for(int i=0;i<n;i++){
		char hstname[100];
		sprintf(hstname,"hit_PID_orig_detector%i",i);
		hhit_PID_orig[i]=new TH1F(hstname,detname[i].c_str(),5000,-2500,2500);  
		sprintf(hstname,"hit_PID_detector%i",i);
		hhit_PID[i]=new TH1F(hstname,detname[i].c_str(),5000,-2500,2500);  
		sprintf(hstname,"hit_vz_%i",i);
		hhit_vz[i]=new TH1F(hstname,detname[i].c_str(),1600,-100,1500);  
		sprintf(hstname,"hit_xy_%i",i);
		hhit_xy[i]=new TH2F(hstname,detname[i].c_str(),400,-20,20,400,-20,20);        
		sprintf(hstname,"hit_xy_orig_%i",i);
		hhit_xy_orig[i]=new TH2F(hstname,detname[i].c_str(),100,-20,20,100,-20,20);        
		sprintf(hstname,"hit_PhiR_%i",i);
		hhit_PhiR[i]=new TH2F(hstname,detname[i].c_str(),360,-180,180,300,0,300);
		sprintf(hstname,"hit_E_%i",i);
		hhit_E[i]=new TH1F(hstname,detname[i].c_str(),1100,0,11);
		sprintf(hstname,"hit_E_mip_%i",i);
		hhit_E_mip[i]=new TH1F(hstname,detname[i].c_str(),1100,0,11);
		sprintf(hstname,"hit_E_photonele_%i",i);
		hhit_E_photonele[i]=new TH1F(hstname,detname[i].c_str(),1100,0,11);
		sprintf(hstname,"hit_E_ele_%i",i);
		hhit_E_ele[i]=new TH1F(hstname,detname[i].c_str(),1100,0,11);	  
		sprintf(hstname,"hit_Edep_%i",i);
		hhit_Edep[i]=new TH1F(hstname,detname[i].c_str(),1000,0,0.1);	  
	}

	//	TH1F *hhit_Edepsc1=new TH1F("hit_Edepsc1","SC1;Edep (GeV);rate(Hz)",100,0,200);
	TH1F *hhit_Edepsc2=new TH1F("hit_Edepsc2","SC2;Edep (GeV);rate(Hz)",100,0,200);
	TH1F *hhit_Edepspd1=new TH1F("hit_Edepspd1","SPD1;Edep (GeV);rate(Hz)",100,0,100);
	TH1F *hhit_Edepspd2=new TH1F("hit_Edepspd2","SPD2;Edep (GeV);rate(Hz)",100,0,100);
	// 	TH1F *hhit_Eec=new TH1F("hit_Eec","EC;(GeV);rate(Hz)",1100,0,11);
	// 	TH1F *hhit_Eec_photonele=new TH1F("hit_Eec_photonele","EC (photon,e-/e+);E(GeV);rate(Hz)",1100,0,11);
	// 	TH1F *hhit_Eec_ele=new TH1F("hit_Eec_ele","EC (e-/e+);E(GeV);rate(Hz)",1100,0,11);			
	// 	TH1F *hhit_Pec_pion=new TH1F("hit_Pec_pion","EC;P(GeV);rate(Hz)",1100,0,11);
	// 	TH1F *hhit_Pec_proton=new TH1F("hit_Pec_proton","EC;P(GeV);rate(Hz)",1100,0,11);	
	TH1F *hprocid_gem2=new TH1F("procid_gem2","gem2;ProcID;rate(Hz)",150,-0.5,149.5);
	TH1F *hpf_gem2=new TH1F("hpf_gem2","gem2;gem2 flux p (MeV);rate(Hz)",1001,-0.5,1000.5);
	TH1F *hE_gem2=new TH1F("hE_gem2","gem2;gem2 track_E (MeV);rate(Hz)",401,-0.5,400.5);

	TH1F *hprocid_gem1=new TH1F("procid_gem1","gem1;ProcID;rate(Hz)",150,-0.5,149.5);
	TH1F *hpf_gem1=new TH1F("hpf_gem1","gem1;flux p (MeV);rate(Hz)",1001,-0.5,1000.5);
	TH1F *hE_gem1=new TH1F("hE_gem1","gem1;track_E (MeV);rate(Hz)",401,-0.5,400.5);
	TH1F *hprocid_sc2=new TH1F("procid_sc2","SC2;ProcID;rate(Hz)",150,-0.5,149.5);
	TH1F *hprocid_ec=new TH1F("procid_ec","EC;ProcID;rate(Hz)",150,-0.5,149.5);
	TH2F *hhit_p_vs_Edepgem1 =new TH2F("hit_p_vs_Edepgem1","gem1;log10(Edep)(MeV);p (MeV/c)",100,-4,3,2000,0,1000);
	TH1F *hhit_Edepgem1=new TH1F("hit_Edepgem1","gem1;log10(Edep)(MeV);rate(Hz)",100,-4,3);
	TH1F *hhit_Edepgem2=new TH1F("hit_Edepgem2","gem2;log10(Edep)(MeV);rate(Hz)",100,-4,3);
	TH1F *hhit_E_gem1=new TH1F("hit_E_gem1","gem1;log10(Edep)(MeV);rate(Hz)",140,-4,3);
	TH1F *hhit_E_gem2=new TH1F("hit_E_gem2","gem2;log10(Edep)(MeV);rate(Hz)",140,-4,3);
	TH1F *hhit_Edepgem1_procID[11];
	TH1F *hhit_Edepgem2_procID[11];
	TH1F *hhit_Egem1_procID[11];
	TH1F *hhit_Egem2_procID[11];
	TH1F *hhit_Edepgem1_gas[6];
	TH1F *hhit_Edepgem2_gas[6];
	for(int k=0;k<11;k++){
		hhit_Edepgem1_procID[k]=new TH1F(Form("hit_Edepgem1_procID%d",k),"gem1_Edepgem1_procID;log10(Edep)(MeV);rate(Hz)",100,-4,3);
		hhit_Edepgem2_procID[k]=new TH1F(Form("hit_Edepgem2_procID%d",k),"gem2_Edepgem2_procID;log10(Edep)(MeV);rate(Hz)",100,-4,3);
		hhit_Egem1_procID[k]=new TH1F(Form("hit_Egem1_procID%d",k),"flux_Edepgem1_procID;log10(E)(MeV);rate(Hz)",70,-3,4);
		hhit_Egem2_procID[k]=new TH1F(Form("hit_Egem2_procID%d",k),"flux_Edepgem2_procID;log10(E)(MeV);rate(Hz)",70,-3,4);
	}
	for(int m=0;m<6;m++){
		hhit_Edepgem1_gas[m]=new TH1F(Form("hit_Edepgem1_gas%d",m),"gem1_Edepgem1_gas_layer;log10(Edep)(MeV);rate(Hz)",100,-4,3);
		hhit_Edepgem2_gas[m]=new TH1F(Form("hit_Edepgem2_gas%d",m),"gem2_Edepgem2_gas_layer;log10(Edep)(MeV);rate(Hz)",100,-4,3);
        }
	TH1F *hhit_Edepgem1_procID_other=new TH1F("hit_Edepgem1_procID_other","gem1_Edepgem1_procID;log10(E)(MeV);rate(Hz)",100,-4,3);
	TH1F *hhit_Edepgem2_procID_other=new TH1F("hit_Edepgem2_procID_other","gem2_Edepgem2_procID;log10(E)(MeV);rate(Hz)",100,-4,3);
	TH1F *hhit_Egem1_procID_other=new TH1F("hit_Egem1_procID_other","flux_Egem1_procID;log10(E)(MeV);rate(Hz)",70,-3,4);
	TH1F *hhit_Egem2_procID_other=new TH1F("hit_Egem2_procID_other","flux_Egem2_procID;log10(E)(MeV);rate(Hz)",70,-3,4);
	TH1F *hhit_Edepgem1_pi0=new TH1F("hit_Edepgem1_pi0","gem1;log10(Edep)(MeV);rate(Hz)",100,-4,3);
	TH1F *hhit_Edepgem1_gamma=new TH1F("hit_Edepgem1_gamma","gem1;log10(Edep)(MeV);rate(Hz)",100,-4,3);
	TH1F *hhit_Edepgem1_electron=new TH1F("hit_Edepgem1_electron","gem1;log10(Edep)(MeV);rate(Hz)",100,-4,3);
	TH1F *hhit_Edepgem1_other=new TH1F("hit_Edepgem1_other","gem1;log10(Edep)(MeV);rate(Hz)",100,-4,3);
	TH1F *hhit_Egem1=new TH1F("hit_Egem1","flux;log10(E)(MeV);rate(Hz)",140,-3,4);
	TH1F *hhit_Egem2=new TH1F("hit_Egem2","flux;log10(E)(MeV);rate(Hz)",140,-3,4);
	TH1F *hhit_Egem12=new TH1F("hit_Egem12","flux;log10(E)(MeV);rate(Hz)",800,-4,4);
	TH1F *hhit_Egem12_test=new TH1F("hit_Egem12_test","flux;log10(E)(MeV);rate(Hz)",800,-4,4);
	TH1F *hhit_Egem1_pi0=new TH1F("hit_Egem1_pi0","flux;log10(E)(MeV);rate(Hz)",70,-3,4);
	TH1F *hhit_Egem1_gamma=new TH1F("hit_Egem1_gamma","flux;log10(E)(MeV);rate(Hz)",70,-3,4);
	TH1F *hhit_Egem1_electron=new TH1F("hit_Egem1_electron","flux;log10(E)(MeV);rate(Hz)",70,-3,4);
	TH1F *hhit_Egem1_other=new TH1F("hit_Egem1_other","flux;log10(E)(MeV);rate(Hz)",70,-3,4);
	TH1F *hhit_Edepsc1=new TH1F("hit_Edepsc1","sc1;log10(Edep)(GeV);rate(Hz)",100,-6,-1);
	//TH1F *hhit_Edepsc2=new TH1F("hit_Edepsc2","SC2;log10(Edep)(GeV);rate(Hz)",100,-6,-1);
	TH1F *hhit_Eec=new TH1F("hit_Eec","EC (all);log10(E)(GeV);rate(Hz)",70,-6,1);
	TH1F *hhit_Eec_photonele=new TH1F("hit_Eec_photonele","EC (photon,e-/e+);log10(E)(GeV);rate(Hz)",70,-6,1);
	TH1F *hhit_x_GEM00 = new TH1F("hhit_x_GEM00","hhit_x_GEM00;GEM00_x(cm);rate(Hz)",400,-10,10);
	TH1F *hhit_Diffx_GEM = new TH1F("hhit_Diffx_GEM","hhit_Diffx_GEM;GEM00_x-GEM10_x (cm);rate(Hz)",400,-10,10);
	TH1F *hhit_Diffy_GEM = new TH1F("hhit_Diffy_GEM","hhit_Diffy_GEM;GEM00_y-GEM10_y (cm);rate(Hz)",400,-10,10);
	TH1F *hhit_x_GEM10 = new TH1F("hhit_x_GEM10","hhit_x_GEM10;GEM10_x(cm);rate(Hz)",400,-10,10);
	TH1F *hhit_y_GEM00 = new TH1F("hhit_y_GEM00","hhit_y_GEM00;GEM00_y(cm);rate(Hz)",400,-10,10);
	TH1F *hhit_y_GEM10 = new TH1F("hhit_y_GEM10","hhit_y_GEM10;GEM10_y(cm);rate(Hz)",400,-10,10);
	TH2F *Diff_x_vs_y_GEM = new TH2F("Diff_x_vs_y_GEM","Diff_x_vs_y_GEM;GEM00_y-GEM10_y(cm);GEM00_x-GEM10_x(cm)",400,-10,10,400,-10,10);
	TH1F *hhit_Eec_ele=new TH1F("hit_Eec_ele","EC (e-/e+);log10(E)(GeV);rate(Hz)",70,-6,1);			
	TH1F *hhit_Pec_pion=new TH1F("hit_Pec_pion","EC;log10(P)(GeV);rate(Hz)",70,-6,1);
	TH1F *hhit_Pec_proton=new TH1F("hit_Pec_proton","EC;log10(P)(GeV);rate(Hz)",70,-6,1);	
	TH1F *vertex_Z_hist=new TH1F("vertex_Z_hist","vertex;z (cm);rate(Hz)",2080,-40,1000);	
	TH2F *vertexZ_vs_vertexR_hist=new TH2F("vertexZ_vs_vertexR_hist","vertex;z (cm);R(cm)",2080,-40,1000,1600,0,800);	
	TH2F *vertexmZ_vs_vertexmR_hist=new TH2F("vertexmZ_vs_vertexmR_hist","vertex;z (cm);R(cm)",4480,-40,2200,1600,0,800);	
	//TH2F *vertexX_vs_vertexY_hist=new TH2F("vertexX_vs_vertexY_hist","vertex;X (cm);Y(cm)",360,-20,160,360,-20,160);	
	//TH2F *vertexX_vs_vertexY_gem2_hist=new TH2F("vertexX_vs_vertexY_gem2_hist","vertex;X (cm);Y(cm)",360,-20,160,360,-20,160);	
	TH2F *vertexX_vs_vertexY_hist=new TH2F("vertexX_vs_vertexY_hist","vertex;X (cm);Y(cm)",360,-160,20,360,-20,160);	
	TH2F *vertexX_vs_vertexY_gem2_hist=new TH2F("vertexX_vs_vertexY_gem2_hist","vertex;X (cm);Y(cm)",360,-160,20,360,-20,160);	
	//TH3F *vertexXYZ_hist=new TH3F("vertexXYZ_hist","vertex;X (cm);Y(cm);Z (cm)",360,-20,160,360,-20,160,1020,-20,1000);	
	//TH3F *vertexXYZ_gem2_hist=new TH3F("vertexXYZ_gem2_hist","vertex;X (cm);Y(cm);Z (cm)",360,-20,160,360,-20,160,1020,-20,1000);	
	TH2F *vertexZ_vs_vertexR_gem2_hist=new TH2F("vertexZ_vs_vertexR_gem2_hist","vertex;z (cm);R(cm)",2080,-40,1000,1600,0,800);	
	TH2F *vertexmZ_vs_vertexmR_gem2_hist=new TH2F("vertexmZ_vs_vertexmR_gem2_hist","vertex;z (cm);R(cm)",4480,-40,2200,1600,0,800);	
	TH2F *vertexZ_vs_vertexR_gem12_hist=new TH2F("vertexZ_vs_vertexR_gem12_hist","vertex;z (cm);R(cm)",2080,-40,1000,1600,0,800);	
	TH2F *vertexZ_vs_vertexR_gem12_test_hist=new TH2F("vertexZ_vs_vertexR_gem12_test_hist","vertex;z (cm);R(cm)",2080,-40,1000,1600,0,800);	
	TH2F *vertexZ_vs_vertexR_cut_hist=new TH2F("vertexZ_vs_vertexR_cut_hist","vertex;z (cm);R(cm)",2080,-40,1000,1600,0,800);	
	TH2F *vertexZ_vs_E_hist=new TH2F("vertexmZ_vs_E_hist","vertex;mz (cm);E (MeV)",4480,-40,2200,2500,0,5000);	
	TH2F *vertexZ_vs_theta_hist=new TH2F("vertexmZ_vs_theta_hist","vertex;mz (cm);hit #theta(deg)",4480,-40,2200,360,0,180);	
	TH2F *vertexZ_vs_theta_gem2_hist=new TH2F("vertexmZ_vs_theta_gem2_hist","vertex;mz (cm);hit #theta (deg)",4480,-40,2200,360,0,180);	
	TH2F *vertexZ_vs_E_gem2_hist=new TH2F("vertexmZ_vs_E_gem2_hist","vertex;mz (cm);E (MeV)",4480,-40,2200,2500,0,5000);	
	TH2F *mvertexZ_vs_E_hist=new TH2F("mvertexZ_vs_E_hist","vertex;mz (cm);E (MeV)",2080,-40,1000,500,0,500);	
	TH2F *mvertexZ_vs_E_cut_hist=new TH2F("mvertexZ_vs_E_cut_hist","vertex;mz (cm);E (MeV)",2080,-40,1000,500,0,500);	
	TH2F *mvertexZ_vs_mvertexR_hist=new TH2F("mvertexZ_vs_mvertexR_hist","vertex;mz (cm);mR (cm)",2080,-40,1000,1600,0,800);	
	TH2F *mvertexZ_vs_mvertexR_cut_hist=new TH2F("mvertexZ_vs_mvertexR_cut_hist","vertex;mz (cm);mR (cm)",2080,-40,1000,1600,0,800);	
	TH1F *vertex_R_hist=new TH1F("vertex_R_hist","vertex;R (cm);rate (Hz)",1600,0,800);	
	TH1F *hit_Z_hist=new TH1F("Z_hist","gem1;z (cm);rate (Hz)",120,200,260);	
	TH1F *hit_R_hist=new TH1F("R_hist","gem1;R (cm);rate (Hz)",80,720,760);	
	TH2F *hitZ_vs_hitR_hist=new TH2F("hitZ_vs_hitR_hist","gem1;z (cm);R (cm)",120,200,260,80,720,760);	

	double hit_Edepsc1_count[3],hit_Edepsc2_count[3];
	double hit_Eec_count[3],hit_Eec_photonele_count[3],hit_Eec_ele_count[3];

	double hit_Pec_pion_count;
	double hit_Pec_proton_count;

	TH1F *hhit_mom_hgc_e=new TH1F("hit_mom_hgc_e","hit_mom_hgc_e",100,0,0.05);		


	TH2F *hec_Eend_2D=new TH2F("ec_Eend_2D","EC;Eend_shower;Eend_preshower",200,0,500,100,0,100);
	TH1F *hec_Eend_shower=new TH1F("ec_Eend_shower","EC;Eend [MeV]",200,0,200);
	TH1F *hec_Eend_preshower=new TH1F("ec_Eend_preshower","EC;Eend_preshower [MeV]",100,0,100);

	//-------------------------
	//   get trees in the real data file
	//-------------------------

	//---header tree
	TTree *tree_header = (TTree*) file->Get("header");
	vector <int> *evn=0,*evn_type=0,*runNo=0;
	vector <double> *beamPol=0;
	vector <double> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0;
	tree_header->SetBranchAddress("evn",&evn);      // number 
	tree_header->SetBranchAddress("evn_type",&evn_type);  // evn_type==-1 for simulated events
	tree_header->SetBranchAddress("beamPol",&beamPol);   //beam polarization
	tree_header->SetBranchAddress("runNo",&runNo);  // run number	  	
	if (!Is_new){	
		tree_header->SetBranchAddress("var1",&var1);     // W+ rate
		tree_header->SetBranchAddress("var2",&var2);     // W- rate
		tree_header->SetBranchAddress("var3",&var3);     // target pol
		tree_header->SetBranchAddress("var4",&var4);     //x
		tree_header->SetBranchAddress("var5",&var5);     //y
		tree_header->SetBranchAddress("var6",&var6);     //w
		tree_header->SetBranchAddress("var7",&var7);     //Q2
		tree_header->SetBranchAddress("var8",&var8);     //rate, Hz, should check the input file of the simulation
	}

	TTree *tree_userHeader;
	vector <double> *userVar001=0,*userVar002=0,*userVar003=0,*userVar004=0,*userVar005=0,*userVar006=0,*userVar007=0,*userVar008=0,*userVar009=0,*userVar010=0;
	if (Is_new){
		tree_userHeader = (TTree*) file->Get("userHeader");
		tree_userHeader->SetBranchAddress("userVar001",&userVar001);
		tree_userHeader->SetBranchAddress("userVar002",&userVar002);
		tree_userHeader->SetBranchAddress("userVar003",&userVar003);
		tree_userHeader->SetBranchAddress("userVar004",&userVar004);
		tree_userHeader->SetBranchAddress("userVar005",&userVar005);
		tree_userHeader->SetBranchAddress("userVar006",&userVar006);
		tree_userHeader->SetBranchAddress("userVar007",&userVar007);
		tree_userHeader->SetBranchAddress("userVar008",&userVar008);
		tree_userHeader->SetBranchAddress("userVar009",&userVar009);
		tree_userHeader->SetBranchAddress("userVar010",&userVar010);
	}

	//---generated tree
	//particle generated with certain momentum at certain vertex
	TTree *tree_generated = (TTree*) file->Get("generated");
	vector <int> *gen_pid=0;
	vector <double> *gen_px=0,*gen_py=0,*gen_pz=0,*gen_vx=0,*gen_vy=0,*gen_vz=0;
	tree_generated->SetBranchAddress("pid",&gen_pid);   //particle ID 
	tree_generated->SetBranchAddress("px",&gen_px);     //momentum of the generated particle at target
	tree_generated->SetBranchAddress("py",&gen_py);
	tree_generated->SetBranchAddress("pz",&gen_pz);
	tree_generated->SetBranchAddress("vx",&gen_vx);    //vertex of the generated particle at target
	tree_generated->SetBranchAddress("vy",&gen_vy);
	tree_generated->SetBranchAddress("vz",&gen_vz);

	//--- flux
	//the real deal output from the GEMC simulation
	TTree *tree_flux = (TTree*) file->Get("flux");
	vector<int> *flux_id=0,*flux_hitn=0;
	vector<int> *flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0,*flux_procID=0;
	vector<double> *flux_trackE=0,*flux_totEdep=0,*flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0,*flux_avg_lz=0,*flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;
	tree_flux->SetBranchAddress("hitn",&flux_hitn);     // hit number
	tree_flux->SetBranchAddress("id",&flux_id);         //hitting detector ID
	tree_flux->SetBranchAddress("pid",&flux_pid);       //pid
	tree_flux->SetBranchAddress("mpid",&flux_mpid);     // mother pid
	tree_flux->SetBranchAddress("tid",&flux_tid);       // track id
	tree_flux->SetBranchAddress("mtid",&flux_mtid);     // mother track id
	tree_flux->SetBranchAddress("otid",&flux_otid);     // original track id
	tree_flux->SetBranchAddress("trackE",&flux_trackE);  // track energy of 1st step,  track here is G4 track
	tree_flux->SetBranchAddress("totEdep",&flux_totEdep); // totEdep in all steps, track here is G4 track
	tree_flux->SetBranchAddress("avg_x",&flux_avg_x);     //average x, weighted by energy deposition in each step
	tree_flux->SetBranchAddress("avg_y",&flux_avg_y);     //average y
	tree_flux->SetBranchAddress("avg_z",&flux_avg_z);     //average z
	tree_flux->SetBranchAddress("avg_lx",&flux_avg_lx);   // local average x 
	tree_flux->SetBranchAddress("avg_ly",&flux_avg_ly);   // local average y
	tree_flux->SetBranchAddress("avg_lz",&flux_avg_lz);   // local average z
	tree_flux->SetBranchAddress("px",&flux_px);          // px of 1st step
	tree_flux->SetBranchAddress("py",&flux_py);          // py of 1st step
	tree_flux->SetBranchAddress("pz",&flux_pz);          // pz of 1st step
	tree_flux->SetBranchAddress("vx",&flux_vx);          // x coordinate of 1st step
	tree_flux->SetBranchAddress("vy",&flux_vy);          // y coordinate of 1st step
	tree_flux->SetBranchAddress("vz",&flux_vz);          // z coordinate of 1st step
	tree_flux->SetBranchAddress("mvx",&flux_mvx);        // mother
	tree_flux->SetBranchAddress("mvy",&flux_mvy);
	tree_flux->SetBranchAddress("mvz",&flux_mvz);
	tree_flux->SetBranchAddress("avg_t",&flux_avg_t);     //average time stamp
	tree_flux->SetBranchAddress("procID",&flux_procID);     // process id
	TTree* tree_solid_gem = (TTree*) file->Get("solid_gem");
	setup_tree_solid_gem(tree_solid_gem);	
	//---hgc
	//information recorded by hgc
	TTree* tree_solid_hgc= (TTree*) file->Get("solid_hgc");
	setup_tree_solid_hgc(tree_solid_hgc);	

	//information recorded by ec
	TTree* tree_solid_ec= (TTree*) file->Get("solid_ec");
	TTree* tree_solid_ec_ps= (TTree*) file->Get("solid_ec_ps");
	setup_tree_solid_ec(tree_solid_ec);	
	setup_tree_solid_ec_ps(tree_solid_ec_ps);	

	//information recorded by spd
	TTree* tree_solid_spd= (TTree*) file->Get("solid_spd");
	setup_tree_solid_spd(tree_solid_spd);	

	TRandom3 rand;
	rand.SetSeed(0);

	int sensor_good=0;
	int event_good=0,event_trig_good=0;
		double totEdep_gem1_gas[6]={0};
		double totEdep_gem2_gas[6]={0};
		double totEdep_gem1tot=0;
		double totEdep_gem2tot=0;
		double totEdep_gem3_gas[6]={0};
		double totEdep_gem4_gas[6]={0};
		double totEdep_gem3tot=0;
		double totEdep_gem4tot=0;
	int procID_gem=0;
	int mpid_gem=0;
	int pid_gem=0;
	int procID_flux=0;
	int N_gem00 = 0;
	int N_gem10 = 0;
	double trackE_flux=0;
	double hit_th_max=0;
	double hit_vz_max=0;
	double hit_mvz_max=0;
	double hit_vx_max=0;
	double hit_vy_max=0;
	double hit_vr_max=0;
	double hit_mvr_max=0;
	double hit_phi_max=0;
	double edep_6p1_max= 0;
	double trackE_flux_gem2=0;
	double edep_6p1_max_gem2= 0;
	double hit_th_max_gem2=0;
	double hit_phi_max_gem2=0;
	double hit_vz_max_gem2=0;
	double hit_mvz_max_gem2=0;
	double hit_vx_max_gem2=0;
	double hit_vy_max_gem2=0;
	double hit_vr_max_gem2=0;
	double hit_mvr_max_gem2=0;
	// 	long int N_events = (long int)tree_header->GetEntries();
	long int N_events = (long int)tree_generated->GetEntries();	

	cout << "total number of events : " << N_events << endl;	
	Fillecal=kFALSE;
	Fillgem=kFALSE;

	//----------------------------
	//      loop trees
	//---------------------------
	for(long int i=0;i<N_events;i++){	  		
		// 	for(long int i=1;i<N_events-1;i++){	  				
		// 	for(long int i=0;i<N_events/100;i++){	  
		// 	for(long int i=N_events/2;i<N_events;i++){	  		
		// 	for(long int i=520;i<521;i++){  //pip event
		// 	for(long int i=5289;i<5290;i++){	  // background event			  
		// 			cout<<"" << i<<endl;
		cout<<"event " << i << "\r";
		//cout<<"rate="<<rate<<endl;
		// 		if (i%1000==0) cout<<i<<"\r";
		// 		if (i%1000==0) cout<<i<<"\n";

		//---
		//---header tree
		//---
		double rate=0;
		if (Is_new){
			tree_userHeader->GetEntry(i);
			//rate=userVar010->at(0); // new eDIS and eAll generator
			//if(userVar005->at(0)>0.01){
			//	rate=userVar006->at(0); // new eDIS and eAll generator
			//}
			//rate=userVar010->at(0)/filenum; 
			if(userVar005->at(0)>0.01){
			//rate=userVar006->at(0)/filenum; // new eDIS and eAll generator
			rate=userVar006->at(0)/1000.; // new eDIS and eAll generator
			//rate=userVar010->at(0); 		
	// 		cout << "rate  " << rate   << endl;
	         }
		}
		else {
			tree_header->GetEntry(i);
			rate=var8->at(0); // old eDIS and eAll generator
		}

		if (filemode=="BeamOnTargetEM" || filemode=="BeamOnTarget") {
			//rate=80e-6/1.6e-19/event_actual/loop_time*add_norm;  //1ua		  
			rate=40e-6/1.6e-19/event_actual/loop_time*add_norm;  //1ua		  
			//rate=2e-6/1.6e-19/event_actual/loop_time*add_norm;  //1ua		  
			// 		  if(Is_He3) rate=1e-6/1.6e-19/event_actual/loop_time*add_norm;
			// 		  else if(Is_C) rate=1e-6/1.6e-19/event_actual/loop_time*add_norm;		  
			// 		  else if(Is_NOtarget) rate=1e-6/1.6e-19/event_actual/loop_time*add_norm;		  		  
			// 		  else {
			// 		    cout << "Not He3 or C or NOtarget setup" << endl;    
			// 		    return 0;
			// 		  }
		}
		else if (filemode=="even") rate=1;
		else if (filemode=="rate") rate=rate/filenum/loop_time*add_norm;
		else {
			cout << "Not right filemode" << endl;    
			return 0; 
		}
		// 		cout << "rate " << rate << endl;

		/*		double x=var4->at(0);	
				double y=var5->at(0);
				double W=var6->at(0);		
				double Q2=var7->at(0);	*/	
		//cout<<"header tree: "<<rate<<endl;	

		//---
		//---generated tree
		//---
		//cout<<"rate="<<rate<<endl;
		tree_generated->GetEntry(i);
		int n_gen=gen_pid->size();
		//cout<<"generated : "<<n_gen<<endl;
		int pid_gen=0;
		double theta_gen=0,phi_gen=0,p_gen=0,px_gen=0,py_gen=0,pz_gen=0,vx_gen=0,vy_gen=0,vz_gen=0;      
		//       cout << "gen_pid->size() " << gen_pid->size() << endl;        
		for (int j=0;j<gen_pid->size();j++) {
			// 	            cout << gen_pid->at(j) << " " << gen_px->at(j) << " " << gen_py->at(j) << " " << gen_pz->at(j) << " " << gen_vx->at(j) << " " << gen_vy->at(j) << " " << gen_vz->at(j) << endl; 
			pid_gen=gen_pid->at(j);
			px_gen=gen_px->at(j);
			py_gen=gen_py->at(j);
			pz_gen=gen_pz->at(j);
			vx_gen=gen_vx->at(j)*0.1;
			vy_gen=gen_vy->at(j)*0.1;
			vz_gen=gen_vz->at(j)*0.1;
			p_gen=sqrt(px_gen*px_gen+py_gen*py_gen+pz_gen*pz_gen);
			theta_gen=acos(pz_gen/p_gen)*DEG;
			phi_gen=atan2(py_gen,px_gen)*DEG;
			// 	            cout << "p_gen " << p_gen << endl; 

		}		
		// 		TVector3 *vec_p_gen(px_gen,py_gen,pz_gen),*vec_v_gen(vx_gen,vy_gen,vz_gen);

		// 		if (phi_gen<-1 || phi_gen>1) continue;
		// 			cout<<"" << i<<endl;

		// 		if (vz_gen<-3550 || -3450<vz_gen) continue;

		hgen_ThetaP->Fill(theta_gen,p_gen/1e3,rate);
		hgen_ThetaPhi->Fill(theta_gen,phi_gen,rate);                  		
		hgen_PhiP->Fill(phi_gen,p_gen/1e3,rate);                  				
		//hgen_ThetaPhiP->Fill(theta_gen,phi_gen,p_gen/1e3,rate);                  			
		///////////////////////////////////////////////////////////////////////////////////////
		//       do trigger
		////////////////////////////////////////////////////////////////////////////////////////
		//---	
		//---flux tree
		//---
		tree_flux->GetEntry(i);		  

		int sec_hgc=0;		

		bool Is_trig=false;					  
		procID_flux=0;	
		//check on EC and other by flux
		// 		 cout << "flux_hitn  " << flux_hitn->size() << endl;
		double Eec=0,Eec_photonele=0,Eec_ele=0,Edepsc1=0,Edepsc2=0;
		int mpid_flux=0,pid_flux=0;
		double hitx_gem00=0,hity_gem00=0,hitx_gem10=0,hity_gem10=0;
		edep_6p1_max= 0;
		edep_6p1_max_gem2= 0;
		Fillecal=kFALSE;
		Fillgem=kFALSE;
		N_gem00=0;
		N_gem10=0;
		trackE_flux=0;
		trackE_flux_gem2=0;
		hit_th_max=0;
		hit_th_max_gem2=0;
		hit_vz_max=0;
		hit_vz_max_gem2=0;
		hit_mvz_max=0;
		hit_mvz_max_gem2=0;
		hit_vx_max=0;
		hit_vx_max_gem2=0;
		hit_vy_max=0;
		hit_vy_max_gem2=0;
		hit_vr_max=0;
		hit_vr_max_gem2=0;
		hit_mvr_max=0;
		hit_mvr_max_gem2=0;
		hit_phi_max=0;
		hit_phi_max_gem2=0;
		for (Int_t j=0;j<flux_hitn->size();j++) {
			// cout << "flux " << " !!! " << flux_hitn->at(j) << " " << flux_id->at(j)<<endl;
			//cout<< " " << flux_pid->at(j) << " " << flux_mpid->at(j) << " " << flux_tid->at(j) << " " << flux_mtid->at(j) << " " << flux_trackE->at(j) << " " << flux_totEdep->at(j) << " " << flux_avg_x->at(j) << " " << flux_avg_y->at(j) << " " << flux_avg_z->at(j) << " " << flux_avg_lx->at(j) << " " << flux_avg_ly->at(j) << " " << flux_avg_lz->at(j) << " " << flux_px->at(j) << " " << flux_py->at(j) << " " << flux_pz->at(j) << " " << flux_vx->at(j) << " " << flux_vy->at(j) << " " << flux_vz->at(j) << " " << flux_mvx->at(j) << " " << flux_mvy->at(j) << " " << flux_mvz->at(j) << " " << flux_avg_t->at(j) << endl;  

			double hit_vr=sqrt(pow(flux_vx->at(j),2)+pow(flux_vy->at(j),2))/1e1; //mm to cm
			double hit_vy=flux_vy->at(j)/1e1,hit_vx=flux_vx->at(j)/1e1,hit_vz=flux_vz->at(j)/1e1;           //mm to cm
			double diff_vy=flux_avg_y->at(j)/1e1-vy_gen,diff_vx=flux_avg_x->at(j)/1e1-vx_gen,diff_vz=flux_avg_z->at(j)/1e1-vz_gen;           //mm to cm
	                //double hit_th_target=atan2(sqrt(diff_vy*diff_vy+diff_vx*diff_vx),diff_vz)*DEG;
			double hit_mvy=flux_mvy->at(j)/1e1,hit_mvx=flux_mvx->at(j)/1e1,hit_mvz=flux_mvz->at(j)/1e1;           //mm to cm		  
			double hit_mvr=sqrt(pow(flux_mvx->at(j),2)+pow(flux_mvy->at(j),2))/1e1; //mm to cm
			double hit_r=sqrt(pow(flux_avg_x->at(j),2)+pow(flux_avg_y->at(j),2))/1e1; //mm to cm
			double hit_y=flux_avg_y->at(j)/1e1,hit_x=flux_avg_x->at(j)/1e1,hit_z=flux_avg_z->at(j)/1e1;           //mm to cm		
			double hit_phi=atan2(hit_y,hit_x)*DEG;       //rad to  deg
			double hit_th_target=atan2(sqrt(diff_vy*diff_vy+diff_vx*diff_vx),diff_vz)*DEG;       //rad to  deg
			double hit_p=sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)+flux_pz->at(j)*flux_pz->at(j));  //MeV to GeV
	                double hit_th=atan2(sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)),flux_pz->at(j))*DEG;
                        double diff_th = hit_th-hit_th_target;
                        //cout<<"target_x="<<vx_gen<<"target_y="<<vy_gen<<"target_z="<<vz_gen<<"hit_vx="<<hit_vx<<"hit_vy="<<hit_vy<<"hit_vz="<<hit_vz<<"hit_th="<<hit_th<<"target_th="<<hit_th_target<<"diff_th="<<diff_th<<endl;		  

			int hit_id=-1;
			if(flux_id->at(j)==1) hit_id=0; // SC front,SC1
			else if(flux_id->at(j)==2) hit_id=1; // SC_D front 6.5x5.5 preshower title
			else if(flux_id->at(j)==3) hit_id=2; // EC front 
			else if(flux_id->at(j)==4) hit_id=3; // EC back 
			else if(flux_id->at(j)==5) hit_id=4; // GEM00
			else if(flux_id->at(j)==6) hit_id=5; // GEM10	  
			else if(flux_id->at(j)==7) hit_id=7; // SC4 5x10x1
			else if(flux_id->at(j)==8) hit_id=8; // LASPD	  
			else if(flux_id->at(j)==10) hit_id=6; // Cherenkov front window
			else if(flux_id->at(j)==11) hit_id=9; // SC_C 4.5x18cm2 
			else if(flux_id->at(j)==20) hit_id=10; // GEM01
			else if(flux_id->at(j)==21) hit_id=11; // GEM11
			else cout << "wrong flux_id" << flux_id->at(j) << endl;

			hhit_xy[hit_id]->Fill(flux_avg_lx->at(j)/1e1,flux_avg_ly->at(j)/1e1,rate);
			hhit_vz[hit_id]->Fill(hit_vz,rate);
			hhit_PID[hit_id]->Fill(flux_pid->at(j),rate);                        
			if (flux_tid->at(j) ==1){
				hhit_xy_orig[hit_id]->Fill(flux_avg_lx->at(j)/1e1,flux_avg_ly->at(j)/1e1,rate);
				hhit_PID_orig[hit_id]->Fill(flux_pid->at(j),rate);
			}

			double E=flux_trackE->at(j)/1e3;
			double Edep=flux_trackE->at(j);		  
			hhit_Edep[hit_id]->Fill(Edep,rate);		  
			hhit_E[hit_id]->Fill(E,rate);
			if (abs(flux_pid->at(j)) == 211 || flux_pid->at(j)==2212|| flux_pid->at(j)==13) hhit_E_mip[hit_id]->Fill(E,rate);
			if (abs(flux_pid->at(j)) == 11 || flux_pid->at(j)==22) hhit_E_photonele[hit_id]->Fill(E,rate);
			if (abs(flux_pid->at(j)) == 11) hhit_E_ele[hit_id]->Fill(E,rate);  

			if (hit_id==2 && flux_tid->at(j)==1) {//gem1
				hhit_x_GEM00->Fill(flux_avg_lx->at(j)/1e1); 
				hhit_y_GEM00->Fill(flux_avg_ly->at(j)/1e1);
				hitx_gem00 = flux_avg_lx->at(j)/1e1;
				hity_gem00 = flux_avg_ly->at(j)/1e1;
				N_gem00 ++;
				if(flux_pz->at(j)>0){  
				//	if (hit_p >= edep_6p1_max){
						edep_6p1_max=hit_p;
						trackE_flux = Edep;
                                                //hit_th_max = hit_th;
                                                hit_th_max = diff_th;
                                                hit_phi_max = hit_phi;
                                                hit_vz_max = hit_vz;
                                                hit_mvz_max = hit_mvz;
                                                hit_vx_max = hit_vx;
                                                hit_vy_max = hit_vy;
					        procID_flux=flux_procID->at(j);
                                                hit_vr_max = hit_vr;
                                                hit_mvr_max = hit_mvr;
				//	}

					//cout<<"event="<<i<<"index="<<j<<"hit_th="<<hit_th<<"diff_th"<<diff_th<<"target_th="<<hit_th_target<<endl;
					Edepsc1 += Edep;
					//procID_flux=flux_procID->at(j);
					mpid_flux=flux_mpid->at(j);
					pid_flux=flux_pid->at(j);
						vertex_Z_hist->Fill(hit_vz,rate);
						vertex_R_hist->Fill(hit_vr,rate);
						mvertexZ_vs_mvertexR_hist->Fill(hit_mvz,hit_mvr,rate);
						//vertexZ_vs_E_hist->Fill(hit_vz,hit_p,rate);
						hit_Z_hist->Fill(hit_z,rate);
						hit_R_hist->Fill(hit_r,rate);
						hitZ_vs_hitR_hist->Fill(hit_z,hit_r,rate);
					if(flux_procID->at(j)==1 && flux_pz->at(j)>0 ){
						mvertexZ_vs_E_hist->Fill(hit_mvz,hit_p,rate);
					}
					if(hit_p>40 && flux_pz->at(j)>0 ){
						mvertexZ_vs_E_cut_hist->Fill(hit_mvz,hit_p,rate);
						vertexZ_vs_vertexR_cut_hist->Fill(hit_vz,hit_vr,hit_p);
					}
					hprocid_gem1->Fill(flux_procID->at(j),rate);
					if(mpid_flux==111){
						hhit_Egem1_pi0->Fill(log10(hit_p),rate);
					}else if(abs(mpid_flux)==11){
						hhit_Egem1_electron->Fill(log10(hit_p),rate);
					}else if(mpid_flux==22){
						hhit_Egem1_gamma->Fill(log10(hit_p),rate);
					}else{
						hhit_Egem1_other->Fill(log10(hit_p),rate);
					}
					Fillecal=kTRUE;
				} else{// end pid=22
					Fillecal=kFALSE;
				}
			}//end gem1
			if (hit_id==1 && flux_tid->at(j)==1) {//EC front 
				if(flux_pz->at(j)>0){
				//	if (hit_p >= edep_6p1_max){
						edep_6p1_max_gem2=hit_p;
						trackE_flux_gem2 = Edep;
                                                //hit_th_max_gem2 = hit_th;
                                                hit_th_max_gem2 = diff_th;
                                                hit_phi_max_gem2 = hit_phi;
                                                hit_vz_max_gem2 = hit_vz;
                                                hit_mvz_max_gem2 = hit_vz;
                                                hit_vy_max_gem2 = hit_vy;
                                                hit_vx_max_gem2 = hit_vx;
                                                hit_vr_max_gem2 = hit_vr;
                                                hit_mvr_max_gem2 = hit_vr;
				//	}
//					cout<<"event="<<i<<"index="<<j<<"Edep="<<trackE_flux_gem2<<endl;

					hhit_x_GEM10->Fill(flux_avg_lx->at(j)/1e1);
					hhit_y_GEM10->Fill(flux_avg_ly->at(j)/1e1);
					hitx_gem10 = flux_avg_lx->at(j)/1e1;
					hity_gem10 = flux_avg_ly->at(j)/1e1;
					N_gem10 ++; 
					//cout<<"event="<<i<<"index="<<j<<"hit_ID="<<hit_id<<" hitx_gem00="<<hitx_gem00<<"hity_gem00="<<hity_gem00<<" hitx_gem10="<<hitx_gem10<<"hity_gem10="<<hity_gem10<<"hitz_gem10="<<flux_avg_z->at(j)/1e1<<endl;
				Fillgem=kTRUE;
				}else { // end gem2
				Fillgem=kFALSE;
                          }
			}//end gem2
		}	// end of flux	
		if(N_gem00>0 || N_gem10>0){
			hhit_Diffx_GEM->Fill(hitx_gem00-hitx_gem10);
			hhit_Diffy_GEM->Fill(hity_gem00-hity_gem10);
			Diff_x_vs_y_GEM->Fill((hitx_gem00-hitx_gem10),(hity_gem00-hity_gem10));
		}

		hhit_Edepsc1->Fill(log10(Edepsc1),rate);
		hhit_Eec->Fill(log10(Eec),rate);
		hhit_Eec_photonele->Fill(log10(Eec_photonele),rate);		  
		hhit_Eec_ele->Fill(log10(Eec_ele),rate);	
		//                gem 
		tree_solid_gem->GetEntry(i);
		totEdep_gem1_gas[6]={0};
		totEdep_gem2_gas[6]={0};
		totEdep_gem1tot=0;
		totEdep_gem2tot=0;
		totEdep_gem3_gas[6]={0};
		totEdep_gem4_gas[6]={0};
		totEdep_gem3tot=0;
		totEdep_gem4tot=0;
			procID_gem=0;
			mpid_gem=0;
			pid_gem=0;
		//	process_tree_solid_gem(tree_solid_gem,totEdep_gem1_gas,totEdep_gem2_gas,totEdep_gem3_gas,totEdep_gem4_gas,totEdep_gem1tot,totEdep_gem2tot,totEdep_gem3tot,totEdep_gem4tot, procID_gem,mpid_gem,pid_gem);
                if(Fillgem && Fillecal){
         			hhit_Egem12->Fill(log10(trackE_flux),rate);
         			hhit_Egem12_test->Fill(log10(trackE_flux_gem2),rate);
		                vertexZ_vs_vertexR_gem12_test_hist->Fill(hit_vz_max_gem2,hit_vr_max_gem2,rate);
		                vertexZ_vs_vertexR_gem12_hist->Fill(hit_vz_max,hit_vr_max,rate);
                }
		if(Fillgem){
                  if(trackE_flux_gem2>5000){
                        //cout<<"event="<<i<<"Edep="<<log10(trackE_flux_gem2)<<endl;
			hgen_ThetaP_gem2->Fill(hit_th_max_gem2,log10(trackE_flux_gem2),rate);
			hgen_ThetaPhi_gem2->Fill(hit_th_max_gem2,hit_phi_max_gem2,rate);                  		
			hgen_PhiP_gem2->Fill(hit_phi_max_gem2,edep_6p1_max_gem2,rate);                  				
			//hgen_ThetaPhiP_gem2->Fill(hit_th_max_gem2,hit_phi_max_gem2,edep_6p1_max_gem2,rate);                  			
                        hgen_Theta_gem2->Fill(hit_th_max_gem2,rate);       
			hpf_gem2->Fill(edep_6p1_max_gem2,rate);
			hE_gem2->Fill(trackE_flux_gem2,rate);
			hhit_Egem2->Fill(log10(trackE_flux_gem2),rate);
		        vertexZ_vs_vertexR_gem2_hist->Fill(hit_vz_max_gem2,hit_vr_max_gem2,rate);
		        vertexmZ_vs_vertexmR_gem2_hist->Fill(hit_mvz_max_gem2,hit_mvr_max_gem2,rate);
		        vertexX_vs_vertexY_gem2_hist->Fill(hit_vx_max_gem2,hit_vy_max_gem2,rate);
			vertexZ_vs_E_gem2_hist->Fill(hit_mvz_max_gem2,trackE_flux_gem2,rate);
			vertexZ_vs_theta_gem2_hist->Fill(hit_mvz_max_gem2,hit_th_max_gem2,rate);
		        //vertexXYZ_gem2_hist->Fill(hit_vx_max_gem2,hit_vy_max_gem2,hit_vz_max_gem2,rate);
	                hgen_Thetavz_gem2->Fill(hit_th_max_gem2,hit_vz_max_gem2,rate);
			if(procID_flux<10){
			 hhit_Egem2_procID[procID_flux]->Fill(log10(trackE_flux_gem2),rate);
			}else{
			 hhit_Egem2_procID_other->Fill(log10(trackE_flux_gem2),rate);
			}
			if(totEdep_gem2tot>0 ){
				hhit_E_gem2->Fill(log10(trackE_flux_gem2),rate);
				hhit_Edepgem2->Fill(log10(totEdep_gem2tot),rate);
                               for(int t=0;t<6;t++){
				hhit_Edepgem2_gas[t]->Fill(log10(totEdep_gem2_gas[t]),rate);
                               }  
			if(procID_flux<10){
				hhit_Edepgem2_procID[procID_flux]->Fill(log10(totEdep_gem2tot),rate);
			}else{
				hhit_Edepgem2_procID_other->Fill(log10(totEdep_gem2tot),rate);
			}
                      }
                    }
		}
		if(Fillecal){
                   if(trackE_flux>5000){
			hgen_ThetaP_gem1->Fill(hit_th_max,log10(trackE_flux),rate);
			hgen_ThetaPhi_gem1->Fill(hit_th_max,hit_phi_max,rate);                  		
			hgen_PhiP_gem1->Fill(hit_phi_max,edep_6p1_max,rate);                  				
			//hgen_ThetaPhiP_gem1->Fill(hit_th_max,hit_phi_max,edep_6p1_max,rate);                  			
                        hgen_Theta_gem1->Fill(hit_th_max,rate);       
			hpf_gem1->Fill(edep_6p1_max,rate);
			hE_gem1->Fill(trackE_flux,rate);
			hhit_Egem1->Fill(log10(trackE_flux),rate);
		        vertexZ_vs_vertexR_hist->Fill(hit_vz_max,hit_vr_max,rate);
		        vertexmZ_vs_vertexmR_hist->Fill(hit_mvz_max,hit_mvr_max,rate);
			vertexZ_vs_E_hist->Fill(hit_mvz_max,trackE_flux,rate);
		        vertexX_vs_vertexY_hist->Fill(hit_vx_max,hit_vy_max,rate);
			vertexZ_vs_theta_hist->Fill(hit_mvz_max,hit_th_max,rate);
		        //vertexXYZ_hist->Fill(hit_vx_max,hit_vy_max,hit_vz_max,rate);
	                hgen_Thetavz_gem1->Fill(hit_th_max,hit_vz_max);
			if(procID_flux<10){
			 hhit_Egem1_procID[procID_flux]->Fill(log10(trackE_flux),rate);
			}else{
			 hhit_Egem1_procID_other->Fill(log10(trackE_flux),rate);
			}
			//cout<<"event="<<i<<"edep_6p1_max="<<edep_6p1_max<<"trackE_flux="<<trackE_flux<<"th_max="<<hit_th_max<<"phi="<<hit_phi_max<<endl;
			//if(mpid_gem==111){
			//cout<<"event="<<i<<"totE_gem="<<totEdep_gem<<"procID="<<procID_gem<<"procID_flux="<<procID_flux<<"mpid_gem="<<mpid_gem<<endl; 
			// }
			//	cout<<"event="<<i<<"totE_gem="<<totEdep_gem<<"procID_gem="<<procID_gem<<"procID_flux="<<procID_flux<<"mpid_gem="<<mpid_gem<<"mpid_flux="<<mpid_flux<<"pid_flux="<<pid_flux<<"pid_gem="<<pid_gem<<endl;
			/*if(totEdep_gem1tot>0 ){
				//cout<<"event="<<i<<"pf="<<edep_6p1_max<<endl;
				//hprocid_gem1->Fill(procID_gem,rate);
				//cout<<"event="<<i<<"totE_gem="<<totEdep_gem<<"procID_gem="<<procID_gem<<"procID_flux="<<procID_flux<<"mpid_gem="<<mpid_gem<<"mpid_flux="<<mpid_flux<<"pid_flux="<<pid_flux<<"pid_gem="<<pid_gem<<endl;
				hhit_Edepgem1->Fill(log10(totEdep_gem1tot),rate);
				hhit_E_gem1->Fill(log10(trackE_flux),rate);
				hhit_p_vs_Edepgem1->Fill(log10(totEdep_gem1tot),edep_6p1_max,rate);
                               for(int t=0;t<6;t++){
				hhit_Edepgem1_gas[t]->Fill(log10(totEdep_gem1_gas[t]),rate);
                               }  
				//if(mpid_gem==111){
				if(mpid_flux==111){
					hhit_Edepgem1_pi0->Fill(log10(totEdep_gem1tot),rate);
				}else if(abs(mpid_flux)==11){
					hhit_Edepgem1_electron->Fill(log10(totEdep_gem1tot),rate);
				}else if(mpid_flux==22){
					hhit_Edepgem1_gamma->Fill(log10(totEdep_gem1tot),rate);
				}else{
					hhit_Edepgem1_other->Fill(log10(totEdep_gem1tot),rate);
					// cout<<"event="<<i<<"totE_gem="<<totEdep_gem<<"procID="<<procID_gem<<"procID_flux="<<procID_flux<<"mpid_gem="<<mpid_gem<<endl;
				}
			}*/
			/*if(procID_flux<10){
				hhit_Edepgem1_procID[procID_flux]->Fill(log10(totEdep_gem1tot),rate);
			}else{
				hhit_Edepgem1_procID_other->Fill(log10(totEdep_gem1tot),rate);
			}*/
                         }
			}//end of Fillall
			// 		  if (Edepsc2>0.7e-3 && Eec>0.1) Is_trig=true;
			if (Eec>0.01) Is_trig=true;	  

			//-----------------------	
			//--- hgc 
			//-----------------------
			tree_solid_hgc->GetEntry(i);

			double hit_hgc[ch_hgc]={0};
			int trigger_hgc[30]={0};
			int ntrigsecs_hgc=0;
			int photon_mtid=0;
			process_tree_solid_hgc(tree_solid_hgc,hit_hgc,trigger_hgc,ntrigsecs_hgc,PMTthresh_hgc,PEthresh_hgc,ch_hgc,htime_photon,photon_mtid);

			for (Int_t j=0;j<flux_hitn->size();j++) {
				if(flux_id->at(j)==1) {
					// 		      cout << "photon_mtid " << photon_mtid << endl;		      		    
					if(flux_tid->at(j)==photon_mtid) {
						hmotherP->Fill(sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)+flux_pz->at(j)*flux_pz->at(j))/1e3,rate);
						hmother_tid->Fill(flux_tid->at(j),rate);		      		      
						hmother_pid->Fill(flux_pid->at(j),rate);
						hmother_vz->Fill(flux_vz->at(j)/10.,rate);
						hmother_vzvx->Fill(flux_vz->at(j)/10.,flux_vx->at(j)/10.,rate);		      		      

						hmother_procid->Fill(flux_procID->at(j),rate);	  		      

						hgrandma_tid->Fill(flux_mtid->at(j),rate);		      		      
						hgrandma_pid->Fill(flux_mpid->at(j),rate);	
						hgrandma_vz->Fill(flux_mvz->at(j)/10.,rate);
						hgrandma_vzvx->Fill(flux_mvz->at(j)/10.,flux_mvx->at(j)/10.,rate);		      		      
					}

					// 		    else cout << "photon_mtid " << photon_mtid << endl;
				}
			}

			// 		if(ntrigsecs_hgc){
			if(true){

				for(int sensor_id=0;sensor_id<ch_hgc;sensor_id++){
					int sensor_sec=sensor_id/sensor_hgc;		  
					int sensor_num=sensor_id%sensor_hgc;
					// 		      int sensor_x=sensor_num%sensor_trans_hgc,sensor_y=sensor_trans_hgc-1-sensor_num/sensor_trans_hgc;
					int sensor_x=sensor_num%sensor_trans_hgc,sensor_y=sensor_num/sensor_trans_hgc;		      

					if(hit_hgc[sensor_id]>0){
						sensor_good++;			
						// 			cout << sensor_num << " " << sensor_x << " " << sensor_y << endl;

						hpe_hgc[0]->Fill(sensor_num,hit_hgc[sensor_id]);	    
						hpe_hgc_2D[0]->Fill(sensor_x,sensor_y,hit_hgc[sensor_id]);			
						hhit_hgc[0]->Fill(sensor_num,hit_hgc[sensor_id]*rate);	    
						hhit_hgc_2D[0]->Fill(sensor_x,sensor_y,hit_hgc[sensor_id]*rate);
						hocc_hgc[0]->Fill(sensor_num,rate);
						hocc_hgc_2D[0]->Fill(sensor_x,sensor_y,rate);
						if (Edepsc2>0.7e-3){
							hpe_hgc[1]->Fill(sensor_num,hit_hgc[sensor_id]);	    
							hpe_hgc_2D[1]->Fill(sensor_x,sensor_y,hit_hgc[sensor_id]);			
							hhit_hgc[1]->Fill(sensor_num,hit_hgc[sensor_id]*rate);	    
							hhit_hgc_2D[1]->Fill(sensor_x,sensor_y,hit_hgc[sensor_id]*rate);
							hocc_hgc[1]->Fill(sensor_num,rate);
							hocc_hgc_2D[1]->Fill(sensor_x,sensor_y,rate);			  
						}
						// 			if (Eec>0.3){
						if (Eec>0.1){		  
							hpe_hgc[2]->Fill(sensor_num,hit_hgc[sensor_id]);	    
							hpe_hgc_2D[2]->Fill(sensor_x,sensor_y,hit_hgc[sensor_id]);			
							hhit_hgc[2]->Fill(sensor_num,hit_hgc[sensor_id]*rate);	    
							hhit_hgc_2D[2]->Fill(sensor_x,sensor_y,hit_hgc[sensor_id]*rate);
							hocc_hgc[2]->Fill(sensor_num,rate);
							hocc_hgc_2D[2]->Fill(sensor_x,sensor_y,rate);			  
						}	
						// 			if (Edepsc2>0.7e-3 && Eec>0.3){
						if (Edepsc2>0.7e-3 && Eec>0.1){
							hpe_hgc[3]->Fill(sensor_num,hit_hgc[sensor_id]);	    
							hpe_hgc_2D[3]->Fill(sensor_x,sensor_y,hit_hgc[sensor_id]);			
							hhit_hgc[3]->Fill(sensor_num,hit_hgc[sensor_id]*rate);	    
							hhit_hgc_2D[3]->Fill(sensor_x,sensor_y,hit_hgc[sensor_id]*rate);
							hocc_hgc[3]->Fill(sensor_num,rate);
							hocc_hgc_2D[3]->Fill(sensor_x,sensor_y,rate);			  
						}			    
					}	

					}		

					} //pass hgc trigger in offline		

					// 		if (1<=sec_hgc && sec_hgc<=30){
					// 		    int this_sec=sec_hgc;
					// 		    int last_sec=-1,next_sec=-1;
					// 		    if (this_sec==1) {last_sec=30;next_sec=2;}
					// 		    else if (this_sec==30) {last_sec=29;next_sec=1;}
					// 		    else {last_sec=this_sec-1;next_sec=this_sec+1;}		    		  
					// 		  double npe_hgc=0;
					// 		  for(int sensor_id=0;sensor_id<16;sensor_id++) npe_hgc += hit_hgc[16*(sec_hgc-1)+sensor_id];
					// 		  for(int sensor_id=0;sensor_id<16;sensor_id++) npe_hgc += hit_hgc[16*(last_sec-1)+sensor_id];
					// 		  for(int sensor_id=0;sensor_id<16;sensor_id++) npe_hgc += hit_hgc[16*(next_sec-1)+sensor_id];

					npe_hgc_total=0;
					npe_hgc_total_trigged=0;		  
					for(int sensor_id=0;sensor_id<ch_hgc;sensor_id++) {	
						if (hit_hgc[sensor_id]>0){
							// 		      cout << "" << i << " hgc sensor_id " << sensor_id << " npe " << hit_hgc[sensor_id] << endl;
							npe_hgc_total += hit_hgc[sensor_id];  

							if (Is_trig) npe_hgc_total_trigged += hit_hgc[sensor_id];  		      

							// 		      if(sensor_id>=16) cout << "why " << sensor_id << endl;
							// 		      npe_hgc[sensor_id] += hit_hgc[sensor_id];
							// 		      npe_hgc[sensor_id]=1;
						}
					}

					if (npe_hgc_total>0) {		  
						// 		  if (npe_hgc_total>0 && Is_trig) {
						event_good++;

						hnpe_hgc_count[0]->Fill(npe_hgc_total);		    
						hnpe_hgc[0]->Fill(npe_hgc_total,rate);
						for(int sensor_id=0;sensor_id<sensor_hgc;sensor_id++) {	
							if (hit_hgc[sensor_id]>0) {
								hnpe_sensor_hgc_count[0][sensor_id]->Fill(hit_hgc[sensor_id]);		    
								hnpe_sensor_hgc[0][sensor_id]->Fill(hit_hgc[sensor_id],rate);		    
							}
						}

						hnpe_nsensor_hgc_count[0]->Fill(npe_hgc_total,trigger_hgc[0]);		    
						hnpe_nsensor_hgc[0]->Fill(npe_hgc_total,trigger_hgc[0],rate);		    
						if (1<=trigger_hgc[0] && trigger_hgc[0]<=sensor_hgc){
							hnpe_hgc_cut[trigger_hgc[0]-1][0]->Fill(npe_hgc_total,rate);
						}
						else cout << "wrong trigger_hgc[0] " << trigger_hgc[0] << endl;
					}
					if (npe_hgc_total_trigged>0) {
						event_trig_good++;

						hnpe_hgc_count[1]->Fill(npe_hgc_total_trigged);		    
						hnpe_hgc[1]->Fill(npe_hgc_total_trigged,rate);	
						for(int sensor_id=0;sensor_id<sensor_hgc;sensor_id++) {	
							if (hit_hgc[sensor_id]>0) {		      
								hnpe_sensor_hgc_count[1][sensor_id]->Fill(hit_hgc[sensor_id]);		    
								hnpe_sensor_hgc[1][sensor_id]->Fill(hit_hgc[sensor_id],rate);		    
							}
						}		    

						hnpe_nsensor_hgc_count[1]->Fill(npe_hgc_total_trigged,trigger_hgc[0]);		    
						hnpe_nsensor_hgc[1]->Fill(npe_hgc_total_trigged,trigger_hgc[0],rate);		    		    
						if (1<=trigger_hgc[0] && trigger_hgc[0]<=sensor_hgc){
							hnpe_hgc_cut[trigger_hgc[0]-1][1]->Fill(npe_hgc_total_trigged,rate);
						}
						else cout << "wrong trigger_hgc[0] " << trigger_hgc[0] << endl;
					}

					// 		  if (npe_hgc_total>0) cout<<"" << i<< " npe_hgc_total " << npe_hgc_total << endl;	

					// 		  for(int sensor_id=0;sensor_id<ch_hgc;sensor_id++) cout << npe_hgc[sensor_id] << "\t";
					// 		  if (npe_hgc_total>0) mlptree_hgc->Fill();

					// 		if (-365< vz_gen/10. && vz_gen/10. < -335){
					if (7<=theta_gen && theta_gen <=15){ //has to cut to print(-1)=0 !!!!!
						if (2500<=p_gen && theta_gen <=7500){	//has to cut to print(-1)=0	  

							int index_mom=int((p_gen/1e3-2.5)/0.5);  //int(-1)=0 Warning !!!!!!!!!!!!!!!!!!
							if (0<=index_mom && index_mom<10){
								// 		    hnpe_hgc->Fill(npe_hgc_total*0.5);
								hnpe_hgc_mom[index_mom]->Fill(npe_hgc_total*0.5);
								int index_theta=int((theta_gen-7));    //int(-1)=0 Warning !!!!!!!!!!!!!!!!!!
								if (0<=index_theta && index_theta<10){
									hnpe_hgc_mom_theta[index_mom][index_theta]->Fill(npe_hgc_total*0.5);	
								}
							}
						}
					}
					// process ec
					tree_solid_ec->GetEntry(i);
					tree_solid_ec_ps->GetEntry(i);

					double Eend_ec_sum=0;
					double Eend_ec_ps_sum=0;	
					double Eend_ec[4]={0};
					double Eend_ec_ps[4]={0};	

					process_tree_solid_ec(tree_solid_ec,tree_solid_ec_ps,Eend_ec_sum,Eend_ec_ps_sum,Eend_ec,Eend_ec_ps);
					if(Eend_ec_ps_sum>0){
						//   cout<<"Edep="<<Eend_ec<<"Eend_ec_ps="<<Eend_ec_ps<<"rate="<<rate<<endl;

						hec_Eend_2D->Fill(Eend_ec_sum,Eend_ec_ps_sum);
						hec_Eend_shower->Fill(Eend_ec_sum,rate); 
						hec_Eend_preshower->Fill(Eend_ec_ps_sum,rate); 
					}
					// process spd
					tree_solid_spd->GetEntry(i);

		                        double Edep_sc1=0, Edep_sc2=0, Edep_sc3=0, Edep_sc4=0, Edep_spd1=0, Edep_spd2=0;
		                        process_tree_solid_spd_simple(tree_solid_spd,Edep_sc1,Edep_sc2,Edep_sc3,Edep_sc4,Edep_spd1,Edep_spd2);
					//hhit_Edepsc1->Fill(Edep_sc1,rate);
					hhit_Edepsc2->Fill(Edep_sc2,rate);
					hhit_Edepspd1->Fill(Edep_spd1,rate);
					hhit_Edepspd2->Fill(Edep_spd2,rate);

					} //end loop


					cout <<" sensor_good " << sensor_good << endl;
					cout <<" event_good " << event_good << endl;
					cout <<" event_trig_good " << event_trig_good << endl;

					//do outputs

					outputfile->Write();	
					outputfile->Flush();
				}
