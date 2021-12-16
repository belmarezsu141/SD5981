////////////////////////////////////////////////////////////////////////////////
// Description:                                                               //
// This c++ file is instance of Hilink15 PUG Function, it contains Calibration//
// ,Read Bert and EyeDiagram's code. link with PUG							  //
////////////////////////////////////////////////////////////////////////////////

#include <HILINK_PUG/HiLink16_PUG.h>

class GLOBAL_SSPARA		SSpara;
class GLOBAL_CSPARA		CSpara;
class GLOBAL_CUSTPARA 	CUSTpara;


/*****DS_ARRAY*******/
map<int,int>  		DS_API_1FFF0;
map<int,int>  		DS_API_1FFF2;
map<int,int>  		DS_API_1FFF4;
map<int,int>  		DS_API_1FFF6;
map<int,int>  		DS_API_1FFF8;
map<int,int>  		DS_API_1FFFA;
map<int,int>  		DS_API_1FFFC;
map<int,int>  		DS_API_1FFFE;
map <int,ARRAY_D> 	RingVcooutoflock;

map<int,int>  		DS_API_Flag;
map <int,int>       RingVcooutoflock_Flag;


void CsConfigurationbeforecalibration(const MACRO_LANE_SEL &MacroLane_Sel, GLOBAL_CUSTPARA &CUSTpara, GLOBAL_SSPARA &SSpara, GLOBAL_CSPARA &CSpara)
{
	INT	srefclk0div2sel = SSpara.SDiv>>1;
	INT	cmldiv = ((CSpara.KbDiv - 1) << 1) | ((CSpara.KaDiv - 2) & 0x01);

	INT 	wordclkdiv;
	switch (CSpara.JDiv) {
		case 20: 		wordclkdiv = 0;		break;
		case 10: 		wordclkdiv = 1;		break;
		case 16: 		wordclkdiv = 2;		break;
		case 8: 		wordclkdiv = 3;		break;
		default: 		wordclkdiv = 1;		break;
	}
	INT		wordclkdiv2 = CSpara.WDiv >> 1;

	DOUBLE RateModeIndex;
	switch (CUSTpara.RateMode) {
		case 0: RateModeIndex = 1; break;
		case 1: RateModeIndex = 0.5; break;
		case 2: RateModeIndex = 0.25; break;
		case 3: RateModeIndex = 0.125; break;
	}
	CUSTpara.Data_Rate = SSpara.Refclk * CSpara.NDiv / (CSpara.KbDiv * CSpara.Mdiv) * 2 * RateModeIndex / 1000;

	CS.clkRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(CUSTpara.CSslice).Broadcast(0);

	if (CUSTpara.SSCGen_EN) {
		/*
		**********************************************
			Ref_CLK = 100MHz
		**********************************************
		Standard 	SSCamp(PPM)		sscamp	sscfreq	sscatt	ssctype
		PCIE-1/2	Down 0/-5000	0x20	0x32	0x1		0x0
		PCIE-3		Down 0/-5000	0x33	0x20	0x2		0x0
		SATA-1/2/3	Down 0/-5000	0x26	0x2A	0x1		0x0
		SAS-1/2/3	Center +/-2300	0x23	0x2E	0x1		0x1
		SAS-1/2/3	Down 0/-2300	0x22	0x2F	0x2		0x0
		SAS-4		Center +/-1000	0x1E	0x35	0x2		0x1
		SAS-4		Down 0/-1000	0x1E	0x35	0x3		0x0
S
		**********************************************
		Ref_CLK = 150MHz
		**********************************************
		Standard 	SSCamp(PPM)		sscamp	sscfreq	sscatt	ssctype
		SATA-1/2/3	Down 0/-5000	0x33	0x30	0x2		0x0
		SAS-1/2/3	Center +/-2300	0x2F	0x34	0x2		0x1
		SAS-1/2/3	Down 0/-2300	0x2E	0x35	0x3		0x0
		SAS-4		Center +/-1000	0x28	0x3C	0x3		0x1
		SAS-4		Down 0/-1000	0x14	0x77	0x3		0x0

		**********************************************
			Ref_CLK = 75MHz
		**********************************************
		Standard 	SSCamp(PPM)		sscamp	sscfreq	sscatt	ssctype
		SATA-1/2/3	Down 0/-5000	0x33	0x18	0x1		0x0
		SAS-1/2/3	Center +/-2300	0x2F	0x1A	0x1		0x1
		SAS-1/2/3	Down 0/-2300	0x2E	0x1A	0x2		0x0
		SAS-4		Center +/-1000	0x28	0x1E	0x2		0x1
		SAS-4		Down 0/-1000	0x14	0x3B	0x2		0x0
		*/

//		/**************   new ssc table ***********
		INT sscamp_table[7][3] = {
			//Ref_100M	Ref_150M	Ref_75M		Standard		SSCamp(PPM)
			{0x1F,		0x00,		0x00},		//PCIE-1/2		Down 0/-5000
			{0x32,		0x00,		0x00},		//PCIE-3		Down 0/-5000
			{0x25,		0x33,		0x33},		//SATA-1/2/3	Down 0/-5000    Ka = 2 Kb = 2
			{0x22,		0x2F,		0x2F},		//SAS-1/2/3		Center +/-2300  Ka = 2 Kb = 2
			{0x21,		0x2E,		0x2E},		//SAS-1/2/3		Down 0/-2300    Ka = 2 Kb = 2
			{0x1D,		0x28,		0x28},		//SAS-4			Center +/-1000
			{0x1D,		0x14,		0x14}		//SAS-4			Down 0/-1000

		};

		INT sscfreq_table[7][3] = {
			//Ref_100M	Ref_150M	Ref_75M		Standard		SSCamp(PPM)
			{0x31,		0x00,		0x00},		//PCIE-1/2		Down 0/-5000
			{0x1F,		0x00,		0x00},		//PCIE-3		Down 0/-5000
			{0x29,		0x30,		0x18},		//SATA-1/2/3	Down 0/-5000  	Ka = 2 Kb = 2
			{0x2E,		0x34,		0x1A},		//SAS-1/2/3		Center +/-2300  Ka = 2 Kb = 2
			{0x2E,		0x35,		0x1A},		//SAS-1/2/3		Down 0/-2300    Ka = 2 Kb = 2
			{0x35,		0x3C,		0x1E},		//SAS-4			Center +/-1000
			{0x35,		0x77,		0x3B}		//SAS-4			Down 0/-1000
		};

		INT sscatt_table[7][3] = {
			//Ref_100M	Ref_150M	Ref_75M		Standard		SSCamp(PPM)
			{0x1,		0x00,		0x00},		//PCIE-1/2		Down 0/-5000
			{0x2,		0x00,		0x00},		//PCIE-3		Down 0/-5000  	Ka = 2 Kb = 2
			{0x1,		0x2,		0x1},		//SATA-1/2/3	Down 0/-5000  	Ka = 2 Kb = 2
			{0x1,		0x2,		0x1},		//SAS-1/2/3		Center +/-2300  Ka = 2 Kb = 2
			{0x2,		0x3,		0x2},		//SAS-1/2/3		Down 0/-2300
			{0x2,		0x3,		0x2},		//SAS-4			Center +/-1000
			{0x3,		0x3,		0x2}		//SAS-4			Down 0/-1000
		};

		INT ssctype_table[7][3] = {
			//Ref_100M	Ref_150M	Ref_75M		Standard		SSCamp(PPM)
			{0x0,		0x00,		0x00},		//PCIE-1/2		Down 0/-5000
			{0x0,		0x00,		0x00},		//PCIE-3		Down 0/-5000  	Ka = 2 Kb = 2
			{0x0,		0x0,		0x0},		//SATA-1/2/3	Down 0/-5000  	Ka = 2 Kb = 2
			{0x1,		0x1,		0x1},		//SAS-1/2/3		Center +/-2300  Ka = 2 Kb = 2
			{0x0,		0x0,		0x0},		//SAS-1/2/3		Down 0/-2300
			{0x1,		0x1,		0x1},		//SAS-4			Center +/-1000
			{0x0,		0x0,		0x0}		//SAS-4			Down 0/-1000
		};
//		 */
		INT 				pcie_sas_data_rate;
		INT 				Ref_clk_index,Standardd_inedx;

		if (SSpara.Refclk == 100) {
			Ref_clk_index = 0;
		} else if (SSpara.Refclk == 150) {
			Ref_clk_index = 1;
		} else if (SSpara.Refclk == 75) {
			Ref_clk_index = 2;
		}

		if (CUSTpara.Protocol == "PCIE") {
			if (CUSTpara.Data_Rate == 2.5) {
				pcie_sas_data_rate = 0;
				Standardd_inedx = 0;
			} else if (CUSTpara.Data_Rate == 5) {
				pcie_sas_data_rate = 1;
				Standardd_inedx = 0;
			} else if (CUSTpara.Data_Rate == 8) {
				pcie_sas_data_rate = 2;
				Standardd_inedx = 1;
			}
		} else if (CUSTpara.Protocol == "SAS") {
			if (CUSTpara.Data_Rate == 1.5) {
				pcie_sas_data_rate = 4;
				Standardd_inedx = 3;
			} else if (CUSTpara.Data_Rate == 3) {
				pcie_sas_data_rate = 5;
				Standardd_inedx = 3;
			} else if (CUSTpara.Data_Rate == 6) {
				pcie_sas_data_rate = 6;
				Standardd_inedx = 3;
			} else if (CUSTpara.Data_Rate == 12) {
				pcie_sas_data_rate = 7;
				Standardd_inedx = 5;
			}
		} else if (CUSTpara.Protocol == "SATA") {
			if (CUSTpara.Data_Rate == 1.5) {
				pcie_sas_data_rate = 4;
				Standardd_inedx = 2;
			} else if (CUSTpara.Data_Rate == 3) {
				pcie_sas_data_rate = 5;
				Standardd_inedx = 2;
			} else if (CUSTpara.Data_Rate == 6) {
				pcie_sas_data_rate = 6;
				Standardd_inedx = 2;
			}
		} else if (CUSTpara.Protocol == "COMMON") {
			hout(RELEASE) << "!!ERROR: SSCGen_EN do not support COMMON mode, please select PCIe/SAS/SATA mode!!" << endl;
			_exit(0);
		}

		hout(DETAIL) << "Ref_CLK : " << SSpara.Refclk << "MHz\tDataRate : " << CUSTpara.Data_Rate << "G\tindex :" << Ref_clk_index << endl;
		hout(DETAIL) << "-|-	sscamp	sscfreq	sscatt	ssctype	-|-\n";
		hout(DETAIL) << hex << "-|-\t" << sscamp_table[Standardd_inedx][Ref_clk_index]
					 << hex << "\t" << sscfreq_table[Standardd_inedx][Ref_clk_index]
					 << hex << "\t" << sscatt_table[Standardd_inedx][Ref_clk_index]
					 << hex << "\t" << ssctype_table[Standardd_inedx][Ref_clk_index] << endl;

		CS.clkRegs.setssc_freeze_en_sel(0x1).Write2DUT(43);
		CS.clkRegs.setssc_clksel(0x0).Write2DUT(58);
		CS.clkRegs.setcs_ctrl_code_max_freqcal(0x38).Write2DUT(32);
		CS.clkRegs.setcpcintsel(0x15).Write2DUT(44);
		CS.clkRegs.setcp_dlf_resfdbkpwrdb(0x2).Write2DUT(44);
		/****put ssc_bypassb ahead to improve 10% yield in Hi1812****/
		CS.clkRegs.setssc_bypassb(0x1).Write2DUT(57);
		CS.clkRegs.setssctype(ssctype_table[Standardd_inedx][Ref_clk_index])
				  .setsscfreq(sscfreq_table[Standardd_inedx][Ref_clk_index]).Write2DUT(56);
		CS.clkRegs.setsscamp(sscamp_table[Standardd_inedx][Ref_clk_index]).Write2DUT(57);
		CS.clkRegs.setsscatt(sscatt_table[Standardd_inedx][Ref_clk_index]).Write2DUT(60);

		CS.clkRegs.setcp_i_propchp_tune(0x1).Write2DUT(4);
		CS.clkRegs.setcp_i_intchp_tune(0x1).Write2DUT(58);
		CS.clkRegs.setcpcurrent(0x0).Write2DUT(4);
	}
	else
	{
		CS.clkRegs.setssc_clksel(0x1).Write2DUT(58);
		CS.clkRegs.setssc_bypassb(0x0).Write2DUT(57);
		CS.clkRegs.setcp_dlf_resfdbkpwrdb(0x3).Write2DUT(44);
		CS.clkRegs.setcpcintsel(0xD).Write2DUT(44);
		CS.clkRegs.setcp_i_propchp_tune(0x0).Write2DUT(4);
		CS.clkRegs.setcp_i_intchp_tune(0x0).Write2DUT(58);
//		CS.clkRegs.setcpcurrent(0xF).Write2DUT(4);
        /**********************************************
        *************  HilinkX start  ****************
        **********************************************/
		CS.clkRegs.setcpcurrent(0xF).Write2DUT(4);
		CS.clkRegs.setcpcintsel(0x4).Write2DUT(4);
        /*********************************************
        *************  HilinkX stop   ****************
        **********************************************/
	}

	CS.clkRegs.setssrefclk0div2sel(srefclk0div2sel)
			  .setssrefclk1div2sel(srefclk0div2sel)
			  .setrefclksel(SSpara.RefclkBus)
			  .Write2DUT(0);

	CS.clkRegs.setwordclkdiv2(wordclkdiv2)
			  .Write2DUT(61);
	CS.clkRegs.setcmldiv(cmldiv)
			  .setfbdivp(CSpara.PDiv)
			  .setfbdivs(CSpara.SDiv)
			  .setrefclkdiv(CSpara.Mdiv)
			  .Write2DUT(1);
	CS.clkRegs.setwordclkdiv(wordclkdiv)
			  .Write2DUT(61);
//
//	CS.clkRegs.setcmldivbiascal(0x5)
//			  .Write2DUT(6);

	hout(DETAIL) << "CUSTpara.CSslice :" 	<< CUSTpara.CSslice 	<< endl;
	hout(DETAIL) << "SSpara.RefclkBus :" 	<< SSpara.RefclkBus 	<< endl;
	hout(DETAIL) << "SSpara.SDiv:" 			<< SSpara.SDiv 			<< endl;
	hout(DETAIL) << "CSpara.KaDiv :" 		<< CSpara.KaDiv 		<< endl;
	hout(DETAIL) << "CSpara.KbDiv :" 		<< CSpara.KbDiv 		<< endl;
	hout(DETAIL) << "CSpara.NDiv :" << dec	<< CSpara.NDiv 			<< endl;
	hout(DETAIL) << "CSpara.WDiv :" 		<< CSpara.WDiv 			<< endl;
	hout(DETAIL) << "CSpara.JDiv :" << dec	<< CSpara.JDiv 			<< endl;
	hout(DETAIL) << "CSpara.PDiv :" << dec	<< CSpara.PDiv 			<< endl;
	hout(DETAIL) << "CSpara.SDiv :" << dec	<< CSpara.SDiv 			<< endl;
	hout(DETAIL) << "CSpara.Mdiv :" 		<< CSpara.Mdiv 			<< endl;
	hout(DETAIL) << "cmldiv :" 				<< cmldiv 				<< endl;
	hout(DETAIL) << "wordclkdiv2 :" 		<< wordclkdiv2 			<< endl;
	hout(DETAIL) << "wordclkdiv :" 			<< wordclkdiv 			<< endl;
	hout(DETAIL) << "CUSTpara.Data_Rate :"  << dec 	<< CUSTpara.Data_Rate 	<< endl;
	if (CUSTpara.SSCGen_EN || CUSTpara.SSCDR_EN)
	{
		hout(DETAIL) << "CUSTpara.SSCGen_EN :"   	<< CUSTpara.SSCGen_EN << endl;
		hout(DETAIL) << "CUSTpara.SSCDR_EN :"   		<< CUSTpara.SSCDR_EN << endl;
		hout(DETAIL) << "CUSTpara.Protocol :"  	 		<< CUSTpara.Protocol 	<< endl;
	}
}



void DSconfigurationbeforecalibration(const MACRO_LANE_SEL& MacroLane_Sel, GLOBAL_CUSTPARA& CUSTpara)
{
	d2s_JTAG & jtag = d2s_JTAG::Instance();

	DS.Broadcast();

	DS.txRegs.settxpwrdb(0x1).Write2DUT(0);
	DS.rxRegs.setrxpwrdb(0x1).Write2DUT(0);

	DS.clkRegs.setinjen(0x0).Write2DUT(1);
	DS.clkRegs.setdsclk_cml2cmos_pwrdnb(0x0).Write2DUT(29);
	DS.clkRegs.setautotune(0x4).Write2DUT(9);

	DS.clkRegs.setclkspinesel(CUSTpara.CSslice).Write2DUT(0);
	/*
	DS.clkRegs.settxbypassen(0).Write2DUT(0);
	DS.clkRegs.settxclkspinesel(CUSTpara.CSslice).Write2DUT(0);
	*/
	/*******************HiLinkX**************************/
	DS.clkRegs.setvreglowlvl(0x2).Write2DUT(4);
	DS.clkRegs.setioscptune(0x1).Write2DUT(3);
	/*******************HiLinkX**************************/

	jtag.wait(200*0.000001);/***make sure dataslice bias and ring VCO stable***/

	/*
	DS.txRegs.settxbitorder(0)
			 .settxpolarity(0).Write2DUT(2);
	*/
	/*Select the clock to which the TX clock is aligned.
	 * 00 = Choose the clock coming along with the TX data from the core;
	 * 01 = Choose the recovered clock from the RX;
	 * 10 = Choose the mclk;
	 * 11 = Choose the clock derived from one of the clock spines.
	 * */
	/*Select the parallel TX data to be sent.
	 * 00 = select core data (i.e., TXD).
	 * 01 = select RX parallel data (parallel loop back).
	 * 10 = select pattern for PRBS generation.
	 * 11 = Reserved for future use
	 * */

	DS.txRegs.settxratemode(CUSTpara.RateMode)
			 .settxclksel(2)						/*Select the clock to which the TX clock is aligned.*/
			 .settxdatasel(2)						/*Select the parallel TX data to be sent.*/
			 .settxalignmode(3)						/*freeze mode*/
			 .Write2DUT(2);

	if(CUSTpara.FIR_setting == "DEFAULT_SETTING")
	{
		if (CUSTpara.RateMode == 0)
		{
			DS.txRegs.settxfirpre1((TxFIR_DEFAULT.iTxPre1st < 0) ? (0x10 | abs(TxFIR_DEFAULT.iTxPre1st)) : TxFIR_DEFAULT.iTxPre1st)
				  .settxfirpre2((TxFIR_DEFAULT.iTxPre2nd < 0) ? (0x10 | abs(TxFIR_DEFAULT.iTxPre2nd)) : TxFIR_DEFAULT.iTxPre2nd)
				  .Write2DUT(0);
			DS.txRegs.settxfirmain(TxFIR_DEFAULT.iTxMain)
				  .settxfirpost1((TxFIR_DEFAULT.iTxPost1st < 0) ? (0x10 | abs(TxFIR_DEFAULT.iTxPost1st)) : TxFIR_DEFAULT.iTxPost1st)
				  .settxfirpost2((TxFIR_DEFAULT.iTxPost2nd < 0) ? (0x10 | abs(TxFIR_DEFAULT.iTxPost2nd)) : TxFIR_DEFAULT.iTxPost2nd)
				  .Write2DUT(1);
		}
		else if (CUSTpara.RateMode == 1)
		{
			DS.txRegs.settxfirpre1(0)
				  .settxfirpre2((TxFIR_DEFAULT.iTxPre2nd < 0) ? (0x10 | abs(TxFIR_DEFAULT.iTxPre2nd)) : TxFIR_DEFAULT.iTxPre2nd)/*Act as pre1*/
				  .Write2DUT(0);
			DS.txRegs.settxfirmain(TxFIR_DEFAULT.iTxMain)
				  .settxfirpost1(0)
				  .settxfirpost2((TxFIR_DEFAULT.iTxPost2nd < 0) ? (0x10 | abs(TxFIR_DEFAULT.iTxPost2nd)) : TxFIR_DEFAULT.iTxPost2nd)/*Act as post1*/
				  .Write2DUT(1);
		}
		else
		{
			DS.txRegs.settxfirpre1(0)
				  .settxfirpre2(0)
				  .Write2DUT(0);
			DS.txRegs.settxfirmain(TxFIR_DEFAULT.iTxMain)
				  .settxfirpost1(0)
				  .settxfirpost2(0)
				  .Write2DUT(1);
		}
		if (TxFIR_DEFAULT.iTxPre2nd != 0 || TxFIR_DEFAULT.iTxPost2nd != 0)
		{
			DS.txRegs.settxtappwrdb (0xff).Write2DUT(10);
		}
		else
		{
			DS.txRegs.settxtappwrdb (0xf6).Write2DUT(10);
		}
	}
	else if (CUSTpara.FIR_setting == "USER_SETTING")
	{
		if (CUSTpara.RateMode == 0)
		{
			DS.txRegs.settxfirpre1((CUSTpara.TxFIR_USER.iTxPre1st < 0) ? (0x10 | abs(CUSTpara.TxFIR_USER.iTxPre1st)) : CUSTpara.TxFIR_USER.iTxPre1st)
				  .settxfirpre2((CUSTpara.TxFIR_USER.iTxPre2nd < 0) ? (0x10 | abs(CUSTpara.TxFIR_USER.iTxPre2nd)) : CUSTpara.TxFIR_USER.iTxPre2nd)
				  .Write2DUT(0);
			DS.txRegs.settxfirmain(CUSTpara.TxFIR_USER.iTxMain)
				  .settxfirpost1((CUSTpara.TxFIR_USER.iTxPost1st < 0) ? (0x10 | abs(CUSTpara.TxFIR_USER.iTxPost1st)) : CUSTpara.TxFIR_USER.iTxPost1st)
				  .settxfirpost2((CUSTpara.TxFIR_USER.iTxPost2nd < 0) ? (0x10 | abs(CUSTpara.TxFIR_USER.iTxPost2nd)) : CUSTpara.TxFIR_USER.iTxPost2nd)
				  .Write2DUT(1);
		}
		else if (CUSTpara.RateMode == 1)
		{
			DS.txRegs.settxfirpre1(0)
				  .settxfirpre2((CUSTpara.TxFIR_USER.iTxPre2nd < 0) ? (0x10 | abs(CUSTpara.TxFIR_USER.iTxPre2nd)) : CUSTpara.TxFIR_USER.iTxPre2nd)/*Act as pre1*/
				  .Write2DUT(0);
			DS.txRegs.settxfirmain(CUSTpara.TxFIR_USER.iTxMain)
				  .settxfirpost1(0)
				  .settxfirpost2((CUSTpara.TxFIR_USER.iTxPost2nd < 0) ? (0x10 | abs(CUSTpara.TxFIR_USER.iTxPost2nd)) : CUSTpara.TxFIR_USER.iTxPost2nd)/*Act as post1*/
				  .Write2DUT(1);
		}
		else
		{
			DS.txRegs.settxfirpre1(0)
				  .settxfirpre2(0)
				  .Write2DUT(0);
			DS.txRegs.settxfirmain(CUSTpara.TxFIR_USER.iTxMain)
				  .settxfirpost1(0)
				  .settxfirpost2(0)
				  .Write2DUT(1);
		}
		if (CUSTpara.TxFIR_USER.iTxPre2nd != 0 || CUSTpara.TxFIR_USER.iTxPost2nd != 0)
		{
			DS.txRegs.settxtappwrdb(0xff).Write2DUT(10);
		}
		else
		{
			DS.txRegs.settxtappwrdb(0xf6).Write2DUT(10);
		}
	}

	/***********TXTDRVRES: 1 == 50 ohm; 2 == 45 ohm **************/
	DS.txRegs.settxdrv_ressel(CUSTpara.TxDrvResSel).Write2DUT(34);

	DS.txRegs.settxdwidth(CUSTpara.DataWidth)
			 .Write2DUT(2);

	DS.rxRegs.setrxratemode(CUSTpara.RateMode)
			 .Write2DUT(10);
	/*
	DS.rxRegs.setrxbitorder(0)
			 .setrxpolarity(0).Write2DUT(10);
	*/

	/**set center phase offset according to ratemode*****/
	if (CUSTpara.RateMode == 0)
	{
		DS.rxRegs.setcphsofst(0x20).Write2DUT(12);
	}
	else
	{
		DS.rxRegs.setcphsofst(0x00).Write2DUT(12);
	}

	/***********RXTERMRES: 0 == 50 ohm; 1 == 45 ohm **************/
	DS.rxRegs.setrxterm_ressel(CUSTpara.RxTermResSel).Write2DUT(31);

	DS.rxRegs.setctlepassgn(0x1).Write2DUT(0);

//	DS.rxRegs.setrxctlerefsel(CUSTpara.RxCTLERefSel).Write2DUT(39);
	/*CTLE GAIN BOOST SETUP*/
	if(CUSTpara.CTLE_setting == "DEFAULT_SETTING")
	{
		SetRxCTLE(RxCTLE_DEFAULT);
	}
	else if (CUSTpara.CTLE_setting == "USER_SETTING")
	{
		SetRxCTLE(CUSTpara.RxCTLE_USER);
	}

	DS.rxRegs.setrxdwidth(CUSTpara.DataWidth)
			 .Write2DUT(10);
	DS.clkRegs.setautotune(0x0).Write2DUT(9);

	DS.clkRegs.setvreglpwrdb(0x1).Write2DUT(1);
}


void CsConfigAPIRegsBeforeCal(UINT MacroID, INT CSslice)
{
	d2s_JTAG & jtag = d2s_JTAG::Instance();
//	DOUBLE              Temp;
//	GET_USER_DOUBLE		("Ttemp",&Temp);
//	if (Temp < 0) {
//		Temp += 256;
//	}
	INT 			CS0TypeAPI;
	INT 			CS1TypeAPI;
//	INT				TempAPI;

	/******choose CS type Auto*******/
	if (HILINK_INFO[MacroID].CS0_Type == CSL) {
		CS0TypeAPI = 0x0002;
	} else if (HILINK_INFO[MacroID].CS0_Type == CSH) {
		CS0TypeAPI = 0x0003;
	} else {
		CS0TypeAPI = 0x0000;
	}


	if (HILINK_INFO[MacroID].CS1_Type == CSL) {
		CS1TypeAPI = 0x0020;
	} else if (HILINK_INFO[MacroID].CS1_Type == CSH) {
		CS1TypeAPI = 0x0030;
	} else {
		CS1TypeAPI = 0x0000;
	}

	/******choose temp Auto*******/

//	TempAPI = (int)Temp << 8;

	MCU.mcuRegs.setmcurstb(0).Write2DUT(0);

//	if (CSslice == 0) {
//		jtag.write(0x1FFEC>>1,CS0TypeAPI | TempAPI);
//	} else {
//		jtag.write(0x1FFEC>>1,CS1TypeAPI | TempAPI);
//	}

//	jtag.write(0x1FFEE>>1,0x0000);

	if (CSslice == 0) {
		jtag.write(0x1FFEC>>1,0x0002);
	} else {
		jtag.write(0x1FFEC>>1,0x0020);
	}
}


void DsConfigAPIRegsBeforeCal(INT MacroNum)
{
	INT					data_slice = 0x1FFF0;
	INT					DS_OFFSET = 0x2;
	INT 				laneSize = 16;/*******For Broadcast*******/

	d2s_JTAG & jtag = d2s_JTAG::Instance();

	if (laneSize % 2 == 0) {
		for (INT i = 0; i < laneSize / 2; i ++, data_slice +=  DS_OFFSET)
		{
			jtag.write(data_slice>>1,0x8080); /**Enable calibration**/
		}
	} else {
		for (INT i = 0; i < (laneSize - 1) / 2; i ++, data_slice +=  DS_OFFSET)
		{
			jtag.write(data_slice>>1,0x8080); /**Enable calibration**/
		}
		data_slice += DS_OFFSET;
		jtag.write(data_slice>>1,0x0080); /**Enable calibration**/
	}
}


void ExpectCSandDSCalibrationDone(const MACRO_LANE_SEL& MacroLane_Sel, STRING sWaitCalDoneLabelName, STRING sCalibrationType)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	/**************Expect CS and DS Cal result***************/
	d2s::d2s_LABEL_BEGIN(sWaitCalDoneLabelName,Global_D2S_Mode);

		jtag.enablePassFailCheckForNextExecution();

		INT				DS_OFFSET = 0x2;

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			INT				data_slice = 0x1FFF0;
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);
			/***************Expect TOP API****************/
			jtag.expectValue(0x1FFEE>>1, 3, 0xfff0);

			/***************Expect CS API****************/
			if (CUSTpara.CSslice == 0) {
				if (HILINK_INFO[MacroID].CS0_Type == CSL) {
					jtag.expectValue(0x1FFEC>>1, 0xa, 0xfff0);
				} else if (HILINK_INFO[MacroID].CS0_Type == CSH) {
					jtag.expectValue(0x1FFEC>>1, 0xa, 0xfff0);
				} else {
					hout(GENERAL) << "+++++++++++ INVALID TYPE OF CS0 ++++++++++++" << endl;
				}
			} else {
				if (HILINK_INFO[MacroID].CS1_Type == CSL) {
					jtag.expectValue(0x1FFEC>>1, 0xa<<4, 0xff0f);
				} else if (HILINK_INFO[MacroID].CS1_Type == CSH) {
					jtag.expectValue(0x1FFEC>>1, 0xa<<4, 0xff0f);
				} else {
					hout(GENERAL) << "+++++++++++ INVALID TYPE OF CS1 ++++++++++++" << endl;
				}
			}

			/***************Expect DS API****************/
			if (sCalibrationType != "VCO") {
				if (vLane.size() % 2 == 0) {
					for (UINT i = 0; i < vLane.size() / 2; i ++, data_slice +=  DS_OFFSET)
					{
						jtag.expectValue(data_slice>>1, 0xc0c0, 0x0000);
					}
				} else {
					for (UINT i = 0; i < (vLane.size() - 1) / 2; i ++, data_slice +=  DS_OFFSET)
					{
						jtag.expectValue(data_slice>>1, 0xc0c0, 0x0000);
					}
					data_slice +=  DS_OFFSET;
					jtag.expectValue(data_slice>>1, 0x00c0, 0xff00);
				}
			}

			/***********Expect CS registor vcooutoflock***********/
			CS.clkRegs.MacroID(MacroID).SliceID(CUSTpara.CSslice).Broadcast(0);
			CS.clkRegs.ExpectValue(2, 0, 0xfffd);

			/***********Expect DS registor ringvcooutoflock***********/
			if (sCalibrationType != "VCO") {
				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					DS.clkRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
					DS.clkRegs.ExpectValue(0, 0, 0xfffd);
				}
			}
		}

	d2s::d2s_LABEL_END();
}


void ExpectFWPIEyeScanDone(const MACRO_LANE_SEL& MacroLane_Sel, STRING sWaitAPIEYEDoneLabelName)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	d2s::d2s_LABEL_BEGIN(sWaitAPIEYEDoneLabelName, Global_D2S_Mode);

		jtag.enablePassFailCheckForNextExecution();

		INT					DS_OFFSET = 0x2;

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			INT				data_slice = 0x1FFF0;
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			/***************Expect TOP API****************/
			jtag.expectValue(0x1FFEE>>1, 3, 0xfff0);

			/***************Expect DS API****************/
			if (vLane.size() % 2 == 0)
			{
				for (UINT i = 0; i < vLane.size() / 2; i ++, data_slice +=  DS_OFFSET)
				{
					jtag.expectValue(data_slice>>1, 0, 0xfefe);
				}
			}
			else
			{
				for (UINT i = 0; i < (vLane.size() - 1) / 2; i ++, data_slice +=  DS_OFFSET)
				{
					jtag.expectValue(data_slice>>1, 0, 0xfefe);
				}
				data_slice +=  DS_OFFSET;
				jtag.expectValue(data_slice>>1, 0, 0xfffe);
			}
		}

	d2s::d2s_LABEL_END();
}



void CsConfigaftercalibration(MACRO_LANE_SEL MacroLane_Sel, GLOBAL_CUSTPARA CUSTpara)
{
	if (CUSTpara.SSCGen_EN) {
		d2s_JTAG& jtag = d2s_JTAG::Instance();
		MACRO_INT	CSR7value;
		CSR_READ(MacroLane_Sel, CUSTpara.CSslice, CS.clkRegs, 7, CSR7value);

		MACRO_INT	CS_CALIB_FSM_STATUS;
		MACRO_INT	CS_GCALIB_FSM_STATUS;
		SEGMENT_READ(MacroLane_Sel, CUSTpara.CSslice,CS.clkRegs.REG_INFO.cs_calib_fsm_status(),CS_CALIB_FSM_STATUS);
		SEGMENT_READ(MacroLane_Sel, CUSTpara.CSslice,CS.clkRegs.REG_INFO.cs_gcalib_fsm_status(),CS_GCALIB_FSM_STATUS);

		MACRO_INT	CS_CALIB_FSM_STATUS_BIT14_9;
		MACRO_INT	CS_CALIB_FSM_STATUS_BIT_7_3;
		MACRO_INT	CS_GCALIB_FSM_STATUS_BIT14_12;

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				CS_CALIB_FSM_STATUS_BIT14_9[SiteID][MacroID] = (CS_CALIB_FSM_STATUS[SiteID][MacroID]&0x7E00)>>9 ;
				CS_CALIB_FSM_STATUS_BIT_7_3[SiteID][MacroID] = (CS_CALIB_FSM_STATUS[SiteID][MacroID]&0x00F8)>>3;
				CS_GCALIB_FSM_STATUS_BIT14_12[SiteID][MacroID] = (CS_GCALIB_FSM_STATUS[SiteID][MacroID]&0x7000)>>12;
			}
		FOREACH_ACTIVESITE_END

	    Update_ForDynamicWrite(MacroLane_Sel, CS.clkRegs.REG_INFO.lcvcofreqcal(), CS_CALIB_FSM_STATUS_BIT14_9, CSR7value);
	    Update_ForDynamicWrite(MacroLane_Sel, CS.clkRegs.REG_INFO.lcvcoitank(), CS_CALIB_FSM_STATUS_BIT_7_3, CSR7value);
	    Update_ForDynamicWrite(MacroLane_Sel, CS.clkRegs.REG_INFO.lcvcobandsel(), CS_GCALIB_FSM_STATUS_BIT14_12, CSR7value);

		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_CSCONFIGURATIONAFTERCALIBRATION_Part1",Global_D2S_Mode);

			CS.clkRegs.addSkipCheckCSR(13);

			selectMacro_MB(MacroLane_Sel);

			CS.clkRegs.setlcvcocalmode(0x1).Write2DUT(13);
			CS.clkRegs.setcalrstb(0x1).Write2DUT(12);

		d2s::d2s_LABEL_END();


		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_CSCONFIGURATIONAFTERCALIBRATION_Part2",Global_D2S_Mode);

			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				selectMacro(MacroID);
				CS.clkRegs.MacroID(MacroID).SliceID(CUSTpara.CSslice).Broadcast(0);

                ostringstream id7;
                id7 << "CSCLK_CSR7_" << "_M" << MacroID << "_CS" << CUSTpara.CSslice << jtag.Context;
                map<int,long long> tmp7;
                parseSiteDataFromMacroInt(tmp7,CSR7value,MacroID);
				CS.clkRegs.Write2DUT_DYN(7,tmp7,id7.str());
			}

		d2s::d2s_LABEL_END();

		MACRO_INT	LCVCOFREQCAL;
		SEGMENT_READ(MacroLane_Sel, CUSTpara.CSslice,CS.clkRegs.REG_INFO.lcvcofreqcal(),LCVCOFREQCAL);

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				LCVCOFREQCAL[SiteID][MacroID] += 1;
			}
		FOREACH_ACTIVESITE_END

	    Update_ForDynamicWrite(MacroLane_Sel, CS.clkRegs.REG_INFO.lcvcofreqcal(), LCVCOFREQCAL, CSR7value);


		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_CSCONFIGURATIONAFTERCALIBRATION_Part3",Global_D2S_Mode);

			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				selectMacro(MacroID);
				CS.clkRegs.MacroID(MacroID).SliceID(CUSTpara.CSslice).Broadcast(0);

                ostringstream id7;
                id7 << "CSCLK_CSR7_" << "_M" << MacroID << "_CS" << CUSTpara.CSslice << jtag.Context;
                map<int,long long> tmp7;
                parseSiteDataFromMacroInt(tmp7,CSR7value,MacroID);
				CS.clkRegs.Write2DUT_DYN(7,tmp7,id7.str());
			}

		d2s::d2s_LABEL_END();
	}
}

void DsConfigurationAfterCalibration(MACRO_LANE_SEL MacroLane_Sel, GLOBAL_CUSTPARA CUSTpara)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	INT 				iDataWidth = DS.txRegs.gettxdwidth();
	INT 				iRateMode = DS.txRegs.gettxratemode();
	sprintf(label,"H16LRTV100_MPB_DSCONFIGURATIONAFTERCALIBRATION_RateMode%d_DataWidth%d",iRateMode,iDataWidth);
	d2s::d2s_LABEL_BEGIN(label,Global_D2S_Mode);

		DS.clkRegs.addSkipCheckCSR(0);

		selectMacro_MB(MacroLane_Sel);
		DS.Broadcast();

		DS.txRegs.settxregdrvlvl(CUSTpara.TxRegDrvLvl).Write2DUT(11);

		if (CUSTpara.RxCapBypass == 0) {
			DS.rxRegs.setrxcapbypass(0).Write2DUT(0);
			DS.rxRegs.setrxterm_floating_en(0).Write2DUT(27);   /*******low-impedance*********/
		} else {
			DS.rxRegs.setrxcapbypass(1).Write2DUT(0);
			DS.rxRegs.setrxterm_floating_en(1).Write2DUT(27);   /*******high-impedance********/
		}

//		DS.txRegs.setpma_mode(0x2).Write2DUT(48);

		if (CUSTpara.SSCDR_EN) {
			DS.rxRegs.setcdr_mode(1).Write2DUT(10);
			DS.clkRegs.setringvcololthr(0x1F).Write2DUT(0);

			if (CUSTpara.Protocol == "SAS" || CUSTpara.Protocol == "SATA" ) {
				DS.rxRegs.setsscdr_sftrst_ctrl(0x1).Write2DUT(51);
				if (CUSTpara.Data_Rate == 12) {
					DS.rxRegs.setsscdr_demux_mode(0x1).Write2DUT(51);
				}
			}
		}

		INT					pcie_wrate_hsclk_sel;
		if (CUSTpara.Protocol == "PCIE") {
			if (CUSTpara.Data_Rate == 2.5 || CUSTpara.Data_Rate == 5) {
				if (CUSTpara.CSslice == 0) {
					pcie_wrate_hsclk_sel = 0x0;
				} else {
					pcie_wrate_hsclk_sel = 0x1;
				}
			} else if (CUSTpara.Data_Rate == 8) {
				if (CUSTpara.CSslice == 0) {
					pcie_wrate_hsclk_sel = 0x1;
				} else {
					pcie_wrate_hsclk_sel = 0x0;
				}
			} else {
				hout(RELEASE) << "DataRate = " << CUSTpara.Data_Rate << " is not a valid option for PCIE protocol!!" << endl;
				_exit(0);
			}
			DS.txRegs.setpcie_wrate_hsclk_sel(pcie_wrate_hsclk_sel).Write2DUT(34);
		} else if (CUSTpara.Protocol == "SAS" || CUSTpara.Protocol == "SATA" ) {
			if (CUSTpara.Data_Rate == 1.5 || CUSTpara.Data_Rate == 3 || CUSTpara.Data_Rate == 6) {
				if (CUSTpara.CSslice == 0) {
					pcie_wrate_hsclk_sel = 0x0;
				} else {
					pcie_wrate_hsclk_sel = 0x1;
				}
			} else if (CUSTpara.Data_Rate == 12) {
				if (CUSTpara.CSslice == 0) {
					pcie_wrate_hsclk_sel = 0x1;
				} else {
					pcie_wrate_hsclk_sel = 0x0;
				}
			} else {
				hout(RELEASE) << "DataRate = " << CUSTpara.Data_Rate << " is not a valid option for SAS protocol!!" << endl;
				_exit(0);
			}
			DS.txRegs.setpcie_wrate_hsclk_sel(pcie_wrate_hsclk_sel).Write2DUT(34);
		} else {
			hout(DETAIL) << "COMMON MODE" << endl;
		}

		/*******open all driver taps to enhance the Tx ffe Capability*/
		DS.txRegs.settxtappwrdb(0xff).Write2DUT(10);
		DS.txRegs.settxdrv_map_sel(0x0).Write2DUT(34);

	d2s::d2s_LABEL_END();
}


void Clear_All_API_Regs()
{
	d2s_JTAG & jtag = d2s_JTAG::Instance();
	INT 			iRegAddrLoop = 0x1FF6C;
	for (iRegAddrLoop = 0x1FF6C; iRegAddrLoop <= 0x1FFFE; iRegAddrLoop += 2)
	{
		jtag.write(iRegAddrLoop>>1,0x0000);
	}
}


SITE_PASSFAIL_RESULT HiLink16_FW_CAL(const MACRO_LANE_SEL& MacroLane_Sel, GLOBAL_CUSTPARA& CUSTpara, GLOBAL_SSPARA& SSpara, GLOBAL_CSPARA& CSpara, MACRO_INT &CS_Cal_MacroResult, MACRO_INT &DS_Cal_MacroResult, LANE_INT& DS_Cal_LaneResult, STRING sCalibrationType, INT iDownLoadHex)
{
	INT					iOffline;
//	GET_SYSTEM_FLAG		("offline",&iOffline);
	iOffline = 0;

	SITE_PASSFAIL_RESULT 	CSCalResult;
	SITE_PASSFAIL_RESULT 	DSCalResult;
	SITE_PASSFAIL_RESULT  	CalResult;

	DOUBLE 				dCalTotalTime_ms = 0.0;
	DOUBLE 				dCalMaxTime_ms = 2000.0;

	if (iOffline || sCalibrationType == "VCO" || sCalibrationType == "VCOILO" ) {
		dCalMaxTime_ms = 200;
	}

	hout(GENERAL) << "&&&&&&&&&&&&& Calibration START! &&&&&&&&&&&&&&&" << endl;

	d2s_JTAG& jtag = d2s_JTAG::Instance();

	/**************Clear API and CSConfigBeforeCal***set proper API depending on applications and Release MCU*********/
	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_FWDownLoadHEX_Clear_CSDSConfig_ReleaseMCU",Global_D2S_Mode);

		DS.clkRegs.addSkipCheckCSR(0);
		DS.clkRegs.addSkipCheckCSR(9);
		DS.rxRegs.addSkipCheckCSR(31);

		selectMacro_MB(MacroLane_Sel);

		/****Load Hex file to MCU****/
		if (iDownLoadHex == 1) {
			if (jtag.Context == "DEFAULT") {
//				unsigned long long FWCycle = PatternManager::getCyclesFromLabel("HiLink_Ctle_Dfe.hex.bin_WRITE_STD", "pJTAG");
//				jtag.execLabel(HILINK_FIRMWARE_LABEL + "_STD", HILINK_FIRMWARE_CYCLE);
				string patternName;
			    patternName = HILINK_FIRMWARE_LABEL; //block check OK
			    TheInst.Digital().Pattern().Start(patternName);
			} else {
//				unsigned long long FWCycle = PatternManager::getCyclesFromLabel("HiLink_Ctle_Dfe.hex.bin_WRITE_FASTDIFF", "pJTAG");
//				jtag.execLabel(HILINK_FIRMWARE_LABEL + "_FASTDIFF", HILINK_FIRMWARE_CYCLE);
				string patternName;
			    patternName = HILINK_FIRMWARE_LABEL; //block check OK
			    TheInst.Digital().Pattern().Start(patternName);
			}
		}

		/******clear API space******/
		MCU.mcuRegs.setmcurstb(0).Write2DUT(0);
		Clear_All_API_Regs();

		/******CSConfigBeforeCal*******/
		CsConfigurationbeforecalibration(MacroLane_Sel, CUSTpara, SSpara, CSpara);
		if (sCalibrationType != "VCO"){
			DSconfigurationbeforecalibration(MacroLane_Sel, CUSTpara);
		}

		CsConfigAPIRegsBeforeCal(MacroLane_Sel[0].MacroID, CUSTpara.CSslice);
		if (sCalibrationType != "VCO"){
			DsConfigAPIRegsBeforeCal(MacroLane_Sel[0].MacroID);
		}

		/****Release MCU from reset ****/
		MCU.mcuRegs.setmcurstb(1).Write2DUT(0);

	d2s::d2s_LABEL_END();


	CS_Cal_MacroResult.init(0);
	DS_Cal_MacroResult.init(0);
	DS_Cal_LaneResult.init(0);
	/******check code running status and wait for calibration done******/
	/*****this timer is used in CS cal , do not remove it.***/
//	MyTimer::start("CalTime");
//	/*****this timer is used in CS cal , do not remove it.***/
//	dCalTotalTime_ms = MyTimer::stop_no_print("CalTime");
//
//	TheInst.Wait(10*0.001); //todo
//
//	while ((dCalTotalTime_ms < dCalMaxTime_ms) && (false == CalResult.isAllSitePassed())) {
//		STRING		sWaitCalDoneLabelName = "H15_Cal_CHECK_EXPECTVALUE";
//		ExpectCSandDSCalibrationDone(MacroLane_Sel, sWaitCalDoneLabelName, sCalibrationType);
//		if (jtag.hasAllSitesPassed(sWaitCalDoneLabelName)) {
//			CalResult.init(true);
//		}
//
//		dCalTotalTime_ms = MyTimer::stop_no_print("CalTime");
//		hout(DETAIL) << "dCalTotalTime_ms:" << dCalTotalTime_ms << endl;
//	}

    INT iCheckCount = 0;
    INT iMaxTimeout = 200;

	while ((iCheckCount < iMaxTimeout) && (false == CalResult.isAllSitePassed())) {
		STRING		sWaitCalDoneLabelName = "H16LRV100_Cal_CHECK_EXPECTVALUE";
		ExpectCSandDSCalibrationDone(MacroLane_Sel, sWaitCalDoneLabelName, sCalibrationType);
		if (hasAllSitesPassed()) {
			CalResult.init(true);
		}

		TheInst.Wait(0.002);
        iCheckCount++;
        hout(DETAIL) << "count " << iCheckCount << endl;
	}

	if ((CalResult.isAllSitePassed() && (1 == Global_D2S_Mode)) || iOffline) {
		hout(DETAIL) << "++++++++++++jtag.hasPassed(label)+++++++++++++++" << endl;
		CalResult.init(true);
		CSCalResult.init(true);
		DSCalResult.init(true);
		CS_Cal_MacroResult.init(1);
		DS_Cal_MacroResult.init(1);
		DS_Cal_LaneResult.init(1);
	} else {
		CSCalResult = check_CS_top_API(MacroLane_Sel, CUSTpara.CSslice, CS_Cal_MacroResult);
		if (sCalibrationType != "VCO"){
			DSCalResult = check_DS_top_API(MacroLane_Sel, DS_Cal_MacroResult, DS_Cal_LaneResult);
		} else {
			DSCalResult.init(true);
		}

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			if (CSCalResult[SiteID] and DSCalResult[SiteID]) {
				CalResult[SiteID] = true;
			}
		FOREACH_ACTIVESITE_END

		if ((CalResult.isAllSitePassed()) && (1 == Global_D2S_Mode)) {
			hout(GENERAL) << "++++++++++++ Unconsistence Calibration result between ExpectValue and Read +++++++++++++++" << endl;
		}
	}

	if (sCalibrationType != "VCO" && sCalibrationType != "VCOILO") {
		/*ONLY WHEN ALL DS IS DONE CAN WE CONFIGDSAFTERCAL*/
		CsConfigaftercalibration(MacroLane_Sel, CUSTpara);
		DsConfigurationAfterCalibration(MacroLane_Sel, CUSTpara);
	}

	if (CalResult.isAllSitePassed()) {
		hout(GENERAL) << "&&&&&&&&&&&&& Calibration DONE ! &&&&&&&&&&&&&&&" << endl;
	} else {
		hout(GENERAL) << "&&&&&&&&&&&&& Calibration FAIL ! &&&&&&&&&&&&&&&" << endl;
	}

	/* Hold MCU in Reset */
	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ResetMCU_AfterCal",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		/****Hold MCU in Reset mode****/
		MCU.mcuRegs.setmcurstb(0).Write2DUT(0);

	d2s::d2s_LABEL_END();

	return CalResult;
}


void FWreadDefaultRegisters2CSR(const MACRO_LANE_SEL& MacroLane_Sel)
{
    /*******Only read macro[0], for There is only one local DS file ***********/
	UINT	MacroID = MacroLane_Sel[0].MacroID;
	UINT	SliceID = 0;
	UINT	LaneID = MacroLane_Sel[0].vLane[0];

	CS.clkRegs.MacroID(MacroID).SliceID(SliceID).Broadcast(0);
	MCU.mcuRegs.MacroID(MacroID).SliceID(SliceID).Broadcast(0);
	DS.clkRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
	DS.txRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
	DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);

	CS.clkRegs.ReadAll2CSR();
	MCU.mcuRegs.ReadAll2CSR();
	DS.clkRegs.ReadAll2CSR();
	DS.txRegs.ReadAll2CSR();
	DS.rxRegs.ReadAll2CSR();
}


void HiLinkPowerUpCtrl(const STRING sPowerUpCtrlVectorName)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	string patternName;

	if (jtag.Context == "DEFAULT") {
//		Primary.label(sPowerUpCtrlVectorName + "_STD");
//		Primary.label(sPowerUpCtrlVectorName);
		patternName = sPowerUpCtrlVectorName;
	} else {
//		Primary.label(sPowerUpCtrlVectorName + "_FASTDIFF");
		patternName = sPowerUpCtrlVectorName + "_FASTDIFF";
	}

//	FLUSH();
//	FUNCTIONAL_TEST();
	TheInst.Digital().Pattern().Start(patternName);

	return;
}

void HiLinkResetAndInit(const STRING sInitVectorName)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	string patternName;
	if (jtag.Context == "DEFAULT") {
//		Primary.label(sInitVectorName + "_STD");
//		Primary.label(sInitVectorName );
		patternName = sInitVectorName;
	} else {
//		Primary.label(sInitVectorName + "_FASTDIFF");
		patternName = sInitVectorName + "_FASTDIFF";
	}

//	FLUSH();
//	FUNCTIONAL_TEST();
	TheInst.Digital().Pattern().Start(patternName);

	return;
}


SITE_PASSFAIL_RESULT check_CS_top_API(const MACRO_LANE_SEL& MacroLane_Sel, INT iCSslice, MACRO_INT& CS_Cal_MacroResult)
{
	SITE_PASSFAIL_RESULT 	CSReadResult;

	d2s_JTAG& jtag = d2s_JTAG::Instance();

	INT				addr1 = 0x1FFEE;
	INT				addr2 = 0x1FFEC;

	MACRO_INT 		Top_API_1FFEE;
	MACRO_INT 		CS_API_1FFEC;
	MACRO_INT 		Vcooutoflock;
	MACRO_INT 		CSResultAPI;
	Top_API_1FFEE.init(0);
	CS_API_1FFEC.init(0);
	Vcooutoflock.init(0);
	CSResultAPI.init(0);

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			if (iCSslice == 0) {
				if (HILINK_INFO[MacroID].CS0_Type == CSL){
					CSResultAPI[SiteID][MacroID] = 0x000a;
				}else if (HILINK_INFO[MacroID].CS0_Type == CSH){
					CSResultAPI[SiteID][MacroID] = 0x000a;
				}else{
					hout(GENERAL) << "++++++++++++ INVALID TYPE OF CS0 ++++++++++++" << endl;
				}
			} else {
				if (HILINK_INFO[MacroID].CS1_Type == CSL){
					CSResultAPI[SiteID][MacroID] = 0x00a0;
				}else if (HILINK_INFO[MacroID].CS1_Type == CSH){
					CSResultAPI[SiteID][MacroID] = 0x00a0;
				}else{
					hout(GENERAL) << "++++++++++++ INVALID TYPE OF CS1 ++++++++++++" << endl;
				}
			}
		}
	FOREACH_ACTIVESITE_END


	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_CSCal_READ",Global_D2S_Mode);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			selectMacro(MacroID);

			ostringstream topapi;
			ostringstream csapi;
			ostringstream id2;
			topapi << "TOPAPI_READ2IDSTRING" << "_0x1FFEE" << "_M" << MacroID <<jtag.Context.c_str();
			csapi << "CSAPI_READ2IDSTRING" << "_0x1FFEC" << "_M" << MacroID << jtag.Context.c_str();
			id2 << "CS_READ2IDSTRING" << "_CSR_2" << "_M" << MacroID << jtag.Context.c_str();

			jtag.read(addr1>>1,topapi.str());
			jtag.read(addr2>>1,csapi.str());
			CS.clkRegs.SliceID(iCSslice).Broadcast(0);
			CS.clkRegs.Read2IDString(2, id2.str());
		}

	d2s::d2s_LABEL_END();

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

			ostringstream topapi;
			ostringstream csapi;
			ostringstream id2;
			topapi << "TOPAPI_READ2IDSTRING" << "_0x1FFEE" << "_M" << MacroID << jtag.Context.c_str();
			csapi << "CSAPI_READ2IDSTRING" << "_0x1FFEC" << "_M" << MacroID << jtag.Context.c_str();
			id2 << "CS_READ2IDSTRING" << "_CSR_2" << "_M" << MacroID << jtag.Context.c_str();

			Top_API_1FFEE[SiteID][MacroID] = (INT)jtag.getReadValue(topapi.str())[SiteID];
			CS_API_1FFEC[SiteID][MacroID] = (INT)jtag.getReadValue(csapi.str())[SiteID];
			CS.clkRegs.csr[2] = (INT)jtag.getReadValue(id2.str())[SiteID];
			Vcooutoflock[SiteID][MacroID] = CS.clkRegs.getlcvcooutoflock();

			hout(DETAIL) << "***************** Macro "<< MacroID << " CS CAL Result:*********************"  		<< endl;
			hout(DETAIL) << "Top_Level_API_1FFEE    & 0x000f:" << hex << (Top_API_1FFEE[SiteID][MacroID] /*& 0x000f*/) 	<< endl;
			hout(DETAIL) << "CS_API_1FFEC           & 0x00ff:" << hex << (CS_API_1FFEC[SiteID][MacroID] & 0x00ff)  	<< endl;
			hout(DETAIL) << "CS_API_1FFEC                   :" << hex << (CS_API_1FFEC[SiteID][MacroID])  			<< endl;
			hout(DETAIL) << "vcooutoflock                   :" << hex << Vcooutoflock[SiteID][MacroID] 			  	<< endl;
			hout(DETAIL) << "*************************************************************"        					<< endl;

			if (((Top_API_1FFEE[SiteID][MacroID] & 0x000f) == 0x0003) &&
				((CS_API_1FFEC[SiteID][MacroID] & 0x00ff) == CSResultAPI[SiteID][MacroID]) &&
				!Vcooutoflock[SiteID][MacroID]){
				CS_Cal_MacroResult[SiteID][MacroID] = 1;
			}
		}
	FOREACH_ACTIVESITE_END

	CSReadResult.init(true);
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			if (0 == CS_Cal_MacroResult[SiteID][MacroID]) {
				CSReadResult[SiteID] = false;
			}
		}
	FOREACH_ACTIVESITE_END

	return CSReadResult;
}









SITE_PASSFAIL_RESULT check_DS_top_API(const MACRO_LANE_SEL& MacroLane_Sel, MACRO_INT& DS_Cal_MacroResult, LANE_INT& DS_Cal_LaneResult)
{
	SITE_PASSFAIL_RESULT 	DSReadResult;

	d2s_JTAG& jtag = d2s_JTAG::Instance();
	/*
	INT 			addr = 0x1FFEE;
	MACRO_INT 		Top_API_1FFEE;
	Top_API_1FFEE.init(0);
	*/
	INT				DS_START = 0X1FFF0;
	INT				DS_OFFSET = 0X2;

	LANE_INT		DS_API;
	LANE_INT 		RingVcooutoflock;
	DS_API.init(0);
	RingVcooutoflock.init(0);

	LANE_INT_ONESITE		ReadFlag;
	ReadFlag.init(0);

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_DSCal_READ",Global_D2S_Mode);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
			selectMacro(MacroID);
			/*
			ostringstream topapi;
			topapi << "TOPAPI_READ2IDSTRING" << "_0x1FFEE" << "_M" << MacroID << jtag.Context.c_str();
			jtag.read(addr>>1,topapi.str());
			*/
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				if (LaneID % 2 == 0) {
					if (0 == ReadFlag[MacroID][LaneID]) {
						INT				addr = DS_START + (LaneID / 2) * DS_OFFSET;
						ostringstream 	dsapi;
						dsapi << "DSAPI_READ2IDSTRING" << "_M" << MacroID << "_L" << LaneID << jtag.Context.c_str();
						jtag.read(addr>>1,dsapi.str());
						ReadFlag[MacroID][LaneID] = 1;
//						ReadFlag[MacroID][LaneID + 1] = 1;
					} else {
						continue;
					}
				} else {
					if (0 == ReadFlag[MacroID][LaneID]) {
						INT				addr = DS_START + ((LaneID - 1) / 2) * DS_OFFSET;
						ostringstream 	dsapi;
						dsapi << "DSAPI_READ2IDSTRING" << "_M" << MacroID << "_L" << LaneID << jtag.Context.c_str();
						jtag.read(addr>>1,dsapi.str());
//						ReadFlag[MacroID][LaneID - 1] = 1;
						ReadFlag[MacroID][LaneID] = 1;
					} else {
						continue;
					}
				}
			}

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				DS.clkRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				ostringstream	id0;
				id0 << "DS_READ2IDSTRING" << "_CSR_0" << "_M" << MacroID << "_L" << LaneID << jtag.Context.c_str();
				DS.clkRegs.Read2IDString(0,id0.str());

			}
		}

	d2s::d2s_LABEL_END();

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			INT		tmp;
			/*
			ostringstream topapi;
			topapi << "TOPAPI_READ2IDSTRING" << "_0x1FFEE" << "_M" << MacroID << jtag.Context.c_str();
			Top_API_1FFEE[SiteID][MacroID] = (INT)jtag.getReadValue(topapi.str())[SiteID];
			hout(DETAIL) << "Top_Level_API_1FFEE & 0x000f:" << (Top_API_1FFEE[SiteID][MacroID] & 0x000f) 	<< endl;
			*/
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				if (1 == ReadFlag[MacroID][LaneID]) {
					ostringstream dsapi;
					dsapi << "DSAPI_READ2IDSTRING" << "_M" << MacroID << "_L" << LaneID << jtag.Context.c_str();
					tmp = (INT)jtag.getReadValue(dsapi.str())[SiteID];
					if (LaneID % 2 == 0) {
						DS_API[SiteID][MacroID][LaneID] = tmp & 0x00ff;
					} else {
						DS_API[SiteID][MacroID][LaneID] = (tmp >> 8) & 0x00ff;
					}
				} else {
					hout(GENERAL) << "MacroID "<< MacroID << "/tLaneID " << LaneID << "Read DS API Error!!!" << endl;
				}
			}

			hout(DETAIL) << "***************** Macro "<< MacroID << " DS CAL Result:*********************" << endl;
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				ostringstream	id0;
				id0 << "DS_READ2IDSTRING" << "_CSR_0" << "_M" << MacroID << "_L" << LaneID << jtag.Context.c_str();
				DS.clkRegs.csr[0] = (INT)jtag.getReadValue(id0.str())[SiteID];
				RingVcooutoflock[SiteID][MacroID][LaneID] = DS.clkRegs.getringvcooutoflock();
				hout(DETAIL) << "**********Lane: " << laneIndex << "**********" << endl;
				hout(DETAIL) << "DS_API:" << hex << DS_API[SiteID][MacroID][LaneID] << endl;
				hout(DETAIL) << "ringvcooutoflock:" << RingVcooutoflock[SiteID][MacroID][LaneID] << endl;
			}
			hout(DETAIL) << "*************************************************************" << endl;
		}
	FOREACH_ACTIVESITE_END

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			DS_Cal_MacroResult[SiteID][MacroID] = 1;
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				if ((0x0040 == (DS_API[SiteID][MacroID][LaneID] & 0x0040)) &&
					0 == RingVcooutoflock[SiteID][MacroID][LaneID]){
					DS_Cal_LaneResult[SiteID][MacroID][LaneID] = 1;
				} else {
					DS_Cal_MacroResult[SiteID][MacroID] = 0;
				}
			}
		}
	FOREACH_ACTIVESITE_END

	DSReadResult.init(true);
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			if (0 == DS_Cal_MacroResult[SiteID][MacroID]) {
				DSReadResult[SiteID] = false;
			}
		}
	FOREACH_ACTIVESITE_END

	return DSReadResult;
}




/**********************Calibration done**************************/





bool ReadBert(const MACRO_LANE_SEL& MacroLane_Sel, PRBS_Pattern mPRBS, LANE_DOUBLE& ErrorCount, STRING TestMode, DOUBLE wait_time_ms)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	INT Errors = 0;
	ErrorCount.init(999);
//	TransactionPort pRX("pHilink16_RX");
//	if (TestMode == "ATE" && CP_FT_Program == "FT")
//	{
//		fr.registerTransactionPort(pRX);
//	}

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ReadBert",Global_D2S_Mode);

		DS.rxRegs.skip_CSR_Check();

//		if (TestMode == "ATE" && CP_FT_Program == "FT")
//		{
//			pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//		}

		selectMacro_MB(MacroLane_Sel);
		DS.Broadcast();

		EnableRxPrbsCheck(mPRBS);

		/*revert prbschkmode to free running mode for bert verify's stability*/
		jtag.wait(100*0.000001);
		DS.rxRegs.setprbschkmode(1).Write2DUT(14);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				DS.rxRegs.ExpectValue(18, 0, 0xffff);
			}
		}

		jtag.wait(wait_time_ms*0.001);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				ostringstream id18;
				id18 << "M" << MacroID << "_L" << LaneID << "_CSR18_" << jtag.Context;
				DS.rxRegs.Read2IDString(18, id18.str());
			}
		}

	d2s::d2s_LABEL_END();

	INT csrindex = 18;

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				Errors = 0;
				ostringstream id18;
				id18 << "M" << MacroID << "_L" << LaneID << "_CSR18_" << jtag.Context;
				INT result = jtag.getReadValue(id18.str())[SiteID];

				DS.rxRegs.csr[csrindex] = (uint)(result);

				if (hout.IsRegAccessEn()) {
					hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  Lane[" << LaneID << "]" << "\tRead ================" << endl;
					DS.rxRegs.DisplayAllSegmentOfCSR(csrindex);
				}


				INT prbsErr = DS.rxRegs.getprbserr();
				INT	prbsCnt = DS.rxRegs.getprbscnt();
				INT	prbsCntExp = DS.rxRegs.getprbscntexp();

				if (1 == prbsCntExp) {
//					Errors = ((1 << 10) + (prbsCnt / 2)) << prbsCntExp;
					Errors = prbsCnt << prbsCntExp;
				} else {
					Errors = prbsCnt;
				}

				ErrorCount[SiteID][MacroID][LaneID] = Errors;

				if (ErrorCount[SiteID][MacroID][LaneID] == 0) {
					hout(DETAIL) << "M" << dec << MacroID << "_L" << LaneID << ": " << "\t" << "No error count" << endl;
					if (prbsErr == 1){hout(DETAIL) << "!!!prbserr(= 1) is not accordance with prbscnt&prbscntexp!!!\n";}
				} else {
					hout(DETAIL) << "M" << dec << MacroID << "_L" << LaneID << ": " << "\t" << "measured error count = " << ErrorCount[SiteID][MacroID][LaneID] << endl;
					if (prbsErr == 0){hout(DETAIL) << "!!!prbserr(= 0) is not accordance with prbscnt&prbscntexp!!!\n";}
				}
			}
		}
	FOREACH_ACTIVESITE_END

	return false;
}

bool ReadBert_ExpectValue(const MACRO_LANE_SEL& MacroLane_Sel, PRBS_Pattern mPRBS, LANE_DOUBLE& ErrorCount, STRING TestMode, DOUBLE wait_time_ms)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();

	ErrorCount.init(999);
//	TransactionPort pRX("pHilink16_RX");
//	if (TestMode == "ATE" && CP_FT_Program == "FT")
//	{
//		fr.registerTransactionPort(pRX);
//	}

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ReadBert_ExpectValue",Global_D2S_Mode);

		DS.rxRegs.skip_CSR_Check();

//		if (TestMode == "ATE" && CP_FT_Program == "FT") {
//			pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//		}

		jtag.wait(20*0.000001);

		selectMacro_MB(MacroLane_Sel);
		DS.Broadcast();

		EnableRxPrbsCheck(mPRBS);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				DS.rxRegs.ExpectValue(18, 0, 0xffff);
			}
		}

		jtag.wait(wait_time_ms*0.001);

		jtag.enablePassFailCheckForNextExecution();

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				DS.rxRegs.ExpectValue(18, 0, 0x0000);
			}
		}

	d2s::d2s_LABEL_END();



//	if ((jtag.hasAllSitesPassed("H16LRTV100_MPB_ReadBert_ExpectValue")) && (Global_D2S_Mode == LearningMode))
	if ((hasAllSitesPassed()) && (Global_D2S_Mode == LearningMode))
	{
		hout(DETAIL) << "+++++++++++++++++jtag.hasPassed(label)+++++++++++++++" << endl;

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					ErrorCount[SiteID][MacroID][LaneID] = 0;
				}
			}
		FOREACH_ACTIVESITE_END

//		return jtag.hasAllSitesPassed("H16LRTV100_MPB_ReadBert_ExpectValue");
		return hasAllSitesPassed();
	}
	else
	{
		hout(DETAIL) << "+++++++++++++++++jtag.hasFailed(label)+++++++++++++++" << endl;
		ReadBert(MacroLane_Sel, mPRBS, ErrorCount, TestMode, wait_time_ms);
		return false;
	}
}

bool AntiFool(const MACRO_LANE_SEL& MacroLane_Sel, PRBS_Pattern mPRBS, LANE_DOUBLE& ErrorCount, STRING TestMode, DOUBLE wait_time_ms)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();

	INT Errors = 0;
	ErrorCount.init(999);

//	TransactionPort pRX("pHilink16_RX");
//	if (TestMode == "ATE" && CP_FT_Program == "FT")
//	{
//		fr.registerTransactionPort(pRX);
//	}

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_AntiFool",Global_D2S_Mode);

		DS.rxRegs.skip_CSR_Check();

//		if (TestMode == "ATE" && CP_FT_Program == "FT")
//		{
//			pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//		}

		selectMacro_MB(MacroLane_Sel);
		DS.Broadcast();

		EnableRxPrbsCheck(mPRBS);

//		/*revert prbschkmode to free running mode for bert verify's stability*/
		jtag.wait(100*0.000001);
		DS.rxRegs.setprbschkmode(1).Write2DUT(14);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				DS.rxRegs.ExpectValue(18, 0, 0xffff);
			}
		}

		jtag.wait(wait_time_ms*0.001);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				ostringstream id18;
				id18 << "M" << MacroID << "_L" << LaneID << "_CSR18_" << jtag.Context;
				DS.rxRegs.Read2IDString(18, id18.str());
			}
		}

	d2s::d2s_LABEL_END();

	INT	csrindex = 18;
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				Errors = 0;
				ostringstream id18;
				id18 << "M" << MacroID << "_L" << LaneID << "_CSR18_" << jtag.Context;
				INT result = jtag.getReadValue(id18.str())[SiteID];

				DS.rxRegs.csr[csrindex] = (uint)(result);

				if (hout.IsRegAccessEn()) {
					hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  Lane[" << LaneID << "]" << "\tRead ================" << endl;
					DS.rxRegs.DisplayAllSegmentOfCSR(csrindex);
				}

				LONG aux = 0;

				INT errflag = DS.rxRegs.getprbserr();

				aux = DS.rxRegs.getprbscnt();
				aux <<= DS.rxRegs.getprbscntexp();

				Errors += aux;
				ErrorCount[SiteID][MacroID][LaneID] = Errors;

				if (ErrorCount[SiteID][MacroID][LaneID] == 0) {
					hout(DETAIL) << "M" << dec << MacroID << "_L" << LaneID << ": " << "\t" << "No error count" << endl;
					if (errflag == 1){hout(DETAIL) << "!!!prbserr(= 1) is not accordance with prbscnt&prbscntexp!!!\n";}
				} else {
					hout(DETAIL) << "M" << dec << MacroID << "_L" << LaneID << ": " << "\t" << "measured error count = " << ErrorCount[SiteID][MacroID][LaneID] << endl;
					if (errflag == 0){hout(DETAIL) << "!!!prbserr(= 0) is not accordance with prbscnt&prbscntexp!!!\n";}
				}
			}
		}
	FOREACH_ACTIVESITE_END

	return false;
}

bool AntiFool_ExpectValue(const MACRO_LANE_SEL& MacroLane_Sel, PRBS_Pattern mPRBS, LANE_DOUBLE& ErrorCount, STRING TestMode, DOUBLE wait_time_ms)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();

	ErrorCount.init(999);

//	TransactionPort pRX("pHilink16_RX");
//	if (TestMode == "ATE" && CP_FT_Program == "FT")
//	{
//		fr.registerTransactionPort(pRX);
//	}

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_AntiFool_ExpectValue",Global_D2S_Mode);

		DS.rxRegs.skip_CSR_Check();

//		if (TestMode == "ATE" && CP_FT_Program == "FT")
//		{
//			pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//		}

		selectMacro_MB(MacroLane_Sel);
		DS.Broadcast();

		EnableRxPrbsCheck(mPRBS);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				DS.rxRegs.ExpectValue(18, 0, 0xffff);
			}
		}

		jtag.wait(wait_time_ms*0.001);

		jtag.enablePassFailCheckForNextExecution();

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			selectMacro(MacroID);

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				DS.rxRegs.MacroID(MacroID).SliceID(LaneID).Broadcast(0);
				DS.rxRegs.ExpectValue(18, 1<<15, 0x7fff);
			}
		}

	d2s::d2s_LABEL_END();

//	if ((jtag.hasAllSitesPassed("H16LRTV100_MPB_AntiFool_ExpectValue")) && (Global_D2S_Mode == LearningMode))
	if ((hasAllSitesPassed()) && (Global_D2S_Mode == LearningMode))
	{
		hout(DETAIL) << "+++++++++++++++++jtag.hasPassed(label)+++++++++++++++" << endl;
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					ErrorCount[SiteID][MacroID][LaneID] = 999;				}
			}
		FOREACH_ACTIVESITE_END
//		return jtag.hasAllSitesPassed("H16LRTV100_MPB_AntiFool_ExpectValue");
		return hasAllSitesPassed();
	}
	else
	{
		hout(DETAIL) << "+++++++++++++++++jtag.hasFailed(label)+++++++++++++++" << endl;
		AntiFool(MacroLane_Sel, mPRBS, ErrorCount, TestMode, wait_time_ms);
		return false;
	}
}


/*Top function of getting four eye point
 *return value: true for getting eye point successfully, false for getting eye point failed
 *rate_mode: full rate/half rate
 *downPoint: down height
 *downPoint: upPonit: up height
 *downPoint: leftPonit: left widtht
 *downPoint: rightPoint: right width
 *downPoint: averageTimes: Times of eye diagram data averaging, recommended to set to 3 for inner eye, 1 for outer eye
 */

bool GetFourPointEyeDiagram(const MACRO_LANE_SEL& MacroLane_Sel, const DOUBLE &dDataRate, LANE_EYEDATA &eyeData, bool eyeheight_enable, STRING TestMode, INT averageTimes)
{
	bool 					SSC_CDR = false;
	EYEDATA					tmpeyeData;
	tmpeyeData.eyeWidth = 0;
	tmpeyeData.eyeHeight = 0;
	tmpeyeData.leftValue = 0;
	tmpeyeData.rightValue = 0;
	tmpeyeData.bottomValue = 0;
	tmpeyeData.upValue = 0;

	eyeData.init(tmpeyeData);

	INT iRateMode = DS.txRegs.gettxratemode();

	INT 					uiSize;
	INT						iMonitorDelay;
	switch (iRateMode)
	{
		case 0: uiSize = 64;iMonitorDelay = (INT) ((dDataRate / 16) * 13);			break;
		case 1: uiSize = 128;iMonitorDelay = (INT) ((dDataRate * 2 / 16) * 13);  	break;
		case 2: uiSize = 256;iMonitorDelay = (INT) ((dDataRate * 4 / 16) * 13); 	break;
		case 3: uiSize = 512;iMonitorDelay = (INT) ((dDataRate * 8 / 16) * 13); 	break;
		default: uiSize = 64;iMonitorDelay = (INT) ((dDataRate / 16) * 13);			break;
	}


	d2s_JTAG& jtag = d2s_JTAG::Instance();

//	TransactionPort pRX("pHilink16_RX");
//	if (TestMode == "ATE" && CP_FT_Program == "FT") {
//		fr.registerTransactionPort(pRX);
//	}

	//********************************************************* Start to scan eye height ************************************************************
	//********************************************************* Start to scan eye height ************************************************************

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEHEIGHT_CHECK_part1",Global_D2S_Mode);

//		if (TestMode == "ATE" && CP_FT_Program == "FT")
//		{
//			pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//		}

		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);

		/*'Disable Rx PRBS checker', confirmed with GAOYIDIAN by T*/
		DS.rxRegs.setprbschken(0x0)
				 .Write2DUT(14);
		/*Enable coarse align*/
		DS.rxRegs.setmcoarsealignen(0x1)
				 .Write2DUT(45);
		/*disable remote EyeMetric*/
		DS.rxRegs.setremotetx(0x0)
				 .Write2DUT(61);

	d2s::d2s_LABEL_END();

	if(SSC_CDR)/*clear eye monitor status*/
	{
		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEHEIGHT_CHECK_part2",Global_D2S_Mode);

//			if (TestMode == "ATE" && CP_FT_Program == "FT")
//			{
//				pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//			}

			selectMacro_MB(MacroLane_Sel);

			DS.rxRegs.SliceID(0).Broadcast(1);
			DS.rxRegs.setmphsofst(0x0)
					 .setmvolofst(0x0)
					 .Write2DUT(16);
			DS.rxRegs.seteyemonpwrdb(1)
					 .Write2DUT(15);

		d2s::d2s_LABEL_END();

		/*Wait eye monitor coarse align done*/
		SITE_PASSFAIL_RESULT		CoarseAlignDone;
		WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.emready(), 1, 100, 0.1, CoarseAlignDone);
		if (CoarseAlignDone.isAllSiteFailed()){
			return false;	/*All Site Wait Done failed*/
		}


		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEHEIGHT_CHECK_part3",Global_D2S_Mode);

//			if (TestMode == "ATE" && CP_FT_Program == "FT")
//			{
//				pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//			}

			selectMacro_MB(MacroLane_Sel);

			DS.rxRegs.SliceID(0).Broadcast(1);
			DS.rxRegs.seteyemonpwrdb(0x0)
					 .Write2DUT(15);

		d2s::d2s_LABEL_END();
	}

	if(eyeheight_enable)
	{

		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEHEIGHT_CHECK_part4",Global_D2S_Mode);

//			if (TestMode == "ATE" && CP_FT_Program == "FT")
//			{
//				pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//			}

			selectMacro_MB(MacroLane_Sel);

			DS.rxRegs.SliceID(0).Broadcast(1);
			/*Set vertical inner eye scan mode*/
			DS.rxRegs.seteyescanmode(0x1)
					 .Write2DUT(15);
			/*Set scan window*/
			DS.rxRegs.seteyescanwin(15)
					 .Write2DUT(15);
			/*Power up eye monitor*/
			DS.rxRegs.seteyemonpwrdb(0x1)
					 .Write2DUT(15);

		d2s::d2s_LABEL_END();

		for (INT i = 0; i < averageTimes; i++)
		{
			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEHEIGHT_CHECK_CoarseAlign",Global_D2S_Mode);

//				if (TestMode == "ATE" && CP_FT_Program == "FT")
//				{
//					pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//				}

				selectMacro_MB(MacroLane_Sel);

				DS.rxRegs.SliceID(0).Broadcast(1);
				/*Clear eye monitor state*/
				DS.rxRegs.seteyescanstart(0x0)
						 .Write2DUT(15);
				DS.rxRegs.setmphsofst(0x0)
						 .setmvolofst(0x0)
						 .Write2DUT(16);

			d2s::d2s_LABEL_END();

			/*Wait eye monitor coarse align done*/
			SITE_PASSFAIL_RESULT		CoarseAlignDone;
			WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.emready(), 1, 100, 0.1, CoarseAlignDone);
			if (true == CoarseAlignDone.isAllSiteFailed()){
				return false;	/*All Site Wait Done failed*/
			}


			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEHEIGHT_CHECK_DisableCoarseAlign",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);

				DS.rxRegs.SliceID(0).Broadcast(1);

				/*Disable coarse align*/
				DS.rxRegs.setmcoarsealignen(0x0)
						 .Write2DUT(45);
				/*Set the center phase value*/
				DS.rxRegs.setmphsofst(iMonitorDelay)
						 .Write2DUT(16);
			d2s::d2s_LABEL_END();

			/*Wait eye monitor ready*/
			WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.emready(), 1, 100, 0.1, CoarseAlignDone);
			if (true == CoarseAlignDone.isAllSiteFailed()){
				return false;	/*All Site Wait Done failed*/
			}


			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEHEIGHT_CHECK_StartEyeScan",Global_D2S_Mode);

				selectMacro_MB(MacroLane_Sel);

				DS.rxRegs.SliceID(0).Broadcast(1);

				/*start eye scan*/
				DS.rxRegs.seteyescanstart(1)
						 .Write2DUT(15);

			d2s::d2s_LABEL_END();


			/*Wait until scan complete*/
			SITE_PASSFAIL_RESULT		EyeScanIsDone;
			WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.eyescanstart(), 0, 10000, 0.1, EyeScanIsDone);
			if (true == EyeScanIsDone.isAllSiteFailed()){
				return false;	/*All Site Wait Done failed*/
			}

			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEHEIGHT_CHECK_RESULT", Global_D2S_Mode);

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					selectMacro(MacroID);

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						DS.rxRegs.SliceID(LaneID).Broadcast(0);
						ostringstream id19;
						id19 << "M" << MacroID << "_L" << LaneID << "_CSR19_EYEHEIGHT" << jtag.Context;
						DS.rxRegs.Read2IDString(19, id19.str());
					}
				}

			d2s::d2s_LABEL_END();

			/*Log scan data*/
			UINT csrindex = 19;
			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						ostringstream id19;
						id19 << "M" << MacroID << "_L" << LaneID << "_CSR19_EYEHEIGHT" << jtag.Context;
						INT result = jtag.getReadValue(id19.str())[SiteID];

						DS.rxRegs.csr[csrindex] = (uint)(result);

						if (hout.IsRegAccessEn()) {
							hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  Lane[" << LaneID << "]" << "\tRead ================" << endl;
							DS.rxRegs.DisplayAllSegmentOfCSR(csrindex);
						}

						INT bottomValue = DS.rxRegs.geteyecor0();
						if(bottomValue > 128) bottomValue -=256;
						eyeData[SiteID][MacroID][LaneID].bottomValue += bottomValue;

						INT upValue = DS.rxRegs.geteyecor1();
						if(upValue > 128) upValue -=256;
						eyeData[SiteID][MacroID][LaneID].upValue += upValue;
					}
				}
			FOREACH_ACTIVESITE_END
		}
		/* Get the up and down point location
		 * 3.9 is the ratio between the actual voltage value and the register value.*/
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					eyeData[SiteID][MacroID][LaneID].bottomValue = (INT)eyeData[SiteID][MacroID][LaneID].bottomValue / averageTimes;
					eyeData[SiteID][MacroID][LaneID].upValue	   = (INT)eyeData[SiteID][MacroID][LaneID].upValue / averageTimes;

					hout(DETAIL) << "Macro = " << dec << MacroID <<", laneIndex = " << dec << LaneID
								 << "\tBottom = " << eyeData[SiteID][MacroID][LaneID].bottomValue << "\t Up = " << eyeData[SiteID][MacroID][LaneID].upValue << "\n";
				}
			}
		FOREACH_ACTIVESITE_END
	}
	//********************************************************* Start to scan eye width ************************************************************
	//********************************************************* Start to scan eye width ************************************************************

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEWIDTH_CHECK",Global_D2S_Mode);

//		if (TestMode == "ATE" && CP_FT_Program == "FT")
//		{
//			pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//		}

		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		/*Enable coarse align*/
		DS.rxRegs.setmcoarsealignen(0x1)
				 .Write2DUT(45);

		/*Set horizontal inner eye scan mode*/
		DS.rxRegs.seteyescanmode(0x0)/*Inner eye scan mode (horizontal)*/
				 .Write2DUT(15);
		/*Set scan window*/
		DS.rxRegs.seteyescanwin(15)
				 .Write2DUT(15);
		/*Power up eye monitor*/
		DS.rxRegs.seteyemonpwrdb(0x1)
				 .Write2DUT(15);

	d2s::d2s_LABEL_END();

	for (INT i = 0; i < averageTimes; i++)
	{
		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEWIDTH_CHECK_CoarseAlign",Global_D2S_Mode);

//			if (TestMode == "ATE" && CP_FT_Program == "FT")
//			{
//				pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//			}

			selectMacro_MB(MacroLane_Sel);

			DS.rxRegs.SliceID(0).Broadcast(1);
			/*Clear eye monitor state*/
			DS.rxRegs.seteyescanstart(0x0)
					 .Write2DUT(15);
			DS.rxRegs.setmphsofst(iMonitorDelay)
					 .setmvolofst(0x0)
					 .Write2DUT(16);

		d2s::d2s_LABEL_END();

		/*Wait eye monitor coarse align done*/
		SITE_PASSFAIL_RESULT		CoarseAlignDone;
		WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.emready(), 1, 100, 0.1, CoarseAlignDone);
		if (true == CoarseAlignDone.isAllSiteFailed()){
			return false;	/*All Site Wait Done failed*/
		}

		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEWIDTH_CHECK_StartEyeScan",Global_D2S_Mode);

			selectMacro_MB(MacroLane_Sel);

			DS.rxRegs.SliceID(0).Broadcast(1);

			/*start eye scan*/
			DS.rxRegs.seteyescanstart(1)
					 .Write2DUT(15);

		d2s::d2s_LABEL_END();

		/*Wait until scan complete*/
		SITE_PASSFAIL_RESULT		EyeScanIsDone;
		WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.eyescanstart(), 0, 10000, 0.1, EyeScanIsDone);
		if (true == EyeScanIsDone.isAllSiteFailed()){
			return false;	/*All Site Wait Done failed*/
		}


		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYEWIDTH_CHECK_RESULT", Global_D2S_Mode);

			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				selectMacro(MacroID);

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					DS.rxRegs.SliceID(LaneID).Broadcast(0);
					ostringstream id19;
					id19 << "M" << MacroID << "_L" << LaneID << "_CSR19_EYEWIDTH" << jtag.Context;
					DS.rxRegs.Read2IDString(19, id19.str());
				}
			}

		d2s::d2s_LABEL_END();

		/*Log scan data*/
		INT csrindex = 19;
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					ostringstream id19;
					id19 << "M" << MacroID << "_L" << LaneID << "_CSR19_EYEWIDTH" << jtag.Context;
					INT result = jtag.getReadValue(id19.str())[SiteID];

					DS.rxRegs.csr[csrindex] = (uint)(result);

					if (hout.IsRegAccessEn()) {
						hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  Lane[" << LaneID << "]" << "\tRead ================" << endl;
						DS.rxRegs.DisplayAllSegmentOfCSR(csrindex);
					}

					INT leftValue = DS.rxRegs.geteyecor0();
					if (leftValue > 128) leftValue -= 256;
					eyeData[SiteID][MacroID][LaneID].leftValue += leftValue;

					INT rightValue = DS.rxRegs.geteyecor1();
					if (rightValue > 128) rightValue -= 256;
					eyeData[SiteID][MacroID][LaneID].rightValue += rightValue;
				}
			}
		FOREACH_ACTIVESITE_END
	}
	/*Get the left and right point location*/
	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				eyeData[SiteID][MacroID][LaneID].leftValue  = (iRateMode == 3) ? (4 * eyeData[SiteID][MacroID][LaneID].leftValue / averageTimes)
														 :  (iRateMode == 2) ? (2 * eyeData[SiteID][MacroID][LaneID].leftValue / averageTimes)
														 : 						    eyeData[SiteID][MacroID][LaneID].leftValue / averageTimes;
				eyeData[SiteID][MacroID][LaneID].rightValue = (iRateMode == 3) ? (4 * eyeData[SiteID][MacroID][LaneID].rightValue / averageTimes)
														 :  (iRateMode == 2) ? (2 * eyeData[SiteID][MacroID][LaneID].rightValue / averageTimes)
														 : 						    eyeData[SiteID][MacroID][LaneID].rightValue / averageTimes;

				hout(DETAIL) << "Macro = " << dec << MacroID <<", laneIndex = " << dec << LaneID
							 << "\tLeft = " << eyeData[SiteID][MacroID][LaneID].leftValue << "\tRight = " << eyeData[SiteID][MacroID][LaneID].rightValue << endl;
			}
		}
	FOREACH_ACTIVESITE_END

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_After_PRBS_EYE",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);
		/*Power down eye monitor and clear eye monitor status*/
		DS.rxRegs.setmphsofst(0x0)
				 .Write2DUT(16);
		DS.rxRegs.setmvolofst(0x0)
				 .Write2DUT(16);

	d2s::d2s_LABEL_END();

	/*Wait eye monitor coarse align done*/
	SITE_PASSFAIL_RESULT		CoarseAlignDone;
	WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.emready(), 1, 100, 0.1, CoarseAlignDone);
	if (true == CoarseAlignDone.isAllSiteFailed()){
		return false;	/*All Site Wait Done failed*/
	}


	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_After_PRBS_EYE_Final",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		DS.rxRegs.SliceID(0).Broadcast(1);

		DS.rxRegs.seteyemonpwrdb(0x0)
				 .Write2DUT(15);

	d2s::d2s_LABEL_END();

	/************Calc EyeWidth and EyeHeight and printToLog**************/

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
		{
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
			{
				UINT LaneID = vLane[laneIndex];
				eyeData[SiteID][MacroID][LaneID].eyeWidth = (DOUBLE)(eyeData[SiteID][MacroID][LaneID].rightValue - eyeData[SiteID][MacroID][LaneID].leftValue) / (DOUBLE)uiSize;
				eyeData[SiteID][MacroID][LaneID].eyeHeight = eyeData[SiteID][MacroID][LaneID].upValue - eyeData[SiteID][MacroID][LaneID].bottomValue;
				hout(GENERAL) << "MacroID = " << MacroID << "\tLaneID = " << LaneID
							  << "\tEye Width = " << eyeData[SiteID][MacroID][LaneID].eyeWidth << "\tEye Height = " << eyeData[SiteID][MacroID][LaneID].eyeHeight << endl;
			}
		}
	FOREACH_ACTIVESITE_END

	return true;
}



/*Top function of getting eye diagram. Users must have reset MCU before by MCU reset or //adaptation reset API.
 * Return value: true for getting eye diagram successfully, false for getting eye diagram failed
 * showInner: true for plot inner eye, false for plot outer eye
 * scanWin: scan window for eye diagram
 * averageTimes: Times of eye diagram data averaging, recommended to set to 3 for inner eye, 1 for outer eye
 */
bool GetEyeDiagram(const MACRO_LANE_SEL& MacroLane_Sel, DOUBLE& dDataRate, STRING TestMode, bool showInner, INT scanWin, INT averageTimes)
{
	bool 					SSC_CDR = false;
	LANE_EYEDIAGRAM			eyeDiagram;

	/*Get UI size and eye monitor delay based on data rate*/
	INT 					iRateMode = DS.txRegs.gettxratemode();
	INT 					uiSize;
	INT						iMonitorDelay;
	switch (iRateMode)
	{

		case 0: uiSize = 64;iMonitorDelay = (INT) ((dDataRate / 16) * 13);			break;
		case 1: uiSize = 128;iMonitorDelay = (INT) ((dDataRate * 2 / 16) * 13);  	break;
		case 2: uiSize = 256;iMonitorDelay = (INT) ((dDataRate * 4 / 16) * 13); 	break;
		case 3: uiSize = 512;iMonitorDelay = (INT) ((dDataRate * 8 / 16) * 13); 	break;
		default: uiSize = 64;iMonitorDelay = (INT) ((dDataRate / 16) * 13);			break;
	}

	/***************Init Diagram*****************/
	vector<EYEDATA>		vtmpeyeData;
	for (INT i = 0; i < uiSize; i ++)
	{
		EYEDATA			tmpeye_perUI;
		tmpeye_perUI.eyeWidth = 0.0;
		tmpeye_perUI.eyeHeight = 0.0;
		tmpeye_perUI.leftValue = 0;
		tmpeye_perUI.rightValue = 0;
		tmpeye_perUI.bottomValue = 0;
		tmpeye_perUI.upValue = 0;
		vtmpeyeData.push_back(tmpeye_perUI);
	}
	eyeDiagram.init(vtmpeyeData);

	d2s_JTAG& jtag = d2s_JTAG::Instance();

//	TransactionPort pRX("pHilink16_RX");
//	if (TestMode == "ATE" && CP_FT_Program == "FT")
//	{
//		fr.registerTransactionPort(pRX);
//	}

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EyeDiagram_PRESET",Global_D2S_Mode);

//		if (TestMode == "ATE" && CP_FT_Program == "FT")
//		{
//			pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//		}

		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.rxRegs.setprbschken(0).Write2DUT(14);  //**disable Rx PRBS checker , follow T program     zhangkai**/
		/*Enable coarse align*/
		DS.rxRegs.setmcoarsealignen(0x1)
				 .Write2DUT(45);
		/*disable remote EyeMetric*/
		DS.rxRegs.setremotetx(0x0)
				 .Write2DUT(61);

	d2s::d2s_LABEL_END();

	if(SSC_CDR)/*clear eye monitor status*/
	{
		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EyeDiagram_PRESET_part2",Global_D2S_Mode);

//			if (TestMode == "ATE" && CP_FT_Program == "FT")
//			{
//				pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//			}

			selectMacro_MB(MacroLane_Sel);

			DS.rxRegs.SliceID(0).Broadcast(1);
			DS.rxRegs.setmphsofst(0x0)
					 .setmvolofst(0x0)
					 .Write2DUT(16);
			DS.rxRegs.seteyemonpwrdb(1)
					 .Write2DUT(15);


		d2s::d2s_LABEL_END();
		/*Wait eye monitor coarse align done*/
		SITE_PASSFAIL_RESULT		CoarseAlignDone;
		WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.emready(), 1, 100, 0.1, CoarseAlignDone);
		if (true == CoarseAlignDone.isAllSiteFailed()){
			return false;	/*All Site Wait Done failed*/
		}


		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EyeDiagram_PRESET_part3",Global_D2S_Mode);

//			if (TestMode == "ATE" && CP_FT_Program == "FT")
//			{
//				pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//			}

			selectMacro_MB(MacroLane_Sel);

			DS.rxRegs.SliceID(0).Broadcast(1);
			DS.rxRegs.seteyemonpwrdb(0x0)
					 .Write2DUT(15);

		d2s::d2s_LABEL_END();
	}

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EyeDiagram_PRESET_part4",Global_D2S_Mode);

//		if (TestMode == "ATE" && CP_FT_Program == "FT") {
//			pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//		}

		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		/*Set inner / outer eye scan mode*/
		if (showInner == true) {
			DS.rxRegs.seteyescanmode(1)/*Inner eye scan mode (vertical)*/
					 .Write2DUT(15);
		} else {
			DS.rxRegs.seteyescanmode(3)/*Outer eye scan mode (vertical)*/
					 .Write2DUT(15);
		}

		/*Set scan window*/
		DS.rxRegs.seteyescanwin(scanWin)    /***********= 15 in T program zhangkai*********/
				 .Write2DUT(15);

		/*Power up eye monitor*/
		DS.rxRegs.seteyemonpwrdb(1)
				 .Write2DUT(15);

	d2s::d2s_LABEL_END();

	/*Loop all phase to get eye*/
	for (INT phase = - uiSize / 2 + iMonitorDelay; phase < uiSize/2 + iMonitorDelay; phase ++)
	{
		INT phaseIndex = phase +  uiSize / 2 - iMonitorDelay;
		/*Initialization*/
		hout (DETAIL) << "+++++++++++++++ Phase = " << phase << " +++++++++++++++" << endl;
		for (INT i = 0; i < averageTimes; i ++)
		{
			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_EYEDIAGRAM_SETUP",Global_D2S_Mode);

//				if (TestMode == "ATE" && CP_FT_Program == "FT") {
//					pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//				}

				/*Clear eye monitor state*/

				selectMacro_MB(MacroLane_Sel);

				DS.rxRegs.SliceID(0).Broadcast(1);
				/*Clear eye monitor state*/
				DS.rxRegs.seteyescanstart(0x0)
						 .Write2DUT(15);
				DS.rxRegs.setmphsofst(0x0)
						 .setmvolofst(0x0)
						 .Write2DUT(16);


			d2s::d2s_LABEL_END();

			/*Wait eye monitor coarse align done*/
			SITE_PASSFAIL_RESULT		CoarseAlignDone;
			WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.emready(), 1, 100, 0.1, CoarseAlignDone);
			if (true == CoarseAlignDone.isAllSiteFailed()){
				return false;	/*All Site Wait Done failed*/
			}


			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_EYEDIAGRAM_SETUP_part2",Global_D2S_Mode);

//				if (TestMode == "ATE" && CP_FT_Program == "FT")
//				{
//					pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//				}

				selectMacro_MB(MacroLane_Sel);

				DS.rxRegs.SliceID(0).Broadcast(1);
//				jtag.wait(100*0.000001);/* coarse align*/
				/*Disable coarse align*/
				DS.rxRegs.setmcoarsealignen(0x0)
						 .Write2DUT(45);
				/*Set monitor phase value*/
				DS.rxRegs.setmphsofst((phase < 0) ? phase + 256 : phase)     /******in T program setmphsofst = monitordelay    zhangkai****/
						 .Write2DUT(16);


			d2s::d2s_LABEL_END();

			/*Wait eye monitor coarse align done*/
			WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.emready(), 1, 100, 0.1, CoarseAlignDone);
			if (true == CoarseAlignDone.isAllSiteFailed()){
				return false;	/*All Site Wait Done failed*/
			}


			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_EYEDIAGRAM_SETUP_part3",Global_D2S_Mode);

//				if (TestMode == "ATE" && CP_FT_Program == "FT")
//				{
//					pRX.execLabel(ATE_MODE_RX_FASTDIFF_PATTERN_LABEL,ATE_MODE_RX_FASTDIFF_PATTERN_CYCLE);
//				}

				selectMacro_MB(MacroLane_Sel);

				DS.rxRegs.SliceID(0).Broadcast(1);
				/*start eye scan*/
				DS.rxRegs.seteyescanstart(1)
						 .Write2DUT(15);

			d2s::d2s_LABEL_END();

			/*Wait until scan complete*/
			SITE_PASSFAIL_RESULT		EyeScanIsDone;
			WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.eyescanstart(), 0, 10000, 0.1, EyeScanIsDone);
			if (true == EyeScanIsDone.isAllSiteFailed()){
				return false;	/*All Site Wait Done failed*/
			}


			d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_EYEDIAGRAM_GETRESULT", Global_D2S_Mode);

				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					selectMacro(MacroID);

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						DS.rxRegs.SliceID(LaneID).Broadcast(0);
						ostringstream id19;
						id19 << "M" << MacroID << "_L" << LaneID << "_CSR19_EYEDIAGRAM" << jtag.Context;
						DS.rxRegs.Read2IDString(19, id19.str());
					}
				}

			d2s::d2s_LABEL_END();

			/*Log scan data*/
			INT csrindex = 19;

			FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
				{
					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
					const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

					for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
					{
						UINT LaneID = vLane[laneIndex];
						ostringstream id19;
						id19 << "M" << MacroID << "_L" << LaneID << "_CSR19_EYEDIAGRAM" << jtag.Context;

						INT result = jtag.getReadValue(id19.str())[SiteID];

						DS.rxRegs.csr[csrindex] = (uint)(result);

						if (hout.IsRegAccessEn()) {
							hout(REG_ACCESS) << "================ Macro[" << dec << MacroID << "]"<< "  Lane[" << LaneID << "]" << "\tRead ================" << endl;
							DS.rxRegs.DisplayAllSegmentOfCSR(csrindex);
						}

						INT bottomValue = DS.rxRegs.geteyecor0();
						if(bottomValue > 128) bottomValue -= 256;
						eyeDiagram[SiteID][MacroID][LaneID][phaseIndex].bottomValue += bottomValue;

						INT upValue = DS.rxRegs.geteyecor1();
						if(upValue > 128) upValue -= 256;
						eyeDiagram[SiteID][MacroID][LaneID][phaseIndex].upValue += upValue;
					}
				}
			FOREACH_ACTIVESITE_END
		}

		/*Store to eye diagram data array.*/
		/*3.9 is the ratio between the actual voltage value and the register value.*/
		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
			{
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
				{
					UINT LaneID = vLane[laneIndex];
					eyeDiagram[SiteID][MacroID][LaneID][phaseIndex].bottomValue /= averageTimes;
					eyeDiagram[SiteID][MacroID][LaneID][phaseIndex].upValue /= averageTimes;
				}
			}
		FOREACH_ACTIVESITE_END
	}

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EyeDiagram_AFTER_part1",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		/*Enable coarse align*/
		DS.rxRegs.setmcoarsealignen(0x1)
				 .Write2DUT(45);

		/*Power down eye monitor and clear eye monitor status*/
		DS.rxRegs.setmphsofst(0x0)
				 .setmvolofst(0x0)
				 .Write2DUT(16);


	d2s::d2s_LABEL_END();

	/*Wait eye monitor coarse align done*/
	SITE_PASSFAIL_RESULT		CoarseAlignDone;
	WaitDone(MacroLane_Sel, DS.rxRegs.REG_INFO.emready(), 1, 100, 0.1, CoarseAlignDone);
	if (true == CoarseAlignDone.isAllSiteFailed()){
		return false;	/*All Site Wait Done failed*/
	}


	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_EyeDiagram_AFTER_part2",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);

		DS.rxRegs.SliceID(0).Broadcast(1);
		DS.rxRegs.seteyemonpwrdb(0x0)
				 .Write2DUT(15);

	d2s::d2s_LABEL_END();

	/*Now the eye diagram data are stored to eyeData array and ready for output*/
	PlotEyeDiagram(MacroLane_Sel, eyeDiagram, uiSize, iMonitorDelay);

	return true;
}


bool EyeScanStartCheck(const MACRO_LANE_SEL& MacroLane_Sel)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EYESCANSTART_CHECK", Global_D2S_Mode);

	jtag.enablePassFailCheckForNextExecution();

	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

		selectMacro(MacroID);

		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
		{
			UINT LaneID = vLane[laneIndex];
			DS.rxRegs.SliceID(LaneID).Broadcast(0);
			DS.rxRegs.ExpectValue(15, 0, 0xfbff);
		}
	}
	d2s::d2s_LABEL_END();

//	return jtag.hasPassed(label);//todo S08V200 api
}


bool EyeMonitorReadyCheck(const MACRO_LANE_SEL& MacroLane_Sel)
{
	d2s_JTAG& jtag = d2s_JTAG::Instance();
	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_PRBS_EMREADY_CHECK", Global_D2S_Mode);

	jtag.enablePassFailCheckForNextExecution();

	for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
	{
		UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
		const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

		selectMacro(MacroID);

		for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++)
		{
			UINT LaneID = vLane[laneIndex];
			DS.rxRegs.SliceID(LaneID).Broadcast(0);
			DS.rxRegs.ExpectValue(15, 1<<11, 0xf7ff);
		}
	}
	d2s::d2s_LABEL_END();

//	return jtag.hasPassed(label);
}

/*Function of set Tx FIR taps
 *Return value indicate whether set operation succeed
 *To keep Tx output impedance, it?s recommended to set the sum of abs value of TXFIRPRE2, TXFIRPRE1, TXFIRMAIN, TXFIRPOST1 and TXFIRPOST2 not more than 64
 */
void Tx_tapmap_Trigger()
{
	DS.txRegs.settxdrvswctrl(0)
		     .Write2DUT(12);
	DS.txRegs.settxdrvswctrl(1)
			 .Write2DUT(12);
}

bool SetTxFir(TxFIR_SETTING FIR, bool PCIE_SATA_SAS_MODE)
{
	/**************** sum of FIR value should not > 63 ***************/
	if ((abs(FIR.iTxPre2nd) + abs(FIR.iTxPre1st) + abs(FIR.iTxMain)
	  + abs(FIR.iTxPost1st) + abs(FIR.iTxPost2nd)) > 63) {
		hout(RELEASE) << "Error: Sum of Five Taps abs value should not > 63, please enter again!!!!!!" << endl;
		_exit(0);
	}
	DS.txRegs.settxdrvbypass(0x1).Write2DUT(10);
	DS.txRegs.settxdrv_map_sel(0x1).Write2DUT(34);
	DS.txRegs.settxdrvf1sel(0x0)
			 .settxdrvf2sel(0x0)
			 .Write2DUT(12);
	/*Set Tx termination calibration mode to map only*/
	DS.txRegs.settxtermcalmode(2)
		     .Write2DUT(14);

	/*Set Tx FIR taps*/
	INT iRateMode = CUSTpara.RateMode;
	if (iRateMode == 0)
	{
		/*For full rate: Tx FIR support pre2, pre1, post1 and post1*/
		DS.txRegs.settxfirmain(FIR.iTxMain)
			     .settxfirpost1((FIR.iTxPost1st < 0) ? (0x10 | abs(FIR.iTxPost1st)) : FIR.iTxPost1st)
			     .settxfirpost2((FIR.iTxPost2nd < 0) ? (0x10 | abs(FIR.iTxPost2nd)) : FIR.iTxPost2nd)
			     .Write2DUT(1);
		DS.txRegs.settxfirpre1((FIR.iTxPre1st < 0) ? (0x10 | abs(FIR.iTxPre1st)) : FIR.iTxPre1st)
			     .settxfirpre2((FIR.iTxPre2nd < 0) ? (0x10 | abs(FIR.iTxPre2nd)) : FIR.iTxPre2nd)
			     .Write2DUT(0);
	}
	else if (iRateMode == 1)
	{
		/*For half rate: Tx FIR support only pre2, and post2*/
		DS.txRegs.settxfirmain(FIR.iTxMain)
			     .settxfirpost1(0)
			     .settxfirpost2((FIR.iTxPost2nd < 0) ? (0x10 | abs(FIR.iTxPost2nd)) : FIR.iTxPost2nd)/*Act as post1*/
			     .Write2DUT(1);
		DS.txRegs.settxfirpre1(0)
			     .settxfirpre2((FIR.iTxPre2nd < 0) ? (0x10 | abs(FIR.iTxPre2nd)) : FIR.iTxPre2nd)/*Act as pre1*/
			     .Write2DUT(0);
	}
	else
	{
		/*For quarter/octal rate, Tx FIR is not supported*/
		DS.txRegs.settxfirmain(FIR.iTxMain)
			     .settxfirpost1(0)
			     .settxfirpost2(0)
			     .Write2DUT(1);
		DS.txRegs.settxfirpre1(0)
			     .settxfirpre2(0)
			     .Write2DUT(0);
	}

	/*Power up/down taps depends on tap used*/
	if (FIR.iTxPre2nd != 0 || FIR.iTxPost2nd != 0)
	{
		DS.txRegs.settxtappwrdb(0xff)
			     .Write2DUT(10);
	}
	else
	{
		DS.txRegs.settxtappwrdb(0xf6)
			     .Write2DUT(10);
	}

	/*Start FIR tap mapping*/
	Tx_tapmap_Trigger();
	/*Check whether Tx tap mapping complete*/

	return true;
}


void EnableTxToRxParLpbk()
{
	DS.rxRegs.settxrxparlpbken(1)	/*Enable Tx to Rx parallel loopback*/
		     .Write2DUT(10);
}

void DisableTxToRxParLpbk()
{
	DS.rxRegs.settxrxparlpbken(0)	/*Disable Tx to Rx parallel loopback*/
		     .Write2DUT(10);
}


void EnableTxToRxSerLpbk(const STRING& LoopBackMode)

{
	//// cbb inversed, modified here-- chang 20211026
	if ("Bump" == LoopBackMode) {
		DS.txRegs.settx_tx2rxloopbacksel(0x0)
				 .Write2DUT(25);
	} else if ("PreDriver" == LoopBackMode) {
		DS.txRegs.settx_tx2rxloopbacksel(0x1)
				 .Write2DUT(25);
	} else {
		hout(RELEASE) << "Error: No valid loopbackmode selected!!" <<endl;
		_exit(0);
	}

	DS.rxRegs.setsscdr_sftrst_ctrl(0)
			 .Write2DUT(51);

	DS.rxRegs.settxrxserlpbken(1) /*Enable Tx to Rx serial loopback*/
			 .Write2DUT(0);

}


void DisableTxToRxSerLpbk()
{
	DS.rxRegs.settxrxserlpbken(0)	/*Disable Tx to Rx serial loopback*/
		     .Write2DUT(0);
	DS.txRegs.settx_tx2rxloopbacksel(0x0)
			 .Write2DUT(25);
	DS.rxRegs.setsscdr_sftrst_ctrl(0x1)
			 .Write2DUT(51);
}


void EnableRxToTxParLpbk()
{
	DS.txRegs.settxalignmode(0)	/*Set Tx aligner mode to SelfAlign firstly*/
		     .settxclksel(1)		/*Set Tx clock to select Rx recovered clock*/
		     .settxdatasel(1)		/*Set Tx data to select Rx recovered data*/
		     .Write2DUT(2);
}


void DisableRxToTxParLpbkAndSwitchToMissionMode()
{
	DS.txRegs.settxalignmode(3)	/*Set Tx aligner mode to original value.*///todo
		     .settxclksel(2)		/*Set Tx clock to select clock coming along with the Tx data from the core*/
		     .settxdatasel(2)		/*Set Tx data to select core data*/
		     .Write2DUT(2);
}


void EnableTxPrbsGen(PRBS_Pattern TxPRBSGenPattern, bool PCIE_SATA_SAS_MODE)
{
	/*Set Tx PRBS generation pattern*/
	switch (TxPRBSGenPattern)
	{
		case PRBS7: 		DS.txRegs.setprbsgenpatsel(0).Write2DUT(4);break;
		case PRBS9: 		DS.txRegs.setprbsgenpatsel(1).Write2DUT(4);break;
		case PRBS10:		DS.txRegs.setprbsgenpatsel(2).Write2DUT(4);break;
		case PRBS11:		DS.txRegs.setprbsgenpatsel(3).Write2DUT(4);break;
		case PRBS15:		DS.txRegs.setprbsgenpatsel(4).Write2DUT(4);break;
		case PRBS20:		DS.txRegs.setprbsgenpatsel(5).Write2DUT(4);break;
		case PRBS23:		DS.txRegs.setprbsgenpatsel(6).Write2DUT(4);break;
		case PRBS31:		DS.txRegs.setprbsgenpatsel(7).Write2DUT(4);break;
		case Custom_CLK:	DS.txRegs.setprbsgenpatsel(8).Write2DUT(4);break;
		case Custom_ALL0:	DS.txRegs.setprbsgenpatsel(8).Write2DUT(4);break;
		case Custom_ALL1:	DS.txRegs.setprbsgenpatsel(8).Write2DUT(4);break;
		case Custom_FF00:	DS.txRegs.setprbsgenpatsel(8).Write2DUT(4);break;
		default:			DS.txRegs.setprbsgenpatsel(0).Write2DUT(4);break;
	}
	/*Set custom pattern is chosen, then set 80-bit custom pattern*/
	if (TxPRBSGenPattern == Custom_CLK)			/*set customer pattern as clk pattern*/
	{
		DS.txRegs.settxcuspat1(0xAAAA).Write2DUT(5);
		DS.txRegs.settxcuspat2(0xAAAA).Write2DUT(6);
		DS.txRegs.settxcuspat3(0xAAAA).Write2DUT(7);
		DS.txRegs.settxcuspat4(0xAAAA).Write2DUT(8);
		DS.txRegs.settxcuspat5(0xAAAA).Write2DUT(9);
	}
	else if (TxPRBSGenPattern == Custom_ALL0)
	{
		DS.txRegs.settxcuspat1(0x0000).Write2DUT(5);
		DS.txRegs.settxcuspat2(0x0000).Write2DUT(6);
		DS.txRegs.settxcuspat3(0x0000).Write2DUT(7);
		DS.txRegs.settxcuspat4(0x0000).Write2DUT(8);
		DS.txRegs.settxcuspat5(0x0000).Write2DUT(9);
	}
	else if (TxPRBSGenPattern == Custom_ALL1)
	{
		DS.txRegs.settxcuspat1(0xFFFF).Write2DUT(5);
		DS.txRegs.settxcuspat2(0xFFFF).Write2DUT(6);
		DS.txRegs.settxcuspat3(0xFFFF).Write2DUT(7);
		DS.txRegs.settxcuspat4(0xFFFF).Write2DUT(8);
		DS.txRegs.settxcuspat5(0xFFFF).Write2DUT(9);
	}
	else if (TxPRBSGenPattern == Custom_FF00)
	{
		DS.txRegs.settxcuspat1(0xFF00).Write2DUT(5);
		DS.txRegs.settxcuspat2(0xFF00).Write2DUT(6);
		DS.txRegs.settxcuspat3(0xFF00).Write2DUT(7);
		DS.txRegs.settxcuspat4(0xFF00).Write2DUT(8);
		DS.txRegs.settxcuspat5(0xFF00).Write2DUT(9);
	}


	DS.txRegs.settxdatasel(2)					/*Select Tx data from PRBS generator*/
		     .settxalignmode(3)					/*Set Tx align mode to Freeze mode*/
		     .Write2DUT(2);

	DS.txRegs.setprbsgenen(1)					/*Enable Tx PRBS generator*/
		     .Write2DUT(4);
}


void DisableTxPrbsGenAndSwitchToMissionMode(bool PCIE_SATA_SAS_MODE)
{
	DS.txRegs.setprbsgenen(0)		/*Disable Tx PRBS generator*/
		     .Write2DUT(4);

	DS.txRegs.settxclksel(0)		/*Set Tx clock to select clock coming along with the Tx data from the core in most applications or Rx recover clock in XPON Mode.*//*UserSetting*///todo
		     .settxdatasel(0)		/*Set Tx data to select core data*/
		     .settxalignmode(0)	/*Set Tx align mode*//*UserSetting*///todo
		     .Write2DUT(2);
}


void EnableRxPrbsCheck(PRBS_Pattern RxPRBSCheckPattern)
{
	/*Set Rx PRBS check pattern*/
	switch (RxPRBSCheckPattern)
	{
		case PRBS7: 					DS.rxRegs.setprbschkpatsel(0x0).Write2DUT(14);break;
		case PRBS9: 					DS.rxRegs.setprbschkpatsel(0x1).Write2DUT(14);break;
		case PRBS10:					DS.rxRegs.setprbschkpatsel(0x2).Write2DUT(14);break;
		case PRBS11:					DS.rxRegs.setprbschkpatsel(0x3).Write2DUT(14);break;
		case PRBS15:					DS.rxRegs.setprbschkpatsel(0x4).Write2DUT(14);break;
		case PRBS20:					DS.rxRegs.setprbschkpatsel(0x5).Write2DUT(14);break;
		case PRBS23:					DS.rxRegs.setprbschkpatsel(0x6).Write2DUT(14);break;
		case PRBS31:					DS.rxRegs.setprbschkpatsel(0x7).Write2DUT(14);break;
		case Custom_CLK:				DS.rxRegs.setprbschkpatsel(0x8).Write2DUT(14);break;
		case Custom_00110011:			DS.rxRegs.setprbschkpatsel(0x9).Write2DUT(14);break;
		case Custom_0000111100001111:	DS.rxRegs.setprbschkpatsel(0xa).Write2DUT(14);break;
		default:						DS.rxRegs.setprbschkpatsel(0).Write2DUT(14);break;
		/*Notes: PRBS checker will be disabled when select Custom Pattern*/
	}

	DS.rxRegs.setprbschkmode(0)		/*Set Rx PRBS check mode*//*SYNC mode*/
		     .setprbschken(1)			/*Enable Rx PRBS checker*/
		     .Write2DUT(14);
}


void DisableRxPrbsCheck()
{
	DS.rxRegs.setprbschken(0)			/*Disable Rx PRBS checker*/
		     .Write2DUT(14);
}

void SetRxCTLE(RxCTLE_SETTING CTLE)
{
	DS.rxRegs.setctleactgn1(CTLE.Gain[0])
		     .setctlebst1(CTLE.Boost[0])
		     .setctlecmband1(CTLE.CMBand[0])
		     .setctlermband1(CTLE.RMBand[0])
		     .setctleza1(CTLE.ZA[0])
		     .setctlesqh1(CTLE.SQH[0])
		     .Write2DUT(1);
	DS.rxRegs.setctleactgn2(CTLE.Gain[1])
		     .setctlebst2(CTLE.Boost[1])
		     .setctlecmband2(CTLE.CMBand[1])
		     .setctlermband2(CTLE.RMBand[1])
		     .setctleza2(CTLE.ZA[1])
		     .setctlesqh2(CTLE.SQH[1])
		     .Write2DUT(2);
	DS.rxRegs.setctleactgn3(CTLE.Gain[2])
		     .setctlebst3(CTLE.Boost[2])
		     .setctlecmband3(CTLE.CMBand[2])
		     .setctlermband3(CTLE.RMBand[2])
		     .setctleza3(CTLE.ZA[2])
		     .setctlesqh3(CTLE.SQH[2])
		     .Write2DUT(3);
}


void GetInnerEyeMetricbyFirmwareAPI(const MACRO_LANE_SEL& MacroLane_Sel, LANE_EYEDATA &eyeData)
{
	EYEDATA					tmpeyeData;
	tmpeyeData.eyeWidth = 0;
	tmpeyeData.eyeHeight = 0;
	tmpeyeData.leftValue = 0;
	tmpeyeData.rightValue = 0;
	tmpeyeData.bottomValue = 0;
	tmpeyeData.upValue = 0;

	eyeData.init(tmpeyeData);

	INT 					uiSize;
	INT iRateMode = DS.txRegs.gettxratemode();
	switch (iRateMode)
	{
		case 0: uiSize = 64;	break;
		case 1: uiSize = 128;  	break;
		case 2: uiSize = 256; 	break;
		case 3: uiSize = 512;	break;
		default: uiSize = 64;	break;
	}
	d2s_JTAG& jtag = d2s_JTAG::Instance();

	INT					data_slice = 0x1FFF0;
	INT					DS_OFFSET = 0x2;
	INT 				laneSize = 16;/*******For Broadcast*******/
	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_GetEyeMetricByFirmWare_Setup",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);

		if (laneSize % 2 == 0)
		{
			for (INT i = 0; i < laneSize / 2; i ++, data_slice +=  DS_OFFSET)
			{
				jtag.write(data_slice>>1,0x0101); /**Enable calibration**/
			}
		}
		else
		{
			for (INT i = 0; i < (laneSize - 1) / 2; i ++, data_slice +=  DS_OFFSET)
			{
				jtag.write(data_slice>>1,0x0101); /**Enable calibration**/
			}
			data_slice += DS_OFFSET;
			jtag.write(data_slice>>1,0x0101); /**Enable calibration**/
		}

		MCU.mcuRegs.setmcurstb(1).Write2DUT(0);

	d2s::d2s_LABEL_END();

	SITE_PASSFAIL_RESULT		APIScanResult;

	/******check code running status and wait for api scan done******/
	/*****this timer is used in API EYE SCAN , do not remove it.***/
//	DOUBLE			dMaxAPIEyeScanTime = 200;
//	DOUBLE			dAPIEyeScanTime = 0;
//	MyTimer::start("APIEyeScanTime");
//	dAPIEyeScanTime = MyTimer::stop_no_print("APIEyeScanTime");
//
//	TheInst.Wait(40*0.001);
//
//	while ((dAPIEyeScanTime < dMaxAPIEyeScanTime) && (false == APIScanResult.isAllSitePassed()))
//	{
//		STRING		sWaitAPIEYEDoneLabelName = "H16LRTV100_MPB_APIEYESCAN_CHECK_EXPECTVALUE";
//		ExpectFWPIEyeScanDone(MacroLane_Sel, sWaitAPIEYEDoneLabelName);
//		if (jtag.hasAllSitesPassed(sWaitAPIEYEDoneLabelName)) {
//			APIScanResult.init(true);
//		}
//
//		dAPIEyeScanTime = MyTimer::stop_no_print("APIEyeScanTime");
//		hout(DETAIL) << "APIEyeScanTime_ms :" << dAPIEyeScanTime << endl;
//	}
    INT iCheckCount = 0;
    INT iMaxTimeout = 200;

	while ((iCheckCount < iMaxTimeout) && (false == APIScanResult.isAllSitePassed()))
	{
		STRING		sWaitAPIEYEDoneLabelName = "H16LRTV100_MPB_APIEYESCAN_CHECK_EXPECTVALUE";
		ExpectFWPIEyeScanDone(MacroLane_Sel, sWaitAPIEYEDoneLabelName);
//		if (jtag.hasAllSitesPassed(sWaitAPIEYEDoneLabelName)) {
		if (hasAllSitesPassed()) {
			APIScanResult.init(true);
		}

		TheInst.Wait(0.002);
        iCheckCount++;
        hout(DETAIL) << "count " << iCheckCount << endl;
//		dAPIEyeScanTime = MyTimer::stop_no_print("APIEyeScanTime");
//		hout(DETAIL) << "APIEyeScanTime_ms :" << dAPIEyeScanTime << endl;
	}

	if (false == APIScanResult.isAllSiteFailed()) {
		d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_GetEyeMetricByFirmWare_READ",Global_D2S_Mode);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
			selectMacro(MacroID);

			INT		addr1 = 0x1FEF8;
			INT		addr2 = 0x1FEFA;
			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
				UINT LaneID = vLane[laneIndex];

				ostringstream eyewidthapi;
				ostringstream eyeheightapi;
				eyewidthapi << "DSEMAPIEYEWIDTH_READ2IDSTRING" << "_M" << MacroID << "_L" << LaneID << jtag.Context.c_str();
				eyeheightapi << "DSEMAPIEYEHEIGHT_READ2IDSTRING" << "_M" << MacroID << "_L" << LaneID << jtag.Context.c_str();

				jtag.read(addr1>>1,eyewidthapi.str());
				jtag.read(addr2>>1,eyeheightapi.str());

				addr1 += 0x4;
				addr2 += 0x4;
			}
		}

		d2s::d2s_LABEL_END();

		FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
			for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
				UINT MacroID = MacroLane_Sel[macroIndex].MacroID;

				const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;
				for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
					UINT LaneID = vLane[laneIndex];

					ostringstream eyewidthapi;
					ostringstream eyeheightapi;
					eyewidthapi << "DSEMAPIEYEWIDTH_READ2IDSTRING" << "_M" << MacroID << "_L" << LaneID << jtag.Context.c_str();
					eyeheightapi << "DSEMAPIEYEHEIGHT_READ2IDSTRING" << "_M" << MacroID << "_L" << LaneID << jtag.Context.c_str();
					INT		tmpeyewidth = (INT)jtag.getReadValue(eyewidthapi.str())[SiteID];
					INT		tmpeyeheight = (INT)jtag.getReadValue(eyeheightapi.str())[SiteID];

					INT		leftValue = tmpeyewidth & 0x00ff;
					INT 	rightValue = (tmpeyewidth & 0xff00)>> 8;
					INT		upValue = tmpeyeheight & 0x00ff;
					INT 	bottomValue = (tmpeyeheight & 0xff00) >> 8;

					if(leftValue > 128) leftValue -=256;
					eyeData[SiteID][MacroID][LaneID].leftValue = leftValue;
					if(rightValue > 128) rightValue -=256;
					eyeData[SiteID][MacroID][LaneID].rightValue = rightValue;
					if(upValue > 128) upValue -=256;
					eyeData[SiteID][MacroID][LaneID].upValue = upValue;
					if(bottomValue > 128) bottomValue -=256;
					eyeData[SiteID][MacroID][LaneID].bottomValue = bottomValue;
				}
			}
		FOREACH_ACTIVESITE_END
	} else {
		hout(GENERAL) << "All sites GetEyeMetricByFirmWare Eye Scan Time out !!!!!"  << endl;
	}

	/* Hold MCU in Reset */
	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ResetMCU_GetEyeMetricByFirmWare",Global_D2S_Mode);

		selectMacro_MB(MacroLane_Sel);
		/****Hold MCU in Reset mode****/
		MCU.mcuRegs.setmcurstb(0).Write2DUT(0);

	d2s::d2s_LABEL_END();

	/************Calc EyeWidth and EyeHeight and printToLog**************/

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
				UINT LaneID = vLane[laneIndex];
				eyeData[SiteID][MacroID][LaneID].eyeWidth = (DOUBLE)(eyeData[SiteID][MacroID][LaneID].rightValue - eyeData[SiteID][MacroID][LaneID].leftValue) / (DOUBLE)uiSize;
				eyeData[SiteID][MacroID][LaneID].eyeHeight = eyeData[SiteID][MacroID][LaneID].upValue - eyeData[SiteID][MacroID][LaneID].bottomValue;
				hout(DETAIL) << "MacroID = " << MacroID << "\tLaneID = " << LaneID
							  << "\tEye Width = " << eyeData[SiteID][MacroID][LaneID].eyeWidth << "\tEye Height = " << eyeData[SiteID][MacroID][LaneID].eyeHeight << endl;
			}
		}
	FOREACH_ACTIVESITE_END
}





void SetpmaMode() {

	INT 	pma_mode[8] = 					{0x2,0x0,0x0,0x0,0x1,0x1,0x1,0x1};
	INT 	pcie_sas_data_rate[8] = 		{NA	,0x0,0x1,0x2,0x4,0x5,0x6,0x7};
	INT 	pcie_sas_data_width[8] = 		{NA	,0x3,0x1,0x0,0x3,0x3,0x1,0x1};
	INT 	pstate_wrate_vld[8] =			{NA ,0x1,0x1,0x1,0x1,0x1,0x1,0x1};
	INT 	pcie_sas_rxtx_status_rdy[8] = 	{NA ,0x1,0x1,0x1,0x1,0x1,0x1,0x1};
	INT 	sigdetclkdiv_pinsel[8] = 		{NA ,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
	INT 	sigdet_clkdiv[8] = 				{NA ,0x0,0x0,0x1,0x0,0x0,0x0,0x1};
	INT 	sigdet_manual[8] = 				{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};
	INT 	sigdet_thr_sel_man[8] = 		{0x1,0x0,0x0,0x1,0x1,0x1,0x1,0x1};

	INT		Index;
	if (CUSTpara.Protocol == "COMMON") {
		Index = 0;
	} else if (CUSTpara.Protocol == "PCIE") {
		if (CUSTpara.Data_Rate == 2.5) {
			Index = 1;
		} else if (CUSTpara.Data_Rate == 5) {
			Index = 2;
		} else if (CUSTpara.Data_Rate == 8) {
			Index = 3;
		}
	} else if (CUSTpara.Protocol == "SAS" || CUSTpara.Protocol == "SATA") {
		if (CUSTpara.Data_Rate == 1.5) {
			Index = 4;
		} else if (CUSTpara.Data_Rate == 3) {
			Index = 5;
		} else if (CUSTpara.Data_Rate == 6) {
			Index = 6;
		} else if (CUSTpara.Data_Rate == 12) {
			Index = 7;
		}
	} else {
		hout(RELEASE) << "!!ERROR: Please select COMMON/PCIe/SAS/SATA mode!!" << endl;
		_exit(0);
	}

	DS.txRegs.setpma_mode(pma_mode[Index]).Write2DUT(48);
	if (CUSTpara.Protocol != "COMMON") {
		DS.txRegs.setpcie_sas_data_rate(pcie_sas_data_rate[Index])
				 .setpcie_sas_data_width(pcie_sas_data_width[Index])
				 .Write2DUT(48);
		DS.txRegs.setpstate_wrate_vld(pstate_wrate_vld[Index])
				 .setpcie_sas_rxtx_status_rdy(pcie_sas_rxtx_status_rdy[Index])
				 .Write2DUT(48);
		DS.rxRegs.setsigdetclkdiv_pinsel(sigdetclkdiv_pinsel[Index])
				 .setsigdet_clkdiv(sigdet_clkdiv[Index])
				 .Write2DUT(14);
	}
	DS.rxRegs.setsigdet_manual(sigdet_manual[Index])
			 .setsigdet_thr_sel_man(sigdet_thr_sel_man[Index])
			 .Write2DUT(40);

}


void SetsigdetMode()
{

	INT	rx_sigdet_bld_dly_sel[8] = 	{0x0,0x0,0x0,0x0,0x1,0x1,0x1,0x1};
	INT	sigdet_win[8] = 			{0x6,NA ,NA ,0x5,0x0,0x0,0x0,0x0};
	INT	sigdet_win_pcie[8] = 		{NA ,0x5,0x5,NA ,NA ,NA ,NA ,NA };
	INT	sigdet_vlv[8] = 			{0xB,0xB,0xB,0xB,0xB,0xB,0xB,0xB};
	INT	sigdet_thr_s1[8] = 			{NA ,0x15,0x15,NA ,NA ,NA ,NA ,NA };
	INT	sigdet_thr_s2[8] = 			{0x20,NA ,NA ,0x15,0x02,0x02,0x02,0x02};
	INT	squelch_detwin[8] = 		{NA ,NA ,NA ,NA ,0x0,0x0,0x0,0x0};
	INT	squelch_det_thr[8]	 = 		{NA ,NA ,NA ,NA ,0x2,0x2,0x2,0x2};
	INT	squelch_det_en[8] = 		{NA ,NA ,NA ,NA ,0x1,0x1,0x1,0x1};
	INT	sigdet_enable[8] = 			{0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};
	INT		Index;
	if (CUSTpara.Protocol == "COMMON") {
		Index = 0;
	} else if (CUSTpara.Protocol == "PCIE") {
		if (CUSTpara.Data_Rate == 2.5) {
			Index = 1;
		} else if (CUSTpara.Data_Rate == 5) {
			Index = 2;
		} else if (CUSTpara.Data_Rate == 8) {
			Index = 3;
		}
	} else if (CUSTpara.Protocol == "SAS" || CUSTpara.Protocol == "SATA") {
		if (CUSTpara.Data_Rate == 1.5) {
			Index = 4;
		} else if (CUSTpara.Data_Rate == 3) {
			Index = 5;
		} else if (CUSTpara.Data_Rate == 6) {
			Index = 6;
		} else if (CUSTpara.Data_Rate == 12) {
			Index = 7;
		}
	}
	else {
		hout(RELEASE) << "!!ERROR: Please select COMMON/PCIe/SAS/SATA mode!!" << endl;
		_exit(0);
	}

	if (rx_sigdet_bld_dly_sel[Index] != NA) {
	DS.rxRegs.setrx_sigdet_bld_dly_sel(rx_sigdet_bld_dly_sel[Index]).Write2DUT(31);
	}

	if (sigdet_win[Index] != NA) {
		DS.rxRegs.setsigdet_win(sigdet_win[Index]).Write2DUT(60);
	}
	if (sigdet_win_pcie[Index] != NA) {
		DS.rxRegs.setsigdet_win_pcie(sigdet_win_pcie[Index]).Write2DUT(27);
	}

	if (sigdet_vlv[Index] != NA) {
		DS.rxRegs.setsigdet_vlv(sigdet_vlv[Index]).Write2DUT(59);
	}

	if (sigdet_thr_s1[Index] != NA) {
		DS.rxRegs.setsigdet_thr_s1(sigdet_thr_s1[Index]).Write2DUT(60);
	}

	if (sigdet_thr_s2[Index] != NA) {
		DS.rxRegs.setsigdet_thr_s2(sigdet_thr_s2[Index]).Write2DUT(61);
	}

	if (CUSTpara.Protocol == "SAS" || CUSTpara.Protocol == "SATA") {
		DS.rxRegs.setsquelch_detwin(squelch_detwin[Index]).Write2DUT(44);
		DS.rxRegs.setsquelch_det_thr(squelch_det_thr[Index]).Write2DUT(37);
		DS.rxRegs.setsquelch_det_en(squelch_det_en[Index]).Write2DUT(50);
	}

	DS.rxRegs.setsigdet_enable(sigdet_enable[Index]).Write2DUT(60);
}

void HiLinkPreset (){
	DS.txRegs.settxpwrdb(0x1).Write2DUT(0);
	DS.rxRegs.setrxpwrdb(0x1).Write2DUT(0);
	DS.rxRegs.setrxterm_floating_sel(0x1).Write2DUT(8);
}



void DSCLK_Setup(MACRO_LANE_SEL& MacroLane_Sel , LANE_DOUBLE IOSCDAC_BAND) {

	LANE_INT                      psel;
	LANE_INT                      s1sel;
	LANE_INT                      s2sel;
	LANE_INT                      injlvl;
	LANE_INT                      injtune;
	LANE_INT                      ptatmixctrl;

	//=============================================
	// Variables and MacroLane initialization
	//=============================================

	FOREACH_ACTIVESITE_BEGIN(SiteID, bInterrupt)
		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
				UINT LaneID = vLane[laneIndex];
				if(IOSCDAC_BAND[SiteID][MacroID][LaneID] == 15) {
					psel[SiteID][MacroID][LaneID] = 0x6;
					s1sel[SiteID][MacroID][LaneID] = 0x5;
					s2sel[SiteID][MacroID][LaneID] = 0x2;
					injlvl[SiteID][MacroID][LaneID] = 0x6;
					injtune[SiteID][MacroID][LaneID] = 0x3;
					ptatmixctrl[SiteID][MacroID][LaneID] = 164;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 14) {
					psel[SiteID][MacroID][LaneID] = 0x6;
					s1sel[SiteID][MacroID][LaneID] = 0x5;
					s2sel[SiteID][MacroID][LaneID] = 0x1;
					injlvl[SiteID][MacroID][LaneID] = 0x6;
					injtune[SiteID][MacroID][LaneID] = 0x3;
					ptatmixctrl[SiteID][MacroID][LaneID] = 164;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 13) {
					psel[SiteID][MacroID][LaneID] = 0x6;
					s1sel[SiteID][MacroID][LaneID] = 0x5;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x6;
					injtune[SiteID][MacroID][LaneID] = 0x3;
					ptatmixctrl[SiteID][MacroID][LaneID] = 164;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 12) {
					psel[SiteID][MacroID][LaneID] = 0x6;
					s1sel[SiteID][MacroID][LaneID] = 0x4;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x6;
					injtune[SiteID][MacroID][LaneID] = 0x3;
					ptatmixctrl[SiteID][MacroID][LaneID] = 164;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 11) {
					psel[SiteID][MacroID][LaneID] = 0x6;
					s1sel[SiteID][MacroID][LaneID] = 0x3;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x6;
					injtune[SiteID][MacroID][LaneID] = 0x3;
					ptatmixctrl[SiteID][MacroID][LaneID] = 36;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 10) {
					psel[SiteID][MacroID][LaneID] = 0x5;
					s1sel[SiteID][MacroID][LaneID] = 0x3;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x6;
					injtune[SiteID][MacroID][LaneID] = 0x2;
					ptatmixctrl[SiteID][MacroID][LaneID] = 36;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 9) {
					psel[SiteID][MacroID][LaneID] = 0x5;
					s1sel[SiteID][MacroID][LaneID] = 0x2;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x6;
					injtune[SiteID][MacroID][LaneID] = 0x2;
					ptatmixctrl[SiteID][MacroID][LaneID] = 36;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 8) {
					psel[SiteID][MacroID][LaneID] = 0x5;
					s1sel[SiteID][MacroID][LaneID] = 0x1;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x5;
					injtune[SiteID][MacroID][LaneID] = 0x2;
					ptatmixctrl[SiteID][MacroID][LaneID] = 36;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 7) {
					psel[SiteID][MacroID][LaneID] = 0x4;
					s1sel[SiteID][MacroID][LaneID] = 0x1;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x5;
					injtune[SiteID][MacroID][LaneID] = 0x2;
					ptatmixctrl[SiteID][MacroID][LaneID] = 36;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 6) {
					psel[SiteID][MacroID][LaneID] = 0x3;
					s1sel[SiteID][MacroID][LaneID] = 0x1;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x4;
					injtune[SiteID][MacroID][LaneID] = 0x2;
					ptatmixctrl[SiteID][MacroID][LaneID] = 36;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 5) {
					psel[SiteID][MacroID][LaneID] = 0x2;
					s1sel[SiteID][MacroID][LaneID] = 0x1;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x3;
					injtune[SiteID][MacroID][LaneID] = 0x2;
					ptatmixctrl[SiteID][MacroID][LaneID] = 36;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 4) {
					psel[SiteID][MacroID][LaneID] = 0x2;
					s1sel[SiteID][MacroID][LaneID] = 0x0;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x3;
					injtune[SiteID][MacroID][LaneID] = 0x2;
					ptatmixctrl[SiteID][MacroID][LaneID] = 36;
				} else if(IOSCDAC_BAND[SiteID][MacroID][LaneID] == 3) {
					psel[SiteID][MacroID][LaneID] = 0x0;
					s1sel[SiteID][MacroID][LaneID] = 0x0;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x0;
					injtune[SiteID][MacroID][LaneID] = 0x0;
					ptatmixctrl[SiteID][MacroID][LaneID] = 27;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 2) {
					psel[SiteID][MacroID][LaneID] = 0x0;
					s1sel[SiteID][MacroID][LaneID] = 0x0;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x0;
					injtune[SiteID][MacroID][LaneID] = 0x0;
					ptatmixctrl[SiteID][MacroID][LaneID] = 27;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 1) {
					psel[SiteID][MacroID][LaneID] = 0x0;
					s1sel[SiteID][MacroID][LaneID] = 0x0;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x0;
					injtune[SiteID][MacroID][LaneID] = 0x0;
					ptatmixctrl[SiteID][MacroID][LaneID] = 27;
				} else if (IOSCDAC_BAND[SiteID][MacroID][LaneID] == 0) {
					psel[SiteID][MacroID][LaneID] = 0x0;
					s1sel[SiteID][MacroID][LaneID] = 0x0;
					s2sel[SiteID][MacroID][LaneID] = 0x0;
					injlvl[SiteID][MacroID][LaneID] = 0x0;
					injtune[SiteID][MacroID][LaneID] = 0x0;
					ptatmixctrl[SiteID][MacroID][LaneID] = 27;
				}
			}
		}
	FOREACH_ACTIVESITE_END

	/***************Relevant Reg Config*******************/
	d2s_JTAG& jtag = d2s_JTAG::Instance();

	LANE_INT                CSR6value;
	LANE_INT                CSR8value;

	CSR_READ(MacroLane_Sel, DS.clkRegs, 6,CSR6value);
	CSR_READ(MacroLane_Sel, DS.clkRegs, 8,CSR8value);

    Update_ForDynamicWrite(MacroLane_Sel, DS.clkRegs.REG_INFO.psel(), psel, CSR6value);
    Update_ForDynamicWrite(MacroLane_Sel, DS.clkRegs.REG_INFO.s1sel(), s1sel, CSR6value);
    Update_ForDynamicWrite(MacroLane_Sel, DS.clkRegs.REG_INFO.s2sel(), s2sel, CSR6value);
    Update_ForDynamicWrite(MacroLane_Sel, DS.clkRegs.REG_INFO.injlvl(), injlvl, CSR6value);
    Update_ForDynamicWrite(MacroLane_Sel, DS.clkRegs.REG_INFO.injtune(), injtune, CSR6value);

    Update_ForDynamicWrite(MacroLane_Sel, DS.clkRegs.REG_INFO.ptatmixctrl(), ptatmixctrl, CSR8value);

	d2s::d2s_LABEL_BEGIN("H16LRTV100_MPB_ILOLockMargin_DSDynamic_setup",Global_D2S_Mode);

		for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++) {
			UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
			selectMacro(MacroID);
			const vector<UINT>& vLane = MacroLane_Sel[macroIndex].vLane;

			for (UINT laneIndex = 0; laneIndex < vLane.size(); laneIndex ++) {
				UINT LaneID = vLane[laneIndex];
				DS.clkRegs.SliceID(LaneID).Broadcast(0);

                ostringstream id6;
                id6 << "DSCLK_CSR6_" << "_M" << MacroID << "_L" << LaneID << jtag.Context;
                map<int,long long> tmp6;
                parseSiteDataFromLaneInt(tmp6,CSR6value,MacroID,LaneID);
				DS.clkRegs.Write2DUT_DYN(6,tmp6,id6.str());

                ostringstream id8;
                id8 << "DSCLK_CSR8_" << "_M" << MacroID << "_L" << LaneID << jtag.Context;
                map<int,long long> tmp8;
                parseSiteDataFromLaneInt(tmp8,CSR8value,MacroID,LaneID);
				DS.clkRegs.Write2DUT_DYN(8,tmp8,id8.str());
			}
		}

	d2s::d2s_LABEL_END();
}


