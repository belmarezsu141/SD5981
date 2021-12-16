#include <SRC_d2s/TransactionPort.h>

#include <iostream>
#include <assert.h>
#include <Common_Func/System_Common_Func.h>

#include <Common_Func/System_Common_Func.h>
#include <Common_Func/System_Common_Func.h>
#include <SRC_d2s/PatternManager.h>

using namespace std;


TransactionPort::sitePortIdPassFailType TransactionPort::globalPassFail; 

bool
TransactionPort::isProductionMode(){
	return is_production_mode;
}

TransactionPort::TransactionPort(const std::string& pName)
{
    currentFrameworkMode = d2sFrameWorkModeType::DefaultMode;
    portName = pName;
    checkPassFail = false;
    inD2sBlock = false;
    //timingPeriod = 0.0;
}


TransactionPort::~TransactionPort()
{
}

void TransactionPort::print_burstlabels(){
//	cout<<"burst labels on port ("<<getPortName()<<") "<<endl;
	for(uint i=0;i<burstLabels.size();i++){
//		cout<<burstLabels[i]<<endl;
	}

}

void TransactionPort::setD2sBlockBegin(){
    if(inD2sBlock){
//        cerr << "Error: TransactionPort on port " << portName << " - No nesting d2s-blocks allowed." << endl; 
        assert(!inD2sBlock);
    }
    inD2sBlock = true;        
	int d2s_mode;
//	GET_USER_FLAG("d2s_mode",&d2s_mode);
	is_production_mode=(d2s_mode==2);
}

void TransactionPort::setD2sBlockEnd(){
    inD2sBlock = false;    
}

std::string TransactionPort::getPortName(){
    return portName;
}


void TransactionPort::preExec(const std::string& labelName){
    //clearing the passFail cache only if testsuite name changed
    static string lastTestSuiteName = "";
    string testSuiteName;
//    GET_TESTSUITE_NAME(testSuiteName);
    if(lastTestSuiteName != testSuiteName){
        lastTestSuiteName = testSuiteName;
        globalPassFail.clear();
    }

	if(currentFrameworkMode == d2sFrameWorkModeType::LearningMode || currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){

		if(burstLabels.size() != 0){
            PatternManager::createBurst(labelName, burstLabels, portName);
        }
        else{
            //noting to create
            //delete Burst if it was available before
            if(PatternManager::isPatternAvailable(labelName, "MAIN", portName)){
            	PatternManager::deleteLabel(labelName, portName);
            }
        }
    }

}

string
TransactionPort::get_label_md5(){
	if(hout.getLevel() & 0x80){
		//hout(GENERAL)<<"===================="<<endl;
		//hout(GENERAL)<<portName<<" md5 sorce:"<<endl;
		for(uint i=0;i<label_md5_tag.size();i++){
			//hout(GENERAL)<<"\t0x"<<hex<<(label_md5_tag[i] & 0xff)<<endl;
		}
		//hout(GENERAL)<<"===================="<<dec<<endl;
	}

	return get_MD5(label_md5_tag);//* label_md5_tag combines the total label name, then translate to md5
}

string TransactionPort::get_burst_md5(){
	burst_md5_tag="";
	for(uint i=0;i<burstLabels.size();i++){
		burst_md5_tag+=burstLabels[i]+"\n";
	}

	burst_md5_tag=get_MD5(burst_md5_tag);

	return burst_md5_tag;
}

void TransactionPort::setFrameworkMode(const d2sFrameWorkModeType::Enum mode){
    currentFrameworkMode = mode;
}


void TransactionPort::postExec(const std::string& executedId, bool executionWasSuccessful){
    if(checkPassFail){
        //store query focus
        string prevSite;
//        fwout << "PQFC?" << endl;  
//        prevSite = fwresult[0][0];
//        
//        //query pass/fail for port and store information
//        FOR_EACH_SITE_BEGIN();
//            int site = CURRENT_SITE_NUMBER();
//            bool passFail = false;
//            if(executionWasSuccessful){
//				fwout << "PQFC " << site << endl;
//				fwout << "PASS? (" << portName << ")" << endl; //would checking global pass/fail (for all ports) first be faster? [PRLT?]
//				passFail = (fwresult[0][0]=="P")?true:false;
//            }
//            else{
//            	passFail = false;
//            }
//            pair<map<string, bool>::iterator,bool> ret = globalPassFail[site][portName].insert(pair<string, bool> (executedId, passFail)); 
//            if(ret.second == false){
//                //replacing existing value from last execution. Maybe should change stl-map to stl-set? 
//                globalPassFail[site][portName].erase(executedId);
//                globalPassFail[site][portName].insert(pair<string, bool> (executedId, passFail));    
//            }
//            //cerr << "site " << site << ": result of " << executedId << " for port " << portName << " was " << passFail << endl; 
//        FOR_EACH_SITE_END();
        //restore query focus
//        fwout << "PQFC " << prevSite << endl;
    }
    
    checkPassFail = false;
    burst_md5_tag="";
    label_md5_tag.clear();
    burstLabels.clear();

//    cout<<"postExec  -- > cycleOffset before:"<<dec<<cycleOffset<<endl;


    cycleOffset = 0;
    call_id=0;
//    cout<<"postExec  -- > cycleOffset after :"<<dec<<cycleOffset<<endl;
}

void TransactionPort::execLabel(const std::string& labelName, unsigned long long cycles,bool check_cycle){
    if(!inD2sBlock){
//        cerr << "execLabel can only be used when inside a d2s_LABEL_BEGIN/END-block" << endl;
        assert(inD2sBlock);    
    }
    call_id++;
    if(currentFrameworkMode != d2sFrameWorkModeType::ProductionMode){
        //do error checks only in Learning Mode
        if(!PatternManager::isPatternAvailable(labelName, "MAIN", portName)){
//            cerr << "Error - execLabel: specificed label \"" << labelName << "\" does NOT exist for port \"" << portName << "\"!" << endl;
//            cerr << "Skipping label from burst" << endl;
            return;
        }
        //check if specified cycles do match the cycles
        if(check_cycle){
			unsigned long long smarTestCalculatedCycles = PatternManager::getCyclesFromLabel(labelName, portName);
			if(smarTestCalculatedCycles != cycles){
//				cerr << "Error - execLabel: specificed cycles don't match the label! Subsequent reads will not work correctly!" << endl;
//				cerr << "SmarTest calculated " << smarTestCalculatedCycles << " cycles for label \"" << labelName << "\"";
			}
        }
    }
    

    cycleOffset += cycles;
    switch(currentFrameworkMode){
            case d2sFrameWorkModeType::LearningMode:
            case d2sFrameWorkModeType::EngineeringMode:
                    burstLabels.push_back(labelName);
                    break;
            case d2sFrameWorkModeType::ProductionMode:
                    //will run the label later
                    break;
        default:
//                cerr << "Error! cannot execLabel: wrong state" << endl;
                break;                     
    }
    label_md5_tag.append(labelName);
    label_md5_tag.push_back('\n');
}

void TransactionPort::wait(double timeInS){
	//TODO: Implement wait using wait-sequencer command!
//	cerr << "wait using sequencer commands not yet implemented for TransactionPort. Cannot be used! Please use DeviceRegisterTransactionPort for the time being." << endl;
	assert(false);
}

void TransactionPort::enablePassFailCheckForNextExecution(){
    checkPassFail = true;
}

bool TransactionPort::hasPassed(const std::string& burst_id){
   int site;// = CURRENT_SITE_NUMBER();
    string id=burst_id;
	if(id.length() > 50){
//		cout << "Warning: Length of label should be less than 50 use MD5 instead!"<<endl;
		id=get_MD5(id);
	}

    std::map<std::string, bool>::const_iterator iter(globalPassFail[site][portName].find(id+d2s_status::get_status()));
    if(iter != globalPassFail[site][portName].end()) return iter->second;
    else{
//        cout << "ERROR: " << portName << ": hasPassed() of ID \"" << id << "\" not possible! Please switch on passFail-check using >>enablePassFailCheckForNextExecution()<< " << endl;
      //  ERROR_EXIT(TM::ABORT_FLOW);
    }
    return false;
}

void
TransactionPort::hasPassed(const std::string& id,bool& isAllSitesPassed,bool& isAllSitesFailed){
	isAllSitesPassed=true;
	isAllSitesFailed=true;
//	FOR_EACH_SITE_BEGIN();
//		isAllSitesPassed = (isAllSitesPassed && hasPassed(id));
//		isAllSitesFailed = (isAllSitesFailed && !hasPassed(id));
//	FOR_EACH_SITE_END();
}

//void
//TransactionPort::hasPassed(const std::string& id,bool& isAllSitesPassed,bool& isAllSitesFailed,ARRAY_I& eachSiteResult){
//	isAllSitesPassed = true;
//	isAllSitesFailed = true;
//	ARRAY_I	sites;
//	INT	ConfiguredSitesNum = GET_CONFIGURED_SITES(sites);
//	eachSiteResult.resize(ConfiguredSitesNum);
//	eachSiteResult.init(0);
//
//	FOR_EACH_SITE_BEGIN();
//    	int site = CURRENT_SITE_NUMBER() - 1;
//		isAllSitesPassed = (isAllSitesPassed && hasPassed(id));
//		isAllSitesFailed = (isAllSitesFailed && !hasPassed(id));
//		eachSiteResult[site] = hasPassed(id);
//	FOR_EACH_SITE_END();
//}

bool
TransactionPort::hasAllSitesPassed(const std::string& id){
	bool allpass,dummy;
	hasPassed(id,allpass,dummy);
	return allpass;
}

bool
TransactionPort::hasAllSitesFailed(const std::string& id){
	bool dummy,allfail;
	hasPassed(id,dummy,allfail);
	return allfail;
}

bool
TransactionPort::needAppendSuiteName(){
	return false;
}

unsigned long long TransactionPort::getCurrentCycleOffset(){
    return cycleOffset;    
}

double TransactionPort::getTimingPeriod(){
    int debug =0;
//    FLUSH(TM::APRM);
//    fwout << "PCLK? PRM, PRM, (" << getTimingPort() << "), EXACT" << endl;
//    if(fwresult.size() != 1){
//    	if(debug) cerr << "ERROR couldn't evaluate timing period for timing-port: " << getTimingPort() << endl;
//        return 1;
//    }else{
//        return fwresult[0].getDoubleParam(2);
//    }
    return 0;
}

double TransactionPort::getCurrentTimeStamp(){
    return getTimingPeriod() * getCurrentCycleOffset();
}

string TransactionPort::getTimingPort(){
    return portName;
}

