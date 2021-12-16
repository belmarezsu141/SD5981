//for test method API interfaces

#include <Common_Func/HiLink30_Common_Func.h>

using namespace std;
/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */

    void binary(int number)
{
        int remainder;
        ostringstream binary;
        for(int i=15;i>=0;i--)
        {

                remainder = number;
                remainder >>= i;
                binary << (remainder & 1);
                if (i%4 == 0) binary << " ";
        }
//        api->Info_message("%s",binary.str().c_str());
        cout <<binary.str()<<endl;
}
    
class HILINK_Register_Write_byIndex: public TestClass{
public:

    void init(){

    }
    void execute(){


        string 	mHiLink30_MacroList;
        string  mReg;
        int  mSlice;
        int  mReg_Index;
        int   	mData;
        mHiLink30_MacroList="0,1";
        mReg = "CS";
        mSlice = 0;
        mReg_Index = 1;
        mData = 0x5a5a;

        stHILINK_Download_FW HILINK_Download_FW;

//        const char * sTestsuiteName = api->Get_current_test_name();
        string sTestsuiteName = TheSoft.Flow().Test().GetCurrentTestName();
        string strTestsuiteName = sTestsuiteName;
//        api->Get_test_values(strTestsuiteName.data(),THE_TESTNUMBER,&m_TestNumber,THE_END);
//	    cout<<"=======Enter=============="<<strTestsuiteName<<"========================"<<endl;
		m_TestNumber = TheSoft.Flow().GetCurrentFlowTestTestNumber();
		m_HardBin = TheSoft.Flow().GetCurrentFlowTestHardFailBin();
		m_SoftBin = TheSoft.Flow().GetCurrentFlowTestSoftFailBin();
        d2s_JTAG& jtag = d2s_JTAG::Instance();

        static MACRO_LANE_SEL MacroLane_Sel;

        Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList);
        selectMacro_Now(MacroLane_Sel[0].MacroID);

        //=============================================
        // FW DownLoad
        //=============================================

        DS.rxRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(mSlice).Broadcast(0);
        DS.txRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(mSlice).Broadcast(0);
        DS.clkRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(mSlice).Broadcast(0);
        CS.clkRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(mSlice).Broadcast(0);
        SRAM.DSAPIRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(mSlice);


        if(mReg == "CS")
        {
                CS.clkRegs.Read2CSR(mReg_Index);
                ostringstream CS_Reg;
                CS_Reg << "CS  csr["<< dec << mReg_Index << "] = 0x" << hex <<  CS.clkRegs.csr[mReg_Index]  << "\t    ";
                CS_Reg << "MSB ";
                binary(CS.clkRegs.csr[mReg_Index]);
                CS_Reg << "LSB ";
                CS_Reg << "\t    ";
//                api->Info_message("%s",CS_Reg.str().c_str());
                cout <<CS_Reg.str()<<endl;

        }
        else if(mReg == "DS_RX")
        {

                DS.rxRegs.Read2CSR(mReg_Index);
                ostringstream DS_RxReg;
                DS_RxReg << "DS RX  csr["<< dec << mReg_Index << "] = 0x" << hex <<  DS.rxRegs.csr[mReg_Index]  << "\t    ";
                DS_RxReg << "MSB ";
                binary(DS.rxRegs.csr[mReg_Index]);
                DS_RxReg << "LSB ";
                DS_RxReg << "\t    ";
//                api->Info_message("%s",DS_RxReg.str().c_str());
                cout <<DS_RxReg.str()<<endl;

        }
        else if(mReg == "DS_TX")
        {
                DS.txRegs.Read2CSR(mReg_Index);
                ostringstream DS_TxReg;
                DS_TxReg << "DS TX  csr["<< dec << mReg_Index << "] = 0x" << hex <<  DS.txRegs.csr[mReg_Index]  << "\t    ";
                DS_TxReg << "MSB ";
                binary(DS.txRegs.csr[mReg_Index]);
                DS_TxReg << "LSB ";
                DS_TxReg << "\t    ";
//                api->Info_message("%s",DS_TxReg.str().c_str());
                cout <<DS_TxReg.str()<<endl;

        }
        else if(mReg == "DS_CLK")
        {
                DS.clkRegs.Read2CSR(mReg_Index);
                ostringstream DS_ClkReg;
                DS_ClkReg << "DS CLK  csr["<< dec << mReg_Index << "] = 0x" << hex <<  DS.clkRegs.csr[mReg_Index]  << "\t    ";
                DS_ClkReg << "MSB ";
                binary(DS.clkRegs.csr[mReg_Index]);
                DS_ClkReg << "LSB ";
                DS_ClkReg << "\t    ";
//                api->Info_message("%s",DS_ClkReg.str().c_str());
                cout <<DS_ClkReg.str()<<endl;
        }
        else if(mReg == "CSapi")
        {
                SRAM.CSAPIRegs.Read2CSR(mReg_Index);
                ostringstream CsApiReg;
                CsApiReg << "CSapi  csr["<< dec << mReg_Index << "] = 0x" << hex <<  SRAM.CSAPIRegs.csr[mReg_Index] << "\t    ";
                CsApiReg << "MSB ";
                binary( SRAM.CSAPIRegs.csr[mReg_Index]);
                CsApiReg << "LSB ";
                CsApiReg << "\t    ";
//                api->Info_message("%s",CsApiReg.str().c_str());
                cout <<CsApiReg.str()<<endl;
        }
        else if(mReg == "DSapi")
        {
                SRAM.DSAPIRegs.Read2CSR(mReg_Index);
                ostringstream DsApiReg;
                DsApiReg << "DSapi  csr["<< dec << mReg_Index << "] = 0x" << hex <<  SRAM.DSAPIRegs.csr[mReg_Index]  << "\t    ";
                DsApiReg << "MSB ";
                binary(  SRAM.DSAPIRegs.csr[mReg_Index]);
                DsApiReg << "LSB ";
                DsApiReg << "\t    ";
//                api->Info_message("%s",DsApiReg.str().c_str());
                cout <<DsApiReg.str()<<endl;
        }
        else if(mReg == "TOPapi")
        {
                SRAM.TOPAPIRegs.Read2CSR(mReg_Index);
                ostringstream TopApiReg;
                TopApiReg << "TOPapi  csr["<< dec << mReg_Index << "] = 0x" << hex <<  SRAM.TOPAPIRegs.csr[mReg_Index]  << "\t    ";
                TopApiReg << "MSB ";
                binary(  SRAM.TOPAPIRegs.csr[mReg_Index]);
                TopApiReg << "LSB ";
                TopApiReg << "\t    ";
//                api->Info_message("%s",TopApiReg.str().c_str());
                cout <<TopApiReg.str()<<endl;
        }
        else if(mReg == "CPapi")
        {
                SRAM.CPAPIRegs.Read2CSR(mReg_Index);
                ostringstream CPApiReg;
                CPApiReg << "CPapi  csr["<< dec << mReg_Index << "] = 0x" << hex <<  SRAM.CPAPIRegs.csr[mReg_Index]  << "\t    ";
                CPApiReg << "MSB ";
                binary(SRAM.CPAPIRegs.csr[mReg_Index]);
                CPApiReg << "LSB ";
                CPApiReg << "\t    ";
//                api->Info_message("%s",CPApiReg.str().c_str());
                cout <<CPApiReg.str()<<endl;
        }


        DS.rxRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(mSlice).Broadcast(0);
        DS.txRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(mSlice).Broadcast(0);
        DS.clkRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(mSlice).Broadcast(0);
        CS.clkRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(mSlice).Broadcast(0);
        SRAM.DSAPIRegs.MacroID(MacroLane_Sel[0].MacroID).SliceID(mSlice);

            d2s::d2s_LABEL_BEGIN("WRite", Global_D2S_Mode);

                        Select_Macro_Lane(MacroLane_Sel,mHiLink30_MacroList);
                        selectMacro(MacroLane_Sel[0].MacroID);

    			if(mReg == "CS")
    			{
    				CS.clkRegs.Write2DUT(mReg_Index,mData);
    			}
    			else if(mReg == "DS_RX")
    			{

    				DS.rxRegs.Write2DUT(mReg_Index,mData);
    			}
    			else if(mReg == "DS_TX")
    			{
    				DS.txRegs.Write2DUT(mReg_Index,mData);
    			}
    			else if(mReg == "DS_CLK")
    			{
    				DS.clkRegs.Write2DUT(mReg_Index,mData);
    			}
    			else if(mReg == "CSapi")
    			{
    				SRAM.CSAPIRegs.Write2DUT(mReg_Index,mData);
    			}
    			else if(mReg == "DSapi")
    			{
    				SRAM.DSAPIRegs.Write2DUT(mReg_Index,mData);
    			}
    			else if(mReg == "TOPapi")
    			{
    				SRAM.TOPAPIRegs.Write2DUT(mReg_Index,mData);
    			}
    			else if(mReg == "CPapi")
    			{
    				SRAM.CPAPIRegs.Write2DUT(mReg_Index,mData);
    			}

         d2s::d2s_LABEL_END();



        selectMacro_Now(MacroLane_Sel[0].MacroID);
         if(mReg == "CS")
        {
                CS.clkRegs.Read2CSR(mReg_Index);
                ostringstream CS_Reg;
                CS_Reg << "CS  csr["<< dec << mReg_Index << "] = 0x" << hex <<  CS.clkRegs.csr[mReg_Index]  << "\t    ";
                CS_Reg << "MSB ";
                binary(CS.clkRegs.csr[mReg_Index]);
                CS_Reg << "LSB ";
                CS_Reg << "\t    ";
//                api->Info_message("%s",CS_Reg.str().c_str());
                cout <<CS_Reg.str()<<endl;

        }
        else if(mReg == "DS_RX")
        {

                DS.rxRegs.Read2CSR(mReg_Index);
                ostringstream DS_RxReg;
                DS_RxReg << "DS RX  csr["<< dec << mReg_Index << "] = 0x" << hex <<  DS.rxRegs.csr[mReg_Index]  << "\t    ";
                DS_RxReg << "MSB ";
                binary(DS.rxRegs.csr[mReg_Index]);
                DS_RxReg << "LSB ";
                DS_RxReg << "\t    ";
//                api->Info_message("%s",DS_RxReg.str().c_str());
                cout <<DS_RxReg.str()<<endl;

        }
        else if(mReg == "DS_TX")
        {
                DS.txRegs.Read2CSR(mReg_Index);
                ostringstream DS_TxReg;
                DS_TxReg << "DS TX  csr["<< dec << mReg_Index << "] = 0x" << hex <<  DS.txRegs.csr[mReg_Index]  << "\t    ";
                DS_TxReg << "MSB ";
                binary(DS.txRegs.csr[mReg_Index]);
                DS_TxReg << "LSB ";
                DS_TxReg << "\t    ";
//                api->Info_message("%s",DS_TxReg.str().c_str());
                cout <<DS_TxReg.str()<<endl;

        }
        else if(mReg == "DS_CLK")
        {
                DS.clkRegs.Read2CSR(mReg_Index);
                ostringstream DS_ClkReg;
                DS_ClkReg << "DS CLK  csr["<< dec << mReg_Index << "] = 0x" << hex <<  DS.clkRegs.csr[mReg_Index]  << "\t    ";
                DS_ClkReg << "MSB ";
                binary(DS.clkRegs.csr[mReg_Index]);
                DS_ClkReg << "LSB ";
                DS_ClkReg << "\t    ";
//                api->Info_message("%s",DS_ClkReg.str().c_str());
                cout <<DS_ClkReg.str()<<endl;
        }
        else if(mReg == "CSapi")
        {
                SRAM.CSAPIRegs.Read2CSR(mReg_Index);
                ostringstream CsApiReg;
                CsApiReg << "CSapi  csr["<< dec << mReg_Index << "] = 0x" << hex <<  SRAM.CSAPIRegs.csr[mReg_Index] << "\t    ";
                CsApiReg << "MSB ";
                binary( SRAM.CSAPIRegs.csr[mReg_Index]);
                CsApiReg << "LSB ";
                CsApiReg << "\t    ";
//                api->Info_message("%s",CsApiReg.str().c_str());
                cout <<CsApiReg.str()<<endl;
        }
        else if(mReg == "DSapi")
        {
                SRAM.DSAPIRegs.Read2CSR(mReg_Index);
                ostringstream DsApiReg;
                DsApiReg << "DSapi  csr["<< dec << mReg_Index << "] = 0x" << hex <<  SRAM.DSAPIRegs.csr[mReg_Index]  << "\t    ";
                DsApiReg << "MSB ";
                binary(  SRAM.DSAPIRegs.csr[mReg_Index]);
                DsApiReg << "LSB ";
                DsApiReg << "\t    ";
//                api->Info_message("%s",DsApiReg.str().c_str());
                cout <<DsApiReg.str()<<endl;
        }
        else if(mReg == "TOPapi")
        {
                SRAM.TOPAPIRegs.Read2CSR(mReg_Index);
                ostringstream TopApiReg;
                TopApiReg << "TOPapi  csr["<< dec << mReg_Index << "] = 0x" << hex <<  SRAM.TOPAPIRegs.csr[mReg_Index]  << "\t    ";
                TopApiReg << "MSB ";
                binary(  SRAM.TOPAPIRegs.csr[mReg_Index]);
                TopApiReg << "LSB ";
                TopApiReg << "\t    ";
//                api->Info_message("%s",TopApiReg.str().c_str());
                cout <<TopApiReg.str()<<endl;
        }
        else if(mReg == "CPapi")
        {
                SRAM.CPAPIRegs.Read2CSR(mReg_Index);
                ostringstream CPApiReg;
                CPApiReg << "CPapi  csr["<< dec << mReg_Index << "] = 0x" << hex <<  SRAM.CPAPIRegs.csr[mReg_Index]  << "\t    ";
                CPApiReg << "MSB ";
                binary(SRAM.CPAPIRegs.csr[mReg_Index]);
                CPApiReg << "LSB ";
                CPApiReg << "\t    ";
//                api->Info_message("%s",CPApiReg.str().c_str());
                cout <<CPApiReg.str()<<endl;
        }

    }
};

REGISTER_TESTCLASS("HILINK_Register_Write_byIndex",HILINK_Register_Write_byIndex)


















