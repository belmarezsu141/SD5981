#ifndef HILINK_COMMON_TYPE
#define HILINK_COMMON_TYPE

//#include "mapi.hpp"
#include <type.h>
using namespace std;

#include <assert.h>
#include <stdio.h>
#include <map>
#include <vector>

#define Hi6871 
#ifdef Hi6871
const UINT		HILINK_SITE_NUMBER = 2; //S08V100
const UINT		HILINK_MACRO_NUM = 2;
const UINT		HILINK_LANE_NUM = 2;
#else 
const UINT		HILINK_SITE_NUMBER = 4;
const UINT		HILINK_MACRO_NUM = 6;
const UINT		HILINK_LANE_NUM = 4;
#endif 

const UINT      HILINK_INIT_VECTOR_NUM = 3;


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
//	string	write_DR2_template_prefix;
//	string	write_DR1_template_prefix;
//	string	write_DR0_template_prefix;
//	string	write_IR2_template_prefix;
//	string	write_IR1_template_prefix;
//	string	write_IR0_template_prefix;
//	string	read_template_prefix;
//	string	wait_template_prefix;
//	string	write_DR_template_prefix;
//	string	write_IR_template_prefix;
} T_JTAG_DEFINITION;


typedef enum{
	PLL0,
    PLL1,
	INVAILD_PLL
} 	PLL_TYPE;

typedef enum{
	H15_IP,
	H30_IP,
	ATHENA,
	INVAILD_IP
} 	HILINK_TYPE;

typedef enum{
	H30_LR,
	H30_VSR,
	H30_TC_BP,
	H30_TC_C2C,
	INVAILD_H30
} 	H30_TYPE;

typedef struct {
    PLL_TYPE PLL_Type;
    UINT Lane_Num;
    HILINK_TYPE Hilink_Type;
    H30_TYPE H30_Type;
    UINT SS_MacroID;
    LONG IR0;
    LONG DR0;
    LONG IR1;
    LONG DR1;
    LONG IR2;
    int DS_powerup_sequence[HILINK_LANE_NUM];
    int DS_powerdown_sequence[HILINK_LANE_NUM];
    int Datalog_EN[HILINK_LANE_NUM];
    int RefclockChoose[HILINK_INIT_VECTOR_NUM];
    int life2digChoose[HILINK_INIT_VECTOR_NUM];

} T_HILINK_INFO; //TODO

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
	NONE_PIN,
} 	JUDGE_PIN;

typedef enum{
	FT_PROGRAM,
	CP_PROGRAM,
	CHAR_PROGRAM
} PROGRAM_TYPE;

typedef struct{
	LANE_TYPE		type;
	string          Lane_Name;
	STRING			TX_to;
	STRING 			TX_P;
	STRING 			TX_N;
	STRING			RX_from;
	STRING 			RX_P;
	STRING 			RX_N;
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

typedef struct
{
	uint CTLEACTGN1;
	uint CTLEACTGN2;
	uint CTLEACTGN3;
	uint CTLEBST1;
	uint CTLEBST2;
	uint CTLEBST3;
	uint CTLESQH1;
	uint CTLESQH2;
	uint CTLESQH3;
	uint CTLEZA1;
	uint CTLEZA2;
	uint CTLEZA3;
	uint CTLERMBAND1;
	uint CTLERMBAND2;
	uint CTLERMBAND3;
	uint CTLECMBAND1;
	uint CTLECMBAND2;
	uint CTLECMBAND3;
	uint CTLEHFZEN1;
	uint CTLEHFZEN2;
	uint CTLEHFZEN3;
	uint CTLEREFSEL;
	uint CPHSOFFT;
    uint CTLEloadsel;
} Ctle_Set;



typedef struct {
	uint iPll1vcodivvregcalbypass_api;
	uint iPll1cpvrefcalbypass_api;
	uint iPll1dlfvregcalbypass_api;
	uint iPll1pllvregcalbypass_api;
	uint iPll1vcocalbypass_api;
	uint iPll0vcodivvregcalbypass_api;
	uint iPll0cpvrefcalbypass_api;
	uint iPll0dlfvregcalbypass_api;
	uint iPll0pllvregcalbypass_api;
	uint iPll0vcocalbypass_api;
	uint iCsvrefgencalbypass_api;
	uint iCsrxtermcalbypass_api;
	uint iCsbandgapcalbypass_api;
	uint iCsgetdpminfobypass_api;
} CSAPI;

typedef struct {
	INT iDsclkvrefgencalbypass_api		;
	INT iDsclkvregcalbypass_api			;
	INT iRxctlevregcalbypass_api		;
	INT iRxopampofstcalbypass_api		;
	INT iRxsumloadrescalbypass_api		;
	INT iRxclkvregcalbypass_api			;
	INT iRxdatavregcalbypass_api		;
	INT iRxsigdetofstcalbypass_api		;
	INT iRxctleofstcalbypass_api		;
	INT iRxsumofstcalbypass_api			;
	INT iRxlatchofstcalbypass_api		;
	INT iRxalfgenofstcalbypass_api		;
	INT iTxdrvregcalbypass_api			;
	INT iTxpredrvregcalbypass_api		;
	INT iTxrxserlpbkofstcalbypass_api	;
	INT iTxdcdcalibbypass_api			;
	INT	iRxctlerefcallibbypass_api		;
	INT iRxctlecurrentcallibbypass_api	;
	INT iLbpkdcdcallibbypass_api		;
	INT iTxcenterpabypass_api			;
	INT iRxalfgenstepsizecalibbypass_api;
}DSAPI;


typedef struct {
	INT iCtle_latchofst_en_api		;
	INT iDfe_boost_en_api			;
	INT iDS_boost_squelch_en_api	;
	INT iDS_offset_en_api			;
	INT iCtle_refsel_en_api			;
	INT iGain_attn_en_api			;
	INT iCentering_en_api			;
	INT iAlphagen_opst_en_api		;
	INT iDlev_target_api			;
	INT iDs_ctle_en_api				;
	INT iCtle_dfetap1_bypass_en_api	;
}DSAPI_Adaptation;


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
	Custom_ALL0,
	Custom_ALL1,
	Custom_0101,
	Custom_0011,
	Custom_00001111,
        Custom_1010,
}       PRBS_Pattern;





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
        INT ALOS_ExpectValue;
        INT ALOS_ReadPerLane;
}       TTR_OPTIMIZE_CYCLE;

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

typedef struct{

        vector<T_CHECK_DATA> MCU;
        vector<T_CHECK_DATA> TOP_API_CSR;
        vector<T_CHECK_DATA> ABIST_API_CSR;
        vector<T_CHECK_DATA> CP_API_CSR;
        vector<T_CHECK_DATA> CS_API_CSR;
        vector<T_CHECK_DATA> DS_API_CSR;

        vector<T_CHECK_DATA> CS_CLK_CSR;
        vector<T_CHECK_DATA> CS_CLKDBG_CSR;

        vector<T_CHECK_DATA> DS_CLK_CSR;
        vector<T_CHECK_DATA> DS_RXEXT_CSR;
        vector<T_CHECK_DATA> DS_TX_CSR;
        vector<T_CHECK_DATA> DS_RX_CSR;




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
		string			PowerUpSeq;	\
		string			PowerDnSeq;\
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
	PowerUpSeq=_HILINK_INFO[id].PowerUpSeq; \
	PowerDnSeq=_HILINK_INFO[id].PowerDnSeq; \
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

typedef enum{
	ALL0,
	ALL1,
	UNSTABLE
} 	SIGDET;

typedef struct{
	INT Gain[3];
	INT Boost[3];
	INT Za[3];
	INT Sqh[3];
	INT Rmband[3];
	INT Cmband[3];
	INT Hfzen[3];
} 	RxCTLE_SETTING;

typedef struct{
	INT iTxPre2nd;
	INT iTxPre1st;
	INT iTxMain;
	INT iTxPost1st;
	INT iTxPost2nd;
} 	TxFIR_SETTING;

typedef struct{
	INT iFxtap[10];//Fxtap[0] = tap1cen, Fxtap[9] = tap1edg;
	INT iMvtap[6];

} 	DFE_SETTING;

typedef struct Tx_Reg_PPM_Info{
	int 	Reg_Value;
	double	PPM_externdedMode;
	double  PPM_normalMode;
}	Tx_Reg_PPM;


#endif
