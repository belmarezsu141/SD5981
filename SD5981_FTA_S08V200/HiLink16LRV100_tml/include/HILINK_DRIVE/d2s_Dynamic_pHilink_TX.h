////////////////////////////////////////////////////////////////////////////////
// Description:                                                               //
// This head file is to define d2s protocol operation used for HiLink  		  //
// dedicated.
////////////////////////////////////////////////////////////////////////////////
#ifndef _d2s_Dynamic_pHilink_TX_MP_H_
#define _d2s_Dynamic_pHilink_TX_MP_H_
#include <SRC_d2s/d2s_Serial.h>
#include <SRC_d2s/d2sFramework.h>
#include <SRC_d2s/PatternManager.h>

//	d2s_Dynamic_pHilink_TX & hilink_tx = d2s_Dynamic_pHilink_TX::Instance();
//	hilink_tx.getContext();
//	fr.registerTransactionPort(hilink_tx);

// for integrated IC
class d2s_Dynamic_pHilink_TX : public d2s_Serial{
private:
	d2s_Dynamic_pHilink_TX(std::string pName):d2s_Serial(pName){};
	d2s_Dynamic_pHilink_TX(const d2s_Dynamic_pHilink_TX&);
	d2s_Dynamic_pHilink_TX& operator= (const d2s_Dynamic_pHilink_TX&);

public:
	static d2s_Dynamic_pHilink_TX& Instance()
	{

		static d2s_Dynamic_pHilink_TX instance(DynamicDC_TX);
		d2s_Dynamic_pHilink_TX& ref = instance;
		return ref;
	}


	int 	context;
	string 	Context;

//	int getContext()
//	{
//		string answer;
//		FW_TASK("GCTX? CURR,",answer);
//		Context = answer.substr(12,answer.size()-14);
//
//        if(Context == "")
//        {
//        	Context = "DEFAULT";
//        }
//
//		if (Context == "DEFAULT")
//		{
//			context = 0;
//		}
//		else if  (Context == "STDDIFF")
//		{
//			context = 1;
//		}
//		else if  (Context == "FASTDIFF")
//		{
//			context = 2;
//		}
//		return 1;
//	}

	int getHighWaveformIndex(){ return 1;}
	int getLowWaveformIndex(){ return 0;}
	int getHighStrobeWaveformIndex(){ return 1;}
	int getLowStrobeWaveformIndex(){ return 0;}
	int getMaskStrobeWaveformIndex(){ return 3;}

	std::string getInterfaceName()
	{
		return "";
	}

	/*wait parameters*/
	std::string getTimingPort(){ return DynamicDC_TX;}

	double getTimingPeriod()
	{
		static double period = 0.0;
		int debug = 0;//modify by thy 20211129
//		if (period == 0.0) {
//			int debug = 0;
////			FLUSH(TM::APRM);
////			fwout << "PCLK? PRM, PRM, (" << getTimingPort() << "), EXACT"
////					<< endl;
//			if (fwresult.size() != 1) {
////				if (debug)
////					cerr
////					<< "ERROR couldn't evaluate timing period for timing-port: "
////					<< getTimingPort() << endl;
//				period = 0.0;
//			} else {
//				period = fwresult[0].getDoubleParam(2);
//			}
//		}
		return period;
	}

	std::string getWaitTemplatePatternName()
	{
		switch(context)
		{
		case 0:
			return DynamicDC_TX_d2s_wait_template+"_STD";
		case 1:
			return DynamicDC_TX_d2s_wait_template+"_STDDIFF";
		case 2:
			return DynamicDC_TX_d2s_wait_template+"_FASTDIFF";
		default:
			return DynamicDC_TX_d2s_wait_template+"_STD";
		}
	}
};


#endif
