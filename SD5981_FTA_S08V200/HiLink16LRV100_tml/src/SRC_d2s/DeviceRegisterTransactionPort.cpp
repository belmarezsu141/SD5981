#include <SRC_d2s/DeviceRegisterTransactionPort.h>

#include <assert.h>

#include <Common_Func/System_Common_Func.h>
#include <SRC_d2s/PatternManager.h>
#include <UserConfig.h> //TODO

#define MAX_WAIT_CYCLES 16777208 //=(2^24-8) <- max repetition of RPTV

DeviceRegisterTransactionPort::portSiteIdValueType DeviceRegisterTransactionPort::readIdValues; 

DeviceRegisterTransactionPort::DeviceRegisterTransactionPort(const std::string& pName):TransactionPort(pName)
{
    readOffsets.clear();
    writeChecked = false;
    readAndExpectValueChecked = false;
    waitChecked = false;
#ifndef D2S_NO_DCSCALE    
    dcScaleCycles = 0;
    dcScaleChecked = false; 
#endif    
    
    
}

DeviceRegisterTransactionPort::~DeviceRegisterTransactionPort()
{
}

std::string DeviceRegisterTransactionPort::getWriteTemplatePatternName(){
//    cerr << "ERROR in framework: getWriteTemplatePatternName needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return "";    
}

void DeviceRegisterTransactionPort::prepareDynamicWriteLabel(long long address, long long data, const std::string& labelName){
//    cerr << "ERROR in framework: prepareDynamicWriteLabel needs to be overridden! Cannot modify write label." << endl;
    bool notOverridden = false;
    assert(notOverridden);    
}


void DeviceRegisterTransactionPort::prepareDynamicWriteLabel(vector<long long>& address, vector<long long> data, const std::string& labelName){
//    cerr << "ERROR in framework: prepareDynamicWriteLabel needs to be overridden! Cannot modify write label." << endl;
    bool notOverridden = false;
    assert(notOverridden);
}

std::string DeviceRegisterTransactionPort::getReadTemplatePatternName(){
//    cerr << "ERROR in framework: getReadTemplatePatternName needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);    
    return "";
}

void DeviceRegisterTransactionPort::prepareDynamicReadOrExpectValueLabel(long long address, const std::string& labelName, long long value, long long mask){
//    cerr << "ERROR in framework: prepareDynamicReadOrExpectValueLabel needs to be overridden! Cannot modify read/expected-value label." << endl;
    bool notOverridden = false;
    assert(notOverridden);        
}

void DeviceRegisterTransactionPort::prepareDynamicReadOrExpectValueLabel(vector<long long> address, const std::string& labelName, long long value, long long mask){
//    cerr << "ERROR in framework: prepareDynamicReadOrExpectValueLabel needs to be overridden! Cannot modify read/expected-value label." << endl;
    bool notOverridden = false;
    assert(notOverridden);        
}

long long DeviceRegisterTransactionPort::readFromErrorMap(int cycleOffset){
//    cerr << "ERROR in framework: readFromErrorMap needs to be overridden! Cannot read from error map." << endl;
    bool notOverridden = false;
    assert(notOverridden);    
    return 0;
}

std::string DeviceRegisterTransactionPort::getWaitTemplatePatternName(){
//    cerr << "ERROR in framework: getWaitTemplatePatternName needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);    
    return "";        
}

#ifndef D2S_NO_DCSCALE
std::string DeviceRegisterTransactionPort::getDCScaleTemplatePatternName(){
//    cerr << "ERROR in framework: getDCScaleTemplatePatternName needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);    
    return "";         
}
#endif  



void DeviceRegisterTransactionPort::preExec(const std::string& labelName){

    //clearing the read cache only if testsuite name changed
    static string lastTestSuiteName = "";
    string testSuiteName;
   // GET_TESTSUITE_NAME(testSuiteName);
    if(lastTestSuiteName != testSuiteName){
        lastTestSuiteName = testSuiteName;
        //cerr << "new Testsuite " << testSuiteName << " - clearing readIdValues" << endl;
        readIdValues.clear();
    }
    
    TransactionPort::preExec(labelName);
}    
    

void DeviceRegisterTransactionPort::postExec(const std::string& executedId, bool executionWasSuccessful){
    if(executionWasSuccessful) evalutateReads();
    readOffsets.clear();
    writeDynamicIDs.clear();
    
    TransactionPort::postExec(executedId, executionWasSuccessful);
}




void DeviceRegisterTransactionPort::checkWrite(){
    if(!writeChecked){
    	if(!isCreatedByFW()){
			if(getWriteTemplatePatternName() == ""){
//				cerr << "getWriteTemplatePatternName cannot return \"\""<< endl;
				assert(getWriteTemplatePatternName() == "");
			}
			if(!PatternManager::isPatternAvailable(getWriteTemplatePatternName(), "MAIN", portName)){
//				cerr << "specified write template pattern doesn't exist: \"" << getWriteTemplatePatternName() << "\"" << endl;
				assert(!PatternManager::isPatternAvailable(getWriteTemplatePatternName(), "MAIN", portName));
			}
    	}
        writeChecked = true;
    }
}




string DeviceRegisterTransactionPort::getNewWriteLabelName(long long address, long long data){
	ostringstream newLabelName;
	newLabelName << getLabelNamePrefix() << "_W_0x" << hex << address << "_0x" << data;
	return newLabelName.str();
}


string DeviceRegisterTransactionPort::getNewWriteLabelName(vector<long long>& address, vector<long long>& data){
	ostringstream newLabelName,regInfoName;
	string md5_info;
	newLabelName << getLabelNamePrefix() ;
	for(uint i=0;i<address.size() and i<data.size();i++){
		regInfoName << "_W_0x"<< hex << address[i] <<"_0x" << data[i];
	}

	md5_info = get_MD5(regInfoName.str());
	newLabelName << md5_info;
//	cout<<"*****newLabelName: " <<newLabelName.str() <<   "  md5_info:   "<<  md5_info<<endl;

	return newLabelName.str();
}


void
DeviceRegisterTransactionPort::write(long long address, long long data,unsigned long long* labelcode){
	checkWrite();
	if(!inD2sBlock){
//		cerr << "write can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
		assert(inD2sBlock);
	}
	cycleOffset += getWriteCycles();
	call_id++;
	if(currentFrameworkMode == d2sFrameWorkModeType::LearningMode || currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){

		string newLabelName = getNewWriteLabelName(address, data);

		if(!PatternManager::isPatternAvailable(newLabelName)){
			if(!isCreatedByFW()){
				prepareDynamicWriteLabel(address, data, getWriteTemplatePatternName());
				PatternManager::copyLabel(getWriteTemplatePatternName(), newLabelName);
			}
			else{
				createWritePattern(address, data,newLabelName);
			}
		}

		burstLabels.push_back(newLabelName);
	}
	label_md5_tag.append((char*)labelcode,8);
	label_md5_tag.push_back('\n');
}

void DeviceRegisterTransactionPort::write(long long address, long long data,const string& label){
    checkWrite();
    if(!inD2sBlock){
//        cerr << "write can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);
    }
    cycleOffset += getWriteCycles();
    call_id++;
    if(currentFrameworkMode == d2sFrameWorkModeType::LearningMode || currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){

        string newLabelName = getNewWriteLabelName(address, data);

        if(!PatternManager::isPatternAvailable(newLabelName)){
			if(!isCreatedByFW()){
				prepareDynamicWriteLabel(address, data, getWriteTemplatePatternName());
				PatternManager::copyLabel(getWriteTemplatePatternName(), newLabelName);
			}
			else{
				createWritePattern(address, data,newLabelName);
			}
        }

        burstLabels.push_back(newLabelName);
    }
    if(label.empty()){
    	label_md5_tag.append(getNewWriteLabelName(address, data));//* show the add and data
    	label_md5_tag.push_back('\n');
    }
    else{
    	label_md5_tag.append(label);//*show the write reg and value
    	label_md5_tag.push_back('\n');
    }
}








void DeviceRegisterTransactionPort::multiwrite(vector<long long>& address, vector<long long> data, const string& label){
    checkWrite();
    if(!inD2sBlock){
//        cerr << "write can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);
    }
    cycleOffset += getWriteCycles();
    call_id++;
    if(currentFrameworkMode == d2sFrameWorkModeType::LearningMode || currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){

        string newLabelName = getNewWriteLabelName(address, data);

     //   if(!PatternManager::isPatternAvailable(newLabelName)){
			if(!isCreatedByFW()){
				prepareDynamicWriteLabel(address, data, getWriteTemplatePatternName());
				PatternManager::copyLabel(getWriteTemplatePatternName(), newLabelName);
			}
			else{
//				createWritePattern(address, data,newLabelName);
				createMultiWritePattern(address, data,newLabelName);


			}
    //    }

        burstLabels.push_back(newLabelName);
    }
    if(label.empty()){
    	label_md5_tag.append(getNewWriteLabelName(address, data));//* show the add and data
    	label_md5_tag.push_back('\n');
    }
    else{
    	label_md5_tag.append(label);//*show the write reg and value
    	label_md5_tag.push_back('\n');
    }
}






void DeviceRegisterTransactionPort::writeDynamic(long long address, long long data, const std::string& id){
    checkWrite();
    if(!inD2sBlock){
//        cerr << "writeDynamic can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);
    }

    string templateLabelName = getNewWriteDynamicLabelName(address, data, id);
    pair<set<string>::iterator, bool> ret = writeDynamicIDs.insert(id);
    if(ret.second != false){
        //first time for this id; add label to burst (in learning mode)
        cycleOffset += getWriteCycles();
        call_id++;

        if(currentFrameworkMode == d2sFrameWorkModeType::LearningMode || currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){
            //copy template pattern
        	if(!isCreatedByFW()){
				if(!PatternManager::isPatternAvailable(templateLabelName)){
					PatternManager::copyLabel(getWriteTemplatePatternName(), templateLabelName);
				}
        	}
        	else{
        		createWritePattern(address, data,templateLabelName);
        	}
            burstLabels.push_back(templateLabelName);
        }
    }
    else{
//    	cerr<<"Error: Label "<<templateLabelName<<" is already exists!"<<endl;
    //	ERROR_EXIT(TM::ABORT_FLOW);
    }

    prepareDynamicWriteLabel(address, data, templateLabelName);
    label_md5_tag.append(templateLabelName);
    label_md5_tag.push_back('\n');
}
/********* Add for dynamic write for each site **********/
void DeviceRegisterTransactionPort::writeDynamicPerSite(long long address, const map<int, long long>& data, const std::string& id){
    checkWrite();
    if(!inD2sBlock){
//        cerr << "writeDynamic can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);
    }

    long long dummy;
    string templateLabelName = getNewWriteDynamicLabelName(address, dummy, id);
    pair<set<string>::iterator, bool> ret = writeDynamicIDs.insert(id);
    if(ret.second != false){
        //first time for this id; add label to burst (in learning mode)
        cycleOffset += getWriteCycles();
        call_id++;

        if(currentFrameworkMode == d2sFrameWorkModeType::LearningMode || currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){
            //copy template pattern
        	if(!isCreatedByFW()){
				if(!PatternManager::isPatternAvailable(templateLabelName)){
					PatternManager::copyLabel(getWriteTemplatePatternName(), templateLabelName);
				}
        	}
        	else{
        		createWritePattern(address, 0x00,templateLabelName);
        	}
            burstLabels.push_back(templateLabelName);
        }
    }
    else{
//    	cerr<<"Error: Label "<<templateLabelName<<" is already exists!"<<endl;
    //	ERROR_EXIT(TM::ABORT_FLOW);
    }

    map <int, long long>::const_iterator it;

//    FOR_EACH_SITE_BEGIN();
//		int SiteID = CURRENT_SITE_NUMBER() - 1;
//		it = data.find(SiteID);
//		if (it != data.end()) {
//			prepareDynamicWriteLabel(address, it -> second, templateLabelName);
//		} else {
//			cerr<<"Error: map data is not consistency with site number,Please check map parameters!"<<endl;
//		}
//	FOR_EACH_SITE_END();

    label_md5_tag.append(templateLabelName);
    label_md5_tag.push_back('\n');
}

string DeviceRegisterTransactionPort::getNewWriteDynamicLabelName(long long address, long long data,const std::string& id){
    ostringstream templateLabelName;
    templateLabelName << getLabelNamePrefix() << "_DW_" << "_" << id;
    return templateLabelName.str();
}



int DeviceRegisterTransactionPort::getWriteCycles(){
    return PatternManager::getCyclesFromLabel(getWriteTemplatePatternName(), portName);
}



void DeviceRegisterTransactionPort::wait(double timeInS){
    int debug =0;
	double timingPeriod = getTimingPeriod();
    double waitInNs = timeInS * 1e9;

    if(waitInNs < timingPeriod/2) return; //wait time too small; do nothing

//    if(debug) cerr << dec << "wait time is " << waitInNs << " ns" << endl;
//    if(debug) cerr << "period is " << timingPeriod << " ns" << endl;
    
    unsigned int cycles = (int)((waitInNs + timingPeriod/2) / timingPeriod); //+0.5*period to round up to next cycle
//    if(debug) cerr << cycles << " cycles are needed to achieve achieve wait time" << endl;
    
    waitCycles(cycles);
}


void DeviceRegisterTransactionPort::waitCycles(unsigned int cycles){
    if(!waitChecked){
    	if(!isCreatedByFW()){
			if(getWaitTemplatePatternName() == ""){
//				cerr << "getWaitTemplatePatternName cannot return \"\""<< endl;
				assert(getWaitTemplatePatternName() == "");
			}
			if(!PatternManager::isPatternAvailable(getWaitTemplatePatternName(), "MAIN", portName)){
//				cerr << "specified wait template pattern doesn't exist: \"" << getWaitTemplatePatternName() << "\"" << endl;
				assert(!PatternManager::isPatternAvailable(getWaitTemplatePatternName(), "MAIN", portName));
			}
    	}
        waitChecked = true;
    }
    if(!inD2sBlock){
//        cerr << "wait can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);
    }
//    if(cycles%8){
//    	cycles=cycles + 8 - (cycles % 8);
//	}
	cycleOffset += cycles;
	call_id++;
    switch(currentFrameworkMode){
        case d2sFrameWorkModeType::LearningMode:
        case d2sFrameWorkModeType::EngineeringMode:
                waitCyclesModeLearning(cycles);
                break;
        case d2sFrameWorkModeType::ProductionMode:
                //will run the pre-generated label on END_DYN_SETUP
                break;
        default:
//                cerr << "Error! cannot wait: wrong state" << endl;
                break;
   }
   label_md5_tag.append(getWaitLabelName(cycles));
   label_md5_tag.push_back('\n');
}
void DeviceRegisterTransactionPort::waitCyclesModeLearning(unsigned int cycles){
    if(cycles > MAX_WAIT_CYCLES){
//        cerr << "ERROR: " << cycles << " of wait-cycles is too big! Cannot adjust repeat count with the given timing period." << endl;
//        cerr << "ERROR: no WAIT added to burst" << endl;
        return;
    }

    string newLabelName = getWaitLabelName(cycles);
    if(!PatternManager::isPatternAvailable(newLabelName)){
        if(!isCreatedByFW()){
			prepareDynamicWaitLabel(cycles);
			PatternManager::copyLabel(getWaitTemplatePatternName(), newLabelName);
		}
		else{
			createWaitPattern(cycles,newLabelName);
		}
    }
    burstLabels.push_back(newLabelName);
}

string DeviceRegisterTransactionPort::getWaitLabelName(unsigned int cycles){
    ostringstream newLabelName;
    newLabelName << dec << getLabelNamePrefix() << "_Wait_" <<  cycles << "Cycles";
    return newLabelName.str();    
}


void DeviceRegisterTransactionPort::prepareDynamicWaitLabel(unsigned int cycles){ 
    
    //default is to only modify the first sequencer command on label to adjust for wait-time
    int seqNoStart;
    int seqNoStop; 
    string port;   
//    fwout << "SQLB? \"" << getWaitTemplatePatternName() << "\",MAIN,(@@)" << endl;
//    if(fwresult.size() != 1){
//        cerr << "ERROR while figuring out repeat sequencer command" << endl;
//        return;
//    }
//    
//    if(fwresult[0].count() == 6) port = fwresult[0][5];
//    else port = "@";
//    
//    seqNoStart = fwresult[0].getIntParam(2);
//    seqNoStop =  fwresult[0].getIntParam(3);
//                        
//    bool foundRPTV = false;
//    for(int i=seqNoStart; i<seqNoStop; i++){
//        fwout << "SQPG? " << i << ",(" << port << ")" << endl;
//        if(fwresult[0][1] == "RPTV"){
//            //cerr << "adjusting repeat count to " << cycles << endl;
//        	string memory = fwresult[0][4];
//        	int amountOfCyclesInRPTV = fwresult[0].getIntParam(2);
//        	int repeatCount = cycles / amountOfCyclesInRPTV;
//        	if(foundRPTV) cerr << "Error: multiple RPTV-sequencer commands found in " << getWaitTemplatePatternName() << " but only 1 is allowed!" << endl; 
//            fwout << "SQPG " << i << ",RPTV," << amountOfCyclesInRPTV << "," << repeatCount << "," << memory << ",(" << port << ")" << endl;
//            foundRPTV = true;
//        }
//    }
//    if(!foundRPTV){
//        cerr << "ERROR: no SQPG RPTV found in " << getWaitTemplatePatternName() << endl;
//        cerr << "ERROR: couldn't adjust repeat count to achieve wait time" << endl;
//    }
}


void DeviceRegisterTransactionPort::addReadLabelOffset( const std::string& id, int cycleOffset){
	//cout<<"readlabeloffset "<<id<<" = "<<dec<<cycleOffset<<endl;
	readOffsets.insert(pair<string, int>(id, cycleOffset));
}

string DeviceRegisterTransactionPort::getNewReadLabelName(long long address,  const std::string& id){
    ostringstream newLabelName;
    newLabelName << getLabelNamePrefix() << "_R_0x" << hex << address;
    return newLabelName.str();
}

string DeviceRegisterTransactionPort::getNewReadLabelName(vector<long long>& address,  const std::string& id){
    ostringstream newLabelName,readRegsInfo;
    string md5_info;
    newLabelName << getLabelNamePrefix();
    for(uint i=0;i < address.size();i++){
    	readRegsInfo<< "_R_0x" << hex << address[i];
    }
    md5_info = get_MD5(readRegsInfo.str());
    newLabelName << md5_info;

    return newLabelName.str();
}


void DeviceRegisterTransactionPort::multireadModeLearning(vector<long long>& address,  const std::string& id){

	string newLabelName = getNewReadLabelName(address, id);
    if(!PatternManager::isPatternAvailable(newLabelName)){
        if(!isCreatedByFW()){
			prepareDynamicReadOrExpectValueLabel(address,getReadTemplatePatternName());
			PatternManager::copyLabel(getReadTemplatePatternName(), newLabelName);
        }
        else{
//        	createReadExpectPattern(address,newLabelName);
        	createMultiReadExpectPattern(address,newLabelName);
        }
    }
    burstLabels.push_back(newLabelName);
}


void DeviceRegisterTransactionPort::readModeLearning(long long address,  const std::string& id){

	string newLabelName = getNewReadLabelName(address, id);
    if(!PatternManager::isPatternAvailable(newLabelName)){
        if(!isCreatedByFW()){
			prepareDynamicReadOrExpectValueLabel(address,getReadTemplatePatternName());
			PatternManager::copyLabel(getReadTemplatePatternName(), newLabelName);
        }
        else{
        	createReadExpectPattern(address,newLabelName);
        }
    }
    burstLabels.push_back(newLabelName);
}

void DeviceRegisterTransactionPort::checkReadAndExpectValue(){
    if(!readAndExpectValueChecked){
    	if(!isCreatedByFW()){
			if(getReadTemplatePatternName() == ""){
//				cerr << "getReadTemplatePatternName cannot return \"\""<< endl;
				assert(getReadTemplatePatternName() == "");
			}
			if(!PatternManager::isPatternAvailable(getReadTemplatePatternName(), "MAIN", portName)){
//				cerr << "specified read template pattern doesn't exist: \"" << getReadTemplatePatternName() << "\"" << endl;
				assert(!PatternManager::isPatternAvailable(getReadTemplatePatternName(), "MAIN", portName));
			}
    	}
        readAndExpectValueChecked = true;
    }
}

void DeviceRegisterTransactionPort::read(long long address, const std::string& id,unsigned long long* labelcode){
	 checkReadAndExpectValue();

	if(!inD2sBlock){
//		cerr << "read can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
		assert(inD2sBlock);
	}
	if(checkPassFail){
//		cerr << "Error: check pass/fail cannot be combined with \"read\" within 1 d2s_LABEL_BEGIN/END-block. Reading is done using the error map and so the port is supposed to fail!" << endl;
//		cerr << "Please either switch off pass/fail check, convert the read to expectValue or split into two d2s_LABEL_BEGIN/END-blocks." << endl;
	}

	//TODO: Check id has no repeat
	std::map<std::string, int>::const_iterator iter(readOffsets.find(id));
	if(iter != readOffsets.end()){
//		cerr << "ERROR: port \"" << portName << "\" read of ID \"" << id << "\" failed. This ID has been defined before!" << endl;
	//	ERROR_EXIT(TM::ABORT_FLOW);
	}
	addReadLabelOffset(id, cycleOffset);

	cycleOffset += getReadCycles();
	call_id++;



	switch(currentFrameworkMode){
		case d2sFrameWorkModeType::LearningMode:
		case d2sFrameWorkModeType::EngineeringMode:
				readModeLearning(address, id);
				break;
		case d2sFrameWorkModeType::ProductionMode:
				//will run the pre-generated label on END_DYN_SETUP
				break;
		default:
//				cerr << "Error! cannot read: wrong state" << endl;
				break;
	}
	label_md5_tag.append((char*)labelcode,8);
	label_md5_tag.push_back('\n');
}


void DeviceRegisterTransactionPort::multiread(vector<long long>& address,  const std::string& id,const string& label){
	checkReadAndExpectValue();
	if(!inD2sBlock){
//		cerr << "read can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
		assert(inD2sBlock);
	}
	if(checkPassFail){
//		cerr << "Error: check pass/fail cannot be combined with \"read\" within 1 d2s_LABEL_BEGIN/END-block. Reading is done using the error map and so the port is supposed to fail!" << endl;
//		cerr << "Please either switch off pass/fail check, convert the read to expectValue or split into two d2s_LABEL_BEGIN/END-blocks." << endl;
	}

	std::map<std::string,int>::const_iterator iter(readOffsets.find(id));
	if(iter != readOffsets.end()){
//		cerr << "ERROR: port \"" << portName << "\" read of ID \"" << id << "\" failed. This ID has been defined before!" << endl;
	//	ERROR_EXIT(TM::ABORT_FLOW);
	}

	for(uint i = 0;i < address.size();i++){
		ostringstream str;
		str<<id<<"_"<<i;
		addReadLabelOffset(str.str(),cycleOffset);
		cycleOffset += getReadCycles();
		call_id++;
	}

	switch(currentFrameworkMode){
		case d2sFrameWorkModeType::LearningMode:
		case d2sFrameWorkModeType::EngineeringMode:
			multireadModeLearning(address, id);
			break;
		case d2sFrameWorkModeType::ProductionMode:
			//will run the pre-generated label on END_DYN_SETUP
			break;
		default:
//			cerr << "Error! cannot read: wrong state" << endl;
			break;
	}
	if(label.empty()){
		label_md5_tag.append(getNewReadLabelName(address, id));
		label_md5_tag.push_back('\n');
	}
	else{
		label_md5_tag.append(label);
		label_md5_tag.push_back('\n');
	}
}



void DeviceRegisterTransactionPort::read(long long address,  const std::string& id,const string& label){
    checkReadAndExpectValue();

    if(!inD2sBlock){
//        cerr << "read can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);    
    }     
    if(checkPassFail){
//        cerr << "Error: check pass/fail cannot be combined with \"read\" within 1 d2s_LABEL_BEGIN/END-block. Reading is done using the error map and so the port is supposed to fail!" << endl;
//        cerr << "Please either switch off pass/fail check, convert the read to expectValue or split into two d2s_LABEL_BEGIN/END-blocks." << endl;            
    }

//    cout << "read offset" << id << " " << cycleOffset << endl;

	//TODO: Check id has no repeat
	std::map<std::string, int>::const_iterator iter(readOffsets.find(id));
	if(iter != readOffsets.end()){
//		cerr << "ERROR: port \"" << portName << "\" read of ID \"" << id << "\" failed. This ID has been defined before!" << endl;
	//	ERROR_EXIT(TM::ABORT_FLOW);
	}
    addReadLabelOffset(id, cycleOffset);

    //Debug cycle do not mactch
//    cout<<"***************Debug cycle do not mactch-start  :: read*********************"<<endl;
//    cout<<"current cycleOffset:"<<dec<<cycleOffset<<endl;
//    cout<<"current getReadCycles:"<<dec<<getReadCycles()<<endl;
//    cout<<"final cycleOffset:"<<dec<<cycleOffset<<endl;
//    cout<<"***************Debug cycle do not mactch-end  :: read**********************"<<endl;
    //Debug cycle do not mactch


    cycleOffset += getReadCycles();
    call_id++;



    switch(currentFrameworkMode){
        case d2sFrameWorkModeType::LearningMode:
        case d2sFrameWorkModeType::EngineeringMode:
                readModeLearning(address, id);
                break;
        case d2sFrameWorkModeType::ProductionMode:
                //will run the pre-generated label on END_DYN_SETUP
                break;
        default:
//                cerr << "Error! cannot read: wrong state" << endl;
                break;             
    }
    if(label.empty()){
    	label_md5_tag.append(getNewReadLabelName(address, id));
    	label_md5_tag.push_back('\n');
    }
    else{
    	label_md5_tag.append(label);
    	label_md5_tag.push_back('\n');
    }
}

int DeviceRegisterTransactionPort::getReadCycles(){
    return PatternManager::getCyclesFromLabel(getReadTemplatePatternName(), portName);
}

void DeviceRegisterTransactionPort::evalutateReads(){

	/*by WeiMin*/


    int site ;//= CURRENT_SITE_NUMBER();
    readIdValues[portName][site].clear();
    /*end of WeiMin*/

    idOffsetType::const_iterator readIDs = readOffsets.begin();
    if(readIDs != readOffsets.end()){
        //something to read
        string prevSite;
      //  fwout << "PQFC?" << endl;  
     //   prevSite = fwresult[0][0];
        for( ; readIDs != readOffsets.end(); readIDs++){
            //get and store value of all sites
            readAndStoreValues(readIDs->first, readIDs->second);
        }    
     //   fwout << "PQFC " << prevSite << endl;
    }    

}

void DeviceRegisterTransactionPort::readAndStoreValues( const std::string& id, int offset){
    //cerr << "reading " << id << "@" << offset << endl;
//    FOR_EACH_SITE_BEGIN_WITH_QUERY();
//        int site = CURRENT_SITE_NUMBER();
//        //fwout << "PQFC " << site << endl;
//        long long readValue = readFromErrorMap(offset);
//        pair<map<string, long long>::iterator,bool> ret = readIdValues[portName][site].insert(pair<string, long long> (id, readValue));
//        if(ret.second == false){
//           // cout << "WARNING: ID \"" << id << "\" already used. Please use unique IDs. ID \"" << id << "\" for site " << site << " will be overwritten." << endl;
//            readIdValues[portName][site].erase(id);
//            readIdValues[portName][site].insert(pair<string, long long> (id, readValue));    
//        }
//    FOR_EACH_SITE_END();
}

void
DeviceRegisterTransactionPort::getReadValuePerSite(const std::string& id,map<int, long long>& data){
	data.clear();
//	FOR_EACH_SITE_BEGIN();
//		uint SiteID=CURRENT_SITE_NUMBER()-1;
//		data[SiteID]=getReadValue(id);
//	FOR_EACH_SITE_END();
}

vector<long long>
DeviceRegisterTransactionPort::getMultiReadValue(const vector<long long>& address ,const std::string& id){
	vector<long long> dummy;
	dummy.assign(address.size(),0);
	return dummy;
}

void
DeviceRegisterTransactionPort::getMultiReadValue(vector<long long>& readout,const vector<long long>& address ,const std::string& id){
	int site; //= CURRENT_SITE_NUMBER();
	readout.clear();
	for(uint i=0;i<address.size();i++){
		ostringstream str;
		str<<id<<"_"<<i;
		std::map<std::string, long long>::const_iterator iter(readIdValues[portName][site].find(str.str()));
	    if(iter != readIdValues[portName][site].end()){
	    	readout.push_back(iter->second);
	    }
	    else{
//	        cerr << "ERROR: port \"" << portName << "\" getReadValue of ID \"" << id << "\" failed. ID is not available." << endl;
	//        ERROR_EXIT(TM::ABORT_FLOW);//TODO
	//        return 0xdeadbeaf;
	    }
	}
}

long long DeviceRegisterTransactionPort::getReadValue(const std::string& id){

    int site;// = CURRENT_SITE_NUMBER();
    std::map<std::string, long long>::const_iterator iter(readIdValues[portName][site].find(id));





    if(iter != readIdValues[portName][site].end()) return iter->second;
    else{
//        cerr << "ERROR: port \"" << portName << "\" getReadValue of ID \"" << id << "\" failed. ID is not available." << endl;
  //      ERROR_EXIT(TM::ABORT_FLOW);//TODO
        return 0xdeadbeaf;
    }


}

void DeviceRegisterTransactionPort::expectValueModeLearning(long long address, long long value, long long mask){
    ostringstream newLabelName;
    newLabelName << getLabelNamePrefix() << "_EV_0x" << hex << address << "_0x" << value << "_0x" << mask;

    if(!PatternManager::isPatternAvailable(newLabelName.str())){
    	if(!isCreatedByFW()){
    		prepareDynamicReadOrExpectValueLabel(address, getReadTemplatePatternName(), value, mask);
    		PatternManager::copyLabel(getReadTemplatePatternName(), newLabelName.str());
    	}
    	else{
    		createReadExpectPattern(address,newLabelName.str(),value,mask);
    	}
    }

    burstLabels.push_back(newLabelName.str());
}


void DeviceRegisterTransactionPort::expectValue_label_code(long long address, long long value, long long mask,unsigned long long* labelcode){
	checkReadAndExpectValue();
	if(!inD2sBlock){
//		cerr << "expectValue can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
		assert(inD2sBlock);
	}
	switch(currentFrameworkMode){
		case d2sFrameWorkModeType::LearningMode:
		case d2sFrameWorkModeType::EngineeringMode:

				cycleOffset += getReadCycles();
				call_id++;
				expectValueModeLearning(address, value, mask);//* here generate label name by d2s, we can not change
				break;
		case d2sFrameWorkModeType::ProductionMode:
				cycleOffset += getReadCycles();
				call_id++;
				//will run the pre-generated label later
				break;
		default:
//				cerr << "Error! cannot expect value: wrong state" << endl;
				break;
	}
	if(labelcode != NULL){
		label_md5_tag.append((char*)labelcode,8);
		label_md5_tag.push_back('\n');
	}
	else{
    	ostringstream newLabelName;
    	newLabelName << getLabelNamePrefix() << "_EV_0x" << hex << address << "_0x" << value << "_0x" << mask;
    	label_md5_tag.append(newLabelName.str());
    	label_md5_tag.push_back('\n');
	}
}


void
DeviceRegisterTransactionPort::expectValueDynamicPerSite(const PerSite_EXPECT_VALUE_PARAM& expect_param,const std::string& id){
	checkReadAndExpectValue();
	if(!inD2sBlock){
//		cerr << "expectValue can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
		assert(inD2sBlock);
	}
	ostringstream str;
	str << getLabelNamePrefix() << "_DW__EV_" << id;
	string newLabelName=str.str();
	pair<set<string>::iterator, bool> ret = writeDynamicIDs.insert("EV_"+id);
	if(ret.second != false){
		//first time for this id; add label to burst (in learning mode)
		cycleOffset += getReadCycles();
		call_id++;

		if(currentFrameworkMode == d2sFrameWorkModeType::LearningMode || currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){
			//copy template pattern
//			if(!PatternManager::isPatternAvailable(newLabelName)){
//				PatternManager::copyLabel(getReadTemplatePatternName(), newLabelName);
//			}
			if(!isCreatedByFW()){
				if(!PatternManager::isPatternAvailable(newLabelName)){
					PatternManager::copyLabel(getReadTemplatePatternName(), newLabelName);
				}
			}
			else{
				createReadExpectPattern(0LL,newLabelName,0LL,0LL);
			}
			burstLabels.push_back(newLabelName);
		}
	}
	else{
//		cerr<<"Error: Label "<<newLabelName<<" is already exists!"<<endl;
	//	ERROR_EXIT(TM::ABORT_FLOW);
	}

//	FOR_EACH_SITE_BEGIN();
//		if(expect_param.find(CURRENT_SITE_NUMBER()-1)==expect_param.end()){
//			cerr<<"Error: no parameter for site "<<CURRENT_SITE_NUMBER()<<endl;
//		//	ERROR_EXIT(TM::ABORT_FLOW);
//		}
//		const T_EXPECT_VALUE_PARAM& param=expect_param.find(CURRENT_SITE_NUMBER()-1)->second;
//		prepareDynamicReadOrExpectValueLabel(param.address, newLabelName, param.value, param.mask);
//	FOR_EACH_SITE_END();
	label_md5_tag.append(newLabelName);
	label_md5_tag.push_back('\n');
}

void
DeviceRegisterTransactionPort::readDynamicPerSite(const map<int,long long>& read_param, const std::string& read_id, const std::string& pat_id){
	checkReadAndExpectValue();
	if(!inD2sBlock){
//		cerr << "expectValue can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
		assert(inD2sBlock);
	}
	ostringstream str;
	str << getLabelNamePrefix() << "_DW__RD_" << pat_id;
	string newLabelName=str.str();
	pair<set<string>::iterator, bool> ret = writeDynamicIDs.insert("RD_"+pat_id);
	if(ret.second != false){
		std::map<std::string, int>::const_iterator iter(readOffsets.find(read_id));
		if(iter != readOffsets.end()){
//			cerr << "ERROR: port \"" << portName << "\" read of ID \"" << read_id << "\" failed. This ID has been defined before!" << endl;
		//	ERROR_EXIT(TM::ABORT_FLOW);
		}
		addReadLabelOffset(read_id, cycleOffset);

		cycleOffset += getReadCycles();
		call_id++;

		if(currentFrameworkMode == d2sFrameWorkModeType::LearningMode || currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){
			//copy template pattern
//			if(!PatternManager::isPatternAvailable(newLabelName)){
//				PatternManager::copyLabel(getReadTemplatePatternName(), newLabelName);
//			}
			if(!isCreatedByFW()){
				if(!PatternManager::isPatternAvailable(newLabelName)){
					PatternManager::copyLabel(getReadTemplatePatternName(), newLabelName);
				}
			}
			else{
				createReadExpectPattern(0LL,newLabelName,0LL,0LL);
			}
			burstLabels.push_back(newLabelName);
		}
	}
	else{
//		cerr<<"Error: Label "<<newLabelName<<" is already exists!"<<endl;
	//	ERROR_EXIT(TM::ABORT_FLOW);
	}

//	FOR_EACH_SITE_BEGIN();
//		if(read_param.find(CURRENT_SITE_NUMBER()-1)==read_param.end()){
//			cerr<<"Error: no parameter for site "<<CURRENT_SITE_NUMBER()<<endl;
//	//		ERROR_EXIT(TM::ABORT_FLOW);
//		}
//		long long address=read_param.find(CURRENT_SITE_NUMBER()-1)->second;
//		prepareDynamicReadOrExpectValueLabel(address, newLabelName, 0LL, 0LL);
//	FOR_EACH_SITE_END();
	label_md5_tag.append(newLabelName);
	label_md5_tag.push_back('\n');
}


void DeviceRegisterTransactionPort::expectValue(long long address, long long value, long long mask,const string& label){
    checkReadAndExpectValue();
    if(!inD2sBlock){
//        cerr << "expectValue can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);    
    }   
//    if(!checkPassFail){
//        cerr << "Warning: expectValue only makes sense when pass/fail check for this port is switched on. Please enable pass/fail check using \"enablePassFailCheckForNextExecution()\"" << endl;
//    }
    switch(currentFrameworkMode){
        case d2sFrameWorkModeType::LearningMode:
        case d2sFrameWorkModeType::EngineeringMode:

        	//debug cycle does not match -statr
//        	cout<<"***********debug cycle does not match -statr : expectValue"<<endl;
//        	cout<<"current cycleOffset:"<<dec<<cycleOffset<<endl;
//        	cout<<"current getReadCycles:"<<dec<<getReadCycles()<<endl;
//
//        	cout<<"***********debug cycle does not match -end : expectValue"<<endl;
        	//debug cycle does not match -end

                cycleOffset += getReadCycles();
                call_id++;
                expectValueModeLearning(address, value, mask);//* here generate label name by d2s, we can not change
                break;
        case d2sFrameWorkModeType::ProductionMode:
                cycleOffset += getReadCycles();
                call_id++;
                //will run the pre-generated label later
                break;
        default:
//                cerr << "Error! cannot expect value: wrong state" << endl;
                break;                      
    }
    if(label.empty()){
    	ostringstream newLabelName;
    	newLabelName << getLabelNamePrefix() << "_EV_0x" << hex << address << "_0x" << value << "_0x" << mask;
    	label_md5_tag.append(newLabelName.str());
    	label_md5_tag.push_back('\n');
    }
    else{//* label is used to define Burst name and to generate md5
    	label_md5_tag.append(label);
    	label_md5_tag.push_back('\n');
    }
}

std::string DeviceRegisterTransactionPort::getLabelNamePrefix(){
    ostringstream prefix;
    
    if(portName == "@") prefix << "d2s_" << getInterfaceName() << "_AT";
    else prefix << "d2s_" << getInterfaceName() << "_" << portName;
    
    return prefix.str();    
}



#ifndef D2S_NO_DCSCALE

int DeviceRegisterTransactionPort::getDcScaleCycles(){
    if(dcScaleCycles == 0) dcScaleCycles = PatternManager::getCyclesFromLabel(getDCScaleTemplatePatternName(), portName);
    return dcScaleCycles;
}

void DeviceRegisterTransactionPort::checkDcScale(){
    if(!dcScaleChecked){
        if(getDCScaleTemplatePatternName() == ""){
//            cerr << "ERROR: getDCScaleTemplatePatternName cannot return \"\""<< endl;
            assert(getDCScaleTemplatePatternName() != "");
        }
        if(!PatternManager::isPatternAvailable(getDCScaleTemplatePatternName(), "MAIN", portName)){
//            cerr << "ERROR: specified read template pattern doesn't exist: \"" << getDCScaleTemplatePatternName() << "\"" << endl;
            assert(PatternManager::isPatternAvailable(getDCScaleTemplatePatternName(), "MAIN", portName));  
        }
        if(getDcScaleCycles() < 32){
//            cerr << "ERROR: " << getDCScaleTemplatePatternName() << " has to generate at least 32 cycles (using 1 GENV-instruction)!" << endl;
            assert(getDcScaleCycles() >= 32);
        }
        int seqNoStart;
        int seqNoStop; 
        string port;   
//        fwout << "SQLB? \"" << getDCScaleTemplatePatternName() << "\",MAIN,(@@)" << endl;
//        if(fwresult.size() != 1){
//            cerr << "ERROR: while checking dcScale pattern. Found multiple patterns." << endl;
//            assert(fwresult.size() == 1);
//        }
//        if(fwresult[0][1] != "MAIN"){
//            cerr << "ERROR: while checking dcScale pattern. It has to be a \"MAIN\"-pattern." << endl;
//            assert(fwresult[0][1] == "MAIN");            
//        }
//        if(fwresult[0].count() == 6) port = fwresult[0][5];
//        else port = "@";
//        
//        seqNoStart = fwresult[0].getIntParam(2);
//        seqNoStop =  fwresult[0].getIntParam(3);
//        
//        fwout << "SQPG? " << seqNoStop-1 << ",(" << port << ")" << endl;
//        if(fwresult[0][1] != "GENV"){
//        	cerr << "ERROR: last sequencer command of template pattern " << getDCScaleTemplatePatternName() << " has to be a \"GENV\"" << endl;
//        	assert(fwresult[0][1] == "GENV"); 
//        }
//        int genvVectorAmount = fwresult[0].getIntParam(2); 
//        if(genvVectorAmount < 32){
//        	cerr << "ERROR: \"GENV\" sequencer command of template pattern " << getDCScaleTemplatePatternName() << " has to generate at least 32 vectors" << endl;
//        	assert(genvVectorAmount >=32);
//        }
//        if(genvVectorAmount != getDcScaleCycles()){
//        	cerr << "ERROR: template pattern " << getDCScaleTemplatePatternName() << " has to consist of a single \"GENV\" command" << endl;
//        	assert(genvVectorAmount == getDcScaleCycles());
//        }

        /*	
        bool lastFoundIsGENV = false;
        for(int i=seqNoStart; i<seqNoStop; i++){
            fwout << "SQPG? " << i << ",(" << port << ")" << endl;
            if(fwresult[0][1] == "GENV" && fwresult[0].getIntParam(2) >= 32){
            	lastFoundIsGENV = true;
            }
        }
        if(!foundGENV){
//            cerr << "ERROR: " << getDCScaleTemplatePatternName() << " should only exist of 1 GENV-command creatig 32 vectors" << endl;
            assert(!foundGENV);
        }*/        
        dcScaleChecked = true;
    }
}

void DeviceRegisterTransactionPort::dcScaleForceVoltageLearninMode(const std::string& pinList, double voltValue){
    //creating measurement pattern
    std::ostringstream newLabelName;
    newLabelName << getLabelNamePrefix() << "_Frc_" << voltValue << "V_on_" << pinList;
    //TODO check that new label name is not >128char
    
    if(!PatternManager::isPatternAvailable(newLabelName.str())){
        PatternManager::copyLabel(getDCScaleTemplatePatternName(), newLabelName.str());
    }
    
    //adding DC measurement definiton
    std::ostringstream id;
    id << "FRC_" << voltValue << "V";
    DC_SCALE::EVENT ev0(id.str(),"dcset"); 
    ev0.addFrcVolt(voltValue); 
    DC_SCALE::TEST_POINTS tp; 
    tp.addPoint(31, ev0); 
    DC_SCALE::DYN_SETUP dynSetup(newLabelName.str(),"MAIN","REPLACE",pinList,tp); 
    dynSetup.download();
    burstLabels.push_back(newLabelName.str());    
}


void DeviceRegisterTransactionPort::dcScaleForceVoltage(const std::string& pinList, double voltValue){
    checkDcScale();
    if(!inD2sBlock){
//        cerr << "dcScaleForceVoltage can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);    
    } 
    
    cycleOffset += getDcScaleCycles();
    call_id++;
    switch(currentFrameworkMode){
            case d2sFrameWorkModeType::LearningMode:
            case d2sFrameWorkModeType::EngineeringMode:
                    dcScaleForceVoltageLearninMode(pinList, voltValue);
                    break;
            case d2sFrameWorkModeType::ProductionMode:
                    //will run the label later
                    break;
            default:
//                cerr << "Error! cannot dcScaleForceVoltage: wrong state" << endl;
                break;                     
    }
    std::ostringstream newLabelName;
    newLabelName << getLabelNamePrefix() << "_Frc_" << voltValue << "V_on_" << pinList;
    label_md5_tag.append(newLabelName.str());
    label_md5_tag.push_back('\n');
}

void DeviceRegisterTransactionPort::dcScaleMeasureLearningMode( const std::string& measureType, const std::string& pinList, int samples, const double limitLow, const double limitHigh, bool ignoreLimit, bool doForceVoltage, double voltValue){
    //creating measurement pattern
    std::ostringstream newLabelName;
    newLabelName << getLabelNamePrefix();
    if(doForceVoltage){
        newLabelName << "_FrcVMeas";
    }
    else{
        newLabelName << "_Meas";    
    }
    newLabelName << measureType << "_" << samples << "avg";
    if(!ignoreLimit){
    	newLabelName << "_ll" << limitLow << "_hl" << limitHigh;
    }
    if(doForceVoltage){
        newLabelName << "_" << voltValue << "V";
    }    
    newLabelName << "_on_" << pinList;
    //TODO check that new label name is not >128char

    if(!PatternManager::isPatternAvailable(newLabelName.str())){
        PatternManager::copyLabel(getDCScaleTemplatePatternName(), newLabelName.str());
    }
    
    //adding measurement definiton
    std::ostringstream id;
    if(doForceVoltage){
        id << "FrcVMeas" << measureType;
    }
    else{
        id << "Meas" << measureType;
    }
    
    DC_SCALE::EVENT ev0(id.str(),"dcset");
    if(doForceVoltage){
        ev0.addFrcVolt(voltValue);    
    } 
    if(measureType == "C"){
    	//measure current
        if(ignoreLimit){
    		ev0.addMeasCurr(samples);
    	}
    	else{
    		ev0.addMeasCurr(limitLow, limitHigh, samples);
    	}
    }
    else{
        //measure voltage
    	if(ignoreLimit){
    		ev0.addMeasVolt(samples);
    	}
    	else{
    		ev0.addMeasVolt(limitLow, limitHigh, samples);
    	}    	
    }
    
    DC_SCALE::TEST_POINTS tp; 
    tp.addPoint(31, ev0); 
    DC_SCALE::DYN_SETUP dynSetup(newLabelName.str(),"MAIN","REPLACE",pinList,tp); 
    dynSetup.download();
    burstLabels.push_back(newLabelName.str());
}

void DeviceRegisterTransactionPort::dcScaleMeasure( const std::string& measureType, const std::string& pinList, int samples, const double limitLow, const double limitHigh, bool ignoreLimit, bool doForceVoltage, double voltValue) {
	checkDcScale();
    if(!inD2sBlock){
//        cerr << "dcScaleMeasure can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);    
    }

	cycleOffset += getDcScaleCycles();
	call_id++;
	switch (currentFrameworkMode) {
	case d2sFrameWorkModeType::LearningMode:
	case d2sFrameWorkModeType::EngineeringMode:
		dcScaleMeasureLearningMode(measureType, pinList, samples, limitLow, limitHigh, ignoreLimit, doForceVoltage, voltValue);
		break;
	case d2sFrameWorkModeType::ProductionMode:
		//will run the label later
		break;
	default:
//		cerr << "Error! cannot dcScaleMeasure: wrong state" << endl;
		break;
	}

    std::ostringstream newLabelName;
    newLabelName << getLabelNamePrefix();
    if(doForceVoltage){
        newLabelName << "_FrcVMeas";
    }
    else{
        newLabelName << "_Meas";
    }
    newLabelName << measureType << "_" << samples << "avg";
    if(!ignoreLimit){
    	newLabelName << "_ll" << limitLow << "_hl" << limitHigh;
    }
    if(doForceVoltage){
        newLabelName << "_" << voltValue << "V";
    }
    newLabelName << "_on_" << pinList;
    //TODO check that new label name is not >128char
    label_md5_tag.append(newLabelName.str());
    label_md5_tag.push_back('\n');

}
    
void DeviceRegisterTransactionPort::dcScaleMeasureVoltage(const std::string& pinList, int samples){
	dcScaleMeasure("V", pinList, samples, 0, 0, true);
}

void DeviceRegisterTransactionPort::dcScaleMeasureVoltage(const std::string& pinList, int samples, const double limitLow, const double limitHigh){
	dcScaleMeasure("V", pinList, samples, limitLow, limitHigh, false);
}

void DeviceRegisterTransactionPort::dcScaleMeasureCurrent(const std::string& pinList, int samples){
	dcScaleMeasure("C", pinList, samples, 0, 0, true);
}

void DeviceRegisterTransactionPort::dcScaleMeasureCurrent(const std::string& pinList, int samples, const double limitLow, const double limitHigh){
	dcScaleMeasure("C", pinList, samples, limitLow, limitHigh, false);
}

void DeviceRegisterTransactionPort::dcScaleForceVoltageMeasureVoltage(const std::string& pinList, int samples, double forceVoltageValue){
    dcScaleMeasure("V", pinList, samples, 0, 0, true, true, forceVoltageValue);
}

void DeviceRegisterTransactionPort::dcScaleForceVoltageMeasureVoltage(const std::string& pinList, int samples, const double limitLow, const double limitHigh, double forceVoltageValue){
    dcScaleMeasure("V", pinList, samples, limitLow, limitHigh, false, true, forceVoltageValue);
}

void DeviceRegisterTransactionPort::dcScaleForceVoltageMeasureCurrent(const std::string& pinList, int samples, double forceVoltageValue){
    dcScaleMeasure("C", pinList, samples, 0, 0, true, true, forceVoltageValue);
}

void DeviceRegisterTransactionPort::dcScaleForceVoltageMeasureCurrent(const std::string& pinList, int samples, const double limitLow, const double limitHigh, double forceVoltageValue){
    dcScaleMeasure("C", pinList, samples, limitLow, limitHigh, false, true, forceVoltageValue);
}


void DeviceRegisterTransactionPort::dcScaleSetMeasureRangeLearningMode(const std::string& pinList, const DC_SCALE::SET_MEAS_RNG setMeasRng, const double minValue, const double maxValue){
    //creating measurement pattern
    std::ostringstream newLabelName;
    newLabelName << getLabelNamePrefix() << "_Rng";
    switch(setMeasRng){
    	case DC_SCALE::CURR_RNG:
    		newLabelName << "C";
    		break;
    	case DC_SCALE::VOLT_RNG:
    		newLabelName << "V";
    		break;
    	default:
//    		cerr << "dcScaleSetMeasureRangeLearningMode(): range " << setMeasRng << " not supported!" << endl;
    		break;
    }
    		
    newLabelName << "_ll" << minValue << "_hl" << maxValue;
    newLabelName << "_on_" << pinList;
    //TODO check that new label name is not >128char
    
    if(!PatternManager::isPatternAvailable(newLabelName.str())){
        PatternManager::copyLabel(getDCScaleTemplatePatternName(), newLabelName.str());
    }
    
    //adding measurement definiton
    std::ostringstream id;
    id << "Rng";
    DC_SCALE::EVENT ev0(id.str(),"dcset"); 
    ev0.addSetRng(setMeasRng, minValue, maxValue);
    DC_SCALE::TEST_POINTS tp;
    tp.addPoint(31, ev0); 
    DC_SCALE::DYN_SETUP dynSetup(newLabelName.str(),"MAIN","REPLACE",pinList,tp); 
    dynSetup.download();
    burstLabels.push_back(newLabelName.str());
}


void DeviceRegisterTransactionPort::dcScaleSetMeasureRange(const std::string& pinList, const DC_SCALE::SET_MEAS_RNG setMeasRng, const double minValue, const double maxValue){
	checkDcScale();
    if(!inD2sBlock){
//        cerr << "dcScaleSetMeasureRange can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);    
    }

	cycleOffset += getDcScaleCycles();
	call_id++;
	switch (currentFrameworkMode) {
	case d2sFrameWorkModeType::LearningMode:
	case d2sFrameWorkModeType::EngineeringMode:
		dcScaleSetMeasureRangeLearningMode(pinList, setMeasRng, minValue, maxValue);
		break;
	case d2sFrameWorkModeType::ProductionMode:
		//will run the label later
		break;
	default:
//		cerr << "Error! cannot dcScaleMeasure: wrong state" << endl;
		break;
	}	
	std::ostringstream newLabelName;
	newLabelName << getLabelNamePrefix() << "_Rng";
	switch(setMeasRng){
		case DC_SCALE::CURR_RNG:
			newLabelName << "C";
			break;
		case DC_SCALE::VOLT_RNG:
			newLabelName << "V";
			break;
		default:
//			cerr << "dcScaleSetMeasureRangeLearningMode(): range " << setMeasRng << " not supported!" << endl;
			break;
	}

	newLabelName << "_ll" << minValue << "_hl" << maxValue;
	newLabelName << "_on_" << pinList;
	//TODO check that new label name is not >128char
	label_md5_tag.append(newLabelName.str());
	label_md5_tag.push_back('\n');
}
#endif


void
DeviceRegisterTransactionPort::createWritePattern(long long address, long long data, const std::string& labelName){
//	cerr << "ERROR in framework: createWritePattern needs to be overridden!" << endl;
	bool notOverridden = false;
	assert(notOverridden);
}

void
DeviceRegisterTransactionPort::createWaitPattern(long long cycle, const std::string& labelName){
//	cerr << "ERROR in framework: createWaitPattern needs to be overridden!" << endl;
	bool notOverridden = false;
	assert(notOverridden);
}

void
DeviceRegisterTransactionPort::createReadExpectPattern(long long address, const std::string& labelName, long long value, long long mask){
//	cerr << "ERROR in framework: createReadExpectPattern needs to be overridden!" << endl;
	bool notOverridden = false;
	assert(notOverridden);
}

bool
DeviceRegisterTransactionPort::isCreatedByFW(){
	return false;
}

void
DeviceRegisterTransactionPort::createMultiWritePattern(vector<long long> address, vector<long long> data, const std::string& labelName){
//	cerr << "ERROR in framework: createWritePattern needs to be overridden!" << endl;
	bool notOverridden = false;
	assert(notOverridden);
}


void
DeviceRegisterTransactionPort::createMultiReadExpectPattern(vector<long long> address, const std::string& labelName, long long value, long long mask){
//	cerr << "ERROR in framework: createReadExpectPattern needs to be overridden!" << endl;
	bool notOverridden = false;
	assert(notOverridden);
}


