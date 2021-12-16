#include <SRC_d2s/d2sFramework.h>

#include <iostream> 
//#include "TestMethod.h"


#include <Common_Func/System_Common_Func.h>
#include <SRC_d2s/PatternManager.h>
#include <SRC_d2s/PortChecker.h>
#include <UserConfig.h>
using namespace std;

#ifdef AUTO_HWPRBS
TransactionPort p_HWPRBS_RX(HWPRBS_RX_PORT);
TransactionPort p_HWPRBS_TX(HWPRBS_TX_PORT);
#endif

map<string,string> d2sFramework::lable_md5;

d2sFramework::d2sFramework()
{
    currentExecutionMode = d2sExecutionModeType::FUNCTIONAL_TST;
    changeFrameworkMode(d2sFrameWorkModeType::DefaultMode);
	currentIdentifier = "";
	default_mode=d2sFrameWorkModeType::LearningMode;
}

d2sFramework::~d2sFramework()
{
}

string d2sFramework::getCurrentBurstName(){
	static bool is_user_var_exists=true;
	string prefix_tag="";
	if(is_user_var_exists){
		try{
//			GET_USER_STRING("H30V200_d2s_prefix",prefix_tag);      //add for 1620 Cp merge confirmed by fang yanfen
			prefix_tag+="_";
		}
		catch(...){
			is_user_var_exists=false;
		}
	}
    return  "d2s_" + prefix_tag +currentIdentifier;
//    return  "d2s_"  +currentIdentifier;
}

bool d2sFramework::hwprbs_enable=false;

void
d2sFramework::d2s_LABEL_BEGIN(const std::string& identifier){
	d2s_LABEL_BEGIN(identifier,default_mode);
}
string d2sFramework::current_prefix;
string
d2sFramework::get_current_prefix(){
	return current_prefix;
}
void d2sFramework::d2s_LABEL_BEGIN(const std::string& identifier, d2sFrameWorkModeType::Enum mode, d2sExecutionModeType::Enum execMode){
	#ifdef AUTO_HWPRBS
	 	static string lastTestSuiteName = "";
	 	static bool prbs_pingroup_exists=true;
	    string testSuiteName;
	    GET_TESTSUITE_NAME(testSuiteName);
	    if(prbs_pingroup_exists and lastTestSuiteName != testSuiteName){
	    	hwprbs_enable=false;
	    	fwout<<"DFGP? ("<<HWPRBS_GROUP<<")"<<endl;
	    	if(prbs_pingroup_exists and fwresult.size()>0){
	    		fwout<<"prmd? prm,("<<HWPRBS_GROUP<<")"<<endl;
	    		if(fwresult[0][1] != "PRBS_OFF") hwprbs_enable=true;
	    	}
	    	else{
//	    		cerr<<"Error: PRBS Pin Group: "<<HWPRBS_GROUP<<" is not found! AUTO_HWPRBS is turned off!"<<endl;
	    		prbs_pingroup_exists=false;
	    	}
	    }

		if(prbs_pingroup_exists and hwprbs_enable){
			d2s_status::set_status("HWPRBS","ON");
			if(registeredPorts.find(p_HWPRBS_RX.getPortName())==registeredPorts.end()){
				registeredPorts.insert(p_HWPRBS_RX.getPortName());
		    	registeredTransactionPorts.insert(&p_HWPRBS_RX);
			}
			if(registeredPorts.find(p_HWPRBS_TX.getPortName())==registeredPorts.end()){
				registeredPorts.insert(p_HWPRBS_TX.getPortName());
		    	registeredTransactionPorts.insert(&p_HWPRBS_TX);
			}
		}

	#endif

	if(currentIdentifier != ""){
//		cerr << "ERROR: a d2s_LABEL_BEGIN-block with the following identifier is still open: " << currentIdentifier << endl;
//		cerr << "ERROR: Please check your code to close using d2s_LABEL_END() before entering the block with the identifier: " << identifier << endl;
    }

	currentIdentifier=identifier;
	if(hout.getLevel()&0x10){
		//hout(GENERAL)<<"-----------------------"<<endl;
		//hout(GENERAL)<<"enter d2s block "<<currentIdentifier<<endl;
//		MyTimer::start("d2s_block");
	}

	if(currentIdentifier.length() > 50){
		if(hout.getLevel()&0x10){
			//hout(GENERAL) << "Warning: Length of label should be less than 50 use MD5 instead!"<<endl;
		}
		currentIdentifier=get_MD5(currentIdentifier);
	}


    //update registered TransactionPorts on block begin
    for(TransactionPortSetIter it = registeredTransactionPorts.begin(); it != registeredTransactionPorts.end(); it++){
        (*it)->setD2sBlockBegin();
    }
    currentExecutionMode = execMode;
    current_prefix=currentIdentifier;

    changeFrameworkMode(mode);

	#ifdef AUTO_HWPRBS
		if(prbs_pingroup_exists and hwprbs_enable){
			p_HWPRBS_RX.execLabel(HWPRBS_RX_LABEL);
			p_HWPRBS_TX.execLabel(HWPRBS_TX_LABEL);
		}
	#endif

	//MyTimer::start("d2s_block");
}

void d2sFramework::d2s_LABEL_END(bool appendsuitename){
	bool executionWasSuccessful = false;
    //inform TransactionPorts about preExec
	string md5_tag="";
	if(hout.getLevel()&0x10){
//		//hout(GENERAL)<<"d2s block prepare "<<currentIdentifier<<" : "<<MyTimer::stop_no_print("d2s_block")<<"ms"<<endl;
	}

	if(hout.getLevel()&0x10){
//		MyTimer::start("MD5_CALC");
	}
	bool port_needappendsuitename=false;
	for(TransactionPortSetIter it = registeredTransactionPorts.begin(); it != registeredTransactionPorts.end(); it++){
		md5_tag.append((*it)->get_label_md5());
		md5_tag.push_back('\n');//* md5_tag combine the the each port's md5
		if((*it)->needAppendSuiteName()){
			port_needappendsuitename=true;
		}
	}
	md5_tag=get_MD5(md5_tag);//* md5_tag is md5 of the part MPB name
	d2s_status::set_status("MD5_TAG",md5_tag);


	if(appendsuitename && port_needappendsuitename){
		string suitename;
//		GET_TESTSUITE_NAME(suitename);
		d2s_status::set_status("SUITENAME",suitename);
	}
	else{
		d2s_status::delete_status("SUITENAME");
	}

	currentIdentifier = currentIdentifier+d2s_status::get_status();//* currentIdentifier is the MPB name except "d2s~"
	if(hout.getLevel()&0x10){
//		//hout(GENERAL)<<"label_md5: "<<MyTimer::stop_no_print("MD5_CALC")<<"ms"<<endl;
	}

	md5_tag="";
    for(TransactionPortSetIter it = registeredTransactionPorts.begin(); it != registeredTransactionPorts.end(); it++){
//        (*it)->preExec(getCurrentBurstName());
        if(currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){
        	md5_tag+=(*it)->get_burst_md5()+"\n";
		}
    }

    if(currentFrameworkMode == d2sFrameWorkModeType::EngineeringMode){
    	md5_tag=get_MD5(md5_tag);
    	if(hout.getLevel()&0x10){
    		//hout(GENERAL)<<getCurrentBurstName()<<":"<<md5_tag<<endl;
    	}
    	if(lable_md5.find(getCurrentBurstName())==lable_md5.end()){
    		lable_md5[getCurrentBurstName()]=md5_tag;
    	}
    	else{
    		if(lable_md5.find(getCurrentBurstName())->second != md5_tag){
//    			cerr<<"ERROR: Burst "<<getCurrentBurstName()<<" is overwritten by different content(exp: CSR initial value is diff,but configured reg value is same), burstname cannot distinguish burst content!"<<endl;
    		    for(TransactionPortSetIter it = registeredTransactionPorts.begin(); it != registeredTransactionPorts.end(); it++){
    		        (*it)->print_burstlabels();//TODO

    		    }
    		//	ERROR_EXIT(TM::ABORT_FLOW);
    		}
    	}
    }
    if(hout.getLevel()&0x10){
  //		MyTimer::start("d2s_pre_exec");
  	}
    for(TransactionPortSetIter it = registeredTransactionPorts.begin(); it != registeredTransactionPorts.end(); it++){
        (*it)->preExec(getCurrentBurstName());//TODO
    }
    if(hout.getLevel()&0x10){
//		//hout(GENERAL)<<"d2s pre_exec: "<<MyTimer::stop_no_print("d2s_pre_exec")<<"ms"<<endl;
	}


    //execBurst
    if(currentFrameworkMode != d2sFrameWorkModeType::ProductionMode){
        //skip test in ProductionMode for Troughput
        if(!PatternManager::isPatternAvailable(getCurrentBurstName())){
//            cerr << "Error: Burst doesn't contain any port-labels. Cannot execute Burst for \"" << currentIdentifier << "\"" << endl;
          //  ERROR_EXIT(TM::ABORT_FLOW);
        }
        else {
        	executionWasSuccessful = setPrimariesAndExecuteStartLabel(getCurrentBurstName());
        }
    }
    else {
    	executionWasSuccessful = setPrimariesAndExecuteStartLabel(getCurrentBurstName());
    }
    
    //inform TransactionPorts about postExec

    if(hout.getLevel()&0x10){
    //	//hout(GENERAL)<<"d2s execute "<<getCurrentBurstName()<<" : "<<MyTimer::stop_no_print("exec_d2s_block")<<"ms"<<endl;
   // 	MyTimer::start("post_d2s");
    }


    for(TransactionPortSetIter it = registeredTransactionPorts.begin(); it != registeredTransactionPorts.end(); it++){
//    	cout<<"TransactionPortSetIter -> port name:"<<(*it)->getPortName()<<endl;

        (*it)->postExec(currentIdentifier, executionWasSuccessful);
    }
    
    //reset states
    currentIdentifier = "";  
    currentExecutionMode = d2sExecutionModeType::FUNCTIONAL_TST;
    changeFrameworkMode(d2sFrameWorkModeType::DefaultMode);
    
    //update registered TransactionPorts on block end
    for(TransactionPortSetIter it = registeredTransactionPorts.begin(); it != registeredTransactionPorts.end(); it++){
        (*it)->setD2sBlockEnd();
    }    
    if(hout.getLevel()&0x10){
//    	//hout(GENERAL)<<"d2s postexec "<<currentIdentifier<<" : "<<MyTimer::stop_no_print("post_d2s")<<"ms"<<endl;
    	//hout(GENERAL)<<"exit d2s-block: "<<endl;
    	//hout(GENERAL)<<"--------------------------"<<endl;
    }

}

void d2sFramework::setPrimaries(){
    
}

void d2sFramework::synchronizePorts(){
	//synch with all registered ports
	synchronizePorts(registeredTransactionPorts);
}

void d2sFramework::synchronizePorts(TransactionPort &port1, TransactionPort &port2){
	TransactionPortSet portsToSync;
	portsToSync.insert(&port1);
	portsToSync.insert(&port2);
	synchronizePorts(portsToSync);
}
void d2sFramework::synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3){
	TransactionPortSet portsToSync;
	portsToSync.insert(&port1);
	portsToSync.insert(&port2);
	portsToSync.insert(&port3);
	synchronizePorts(portsToSync);
}
void d2sFramework::synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3, TransactionPort &port4){
	TransactionPortSet portsToSync;
	portsToSync.insert(&port1);
	portsToSync.insert(&port2);
	portsToSync.insert(&port3);
	portsToSync.insert(&port4);
	synchronizePorts(portsToSync);
}
void d2sFramework::synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3, TransactionPort &port4, TransactionPort &port5){
	TransactionPortSet portsToSync;
	portsToSync.insert(&port1);
	portsToSync.insert(&port2);
	portsToSync.insert(&port3);
	portsToSync.insert(&port4);
	portsToSync.insert(&port5);
	synchronizePorts(portsToSync);
}
void d2sFramework::synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3, TransactionPort &port4, TransactionPort &port5, TransactionPort &port6){
	TransactionPortSet portsToSync;
	portsToSync.insert(&port1);
	portsToSync.insert(&port2);
	portsToSync.insert(&port3);
	portsToSync.insert(&port4);
	portsToSync.insert(&port5);
	portsToSync.insert(&port6);
	synchronizePorts(portsToSync);
}
void d2sFramework::synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3, TransactionPort &port4, TransactionPort &port5, TransactionPort &port6, TransactionPort &port7){
	TransactionPortSet portsToSync;
	portsToSync.insert(&port1);
	portsToSync.insert(&port2);
	portsToSync.insert(&port3);
	portsToSync.insert(&port4);
	portsToSync.insert(&port5);
	portsToSync.insert(&port6);
	portsToSync.insert(&port7);
	synchronizePorts(portsToSync);
}
void d2sFramework::synchronizePorts(TransactionPort &port1, TransactionPort &port2, TransactionPort &port3, TransactionPort &port4, TransactionPort &port5, TransactionPort &port6, TransactionPort &port7, TransactionPort &port8){
	TransactionPortSet portsToSync;
	portsToSync.insert(&port1);
	portsToSync.insert(&port2);
	portsToSync.insert(&port3);
	portsToSync.insert(&port4);
	portsToSync.insert(&port5);
	portsToSync.insert(&port6);
	portsToSync.insert(&port7);
	portsToSync.insert(&port8);
	synchronizePorts(portsToSync);
}

void d2sFramework::synchronizePorts(TransactionPortSet selectedPortsToSync){
	double maxElapsedTime = 0.0;
	//find longest port
	for(TransactionPortSetIter it = registeredTransactionPorts.begin(); it != registeredTransactionPorts.end(); it++){
		double curElapsedTime = (*it)->getCurrentTimeStamp();

		if(curElapsedTime > maxElapsedTime) maxElapsedTime = curElapsedTime;
	}

	//adjust other ports to longest port
	for(TransactionPortSetIter it = registeredTransactionPorts.begin(); it != registeredTransactionPorts.end(); it++){
		double curElapsedTime = (*it)->getCurrentTimeStamp();
		if((maxElapsedTime - curElapsedTime) > 0){
//			(*it)->wait((maxElapsedTime - curElapsedTime) ns);//wait is in seconds
		}
	}

}

void d2sFramework::changeFrameworkMode(d2sFrameWorkModeType::Enum newMode){
    currentFrameworkMode = newMode;
    
    //update registered TransactionPorts on mode change
    for(TransactionPortSetIter it = registeredTransactionPorts.begin(); it != registeredTransactionPorts.end(); it++){
        (*it)->setFrameworkMode(currentFrameworkMode);
    }
}

d2sFrameWorkModeType::Enum d2sFramework::getCurrentMode(){
    return currentFrameworkMode;
}

d2sExecutionModeType::Enum d2sFramework::getCurrentExecutionMode(){
    return currentExecutionMode;
}  

bool d2sFramework::registerTransactionPort(TransactionPort &portToAdd){
    PortChecker &portChecker = PortChecker::Instance();
    
    //add new Port
    string strPortToAdd = portToAdd.getPortName();
    pair<set<string>::iterator, bool>  ret = registeredPorts.insert(strPortToAdd);
    if(ret.second == false) {
//    	cerr << "registerTransactionPort(): cannot register Port \"" << strPortToAdd << "\". Port with the same name already registered." << endl;
    	return false;
    }
    
    if(portChecker.arePortsIntersecting(registeredPorts)){
//        cerr << "registerTransactionPort(): cannot register Port! Port has common pins with already registered ports and so they cannot be used together!" << endl;
        registeredPorts.erase(strPortToAdd);
        return false;
    }
    else{
        registeredTransactionPorts.insert(&portToAdd);
        return true;    
    }
}
   

bool d2sFramework::setPrimariesAndExecuteStartLabel(const std::string&  startLabel){

	if(currentExecutionMode != d2sExecutionModeType::NONE){
		try{
			if(hout.getLevel()&0x10){
//				MyTimer::start("apply_prm");
			}
			setPrimaries();
//			Primary.label(startLabel);

			if(hout.getLevel()&0x10){
//				//hout(GENERAL)<<"d2s block apply primary "<<currentIdentifier<<" : "<<MyTimer::stop_no_print("apply_prm")<<"ms"<<endl;
//				MyTimer::start("exec_d2s_block");
			}

			switch(currentExecutionMode){
			case d2sExecutionModeType::FUNCTIONAL_TST:
	//			FUNCTIONAL_TEST();
				break;
			case d2sExecutionModeType::EXECUTE_TST:
	//			EXECUTE_TEST();
				break;
			case d2sExecutionModeType::DIGITAL_CAPTURE_TST:
//				DIGITAL_CAPTURE_TEST();
				break;
			case d2sExecutionModeType::SMC_FUNCTIONAL_TST:
	//			SMC_FUNCTIONAL_TEST();
				break;
			case d2sExecutionModeType::SMC_EXECUTE_TST:
	//			SMC_EXECUTE_TEST();
				break;
			case d2sExecutionModeType::SMC_DIGITAL_CAPTURE_TST:
	//			SMC_DIGITAL_CAPTURE_TEST();
				break;
			default:
//				cerr << "execMode not known. Please check your execMode!" << endl;
		//		ERROR_EXIT(TM::ABORT_FLOW);
				break;
			}
			//cout<<"getCurrentBurstName: "<<getCurrentBurstName()<<endl;
		}
		catch(...){
			string testSuiteName;
//			GET_TESTSUITE_NAME(testSuiteName);
//			cerr << "Setting and Executing label \"" << startLabel << "\" in test suite \"" << testSuiteName << "\" wasn't possible!" << endl;
//			cerr << "Error: Please check d2s-block: \"" << currentIdentifier << "\"" << endl;
		//	ERROR_EXIT(TM::ABORT_FLOW);
			return false;
		}
		return true;
	}
	else{
		return false;
	}
}

