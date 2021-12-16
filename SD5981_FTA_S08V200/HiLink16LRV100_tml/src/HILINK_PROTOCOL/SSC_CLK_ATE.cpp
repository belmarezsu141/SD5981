
//for test method API interfaces
//#include "mapi.hpp"
//using namespace std;
//using namespace V93kLimits;

#include <HILINK_PUG/HiLink16_PUG.h>

/**
 * Test method class.
 *
 * For each testsuite using this test method, one object of this
 * class is created.
 */
class SSC_CLK_ATE: public TestClass {


public:
	STRING 				mHiLink16_MacroList;
	STRING 				mPinList;
	STRING 				sPinList;
	STRING 				sPinList_P;
	STRING 				sPinList_N;
	STRING 				mCaptureVars;
	INT					iPrintLvl;


	/**
	*Initialize the parameter interface to the testflow.
	*This method is called just once after a testsuite is created.
	*/
	void init()
	{
		add_param("H16LR_MacroList","string",&mHiLink16_MacroList)
					 .set_comment("HiLink16 Macro List for test")
					 //.set_options("0,1:FromPinList")
					 .set_default("0,1");
		add_param("PinList","PinString",&mPinList);
		add_param("CaptureVars","string",&mCaptureVars)
					 .set_comment("HiLink15 Macro List Capture Vars")
					 .set_default("SSC_CLK_Capture");
		add_param("PrintLvl[0~15]","int",&iPrintLvl)
					 .set_comment("Enable this flag when FlowVariable DebugLevel = 10000(16)"
							     "0000 = RELEASE; 0001 = GENERAL; 0010 = DETAIL; 0100 = EYE_PLOT; 1000 = REG_ACCESS; Can be Assembled")
					 //.set_options("0:1:3:4:7:9")
					 .set_default("3");
	}

	void execute()
		{

		}
	//===================Hi1213=============
	void Frequency_Average_Calc(ARRAY_D source_date, ARRAY_D &result_data, int average_index=1)
		{
			INT source_size = source_date.size();
			INT result_size = source_size/average_index;
			result_data.resize(result_size);
			result_data.init(0);

			for (INT i = 0; i < result_size; i ++)
			{
				for (INT j = 0; j < average_index; j ++)
				{
					result_data[i] += source_date[i * average_index + j];
				}
				result_data[i] = result_data[i] / double(average_index);
			}
		}

//=====================93k================
//	void Frequency_Average_Calc(ARRAY_D source_date, ARRAY_D &result_data, int average_index=1)
//	{
//		INT source_size = source_date.size();
//		INT result_size = source_size/average_index;
//		result_data.resize(result_size);
//		result_data.init(0);
//
//		for (INT i = 0; i < result_size; i ++)
//		{
//			for (INT j = 0; j < average_index; j ++)
//			{
//				result_data[i] += source_date[i * average_index + j];
//			}
//			result_data[i] = result_data[i] / double(average_index);
//		}
//	}

	/*
	void End_point_Calc(ARRAY_D source_data,vector<double> &Select_wave,bool RampUP = 1)
	{
		INT_VECTOR 		top_point, bot_point;
		//ignor the first points and the last point, then find the end point
		for (INT i = 8; i < (source_data.size() - 8); i ++)
		{
			//top_point
			if((source_data[i]>=source_data[i-1])&&(source_data[i]>=source_data[i-2])&&(source_data[i]>source_data[i-3])&&(source_data[i]>source_data[i-4])
					&&(source_data[i]>source_data[i-5])&&(source_data[i]>source_data[i-6])&&(source_data[i]>source_data[i-7])&&(source_data[i]>source_data[i-8])
					&&(source_data[i]>source_data[i+1])&&(source_data[i]>source_data[i+2])&&(source_data[i]>source_data[i+3])&&(source_data[i]>source_data[i+4])
					&&(source_data[i]>source_data[i+5])&&(source_data[i]>source_data[i+6])&&(source_data[i]>source_data[i+7])&&(source_data[i]>source_data[i+8]))
			{
				top_point.push_back(i);
			}

			//bot_point
			if((source_data[i]<=source_data[i-1])&&(source_data[i]<=source_data[i-2])&&(source_data[i]<source_data[i-3])&&(source_data[i]<source_data[i-4])
					&&(source_data[i]<source_data[i-5])&&(source_data[i]<source_data[i-6])&&(source_data[i]<source_data[i-7])&&(source_data[i]<source_data[i-8])
					&&(source_data[i]<source_data[i+1])&&(source_data[i]<source_data[i+2])&&(source_data[i]<source_data[i+3])&&(source_data[i]<source_data[i+4])
					&&(source_data[i]<source_data[i+5])&&(source_data[i]<source_data[i+6])&&(source_data[i]<source_data[i+7])&&(source_data[i]<source_data[i+8]))
			{
				bot_point.push_back(i);
			}
		}


		INT start = -999;
		INT stop = 999;

		if ((( top_point.size() + bot_point.size()) < 3) or (top_point.size() < 1) or (bot_point.size() < 1))
		{
			hout(GENERAL) << " ERROR : there is less than 3 end point found!! please modify the sampling point No. or sampling rate !!!"<<endl;

			for (INT i = 0; i < 100; i ++)
			{
				Select_wave.push_back(0);
			}
		}
		else
		{
			hout(DETAIL) << "## Select Ramp wave format(0:RampDown; 1:RamdUP)	:	" << RampUP << endl;

			if(!RampUP)
			{

				if(top_point.size() > 1)
				{
					start = top_point[0];
					stop = (bot_point[0] > top_point[0]) ? bot_point[0] : bot_point[1];
				}
				else
				{
					start = top_point[0];
					stop = bot_point[1];
				}
			}
			else
			{
				if(bot_point.size() > 1)
				{
					start = bot_point[0];
					stop = (top_point[0] > bot_point[0]) ? top_point[0] : top_point[1];
				}
				else
				{
					start = bot_point[0];
					stop = top_point[1];
				}
			}

			hout(DETAIL) << "--> Ramp wave start point : " << start << "\n-->           stop  point: " << stop << endl;

			for (INT i = 0; i < (stop - start); i ++)
			Select_wave.push_back(source_data[start + i]);

			hout(DETAIL) << "##### Stop - Start = " << dec << stop - start << endl;
		}
	}
	*/
	//===============Hi1213===================
	void End_point_Calc_Average(ARRAY_D source_data,vector<double> &Select_wave,bool RampUP = 1)
		{
			INT_VECTOR 			top_point, bot_point;
			//ignor the first points and the last point, then find the end point
			for (INT i = 8; i < source_data.size() - 8; i ++)
			{
				//top_point
				if((source_data[i]>=source_data[i-1])&&(source_data[i]>=source_data[i-2])&&(source_data[i]>=source_data[i-3])&&(source_data[i]>=source_data[i-4])
						&&(source_data[i]>=source_data[i-5])&&(source_data[i]>source_data[i-6])&&(source_data[i]>source_data[i-7])&&(source_data[i]>source_data[i-8])
						&&(source_data[i]>source_data[i+1])&&(source_data[i]>source_data[i+2])&&(source_data[i]>source_data[i+3])&&(source_data[i]>source_data[i+4])
						&&(source_data[i]>source_data[i+5])&&(source_data[i]>source_data[i+6])&&(source_data[i]>source_data[i+7])&&(source_data[i]>source_data[i+8]))
				{
					top_point.push_back(i);
				}

				//bot_point
				if((source_data[i]<=source_data[i-1])&&(source_data[i]<=source_data[i-2])&&(source_data[i]<=source_data[i-3])&&(source_data[i]<=source_data[i-4])
						&&(source_data[i]<=source_data[i-5])&&(source_data[i]<source_data[i-6])&&(source_data[i]<source_data[i-7])&&(source_data[i]<source_data[i-8])
						&&(source_data[i]<source_data[i+1])&&(source_data[i]<source_data[i+2])&&(source_data[i]<source_data[i+3])&&(source_data[i]<source_data[i+4])
						&&(source_data[i]<source_data[i+5])&&(source_data[i]<source_data[i+6])&&(source_data[i]<source_data[i+7])&&(source_data[i]<source_data[i+8]))
				{
					bot_point.push_back(i);
				}
			}

			INT start = -999;
			INT stop = 999;

			if (((top_point.size() + bot_point.size()) < 3) or (top_point.size() < 1) or (bot_point.size() < 1))
			{
				hout(GENERAL) << " ERROR : there is less than 3 end point found!! please modify the sampling point No. or sampling rate !!!" << endl;

				for (INT i = 0; i < 100; i ++)
				{
					Select_wave.push_back(0);
				}
			}
			else
			{
				hout(DETAIL) << "Select Ramp wave format (0:RampDown; 1:RamdUP): " << RampUP << endl;

				INT 				ramp_up_sum = 0, ramp_up_Num = 0;
				INT 				ramp_down_sum = 0, ramp_down_Num = 0;
				DOUBLE_VECTOR 		ramp_up,ramp_down;

				if(!RampUP)
				{
					if (top_point.size() > 1)
					{
						if(top_point[0] > bot_point[0])
						{
							for (UINT i = 1; i < bot_point.size(); i ++)
							{
								ramp_down_sum += (bot_point[i] - top_point[i - 1]);
							}
							ramp_down_Num = ramp_down_sum / (bot_point.size() - 1);
							ramp_down.resize(ramp_down_Num);

							for (INT i = 0; i < ramp_down_Num; i ++)
							{
								for (UINT k = 0; k < bot_point.size() - 1; k ++)
								{
									INT top_point_Num = top_point[k];
									ramp_down[i] += source_data[top_point_Num + i];
								}
								ramp_down[i] = ramp_down[i] / (bot_point.size() - 1);

								hout(DETAIL) << "ramp_down[" << i << "] = " << ramp_down[i] << endl;
								Select_wave.push_back(ramp_down[i]);
							}
						}
						else
						{
							for (UINT i = 0; i < bot_point.size(); i ++)
							{
								ramp_down_sum += (bot_point[i] - top_point[i]);
							}
							ramp_down_Num = ramp_down_sum / bot_point.size();
							ramp_down.resize(ramp_down_Num);
							for (INT i = 0; i < ramp_down_Num; i ++)
							{
								for (UINT k = 0; k < bot_point.size(); k ++)
								{
									INT top_point_Num = top_point[k];
									ramp_down[i] +=  source_data[top_point_Num + i];
								}
								ramp_down[i] = ramp_down[i] / (bot_point.size());
								hout(DETAIL) << "ramp_down[" << i << "] = " << ramp_down[i] << endl;
								Select_wave.push_back(ramp_down[i]);
							}
						}
					}
					else
					{
						start = top_point[0];
						stop = (bot_point[0] > top_point[0]) ? bot_point[0] : bot_point[1];
					}
				}
				else
				{
					if(bot_point.size() > 1)
					{
						if(top_point[0] > bot_point[0])
						{
							for (UINT i = 0; i < top_point.size(); i ++)
							{
								ramp_up_sum += (top_point[i] - bot_point[i]);
							}
							ramp_up_Num = ramp_up_sum / top_point.size();
							ramp_up.resize(ramp_up_Num);

							for (INT i = 0; i < ramp_up_Num; i ++)
							{
								for(UINT k = 0; k < top_point.size(); k ++)
								{
									INT bot_point_Num = bot_point[k];
									ramp_up[i] += source_data[bot_point_Num + i];
								}
								ramp_up[i] = ramp_up[i] / (top_point.size());
								hout(DETAIL) << "ramp_up[" << i << "] = " << ramp_up[i] << endl;
								Select_wave.push_back(ramp_up[i]);
							}
						}
						else
						{
							for (UINT i = 1; i < top_point.size(); i ++)
							{
								ramp_up_sum += (top_point[i] - bot_point[i - 1]);
							}
							ramp_up_Num = ramp_up_sum / (top_point.size() - 1);
							ramp_up.resize(ramp_up_Num);
							for (INT i = 0; i < ramp_up_Num; i ++)
							{
								for(UINT k = 0; k < top_point.size() - 1; k ++)
								{
									INT bot_point_Num = bot_point[k];
									ramp_up[i] +=  source_data[bot_point_Num + i];
								}
								ramp_up[i] = ramp_up[i] / (top_point.size() - 1);
								hout(DETAIL) << "ramp_up[" << i << "] = " << ramp_up[i] << endl;
								Select_wave.push_back(ramp_up[i]);
							}
						}
					}
					else
					{
						start = bot_point[0];
						stop = (top_point[0] > bot_point[0]) ? top_point[0] : top_point[1];

						hout(DETAIL) << "--> Ramp wave start point : " << start << "\n-->           stop  point: " << stop << endl;
						for (INT i = 0; i < abs(stop - start); i ++)
						Select_wave.push_back(source_data[start + i]);
					}
				}
			}
		}
	//=======================93k======================

//	void End_point_Calc_Average(ARRAY_D source_data,vector<double> &Select_wave,bool RampUP = 1)
//	{
//		INT_VECTOR 			top_point, bot_point;
//		//ignor the first points and the last point, then find the end point
//		for (INT i = 8; i < source_data.size() - 8; i ++)
//		{
//			//top_point
//			if((source_data[i]>=source_data[i-1])&&(source_data[i]>=source_data[i-2])&&(source_data[i]>=source_data[i-3])&&(source_data[i]>=source_data[i-4])
//					&&(source_data[i]>=source_data[i-5])&&(source_data[i]>source_data[i-6])&&(source_data[i]>source_data[i-7])&&(source_data[i]>source_data[i-8])
//					&&(source_data[i]>source_data[i+1])&&(source_data[i]>source_data[i+2])&&(source_data[i]>source_data[i+3])&&(source_data[i]>source_data[i+4])
//					&&(source_data[i]>source_data[i+5])&&(source_data[i]>source_data[i+6])&&(source_data[i]>source_data[i+7])&&(source_data[i]>source_data[i+8]))
//			{
//				top_point.push_back(i);
//			}
//
//			//bot_point
//			if((source_data[i]<=source_data[i-1])&&(source_data[i]<=source_data[i-2])&&(source_data[i]<=source_data[i-3])&&(source_data[i]<=source_data[i-4])
//					&&(source_data[i]<=source_data[i-5])&&(source_data[i]<source_data[i-6])&&(source_data[i]<source_data[i-7])&&(source_data[i]<source_data[i-8])
//					&&(source_data[i]<source_data[i+1])&&(source_data[i]<source_data[i+2])&&(source_data[i]<source_data[i+3])&&(source_data[i]<source_data[i+4])
//					&&(source_data[i]<source_data[i+5])&&(source_data[i]<source_data[i+6])&&(source_data[i]<source_data[i+7])&&(source_data[i]<source_data[i+8]))
//			{
//				bot_point.push_back(i);
//			}
//		}
//
//		INT start = -999;
//		INT stop = 999;
//
//		if (((top_point.size() + bot_point.size()) < 3) or (top_point.size() < 1) or (bot_point.size() < 1))
//		{
//			hout(GENERAL) << " ERROR : there is less than 3 end point found!! please modify the sampling point No. or sampling rate !!!" << endl;
//
//			for (INT i = 0; i < 100; i ++)
//			{
//				Select_wave.push_back(0);
//			}
//		}
//		else
//		{
//			hout(DETAIL) << "Select Ramp wave format (0:RampDown; 1:RamdUP): " << RampUP << endl;
//
//			INT 				ramp_up_sum = 0, ramp_up_Num = 0;
//			INT 				ramp_down_sum = 0, ramp_down_Num = 0;
//			DOUBLE_VECTOR 		ramp_up,ramp_down;
//
//			if(!RampUP)
//			{
//				if (top_point.size() > 1)
//				{
//					if(top_point[0] > bot_point[0])
//					{
//						for (UINT i = 1; i < bot_point.size(); i ++)
//						{
//							ramp_down_sum += (bot_point[i] - top_point[i - 1]);
//						}
//						ramp_down_Num = ramp_down_sum / (bot_point.size() - 1);
//						ramp_down.resize(ramp_down_Num);
//
//						for (INT i = 0; i < ramp_down_Num; i ++)
//						{
//							for (UINT k = 0; k < bot_point.size() - 1; k ++)
//							{
//								INT top_point_Num = top_point[k];
//								ramp_down[i] += source_data[top_point_Num + i];
//							}
//							ramp_down[i] = ramp_down[i] / (bot_point.size() - 1);
//
//							hout(DETAIL) << "ramp_down[" << i << "] = " << ramp_down[i] << endl;
//							Select_wave.push_back(ramp_down[i]);
//						}
//					}
//					else
//					{
//						for (UINT i = 0; i < bot_point.size(); i ++)
//						{
//							ramp_down_sum += (bot_point[i] - top_point[i]);
//						}
//						ramp_down_Num = ramp_down_sum / bot_point.size();
//						ramp_down.resize(ramp_down_Num);
//						for (INT i = 0; i < ramp_down_Num; i ++)
//						{
//							for (UINT k = 0; k < bot_point.size(); k ++)
//							{
//								INT top_point_Num = top_point[k];
//								ramp_down[i] +=  source_data[top_point_Num + i];
//							}
//							ramp_down[i] = ramp_down[i] / (bot_point.size());
//							hout(DETAIL) << "ramp_down[" << i << "] = " << ramp_down[i] << endl;
//							Select_wave.push_back(ramp_down[i]);
//						}
//					}
//				}
//				else
//				{
//					start = top_point[0];
//					stop = (bot_point[0] > top_point[0]) ? bot_point[0] : bot_point[1];
//				}
//			}
//			else
//			{
//				if(bot_point.size() > 1)
//				{
//					if(top_point[0] > bot_point[0])
//					{
//						for (UINT i = 0; i < top_point.size(); i ++)
//						{
//							ramp_up_sum += (top_point[i] - bot_point[i]);
//						}
//						ramp_up_Num = ramp_up_sum / top_point.size();
//						ramp_up.resize(ramp_up_Num);
//
//						for (INT i = 0; i < ramp_up_Num; i ++)
//						{
//							for(UINT k = 0; k < top_point.size(); k ++)
//							{
//								INT bot_point_Num = bot_point[k];
//								ramp_up[i] += source_data[bot_point_Num + i];
//							}
//							ramp_up[i] = ramp_up[i] / (top_point.size());
//							hout(DETAIL) << "ramp_up[" << i << "] = " << ramp_up[i] << endl;
//							Select_wave.push_back(ramp_up[i]);
//						}
//					}
//					else
//					{
//						for (UINT i = 1; i < top_point.size(); i ++)
//						{
//							ramp_up_sum += (top_point[i] - bot_point[i - 1]);
//						}
//						ramp_up_Num = ramp_up_sum / (top_point.size() - 1);
//						ramp_up.resize(ramp_up_Num);
//						for (INT i = 0; i < ramp_up_Num; i ++)
//						{
//							for(UINT k = 0; k < top_point.size() - 1; k ++)
//							{
//								INT bot_point_Num = bot_point[k];
//								ramp_up[i] +=  source_data[bot_point_Num + i];
//							}
//							ramp_up[i] = ramp_up[i] / (top_point.size() - 1);
//							hout(DETAIL) << "ramp_up[" << i << "] = " << ramp_up[i] << endl;
//							Select_wave.push_back(ramp_up[i]);
//						}
//					}
//				}
//				else
//				{
//					start = bot_point[0];
//					stop = (top_point[0] > bot_point[0]) ? top_point[0] : top_point[1];
//
//					hout(DETAIL) << "--> Ramp wave start point : " << start << "\n-->           stop  point: " << stop << endl;
//					for (INT i = 0; i < abs(stop - start); i ++)
//					Select_wave.push_back(source_data[start + i]);
//				}
//			}
//		}
//	}


	//============================Hi1213==============
	bool End_point_Varify(ARRAY_D source_data)
		{
			vector<int> top_point, bot_point;
			//ignor the first points and the last point, then find the end point
			for (INT i = 8; i < source_data.size() - 8; i ++)
			{
				//top_point
				if((source_data[i]>=source_data[i-1])&&(source_data[i]>=source_data[i-2])&&(source_data[i]>=source_data[i-3])&&(source_data[i]>=source_data[i-4])
						&&(source_data[i]>=source_data[i-5])&&(source_data[i]>source_data[i-6])&&(source_data[i]>source_data[i-7])&&(source_data[i]>source_data[i-8])
						&&(source_data[i]>source_data[i+1])&&(source_data[i]>source_data[i+2])&&(source_data[i]>source_data[i+3])&&(source_data[i]>source_data[i+4])
						&&(source_data[i]>source_data[i+5])&&(source_data[i]>source_data[i+6])&&(source_data[i]>source_data[i+7])&&(source_data[i]>source_data[i+8]))
				{
					top_point.push_back(i);
				}

				//bot_point
				if((source_data[i]<=source_data[i-1])&&(source_data[i]<=source_data[i-2])&&(source_data[i]<=source_data[i-3])&&(source_data[i]<=source_data[i-4])
						&&(source_data[i]<=source_data[i-5])&&(source_data[i]<source_data[i-6])&&(source_data[i]<source_data[i-7])&&(source_data[i]<source_data[i-8])
						&&(source_data[i]<source_data[i+1])&&(source_data[i]<source_data[i+2])&&(source_data[i]<source_data[i+3])&&(source_data[i]<source_data[i+4])
						&&(source_data[i]<source_data[i+5])&&(source_data[i]<source_data[i+6])&&(source_data[i]<source_data[i+7])&&(source_data[i]<source_data[i+8]))
				{
					bot_point.push_back(i);
				}
			}

			INT pair_pt_size = (top_point.size() <= bot_point.size() ) ? top_point.size() : bot_point.size();

			bool result = true;

			//****************************************************
			// 1. verify that there are more than 2 top_point and 2 bot_point; (should verify that digital capture's cycle to get more than 4 SSC CLK ramp wave)
			// 2. verify that sequence of the end point
			//*****************************************************

			if((top_point.size() < 2) or (bot_point.size() < 2))
			{
				result = false;
				hout(DETAIL) << "WARNING: End Point is not enough, (at last 2 point of top and bot)" << endl;
			}
			else
			{
				if(top_point[0] < bot_point[0])
				{

					for (INT i = 1; i < pair_pt_size ; i ++)
					{
						if((top_point[i] < bot_point[i-1]) or (top_point[i] >= bot_point[i]))
							{
								result = false;
								hout(DETAIL) << "WARNING: End Points are not the correct sequencer !!" << endl;
							}
					}

				}
				else if (top_point[0] > bot_point[0])
				{

					for (INT i = 1; i < pair_pt_size ; i ++)
					{
						if((bot_point[i] < top_point[i-1]) or (bot_point[i] > top_point[i]))
						{
							result = false;
							hout(DETAIL) << "WARNING: End Points are not the correct sequencer !!" << endl;
						}
					}
				}
				else
					result = false;
			}

			return result;
		}
	//======================93K=======================
//
//
//	bool End_point_Varify(ARRAY_D source_data)
//	{
//		vector<int> top_point, bot_point;
//		//ignor the first points and the last point, then find the end point
//		for (INT i = 8; i < source_data.size() - 8; i ++)
//		{
//			//top_point
//			if((source_data[i]>=source_data[i-1])&&(source_data[i]>=source_data[i-2])&&(source_data[i]>=source_data[i-3])&&(source_data[i]>=source_data[i-4])
//					&&(source_data[i]>=source_data[i-5])&&(source_data[i]>source_data[i-6])&&(source_data[i]>source_data[i-7])&&(source_data[i]>source_data[i-8])
//					&&(source_data[i]>source_data[i+1])&&(source_data[i]>source_data[i+2])&&(source_data[i]>source_data[i+3])&&(source_data[i]>source_data[i+4])
//					&&(source_data[i]>source_data[i+5])&&(source_data[i]>source_data[i+6])&&(source_data[i]>source_data[i+7])&&(source_data[i]>source_data[i+8]))
//			{
//				top_point.push_back(i);
//			}
//
//			//bot_point
//			if((source_data[i]<=source_data[i-1])&&(source_data[i]<=source_data[i-2])&&(source_data[i]<=source_data[i-3])&&(source_data[i]<=source_data[i-4])
//					&&(source_data[i]<=source_data[i-5])&&(source_data[i]<source_data[i-6])&&(source_data[i]<source_data[i-7])&&(source_data[i]<source_data[i-8])
//					&&(source_data[i]<source_data[i+1])&&(source_data[i]<source_data[i+2])&&(source_data[i]<source_data[i+3])&&(source_data[i]<source_data[i+4])
//					&&(source_data[i]<source_data[i+5])&&(source_data[i]<source_data[i+6])&&(source_data[i]<source_data[i+7])&&(source_data[i]<source_data[i+8]))
//			{
//				bot_point.push_back(i);
//			}
//		}
//
//		INT pair_pt_size = (top_point.size() <= bot_point.size() ) ? top_point.size() : bot_point.size();
//
//		bool result = true;
//
//		//****************************************************
//		// 1. verify that there are more than 2 top_point and 2 bot_point; (should verify that digital capture's cycle to get more than 4 SSC CLK ramp wave)
//		// 2. verify that sequence of the end point
//		//*****************************************************
//
//		if((top_point.size() < 2) or (bot_point.size() < 2))
//		{
//			result = false;
//			hout(DETAIL) << "WARNING: End Point is not enough, (at last 2 point of top and bot)" << endl;
//		}
//		else
//		{
//			if(top_point[0] < bot_point[0])
//			{
//
//				for (INT i = 1; i < pair_pt_size ; i ++)
//				{
//					if((top_point[i] < bot_point[i-1]) or (top_point[i] >= bot_point[i]))
//						{
//							result = false;
//							hout(DETAIL) << "WARNING: End Points are not the correct sequencer !!" << endl;
//						}
//				}
//
//			}
//			else if (top_point[0] > bot_point[0])
//			{
//
//				for (INT i = 1; i < pair_pt_size ; i ++)
//				{
//					if((bot_point[i] < top_point[i-1]) or (bot_point[i] > top_point[i]))
//					{
//						result = false;
//						hout(DETAIL) << "WARNING: End Points are not the correct sequencer !!" << endl;
//					}
//				}
//			}
//			else
//				result = false;
//		}
//
//		return result;
//	}
	/**
	*This test is invoked per site.
	*/
//	virtual void run()
//	{
//		//=============================================
//		// Common definition of TM for offline flag,
//		// d2s mode, debug mode, test suite name, etc.
//		//=============================================
//		static	STRING          	sTestsuiteName;
//		static	INT					iOffline;
//		static  MACRO_LANE_SEL 		MacroLane_Sel;
//
//		static	MACRO_DOUBLE		INL;
//		static	MACRO_DOUBLE		DNL;
//		static	MACRO_DOUBLE		SSC_Freq;
//		static	MACRO_DOUBLE		Freq_Offset_PPM;
//		static	MACRO_DOUBLE		Freq_UPSpread_PPM;
//		static	MACRO_DOUBLE		Freq_DOWNSpread_PPM;
//
//		ON_FIRST_INVOCATION_BEGIN();
//
//			//=============================================
//			// Variables and MacroLane initialization
//			//=============================================
//			GET_SYSTEM_FLAG		("offline",&iOffline);
//			GET_TESTSUITE_NAME	(sTestsuiteName);
//			hout.setLevel(iPrintLvl);
//			hout.printsuitename(sTestsuiteName);
//			Select_Macro_Lane(MacroLane_Sel,mHiLink16_MacroList,mPinList);
//
//			GetRxPinList(MacroLane_Sel, sPinList_P, sPinList_N, sPinList);
//
//			/*** Connect PSSL AC Relay to DUT ****/
//			if (CP_FT_Program == "FT") {
//				FLEX_RELAY frelay;
//				frelay.pin("pHilink16_TX,pHilink16_RX").set("AC","OFF");
//				frelay.wait(0.3 ms);
//				frelay.execute();
//			}
//
//			//=============================================
//			// Device Setup
//			//=============================================
//			D2S_FRAMEWORK;
//
//			STRING_VECTOR 			vCaptureVars;
//			parseListOfString(mCaptureVars,vCaptureVars,',');
//
//			DIGITAL_CAPTURE_TEST();
//
//			STRING 	sSpecName = "DataRate@pHilink16_TX";
//			DOUBLE 	dOrgVal = Primary.getSpecification().getSpecValue(sSpecName);
//			DOUBLE 	Tsample = (1 / (dOrgVal)) * 2;
//			DOUBLE	Fmax,Fmin,Tmin,Tmax;
//			DOUBLE	PTmin,PTmax;
//			if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 1.5) {
//				Fmax = (CUSTpara.Data_Rate / 2) * (1 + (DOUBLE)2300/1000000);
//				Fmin = (CUSTpara.Data_Rate / 2) * (1 - (DOUBLE)2300/1000000);
//			} else if (CUSTpara.Protocol == "PCIE" && CUSTpara.Data_Rate == 2.5) {
//				Fmax = (CUSTpara.Data_Rate / 2) * (1 + (DOUBLE)0/1000000);
//				Fmin = (CUSTpara.Data_Rate / 2) * (1 - (DOUBLE)5000/1000000);
//			} else if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 3) {
//				Fmax = (CUSTpara.Data_Rate / 2) * (1 + (DOUBLE)2300/1000000);
//				Fmin = (CUSTpara.Data_Rate / 2) * (1 - (DOUBLE)2300/1000000);
//			} else if (CUSTpara.Protocol == "PCIE" && CUSTpara.Data_Rate == 5) {
//				Fmax = (CUSTpara.Data_Rate / 2) * (1 + (DOUBLE)0/1000000);
//				Fmin = (CUSTpara.Data_Rate / 2) * (1 - (DOUBLE)5000/1000000);
//			} else if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 6) {
//				Fmax = (CUSTpara.Data_Rate / 2) * (1 + (DOUBLE)2300/1000000);
//				Fmin = (CUSTpara.Data_Rate / 2) * (1 - (DOUBLE)2300/1000000);
//			} else if (CUSTpara.Protocol == "PCIE" && CUSTpara.Data_Rate == 8) {
//				Fmax = (CUSTpara.Data_Rate / 2) * (1 + (DOUBLE)0/1000000);
//				Fmin = (CUSTpara.Data_Rate / 2) * (1 - (DOUBLE)5000/1000000);
//			} else if(CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 12){
//				Fmax = (CUSTpara.Data_Rate / 2) * (1 + (DOUBLE)1000/1000000);
//				Fmin = (CUSTpara.Data_Rate / 2) * (1 - (DOUBLE)1000/1000000);
//			} else if(CUSTpara.Protocol == "SATA" && CUSTpara.Data_Rate == 1.5){
//				Fmax = (CUSTpara.Data_Rate / 2) * (1 + (DOUBLE)0/1000000);
//				Fmin = (CUSTpara.Data_Rate / 2) * (1 - (DOUBLE)5000/1000000);
//			} else if(CUSTpara.Protocol == "SATA" && CUSTpara.Data_Rate == 3){
//				Fmax = (CUSTpara.Data_Rate / 2) * (1 + (DOUBLE)0/1000000);
//				Fmin = (CUSTpara.Data_Rate / 2) * (1 - (DOUBLE)5000/1000000);
//			} else if(CUSTpara.Protocol == "SATA" && CUSTpara.Data_Rate == 6){
//				Fmax = (CUSTpara.Data_Rate / 2) * (1 + (DOUBLE)0/1000000);
//				Fmin = (CUSTpara.Data_Rate / 2) * (1 - (DOUBLE)5000/1000000);
//			} else {
//				hout(RELEASE) << "Protocol " << CUSTpara.Protocol << " DataRate " << CUSTpara.Data_Rate << " is not a valid option for PCIE/SATA/SAS protocol!!" << endl;
//				_exit(0);
//			}
//
//			Tmin = 1 / Fmax;
//			Tmax = 1 / Fmin;
//			/*  T * (pt + 1) = Ts * pt  */
//			if ((Tsample > Tmin) && (Tsample > Tmax)) {
//				PTmin = Tmin / (Tsample - Tmin);
//				PTmax = Tmax / (Tsample - Tmax);
//				hout (DETAIL) << "Protocol = " << CUSTpara.Protocol << "\tDataRate = " << CUSTpara.Data_Rate << endl;
//				hout (DETAIL) << "Fsample = " << dOrgVal / 2 << " [GHz]" << "\tTsample = " << Tsample << " [ns]" << endl;
//				hout (DETAIL) << "Fmax = " << Fmax << " [GHz]" << "\tTmin = " << Tmin << " [ns]" << endl;
//				hout (DETAIL) << "Fmin = " << Fmin << " [GHz]" << "\tTmax = " << Tmax << " [ns]" << endl;
//				hout (DETAIL) << "PTmin = " << PTmin << "\tPTmax = " << PTmax << endl;
//			} else {
//				hout(RELEASE) << "Tsample = " << Tsample << " which is small than SSC waveform period, plseas adjuest your Sample Rate in Timing" << endl;
//				_exit(0);
//			}
//
//
//
//			MACRO_DOUBLE 		DNL_max_UP,INL_max_UP,DNL_max_DOWN,INL_max_DOWN;
//			DNL_max_UP.init(0.0);
//			INL_max_UP.init(0.0);
//			DNL_max_DOWN.init(0.0);
//			INL_max_DOWN.init(0.0);
//
//			INL.init(0.0);
//			DNL.init(0.0);
//			SSC_Freq.init(0.0);
//			Freq_Offset_PPM.init(0.0);
//			Freq_UPSpread_PPM.init(0.0);
//			Freq_DOWNSpread_PPM.init(0.0);
//
//
//			FOR_EACH_SITE_BEGIN();
//				INT SiteID = CURRENT_SITE_NUMBER() - 1;
//				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//				{
//					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//					ARRAY_I captWfm = VECTOR(vCaptureVars[macroIndex]).getVectors();
//
//					INT wfmSize = captWfm.size();
//					if (hout.getLevel() != 0) {
//						PUT_DEBUG("",vCaptureVars[macroIndex] + "_Waveform",captWfm);
//					}
//
//					//calculate period
//					INT 			state0_num = 0;
//					INT 			state1_num = 0;
//					INT 			changeIndex = 0;
//					INT_VECTOR 		vPeriod;
//					for (INT i = 1; i < wfmSize - 4; i ++) {
//						if (captWfm[i] == 0) {
//							state0_num ++;
//						} else if (captWfm[i] == 1) {
//							state1_num ++;
//						}
//
//						if ((captWfm[i - 1] == 1) && (captWfm[i] == 0) && (captWfm[i + 1] == 0) && (captWfm[i + 2] == 0) && (captWfm[i + 3] == 0) && (captWfm[i + 4] == 0)) {
//							changeIndex ++;
//							INT period = (state0_num + state1_num);
//							if ((period >= (INT)(PTmin - 5)) && (period <= (INT)(PTmax + 5))) {
//								vPeriod.push_back(period);
//							}
//							state0_num = 0;
//							state1_num = 0;
//						}
//					}
//
//					ARRAY_I 			arryPeriod;
//					arryPeriod.resize(vPeriod.size());
//					for (UINT i = 0; i < vPeriod.size(); i ++) {
//						arryPeriod[i] = vPeriod[i];
//					}
//					if (hout.getLevel() != 0) {
//						PUT_DEBUG("",vCaptureVars[macroIndex] + "_ArryPeriod",arryPeriod);
//					}
//					//*********************************
//					// frequency Calculation
//					//*********************************
//					ARRAY_D Frequency;
//					Frequency.resize(vPeriod.size());
//					for (UINT i = 0; i < vPeriod.size(); i ++) {
//						Frequency[i] = ((vPeriod[i] + 1) / (vPeriod[i] * (Tsample ns))) / (1 MHz);
//					}
//
//					if (hout.getLevel() != 0) {
//						PUT_DEBUG("",vCaptureVars[macroIndex] + "_Frequency",Frequency);
//					}
//
//					int average_index = 10;
//					ARRAY_D Frequency_average;
//					Frequency_average.resize(Frequency.size()/average_index);
//					Frequency_average.init(0);
//					Frequency_Average_Calc(Frequency,Frequency_average,average_index);
//
//					hout(DETAIL) << "Total Average point = : " << dec << Frequency_average.size() << endl;
//
//					if (hout.getLevel() != 0) {
//						PUT_DEBUG("",vCaptureVars[macroIndex] + "Frequency_Average",Frequency_average);
//					}
//
//					if (End_point_Varify(Frequency_average)) {
//						//***************************************
//						//1. End point find and slop wave selection
//						//2. Linearity Calc
//						//***************************************
//
//						DOUBLE_VECTOR 		Selected_wave_tmp_UP,Selected_wave_tmp_Down;
//						ARRAY_D 			Selected_wave;
//						LINEARtype 			linear;
//						ARRAY_D 			DNL_tmp,INL_tmp;
//
//						End_point_Calc_Average(Frequency_average,Selected_wave_tmp_UP,1);
//
//						Selected_wave.resize(Selected_wave_tmp_UP.size());
//						for(UINT i = 0; i < Selected_wave_tmp_UP.size(); i ++)
//							Selected_wave[i] = Selected_wave_tmp_UP[i];
//
//						DSP_LINEAR(Selected_wave,&linear,DNL_tmp,INL_tmp,END_PT_LSB);
//						if (hout.getLevel() != 0) {
//							PUT_DEBUG("",vCaptureVars[macroIndex] + "Frequency_Select_wave_UP",Selected_wave);
//							PUT_DEBUG("",vCaptureVars[macroIndex] + "UP_DNL",DNL_tmp);
//							PUT_DEBUG("",vCaptureVars[macroIndex] + "UP_INL",INL_tmp);
//						}
//						DNL_max_UP[SiteID][MacroID] = linear.damax;
//						INL_max_UP[SiteID][MacroID] = linear.iamax;
//
//						End_point_Calc_Average(Frequency_average,Selected_wave_tmp_Down,0);
//						Selected_wave.resize(Selected_wave_tmp_Down.size());
//						for (UINT i = 0; i < Selected_wave_tmp_Down.size(); i ++)
//							Selected_wave[i] = Selected_wave_tmp_Down[i];
//
//						DSP_LINEAR(Selected_wave,&linear,DNL_tmp,INL_tmp,END_PT_LSB);
//						if (hout.getLevel() != 0) {
//							PUT_DEBUG("",vCaptureVars[macroIndex] + "Frequency_Select_wave_DOWN",Selected_wave);
//							PUT_DEBUG("",vCaptureVars[macroIndex] + "DOWN_DNL",DNL_tmp);
//							PUT_DEBUG("",vCaptureVars[macroIndex] + "DOWN_INL",INL_tmp);
//						}
//						DNL_max_DOWN[SiteID][MacroID] = linear.damax;
//						INL_max_DOWN[SiteID][MacroID] = linear.iamax;
//
//
//						//*******************************
//						// SSC Freq Calc
//						//*******************************
//						double 				tmp_freq;
//						double 				total_PT = 0;
//						DOUBLE_VECTOR		period_calc;
//						period_calc.resize(Selected_wave_tmp_Down.size(),0);
//						for (UINT i = 0; i < Selected_wave_tmp_Down.size(); i ++) {
//							period_calc[i] = 1 / ((Tsample ns) * (Selected_wave_tmp_Down[i] MHz) - 1);
//							total_PT += period_calc[i];
//						}
//						period_calc.resize(Selected_wave_tmp_UP.size(),0);
//						for (UINT i = 0; i < Selected_wave_tmp_UP.size(); i ++) {
//							period_calc[i] = 1 / ((Tsample ns) * (Selected_wave_tmp_UP[i] MHz) - 1);
//							total_PT += period_calc[i];
//						}
//						total_PT *= average_index;
//						tmp_freq = ((dOrgVal/2 GHz) / total_PT) * 1e-3;
//
//						SSC_Freq[SiteID][MacroID] = tmp_freq;
//
//						DOUBLE freq_offset_tmp = 0, freq_UPSpread_tmp = 0,freq_DOWNSpread_tmp = 0;
//						if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 1.5) {
//							freq_offset_tmp = ((Selected_wave_tmp_UP[Selected_wave_tmp_UP.size() - 1] + Selected_wave_tmp_Down[0]) / 2
//											+ (Selected_wave_tmp_Down[Selected_wave_tmp_Down.size() - 1] + Selected_wave_tmp_UP[0]) / 2) / 2 - 750;
//							freq_offset_tmp = freq_offset_tmp / 750 * 1e6;
//							freq_UPSpread_tmp = Selected_wave_tmp_Down[0] - 750;
//							freq_UPSpread_tmp = freq_UPSpread_tmp / 750 * 1e6;
//							freq_DOWNSpread_tmp = Selected_wave_tmp_UP[0] - 750;
//							freq_DOWNSpread_tmp = freq_DOWNSpread_tmp / 750 * 1e6;
//						} else if (CUSTpara.Protocol == "PCIE" && CUSTpara.Data_Rate == 2.5) {
//							freq_offset_tmp = ((Selected_wave_tmp_UP[Selected_wave_tmp_UP.size() - 1] + Selected_wave_tmp_Down[0]) / 2
//											+ (Selected_wave_tmp_Down[Selected_wave_tmp_Down.size() - 1] + Selected_wave_tmp_UP[0]) / 2) / 2 - 1246.875;
//							freq_offset_tmp = freq_offset_tmp / 1250 * 1e6;
//							freq_UPSpread_tmp = Selected_wave_tmp_Down[0] - 1250;
//							freq_UPSpread_tmp = freq_UPSpread_tmp / 1250 * 1e6;
//							freq_DOWNSpread_tmp = Selected_wave_tmp_UP[0] - 1250;
//							freq_DOWNSpread_tmp = freq_DOWNSpread_tmp / 1250 * 1e6;
//						} else if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 3) {
//							freq_offset_tmp = ((Selected_wave_tmp_UP[Selected_wave_tmp_UP.size() - 1] + Selected_wave_tmp_Down[0]) / 2
//											+ (Selected_wave_tmp_Down[Selected_wave_tmp_Down.size() - 1] + Selected_wave_tmp_UP[0]) / 2) / 2 - 1500;
//							freq_offset_tmp = freq_offset_tmp / 1500 * 1e6;
//							freq_UPSpread_tmp = Selected_wave_tmp_Down[0] - 1500;
//							freq_UPSpread_tmp = freq_UPSpread_tmp / 1500 * 1e6;
//							freq_DOWNSpread_tmp = Selected_wave_tmp_UP[0] - 1500;
//							freq_DOWNSpread_tmp = freq_DOWNSpread_tmp / 1500 * 1e6;
//						} else if (CUSTpara.Protocol == "PCIE" && CUSTpara.Data_Rate == 5) {
//							freq_offset_tmp = ((Selected_wave_tmp_UP[Selected_wave_tmp_UP.size() - 1] + Selected_wave_tmp_Down[0]) / 2
//											+ (Selected_wave_tmp_Down[Selected_wave_tmp_Down.size() - 1] + Selected_wave_tmp_UP[0]) / 2) / 2 - 2493.75;
//							freq_offset_tmp = freq_offset_tmp / 2500 * 1e6;
//							freq_UPSpread_tmp = Selected_wave_tmp_Down[0] - 2500;
//							freq_UPSpread_tmp = freq_UPSpread_tmp / 2500 * 1e6;
//							freq_DOWNSpread_tmp = Selected_wave_tmp_UP[0] - 2500;
//							freq_DOWNSpread_tmp = freq_DOWNSpread_tmp / 2500 * 1e6;
//						} else if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 6) {
//							freq_offset_tmp = ((Selected_wave_tmp_UP[Selected_wave_tmp_UP.size() - 1] + Selected_wave_tmp_Down[0]) / 2
//											+ (Selected_wave_tmp_Down[Selected_wave_tmp_Down.size() - 1] + Selected_wave_tmp_UP[0]) / 2) / 2 - 3000;
//							freq_offset_tmp = freq_offset_tmp / 3000 * 1e6;
//							freq_UPSpread_tmp = Selected_wave_tmp_Down[0] - 3000;
//							freq_UPSpread_tmp = freq_UPSpread_tmp / 3000 * 1e6;
//							freq_DOWNSpread_tmp = Selected_wave_tmp_UP[0] - 3000;
//							freq_DOWNSpread_tmp = freq_DOWNSpread_tmp / 3000 * 1e6;
//						} else if (CUSTpara.Protocol == "PCIE" && CUSTpara.Data_Rate == 8) {
//							freq_offset_tmp = ((Selected_wave_tmp_UP[Selected_wave_tmp_UP.size() - 1] + Selected_wave_tmp_Down[0]) / 2
//											+ (Selected_wave_tmp_Down[Selected_wave_tmp_Down.size() - 1] + Selected_wave_tmp_UP[0]) / 2) / 2 - 3990;
//							freq_offset_tmp = freq_offset_tmp / 4000 * 1e6;
//							freq_UPSpread_tmp = Selected_wave_tmp_Down[0] - 4000;
//							freq_UPSpread_tmp = freq_UPSpread_tmp / 4000 * 1e6;
//							freq_DOWNSpread_tmp = Selected_wave_tmp_UP[0] - 4000;
//							freq_DOWNSpread_tmp = freq_DOWNSpread_tmp / 4000 * 1e6;
//						} else if(CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 12){
//							freq_offset_tmp = ((Selected_wave_tmp_UP[Selected_wave_tmp_UP.size() - 1] + Selected_wave_tmp_Down[0]) / 2
//											+ (Selected_wave_tmp_Down[Selected_wave_tmp_Down.size() - 1] + Selected_wave_tmp_UP[0]) / 2) / 2 - 6000;
//							freq_offset_tmp = freq_offset_tmp / 6000 * 1e6;
//							freq_UPSpread_tmp = Selected_wave_tmp_Down[0] - 6000;
//							freq_UPSpread_tmp = freq_UPSpread_tmp / 6000 * 1e6;
//							freq_DOWNSpread_tmp = Selected_wave_tmp_UP[0] - 6000;
//							freq_DOWNSpread_tmp = freq_DOWNSpread_tmp / 6000 * 1e6;
//						} else if (CUSTpara.Protocol == "SATA" && CUSTpara.Data_Rate == 1.5) {
//							freq_offset_tmp = ((Selected_wave_tmp_UP[Selected_wave_tmp_UP.size() - 1] + Selected_wave_tmp_Down[0]) / 2
//											+ (Selected_wave_tmp_Down[Selected_wave_tmp_Down.size() - 1] + Selected_wave_tmp_UP[0]) / 2) / 2 - 748.125;
//							freq_offset_tmp = freq_offset_tmp / 750 * 1e6;
//							freq_UPSpread_tmp = Selected_wave_tmp_Down[0] - 750;
//							freq_UPSpread_tmp = freq_UPSpread_tmp / 750 * 1e6;
//							freq_DOWNSpread_tmp = Selected_wave_tmp_UP[0] - 750;
//							freq_DOWNSpread_tmp = freq_DOWNSpread_tmp / 750 * 1e6;
//						} else if (CUSTpara.Protocol == "SATA" && CUSTpara.Data_Rate == 3) {
//							freq_offset_tmp = ((Selected_wave_tmp_UP[Selected_wave_tmp_UP.size() - 1] + Selected_wave_tmp_Down[0]) / 2
//											+ (Selected_wave_tmp_Down[Selected_wave_tmp_Down.size() - 1] + Selected_wave_tmp_UP[0]) / 2) / 2 - 1496.25;
//							freq_offset_tmp = freq_offset_tmp / 1500 * 1e6;
//							freq_UPSpread_tmp = Selected_wave_tmp_Down[0] - 1500;
//							freq_UPSpread_tmp = freq_UPSpread_tmp / 1500 * 1e6;
//							freq_DOWNSpread_tmp = Selected_wave_tmp_UP[0] - 1500;
//							freq_DOWNSpread_tmp = freq_DOWNSpread_tmp / 1500 * 1e6;
//						} else if (CUSTpara.Protocol == "SATA" && CUSTpara.Data_Rate == 6) {
//							freq_offset_tmp = ((Selected_wave_tmp_UP[Selected_wave_tmp_UP.size() - 1] + Selected_wave_tmp_Down[0]) / 2
//											+ (Selected_wave_tmp_Down[Selected_wave_tmp_Down.size() - 1] + Selected_wave_tmp_UP[0]) / 2) / 2 - 2992.5;
//							freq_offset_tmp = freq_offset_tmp / 3000 * 1e6;
//							freq_UPSpread_tmp = Selected_wave_tmp_Down[0] - 3000;
//							freq_UPSpread_tmp = freq_UPSpread_tmp / 3000 * 1e6;
//							freq_DOWNSpread_tmp = Selected_wave_tmp_UP[0] - 3000;
//							freq_DOWNSpread_tmp = freq_DOWNSpread_tmp / 3000 * 1e6;
//						} else {
//							hout(RELEASE) << "Protocol " << CUSTpara.Protocol << " DataRate " << CUSTpara.Data_Rate << " is not a valid option for PCIE/SAS/SATA protocol!!" << endl;
//							_exit(0);
//						}
//						Freq_Offset_PPM[SiteID][MacroID] = freq_offset_tmp;
//						Freq_UPSpread_PPM[SiteID][MacroID] = freq_UPSpread_tmp;
//						Freq_DOWNSpread_PPM[SiteID][MacroID] = freq_DOWNSpread_tmp;
//					}
//
//				}
//			FOR_EACH_SITE_END();
//
//
//
//			FOR_EACH_SITE_BEGIN();
//				INT SiteID = CURRENT_SITE_NUMBER() - 1;
//				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//				{
//					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//					if (DNL_max_UP[SiteID][MacroID] >= DNL_max_DOWN[SiteID][MacroID]) {
//						DNL[SiteID][MacroID] = DNL_max_UP[SiteID][MacroID];
//					} else {
//						DNL[SiteID][MacroID] = DNL_max_DOWN[SiteID][MacroID];
//					}
//					if (INL_max_UP[SiteID][MacroID] >= INL_max_DOWN[SiteID][MacroID]) {
//						INL[SiteID][MacroID] = INL_max_UP[SiteID][MacroID];
//					} else {
//						INL[SiteID][MacroID] = INL_max_DOWN[SiteID][MacroID];
//					}
//				}
//			FOR_EACH_SITE_END();
//
//			FOR_EACH_SITE_BEGIN();
//				INT SiteID = CURRENT_SITE_NUMBER() - 1;
//				for (UINT macroIndex = 0; macroIndex < MacroLane_Sel.size(); macroIndex ++)
//				{
//					UINT MacroID = MacroLane_Sel[macroIndex].MacroID;
//					if (iOffline) {
//						DNL[SiteID][MacroID] = 2;
//						INL[SiteID][MacroID] = 2;
//						SSC_Freq[SiteID][MacroID] = 32;
//						Freq_Offset_PPM[SiteID][MacroID] = 0;
//
//						if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 1.5) {
//							Freq_UPSpread_PPM[SiteID][MacroID] = 2300;
//							Freq_DOWNSpread_PPM[SiteID][MacroID] = -2300;
//						} else if (CUSTpara.Protocol == "PCIE" && CUSTpara.Data_Rate == 2.5) {
//							Freq_UPSpread_PPM[SiteID][MacroID] = 0;
//							Freq_DOWNSpread_PPM[SiteID][MacroID] = -5000;
//						} else if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 3) {
//							Freq_UPSpread_PPM[SiteID][MacroID] = 2300;
//							Freq_DOWNSpread_PPM[SiteID][MacroID] = -2300;
//						} else if (CUSTpara.Protocol == "PCIE" && CUSTpara.Data_Rate == 5) {
//							Freq_UPSpread_PPM[SiteID][MacroID] = 0;
//							Freq_DOWNSpread_PPM[SiteID][MacroID] = -5000;
//						} else if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 6) {
//							Freq_UPSpread_PPM[SiteID][MacroID] = 2300;
//							Freq_DOWNSpread_PPM[SiteID][MacroID] = -2300;
//						} else if (CUSTpara.Protocol == "PCIE" && CUSTpara.Data_Rate == 8) {
//							Freq_UPSpread_PPM[SiteID][MacroID] = 0;
//							Freq_DOWNSpread_PPM[SiteID][MacroID] = -5000;
//						} else if (CUSTpara.Protocol == "SAS" && CUSTpara.Data_Rate == 12) {
//							Freq_UPSpread_PPM[SiteID][MacroID] = 1000;
//							Freq_DOWNSpread_PPM[SiteID][MacroID] = -1000;
//						} else {
//							cerr << "Protocol " << CUSTpara.Protocol << " DataRate " << CUSTpara.Data_Rate << " is not a valid option for PCIE/SAS protocol!!" << endl;
//							_exit(0);
//						}
//					}
//				}
//			FOR_EACH_SITE_END();
//
//
//		ON_FIRST_INVOCATION_END();
//
//		//=============================================
//		// Datalog
//		//=============================================
//		HiLink_PerMacro_Judge(MacroLane_Sel, "DNL", DNL, PIN_TXP);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "INL", INL, PIN_TXP);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "SSC_Freq", SSC_Freq, PIN_TXP);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "SSC_Offset_PPM", Freq_Offset_PPM, PIN_TXP);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "SSC_UPSpread_PPM", Freq_UPSpread_PPM, PIN_TXP);
//		HiLink_PerMacro_Judge(MacroLane_Sel, "SSC_DOWNSpread_PPM", Freq_DOWNSpread_PPM, PIN_TXP);
//
//		return;
//    }

	/**
	*This function will be invoked once the specified parameter's value is changed.
	*@param parameterIdentifier
	*/
//	virtual void postParameterChange(const string& parameterIdentifier)
//	{
//		//Add your code
//		//Note: Test Method API should not be used in this method!
//		bool visible = (mHiLink16_MacroList == "FromPinList");
//		getParameter("PinList").setVisible(visible);
//
//
//		return;
//	}
//
//  /**
//   *This function will be invoked once the Select Test Method Dialog is opened.
//   */
//  virtual const string getComment() const
//  {
//    string comment = " please add your comment for this method.";
//    return comment;
//  }
};
REGISTER_TESTCLASS("SSC_CLK_ATE", SSC_CLK_ATE);
