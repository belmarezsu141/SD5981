#include <SRC_d2s/d2s_Serial.h>

#include "assert.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
/*write parameters*/

d2s_Serial::d2s_Serial(const std::string& pName):d2s_Generic(pName)
{  
    writeMapInitialized = false;
    readAndExpectValueMapInitialized = false;
}

int d2s_Serial::getAddressBits(){
//    cerr << "Error in framework: getAddressBits() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return 0;    
}
      
int d2s_Serial::getDataBits(){
//    cerr << "Error in framework: getDataBits() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);    
    return 0;    
}

int d2s_Serial::getHighWaveformIndex(){
//    cerr << "Error in framework: getHighWaveformIndex() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);    
    return -1;
}

int d2s_Serial::getLowWaveformIndex(){
//    cerr << "Error in framework: getLowWaveformIndex() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return -1;
}
       
int d2s_Serial::getHighStrobeWaveformIndex(){
//    cerr << "Error in framework: getHighStrobeWaveformIndex() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return -1;
}

int d2s_Serial::getLowStrobeWaveformIndex(){
//    cerr << "Error in framework: getLowStrobeWaveformIndex() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return -1;
}
    
int d2s_Serial::getMaskStrobeWaveformIndex(){
//    cerr << "Error in framework: getMaskStrobeWaveformIndex() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);    
    return -1;
}        


    /*write parameters*/
std::string d2s_Serial::getWritePinName(){
//    cerr << "Error in framework: getWritePinName() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return "";
}
  
int d2s_Serial::getWriteAddressVectorNumberLSB(){
//    cerr << "Error in framework: getWriteAddressVectorNumberLSB() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return 0;
}
    
int d2s_Serial::getWriteAddressVectorNumberMSB(){
//    cerr << "Error in framework: getWriteAddressVectorNumberMSB() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return 0;
}
        
int d2s_Serial::getWriteDataVectorNumberLSB(){
//    cerr << "Error in framework: getWriteDataVectorNumberLSB() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return 0;
}
    

int d2s_Serial::getWriteDataVectorNumberMSB(){
//    cerr << "Error in framework: getWriteDataVectorNumberMSB() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return 0;
}

/*read parameters*/    
std::string d2s_Serial::getReadAddressPinName(){
//    cerr << "Error in framework: getReadAddressPinName() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return "";            
}
    
std::string d2s_Serial::getReadPinName(){
//    cerr << "Error in framework: getReadPinName() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return "";
}
    
 
int d2s_Serial::getReadAddressVectorNumberLSB(){
//    cerr << "Error in framework: getReadAddressVectorNumberLSB() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return 0;            
} 
           
int d2s_Serial::getReadAddressVectorNumberMSB(){
//    cerr << "Error in framework: getReadAddressVectorNumberMSB() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return 0;            
} 
       
int d2s_Serial::getReadDataCycleNumberLSB(){
//    cerr << "Error in framework: getReadDataCycleNumberLSB() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);    
    return 0;            
}
          
int d2s_Serial::getReadDataCycleNumberMSB(){
//    cerr << "Error in framework: getReadDataCycleNumberMSB() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return 0;            
}  
    
int d2s_Serial::getReadDataVectorNumberLSB(){
//    cerr << "Error in framework: getReadDataVectorNumberLSB() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return 0;            
}
    
int d2s_Serial::getReadDataVectorNumberMSB(){
//    cerr << "Error in framework: getReadDataVectorNumberMSB() needs to be overridden!" << endl;
    bool notOverridden = false;
    assert(notOverridden);
    return 0;            
}


int d2s_Serial::getPadding(){
    return 1;
}

void d2s_Serial::initWriteValueVectorMaps(){

	writeAddressValueVectorMap[0].clear(); //added by zh, 20141027  this row was not found in A21
	writeDataValueVectorMap[0].clear();    //added by zh, 20141027  this row was not found in A21


    bool parametersValid = true;

//    cout<<"VectorNumberMSB:"<<dec<<getWriteAddressVectorNumberMSB()<<endl;
//    cout<<"getWriteAddressVectorNumberLSB:"<<dec<<getWriteAddressVectorNumberLSB()<<endl;
//    cout<<"getAddressBits():"<<dec<<getAddressBits()<<endl;
//    cout<<"getPaddinggetWriteAddress():"<<dec<<getPadding()<<endl;


	if(getWriteAddressVectorNumberMSB()!=getWriteAddressVectorNumberLSB() and getAddressBits()!=0){ // add this if condition for single d2s template solution. Only writing data no address writing required.


			int addressVectors = abs(getWriteAddressVectorNumberMSB() - getWriteAddressVectorNumberLSB());
			if(addressVectors != ((getAddressBits()-1)*getPadding())){

//				cout<<"***************D2S  Debugging ***************************************"<<endl<<endl;

//				cout<<"addressVectors (MSB-LSB):"<<addressVectors <<" !=   (getAddressBits()-1)*getPadding()     default:getPadding=1 "<<endl;

//				cerr << "Error: specified MSB and LSB vectors for address don't match amount of address bits specified!" << endl;

				parametersValid = false;

//				cout<<"***************D2S  Debugging ***************************************"<<endl<<endl;

			}

	}



    int dataVectors = abs(getWriteDataVectorNumberMSB() - getWriteDataVectorNumberLSB());
    if(dataVectors != ((getDataBits()-1)*getPadding())){


//		cout<<"***************D2S  Debugging ***************************************"<<endl<<endl;

//		cout<<"getWriteDataVectorNumberMSB():"<<getWriteDataVectorNumberMSB()<<endl;

//		cout<<"getWriteDataVectorNumberLSB():"<<getWriteDataVectorNumberLSB()<<endl;

//		cout<<"getDataBits:"<<getDataBits()<<endl;

//		cout<<"dataVectors (MSB-LSB):"<<dataVectors<<" !=   (getAddressBits()-1)*getPadding()     default:getPadding=1 "<<endl;

//        cerr << "Error: specified MSB and LSB vectors for data don't match amount of data bits specified!" << endl;
        parametersValid = false;

//		cout<<"***************D2S  Debugging ***************************************"<<endl<<endl;

    }
    assert(parametersValid);
    
    //address
    unsigned long long mask = 1LL<<(getAddressBits()-1);
    int vector = getWriteAddressVectorNumberMSB();

	if(getWriteAddressVectorNumberMSB()!=getWriteAddressVectorNumberLSB() and getAddressBits()!=0){ // add this if condition for single d2s template solution. Only writing data no address writing required.

	    while(mask>0){
	    	writeAddressValueVectorMap[0].insert(std::pair<long long, std::pair<std::string, long long> > (mask, std::pair<std::string, long long> (getWritePinName(), vector)));
	        if(getWriteAddressVectorNumberLSB() > getWriteAddressVectorNumberMSB()) vector += getPadding();
	        else vector -= getPadding();
	        mask = mask>>1;
	    }

	}



    //data
    mask = 1LL<<(getDataBits()-1);
    vector = getWriteDataVectorNumberMSB();
    while(mask>0){
    	writeDataValueVectorMap[0].insert(std::pair<long long, std::pair<std::string, long long> > (mask, std::pair<std::string, long long> (getWritePinName(), vector)));
        if(getWriteDataVectorNumberLSB() > getWriteDataVectorNumberMSB()) vector += getPadding();
        else vector -= getPadding();
        mask = mask>>1;    
    }
    
//    writeMapInitialized = true;    marked by ZH,10241027  this row was not masked in A21
}


/*read parameters*/    

void d2s_Serial::initReadAndExpectValueVectorMaps(){

	readAndExpectAddressValueVectorMap[0].clear(); //ZH edit 20141027  this row was not found in A21
	readAndExpectDataValueVectorMap[0].clear();    //ZH edit 20141027  this row was not found in A21

    bool parametersValid = true;
    int addressVectors = abs(getReadAddressVectorNumberMSB() - getReadAddressVectorNumberLSB());
    if(addressVectors != ((getAddressBits()-1)*getPadding())){
//        cerr << "Error: specified MSB and LSB vectors for address don't match amount of address bits specified!" << endl; 
        parametersValid = false;
    }
    int dataVectors = abs(getReadDataVectorNumberMSB() - getReadDataVectorNumberLSB());

//    cout<<"getReadDataVectorNumberMSB:"<<getReadDataVectorNumberMSB()<<endl;
//    cout<<"getReadDataVectorNumberLSB:"<<getReadDataVectorNumberLSB()<<endl;
//    cout<<"getDataBits:"<<getDataBits()<<endl;


    if(dataVectors != ((getDataBits()-1)*getPadding())){


//    	cout <<"dataVectors = abs(getReadDataVectorNumberMSB() - getReadDataVectorNumberLSB()):"<<abs(getReadDataVectorNumberMSB() - getReadDataVectorNumberLSB())<<endl;
//    	cout <<"((getDataBits()-1)*getPadding())):"<<((getDataBits()-1)*getPadding())<<endl;
//        cerr << "Error: specified MSB and LSB vectors for data don't match amount of data bits specified!" << endl;  
        parametersValid = false;
    }
    assert(parametersValid);
    
    //address
    unsigned long long mask = 1LL<<(getAddressBits()-1);
    int vector = getReadAddressVectorNumberMSB();
    while(mask>0){
        readAndExpectAddressValueVectorMap[0].insert(std::pair<long long, std::pair<std::string, long long> > (mask, std::pair<std::string, long long> (getReadAddressPinName(), vector)));//a00
        if(getReadAddressVectorNumberLSB() > getReadAddressVectorNumberMSB()) vector += getPadding();
        else vector -= getPadding();
        mask = mask>>1;
    }

    //data
    mask = 1LL<<(getDataBits()-1);
    vector = getReadDataVectorNumberMSB();
    while(mask>0){
    	readAndExpectDataValueVectorMap[0].insert(std::pair<long long, std::pair<std::string, long long> > (mask, std::pair<std::string, long long> (getReadPinName(), vector)));//d00
        if(getReadDataVectorNumberLSB() > getReadDataVectorNumberMSB()) vector += getPadding();
        else vector -= getPadding();
        mask = mask>>1;    
    }
    
//    readAndExpectValueMapInitialized = true;   // ZH edit 20141027
}


void d2s_Serial::initReadValueCycleMaps(){
	//TODO: parameter checking...
    //data
	readDataValueCycleMap.clear();	//add by WeiMin
    unsigned long long mask = 1LL<<(getDataBits()-1);
    int cycle = getReadDataCycleNumberMSB();
    while(mask>0){
    	readDataValueCycleMap[0].insert(std::pair<long long, std::pair<std::string, long long> > (mask, std::pair<std::string, long long> (getReadPinName(), cycle)));//d00
        if(getReadDataCycleNumberLSB() > getReadDataCycleNumberMSB()) cycle += getPadding();
        else cycle -= getPadding();
        mask = mask>>1;    
    }
    readCycleMapInitialized = true;
}
