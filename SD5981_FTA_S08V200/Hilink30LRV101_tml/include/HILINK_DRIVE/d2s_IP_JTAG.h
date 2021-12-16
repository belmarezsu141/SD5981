/*
 * d2s_IP_JTAG.h
 *
 *  Created on: Jun 13, 2016
 *      Author: yanfen.fang
 */

#ifndef D2S_IP_JTAG_H_
#define D2S_IP_JTAG_H_
#include <HILINK_DRIVE/HiLinkPatternHelper.h>
#include <SRC_d2s/d2s.h>
#include <UserConfig.h>

/*	GET_USER_FLAG("d2s_mode",&d2s_mode);	\  */
/*	GET_USER_FLAG("d2s_mode",&d2s_mode);	\  */
//jtag.getContext();
extern bool PrintDebugEn;
extern bool PrintFWDetailLogEn;
extern d2sWorkModeType Global_D2S_Mode;
#define D2S_FRAMEWORK_JTAG(jtag_id)	d2s_IP_JTAG::select_JTAG(jtag_id);	\
									int d2s_mode;	\
									GET_USER_FLAG("d2s_mode",&d2s_mode);	\
									d2sFramework fr;\
									fr.default_mode=d2sFrameWorkModeType::Enum(d2s_mode);\
									for(uint i=0;i<JTAG_PORT_COUNT;i++){\
										d2s_IP_JTAG & jtag = d2s_IP_JTAG::JTAG_port(i);	\
										jtag.getContext();	\
										fr.registerTransactionPort(jtag);	\
									}\
									d2s_IP_JTAG & jtag = d2s_IP_JTAG::Instance();	\


//TODO
#define D2S_FRAMEWORK_JTAG_CURRENT	d2s_IP_JTAG::select_JTAG(d2s_IP_JTAG::get_current_JTAG_port());	\
									int d2s_mode;	\
									GET_USER_FLAG("d2s_mode",&d2s_mode);	\
									d2sFramework fr;\
									fr.default_mode=d2sFrameWorkModeType::Enum(d2s_mode);\
									for(uint i=0;i<JTAG_PORT_COUNT;i++){\
										d2s_IP_JTAG & jtag = d2s_IP_JTAG::JTAG_port(i);	\
										jtag.getContext();	\
										fr.registerTransactionPort(jtag);	\
									}\
									char label[128]="";\
									d2s_IP_JTAG & jtag = d2s_IP_JTAG::Instance();	\


typedef enum {
    HILINK_JTAG_WRITEDYN_DR2,
    HILINK_JTAG_WRITEDYN_WAIT
} E_HILINK_JTAG_DYNAMIC;

typedef struct {
    E_HILINK_JTAG_DYNAMIC type;
    uint data;
} T_HILINK_JTAG_WRITEDYN;

typedef struct {
    string csr_check_id;
    uint cycle;
    uint macroid;
} T_HILINK_JTAG_CSR_CHECK_CYCLE_INFO;

typedef map<string, map<string, uint> > M_CSR_REG_INFO;


typedef map<int, T_HILINK_JTAG_WRITEDYN> HILINK_PERSITE_WRITEDYN_EX;

//TODO
#define HILINK_MAX_IRLength_NUM 64
#define HILINK_MAX_DRxLength_NUM 64

class d2s_IP_JTAG : public d2s {
public:

    static int current_JTAG_port_id;
    const static INT HilinkDR2AddrLength;
    const static INT HilinkDR2DataLength;
    const static string CONTEXT_POSTFIX_MAP[2];
    const static string JTAG_MODE_MAP[10];
    static int JTAG_id;

    typedef enum {
        CTX_DEFAULT = 0,
        CTX_FASTDIFF = 1
    } E_CONTEXT_TYPE;
    E_CONTEXT_TYPE context;

    typedef enum {
        JTAG_WR_DR2	=0,
        JTAG_WR_DR1	=1,
        JTAG_WR_DR0	=2,
        JTAG_WR_IR2	=3,
        JTAG_WR_IR1	=4,
        JTAG_WR_IR0	=5,
        JTAG_RD		=6,
        JTAG_WAIT	=7,
        JTAG_WR_DR	=8,
        JTAG_WR_IR	=9
    } E_JTAG_MODE;
    E_JTAG_MODE jtag_mode;
    void write_TMS(const std::string& templatePatternName);
    d2s_IP_JTAG(int id, bool pre_d2s = false);
    d2s_IP_JTAG();
    d2s_IP_JTAG(const std::string& pName);

    void init_val(int id);

    bool is_pre_d2s;

    static map<string, set<int> > synchronized_address; //masked by tony 20210816
    static d2sFrameWorkModeType::Enum exchg_d2smode;
    static bool exchg_ind2sblock;

    //labelname call_id expectvalue_id
    typedef map<string, map<int, string> > M_FLBL_INFO;
    M_FLBL_INFO LabelPassFailMap;

    map<string, map<int, bool> > LabelPassFailResult;
    bool AppendSuiteName;

protected:
#ifdef CREATE_PATTERN_BY_FW
    static int IR_cycles;
    static int DR0_cycles;
    static int DR1_cycles;
    static int DR2_cycles;


    virtual void createMultiWritePattern(vector<long long> address, vector<long long> data, const std::string& labelName){};
    virtual void createWritePattern(long long address, long long data, const std::string& labelName){};
    virtual void createWaitPattern(long long cycle, const std::string& labelName){};
    virtual void createMultiReadExpectPattern(vector<long long> address, const std::string& labelName, long long value = 0LL, long long mask = 0LL){};
    virtual void createReadExpectPattern(long long address, const std::string& labelName, long long value = 0LL, long long mask = 0LL){};
    virtual bool isCreatedByFW(){};
    static map<int, bool> CSR_Check_result;
    M_CSR_REG_INFO CSR_Check_Info;
    vector<T_HILINK_JTAG_CSR_CHECK_CYCLE_INFO> csr_check_cycle_info;
    void display_fail_registers(const string& csr_check_id, uint fail_code);

#endif
    string read_template_postfix;
#ifdef AHB_MODE
    map<string, int> readid_macroid_map;
    void readAndStoreValues(const std::string& id, int offset);
#endif
    bool check_csr;
    int isCSRCheck;
public:
#ifdef AHB_MODE
    virtual void read(long long address, const std::string& id, const string& label = "");
    virtual void read(long long address, const std::string& id, unsigned long long* labelcode);
    virtual void readDynamic(const map<int, long long>& read_param, const std::string& read_id, const std::string& pat_id);
#endif

    int template_selector;
    string Context;
    int macroid;
    void setmacroid(int macroidvar);
    //void getContext();
    void setJtagMode(const string& mode);
    void write_IRxDR0DR1(unsigned long long value);
    int getHighWaveformIndex();
    int getLowWaveformIndex();
    int getHighStrobeWaveformIndex();
    int getLowStrobeWaveformIndex();
    int getMaskStrobeWaveformIndex();
    int getAddressBits();
    int getDataBits();
    int getWriteCycles();

    int getPadding() {
        return 1;
    }
    std::string getWriteTemplatePatternName();
    std::string getWriteTemplateTestName();
    std::string getWritePinName();
    int getWriteAddressVectorNumberLSB();
    int getWriteAddressVectorNumberMSB();
    int getWriteDataVectorNumberLSB();
    int getWriteDataVectorNumberMSB();
    int getWritePatternVectors();
    std::string getReadTemplatePatternName();

    std::string getReadTemplateTestName();
    std::string getReadAddressPinName();
    std::string getReadPinName();

    int getReadPatternVectors();

    int getReadAddressVectorNumberLSB();
    int getReadAddressVectorNumberMSB();
    int getReadDataCycleNumberLSB();
    int getReadDataCycleNumberMSB();
    int getReadDataVectorNumberLSB();
    int getReadDataVectorNumberMSB();

    // xixi
    std::string getExpectAddressPinName();
	std::string getExpectPinName();
	std::string getExpectTemplatePatternName();
	int getExpectPatternVectors();


	int getExpectAddressVectorNumberLSB();
	int getExpectAddressVectorNumberMSB();
	int getExpectDataVectorNumberLSB();
	int getExpectDataVectorNumberMSB();


    void prepareDynamicWriteLabel(long long address, long long data, const std::string& templatePatternName);
    void prepareDynamicReadOrExpectValueLabel(long long address, const std::string& labelName, long long data = 0LL, long long strobeMask = 0LL);

    void expectValue(long long address, long long value, long long mask = 0LL, const string& id = "", const string& label = "");

    virtual void preExec(const std::string& burstName);
    virtual void postExec(const std::string& executedId, bool executionWasSuccessful);
    virtual void enablePassFailCheckForNextExecution();

    std::string getTimingPort() {
        return "timeplate_1";
    }
    double getTimingPeriod();
    string getTimingSetName(){return "timeplate_1_0";};

    bool getExpectValue(const string& id);

    std::string getWaitTemplatePatternName();
    virtual ~d2s_IP_JTAG();
    virtual std::string getInterfaceName();

    static d2s_IP_JTAG& Instance();
    static d2s_IP_JTAG& JTAG_port(int id);
    static void select_JTAG(int id);
    static int get_current_JTAG_port();
    static void switch_JTAG(int id);

    static d2s_IP_JTAG& pre_d2s_Instance();
    static d2s_IP_JTAG& pre_d2s_JTAG_port(int id);

    std::string getWaitTemplateTestName();

    void writeDynamicPerSite_EX(long long address, const HILINK_PERSITE_WRITEDYN_EX& data, const string& id);
    void writeDynamicPerSite(long long address, const map<int, long long>& value, const string& id);
    void prepareDynamicWriteLabel_EX(long long address, const T_HILINK_JTAG_WRITEDYN& data, const std::string& templatePatternName);
#ifdef CREATE_PATTERN_BY_FW
    virtual int getReadCycles(){return 0;};
    void make_capture_pattern(uint addr);
#endif

    virtual void setFrameworkMode(const d2sFrameWorkModeType::Enum mode);
    virtual void setD2sBlockBegin();
    virtual void setD2sBlockEnd();
    bool is_address_synchronized(const string& reg_grp, uint addr);
    void set_address_synchronized_flag(const string& reg_grp, uint addr);
    void pre_d2s_begin();
    void pre_d2s_end(const string& label, bool append_suitename = false, bool overwrite = true);

    void setAppendSuiteName();
    virtual bool needAppendSuiteName();
    bool has_CSR_Check_Passed();
    int isCheck();
    virtual void enableCSRCheckForNextExecution();
    void add_CSR_Reg_Info(const string& csr_check_id, const string& regname, uint reg_mask);
};

#endif /* D2S_IP_JTAG_H_ */
