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

using namespace std;

#include "analysis_tree_solid_hgc.C"
#include "analysis_tree_solid_ec.C"
#include "analysis_tree_solid_spdsurvey.C"
#include "analysis_tree_solid_gemsurvey.C"
#define MAX_CLUSTERS_PER_PLANE 2000
#define MAX_CHANNEL 16
// some numbers to be hard coded 
// make sure they are correct while using this script
//################################################################################################################################################## 

const double DEG=180./3.1415926;   //rad to degree

//#####################################################################################################################################################

//input:
//    infile: the path of input root file from GEMC_SOLID
//    numberofFile: how many number of files in the infile, usually 1.0E4 events per file,
//                  for beam on target root tree, 1.0E9 corresponds to 80 triggers, use 80 for it
//    key:  the string used to tell what kind of run it is
//    evgen: event type, 0 is beam on target, 1 is eDIS, 2 is eAll, 3 is bggen, 4 is even file 
//int fileReducer_beamtest_gem_survey(string inputfile_name,int numberOfFile=1, double event_actual=1, int evgen=1){
//int fileReducer_beamtest_gem_survey(int numberOfFile=1, double event_actual=1, int evgen=1){
int fileReducer_beamtest_gem_survey(string inputfile_name,int numberOfFile=1, double event_actual=1, int evgen=1){
	char the_filename[500];
	sprintf(the_filename, "%s",inputfile_name.substr(0,inputfile_name.rfind(".")).c_str());
	//TFile* outFile = new TFile(Form("%s_reduce_tree_analysis.root",the_filename), "RECREATE");
	TFile* outFile = new TFile(Form("%s_reduce_tree_analysis_2022.root",the_filename), "RECREATE");
        std::map<int,double> pidmass;
 const int t=1;
       // TFile *file[t];
  TTree *tree_generated;
  TTree *tree_flux;
  TTree *tree_solid_gem;
  TTree *tree_header;
  TTree *tree_solid_ec;
  TTree *tree_solid_ec_ps;
  TTree *tree_solid_hgc;
  TTree *tree_solid_spd;
	TTree* outTree = new TTree("T", "HallC beam test simulation tree");
	TFile *file=new TFile(inputfile_name.c_str());
//	ofstream outfile1(Form("%s_output.csv",the_filename));
	cout<<"numberOfFile="<<numberOfFile<<"event_actual="<<event_actual<<"evgen="<<evgen<<endl;
	//const int ch_hgc=17;	//quad readout
	const int ch_hgc=480;	//quad readout
	const double PEthresh_hgc=1; //hgc pe threshold for each pmt
	const double PMTthresh_hgc=2; //hgc pmt threshold, at least 2pmts are fired in each sector
	Float_t npe_hgc_total=0,npe_hgc_total_trigged=0;
	float px_gen = 0;
	float py_gen = 0;
	float pz_gen = 0;
	float vx_gen = 0;
	float vy_gen = 0;
	float vz_gen = 0;
	int pid_gen = 0;

	float p_gen=0, theta_gen=0, phi_gen=0;
  pidmass[111]=134.9766/1;//GeV pi0
  pidmass[211]=139.57018/1;//GeV pi-
  pidmass[2212]=938.272/1;//GeV proton
  pidmass[2112]=939.565/1;//GeV neutron
  pidmass[11]=0.511/1;//GeV electron
  pidmass[22]=0.0;//GeV photon
  pidmass[3112]=1197.449/1;//GeV sigma-
  pidmass[3122]=1115.683/1;//GeV lamda
  pidmass[3212]=1192.642/1;//GeV sigma0 
  pidmass[3222]=1189.37/1;//GeV sgima+
  pidmass[130]=497.648/1;//GeV kaon0L
  pidmass[221]=547.862/1;//GeV eta 
  pidmass[310]=497.648/1;//GeV kaon0S
  pidmass[321]=493.667/1;//GeV kaon+
  
  pidmass[-3112]=1197.449/1;//GeV
  pidmass[-3122]=1115.683/1;//GeV
  pidmass[-3212]=1192.642/1;//GeV
  pidmass[-3222]=1189.37/1;//GeV
  pidmass[-3312]=1321.71/1;//GeV
  pidmass[-3322]=1314.86/1;//GeV
  pidmass[-2212]=938.272/1;//GeV
  pidmass[-2112]=939.565/1;//GeV
  
  pidmass[-321]=493.667/1;//GeV
  pidmass[-211]=139.57018/1;//GeV
  pidmass[-11]=0.511/1;//GeV

	float rate = 0;
	float Q2 = 0;
	float rateRad = 0;
	float Npesum=0;
        float Cer[MAX_CHANNEL];
	int ecN=0;
	float PreShP,PreShP_e,PreShPx,PreShPy,PreShPz,PreShSum,PreShE, PreShEkmax, PreSh_l, PreSh_r, PreSh_t,PreShthetamax,GEM00theta;
	//  float ShP,ShPx,ShPy,ShPz;
	float ShowerSum,GEM00E, Shower_l, Shower_r, Shower_t;
	float LASPD_Eendsum, SPD_Eendsum, SC_A_Eendsum, SC_D_Eendsum, SC_C_Eendsum,SC_B_Eendsum;
	float LASPD_Eend, SPD_Eend, SC_A_Eend, SC_D_Eend, SC_C_Eend,SC_B_Eend;
	float SC_A_P;
	float SC_D_P;
	float SC_C_P;
	float SC_B_P;
	float SPD_P;
	float LASPD_P;
	int GEM00_n=0,GEM10_n=0,GEM01_n=0,GEM11_n=0;
	int SC_A_n=0,SC_B_n=0,SC_D_n=0, PreSh_n=0, Sh_n=0;
	//int Cer_n;
	int GEM00_np=0,GEM10_np=0,GEM01_np=0,GEM11_np=0;
	float GEM00_Edep,GEM10_Edep,GEM00_Etot,GEM10_Etot;
	float GEM01_Edep,GEM11_Edep,GEM01_Etot,GEM11_Etot;
	float GEM00_Edep2,GEM10_Edep2;
	float GEM00_Edep3,GEM10_Edep3;
	float GEM01_Edep2,GEM11_Edep2;
	float GEM01_Edep3,GEM11_Edep3;
	float GEM00_tid1x,GEM00_tid1y;
	float GEM10_tid1x,GEM01_tid1y;
	float GEM01_tid1x,GEM10_tid1y;
	float GEM11_tid1x,GEM11_tid1y;
	float GEM00_p,GEM10_p,GEM01_p,GEM11_p;
	float GEM00_thetamax,GEM10_thetamax,GEM01_thetamax,GEM11_thetamax;
	float GEM00_vzmax,GEM10_vzmax,GEM01_vzmax,GEM11_vzmax;
	float GEM00_vxmax,GEM10_vxmax,GEM01_vxmax,GEM11_vxmax;
	float GEM00_vymax,GEM10_vymax,GEM01_vymax,GEM11_vymax;
	float GEM00_x[MAX_CLUSTERS_PER_PLANE],GEM00_y[MAX_CLUSTERS_PER_PLANE];
	float GEM10_x[MAX_CLUSTERS_PER_PLANE],GEM10_y[MAX_CLUSTERS_PER_PLANE];
	float GEM01_x[MAX_CLUSTERS_PER_PLANE],GEM01_y[MAX_CLUSTERS_PER_PLANE];
	float GEM11_x[MAX_CLUSTERS_PER_PLANE],GEM11_y[MAX_CLUSTERS_PER_PLANE];
	float GEM00_vx[MAX_CLUSTERS_PER_PLANE],GEM00_vy[MAX_CLUSTERS_PER_PLANE];
	float GEM10_vx[MAX_CLUSTERS_PER_PLANE],GEM10_vy[MAX_CLUSTERS_PER_PLANE];
	float GEM01_vx[MAX_CLUSTERS_PER_PLANE],GEM01_vy[MAX_CLUSTERS_PER_PLANE];
	float GEM11_vx[MAX_CLUSTERS_PER_PLANE],GEM11_vy[MAX_CLUSTERS_PER_PLANE];
	float GEM00_x_max[MAX_CLUSTERS_PER_PLANE],GEM00_y_max[MAX_CLUSTERS_PER_PLANE];
	float GEM10_x_max[MAX_CLUSTERS_PER_PLANE],GEM10_y_max[MAX_CLUSTERS_PER_PLANE];
	float GEM01_x_max[MAX_CLUSTERS_PER_PLANE],GEM01_y_max[MAX_CLUSTERS_PER_PLANE];
	float GEM11_x_max[MAX_CLUSTERS_PER_PLANE],GEM11_y_max[MAX_CLUSTERS_PER_PLANE];
	int GEM00_pid[MAX_CLUSTERS_PER_PLANE],GEM01_pid[MAX_CLUSTERS_PER_PLANE],GEM10_pid[MAX_CLUSTERS_PER_PLANE],GEM11_pid[MAX_CLUSTERS_PER_PLANE];
	int GEM00_tid[MAX_CLUSTERS_PER_PLANE],GEM01_tid[MAX_CLUSTERS_PER_PLANE],GEM10_tid[MAX_CLUSTERS_PER_PLANE],GEM11_tid[MAX_CLUSTERS_PER_PLANE];
	int GEM00_mtid[MAX_CLUSTERS_PER_PLANE],GEM01_mtid[MAX_CLUSTERS_PER_PLANE],GEM10_mtid[MAX_CLUSTERS_PER_PLANE],GEM11_mtid[MAX_CLUSTERS_PER_PLANE];
	float GEM00_mvz[MAX_CLUSTERS_PER_PLANE],GEM01_mvz[MAX_CLUSTERS_PER_PLANE],GEM10_mvz[MAX_CLUSTERS_PER_PLANE],GEM11_mvz[MAX_CLUSTERS_PER_PLANE];
	float GEM00_mvx[MAX_CLUSTERS_PER_PLANE],GEM01_mvx[MAX_CLUSTERS_PER_PLANE],GEM10_mvx[MAX_CLUSTERS_PER_PLANE],GEM11_mvx[MAX_CLUSTERS_PER_PLANE];
	float GEM00_mvy[MAX_CLUSTERS_PER_PLANE],GEM01_mvy[MAX_CLUSTERS_PER_PLANE],GEM10_mvy[MAX_CLUSTERS_PER_PLANE],GEM11_mvy[MAX_CLUSTERS_PER_PLANE];
	float GEM00_fvz[MAX_CLUSTERS_PER_PLANE],GEM01_fvz[MAX_CLUSTERS_PER_PLANE],GEM10_fvz[MAX_CLUSTERS_PER_PLANE],GEM11_fvz[MAX_CLUSTERS_PER_PLANE];
	float GEM00_fvx[MAX_CLUSTERS_PER_PLANE],GEM01_fvx[MAX_CLUSTERS_PER_PLANE],GEM10_fvx[MAX_CLUSTERS_PER_PLANE],GEM11_fvx[MAX_CLUSTERS_PER_PLANE];
	float GEM00_fvy[MAX_CLUSTERS_PER_PLANE],GEM01_fvy[MAX_CLUSTERS_PER_PLANE],GEM10_fvy[MAX_CLUSTERS_PER_PLANE],GEM11_fvy[MAX_CLUSTERS_PER_PLANE];
	float GEM00_Ek[MAX_CLUSTERS_PER_PLANE],GEM01_Ek[MAX_CLUSTERS_PER_PLANE],GEM10_Ek[MAX_CLUSTERS_PER_PLANE],GEM11_Ek[MAX_CLUSTERS_PER_PLANE];
	float GEM00_theta[MAX_CLUSTERS_PER_PLANE],GEM01_theta[MAX_CLUSTERS_PER_PLANE],GEM10_theta[MAX_CLUSTERS_PER_PLANE],GEM11_theta[MAX_CLUSTERS_PER_PLANE];
	float SC_A_mvz[MAX_CLUSTERS_PER_PLANE],SC_D_mvz[MAX_CLUSTERS_PER_PLANE], SC_B_mvz[MAX_CLUSTERS_PER_PLANE];
	float SC_A_mvx[MAX_CLUSTERS_PER_PLANE],SC_D_mvx[MAX_CLUSTERS_PER_PLANE], SC_B_mvx[MAX_CLUSTERS_PER_PLANE];
	float SC_A_mvy[MAX_CLUSTERS_PER_PLANE],SC_D_mvy[MAX_CLUSTERS_PER_PLANE], SC_B_mvy[MAX_CLUSTERS_PER_PLANE];
	float SC_A_fvz[MAX_CLUSTERS_PER_PLANE],SC_D_fvz[MAX_CLUSTERS_PER_PLANE], SC_B_fvz[MAX_CLUSTERS_PER_PLANE];
	float SC_A_fvx[MAX_CLUSTERS_PER_PLANE],SC_D_fvx[MAX_CLUSTERS_PER_PLANE], SC_B_fvx[MAX_CLUSTERS_PER_PLANE];
	float SC_A_fvy[MAX_CLUSTERS_PER_PLANE],SC_D_fvy[MAX_CLUSTERS_PER_PLANE], SC_B_fvy[MAX_CLUSTERS_PER_PLANE];
	//int SC_A_pid[MAX_CLUSTERS_PER_PLANE],SC_D_pid[MAX_CLUSTERS_PER_PLANE],SC_B_pid[MAX_CLUSTERS_PER_PLANE];
	//int SC_A_tid[MAX_CLUSTERS_PER_PLANE],SC_D_tid[MAX_CLUSTERS_PER_PLANE],SC_B_tid[MAX_CLUSTERS_PER_PLANE];
	//int SC_A_mtid[MAX_CLUSTERS_PER_PLANE],SC_D_mtid[MAX_CLUSTERS_PER_PLANE],SC_B_mtid[MAX_CLUSTERS_PER_PLANE];
	float SC_A_Ek[MAX_CLUSTERS_PER_PLANE],SC_D_Ek[MAX_CLUSTERS_PER_PLANE],SC_B_Ek[MAX_CLUSTERS_PER_PLANE];
	float SC_A_theta[MAX_CLUSTERS_PER_PLANE],SC_D_theta[MAX_CLUSTERS_PER_PLANE],SC_B_theta[MAX_CLUSTERS_PER_PLANE];
	float SC_A_z[MAX_CLUSTERS_PER_PLANE],SC_D_z[MAX_CLUSTERS_PER_PLANE], SC_B_z[MAX_CLUSTERS_PER_PLANE];
	float SC_A_x[MAX_CLUSTERS_PER_PLANE],SC_D_x[MAX_CLUSTERS_PER_PLANE], SC_B_x[MAX_CLUSTERS_PER_PLANE];
	float SC_A_y[MAX_CLUSTERS_PER_PLANE],SC_D_y[MAX_CLUSTERS_PER_PLANE], SC_B_y[MAX_CLUSTERS_PER_PLANE];
	//float PreShEk[MAX_CLUSTERS_PER_PLANE], PreShtheta[MAX_CLUSTERS_PER_PLANE];
	int SC_A_pid,SC_D_pid,SC_B_pid;
	int SC_A_tid,SC_D_tid,SC_B_tid;
	int SC_A_mtid,SC_D_mtid,SC_B_mtid;
	int GEM00_pidmax,GEM01_pidmax,GEM10_pidmax, GEM11_pidmax;
	int GEM00_tidmax,GEM01_tidmax,GEM10_tidmax, GEM11_tidmax;
	int GEM00_mtidmax,GEM01_mtidmax,GEM10_mtidmax, GEM11_mtidmax;

	outTree->Branch("rate",       &rate,       "rate/F"      ); //vx at vertex
	outTree->Branch("Q2",       &Q2,       "Q2/F"      ); //vx at vertex
	outTree->Branch("vx",       &vx_gen,       "vx/F"      ); //vx at vertex
	outTree->Branch("vy",       &vy_gen,       "vy/F"      ); //vy at vertex
	outTree->Branch("vz",       &vz_gen,       "vz/F"      ); //vz at vertex
	outTree->Branch("px",       &px_gen,       "px/F"      ); //px at vertex
	outTree->Branch("py",       &py_gen,       "py/F"      ); //py at vertex
	outTree->Branch("pz",       &pz_gen,       "pz/F"      ); //pz at vertex
	outTree->Branch("p",        &p_gen,        "p/F"       ); //ptot at vertex
	outTree->Branch("theta",        &theta_gen,        "theta/F"       ); //ptot at vertex
	outTree->Branch("phi",        &phi_gen,        "phi/F"       ); //ptot at vertex
	outTree->Branch("pid",      &pid_gen,        "pid/I"       ); //ptot at vertex
	// preshower tree
	//outTree->Branch("PreSh_n",      &PreSh_n,   "PreSh_n/I"    ); //total hits on the virtual plane of GEM00 
	outTree->Branch("PreShP",      &PreShP,   "PreShP/F"    ); //momentum hit on the virtual plane of presh 
	outTree->Branch("PreShP_e",      &PreShP_e,   "PreShP_e/F"    ); //momentum hit on the virtual plane of presh 
	outTree->Branch("PreShPx",      &PreShPx,   "PreShPx/F"    ); //momentum px hit on the virtual plane of presh
	outTree->Branch("PreShPy",      &PreShPy,   "PreShPy/F"    ); //momentum py hit on the virtual plane of presh
	outTree->Branch("PreShPz",      &PreShPz,   "PreShPz/F"    ); //momentum pz hit on the virtual plane of presh
	//outTree->Branch("PreShtheta",      &PreShtheta[0],   "PreShtheta[PreSh_n]/F"    ); //momentum pz hit on the virtual plane of presh
	//outTree->Branch("PreShEk",      &PreShEk[0],   "PreShEk[PreSh_n]/F"    ); //momentum pz hit on the virtual plane of presh
	//outTree->Branch("PreShthetamax",      &PreShthetamax,   "PreShthetamax/F"    ); //momentum pz hit on the virtual plane of presh
	//outTree->Branch("PreShEkmax",      &PreShEk,   "PreShEkmax/F"    ); //momentum pz hit on the virtual plane of presh


	outTree->Branch("GEM00theta",      &GEM00theta,   "GEM00theta/F"    ); //momentum pz hit on the virtual plane of presh
	outTree->Branch("PreShSum",      &PreShSum,   "PreShSum/F"    ); //Sum of the deposit energy in three preshower modules
	outTree->Branch("PreShE",      &PreShE,   "PreShE/F"    ); //Sum of the hit energy in three preshower modules
	outTree->Branch("PreSh_l",      &PreSh_l,   "PreSh_l/F"    ); //Deposit energy in the left preshower module
	outTree->Branch("PreSh_r",      &PreSh_r,   "PreSh_r/F"    ); //Deposit energy in the right preshower module
	outTree->Branch("PreSh_t",      &PreSh_t,   "PreSh_t/F"    ); //Deposit energy in the top preshower module
	// shower tree
	outTree->Branch("ShowerSum",      &ShowerSum,   "ShowerSum/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("Shower_l",      &Shower_l,   "Shower_l/F"    ); //Deposit energy in the left shower module
	outTree->Branch("Shower_r",      &Shower_r,   "Shower_r/F"    ); //Deposit energy in the right shower module
	outTree->Branch("Shower_t",      &Shower_t,   "Shower_t/F"    ); //Deposit energy in the top shower module
	outTree->Branch("SC_A_n",      &SC_A_n,   "SC_A_n/I"    ); //total hits on the virtual plane of GEM00 
	outTree->Branch("SC_A_pid", &SC_A_pid,"SC_A_pid/I");// local x of GEM00
	outTree->Branch("SC_A_tid", &SC_A_tid,"SC_A_tid/I");// local x of GEM00
	outTree->Branch("SC_A_mtid", &SC_A_mtid,"SC_A_mtid/I");// local x of GEM00
	outTree->Branch("SC_A_x", &SC_A_x[0],"SC_A_x[SC_A_n]/F");// vertex x of GEM10
	outTree->Branch("SC_A_y", &SC_A_y[0],"SC_A_y[SC_A_n]/F");// vertex x of GEM10
	outTree->Branch("SC_A_z", &SC_A_z[0],"SC_A_z[SC_A_n]/F");// vertex x of GEM10
	outTree->Branch("SC_A_fvx", &SC_A_fvx[0],"SC_A_fvx[SC_A_n]/F");// vertex x of GEM10
	outTree->Branch("SC_A_fvy", &SC_A_fvy[0],"SC_A_fvy[SC_A_n]/F");// vertex x of GEM10
	outTree->Branch("SC_A_fvz", &SC_A_fvz[0],"SC_A_fvz[SC_A_n]/F");// vertex x of GEM10
	outTree->Branch("SC_A_mvx", &SC_A_mvx[0],"SC_A_mvx[SC_A_n]/F");// vertex x of GEM10
	outTree->Branch("SC_A_mvy", &SC_A_mvy[0],"SC_A_mvy[SC_A_n]/F");// vertex x of GEM10
	outTree->Branch("SC_A_mvz", &SC_A_mvz[0],"SC_A_mvz[SC_A_n]/F");// vertex x of GEM10
	outTree->Branch("SC_A_theta", &SC_A_theta[0],"SC_A_theta[SC_A_n]/F");// vertex x of GEM10
	outTree->Branch("SC_A_Ek", &SC_A_Ek[0],"SC_A_Ek[SC_A_n]/F");// Deposit energy of GEM00
	outTree->Branch("SC_A_P",      &SC_A_P,   "SC_A_P/F"    ); //momentum hit on the virtual plane of SC_A
	outTree->Branch("SC_A_Eendsum",      &SC_A_Eendsum,   "SC_A_Eendsum/F"    ); //total Eendosit energy in the SC_A
	outTree->Branch("SC_A_Eend",      &SC_A_Eend,   "SC_A_Eend/F"    ); //prime partile deposit energy in the SC_A
	outTree->Branch("SC_D_n",      &SC_D_n,   "SC_D_n/I"    ); //total hits on the virtual plane of GEM00 
	outTree->Branch("SC_D_pid", &SC_D_pid,"SC_D_pid/I");// local x of GEM00
	outTree->Branch("SC_D_tid", &SC_D_tid,"SC_D_tid/I");// local x of GEM00
	outTree->Branch("SC_D_mtid", &SC_D_mtid,"SC_D_mtid/I");// local x of GEM00
	outTree->Branch("SC_D_x", &SC_D_x[0],"SC_D_x[SC_D_n]/F");// vertex x of GEM10
	outTree->Branch("SC_D_y", &SC_D_y[0],"SC_D_y[SC_D_n]/F");// vertex x of GEM10
	outTree->Branch("SC_D_z", &SC_D_z[0],"SC_D_z[SC_D_n]/F");// vertex x of GEM10
	outTree->Branch("SC_D_fvx", &SC_D_fvx[0],"SC_D_fvx[SC_D_n]/F");// vertex x of GEM10
	outTree->Branch("SC_D_fvy", &SC_D_fvy[0],"SC_D_fvy[SC_D_n]/F");// vertex x of GEM10
	outTree->Branch("SC_D_fvz", &SC_D_fvz[0],"SC_D_fvz[SC_D_n]/F");// vertex x of GEM10
	outTree->Branch("SC_D_mvx", &SC_D_mvx[0],"SC_D_mvx[SC_D_n]/F");// vertex x of GEM10
	outTree->Branch("SC_D_mvy", &SC_D_mvy[0],"SC_D_mvy[SC_D_n]/F");// vertex x of GEM10
	outTree->Branch("SC_D_mvz", &SC_D_mvz[0],"SC_D_mvz[SC_D_n]/F");// vertex x of GEM10
	outTree->Branch("SC_D_theta", &SC_D_theta[0],"SC_D_theta[SC_D_n]/F");// vertex x of GEM10
	outTree->Branch("SC_D_Ek", &SC_D_Ek[0],"SC_D_Ek[SC_D_n]/F");// Deposit energy of GEM00
	outTree->Branch("SC_D_P",      &SC_D_P,   "SC_D_P/F"    ); //momentum hit on the virtual plane of SC_D
	outTree->Branch("SC_D_Eendsum",      &SC_D_Eendsum,   "SC_D_Eendsum/F"    ); //Deposit energy in the SC_D
	outTree->Branch("SC_D_Eend",      &SC_D_Eend,   "SC_D_Eend/F"    ); //prime particle deposit energy in the SC_D
	outTree->Branch("SC_C_P",      &SC_C_P,   "SC_C_P/F"    ); //momentum hit on the virtual plane of SC_D
	outTree->Branch("SC_C_Eendsum",      &SC_C_Eendsum,   "SC_C_Eendsum/F"    ); //Deposit energy in the SC_D
	outTree->Branch("SC_C_Eend",      &SC_C_Eend,   "SC_C_Eend/F"    ); //prime particle deposit energy in the SC_D
	outTree->Branch("SC_B_n",      &SC_B_n,   "SC_B_n/I"    ); //total hits on the virtual plane of GEM00 
	outTree->Branch("SC_B_pid", &SC_B_pid,"SC_B_pid/I");// local x of GEM00
	outTree->Branch("SC_B_tid", &SC_B_tid,"SC_B_tid/I");// local x of GEM00
	outTree->Branch("SC_B_mtid", &SC_B_mtid,"SC_B_mtid/I");// local x of GEM00
	outTree->Branch("SC_B_x", &SC_B_x[0],"SC_B_x[SC_B_n]/F");// vertex x of GEM10
	outTree->Branch("SC_B_y", &SC_B_y[0],"SC_B_y[SC_B_n]/F");// vertex x of GEM10
	outTree->Branch("SC_B_z", &SC_B_z[0],"SC_B_z[SC_B_n]/F");// vertex x of GEM10
	outTree->Branch("SC_B_fvx", &SC_B_fvx[0],"SC_B_fvx[SC_B_n]/F");// vertex x of GEM10
	outTree->Branch("SC_B_fvy", &SC_B_fvy[0],"SC_B_fvy[SC_B_n]/F");// vertex x of GEM10
	outTree->Branch("SC_B_fvz", &SC_B_fvz[0],"SC_B_fvz[SC_B_n]/F");// vertex x of GEM10
	outTree->Branch("SC_B_mvx", &SC_B_mvx[0],"SC_B_mvx[SC_B_n]/F");// vertex x of GEM10
	outTree->Branch("SC_B_mvy", &SC_B_mvy[0],"SC_B_mvy[SC_B_n]/F");// vertex x of GEM10
	outTree->Branch("SC_B_mvz", &SC_B_mvz[0],"SC_B_mvz[SC_B_n]/F");// vertex x of GEM10
	outTree->Branch("SC_B_theta", &SC_B_theta[0],"SC_B_theta[SC_B_n]/F");// vertex x of GEM10
	outTree->Branch("SC_B_Ek", &SC_B_Ek[0],"SC_B_Ek[SC_B_n]/F");// Deposit energy of GEM00
	outTree->Branch("SC_B_P",      &SC_B_P,   "SC_B_P/F"    ); //momentum hit on the virtual plane of SC_C
	outTree->Branch("SC_B_Eendsum",      &SC_B_Eendsum,   "SC_B_Eendsum/F"    ); //Deposit energy in the SC_C
	outTree->Branch("SC_B_Eend",      &SC_B_Eend,   "SC_B_Eend/F"    ); //prime particle deposit energy in the SC_C
	outTree->Branch("SPD_P",      &SPD_P,   "SPD_P/F"    ); //momentum hit on the virtual plane of SPD
	outTree->Branch("SPD_Eendsum",      &SPD_Eendsum,   "SPD_Eendsum/F"    ); //Deposit energy in the SPD
	outTree->Branch("SPD_Eend",      &SPD_Eend,   "SPD_Eend/F"    ); // prime particle deposit energy in the SPD
	outTree->Branch("LASPD_P",      &LASPD_P,   "LASPD_P/F"    ); //momentum hit on the virtual plane of LASPD
	outTree->Branch("LASPD_Eendsum",      &LASPD_Eendsum,   "LASPD_Eendsum/F"    ); //Deposit energy in the LASPD
	outTree->Branch("LASPD_Eend",      &LASPD_Eend,   "LASPD_Eend/F"    ); //prime partile deposit energy in the LASPD
	outTree->Branch("GEM00_n",      &GEM00_n,   "GEM00_n/I"    ); //total hits on the virtual plane of GEM00 
	outTree->Branch("GEM00_np",      &GEM00_np,   "GEM00_np/I"    ); //prime partile index hit on the virtual plane of GEM00 
	outTree->Branch("GEM00E",      &GEM00E,   "GEM00E/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM00_thetamax",      &GEM00_thetamax,   "GEM00_thetamax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM00_vzmax",      &GEM00_vzmax,   "GEM00_vzmax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM00_vymax",      &GEM00_vymax,   "GEM00_vymax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM00_vxmax",      &GEM00_vxmax,   "GEM00_vxmax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM00_pid", &GEM00_pid[0],"GEM00_pid[GEM00_n]/I");// local x of GEM00
	outTree->Branch("GEM00_tid", &GEM00_tid[0],"GEM00_tid[GEM00_n]/I");// local x of GEM00
	outTree->Branch("GEM00_mtid", &GEM00_mtid[0],"GEM00_mtid[GEM00_n]/I");// local x of GEM00
	outTree->Branch("GEM00_pidmax", &GEM00_pidmax,"GEM00_pidmax/I");// local x of GEM00
	outTree->Branch("GEM00_tidmax", &GEM00_tidmax,"GEM00_tidmax/I");// local x of GEM00
	outTree->Branch("GEM00_mtidmax", &GEM00_mtidmax,"GEM00_mtidmax/I");// local x of GEM00
	outTree->Branch("GEM00_x", &GEM00_x[0],"GEM00_x[GEM00_n]/F");// local x of GEM00
	outTree->Branch("GEM00_y", &GEM00_y[0],"GEM00_y[GEM00_n]/F");// local y of GEM00
	outTree->Branch("GEM00_vy", &GEM00_vy[0],"GEM00_vy[GEM00_n]/F");// vertex y of GEM00
	outTree->Branch("GEM00_vx", &GEM00_vx[0],"GEM00_vx[GEM00_n]/F");// vertex x of GEM00
	outTree->Branch("GEM00_fvx", &GEM00_fvx[0],"GEM00_fvx[GEM00_n]/F");// vertex x of GEM00
	outTree->Branch("GEM00_fvy", &GEM00_fvy[0],"GEM00_fvy[GEM00_n]/F");// vertex x of GEM00
	outTree->Branch("GEM00_fvz", &GEM00_fvz[0],"GEM00_fvz[GEM00_n]/F");// vertex x of GEM00
	outTree->Branch("GEM00_mvx", &GEM00_mvx[0],"GEM00_mvx[GEM00_n]/F");// vertex x of GEM00
	outTree->Branch("GEM00_mvy", &GEM00_mvy[0],"GEM00_mvy[GEM00_n]/F");// vertex x of GEM00
	outTree->Branch("GEM00_mvz", &GEM00_mvz[0],"GEM00_mvz[GEM00_n]/F");// vertex x of GEM00
	outTree->Branch("GEM00_theta", &GEM00_theta[0],"GEM00_theta[GEM00_n]/F");// vertex x of GEM10
	outTree->Branch("GEM00_Edep", &GEM00_Edep,"GEM00_Edep/F");// Deposit energy of GEM00
	outTree->Branch("GEM00_Ek", &GEM00_Ek[0],"GEM00_Ek[GEM00_n]/F");// Deposit energy of GEM00
	outTree->Branch("GEM00_Edep2", &GEM00_Edep2,"GEM00_Edep2/F");// Deposit energy of GEM00
	outTree->Branch("GEM00_Edep3", &GEM00_Edep3,"GEM00_Edep3/F");// Deposit energy of GEM00
	outTree->Branch("GEM00_Etot", &GEM00_Etot,"GEM00_Etot/F");// Deposit energy of GEM00
	outTree->Branch("GEM00_x_max", &GEM00_x_max[0],"GEM00_x_max[GEM00_np]/F");// local x of GEM00
	outTree->Branch("GEM00_y_max", &GEM00_y_max[0],"GEM00_y_max[GEM00_np]/F");// local y of GEM00
	outTree->Branch("GEM00_p", &GEM00_p,"GEM00_p/F");// momentum in front of GEM00 vertual plane

	outTree->Branch("GEM10_n",      &GEM10_n,   "GEM10_n/I"    ); //total hits on the virtual plane of GEM00 
	outTree->Branch("GEM10_np",      &GEM10_np,   "GEM10_np/I"    ); //prime partile index hit on the virtual plane of GEM00 
	outTree->Branch("GEM10_x", &GEM10_x[0],"GEM10_x[GEM10_n]/F");// local x of GEM10
	outTree->Branch("GEM10_y", &GEM10_y[0],"GEM10_y[GEM10_n]/F");// local y of GEM10
	outTree->Branch("GEM10_vy", &GEM10_vy[0],"GEM10_vy[GEM10_n]/F");// vertex y of GEM10
	outTree->Branch("GEM10_vx", &GEM10_vx[0],"GEM10_vx[GEM10_n]/F");// vertex x of GEM10
	outTree->Branch("GEM10_fvx", &GEM10_fvx[0],"GEM10_fvx[GEM10_n]/F");// vertex x of GEM10
	outTree->Branch("GEM10_fvy", &GEM10_fvy[0],"GEM10_fvy[GEM10_n]/F");// vertex x of GEM10
	outTree->Branch("GEM10_fvz", &GEM10_fvz[0],"GEM10_fvz[GEM10_n]/F");// vertex x of GEM10
	outTree->Branch("GEM10_mvx", &GEM10_mvx[0],"GEM10_mvx[GEM10_n]/F");// vertex x of GEM10
	outTree->Branch("GEM10_mvy", &GEM10_mvy[0],"GEM10_mvy[GEM10_n]/F");// vertex x of GEM10
	outTree->Branch("GEM10_mvz", &GEM10_mvz[0],"GEM10_mvz[GEM10_n]/F");// vertex x of GEM10
	outTree->Branch("GEM10_theta", &GEM10_theta[0],"GEM10_theta[GEM10_n]/F");// vertex x of GEM10
	outTree->Branch("GEM10_thetamax",      &GEM10_thetamax,   "GEM10_thetamax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM10_vzmax",      &GEM10_vzmax,   "GEM10_vzmax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM10_vymax",      &GEM10_vymax,   "GEM10_vymax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM10_vxmax",      &GEM10_vxmax,   "GEM10_vxmax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM10_Edep", &GEM10_Edep,"GEM10_Edep/F");// Deposit energy of GEM10
	outTree->Branch("GEM10_Ek", &GEM10_Ek[0],"GEM10_Ek[GEM10_n]/F");// Deposit energy of GEM00
	outTree->Branch("GEM10_Edep2", &GEM10_Edep2,"GEM10_Edep2/F");// Deposit energy of GEM10
	outTree->Branch("GEM10_Edep3", &GEM10_Edep3,"GEM10_Edep3/F");// Deposit energy of GEM10
	outTree->Branch("GEM10_Etot", &GEM10_Etot,"GEM10_Etot/F");// Deposit energy of GEM10
	outTree->Branch("GEM10_pid", &GEM10_pid[0],"GEM10_pid[GEM10_n]/I");// local x of GEM00
	outTree->Branch("GEM10_tid", &GEM10_tid[0],"GEM10_tid[GEM10_n]/I");// local x of GEM00
	outTree->Branch("GEM10_mtid", &GEM10_mtid[0],"GEM10_mtid[GEM10_n]/I");// local x of GEM00
	outTree->Branch("GEM10_pidmax", &GEM10_pidmax,"GEM10_pidmax/I");// local x of GEM00
	outTree->Branch("GEM10_tidmax", &GEM10_tidmax,"GEM10_tidmax/I");// local x of GEM00
	outTree->Branch("GEM10_mtidmax", &GEM10_mtidmax,"GEM10_mtidmax/I");// local x of GEM00
	outTree->Branch("GEM10_x_max", &GEM10_x_max[0],"GEM10_x_max[GEM10_np]/F");// local x of GEM00
	outTree->Branch("GEM10_y_max", &GEM10_y_max[0],"GEM10_y_max[GEM10_np]/F");// local y of GEM00
	outTree->Branch("GEM10_p", &GEM10_p,"GEM10_p/F");// momentum in front of GEM10 vertual plane

	outTree->Branch("GEM01_n",      &GEM01_n,   "GEM01_n/I"    ); //total hits on the virtual plane of GEM00 
	outTree->Branch("GEM01_np",      &GEM01_np,   "GEM01_np/I"    ); //prime partile index hit on the virtual plane of GEM00 
	outTree->Branch("GEM01_x", &GEM01_x[0],"GEM01_x[GEM01_n]/F");// local x of GEM00
	outTree->Branch("GEM01_y", &GEM01_y[0],"GEM01_y[GEM01_n]/F");// local y of GEM00
	outTree->Branch("GEM01_vy", &GEM01_vy[0],"GEM01_vy[GEM01_n]/F");// vertex y of GEM00
	outTree->Branch("GEM01_vx", &GEM01_vx[0],"GEM01_vx[GEM01_n]/F");// vertex x of GEM00
	outTree->Branch("GEM01_fvx", &GEM01_fvx[0],"GEM01_fvx[GEM01_n]/F");// vertex x of GEM00
	outTree->Branch("GEM01_fvy", &GEM01_fvy[0],"GEM01_fvy[GEM01_n]/F");// vertex x of GEM00
	outTree->Branch("GEM01_fvz", &GEM01_fvz[0],"GEM01_fvz[GEM01_n]/F");// vertex x of GEM00
	outTree->Branch("GEM01_mvx", &GEM01_mvx[0],"GEM01_mvx[GEM01_n]/F");// vertex x of GEM00
	outTree->Branch("GEM01_mvy", &GEM01_mvy[0],"GEM01_mvy[GEM01_n]/F");// vertex x of GEM00
	outTree->Branch("GEM01_mvz", &GEM01_mvz[0],"GEM01_mvz[GEM01_n]/F");// vertex x of GEM00
	outTree->Branch("GEM01_theta", &GEM01_theta[0],"GEM01_theta[GEM01_n]/F");// vertex x of GEM10
	outTree->Branch("GEM01_thetamax",      &GEM01_thetamax,   "GEM01_thetamax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM01_vzmax",      &GEM01_vzmax,   "GEM01_vzmax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM01_vymax",      &GEM01_vymax,   "GEM01_vymax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM01_vxmax",      &GEM01_vxmax,   "GEM01_vxmax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM01_Edep", &GEM01_Edep,"GEM01_Edep/F");// Deposit energy of GEM00
	outTree->Branch("GEM01_Ek", &GEM01_Ek[0],"GEM01_Ek[GEM01_n]/F");// Deposit energy of GEM00
	outTree->Branch("GEM01_Edep2", &GEM01_Edep2,"GEM01_Edep2/F");// Deposit energy of GEM00
	outTree->Branch("GEM01_Edep3", &GEM01_Edep3,"GEM01_Edep3/F");// Deposit energy of GEM00
	outTree->Branch("GEM01_Etot", &GEM01_Etot,"GEM01_Etot/F");// Deposit energy of GEM00
	outTree->Branch("GEM01_pid", &GEM01_pid[0],"GEM01_pid[GEM01_n]/I");// local x of GEM00
	outTree->Branch("GEM01_tid", &GEM01_tid[0],"GEM01_tid[GEM01_n]/I");// local x of GEM00
	outTree->Branch("GEM01_mtid", &GEM01_mtid[0],"GEM01_mtid[GEM01_n]/I");// local x of GEM00
	outTree->Branch("GEM01_pidmax", &GEM01_pidmax,"GEM01_pidmax/I");// local x of GEM00
	outTree->Branch("GEM01_tidmax", &GEM01_tidmax,"GEM01_tidmax/I");// local x of GEM00
	outTree->Branch("GEM01_mtidmax", &GEM01_mtidmax,"GEM01_mtidmax/I");// local x of GEM00
	outTree->Branch("GEM01_x_max", &GEM01_x_max[0],"GEM01_x_max[GEM01_np]/F");// local x of GEM00
	outTree->Branch("GEM01_y_max", &GEM01_y_max[0],"GEM01_y_max[GEM01_np]/F");// local y of GEM00
	outTree->Branch("GEM01_p", &GEM01_p,"GEM01_p/F");// momentum in front of GEM01 vertual plane

	outTree->Branch("GEM11_n",      &GEM11_n,   "GEM11_n/I"    ); //total hits on the virtual plane of GEM00 
	outTree->Branch("GEM11_np",      &GEM11_np,   "GEM11_np/I"    ); //prime partile index hit on the virtual plane of GEM00 
	outTree->Branch("GEM11_x", &GEM11_x[0],"GEM11_x[GEM11_n]/F");// local x of GEM10
	outTree->Branch("GEM11_y", &GEM11_y[0],"GEM11_y[GEM11_n]/F");// local y of GEM10
	outTree->Branch("GEM11_vy", &GEM11_vy[0],"GEM11_vy[GEM11_n]/F");// vertex y of GEM10
	outTree->Branch("GEM11_vx", &GEM11_vx[0],"GEM11_vx[GEM11_n]/F");// vertex x of GEM10
	outTree->Branch("GEM11_fvx", &GEM11_fvx[0],"GEM11_fvx[GEM11_n]/F");// vertex x of GEM10
	outTree->Branch("GEM11_fvy", &GEM11_fvy[0],"GEM11_fvy[GEM11_n]/F");// vertex x of GEM10
	outTree->Branch("GEM11_fvz", &GEM11_fvz[0],"GEM11_fvz[GEM11_n]/F");// vertex x of GEM10
	outTree->Branch("GEM11_mvx", &GEM11_mvx[0],"GEM11_mvx[GEM11_n]/F");// vertex x of GEM10
	outTree->Branch("GEM11_mvy", &GEM11_mvy[0],"GEM11_mvy[GEM11_n]/F");// vertex x of GEM10
	outTree->Branch("GEM11_mvz", &GEM11_mvz[0],"GEM11_mvz[GEM11_n]/F");// vertex x of GEM10
	outTree->Branch("GEM11_theta", &GEM11_theta[0],"GEM11_theta[GEM11_n]/F");// vertex x of GEM10
	outTree->Branch("GEM11_thetamax",      &GEM11_thetamax,   "GEM11_thetamax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM11_vzmax",      &GEM11_vzmax,   "GEM11_vzmax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM11_vymax",      &GEM11_vymax,   "GEM11_vymax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM11_vxmax",      &GEM11_vxmax,   "GEM11_vxmax/F"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("GEM11_x_max", &GEM11_x_max[0],"GEM11_x_max[GEM11_np]/F");// local x of GEM00
	outTree->Branch("GEM11_y_max", &GEM11_y_max[0],"GEM11_y_max[GEM11_np]/F");// local y of GEM00
	outTree->Branch("GEM11_Edep", &GEM11_Edep,"GEM11_Edep/F");// Deposit energy of GEM10
	outTree->Branch("GEM11_Ek", &GEM11_Ek[0],"GEM11_Ek[GEM11_n]/F");// Deposit energy of GEM00
	outTree->Branch("GEM11_Edep2", &GEM11_Edep2,"GEM11_Edep2/F");// Deposit energy of GEM10
	outTree->Branch("GEM11_Edep3", &GEM11_Edep3,"GEM11_Edep3/F");// Deposit energy of GEM10
	outTree->Branch("GEM11_Etot", &GEM11_Etot,"GEM11_Etot/F");// Deposit energy of GEM10
	outTree->Branch("GEM11_pid", &GEM11_pid[0],"GEM11_pid[GEM11_n]/I");// local x of GEM00
	outTree->Branch("GEM11_tid", &GEM11_tid[0],"GEM11_tid[GEM11_n]/I");// local x of GEM00
	outTree->Branch("GEM11_mtid", &GEM11_mtid[0],"GEM11_mtid[GEM11_n]/I");// local x of GEM00
	outTree->Branch("GEM11_pidmax", &GEM11_pidmax,"GEM11_pidmax/I");// local x of GEM00
	outTree->Branch("GEM11_tidmax", &GEM11_tidmax,"GEM11_tidmax/I");// local x of GEM00
	outTree->Branch("GEM11_mtidmax", &GEM11_mtidmax,"GEM11_mtidmax/I");// local x of GEM00
	outTree->Branch("GEM11_p", &GEM11_p,"GEM11_p/F");// momentum in front of GEM11 vertual plane
	outTree->Branch("Npesum",      &Npesum,   "Npesum/F"    ); //Npe sum in the hgc
        outTree->Branch("Cer",&Cer[0],"Cer[16]/F");
//	outTree->Branch("Cer_n",      &Cer_n,   "Cer_n/I"    ); //total hits on the virtual plane of GEM00 
	//outTree->Branch("hit_Cer", &hit_Cer[0],"hit_Cer[Cer_n]/F");// local x of GEM10
       
	//TFile *file=new TFile(infile, "READ");
//	TFile *file=new TFile(inputfile_name.c_str());
        long int nentries;
	vector <double> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0, *var9=0,*var10=0;
	vector <int> *gen_pid=0;
	vector <double> *gen_px=0,*gen_py=0,*gen_pz=0,*gen_vx=0,*gen_vy=0,*gen_vz=0;
	vector<double> *flux_id=0,*flux_hitn=0;
	vector<double> *flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0;
	vector<double> *flux_trackE=0,*flux_totEdep=0,*flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0, *flux_avg_lz=0,*flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;

	TH1F *htime_photon=new TH1F("time_photon","time_photon;t (ns)",100,0,100);
  //for(int n=0;n<t;n++){
	//TTree *tree_header = 0;

	tree_header = (TTree*) file->Get("userHeader");
	tree_header->SetBranchAddress("userVar001",&var1);     //1
	tree_header->SetBranchAddress("userVar002",&var2);     //x
	tree_header->SetBranchAddress("userVar003",&var3);     //y
	tree_header->SetBranchAddress("userVar004",&var4);     //W
	tree_header->SetBranchAddress("userVar005",&var5);     //Q2
	tree_header->SetBranchAddress("userVar006",&var6);     //rate
	tree_header->SetBranchAddress("userVar007",&var7);     //radrate
	tree_header->SetBranchAddress("userVar008",&var8);     //Ei, incoming beam energy after energy loss????
	tree_header->SetBranchAddress("userVar009",&var9);     //Abeam
	tree_header->SetBranchAddress("userVar010",&var10);    //Abeam

	tree_generated = (TTree*) file->Get("generated");
	tree_generated->SetBranchAddress("pid",&gen_pid);   //particle ID
	tree_generated->SetBranchAddress("px",&gen_px);     //momentum of the generated particle at target
	tree_generated->SetBranchAddress("py",&gen_py);
	tree_generated->SetBranchAddress("pz",&gen_pz);
	tree_generated->SetBranchAddress("vx",&gen_vx);     //vertex of the generated particle at target
	tree_generated->SetBranchAddress("vy",&gen_vy);
	tree_generated->SetBranchAddress("vz",&gen_vz);

	tree_flux = (TTree*) file->Get("flux");
	tree_flux->SetBranchAddress("hitn",&flux_hitn);     // hit number
	tree_flux->SetBranchAddress("id",&flux_id);         //hitting detector ID
	tree_flux->SetBranchAddress("pid",&flux_pid);       //pid
	tree_flux->SetBranchAddress("mpid",&flux_mpid);     // mother pid
	tree_flux->SetBranchAddress("tid",&flux_tid);       // track id
	tree_flux->SetBranchAddress("mtid",&flux_mtid);     // mother track id
	tree_flux->SetBranchAddress("otid",&flux_otid);     // original track id
	tree_flux->SetBranchAddress("trackE",&flux_trackE);   //track energy of 1st step,  track here is G4 track
	tree_flux->SetBranchAddress("totEdep",&flux_totEdep); //totEdep in all steps, track here is G4 track
	tree_flux->SetBranchAddress("avg_x",&flux_avg_x);     //average x, weighted by energy deposition in each step
	tree_flux->SetBranchAddress("avg_y",&flux_avg_y);     //average y
	tree_flux->SetBranchAddress("avg_z",&flux_avg_z);     //average z
	tree_flux->SetBranchAddress("avg_lx",&flux_avg_lx);   // local average x
	tree_flux->SetBranchAddress("avg_ly",&flux_avg_ly);   // local average y
	tree_flux->SetBranchAddress("avg_lz",&flux_avg_lz);   // local average z
	tree_flux->SetBranchAddress("px",&flux_px);          // px of 1st step
	tree_flux->SetBranchAddress("py",&flux_py);          // px of 1st step
	tree_flux->SetBranchAddress("pz",&flux_pz);          // px of 1st step
	tree_flux->SetBranchAddress("vx",&flux_vx);          // x coordinate of 1st step
	tree_flux->SetBranchAddress("vy",&flux_vy);          // y coordinate of 1st step
	tree_flux->SetBranchAddress("vz",&flux_vz);          // z coordinate of 1st step
	tree_flux->SetBranchAddress("mvx",&flux_mvx);          // x coordinate of 1st step
	tree_flux->SetBranchAddress("mvy",&flux_mvy);          // y coordinate of 1st step
	tree_flux->SetBranchAddress("mvz",&flux_mvz);          // z coordinate of 1st step
	//information recorded by ec
	tree_solid_ec= (TTree*) file->Get("solid_ec");
	tree_solid_ec_ps= (TTree*) file->Get("solid_ec_ps");
	setup_tree_solid_ec(tree_solid_ec);	
	setup_tree_solid_ec_ps(tree_solid_ec_ps);	
	//information recorded by spd
	tree_solid_spd= (TTree*) file->Get("solid_spd");
	setup_tree_solid_spd(tree_solid_spd);	 
	//information recorded by spd
	tree_solid_gem = (TTree*) file->Get("solid_gem");
	setup_tree_solid_gem(tree_solid_gem);	
	tree_solid_hgc= (TTree*) file->Get("solid_hgc");
	setup_tree_solid_hgc(tree_solid_hgc);	
	TRandom3 rand;
	rand.SetSeed(0);

	int sensor_good=0;
	int event_good=0,event_trig_good=0;
	// 	long int N_events = (long int)tree_header->GetEntries();
	nentries = (long int)tree_generated->GetEntries();	
        printf("Entries = %li \n",nentries);

	cout << "total number of events : " << nentries << endl;	

	//----------------------------
	//      loop trees
	//---------------------------
	double Ek=0;
	double Ec=0;
	double trigger_ec=0;
	int hit_id=-1,pid_max=0,mpid_max=0;
	double px_max=0,py_max=0,pz_max=0,p_max=0,p_max_e=0,theta_max=0,theta_GEM00=0;
	double SC_A_p_max=0;
	double SC_D_p_max=0;
	double SC_C_p_max=0;
	double SC_B_p_max=0;
	double SPD_p_max=0;
	double LASPD_p_max=0;
	double GEM00_p_max=0;
	//double GEM00_x_max=0;
	//double GEM00_y_max=0;
	double GEM01_p_max=0;
	//double GEM01_x_max=0;
	//double GEM01_y_max=0;
	double GEM10_p_max=0;
	//double GEM10_x_max=0;
	//double GEM10_y_max=0;
	double GEM11_p_max=0;
	//double GEM11_x_max=0;
	//double GEM11_y_max=0;
	double Eend_ec_Esum=0;
        double Eend_ec_ps_Esum=0;
	double GEM00_Esum=0;	
	int GEM00_index_max=0;
	int GEM10_index_max=0;
        int N_preshower=0;
	int pid_gen1=0;
	double hit_th_max[12]={0};
	double hit_Ek_max[12]={0};
	double hit_vz_max[12]={0};
	double hit_mvz_max[12]={0};
	double hit_vx_max[12]={0};
	double hit_vy_max[12]={0};
	double hit_vr_max[12]={0};
	double hit_mvr_max[12]={0};
	double hit_phi_max[12]={0};
	double hit_pid_max[12]={0};
	double hit_vzmax[12]={0};
	double hit_vxmax[12]={0};
	double hit_vymax[12]={0};
	double hit_p_max[12]={0};
	double hit_tid_max[12]={0};
	double hit_mtid_max[12]={0};
	int hit_proID_max[12]={0};
	int hit_proID_max_e[12]={0};
	int hit_proID_max_gamma[12]={0};
	double E_max[12]= {0};
	double E_max_gamma[12]= {0};
	double Edep_max_gamma[12]= {0};
	double E_max_ele[12]= {0};
	double Edep_max_ele[12]= {0};
	double Edep_max[12]= {0};
	double hit_th_max_gamma[12]={0};
	double hit_phi_max_gamma[12]={0};
	double hit_vz_max_gamma[12]={0};
	double hit_mvz_max_gamma[12]={0};
	double hit_vx_max_gamma[12]={0};
	double hit_vy_max_gamma[12]={0};
	double hit_vr_max_gamma[12]={0};
	double hit_mvr_max_gamma[12]={0};
	double hit_th_max_e[12]={0};
	double hit_phi_max_e[12]={0};
	double hit_vz_max_e[12]={0};
	double hit_mvz_max_e[12]={0};
	double hit_vx_max_e[12]={0};
	double hit_vy_max_e[12]={0};
	double hit_vr_max_e[12]={0};
	double hit_mvr_max_e[12]={0};
	double hit_pf=0;
        double edep_6p1_max= 0;
		int Is_prime=0;					  
		int Is_ECback=-1;			
        double dE=0;		  
	//	double theta_gen1=0,p_gen1=0,px_gen1=0,py_gen1=0,pz_gen1=0,vx_gen1=0,vy_gen1=0,vz_gen1=0;      
	bool writeFlag = false;
	for(long int i=0;i<nentries;i++){	  		
//	for(long int i=0;i<100000;i++){	  		
		cout<<"event " << i << "\r";
		if (evgen==2){
			tree_header->GetEntry(i);
	                Q2 = var5->at(0);
			rate=var6->at(0)/numberOfFile; // new eDIS and eAll generator
		}
		else if (evgen==0) {
			//rate=80e-6/1.6e-19/event_actual;  //beamOnTarget  file		  
			//rate=2e-6/1.6e-19/event_actual;  //beamOnTarget  file I= 5 uA	 	  
			rate=40e-6/1.6e-19/event_actual;  //beamOnTarget  file I= 5 uA	 	  
		}
		else if (evgen==4) rate=1; //even event file
		else if (evgen==3){         // bggen file
			tree_header->GetEntry(i);
			rate=var10->at(0)/numberOfFile; 
		}
		else {
			cout << "Not right filemode" << endl;    
			return 0; 
		}
		tree_generated->GetEntry(i);
		for (std::size_t j=0;j<gen_pid->size();j++) {
			pid_gen= gen_pid->at(j);
			px_gen=gen_px->at(j)*0.001;
			py_gen=gen_py->at(j)*0.001;
			pz_gen=gen_pz->at(j)*0.001;
			vx_gen=gen_vx->at(j)*0.1;
			vy_gen=gen_vy->at(j)*0.1;
			vz_gen=gen_vz->at(j)*0.1;
			p_gen=sqrt(px_gen*px_gen+py_gen*py_gen+pz_gen*pz_gen);
                        theta_gen=TMath::ACos(pz_gen/p_gen)*DEG;
                        phi_gen=TMath::ATan2(py_gen,px_gen)*DEG;
		//cout<<"event="<<i<<"j="<<j<<"gen_p="<<p_gen<<endl; 
		}
		//---
		tree_flux->GetEntry(i);		  
		int sec_hgc=0;		
		int Is_trig=0;					  
		Is_prime=0;					  
		Is_ECback=-1;					  
		hit_id=-1;
		double Eec=0,Eec_photonele=0,Eec_ele=0,EdepSC_D=0,EdepSC_C=0;
		px_max = 0;
		theta_max = 0;
		theta_GEM00 = 0;
		py_max = 0;
		pz_max = 0;
		p_max = 0;
		p_max_e = 0;
		pid_max = 0;
		mpid_max = 0;
		GEM00_n=0;
		GEM10_n=0;
		GEM01_n=0;
		GEM11_n=0;
		SC_A_n=0;
		SC_B_n=0;
		SC_D_n=0;
		PreSh_n=0;
		Sh_n=0;
                edep_6p1_max=0;
                Eend_ec_ps_Esum=0;
		//Cer_n=0;
		SC_A_p_max=0;
		SC_D_p_max=0;
		SC_C_p_max=0;
		SC_B_p_max=0;
		SPD_p_max=0;
		LASPD_p_max=0;
               for(int nt=0;nt<12;nt++){
	        E_max[nt]= 0;
	        E_max_gamma[nt]= 0;
	        E_max_ele[nt]= 0;
	        Edep_max_gamma[nt]= 0;
	        Edep_max_ele[nt]= 0;
		Edep_max[nt]= 0;
		hit_th_max[nt]=0;
		hit_Ek_max[nt]=0;
		hit_pid_max[nt]=0;
		hit_vzmax[nt]=0;
		hit_vxmax[nt]=0;
		hit_vymax[nt]=0;
		hit_p_max[nt]=0;
		hit_mtid_max[nt]=0;
		hit_tid_max[nt]=0;
		hit_th_max_gamma[nt]=0;
		hit_th_max_e[nt]=0;
		hit_vz_max[nt]=0;
		hit_vz_max_gamma[nt]=0;
		hit_vz_max_e[nt]=0;
		hit_mvz_max[nt]=0;
		hit_mvz_max_gamma[nt]=0;
		hit_mvz_max_e[nt]=0;
		hit_vx_max[nt]=0;
		hit_vx_max_gamma[nt]=0;
		hit_vx_max_e[nt]=0;
		hit_vy_max[nt]=0;
		hit_vy_max_gamma[nt]=0;
		hit_vy_max_e[nt]=0;
		hit_vr_max[nt]=0;
		hit_vr_max_gamma[nt]=0;
		hit_vr_max_e[nt]=0;
		hit_mvr_max[nt]=0;
		hit_mvr_max_gamma[nt]=0;
		hit_mvr_max_e[nt]=0;
		hit_phi_max[nt]=0;
		hit_phi_max_gamma[nt]=0;
		hit_phi_max_e[nt]=0;
		hit_proID_max[nt]=0;
		hit_proID_max_gamma[nt]=0;
		hit_proID_max_e[nt]=0;
	       }
	GEM00_p_max=0;
	//GEM00_x_max=0;
	//GEM00_y_max=0;
	GEM01_p_max=0;
	//GEM01_x_max=0;
	//GEM01_y_max=0;
	GEM10_p_max=0;
	//GEM10_x_max=0;
	//GEM10_y_max=0;
	GEM11_p_max=0;
	//GEM11_x_max=0;
	//GEM11_y_max=0;
		GEM00_index_max=0;
		GEM10_index_max=0;
	 Eend_ec_Esum=0;
	 GEM00_Esum=0;	
	 GEM00_np=0;
	 GEM01_np=0;
	 GEM10_np=0;
	 GEM11_np=0;
                N_preshower=0;
              //if(Q2>0.01){
   //                            cout<<"event="<<i<<"flux_size="<<flux_hitn->size()<<endl;
		for (std::size_t j=0;j<flux_hitn->size();j++) {
     //                          cout<<"event="<<i<<"flux="<<j<<"flux_size="<<flux_hitn->size()<<"pf="<<flux_pz->at(j)<<endl;
		   if(flux_pz->at(j)>0 ){  
                      Is_prime ++;
			//check tid tid==1 prime particle
			//	if(flux_tid->at(j) !=1) continue;
			hit_pf=sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)+flux_pz->at(j)*flux_pz->at(j));  //MeV to GeV
	                double hit_th=atan2(sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)),flux_pz->at(j))*DEG;
			//double E=flux_trackE->at(j)/1e3;		  
			double E=flux_trackE->at(j);		  
			if(flux_id->at(j)==1) hit_id=0; // SC_A front 5x7 cm2
			else if(flux_id->at(j)==2) hit_id=1; // SC_D front 6.5x5.5 preshower title
			else if(flux_id->at(j)==3) hit_id=2; // EC front 
		//	else if(flux_id->at(j)==9) hit_id=9; // EC shower front
			else if(flux_id->at(j)==4) hit_id=3; // EC back 
			else if(flux_id->at(j)==5) hit_id=4; // GEM00
			else if(flux_id->at(j)==6) hit_id=5; // GEM10	  
			else if(flux_id->at(j)==7) hit_id=7; // SC4 5x10x1
			else if(flux_id->at(j)==8) hit_id=8; // LASPD	  
			else if(flux_id->at(j)==10) hit_id=6; // Cherenkov front window
			else if(flux_id->at(j)==11) hit_id=9; // SC_C 4.5x18cm2 
		//	else if(flux_id->at(j)==13) hit_id=10; // 
			else if(flux_id->at(j)==20) hit_id=10; // GEM01
			else if(flux_id->at(j)==21) hit_id=11; // GEM11
		//	else if(flux_id->at(j)==22) hit_id=13; // 
		//	else if(flux_id->at(j)==23) hit_id=14; // 
		//	else if(flux_id->at(j)==24) hit_id=15; // 
		//	else if(flux_id->at(j)==30) hit_id=16; //
			else cout << "wrong flux_id " << flux_id->at(j) << endl;
				//if(hit_id==2 ){
				//if(hit_id==2 && flux_tid->at(j)==1 && flux_mtid->at(j)==0){
				//if( flux_tid->at(j)==1 && hit_id==6){
                                
                                //Is_prime=1;
		                N_preshower ++;
				if (E >= edep_6p1_max){
					edep_6p1_max=E;
					p_max=hit_pf;
					px_max=flux_px->at(j);
					py_max=flux_py->at(j);
					pz_max=flux_pz->at(j);
                                        theta_max = hit_th;
                                        //theta_max = theta_gen;
                                        pid_max = flux_pid->at(j);
                                        mpid_max = flux_mpid->at(j);
                                 }
                                        Eend_ec_ps_Esum += E;
		        if (E >= E_max[hit_id]){
			   E_max[hit_id]=E;
                           hit_th_max[hit_id] = hit_th;
                           hit_pid_max[hit_id] = flux_pid->at(j);
                           hit_p_max[hit_id] = sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)+flux_pz->at(j)*flux_pz->at(j));
                           hit_tid_max[hit_id] = flux_tid->at(j);
                           hit_mtid_max[hit_id] = flux_mtid->at(j);
			   hit_vzmax[hit_id]=flux_vz->at(j)*0.1;
			   hit_vymax[hit_id]=flux_vy->at(j)*0.1;
			   hit_vxmax[hit_id]=flux_vx->at(j)*0.1;
                                if(flux_pid->at(j)==22){
				hit_Ek_max[hit_id]= flux_trackE->at(j);
			        }else{ 
				hit_Ek_max[hit_id]= flux_trackE->at(j)-pidmass[flux_pid->at(j)];
				}
                         }
			       //} //no tid cut 
				if(hit_id==0 ){
					SC_A_p_max=hit_pf;
				SC_A_x[SC_A_n]=flux_avg_lx->at(j)*0.1;
				SC_A_y[SC_A_n]=flux_avg_ly->at(j)*0.1;
				SC_A_z[SC_A_n]=flux_avg_lz->at(j)*0.1;
			//	SC_A_pid[SC_A_n]=flux_pid->at(j);
			//	SC_A_tid[SC_A_n]=flux_tid->at(j);
			//	SC_A_mtid[SC_A_n]=flux_mtid->at(j);
				SC_A_fvx[SC_A_n]=flux_vx->at(j)*0.1;
				SC_A_fvy[SC_A_n]=flux_vy->at(j)*0.1;
			        SC_A_fvz[SC_A_n]=flux_vz->at(j)*0.1;
				SC_A_mvx[SC_A_n]=flux_mvx->at(j)*0.1;
				SC_A_mvy[SC_A_n]=flux_mvy->at(j)*0.1;
				SC_A_mvz[SC_A_n]=flux_mvz->at(j)*0.1;
				SC_A_theta[SC_A_n]=atan2(sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)),flux_pz->at(j))*DEG;
                                if(flux_pid->at(j)==22){
				SC_A_Ek[SC_A_n]= flux_trackE->at(j);
			        }else{ 
				SC_A_Ek[SC_A_n]= flux_trackE->at(j)-pidmass[flux_pid->at(j)];
				}
				SC_A_n++;
				}
				if(hit_id==1){
					SC_D_p_max=hit_pf;
				SC_D_x[SC_D_n]=flux_avg_lx->at(j)*0.1;
				SC_D_y[SC_D_n]=flux_avg_ly->at(j)*0.1;
				SC_D_z[SC_D_n]=flux_avg_lz->at(j)*0.1;
			//	SC_D_pid[SC_D_n]=flux_pid->at(j);
			//	SC_D_tid[SC_D_n]=flux_tid->at(j);
			//	SC_D_mtid[SC_D_n]=flux_mtid->at(j);
				SC_D_fvx[SC_D_n]=flux_vx->at(j)*0.1;
				SC_D_fvy[SC_D_n]=flux_vy->at(j)*0.1;
			        SC_D_fvz[SC_D_n]=flux_vz->at(j)*0.1;
				SC_D_mvx[SC_D_n]=flux_mvx->at(j)*0.1;
				SC_D_mvy[SC_D_n]=flux_mvy->at(j)*0.1;
				SC_D_mvz[SC_D_n]=flux_mvz->at(j)*0.1;
				SC_D_theta[SC_D_n]=atan2(sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)),flux_pz->at(j))*DEG;
                                if(flux_pid->at(j)==22){
				SC_D_Ek[SC_D_n]= flux_trackE->at(j);
			        }else{ 
				SC_D_Ek[SC_D_n]= flux_trackE->at(j)-pidmass[flux_pid->at(j)];
				}
				SC_D_n++;
				}

				if(hit_id==7){
                                Is_ECback=1;
					SC_B_p_max=hit_pf;
				SC_B_x[SC_B_n]=flux_avg_lx->at(j)*0.1;
				SC_B_y[SC_B_n]=flux_avg_ly->at(j)*0.1;
				SC_B_z[SC_B_n]=flux_avg_lz->at(j)*0.1;
				//SC_B_pid[SC_B_n]=flux_pid->at(j);
				//SC_B_tid[SC_B_n]=flux_tid->at(j);
				//SC_B_mtid[SC_B_n]=flux_mtid->at(j);
				SC_B_fvx[SC_B_n]=flux_vx->at(j)*0.1;
				SC_B_fvy[SC_B_n]=flux_vy->at(j)*0.1;
			        SC_B_fvz[SC_B_n]=flux_vz->at(j)*0.1;
				SC_B_mvx[SC_B_n]=flux_mvx->at(j)*0.1;
				SC_B_mvy[SC_B_n]=flux_mvy->at(j)*0.1;
				SC_B_mvz[SC_B_n]=flux_mvz->at(j)*0.1;
				SC_B_theta[SC_B_n]=atan2(sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)),flux_pz->at(j))*DEG;
                                if(flux_pid->at(j)==22){
				SC_B_Ek[SC_B_n]= flux_trackE->at(j);
			        }else{ 
				SC_B_Ek[SC_B_n]= flux_trackE->at(j)-pidmass[flux_pid->at(j)];
				}
				SC_B_n++;
				}
				if(hit_id==9){
					SC_C_p_max=hit_pf;
				}
				//if(hit_id==7){
				//	SPD_p_max=hit_pf;
				//}
				if(hit_id==8){
					LASPD_p_max=hit_pf;
				}
				if(hit_id==4){
				//	GEM00_np=j;
                                        GEM00_Esum += E;
                                 if(flux_mtid->at(j)==0){
                                      theta_GEM00=theta_gen;
                                      GEM00_p_max=hit_pf;
	                                GEM00_x_max[GEM00_np]=flux_avg_lx->at(j)*0.1;
	                                GEM00_y_max[GEM00_np]=flux_avg_ly->at(j)*0.1;
					GEM00_np++;
                                 }
				}
				if(hit_id==5){
					//GEM10_np=j;
                                  if(flux_mtid->at(j)==0){
					GEM10_p_max=hit_pf;
	                                GEM10_x_max[GEM10_np]=flux_avg_lx->at(j)*0.1;
	                                GEM10_y_max[GEM10_np]=flux_avg_ly->at(j)*0.1;
					GEM10_np++;
                                  }
				}
				if(hit_id==10){
				//	GEM01_np=j;
                                  if(flux_mtid->at(j)==0){
					GEM01_p_max=hit_pf;
	                                GEM01_x_max[GEM01_np]=flux_avg_lx->at(j)*0.1;
	                                GEM01_y_max[GEM01_np]=flux_avg_ly->at(j)*0.1;
				        GEM01_np++;
                                  }
				}
				if(hit_id==11){
					//GEM11_np=j;
                                  if(flux_mtid->at(j)==0){
					GEM11_p_max=hit_pf;
	                                GEM11_x_max[GEM11_np]=flux_avg_lx->at(j)*0.1;
	                                GEM11_y_max[GEM11_np]=flux_avg_ly->at(j)*0.1;
				        GEM11_np++;
                                  }
				}
			//}// end tid==1
			if(hit_id==4){
			//	GEM00_thetamax = hit_th_max[4];
				GEM00_x[GEM00_n]=flux_avg_lx->at(j)*0.1;
				GEM00_y[GEM00_n]=flux_avg_ly->at(j)*0.1;
				GEM00_vx[GEM00_n]=flux_avg_x->at(j)*0.1;
				GEM00_vy[GEM00_n]=flux_avg_y->at(j)*0.1;
				GEM00_pid[GEM00_n]=flux_pid->at(j);
				GEM00_tid[GEM00_n]=flux_tid->at(j);
				GEM00_mtid[GEM00_n]=flux_mtid->at(j);
				GEM00_fvx[GEM00_n]=flux_vx->at(j)*0.1;
				GEM00_fvy[GEM00_n]=flux_vy->at(j)*0.1;
				GEM00_fvz[GEM00_n]=flux_vz->at(j)*0.1;
				GEM00_mvx[GEM00_n]=flux_mvx->at(j)*0.1;
				GEM00_mvy[GEM00_n]=flux_mvy->at(j)*0.1;
				GEM00_mvz[GEM00_n]=flux_mvz->at(j)*0.1;
				GEM00_theta[GEM00_n]=atan2(sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)),flux_pz->at(j))*DEG;
                                if(flux_pid->at(j)==22){
				GEM00_Ek[GEM00_n]= flux_trackE->at(j);
			        }else{ 
				GEM00_Ek[GEM00_n]= flux_trackE->at(j)-pidmass[flux_pid->at(j)];
				}
				GEM00_n++;
			}
			if(hit_id==5){
			//	GEM10_thetamax = hit_th_max[5];
				GEM10_x[GEM10_n]=flux_avg_lx->at(j)*0.1;
				GEM10_y[GEM10_n]=flux_avg_ly->at(j)*0.1;
				GEM10_vx[GEM10_n]=flux_avg_x->at(j)*0.1;
				GEM10_vy[GEM10_n]=flux_avg_y->at(j)*0.1;
				GEM10_pid[GEM10_n]=flux_pid->at(j);
				GEM10_tid[GEM10_n]=flux_tid->at(j);
				GEM10_mtid[GEM10_n]=flux_mtid->at(j);
				GEM10_fvx[GEM10_n]=flux_vx->at(j)*0.1;
				GEM10_fvy[GEM10_n]=flux_vy->at(j)*0.1;
				GEM10_fvz[GEM10_n]=flux_vz->at(j)*0.1;
				GEM10_mvx[GEM10_n]=flux_mvx->at(j)*0.1;
				GEM10_mvy[GEM10_n]=flux_mvy->at(j)*0.1;
				GEM10_mvz[GEM10_n]=flux_mvz->at(j)*0.1;
				GEM10_theta[GEM10_n]=atan2(sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)),flux_pz->at(j))*DEG;
                                if(flux_pid->at(j)==22){
				GEM10_Ek[GEM10_n]= flux_trackE->at(j);
			        }else{ 
				GEM10_Ek[GEM10_n]= flux_trackE->at(j)-pidmass[flux_pid->at(j)];
				}
				GEM10_n++;
			}
			if(hit_id==10){
			//	GEM01_thetamax = hit_th_max[10];
				GEM01_x[GEM01_n]=flux_avg_lx->at(j)*0.1;
				GEM01_y[GEM01_n]=flux_avg_ly->at(j)*0.1;
				GEM01_vx[GEM01_n]=flux_avg_x->at(j)*0.1;
				GEM01_vy[GEM01_n]=flux_avg_y->at(j)*0.1;
				GEM01_pid[GEM01_n]=flux_pid->at(j);
				GEM01_tid[GEM01_n]=flux_tid->at(j);
				GEM01_mtid[GEM01_n]=flux_mtid->at(j);
				GEM01_fvx[GEM01_n]=flux_vx->at(j)*0.1;
				GEM01_fvy[GEM01_n]=flux_vy->at(j)*0.1;
				GEM01_fvz[GEM01_n]=flux_vz->at(j)*0.1;
				GEM01_mvx[GEM01_n]=flux_mvx->at(j)*0.1;
				GEM01_mvy[GEM01_n]=flux_mvy->at(j)*0.1;
				GEM01_mvz[GEM01_n]=flux_mvz->at(j)*0.1;
				GEM01_theta[GEM01_n]=atan2(sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)),flux_pz->at(j))*DEG;
                                if(flux_pid->at(j)==22){
				GEM01_Ek[GEM01_n]= flux_trackE->at(j);
			        }else{ 
				GEM01_Ek[GEM01_n]= flux_trackE->at(j)-pidmass[flux_pid->at(j)];
				}
				GEM01_n++;
			}
			if(hit_id==11){
			//	GEM11_thetamax = hit_th_max[11];
				GEM11_x[GEM11_n]=flux_avg_lx->at(j)*0.1;
				GEM11_y[GEM11_n]=flux_avg_ly->at(j)*0.1;
				GEM11_vx[GEM11_n]=flux_avg_x->at(j)*0.1;
				GEM11_vy[GEM11_n]=flux_avg_y->at(j)*0.1;
				GEM11_pid[GEM11_n]=flux_pid->at(j);
				GEM11_tid[GEM11_n]=flux_tid->at(j);
				GEM11_mtid[GEM11_n]=flux_mtid->at(j);
				GEM11_fvx[GEM11_n]=flux_vx->at(j)*0.1;
				GEM11_fvy[GEM11_n]=flux_vy->at(j)*0.1;
				GEM11_fvz[GEM11_n]=flux_vz->at(j)*0.1;
				GEM11_mvx[GEM11_n]=flux_mvx->at(j)*0.1;
				GEM11_mvy[GEM11_n]=flux_mvy->at(j)*0.1;
				GEM11_mvz[GEM11_n]=flux_mvz->at(j)*0.1;
				GEM11_theta[GEM11_n]=atan2(sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)),flux_pz->at(j))*DEG;
                                if(flux_pid->at(j)==22){
				GEM11_Ek[GEM11_n]= flux_trackE->at(j);
			        }else{ 
				GEM11_Ek[GEM11_n]= flux_trackE->at(j)-pidmass[flux_pid->at(j)];
				}
				GEM11_n++;
			}
			if(hit_id==6 && abs(flux_avg_lx->at(j)*0.1)<2 && abs(flux_avg_ly->at(j)*0.1)<2){                                
				Is_trig=1;
			}
                    }//pf>0
			//cout<<"event="<<i<<"j="<<j<<" GEM00_n="<<GEM00_n<<"GEM10_n="<<GEM10_n<<endl;
		}	// end of flux		
			//cout<<"event="<<i<<" GEM00_n="<<GEM00_n<<"GEM10_n="<<GEM10_n<<endl;
                // process gem
		GEM00_p = GEM00_p_max;
		//GEM00_tid1x = GEM00_x_max;
		//GEM00_tid1y = GEM00_y_max;
		GEM10_p = GEM10_p_max;
		//GEM10_tid1x = GEM10_x_max;
		//GEM10_tid1y = GEM10_y_max;
		GEM01_p = GEM01_p_max;
		//GEM01_tid1x = GEM01_x_max;
		//GEM01_tid1y = GEM01_y_max;
		GEM11_p = GEM11_p_max;
		//GEM11_tid1x = GEM11_x_max;
		//GEM11_tid1y = GEM11_y_max;

		tree_solid_gem->GetEntry(i);
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
	//		process_tree_solid_gem(tree_solid_gem,totEdep_gem1_gas,totEdep_gem2_gas,totEdep_gem1tot,totEdep_gem2tot, procID_gem,mpid_gem,pid_gem);
			process_tree_solid_gem(tree_solid_gem,totEdep_gem1_gas,totEdep_gem2_gas,totEdep_gem3_gas,totEdep_gem4_gas,totEdep_gem1tot,totEdep_gem2tot,totEdep_gem3tot,totEdep_gem4tot, procID_gem,mpid_gem,pid_gem);
                GEM00_Edep=totEdep_gem1_gas[1];
                GEM01_Edep=totEdep_gem2_gas[1];
                GEM10_Edep=totEdep_gem3_gas[1];
                GEM11_Edep=totEdep_gem4_gas[1];
                GEM00_Etot=totEdep_gem1tot;
                GEM10_Etot=totEdep_gem2tot;
                GEM01_Etot=totEdep_gem3tot;
                GEM11_Etot=totEdep_gem4tot;
                GEM00_Edep2=totEdep_gem1_gas[2];
                GEM10_Edep2=totEdep_gem2_gas[2];
                GEM00_Edep3=totEdep_gem1_gas[3];
                GEM10_Edep3=totEdep_gem2_gas[3];
                GEM01_Edep2=totEdep_gem3_gas[2];
                GEM11_Edep2=totEdep_gem4_gas[2];
                GEM01_Edep3=totEdep_gem3_gas[3];
                GEM11_Edep3=totEdep_gem4_gas[3];
		if(GEM00_n>0){
				GEM00_thetamax = hit_th_max[4];
				GEM00_vzmax = hit_vzmax[4];
				GEM00_vymax = hit_vymax[4];
				GEM00_vxmax = hit_vxmax[4];
				GEM00_pidmax = hit_pid_max[4];
				GEM00_tidmax = hit_tid_max[4];
				GEM00_mtidmax = hit_pid_max[4];
		}
		if(GEM10_n>0){
				GEM10_thetamax = hit_th_max[5];
				GEM10_vzmax = hit_vzmax[5];
				GEM10_vymax = hit_vymax[5];
				GEM10_vxmax = hit_vxmax[5];
				GEM10_pidmax = hit_pid_max[5];
				GEM10_tidmax = hit_tid_max[5];
				GEM10_mtidmax = hit_mtid_max[5];
		}
		if(GEM01_n>0){
				GEM01_thetamax = hit_th_max[10];
				GEM01_vzmax = hit_vzmax[10];
				GEM01_vymax = hit_vymax[10];
				GEM01_vxmax = hit_vxmax[10];
				GEM01_pidmax = hit_pid_max[10];
				GEM01_tidmax = hit_tid_max[10];
				GEM01_mtidmax = hit_mtid_max[10];
	        }
		if(GEM11_n>0){
				GEM11_thetamax = hit_th_max[11];
				GEM11_vzmax = hit_vzmax[11];
				GEM11_vymax = hit_vymax[11];
				GEM11_vxmax = hit_vxmax[11];
				GEM11_pidmax = hit_pid_max[11];
				GEM11_tidmax = hit_tid_max[11];
				GEM11_mtidmax = hit_mtid_max[11];
                }
		// process ec
		tree_solid_ec->GetEntry(i);
		tree_solid_ec_ps->GetEntry(i);
                dE=gRandom->Gaus(1.0,sqrt(pow(0.04149,2)+pow(0.07938,2)/7.0));
                //dE=1.0;
		//if(hit_preshowerN>0){
		double Eend_ec_sum=0;
		double Eend_ec_ps_sum=0;	
	//	double Eend_ec_Esum=0;
	//	double Eend_ec_ps_Esum=0;	
		double Eend_ec[4]={0};
		double Eend_ec_ps[4]={0};
		//process_tree_solid_ec(tree_solid_ec[n],tree_solid_ec_ps[n],Eend_ec_sum,Eend_ec_ps_sum,Eend_ec_Esum, Eend_ec_ps_Esum,Eend_ec,Eend_ec_ps);
		process_tree_solid_ec(tree_solid_ec,tree_solid_ec_ps,Eend_ec_sum,Eend_ec_ps_sum,Eend_ec,Eend_ec_ps);
		PreShSum=Eend_ec_ps_sum;
		PreShE=Eend_ec_ps_Esum;
		PreSh_l=Eend_ec_ps[2];
		PreSh_r=Eend_ec_ps[3];
		PreSh_t=Eend_ec_ps[1];
		ShowerSum=Eend_ec_sum*dE;
		GEM00E=GEM00_Esum;
		Shower_l=Eend_ec[2]*dE;
		Shower_r=Eend_ec[3]*dE;
		Shower_t=Eend_ec[1]*dE;
		//PreShP=p_max;
		PreShP=edep_6p1_max;
		PreShPx=px_max;
		PreShPy=py_max;
		PreShPz=pz_max;
		//PreShthetamax=theta_max;
		GEM00theta=theta_GEM00;
                //if(ShowerSum>0){                
  //               cout<<"event="<<i<<"ShowerSum="<<Eend_ec_sum<<endl;
               // }
		tree_solid_spd->GetEntry(i);
		double Edep_sc1=0, Edep_sc2=0, Edep_sc3=0, Edep_sc4=0, Edep_spd1=0, Edep_spd2=0;
		process_tree_solid_spd_simple(tree_solid_spd,Edep_sc1,Edep_sc2,Edep_sc3,Edep_sc4,Edep_spd1,Edep_spd2);
		//SC_A
		SC_A_P=hit_p_max[0];
		SC_A_Eendsum = Edep_sc1;
		if(SC_A_n>0){
			SC_A_Eend = Edep_sc1;
			//cout<<"event="<<i<<"SC_A_P="<<SC_A_P<<"SC_A_Eendsum="<<SC_A_Eendsum<<endl;
	        SC_A_pid=hit_pid_max[0];
	        SC_A_tid=hit_tid_max[0];
		SC_A_mtid=hit_mtid_max[0];
		}
		//SC_D
		SC_D_P=hit_p_max[1];
		SC_D_Eendsum = Edep_sc2;
		if(SC_D_n>0){
			SC_D_Eend = Edep_sc2;
	        SC_D_pid=hit_pid_max[1];
	        SC_D_tid=hit_tid_max[1];
		SC_D_mtid=hit_mtid_max[1];
		}
                //SC_C
		SC_C_P=hit_p_max[9];
		SC_C_Eendsum = Edep_sc3;
		if(SC_C_Eendsum>0){
			SC_C_Eend = Edep_sc3;
		}
                //SC_B
		SC_B_P=hit_p_max[7];
		SC_B_Eendsum = Edep_sc4;
		if(SC_B_n>0){
			SC_B_Eend = Edep_sc4;
	        SC_B_pid=hit_pid_max[7];
	        SC_B_tid=hit_tid_max[7];
		SC_B_mtid=hit_mtid_max[7];
		}
		//SPD
		SPD_P=SPD_p_max;
		SPD_Eendsum = Edep_spd1;
		if(SPD_Eendsum>0){
			SPD_Eend = Edep_spd1;
		}
		//LASPD
		LASPD_P=LASPD_p_max;
		LASPD_Eendsum = Edep_spd2;
		if(LASPD_Eendsum>0){
			LASPD_Eend = Edep_spd2;
		}
		//--- hgc 
		//-----------------------
		tree_solid_hgc->GetEntry(i);
		double hit_hgc[ch_hgc]={0};
		int trigger_hgc[30]={0};
		int ntrigsecs_hgc=0;
		int ntrigpmts_hgc=0;
		int photon_mtid=0;
                process_tree_solid_hgc(tree_solid_hgc,hit_hgc,trigger_hgc,ntrigsecs_hgc,PMTthresh_hgc,PEthresh_hgc,ch_hgc,htime_photon,photon_mtid);
		npe_hgc_total=0;
		npe_hgc_total_trigged=0;		  
		Cer[ch_hgc]={0};
                if(PreShSum>0 || ShowerSum>0 || SC_A_Eendsum>0 || SC_B_Eendsum>0 || SC_C_Eendsum>0 || SC_D_Eendsum || SPD_Eendsum>0 || LASPD_Eendsum>0){                
		outTree->Fill();
                Is_prime=0;
             }//ShowerSum>0 cut
         // }//prime cut
	   } //end loop
        // }//file loop
	cout<<endl;
	outFile->cd();
	outTree->Write();
	outFile->Close();
        return 0;
	}
