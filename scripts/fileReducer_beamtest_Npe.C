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
#include "analysis_tree_solid_spd.C"

// some numbers to be hard coded 
// make sure they are correct while using this script
//################################################################################################################################################## 

const double DEG=180./3.1415926;   //rad to degree

//#####################################################################################################################################################

int fileReducer_beamtest_Npe(string inputfile_name,string runmode="trigger", bool Is_tellorig=false,string filetype="",bool Is_new=true){
	const int ch_hgc=16;	//quad readout
	const double PEthresh_hgc=1; //hgc pe threshold for each pmt
	const double PMTthresh_hgc=2; //hgc pmt threshold, at least 2pmts are fired in each sector
	Float_t npe_hgc_total=0,npe_hgc_total_trigged=0;

	char the_filename[500];
	sprintf(the_filename, "%s",inputfile_name.substr(0,inputfile_name.rfind(".")).c_str());
	TFile* outFile = new TFile(Form("%s_reduce_tree_Npe_test.root",the_filename), "RECREATE");
	TTree* outTree = new TTree("T", "HallC beam test simulation tree");
	//ofstream outfile1(Form("%s_output.csv",the_filename));

	double Ei = 0;
	double Q2 = 0;
	double W = 0;
	double x = 0;
	double y = 0;
	double Abeam = 0;
	double px_gen = 0;
	double py_gen = 0;
	double pz_gen = 0;
	double vx_gen = 0;
	double vy_gen = 0;
	double vz_gen = 0;
	int pid_gen = 0;
	double Npe[16];
        double Npesum=0;
	double p_gen=0, theta_gen=0, phi_gen=0;

	double rate = 0;
	double rateRad = 0;

	int ecN=0;
	double preShP,preShPx,preShPy,preShPz,preShEendSum, preShLEend, preShREend, preShTEend;
	//  double ShP,ShPx,ShPy,ShPz;
	double ShEendSum, ShLEend, ShREend, ShTEend;
	double LASPDEend, SPDEend, SC0Eend, SC1Eend;
	double SC0P,SC0Px,SC0Py,SC0Pz;
	double SC1P,SC1Px,SC1Py,SC1Pz;
	double SPDP,SPDPx,SPDPy,SPDPz;
	double LASPDP,LASPDPx,LASPDPy,LASPDPz;
	outTree->Branch("vx",       &vx_gen,       "vx/D"      ); //vx at vertex
	outTree->Branch("vy",       &vy_gen,       "vy/D"      ); //vy at vertex
	outTree->Branch("vz",       &vz_gen,       "vz/D"      ); //vz at vertex
	outTree->Branch("px",       &px_gen,       "px/D"      ); //px at vertex
	outTree->Branch("py",       &py_gen,       "py/D"      ); //py at vertex
	outTree->Branch("pz",       &pz_gen,       "pz/D"      ); //pz at vertex
	outTree->Branch("p",        &p_gen,        "p/D"       ); //ptot at vertex
	outTree->Branch("pid",      &pid_gen,        "pid/I"       ); //ptot at vertex
	// preshower tree
	outTree->Branch("preShP",      &preShP,   "preShP/D"    ); //momentum hit on the virtual plane of presh 
	outTree->Branch("preShPx",      &preShPx,   "preShPx/D"    ); //momentum px hit on the virtual plane of presh
	outTree->Branch("preShPy",      &preShPy,   "preShPy/D"    ); //momentum py hit on the virtual plane of presh
	outTree->Branch("preShPz",      &preShPz,   "preShPz/D"    ); //momentum pz hit on the virtual plane of presh
	outTree->Branch("preShEendSum",      &preShEendSum,   "preShEendSum/D"    ); //Sum of the deposit energy in three preshower modules
	outTree->Branch("preShLEend",      &preShLEend,   "preShLEend/D"    ); //Deposit energy in the left preshower module
	outTree->Branch("preShREend",      &preShREend,   "preShREend/D"    ); //Deposit energy in the right preshower module
	outTree->Branch("preShTEend",      &preShTEend,   "preShTEend/D"    ); //Deposit energy in the top preshower module
	// shower tree
	outTree->Branch("ShEendSum",      &ShEendSum,   "ShEendSum/D"    ); //Sum of the deposit energy in three shower modules
	outTree->Branch("ShLEend",      &ShLEend,   "ShLEend/D"    ); //Deposit energy in the left shower module
	outTree->Branch("ShREend",      &ShREend,   "ShREend/D"    ); //Deposit energy in the right shower module
	outTree->Branch("ShTEend",      &ShTEend,   "ShTEend/D"    ); //Deposit energy in the top shower module
	outTree->Branch("SC0P",      &SC0P,   "SC0P/D"    ); //momentum hit on the virtual plane of SC0
	outTree->Branch("SC0Px",      &SC0Px,   "SC0Px/D"    ); //momentum px hit on the virtual plane of SC0
	outTree->Branch("SC0Py",      &SC0Py,   "SC0Py/D"    ); //momentum py hit on the virtual plane of SC0
	outTree->Branch("SC0Pz",      &SC0Pz,   "SC0Pz/D"    ); //momentum pz hit on the virtual plane of SC0
	outTree->Branch("SC0Eend",      &SC0Eend,   "SC0Eend/D"    ); //Deposit energy in the SC0
	outTree->Branch("SC1P",      &SC1P,   "SC1P/D"    ); //momentum hit on the virtual plane of SC1
	outTree->Branch("SC1Px",      &SC1Px,   "SC1Px/D"    ); //momentum px hit on the virtual plane of SC1
	outTree->Branch("SC1Py",      &SC1Py,   "SC1Py/D"    ); //momentum py hit on the virtual plane of SC1
	outTree->Branch("SC1Pz",      &SC1Pz,   "SC1Pz/D"    ); //momentum pz hit on the virtual plane of SC1
	outTree->Branch("SC1Eend",      &SC1Eend,   "SC1Eend/D"    ); //Deposit energy in the SC1
	outTree->Branch("SPDP",      &SPDP,   "SPDP/D"    ); //momentum hit on the virtual plane of SPD
	outTree->Branch("SPDPx",      &SPDPx,   "SPDPx/D"    ); //momentum px hit on the virtual plane of SPD
	outTree->Branch("SPDPy",      &SPDPy,   "SPDPy/D"    ); //momentum py hit on the virtual plane of SPD
	outTree->Branch("SPDPz",      &SPDPz,   "SPDPz/D"    ); //momentum pz hit on the virtual plane of SPD
	outTree->Branch("SPDEend",      &SPDEend,   "SPDEend/D"    ); //Deposit energy in the SPD
	outTree->Branch("LASPDP",      &LASPDP,   "LASPDP/D"    ); //momentum hit on the virtual plane of LASPD
	outTree->Branch("LASPDPx",      &LASPDPx,   "LASPDPx/D"    ); //momentum px hit on the virtual plane of LASPD
	outTree->Branch("LASPDPy",      &LASPDPy,   "LASPDPy/D"    ); //momentum py hit on the virtual plane of LASPD
	outTree->Branch("LASPDPz",      &LASPDPz,   "LASPDPz/D"    ); //momentum pz hit on the virtual plane of LASPD
	outTree->Branch("LASPDEend",      &LASPDEend,   "LASPDEend/D"    ); //Deposit energy in the LASPD
	outTree->Branch("Npesum",      &Npesum,   "Npesum/D"    ); //Npe sum in the hgc
	outTree->Branch("Npe",      &Npe[0],   "Npe[0]/D"    ); // Npe #PMT in hgc
	//TFile *file=new TFile(infile, "READ");
	TFile *file=new TFile(inputfile_name.c_str());
	TTree *tree_header = 0;
	vector <double> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0, *var9=0,*var10;
	TH1F *htime_photon=new TH1F("time_photon","time_photon;t (ns)",100,0,100);

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
	tree_header->SetBranchAddress("userVar010",&var10);     //Abeam

	TTree *tree_generated = (TTree*) file->Get("generated");
	vector <int> *gen_pid=0;
	vector <double> *gen_px=0,*gen_py=0,*gen_pz=0,*gen_vx=0,*gen_vy=0,*gen_vz=0;
	tree_generated->SetBranchAddress("pid",&gen_pid);   //particle ID
	tree_generated->SetBranchAddress("px",&gen_px);     //momentum of the generated particle at target
	tree_generated->SetBranchAddress("py",&gen_py);
	tree_generated->SetBranchAddress("pz",&gen_pz);
	tree_generated->SetBranchAddress("vx",&gen_vx);     //vertex of the generated particle at target
	tree_generated->SetBranchAddress("vy",&gen_vy);
	tree_generated->SetBranchAddress("vz",&gen_vz);

	TTree *tree_flux = (TTree*) file->Get("flux");
	vector<double> *flux_id=0,*flux_hitn=0;
	vector<double> *flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0;
	vector<double> *flux_trackE=0,*flux_totEdep=0,*flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0, *flux_avg_lz=0,*flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;

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
	//information recorded by ec
	TTree* tree_solid_ec= (TTree*) file->Get("solid_ec");
	TTree* tree_solid_ec_ps= (TTree*) file->Get("solid_ec_ps");
	setup_tree_solid_ec(tree_solid_ec);	
	setup_tree_solid_ec_ps(tree_solid_ec_ps);	
	//information recorded by spd
	TTree* tree_solid_spd= (TTree*) file->Get("solid_spd");
	setup_tree_solid_spd(tree_solid_spd);	
	TTree* tree_solid_hgc= (TTree*) file->Get("solid_hgc");
	setup_tree_solid_hgc(tree_solid_hgc);	
	TRandom3 rand;
	rand.SetSeed(0);

	int sensor_good=0;
	int event_good=0,event_trig_good=0;
	// 	long int N_events = (long int)tree_header->GetEntries();
	long int N_events = (long int)tree_generated->GetEntries();	

	cout << "total number of events : " << N_events << endl;	

	//----------------------------
	//      loop trees
	//---------------------------
	double Ek=0;
	double Ec=0;
	double trigger_ec=0;
	int hit_id=-1;
	int hit_showerN=0;
	int hit_preshowerN=0;
	int hit_SPDN=0;
	int hit_LASPDN=0;
	int hit_SC0N=0;
	int hit_SC1N=0;
	double edep_6p1_max= 0,edep_6p1_SC0_max= 0,edep_6p1_SC1_max= 0,edep_6p1_SPD_max= 0,edep_6p1_LASPD_max= 0;
	double px_max=0,py_max=0,pz_max=0,p_max=0;
	double SC0_px_max=0,SC0_py_max=0,SC0_pz_max=0,SC0_p_max=0;
	double SC1_px_max=0,SC1_py_max=0,SC1_pz_max=0,SC1_p_max=0;
	double SPD_px_max=0,SPD_py_max=0,SPD_pz_max=0,SPD_p_max=0;
	double LASPD_px_max=0,LASPD_py_max=0,LASPD_pz_max=0,LASPD_p_max=0;
	int pid_gen1=0;
	double hit_pf=0;
	//	double theta_gen1=0,p_gen1=0,px_gen1=0,py_gen1=0,pz_gen1=0,vx_gen1=0,vy_gen1=0,vz_gen1=0;      
	bool writeFlag = false;
	for(long int i=0;i<1000000/*N_events*/;i++){	  		
		cout<<"event " << i << "\r";
		// cout<<"pid_size="<<gen_pid->size()<<endl;
		tree_generated->GetEntry(i);
		for (int j=0;j<gen_pid->size();j++) {
			pid_gen= gen_pid->at(j);
			px_gen=gen_px->at(j)/1e3;
			py_gen=gen_py->at(j)/1e3;
			pz_gen=gen_pz->at(j)/1e3;
			vx_gen=gen_vx->at(j)*0.1;
			vy_gen=gen_vy->at(j)*0.1;
			vz_gen=gen_vz->at(j)*0.1;
			p_gen=sqrt(px_gen*px_gen+py_gen*py_gen+pz_gen*pz_gen); 
		}
		//---
		tree_flux->GetEntry(i);		  
		int sec_hgc=0;		
		bool Is_trig=false;					  
		hit_id=-1;
		hit_showerN=0;
		hit_preshowerN=0;
		double Eec=0,Eec_photonele=0,Eec_ele=0,Edepsc1=0,Edepsc2=0;
		edep_6p1_max = 0;
		px_max = 0;
		py_max = 0;
		pz_max = 0;
		p_max = 0;
		for (Int_t j=0;j<flux_hitn->size();j++) {
			hit_pf=sqrt(flux_px->at(j)*flux_px->at(j)+flux_py->at(j)*flux_py->at(j)+flux_pz->at(j)*flux_pz->at(j))/1e3;  //MeV to GeV
			double E=flux_trackE->at(j)/1e3;		  
			if(flux_id->at(j)==1) hit_id=0; // SC0 front
			else if(flux_id->at(j)==2) hit_id=1; // SC1 front
			else if(flux_id->at(j)==3) hit_id=2; // EC front
			else if(flux_id->at(j)==9) hit_id=9; // EC shower front
			else if(flux_id->at(j)==4) hit_id=3; // EC back
			else if(flux_id->at(j)==5) hit_id=4; // GEM 1
			else if(flux_id->at(j)==6) hit_id=5; // GEM 2	  
			else if(flux_id->at(j)==7) hit_id=7; // spd 1
			else if(flux_id->at(j)==8) hit_id=8; // spd 2	  
			else if(flux_id->at(j)==10) hit_id=6; // Cherenkov front window
			else cout << "wrong flux_id" << flux_id->at(j) << endl;
			if(hit_id==2){
				hit_preshowerN ++;
				if (E >= edep_6p1_max){
					edep_6p1_max=E;
					p_max=hit_pf;
					px_max=flux_px->at(j)/1e3;
					py_max=flux_py->at(j)/1e3;
					pz_max=flux_pz->at(j)/1e3;
				}
			}else hit_preshowerN=hit_preshowerN;
			if(hit_id==0){
				hit_SC0N ++;
				if (E >= edep_6p1_SC0_max){
					edep_6p1_SC0_max=E;
					SC0_p_max=hit_pf;
					SC0_px_max=flux_px->at(j)/1e3;
					SC0_py_max=flux_py->at(j)/1e3;
					SC0_pz_max=flux_pz->at(j)/1e3;
				}
			}else hit_SC0N=hit_SC0N;
			if(hit_id==1){
				hit_SC1N ++;
				if (E >= edep_6p1_SC1_max){
					edep_6p1_SC1_max=E;
					SC1_p_max=hit_pf;
					SC1_px_max=flux_px->at(j)/1e3;
					SC1_py_max=flux_py->at(j)/1e3;
					SC1_pz_max=flux_pz->at(j)/1e3;
				}
			}else hit_SC0N=hit_SC0N;
			if(hit_id==7){
				hit_SPDN ++;
				if (E >= edep_6p1_SPD_max){
					edep_6p1_SPD_max=E;
					SPD_p_max=hit_pf;
					SPD_px_max=flux_px->at(j)/1e3;
					SPD_py_max=flux_py->at(j)/1e3;
					SPD_pz_max=flux_pz->at(j)/1e3;
				}
			}else hit_SPDN=hit_SPDN;
			if(hit_id==8){
				hit_LASPDN ++;
				if (E >= edep_6p1_LASPD_max){
					edep_6p1_LASPD_max=E;
					LASPD_p_max=hit_pf;
					LASPD_px_max=flux_px->at(j)/1e3;
					LASPD_py_max=flux_py->at(j)/1e3;
					LASPD_pz_max=flux_pz->at(j)/1e3;
				}
			}else hit_LASPDN=hit_LASPDN;
		}	// end of flux		

		// process ec
		tree_solid_ec->GetEntry(i);
		tree_solid_ec_ps->GetEntry(i);
		//if(hit_preshowerN>0){
		double Eend_ec_sum=0;
		double Eend_ec_ps_sum=0;	
		double Eend_ec[4]={0};
		double Eend_ec_ps[4]={0};
		process_tree_solid_ec(tree_solid_ec,tree_solid_ec_ps,Eend_ec_sum,Eend_ec_ps_sum,Eend_ec,Eend_ec_ps);
		//if(Eend_ec_ps_sum>0){ 
		preShEendSum=Eend_ec_ps_sum;
		preShLEend=Eend_ec_ps[2];
		preShREend=Eend_ec_ps[3];
		preShTEend=Eend_ec_ps[1];
		ShEendSum=Eend_ec_sum;
		ShLEend=Eend_ec[2];
		ShREend=Eend_ec[3];
		ShTEend=Eend_ec[1];
		preShP=p_max;
		preShPx=px_max;
		preShPy=py_max;
		preShPz=pz_max;
		writeFlag = true;
		//cout<<"event="<<i<<"  pid_gen="<<pid_gen<<endl;
		//if(Eend_ec_ps_sum>0){
		//cout<<"event="<<i<<"   "<<"Eend_ec_ps_sum="<<Eend_ec_ps_sum<<"preShLEend="<<preShLEend<<"preShREend="<<preShREend<<"preShTEend="<<preShTEend<<endl;
		//cout<<"event="<<i<<"   "<<"Eend_ec_sum="<<Eend_ec_sum<<"ShLEend="<<ShLEend<<"ShREend="<<ShREend<<"ShTEend="<<ShTEend<<endl;
		//}
		// process spd
		tree_solid_spd->GetEntry(i);
		double Edep_sc1=0, Edep_sc2=0, Edep_spd1=0, Edep_spd2=0;
		process_tree_solid_spd_simple(tree_solid_spd,Edep_sc1,Edep_sc2,Edep_spd1,Edep_spd2);
		//SC0
		SC0P=SC0_p_max;
		SC0Px=SC0_px_max;
		SC0Py=SC0_py_max;
		SC0Pz=SC0_pz_max;
		SC0Eend = Edep_sc1;
		//SC0
		SC1P=SC1_p_max;
		SC1Px=SC1_px_max;
		SC1Py=SC1_py_max;
		SC1Pz=SC1_pz_max;
		SC1Eend = Edep_sc2;
		//SPD
		SPDP=SPD_p_max;
		SPDPx=SPD_px_max;
		SPDPy=SPD_py_max;
		SPDPz=SPD_pz_max;
		SPDEend = Edep_spd1;
		//LASPD
		LASPDP=LASPD_p_max;
		LASPDPx=LASPD_px_max;
		LASPDPy=LASPD_py_max;
		LASPDPz=LASPD_pz_max;
		LASPDEend = Edep_spd2;
		//--- hgc 
		//-----------------------
		tree_solid_hgc->GetEntry(i);

		double hit_hgc[ch_hgc]={0};
		int trigger_hgc[30]={0};
		int ntrigsecs_hgc=0;
		int photon_mtid=0;
		process_tree_solid_hgc(tree_solid_hgc,hit_hgc,trigger_hgc,ntrigsecs_hgc,PMTthresh_hgc,PEthresh_hgc,ch_hgc,htime_photon,photon_mtid);
		npe_hgc_total=0;
		npe_hgc_total_trigged=0;		  
		for(int sensor_id=0;sensor_id<ch_hgc;sensor_id++) {	
			if (hit_hgc[sensor_id]>0){
				npe_hgc_total += hit_hgc[sensor_id];  
                                Npe[sensor_id] = hit_hgc[sensor_id];
                      //cout<<"sensor_id="<<sensor_id<<"hit_hgc="<<hit_hgc[sensor_id]<<endl;

			}
		}
		Npesum=npe_hgc_total;
		//if (npe_hgc_total>0) {		  
		//	event_good++;
		//	hnpe_hgc_count[0]->Fill(npe_hgc_total);		    
		//}

		if (writeFlag){
			outTree->Fill();
			//		outfile1<<pid_gen<<","<<vx_gen<<","<<vy_gen<<","<<vz_gen<<","<<px_gen<<","<<py_gen<<","<<pz_gen<<","<<p_gen<<","<<SC0Px<<","<<SC0Py<<","<<SC0Pz<<","<<SC0P<<","<<SC0Eend<<","<<SC1Px<<","<<SC1Py<<","<<SC1Pz<<","<<SC1P<<","<<SC1Eend<<","<<SPDPx<<","<<SPDPy<<","<<SPDPz<<","<<SPDP<<","<<SPDEend<<","<<LASPDPx<<","<<LASPDPy<<","<<LASPDPz<<","<<LASPDP<<","<<LASPDEend<<","<<preShPx<<","<<preShPy<<","<<preShPz<<","<<preShP<<","<<preShLEend<<","<<preShREend<<","<<preShTEend<<","<<preShEendSum<<","<<ShLEend<<","<<ShREend<<","<<ShTEend<<","<<ShEendSum<<endl;              
		}		
		if(((i+1)%1000)==0) {
			cout<<i+1<<"/"<<N_events<<" events processed \r";
		}

	} //end loop
	//do outputs
	cout<<endl;
	outFile->cd();
	outTree->Write();
	outFile->Close();
	}
