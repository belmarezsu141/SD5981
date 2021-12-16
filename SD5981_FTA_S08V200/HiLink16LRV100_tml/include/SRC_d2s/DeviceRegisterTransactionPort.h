#ifndef DEVICEREGISTERTRANSACTIONPORT_H_
#define DEVICEREGISTERTRANSACTIONPORT_H_
#include <set>

#include <SRC_d2s/TransactionPort.h>
//#define D2S_NO_DCSCALE
#ifndef D2S_NO_DCSCALE
    #include <SRC_d2s/Event.h>
#endif


typedef struct{
	long long address;
	long long value;
	long long mask;
} T_EXPECT_VALUE_PARAM;
typedef map<int,T_EXPECT_VALUE_PARAM> PerSite_EXPECT_VALUE_PARAM;

class DeviceRegisterTransactionPort : public TransactionPort
{
public:
	DeviceRegisterTransactionPort(const std::string& pName);
	virtual ~DeviceRegisterTransactionPort();
    
    virtual void preExec(const std::string& burstName);
    virtual void postExec(const std::string& executedId, bool executionWasSuccessful);
    virtual void expectValueDynamicPerSite(const PerSite_EXPECT_VALUE_PARAM& expect_param,const std::string& id);
    virtual void readDynamicPerSite(const map<int,long long>& read_param, const std::string& read_id, const std::string& pat_id);
    virtual void writeDynamicPerSite(long long address, const map<int, long long>& data, const std::string& id);
    virtual void read(long long address, const std::string& id,const string& label="");
    virtual void multiread(vector<long long>& address,  const std::string& id,const string& label="");
    virtual void read(long long address, const std::string& id,unsigned long long* labelcode);


    void write(long long address, long long data,const string& label="");
    void multiwrite(vector<long long>& address, vector<long long> data, const string& label="");
    void write(long long address, long long data,unsigned long long* labelcode);
    void writeDynamic(long long address, long long data, const std::string& id);

    /***************used for dynamic write***********/
    vector<long long> getMultiReadValue(const vector<long long>& address ,const std::string& id);
    void getMultiReadValue(vector<long long>& readout,const vector<long long>& address ,const std::string& id);
    long long getReadValue(const std::string& id);
    void getReadValuePerSite(const std::string& id,map<int, long long>& data);
    
    void expectValue(long long address, long long value, long long mask=0LL,const string& label="");
    void expectValue_label_code(long long address, long long value, long long mask,unsigned long long* labelcode);

    void wait(double timeInS);
    void waitCycles(unsigned int cycles);

#ifndef D2S_NO_DCSCALE
    void dcScaleForceVoltage(const std::string& pinList, double voltValue);
    void dcScaleForceVoltageMeasureVoltage(const std::string& pinList, int samples, double voltValue);
    void dcScaleForceVoltageMeasureVoltage(const std::string& pinList, int samples, const double limitLow, const double limitHigh, double voltValue);
    void dcScaleForceVoltageMeasureCurrent(const std::string& pinList, int samples, double voltValue);
    void dcScaleForceVoltageMeasureCurrent(const std::string& pinList, int samples, const double limitLow, const double limitHigh, double voltValue);
    void dcScaleMeasureVoltage(const std::string& pinList, int samples);
    void dcScaleMeasureVoltage(const std::string& pinList, int samples, const double limitLow, const double limitHigh);
    void dcScaleMeasureCurrent(const std::string& pinList, int samples);
    void dcScaleMeasureCurrent(const std::string& pinList, int samples, const double limitLow, const double limitHigh);
    void dcScaleSetMeasureRange(const std::string& pinList, const DC_SCALE::SET_MEAS_RNG setMeasRng, const double minValue, const double maxValue);
#endif    

protected:

    /**
     * @brief getInterfaceName is a pure virtual method. This method defines the name of the device protocol.
     * 
     * This method needs to be implemented in the inherited port specific class. It defines how the labels are named for the framework.
     */ 
    virtual std::string getInterfaceName() = 0;


    virtual void createWritePattern(long long address, long long data, const std::string& labelName);
    virtual void createWaitPattern(long long cycle, const std::string& labelName);
    virtual void createReadExpectPattern(long long address, const std::string& labelName, long long value=0LL, long long mask=0LL);
    virtual bool isCreatedByFW();

    virtual void createMultiWritePattern(vector<long long> address, vector<long long> data, const std::string& labelName);

    virtual void createMultiReadExpectPattern(vector<long long> address, const std::string& labelName, long long value=0LL, long long mask=0LL);


    virtual void prepareDynamicWriteLabel(long long address, long long data, const std::string& labelName);
    
    virtual void prepareDynamicWriteLabel(vector<long long>& address, vector<long long> data, const std::string& labelName);
    /**
     * @brief getWriteTemplatePatternName specifies the label name of your write template label
     */       
    virtual std::string getWriteTemplatePatternName();
    
    virtual std::string getNewWriteLabelName(long long address, long long data); 

    virtual std::string getNewWriteLabelName(vector<long long>& address, vector<long long>& data);

    virtual std::string getNewWriteDynamicLabelName(long long address, long long data, const std::string& id);
    virtual std::string getNewReadLabelName(long long address, const std::string& id);
    virtual std::string getNewReadLabelName(vector<long long>& address,  const std::string& id);

    
    virtual void prepareDynamicReadOrExpectValueLabel(long long address, const std::string& labelName, long long value=0LL, long long mask=0LL);
    virtual void prepareDynamicReadOrExpectValueLabel(vector<long long> address, const std::string& labelName, long long value=0LL, long long mask=0LL);
    /**
     * @brief getReadTemplatePatternName specifies the label name of the read-template
     * 
     */
    virtual std::string getReadTemplatePatternName(); 
    virtual int getReadCycles();
    virtual long long readFromErrorMap(int cycleOffset);


    virtual void prepareDynamicWaitLabel(unsigned int cycles);
    virtual std::string getWaitTemplatePatternName();

    
#ifndef D2S_NO_DCSCALE
    virtual std::string getDCScaleTemplatePatternName();
#endif    
       
    
    virtual int getWriteCycles();
    
    void waitCyclesModeLearning(unsigned int cycles);
    void checkWrite();
    
    std::string getWaitLabelName(unsigned int cycles);
    
    typedef std::map<std::string, int> idOffsetType;
    idOffsetType readOffsets;  
    typedef std::map<std::string, std::map<int, std::map<std::string, long long> > > portSiteIdValueType;
    static portSiteIdValueType readIdValues;
    void evalutateReads();
    virtual void readAndStoreValues(const std::string& id, int offset=0);
    void addReadLabelOffset(const std::string& id, int cycleOffset);
    void multireadModeLearning(vector<long long>& address,  const std::string& id);
    void readModeLearning(long long address, const std::string& id);
    void expectValueModeLearning(long long address, long long value, long long mask);
    void checkReadAndExpectValue();    

#ifndef D2S_NO_DCSCALE        
    void checkDcScale();
    virtual int getDcScaleCycles();
    void dcScaleForceVoltageLearninMode(const std::string& pinList, double voltValue);
    void dcScaleMeasure(const std::string& measureType, const std::string& pinList, int samples, const double limitLow, const double limitHigh, bool ignoreLimit, bool doForceVoltage=false, double voltValue=0.0);
    void dcScaleMeasureLearningMode(const std::string& measureType, const std::string& pinList, int samples, const double limitLow, const double limitHigh, bool ignoreLimit, bool doForceVoltage=false, double voltValue=0.0);
    void dcScaleSetMeasureRangeLearningMode(const std::string& pinList, const DC_SCALE::SET_MEAS_RNG setMeasRng, const double minValue, const double maxValue);
#endif    

#ifndef D2S_NO_DCSCALE    
    unsigned int dcScaleCycles;
#endif    
    bool writeChecked;
    bool readAndExpectValueChecked;
    bool waitChecked;
#ifndef D2S_NO_DCSCALE    
    bool dcScaleChecked;
#endif    

    std::set<std::string> writeDynamicIDs;   
    std::string getLabelNamePrefix();
};

#endif /*DEVICEREGISTERTRANSACTIONPORT_H_*/
