#ifndef HILINK_COMMON_TYPE
#define HILINK_COMMON_TYPE
#include <type.h>
using namespace std;

#include <assert.h>
#include <stdio.h>
#include <map>
#include <vector>

typedef struct{
	string std_wavetable;
	string fastdiff_wavetable;
} T_JTAG_WAVETABLE;

typedef struct{
	string	port_name;
	string	tdi_pin;
	string	tdo_pin;
	string	tms_pin;
	string	tck_pin;
	string	trstn_pin;
	T_JTAG_WAVETABLE wavetable;
	uint	HilinkIRLength;
	uint	HilinkDR0Length;
	uint	HilinkDR1Length;
	string	d2s_template[10];
} T_JTAG_DEFINITION;


typedef enum{
	CSL,
	CSH,
	NOTEXIST
} 	CS_TYPE;

typedef enum{
	HiLink16LRTV100,
	INVAILD_IP
} 	HILINK_TYPE;


typedef struct{
	CS_TYPE 		CS0_Type;
	CS_TYPE 		CS1_Type;
	UINT            Lane_Num;
	HILINK_TYPE     Hilink_Type;
	LONG            IR0;
	LONG 			DR0;
	LONG 			IR1;
	LONG 			DR1;
	LONG 			IR2;
} 	T_HILINK_INFO;

typedef map<uint,T_HILINK_INFO> Map_HILINK_INFO;

typedef enum{
	LANE_DISABLE,
	LANE_BOTH,
	LANE_RX_ONLY,
	LANE_TX_ONLY
} 	LANE_TYPE;

typedef enum{
	PIN_RXP,
	PIN_RXN,
	PIN_TXP,
	PIN_TXN,
	NONE
} 	JUDGE_PIN;

typedef enum{
	FT_PROGRAM,
	CP_PROGRAM,
	CHAR_PROGRAM
} PROGRAM_TYPE;

typedef struct{
	LANE_TYPE		type;
	STRING 			TX_P;
	STRING 			TX_N;
	STRING			TX_to;
	STRING 			RX_P;
	STRING 			RX_N;
	STRING			RX_from;
} 	T_LANE_INFO;

typedef struct{
        UINT MacroID;
        UINT SliceID;
        vector<UINT> vLane;
} T_MACRO_LANE_SEL;

typedef struct{
	UINT MacroID;
	UINT LaneID;
} 	T_MacroLaneID;

typedef vector<T_MACRO_LANE_SEL> MACRO_LANE_SEL;

typedef struct{
	uint csr;
	string reg_name;
	uint hi_bit;
	uint low_bit;
} T_REG_INFO;

class HILINK_Regs_Base;

typedef struct{
	HILINK_Regs_Base& parent;
	T_REG_INFO reg_info;
} T_REG_INFO_EX;

typedef map<string,uint> M_CSR_INFO;

typedef struct{
	uint csrindex;
	uint value;
	uint mask;
} T_EXPECT_INFO;

typedef vector<T_EXPECT_INFO> T_EXPECT_INFOs;

typedef enum{
	PRBS7,
	PRBS9,
	PRBS10,
	PRBS11,
	PRBS15,
	PRBS20,
	PRBS23,
	PRBS31,
	Custom_CLK,
	Custom_00110011,
	Custom_0000111100001111,
	Custom_ALL0,
	Custom_ALL1,
	Custom_FF00,
} 	PRBS_Pattern;

struct JI {
	INT AMPINDEX;
	INT FREQINDEX;
	INT Kfactor;
};

typedef struct{
	INT 	Findex;
	DOUBLE	JFreqDiff;
	DOUBLE	jFreq;
}	JITFREQ;

typedef struct {
	DOUBLE eyeWidth;
	DOUBLE eyeHeight;
	INT	   leftValue;
	INT	   rightValue;
	INT	   bottomValue;
	INT	   upValue;
} EYEDATA;


typedef struct {
	INT	   bottomShrinkValue;
	INT	   upShrinkValue;
	INT	   phaseShrinkValue;
} plotData;

typedef struct{
	int address;
	int data;
	int mask;
} T_CHECK_DATA;


typedef enum{
	ALL0,
	ALL1,
	UNSTABLE
} 	SIGDET;

typedef struct{
	vector<T_CHECK_DATA> CS_CLK_CSR;
	vector<T_CHECK_DATA> DS_CLK_CSR;
	vector<T_CHECK_DATA> DS_TX_CSR;
	vector<T_CHECK_DATA> DS_RX_CSR;
	vector<T_CHECK_DATA> CTRLPLANE_MCU;;
} T_HILINK_CSR_CHECK;


typedef struct{
	double			start_val;
	double			stop_val;
	double			step_val;
	vector<string>&	speclist;
	string 			RxPortName;
	string 			ALOS_RX_Pattern;
	uint			ALOS_RX_Pattern_cycle;
	const T_REG_INFO_EX& 	reg_info_ex;
	uint			read_count;
}T_ALOS_SEARCH_INFO;


typedef struct{
	INT Gain[4];
	INT Boost[3];
	INT CMBand[3];
	INT RMBand[3];
	INT ZA[3];
	INT SQH[3];
} 	RxCTLE_SETTING;

typedef struct{
	INT iTxPre2nd;
	INT iTxPre1st;
	INT iTxMain;
	INT iTxPost1st;
	INT iTxPost2nd;
} 	TxFIR_SETTING;

typedef struct{
	INT	dfefxtap1;
	INT	dfefxtap2;
	INT	dfefxtap3;
	INT	dfefxtap4;
	INT	dfefxtap5;
	INT	dfemvtap1;
	INT	dfemvtap2;
	INT	dfemvtap3;
	INT	dfemvtap4;
	INT	dfemvtap5;
	INT	dfemvtap6;
}	RxDFE_SETTING;

typedef struct Tx_Reg_PPM_Info{
	int 	Reg_Value;
	double	PPM_externdedMode;
	double  PPM_normalMode;
}	Tx_Reg_PPM;


class C_HILINK_INFO{
private:
	virtual void get_info(uint id,uint& MacroID,T_HILINK_INFO& Info,string& PowerUpSeq,string& PowerDnSeq,vector<T_LANE_INFO>& lane_info) const=0;
	mutable map<uint,T_HILINK_INFO> macroid_hilink_info_map;
	mutable map<uint,uint> macroid_storeid_map;
	mutable map<uint,vector<T_LANE_INFO> > macroid_lane_info_map;
	mutable vector<uint> all_macroid;
	mutable map<uint,vector<int> > macroid_PowerUpSeq_map;
	mutable map<uint,vector<int> > macroid_PowerDnSeq_map;
	void initial_info() const;
public:
	C_HILINK_INFO();
	virtual ~C_HILINK_INFO();
	const T_HILINK_INFO& operator[](uint MacroID) const;
	const T_HILINK_INFO& getHiLinkInfo(uint MacroID) const;
	const T_LANE_INFO& get_lane_info(uint MacroID,uint LaneID) const;
	const vector<int>& get_PowerUpSeq(uint MacroID) const;
	const vector<int>& get_PowerDnSeq(uint MacroID) const;
	uint get_Macro_Store_ID(uint MacroID) const;
	void get_AllMacroList(vector<uint>& list) const;
	uint getFirstMacroID() const;
};

class C_LANE_INFO{
private:
	class LANE_INFO_ON_MACRO{
	friend class C_LANE_INFO;
	public:
		const T_LANE_INFO& operator[](uint laneid) const;
		LANE_INFO_ON_MACRO();
	private:
		mutable uint MacroID;
	};
private:
	LANE_INFO_ON_MACRO lane_info_each_macro;
	C_LANE_INFO();

public:
	static const C_LANE_INFO& getInstance();
	const LANE_INFO_ON_MACRO& operator[](uint MacroID) const;
	const T_MacroLaneID get_MacroLaneID(const string& pin) const;
};

extern const C_LANE_INFO& LANE_INFO;

#define HILINK_INFO_BEGIN() class This_HILINK_INFO:public C_HILINK_INFO{ \
private: \
	typedef struct{ \
		uint MacroID; \
		T_HILINK_INFO info; \
		T_LANE_INFO LANE_INFO[HILINK_LANE_NUM]; \
	} sT_HILINK_INFO; \
	void get_info(uint id,uint& MacroID,T_HILINK_INFO& Info,string& PowerUpSeq,string& PowerDnSeq,vector<T_LANE_INFO>& lane_info) const{ \


#define HILINK_INFO_END() \
	static bool isinit=false; \
	if(!isinit){ \
		if((sizeof(_HILINK_INFO)/sizeof(_HILINK_INFO[0])) != HILINK_MACRO_NUM){ \
			puts("Error: Item in HILINK_INFO[] is different from HILINK_MACRO_NUM!\n"); \
			printf("Error: Count of HILINK_INFO = %d\n",sizeof(_HILINK_INFO)/sizeof(_HILINK_INFO[0])); \
		} \
		isinit=true; \
	} \
	\
	assert(id<HILINK_MACRO_NUM); \
	MacroID=_HILINK_INFO[id].MacroID; \
	Info=_HILINK_INFO[id].info; \
	lane_info.clear(); \
	for(uint i=0;i<HILINK_LANE_NUM;i++){ \
		lane_info.push_back(_HILINK_INFO[id].LANE_INFO[i]); \
	} \
	\
	} \
	This_HILINK_INFO(){}; \
	virtual ~This_HILINK_INFO(){}; \
	public: \
static const This_HILINK_INFO& getInstance(){static This_HILINK_INFO inst;return inst;} \
}; \
extern const This_HILINK_INFO& HILINK_INFO; \


const RxCTLE_SETTING RxCTLE_default = {
				{5,5,5},/*CTLE GAIN*/
				{0,0,0},/*CTLE BOOST*/
				{0,0,0},/*CTLE CMBand*/
				{0,0,0},/*CTLE RMBand*/
				{0,0,0},/*CTLE ZA*/
				{0,0,0} /*CTLE SQH*/
};
const TxFIR_SETTING TxFIR_default = {0, 0, 63, 0, 0};/*iTxPre2nd, iTxPre1st, iTxMain, iTxPost1st, iTxPost2nd*/

class GLOBAL_SSPARA {
public:
	DOUBLE 	Refclk;		 /*Mhz*/
	INT		RefclkBus;
	INT		SDiv;
	void initial() {
		Refclk = 0;
		RefclkBus = 0;
		SDiv = 0;
	}
	void clear() {
		Refclk = 0;
		RefclkBus = 0;
		SDiv = 0;
	}
};

class GLOBAL_CSPARA {
public:
//	DOUBLE	RCDCLK;		/*Mhz*/
	INT		Mdiv;		/*REFCLKDIV*/
	DOUBLE	VCOfreq;
	INT		KDiv;		/*CMLDIV  K = Ka*Kb*/
	INT		KaDiv;
	INT 	KbDiv;
	DOUBLE	HSCLK;		/*Ghz*/
//	INT		SSC_BYPASSB;
	INT 	NDiv;
	INT 	PDiv;		/*FBDIVP*/
	INT 	SDiv;		/*FBDIVS*/
	INT 	JDiv;		/*WORDCLKDIV*/
	INT 	GDiv;
	INT 	WDiv;		/*WORDCLKDIV2*/
	INT 	VDiv;		/*WORDCLKDIV2_16B32B*/
//	DOUBLE	A2DInterface;
	void initial() {
	//	RCDCLK = 0;
		Mdiv = 0;
		VCOfreq = 0;
		KDiv = 0;
		KaDiv = 0;
		KbDiv = 0;
		HSCLK = 0;
	//	SSC_BYPASSB = 0;
		NDiv = 0;
		PDiv = 0;
		SDiv = 0;
		JDiv = 0;
		GDiv = 0;
		WDiv = 0;
		VDiv = 0;
	//	A2DInterface = 0;
	}
	void clear() {
	//	RCDCLK = 0;
		Mdiv = 0;
		VCOfreq = 0;
		KDiv = 0;
		KaDiv = 0;
		KbDiv = 0;
		HSCLK = 0;
	//	SSC_BYPASSB = 0;
		NDiv = 0;
		PDiv = 0;
		SDiv = 0;
		JDiv = 0;
		GDiv = 0;
		WDiv = 0;
		VDiv = 0;
	//	A2DInterface = 0;
	}
};

class GLOBAL_CUSTPARA {
public:
	STRING 			Protocol;
	DOUBLE			Data_Rate;   /*Gbps*/
	INT				CSslice;
	INT				RateMode;
	INT				DataWidth;
	bool			SSCGen_EN;
	INT				TxDrvResSel;
	INT				RxTermResSel;
	INT				TxRegDrvLvl;
//	INT				RxCTLERefSel;
	STRING 			FIR_setting;
	TxFIR_SETTING	TxFIR_USER;
	STRING 			CTLE_setting;
	RxCTLE_SETTING 	RxCTLE_USER;
	INT 			RxCapBypass;
	bool			SSCDR_EN;
	STRING			Scenario;
	void initial() {
		Protocol = "";
		Data_Rate = 0;   /*Gbps*/
		CSslice = 0;
		RateMode = 0;
		DataWidth = 0;
		SSCGen_EN = false;
		TxDrvResSel = 0;
		RxTermResSel = 0;
		TxRegDrvLvl = 0;
//		RxCTLERefSel = 0;
		FIR_setting = "DEFAULT";
		TxFIR_USER = TxFIR_default;
		CTLE_setting = "DEFAULT";
		RxCTLE_USER = RxCTLE_default;
		RxCapBypass = 0;
		SSCDR_EN = false;
		Scenario = "BP";
	}
	void clear() {
		Protocol = "";
		Data_Rate = 0;   /*Gbps*/
		CSslice = 0;
		RateMode = 0;
		DataWidth = 0;
		SSCGen_EN = false;
		TxDrvResSel = 0;
		RxTermResSel = 0;
		TxRegDrvLvl = 0;
//		RxCTLERefSel = 0;
		FIR_setting = "DEFAULT";
		TxFIR_USER = TxFIR_default;
		CTLE_setting = "DEFAULT";
		RxCTLE_USER = RxCTLE_default;
		RxCapBypass = 0;
		SSCDR_EN = false;
		Scenario = "BP";
	}
};

#endif
