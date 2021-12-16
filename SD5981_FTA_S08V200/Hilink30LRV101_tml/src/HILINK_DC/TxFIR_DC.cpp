//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>
#include <HILINK_DC/Execute_functions.h>
using namespace std;

void DSP_LINEAR(ARRAY_D& src, LINEARtype *result, ARRAY_D& dle, ARRAY_D& ile, ILEtype ile_type) {

    int n;
	n= src.size();

	DOUBLE A1 = 0;
	DOUBLE B = 0;
    DOUBLE sum;
    DOUBLE DeviceLSB;
    DOUBLE Vref;

    for (int i = 0; i < n; i++) {   //masked by tony 20210811
    	A1 += double(src[i] * 1.0*i);
        B += double(src[i]);
    }

    switch (ile_type) {
        case MIN_RMS_LSB:
            DeviceLSB = (n * A1 - (B * n * (n - 1) / 2)) / (n * n * (n - 1) * (2 * n - 1) / 6 - ((n - 1) * n / 2) * ((n - 1) * n / 2));
            Vref = (B - DeviceLSB * n * (n - 1) / 2) / n;
            break;

    }
    for (int i = 0; i < (n - 1); i++) {
        switch (ile_type) {
            case MIN_RMS_LSB:
                dle[i] = (src[i + 1] - src[i]) / DeviceLSB - 1;
                ile[i] = (src[i] - (DeviceLSB * i + Vref)) / DeviceLSB;
                break;
        }
    }

    result->dmax = dle[0];
    result->dmin = dle[0];
    result->damax = abs(dle[0]);
    result->imax = ile[0];
    result->imin = ile[0];
    result->iamax = abs(ile[0]);
    result->dmax_index = 0;
    result->dmin_index = 0;
    result->damax_index = 0;
    result->imax_index = 0;
    result->imin_index = 0;
    result->iamax_index = 0;
    for (int i = 0; i < (n - 1); i++) {
        if (result->dmax < dle[i]) {
            result->dmax = dle[i];
            result->dmax_index = i;
        }
        if (result->dmin > dle[i]) {
            result->dmin = dle[i];
            result->dmin_index = i;
        }
        if (result->damax < dle[i]) {
            result->damax = abs(dle[i]);
            result->damax_index = i;
        }
        if (result->imax < ile[i]) {
            result->imax = ile[i];
            result->imax_index = i;
        }
        if (result->imin > ile[i]) {
            result->imin = ile[i];
            result->imin_index = i;
        }
        if (result->iamax < ile[i]) {
            result->iamax = abs(ile[i]);
            result->iamax_index = i;
        }
    }
}

class TxFIR_DC: public TestClass{
public:

	STRING 				mHiLink30_MacroList;
	STRING 				mPinList;
	STRING 				mFIR_SCAN;
	STRING 				mPinList_P;
	STRING 				mPinList_N;
	STRING 				mPattern;
	INT					mRateMode;
	INT					iPrintLvl;

	void init(){
		add_param("HiLink30_MacroList","string",&mHiLink30_MacroList)
					 .set_comment("HiLink30 Macro List for test")
					 //.setOptions("0,1:FromPinList")
					 .set_default("0,1");
//		add_param("PinList","PinString",&mPinList);
		add_param("FIR_SCAN","string",&mFIR_SCAN)
					 .set_default("MAIN");
					 //.setOptions("MAIN:PRE1ST:PRE2ND:POST1ST:POST2ND");
		add_param("Data","string",&mPattern)
					 .set_default("ALL0");
					 //.setOptions("ALL0:ALL1");
		add_param("RateMode","int",&mRateMode)
		             .set_default("0");
		add_param("PrintLvl[0~8]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 1000(16)"
					 "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYEPLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.setOptions("0:1:3:4:7:8")
					 .set_default("3");
	}
	void execute(){


	    H30_FailBin_Flag.init(0);
//	    STRING mPinList_P;
//	    STRING mPinList_N;
	    INT iDebugAnalog;
//	    STRING mPinList;

	    static INT iOffline;
	    static INT iCSR_check;
	    static MACRO_LANE_SEL MacroLane_Sel;

	    static LANE_ARRAY_D vTxDiffMeasVoltageSCAN;
	    static LANE_DOUBLE vTxPosMeasVoltage;
	    static LANE_DOUBLE vTxNegMeasVoltage;
	    static LANE_DOUBLE vTxDiffMeasVoltage;
	    static LANE_DOUBLE vINL;
	    static LANE_DOUBLE vDNL;
	    static LANE_DOUBLE vGain;
	    static LANE_DOUBLE vOffset;
	    static bool CSRVerifyResult;



	    stTxFIR_DC TxFIR_DC; //=SSbandGap_SSBandGap;
	    stTxFIR_DC_Limit TxFIR_DC_Limit;
//	    const char * sTestsuiteName = api->Get_current_test_name();
	    string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
	    string strTestsuiteName = sTestsuiteName;
//	    api->Get_test_values(strTestsuiteName.data(), THE_TESTNUMBER, &m_TestNumber, THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();

	    if (strTestsuiteName == "H30_TxFIR_DC_MAIN_ALL0_VDDN")////PLL0_1G  1
	    {
	        TxFIR_DC = H30_TxFIR_DC_MAIN_ALL0_VDDN_TxFIR_DC;
	        TxFIR_DC_Limit = H30_TxFIR_DC_MAIN_ALL0_VDDN_TxFIR_DC_Limit;
	    }
	    else if (strTestsuiteName == "H30_TxFIR_DC_MAIN_ALL1_VDDN") {
	        TxFIR_DC = H30_TxFIR_DC_MAIN_ALL1_VDDN_TxFIR_DC;
	        TxFIR_DC_Limit = H30_TxFIR_DC_MAIN_ALL1_VDDN_TxFIR_DC_Limit;

	    }
	    else if (strTestsuiteName == "H30_TxFIR_DC_PRE1_ALL0_VDDN") {
	        TxFIR_DC = H30_TxFIR_DC_PRE1_ALL0_VDDN_TxFIR_DC;
	        TxFIR_DC_Limit = H30_TxFIR_DC_MAIN_ALL1_VDDN_TxFIR_DC_Limit;

	    }
	    else if (strTestsuiteName == "H30_TxFIR_DC_PRE1_ALL1_VDDN") {
	        TxFIR_DC = H30_TxFIR_DC_PRE1_ALL1_VDDN_TxFIR_DC;
	        TxFIR_DC_Limit = H30_TxFIR_DC_MAIN_ALL1_VDDN_TxFIR_DC_Limit;

	    }
	    else if (strTestsuiteName == "H30_TxFIR_DC_PRE2_ALL0_VDDN") {
	        TxFIR_DC = H30_TxFIR_DC_PRE2_ALL0_VDDN_TxFIR_DC;
	        TxFIR_DC_Limit = H30_TxFIR_DC_MAIN_ALL1_VDDN_TxFIR_DC_Limit;

	    }
	    else if (strTestsuiteName == "H30_TxFIR_DC_PRE2_ALL1_VDDN") {
	        TxFIR_DC = H30_TxFIR_DC_PRE2_ALL1_VDDN_TxFIR_DC;
	        TxFIR_DC_Limit = H30_TxFIR_DC_MAIN_ALL1_VDDN_TxFIR_DC_Limit;

	    }
	    else if (strTestsuiteName == "H30_TxFIR_DC_POST1_ALL0_VDDN") {
	        TxFIR_DC = H30_TxFIR_DC_POST1_ALL0_VDDN_TxFIR_DC;
	        TxFIR_DC_Limit = H30_TxFIR_DC_POST1_ALL0_VDDN_TxFIR_DC_Limit;

	    }
	    else if (strTestsuiteName == "H30_TxFIR_DC_POST1_ALL1_VDDN") {
	        TxFIR_DC = H30_TxFIR_DC_POST1_ALL1_VDDN_TxFIR_DC;
	        TxFIR_DC_Limit = H30_TxFIR_DC_POST1_ALL1_VDDN_TxFIR_DC_Limit;
	    }

	    hout.setLevel(iPrintLvl);
	    hout.printsuitename(sTestsuiteName);
	    Select_Macro_Lane(MacroLane_Sel, mHiLink30_MacroList, mPinList);

	    get_pinlists( MacroLane_Sel, mPinList_P, mPinList_N, mPinList, "TX");

	    //=============================================
	    // Variables definition and initialization
	    //=============================================
	    //		INT 				i;
	    //		PPMU_SETTING 		Set;
	    //		PPMU_RELAY   		Rly1,Rly2;
	    //		PPMU_MEASURE 		Meas;
	    //		TASK_LIST    		Task, TaskSetup, TaskClean;
	    //
	    //		Set.pin(mPinList_P + "," + mPinList_N).iForce(- 0.1 uA).iRange(2 uA).min(-1 V).max(2 V);
	    //		Rly1.pin(mPinList_P + "," + mPinList_N).status("ACPM_ON");
	    //
	    //		Rly2.pin(mPinList_P + "," + mPinList_N).status("AC_ON");
	    //
	    //		Meas.pin(mPinList_P + "," + mPinList_N).execMode(TM::OVAL);
	    //
	    //		TaskSetup.add(Rly1).add(Set).setup();
	    //		Task.add(Meas).setup();
	    //		TaskClean.add(Rly2).setup();
	    //		TaskSetup.execute();



	    double *data1, *data2;
	    double resource[48] = {0};

	    data1 = resource; /////初始化指针
	    data2 = resource; /////初始化指针

	    INT RateMode;

	    //total = abs(pre2) + abs(pre1) + abs(main) + abs(post1) + abs(post2) must < 63!!!

	    vector<INT> iMain, iPre1st, iPre2nd, iPost1st;
	    //iMain.resize(33);
	    //iPre1st.resize(17);
	    //iPre2nd.resize(17);
	    //iPost1st.resize(31);
	    for (int i = 0; i <= 63;) {
	        //debug
	        if (i == 48) {
	            iMain.push_back(48);
	        } else {
	            iMain.push_back(i);
	        }
	        //end
	        if (i != 60)i = i + 2;
	        else if (i == 60)i++;
	    }
	    for (int i = -15; i < 16;) {
	        iPre1st.push_back(i);
	        iPre2nd.push_back(i);
	        if ((i<-14) || (i == 12))i++;
	        else if ((i >= -14)&&(i < 12))i = i + 2;
	        else if (i > 12) i = i + 2;
	    }

	    for (int i = -30; i <= 30; i = i + 2) {
	        iPost1st.push_back(i);
	    }


	    CUSTPARA Custpara;

	    Custpara.TxFIR_USER.iTxMain = 0;
	    Custpara.TxFIR_USER.iTxPre1st = 0;
	    Custpara.TxFIR_USER.iTxPost1st = 0;
	    Custpara.TxFIR_USER.iTxPre2nd = 0;
	    Custpara.TxFIR_USER.iTxPost2nd = 0;

	    //=============================================
	    // Device Setup
	    //=============================================

	    RateMode = mRateMode;

	    d2s::d2s_LABEL_BEGIN( "MPB_DS_TX_FIR_DC_MAIN_SETUP_", Global_D2S_Mode);
	    selectMacro_MB(MacroLane_Sel);
	    DS.txRegs.SliceID(0).Broadcast(1);
	    if (mPattern == "ALL0")
	        EnableTxPrbsGen( "CUSTOMER_PATTERN", 0x0000);
	    else if (mPattern == "ALL1")
	        EnableTxPrbsGen( "CUSTOMER_PATTERN", 0xFFFF);
	    d2s::d2s_LABEL_END();

	    //=============================================
	    // Measurement
	    //=============================================
	    int scan_num;
	    if (mFIR_SCAN == "MAIN") scan_num = iMain.size();
	    else if (mFIR_SCAN == "PRE1ST") scan_num = iPre1st.size();
	    else if (mFIR_SCAN == "PRE2ND") scan_num = iPre2nd.size();
	    else if (mFIR_SCAN == "POST1ST") scan_num = iPost1st.size();
	    //                //
	    //                ostringstream File_name;
	    //                const char* devpath;
	    //                devpath = "E:\\wenxinyu\\git-workspace";
	    //
	    //                File_name<<devpath<<"\\report\\FirDc_Main.log";
	    //
	    //                ofstream csrfile;
	    //                csrfile.open(File_name.str().c_str(),ios::binary);
	    //                //
	    vTxDiffMeasVoltageSCAN.init(scan_num, 0);
	    for (int i = 0; i < scan_num; i++) {

	        if (mFIR_SCAN == "MAIN") Custpara.TxFIR_USER.iTxMain = iMain[i];
	        else if (mFIR_SCAN == "PRE1ST") Custpara.TxFIR_USER.iTxPre1st = iPre1st[i];
	        else if (mFIR_SCAN == "PRE2ND") Custpara.TxFIR_USER.iTxPre2nd = iPre2nd[i];
	        else if (mFIR_SCAN == "POST1ST") Custpara.TxFIR_USER.iTxPost1st = iPost1st[i];


	        SetTxFir( MacroLane_Sel, Custpara);

//	        Sleep(0.001);

//	        api->Execute_test("H30LR_FIR_MForce_I_N0P1UA");
	        PinArrayDouble H30LR_FIR_MForce_I_N0P1UA_result = H30LR_FIR_MForce_I_N0P1UA();
//	        Sleep(0.003);
	        if(PrintDebugEn)  H30LR_FIR_MForce_I_N0P1UA_result.ShowPinArrayData();
	        vTxPosMeasVoltage.init(0);
	        vTxNegMeasVoltage.init(0);
	        vTxDiffMeasVoltage.init(0);

//	        FOREACH_ACTIVE_SITE(api) {
//	            unsigned int SiteID = api->Get_active_site();
	            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

	            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
	                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
	                const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

	                for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
	                    UINT LaneID = vLane[laneIndex];

	                    //						vTxPosMeasVoltage[SiteID][MacroID][LaneID] = Meas.getValue(LANE_INFO[MacroID][LaneID].TX_P) / (1 mV);
	                    //						vTxNegMeasVoltage[SiteID][MacroID][LaneID] = Meas.getValue(LANE_INFO[MacroID][LaneID].TX_N) / (1 mV);
	                    //                                                need revise

	                    const char * TxPos_Pin = LANE_INFO[MacroID][LaneID].TX_P.c_str();
	                    const char * TxNeg_Pin = LANE_INFO[MacroID][LaneID].TX_N.c_str();

//	                    api->Get_dctest_values("H30LR_FIR_MForce_I_N0P1UA", TxPos_Pin, 0, THE_MEASURE, &data1[0], THE_END); //modify by tony 20210524 data1 to data1[0]]
	                    data1[0] = H30LR_FIR_MForce_I_N0P1UA_result.GetData(string(TxPos_Pin),SiteID);

	                    vTxPosMeasVoltage[SiteID][MacroID][LaneID] = data1[0] *1000; //mV

//	                    api->Get_dctest_values("H30LR_FIR_MForce_I_N0P1UA", TxNeg_Pin, 0, THE_MEASURE, &data2[0], THE_END);//modify by tony 20210524 data2 to data2[0]]
	                    data2[0] = H30LR_FIR_MForce_I_N0P1UA_result.GetData(string(TxNeg_Pin),SiteID);

	                    vTxNegMeasVoltage[SiteID][MacroID][LaneID] = data2[0] *1000; //mV

	                    vTxDiffMeasVoltage[SiteID][MacroID][LaneID] = vTxNegMeasVoltage[SiteID][MacroID][LaneID];
	                    //						vTxDiffMeasVoltage[SiteID][MacroID][LaneID] = vTxPosMeasVoltage[SiteID][MacroID][LaneID] - vTxNegMeasVoltage[SiteID][MacroID][LaneID];
	                    //hout(DETAIL) << "***************MainPole = " << MainPole << "**************"<< endl;
	                    if (mFIR_SCAN == "MAIN") hout(DETAIL) << "***************Main = " << iMain[i] << "**************" << endl;
	                    else if (mFIR_SCAN == "PRE1ST") hout(DETAIL) << "***************Pre1st = " << iPre1st[i] << "**************" << endl;
	                    else if (mFIR_SCAN == "PRE2ND") hout(DETAIL) << "***************Pre2nd = " << iPre2nd[i] << "**************" << endl;
	                    else if (mFIR_SCAN == "POST1ST") hout(DETAIL) << "***************Post1st = " << iPost1st[i] << "**************" << endl;
	                    hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
	                            << " Pos Voltage = " << vTxPosMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;
	                    hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
	                            << " Neg Voltage = " << vTxNegMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;
	                    hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
	                            << " DiffVoltage = " << vTxDiffMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;


	                   cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
	                            << " Pos Voltage = " << vTxPosMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;
	                   cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_N
	                            << " Neg Voltage = " << vTxNegMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;
	                   cout << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
	                            << " DiffVoltage = " << vTxDiffMeasVoltage[SiteID][MacroID][LaneID] << " [mV]" << endl;

	                    if (iOffline) {
	                        vTxDiffMeasVoltage[SiteID][MacroID][LaneID] = i;
	                    }
	                }
	            }
	            FOREACH_ACTIVESITE_END

//	        FOREACH_ACTIVE_SITE(api) {
//	            unsigned int SiteID = api->Get_active_site();
	            FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

	            for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
	                UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
	                const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
	                for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
	                    UINT LaneID = vLane[laneIndex];
	                    vTxDiffMeasVoltageSCAN[SiteID][MacroID][LaneID][i] = vTxDiffMeasVoltage[SiteID][MacroID][LaneID];
	                    //                                                        //
	                    //                                                        ostringstream str;
	                    //                                                         str << "vTxDiffMeasVoltageSCAN[" << SiteID<< "]["<< MacroID<< "]["<<LaneID<<"]["<<i <<"] = "<<vTxDiffMeasVoltageSCAN[SiteID][MacroID][LaneID][i];
	                    //                                                        csrfile<<str.str()<<endl;
	                    //                                                        //
	                    printf("vTxDiffMeasVoltageSCAN[%d][%d][%d][%d] = %f\n", SiteID, MacroID, LaneID, i, vTxDiffMeasVoltageSCAN[SiteID][MacroID][LaneID][i]);
	                }
	            }
	            FOREACH_ACTIVESITE_END
	    }

	    //		TaskClean.execute();

	    vINL.init(999);
	    vDNL.init(999);
	    vGain.init(999);
	    vOffset.init(999);

	    ARRAY_D dnla_main, inla_main;
	    LINEARtype linRes_main;
	    ARRAY_D dnl_res_main, inl_res_main, gain_main, offset_main;

	    dnla_main.resize(scan_num);
	    inla_main.resize(scan_num);

//	    FOREACH_ACTIVE_SITE(api) {
//	        unsigned int SiteID = api->Get_active_site();
	        FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)

	        for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex++) {
	            UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
	            const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
	            for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex++) {
	                UINT LaneID = vLane[laneIndex];
	                if (iDebugAnalog) {
	                    //PUT_DEBUG(LANE_INFO[MacroID][LaneID].TX_P,"MAIN",vTxDiffMeasVoltageSCAN[SiteID][MacroID][LaneID]);

	                    for (int i = 0; i < scan_num; i++) {
	                        hout(DETAIL) << "LaneIndex " << LaneID << "  Scan Points: " << i << "  " << dec << vTxDiffMeasVoltageSCAN[SiteID][MacroID][LaneID][i] << endl;
	                    }
	                }

	                inl_res_main.resize(vLane.size());
	                dnl_res_main.resize(vLane.size());
	                gain_main.resize(vLane.size());
	                offset_main.resize(vLane.size());

	                //calculate
	                DSP_LINEAR(vTxDiffMeasVoltageSCAN[SiteID][MacroID][LaneID], &linRes_main, dnla_main, inla_main, MIN_RMS_LSB);

	                //                                            double temp[33];
	                //                                            for(int i =0;i<33;++i)
	                //                                            {
	                //                                                temp[i] =  vTxDiffMeasVoltageSCAN[SiteID][MacroID][LaneID][i];
	                //                                            }

	                //                                            double offset, fsr, inl, dnl;
	                //                                            unsigned monotonic;
	                //
	                //                                            stringstream ss;   //int 2 string
	                //                                            ss<<macroIndex;
	                //                                            string strmacroIndex;
	                //                                            ss>>strmacroIndex;
	                //
	                //                                            stringstream ss1;   //int 2 string
	                //                                            ss1<<laneIndex;
	                //                                            string strlaneIndex;
	                //                                            ss1>>strlaneIndex;
	                //                                            string Macro_Lane_Name=strTestsuiteName+"M"+strmacroIndex+"_L"+strlaneIndex;
	                //
	                //                                            dacStaticCalc( &vTxDiffMeasVoltageSCAN[SiteID][MacroID][LaneID][0], 33,offset, fsr, inl, dnl, monotonic, Macro_Lane_Name, END_POINT_ANALYSIS);
	                //                                            std::stringstream info;
	                //                                            info << "offset is "<< offset << std::endl;
	                //                                            info << "gain is   "<< fsr << std::endl;
	                //                                            info << "inl is    "<< inl << std::endl;
	                //                                            info << "dnl is    "<< dnl << std::endl;
	                //
	                //
	                //                                            api->Info_message(info.str().c_str());

	                vINL[SiteID][MacroID][LaneID] = linRes_main.iamax;
	                vDNL[SiteID][MacroID][LaneID] = linRes_main.damax;
	                vOffset[SiteID][MacroID][LaneID] = vTxDiffMeasVoltageSCAN[SiteID][MacroID][LaneID][0]; //mV
	                vGain[SiteID][MacroID][LaneID] = vTxDiffMeasVoltageSCAN[SiteID][MacroID][LaneID][scan_num - 1]; //mV
	                //
	                //                                            ostringstream str;
	                //                                             str << "vINL[" << SiteID<< "]["<< MacroID<< "]["<<LaneID <<"] = "<<vINL[SiteID][MacroID][LaneID]<<endl;
	                //                                             str << "vDNL[" << SiteID<< "]["<< MacroID<< "]["<<LaneID <<"] = "<<vDNL[SiteID][MacroID][LaneID];
	                //                                            csrfile<<str.str()<<endl;
	                //

	                hout(DETAIL) << "Pin " << LANE_INFO[MacroID][LaneID].TX_P
	                        << mFIR_SCAN
	                        << "\tINL = " << vINL[SiteID][MacroID][LaneID]
	                        << "\tDNL = " << vDNL[SiteID][MacroID][LaneID]
	                        << "\tOffset = " << vOffset[SiteID][MacroID][LaneID]
	                        << "\tGain = " << vGain[SiteID][MacroID][LaneID]
	                        << endl;


	            }
	        }
	        FOREACH_ACTIVESITE_END
	    //
	    //                csrfile.close();
	    //
	    //		ON_FIRST_INVOCATION_END();

	    //=============================================
	    // Datalog
	    //=============================================
	    double LimitL_INL = TxFIR_DC_Limit.LimitL_INL;
	    double LimitH_INL = TxFIR_DC_Limit.LimitH_INL;
	    double LimitL_DNL = TxFIR_DC_Limit.LimitL_DNL;
	    double LimitH_DNL = TxFIR_DC_Limit.LimitH_DNL;
	    double LimitL_GAIN = TxFIR_DC_Limit.LimitL_GAIN;
	    double LimitH_GAIN = TxFIR_DC_Limit.LimitH_GAIN;
	    double LimitL_OFFSET = TxFIR_DC_Limit.LimitL_OFFSET;
	    double LimitH_OFFSET = TxFIR_DC_Limit.LimitH_OFFSET;


	    HiLink_PerLane_Judge( MacroLane_Sel, "INL", LimitL_INL, vINL, LimitH_INL, PIN_TXP);
	    HiLink_PerLane_Judge( MacroLane_Sel, "DNL", LimitL_DNL, vDNL, LimitH_DNL, PIN_TXP);
	    HiLink_PerLane_Judge( MacroLane_Sel, "GAIN", LimitL_GAIN, vGain, LimitH_GAIN, PIN_TXP);
	    HiLink_PerLane_Judge( MacroLane_Sel, "OFFSET", LimitL_OFFSET, vOffset, LimitH_OFFSET, PIN_TXP);

	    SetTestBin();
	}

};
REGISTER_TESTCLASS("TxFIR_DC",TxFIR_DC)





//int debug_post(API * api) {    //for debug dc group pin  , tony 20210524
//
//    double data1;
////    double resource[48] = {0};
////
////    data1 = resource; /////初始化指针
////    data2 = resource; /////初始化指针
//
//    api->Execute_test("H30LR_FIR_MForce_I_N0P1UA");
//
//    FOREACH_ACTIVE_SITE(api) {
//        unsigned int SiteID = api->Get_active_site();
//        api->Get_dctest_values("H30LR_FIR_MForce_I_N0P1UA_group", "TX_SDS0_P", 0, THE_MEASURE, &data1, THE_END); //modify by tony 20210524 data1 to data1[0]]
//    }
//    api->info_message("nihao==========debug");
//    return EXIT_SUCCESS;
//}
