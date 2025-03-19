// Fill out your copyright notice in the Description page of Project Settings.


#include "SPCameraManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/MessageDialog.h"
#include <string>

#include "ImageUtils.h"

//#define UpdateResource UpdateResource
#pragma   warning(disable: 4996)//忽略被否决的警告
//时间解析宏定义
#define GET_YEAR(_time_)     (((_time_)>>26) + 2000) 
#define GET_MONTH(_time_)    (((_time_)>>22) & 15)
#define GET_DAY(_time_)      (((_time_)>>17) & 31)
#define GET_HOUR(_time_)     (((_time_)>>12) & 31) 
#define GET_MINUTE(_time_)   (((_time_)>>6)  & 63)
#define GET_SECOND(_time_)   (((_time_)>>0)  & 63)


TArray<char*> GHardDiskVideoBuf;
TArray<long> GHardDiskVideoType;
TArray<long> GHardDiskVideoSize;
TArray<int> GHardDiskVideoWidth;
TArray<int> GHardDiskVideoHeight;
 
//从视频文件获取封面
void USPCameraManager::SaveJPEGFromMovie(const FString& sImageSavePath)
{
	/*FString szMsg = sMovieFullPath;
	TCHAR* pSendData = szMsg.GetCharArray().GetData();
	int32 nDataLen = FCString::Strlen(pSendData);
	char* sDest = new char[sizeof(char) * nDataLen];
	TcharToChar(pSendData, sDest);
	std::string sPath = sDest;
	delete[]sDest;*/
	AVFormatContext *pFormatCtx = avformat_alloc_context();
	int res;
	std::string sPath = TCHAR_TO_UTF8(*sImageSavePath);
	res = avformat_open_input(&pFormatCtx, sPath.c_str(), nullptr, nullptr);
	if (res) {
		return;
	}
	avformat_find_stream_info(pFormatCtx, nullptr);
	int videoStream = -1;
	for (int i = 0; i < (int)(pFormatCtx->nb_streams); i++) {
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStream = i;
			break;
		}
	}
	if (videoStream == -1) {
		return;
	}
	AVCodecContext *pCodecCtxOrig = nullptr;
	// Get a pointer to the codec context for the video stream
	pCodecCtxOrig = pFormatCtx->streams[videoStream]->codec;
	AVCodec *pCodec = nullptr;
	// Find the decoder for the video stream
	pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);
	if (pCodec == nullptr) {
		fprintf(stderr, "Unsupported codec!\n");
		return; // Codec not found
	}
	AVCodecContext *pCodecCtx = nullptr;
	// Copy context
	pCodecCtx = avcodec_alloc_context3(pCodec);
	if (avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
		fprintf(stderr, "Couldn't copy codec context");
		return; // Error copying codec context
	}
	// Open codec
	if (avcodec_open2(pCodecCtx, pCodec, nullptr) < 0) {
		return;// Could not open codec
	}
	AVFrame *pFrameRGB = nullptr;
	pFrameRGB = av_frame_alloc();
	res = av_seek_frame(pFormatCtx, -1, 10 * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);//10(second)
	if (res < 0) {
		return;
	}
	AVPacket packet;
	while (1) {
		av_read_frame(pFormatCtx, &packet);
		if (packet.stream_index == videoStream) {
			res = avcodec_send_packet(pCodecCtx, &packet);
			int gotPicture = avcodec_receive_frame(pCodecCtx, pFrameRGB); //gotPicture = 0 success, a frame was returned
			if (gotPicture == 0) {
				SwsContext* swsContext = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, (AVPixelFormat)AV_PIX_FMT_RGB24,
					SWS_BICUBIC, nullptr, nullptr, nullptr);
				AVFrame* frameRGB = av_frame_alloc();
				avpicture_alloc((AVPicture*)frameRGB, (AVPixelFormat)AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
				sws_scale(swsContext, pFrameRGB->data, pFrameRGB->linesize, 0, pCodecCtx->height, frameRGB->data, frameRGB->linesize);
				saveMovieAsJPEG(pFrameRGB, pCodecCtx->width, pCodecCtx->height, 10, sImageSavePath);
				avformat_close_input(&pFormatCtx);
				return;
			}
		}
	}
}
 
int USPCameraManager::saveMovieAsJPEG(AVFrame* pFrame, int width, int height, int index, FString sName)
{
	char out_file[256] = { 0 };
	sprintf_s(out_file, sizeof(out_file), "%s%d.jpg", "", index);
	sName.Append(".jpg");
	std::string cstr(TCHAR_TO_UTF8(*sName));
 
	AVFormatContext* pFormatCtx = avformat_alloc_context();
	pFormatCtx->oformat = av_guess_format("mjpeg", nullptr, nullptr);
	if (avio_open(&pFormatCtx->pb, cstr.c_str(), AVIO_FLAG_READ_WRITE) < 0)
	{
		printf("Couldn't open output file.");
		return -1;
	}
	AVStream* pAVStream = avformat_new_stream(pFormatCtx, 0);
	if (pAVStream == nullptr)
	{
		return -1;
	}
	AVCodecContext* pCodecCtx = pAVStream->codec;
	pCodecCtx->codec_id = pFormatCtx->oformat->video_codec;
	pCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
	pCodecCtx->pix_fmt = (AVPixelFormat)AV_PIX_FMT_YUVJ420P;
	pCodecCtx->width = width;
	pCodecCtx->height = height;
	pCodecCtx->time_base.num = 1;
	pCodecCtx->time_base.den = 25;
	//打印输出相关信息
	av_dump_format(pFormatCtx, 0, out_file, 1);
	//================================== 查找编码器 ==================================//
	AVCodec* pCodec = avcodec_find_encoder(pCodecCtx->codec_id);
	if (!pCodec)
	{
		printf("Codec not found.");
		return -1;
	}
	if (avcodec_open2(pCodecCtx, pCodec, nullptr) < 0)
	{
		printf("Could not open codec.");
		return -1;
	}
	//================================Write Header ===============================//
	avformat_write_header(pFormatCtx, nullptr);
	int y_size = pCodecCtx->width * pCodecCtx->height;
	AVPacket pkt;
	av_new_packet(&pkt, y_size * 3);
 
	//
	int got_picture = 0;
	int ret = avcodec_encode_video2(pCodecCtx, &pkt, pFrame, &got_picture);
	if (ret < 0)
	{
		printf("Encode Error.\n");
		return -1;
	}
	if (got_picture == 1)
	{
		pkt.stream_index = pAVStream->index;
		ret = av_write_frame(pFormatCtx, &pkt);
	}
	av_free_packet(&pkt);
	av_write_trailer(pFormatCtx);
	if (pAVStream)
	{
		avcodec_close(pAVStream->codec);
	}
	avio_close(pFormatCtx->pb);
	avformat_free_context(pFormatCtx);
	return 0;
}
 
/*
*	使用FFmpeg库来进行图片数据, 速度是所有转换里面最快的.需要注意的是UE4是RGB32而不是RGB24, 如果用RGB24你会发现怎么转都不对.卡了半天
*	转换效率的对比, 尝试过的方法和时间
	Method					Time(ms)
	YV12ToBGR24_Native		83.7263
	YV12ToBGR24_Table		54.2376
	YV12ToBGR24_OpenCV		26.0529
	YV12ToBGR24_FFmpeg		3.41499
	YV12ToBGR24_Pinknoise	14.1215
*	https://www.cnblogs.com/yuandaozhe/p/5766717.html
*	ffmpeg集成:https://www.cnblogs.com/xiexinbei0318/p/11426110.html  &  https://ffmpeg.zeranoe.com/builds/
*	https://blog.csdn.net/shangtao1989/article/details/50260661		https://www.cnblogs.com/dwdxdy/p/3713990.html 使用ffmpeg解码的贴子
*	注意这里ffmpeg会出现函数被否决,需要用新接口替换,也可以忽略这个警告,并且头文件需要用extern "C"包含
*	extern "C"
*	{
*		#include <libavcodec\avcodec.h>
*		#include <libswscale\swscale.h>
*		#include <libavutil\pixfmt.h>
*		#include <libavutil\imgutils.h>
*	}
*	#pragma   warning(disable: 4996)//忽略被否决的警告
*/
bool YV12ToBGR32_FFmpeg(unsigned char* pYUV, unsigned char* pBGR24, int width, int height)
{
	if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
		return false;
	AVPicture pFrameYUV, pFrameBGR;
	avpicture_fill(&pFrameYUV, pYUV, (AVPixelFormat)AV_PIX_FMT_YUV420P, width, height);
	//U,V互换
	uint8_t * ptmp = pFrameYUV.data[1];
	pFrameYUV.data[1] = pFrameYUV.data[2];
	pFrameYUV.data[2] = ptmp;
	avpicture_fill(&pFrameBGR, pBGR24, (AVPixelFormat)AV_PIX_FMT_BGRA, width, height);
 
	struct SwsContext* imgCtx = NULL;
	imgCtx = sws_getContext(width, height, (AVPixelFormat)AV_PIX_FMT_YUV420P, width, height, (AVPixelFormat)AV_PIX_FMT_BGRA, SWS_BILINEAR, 0, 0, 0);
 
	if (imgCtx != NULL) {
		sws_scale(imgCtx, pFrameYUV.data, pFrameYUV.linesize, 0, height, pFrameBGR.data, pFrameBGR.linesize);
		if (imgCtx) {
			sws_freeContext(imgCtx);
			imgCtx = NULL;
		}
		return true;
	}
	else {
		sws_freeContext(imgCtx);
		imgCtx = NULL;
		return false;
	}
}

BOOL YV12ToBGR24_FFmpeg(unsigned char* pYUV,unsigned char* pBGR24,int width,int height)
{
	if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
		return false;
 
	AVPicture pFrameYUV, pFrameBGR;
	avpicture_fill(&pFrameYUV, pYUV, AV_PIX_FMT_YUV420P, width, height);
	avpicture_fill(&pFrameBGR, pBGR24, AV_PIX_FMT_BGR24, width, height);
 
	struct SwsContext* imgCtx = NULL;
	imgCtx = sws_getContext(width, height, AV_PIX_FMT_YUV420P, width, height, AV_PIX_FMT_BGR24, SWS_BILINEAR, 0, 0, 0);
 
	if (imgCtx != NULL)
	{
		sws_scale(imgCtx, pFrameYUV.data, pFrameYUV.linesize, 0, height, pFrameBGR.data, pFrameBGR.linesize);
		if(imgCtx)
		{
			sws_freeContext(imgCtx);
			imgCtx = NULL;
		}
 
		return true;
	}
	else
	{
		sws_freeContext(imgCtx);
		imgCtx = NULL;
		return false;
	}
}



// int iPicNum=0;//Set channel NO.
// FILE *Videofile=NULL;
// FILE *Audiofile=NULL;
// char filename[100];
//////////////////////////////////////////////////////////////////////////
////解码回调 视频为YUV数据(YV12)，音频为PCM数据
void CALLBACK g_DecCBFun(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2)
{
	//GHardDiskVideoPort.Add(nPort);
	GHardDiskVideoBuf.Add(pBuf);
	GHardDiskVideoSize.Add(nSize);
	//PFrameInfo = pFrameInfo;
	GHardDiskVideoWidth.Add(pFrameInfo->nWidth);
	GHardDiskVideoHeight.Add(pFrameInfo->nHeight);
	//GHardDiskVideoStamp.Add(pFrameInfo->nStamp);
	GHardDiskVideoType.Add(pFrameInfo->nType);
	//GHardDiskVideoFrameRate.Add(pFrameInfo->nFrameRate);
	//GHardDiskVideoFrameNum.Add(pFrameInfo->dwFrameNum);
	//GHardDiskVideoReserved1.Add(nReserved1);
	//GHardDiskVideoReserved2.Add(nReserved2);
	
	// long lFrameType = pFrameInfo->nType;	
	// if (lFrameType ==T_AUDIO16)
	// {
	// 	UE_LOG(LogTemp,Log,TEXT("Audio nStamp:%d\n",pFrameInfo->nStamp));
	// 	UE_LOG(LogTemp,Log,TEXT("test_DecCb_Write Audio16 \n"));
	// 	if (Audiofile==NULL)
	// 	{
	// 		sprintf_s(filename,"AudionPCM.pcm",iPicNum);
	// 		Audiofile = fopen(filename,"wb");
	// 	}
	// 	fwrite(pBuf,nSize,1,Audiofile);
	// }
	//
	// else if(lFrameType ==T_YV12)
	// {		
	// 	UE_LOG(LogTemp,Log,TEXT("Video nStamp:%d\n",pFrameInfo->nStamp));
	// 	UE_LOG(LogTemp,Log,TEXT("test_DecCb_Write YUV \n"));
	// 	if (Videofile==NULL)
	// 	{
	// 		sprintf_s(filename,"VideoYV12.yuv",iPicNum);
	// 		Videofile = fopen(filename,"wb");
	// 	}
	// 	fwrite(pBuf,nSize,1,Videofile);
	// }
	// else
	// {
	//
	// }
}
 
/*********************************************************
  Function:	g_RealDataCallBack_V30
  Desc:		use the player interface to decode the stream
  Input:	lRealHandle, player port;
			dwDataType,data type;
			pBuffer, stream data;
			dwBufSize, data length;
			pUser, user data,here is the current play output window index;
  Output:
  Return:
**********************************************************/
static LONG nGetPort = -1;

void CALLBACK g_RealDataCallBack(LONG IRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, /*DWORD aaa*/void* pUser)
{
	//DWORD dRet = 0;
	bool inData = false;
 
	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:
		//一一对应PlayM4_Play/PlayM4_OpenStream/PlayM4_GetPort.不调用的话会有内存泄漏, 天坑, 海康威视文档连个介绍都没有
		/*PlayM4_StopSound();*/
		// PlayM4_Stop(nGetPort);
		// PlayM4_CloseStream(nGetPort);
		// PlayM4_FreePort(nGetPort);
 
		if (!PlayM4_GetPort(&nGetPort))
		{
			break;
		}
		if (!PlayM4_OpenStream(nGetPort,pBuffer,dwBufSize,1024*1024))
		{
			//dRet=PlayM4_GetLastError(nGetPort);
			break;
		}
		//if (dwBufSize > 0)
		//{
		//设置解码回调函数 解码且显示
		// if (!PlayM4_SetStreamOpenMode(nGetPort, STREAME_REALTIME))
		// {
		// 	break;
		// }
 
		// if (!PlayM4_OpenStream(nGetPort, pBuffer, dwBufSize, 1024 * 1024))
		// {
		// 	//dRet = PlayM4_GetLastError(nPort);
		// 	break;
		// }

		if (!PlayM4_SetDecCallBack(nGetPort, g_DecCBFun))
		{
			//dRet = PlayM4_GetLastError(nPort);
			break;
		}
		
		//打开视频解码
		if (!PlayM4_Play(nGetPort, NULL))
		{
			//dRet = PlayM4_GetLastError(nPort);
			break;
		}
 
		//打开音频解码, 需要码流是复合流
		if (!PlayM4_PlaySound(nGetPort))
		{
			//dRet = PlayM4_GetLastError(nPort);
			break;
		}
		//}
		break;
		
	case NET_DVR_STREAMDATA:
		//if (dwBufSize > 0 && nGetPort != -1)
		//{
			inData = PlayM4_InputData(nGetPort, pBuffer, dwBufSize);
			while (!inData)
			{
				Sleep(10);
				inData = PlayM4_InputData(nGetPort, pBuffer, dwBufSize);
				UE_LOG(LogTemp,Log,TEXT("PlayM4_InputData faild %d\n"), PlayM4_GetLastError(nGetPort));
			}
		//}
		break;
	default:
		//{
			inData = PlayM4_InputData(nGetPort, pBuffer, dwBufSize);
			while (!inData)
			{
				Sleep(10);
				inData = PlayM4_InputData(nGetPort, pBuffer, dwBufSize);
				UE_LOG(LogTemp,Log,TEXT("PlayM4_InputData failed 2\n"));
			}
			break;
		//}
	}
}

 
void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
	//char tempbuf[256] = { 0 };
	switch (dwType)
	{
	case EXCEPTION_RECONNECT:    //预览时重连
		//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("HaiKangWeiShi SDK TIPS_g_ExceptionCallBack EXCEPTION_RECONNECT")));
		//printf("----------reconnect--------%d\n", time(NULL));
		break;
	default:
		break;
	}
}

void CALLBACK GetThermInfoCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
	{
		NET_DVR_THERMOMETRY_UPLOAD struThermometry = { 0 };
		memcpy(&struThermometry, lpBuffer, sizeof(NET_DVR_THERMOMETRY_UPLOAD));

		NET_DVR_TIME struAbsTime = { 0 };
		struAbsTime.dwYear = GET_YEAR(struThermometry.dwAbsTime);
		struAbsTime.dwMonth = GET_MONTH(struThermometry.dwAbsTime);
		struAbsTime.dwDay = GET_DAY(struThermometry.dwAbsTime);
		struAbsTime.dwHour = GET_HOUR(struThermometry.dwAbsTime);
		struAbsTime.dwMinute = GET_MINUTE(struThermometry.dwAbsTime);
		struAbsTime.dwSecond = GET_SECOND(struThermometry.dwAbsTime);

		/*printf("实时测温结果:byRuleID[%d]wPresetNo[%d]byRuleCalibType[%d]byThermometryUnit[%d]byDataType[%d]dwAbsTime[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]\n",
			struThermometry.byRuleID, struThermometry.wPresetNo, struThermometry.byRuleCalibType, struThermometry.byThermometryUnit,
			struThermometry.byDataType, struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond);*/

		UE_LOG(LogTemp, Log, TEXT("实时测温结果:byRuleID[%d]wPresetNo[%d]byRuleCalibType[%d]byThermometryUnit[%d]byDataType[%d]dwAbsTime[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]\n"),
			struThermometry.byRuleID, struThermometry.wPresetNo, struThermometry.byRuleCalibType, struThermometry.byThermometryUnit,
			struThermometry.byDataType, struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, struAbsTime.dwHour, struAbsTime.dwMinute, struAbsTime.dwSecond);

		//点测温
		if (struThermometry.byRuleCalibType == 0)
		{
			UE_LOG(LogTemp, Log, TEXT("点测温信息:fTemperature[%f]\n"), struThermometry.struPointThermCfg.fTemperature);
			//printf("点测温信息:fTemperature[%f]\n", struThermometry.struPointThermCfg.fTemperature);
		}

		//框/线测温
		if ((struThermometry.byRuleCalibType == 1) || (struThermometry.byRuleCalibType == 2))
		{
			UE_LOG(LogTemp, Log, TEXT("框/线测温信息:fMaxTemperature[%f]fMinTemperature[%f]fAverageTemperature[%f]fTemperatureDiff[%f]\n"),
				struThermometry.struLinePolygonThermCfg.fMaxTemperature, struThermometry.struLinePolygonThermCfg.fMinTemperature,
				struThermometry.struLinePolygonThermCfg.fAverageTemperature, struThermometry.struLinePolygonThermCfg.fTemperatureDiff);
			/*printf("框/线测温信息:fMaxTemperature[%f]fMinTemperature[%f]fAverageTemperature[%f]fTemperatureDiff[%f]\n",
				struThermometry.struLinePolygonThermCfg.fMaxTemperature, struThermometry.struLinePolygonThermCfg.fMinTemperature,
				struThermometry.struLinePolygonThermCfg.fAverageTemperature, struThermometry.struLinePolygonThermCfg.fTemperatureDiff);*/
		}
	}
	else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
	{
		DWORD dwStatus = *(DWORD*)lpBuffer;
		if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
		{
			UE_LOG(LogTemp, Log, TEXT("dwStatus:NET_SDK_CALLBACK_STATUS_SUCCESS\n"));
			//printf("dwStatus:NET_SDK_CALLBACK_STATUS_SUCCESS\n");
		}
		else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
		{
			DWORD dwErrCode = *(DWORD*)((char*)lpBuffer + 4);
			UE_LOG(LogTemp, Log, TEXT("NET_DVR_GET_MANUALTHERM_INFO failed, Error code %d\n"), dwErrCode);
			//printf("NET_DVR_GET_MANUALTHERM_INFO failed, Error code %d\n", dwErrCode);
		}
	}
}

BOOL CALLBACK MessageCallback(LONG lCommand, NET_DVR_ALARMER* pAlarmer, char* pAlarmInfo, DWORD dwBufLen, void* pUser)
{

	switch (lCommand)
	{
	case COMM_THERMOMETRY_ALARM: //温度预警或者温度报警
	{
		NET_DVR_THERMOMETRY_ALARM struThermometryAlarm = { 0 };
		memcpy(&struThermometryAlarm, pAlarmInfo, sizeof(NET_DVR_THERMOMETRY_ALARM));
		if (0 == struThermometryAlarm.byRuleCalibType)
		{
			UE_LOG(LogTemp, Log, TEXT("点测温: Channel:%d, RuleID:%d, ThermometryUnit:%d, PresetNo:%d, RuleTemperature:%.1f, CurrTemperature:%.1f, PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], AlarmLevel:%d, AlarmType:%d, AlarmRule:%d, RuleCalibType:%d,  Point[x:%f, y:%f], PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d"), struThermometryAlarm.dwChannel, struThermometryAlarm.byRuleID, struThermometryAlarm.byThermometryUnit, struThermometryAlarm.wPresetNo, struThermometryAlarm.fRuleTemperature, struThermometryAlarm.fCurrTemperature, struThermometryAlarm.struPtzInfo.fPan, struThermometryAlarm.struPtzInfo.fTilt, struThermometryAlarm.struPtzInfo.fZoom, struThermometryAlarm.byAlarmLevel, struThermometryAlarm.byAlarmType, struThermometryAlarm.byAlarmRule, struThermometryAlarm.byRuleCalibType, struThermometryAlarm.struPoint.fX, struThermometryAlarm.struPoint.fY, struThermometryAlarm.dwPicLen, struThermometryAlarm.dwThermalPicLen, struThermometryAlarm.dwThermalInfoLen);
			//printf("点测温: Channel:%d, RuleID:%d, ThermometryUnit:%d, PresetNo:%d, RuleTemperature:%.1f, CurrTemperature:%.1f, PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], AlarmLevel:%d, AlarmType:%d, AlarmRule:%d, RuleCalibType:%d,  Point[x:%f, y:%f], PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d", struThermometryAlarm.dwChannel, struThermometryAlarm.byRuleID, struThermometryAlarm.byThermometryUnit, struThermometryAlarm.wPresetNo, struThermometryAlarm.fRuleTemperature, struThermometryAlarm.fCurrTemperature, struThermometryAlarm.struPtzInfo.fPan, struThermometryAlarm.struPtzInfo.fTilt, struThermometryAlarm.struPtzInfo.fZoom, struThermometryAlarm.byAlarmLevel, struThermometryAlarm.byAlarmType, struThermometryAlarm.byAlarmRule, struThermometryAlarm.byRuleCalibType, struThermometryAlarm.struPoint.fX, struThermometryAlarm.struPoint.fY, struThermometryAlarm.dwPicLen, struThermometryAlarm.dwThermalPicLen, struThermometryAlarm.dwThermalInfoLen);
		}
		else if (1 == struThermometryAlarm.byRuleCalibType || 2 == struThermometryAlarm.byRuleCalibType)
		{
			int iPointNum = struThermometryAlarm.struRegion.dwPointNum;
			for (int i = 0; i < iPointNum; i++)
			{
				float fX = struThermometryAlarm.struRegion.struPos[i].fX;
				float fY = struThermometryAlarm.struRegion.struPos[i].fY;
				UE_LOG(LogTemp, Log, TEXT("测温区域坐标点:X%d:%f,Y%d:%f;"), iPointNum + 1, fX, iPointNum + 1, fY);
				//printf("测温区域坐标点:X%d:%f,Y%d:%f;", iPointNum + 1, fX, iPointNum + 1, fY);
			}
			UE_LOG(LogTemp, Log, TEXT("线测温或者框测温: Channel:%d, RuleID:%d,HighestPoint[x:%f, y:%f],ThermometryUnit:%d, PresetNo:%d, RuleTemperature:%.1f, CurrTemperature:%.1f, PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], AlarmLevel:%d, AlarmType:%d, AlarmRule:%d, RuleCalibType:%d, PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d"), struThermometryAlarm.dwChannel, struThermometryAlarm.byRuleID,
				struThermometryAlarm.struHighestPoint.fX, struThermometryAlarm.struHighestPoint.fY,
				struThermometryAlarm.byThermometryUnit, struThermometryAlarm.wPresetNo, struThermometryAlarm.fRuleTemperature, struThermometryAlarm.fCurrTemperature,
				struThermometryAlarm.struPtzInfo.fPan, struThermometryAlarm.struPtzInfo.fTilt, struThermometryAlarm.struPtzInfo.fZoom, struThermometryAlarm.byAlarmLevel, struThermometryAlarm.byAlarmType, struThermometryAlarm.byAlarmRule, struThermometryAlarm.byRuleCalibType, struThermometryAlarm.dwPicLen, struThermometryAlarm.dwThermalPicLen, struThermometryAlarm.dwThermalInfoLen);

			/*printf("线测温或者框测温: Channel:%d, RuleID:%d,HighestPoint[x:%f, y:%f],ThermometryUnit:%d, PresetNo:%d, RuleTemperature:%.1f, CurrTemperature:%.1f, PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], AlarmLevel:%d, AlarmType:%d, AlarmRule:%d, RuleCalibType:%d, PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d", struThermometryAlarm.dwChannel, struThermometryAlarm.byRuleID,
				struThermometryAlarm.struHighestPoint.fX, struThermometryAlarm.struHighestPoint.fY,
				struThermometryAlarm.byThermometryUnit, struThermometryAlarm.wPresetNo, struThermometryAlarm.fRuleTemperature, struThermometryAlarm.fCurrTemperature,
				struThermometryAlarm.struPtzInfo.fPan, struThermometryAlarm.struPtzInfo.fTilt, struThermometryAlarm.struPtzInfo.fZoom, struThermometryAlarm.byAlarmLevel, struThermometryAlarm.byAlarmType, struThermometryAlarm.byAlarmRule, struThermometryAlarm.byRuleCalibType, struThermometryAlarm.dwPicLen, struThermometryAlarm.dwThermalPicLen, struThermometryAlarm.dwThermalInfoLen);
		*/}
		break;
	}

	case COMM_THERMOMETRY_DIFF_ALARM: //温差报警
	{
		NET_DVR_THERMOMETRY_DIFF_ALARM struThermometryDiffAlarm = { 0 };
		memcpy(&struThermometryDiffAlarm, pAlarmInfo, sizeof(NET_DVR_THERMOMETRY_DIFF_ALARM));
		if (0 == struThermometryDiffAlarm.byRuleCalibType)
		{
			UE_LOG(LogTemp, Log, TEXT("温差报警: Channel:%d, AlarmID1:%d, AlarmID2:%d, PresetNo:%d, RuleTemperatureDiff:%.1f, CurTemperatureDiff:%.1f, AlarmLevel:%d, AlarmType:%d, AlarmRule:%d, RuleCalibType:%d, Point1[x:%f, y:%f], point2[x:%f, y:%f], PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d, ThermometryUnit:%d"), struThermometryDiffAlarm.dwChannel, struThermometryDiffAlarm.byAlarmID1, struThermometryDiffAlarm.byAlarmID2, struThermometryDiffAlarm.wPresetNo, struThermometryDiffAlarm.fRuleTemperatureDiff, struThermometryDiffAlarm.fCurTemperatureDiff, struThermometryDiffAlarm.byAlarmLevel, struThermometryDiffAlarm.byAlarmType, struThermometryDiffAlarm.byAlarmRule, struThermometryDiffAlarm.byRuleCalibType, struThermometryDiffAlarm.struPoint[0].fX, struThermometryDiffAlarm.struPoint[0].fY, struThermometryDiffAlarm.struPoint[1].fX, struThermometryDiffAlarm.struPoint[1].fY, struThermometryDiffAlarm.struPtzInfo.fPan, struThermometryDiffAlarm.struPtzInfo.fTilt, struThermometryDiffAlarm.struPtzInfo.fZoom, struThermometryDiffAlarm.dwPicLen, struThermometryDiffAlarm.dwThermalPicLen, struThermometryDiffAlarm.dwThermalInfoLen, struThermometryDiffAlarm.byThermometryUnit);
			//printf("温差报警: Channel:%d, AlarmID1:%d, AlarmID2:%d, PresetNo:%d, RuleTemperatureDiff:%.1f, CurTemperatureDiff:%.1f, AlarmLevel:%d, AlarmType:%d, AlarmRule:%d, RuleCalibType:%d, Point1[x:%f, y:%f], point2[x:%f, y:%f], PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d, ThermometryUnit:%d", struThermometryDiffAlarm.dwChannel, struThermometryDiffAlarm.byAlarmID1, struThermometryDiffAlarm.byAlarmID2, struThermometryDiffAlarm.wPresetNo, struThermometryDiffAlarm.fRuleTemperatureDiff, struThermometryDiffAlarm.fCurTemperatureDiff, struThermometryDiffAlarm.byAlarmLevel, struThermometryDiffAlarm.byAlarmType, struThermometryDiffAlarm.byAlarmRule, struThermometryDiffAlarm.byRuleCalibType, struThermometryDiffAlarm.struPoint[0].fX, struThermometryDiffAlarm.struPoint[0].fY, struThermometryDiffAlarm.struPoint[1].fX, struThermometryDiffAlarm.struPoint[1].fY, struThermometryDiffAlarm.struPtzInfo.fPan, struThermometryDiffAlarm.struPtzInfo.fTilt, struThermometryDiffAlarm.struPtzInfo.fZoom, struThermometryDiffAlarm.dwPicLen, struThermometryDiffAlarm.dwThermalPicLen, struThermometryDiffAlarm.dwThermalInfoLen, struThermometryDiffAlarm.byThermometryUnit);
		}
		else if (1 == struThermometryDiffAlarm.byRuleCalibType || 2 == struThermometryDiffAlarm.byRuleCalibType)
		{
			int i = 0;
			int iPointNum = struThermometryDiffAlarm.struRegion[0].dwPointNum;
			for (i = 0; i < iPointNum; i++)
			{
				float fX = struThermometryDiffAlarm.struRegion[0].struPos[i].fX;
				float fY = struThermometryDiffAlarm.struRegion[0].struPos[i].fY;
				UE_LOG(LogTemp, Log, TEXT("测温区域1坐标点: X%d:%f,Y%d:%f;"), iPointNum + 1, fX, iPointNum + 1, fY);
				//printf("测温区域1坐标点: X%d:%f,Y%d:%f;", iPointNum + 1, fX, iPointNum + 1, fY);
			}
			iPointNum = struThermometryDiffAlarm.struRegion[1].dwPointNum;
			for (i = 0; i < iPointNum; i++)
			{
				float fX = struThermometryDiffAlarm.struRegion[1].struPos[i].fX;
				float fY = struThermometryDiffAlarm.struRegion[1].struPos[i].fY;
				UE_LOG(LogTemp, Log, TEXT("测温区域2坐标点: X%d:%f,Y%d:%f;"), iPointNum + 1, fX, iPointNum + 1, fY);
				//printf("测温区域2坐标点: X%d:%f,Y%d:%f;", iPointNum + 1, fX, iPointNum + 1, fY);
			}
			UE_LOG(LogTemp, Log, TEXT("温差报警: Channel:%d, AlarmID1:%d, AlarmID2:%d, PresetNo:%d, RuleTemperatureDiff:%.1f, CurTemperatureDiff:%.1f, AlarmLevel:%d, AlarmType:%d, AlarmRule:%d, RuleCalibType:%d,  PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d, ThermometryUnit:%d"), struThermometryDiffAlarm.dwChannel, struThermometryDiffAlarm.byAlarmID1, struThermometryDiffAlarm.byAlarmID2, struThermometryDiffAlarm.wPresetNo, struThermometryDiffAlarm.fRuleTemperatureDiff, struThermometryDiffAlarm.fCurTemperatureDiff, struThermometryDiffAlarm.byAlarmLevel, struThermometryDiffAlarm.byAlarmType, struThermometryDiffAlarm.byAlarmRule, struThermometryDiffAlarm.byRuleCalibType, struThermometryDiffAlarm.struPtzInfo.fPan, struThermometryDiffAlarm.struPtzInfo.fTilt, struThermometryDiffAlarm.struPtzInfo.fZoom, struThermometryDiffAlarm.dwPicLen, struThermometryDiffAlarm.dwThermalPicLen, struThermometryDiffAlarm.dwThermalInfoLen, struThermometryDiffAlarm.byThermometryUnit);
			//printf("温差报警: Channel:%d, AlarmID1:%d, AlarmID2:%d, PresetNo:%d, RuleTemperatureDiff:%.1f, CurTemperatureDiff:%.1f, AlarmLevel:%d, AlarmType:%d, AlarmRule:%d, RuleCalibType:%d,  PTZ Info[Pan:%f, Tilt:%f, Zoom:%f], PicLen:%d, ThermalPicLen:%d, ThermalInfoLen:%d, ThermometryUnit:%d", struThermometryDiffAlarm.dwChannel, struThermometryDiffAlarm.byAlarmID1, struThermometryDiffAlarm.byAlarmID2, struThermometryDiffAlarm.wPresetNo, struThermometryDiffAlarm.fRuleTemperatureDiff, struThermometryDiffAlarm.fCurTemperatureDiff, struThermometryDiffAlarm.byAlarmLevel, struThermometryDiffAlarm.byAlarmType, struThermometryDiffAlarm.byAlarmRule, struThermometryDiffAlarm.byRuleCalibType, struThermometryDiffAlarm.struPtzInfo.fPan, struThermometryDiffAlarm.struPtzInfo.fTilt, struThermometryDiffAlarm.struPtzInfo.fZoom, struThermometryDiffAlarm.dwPicLen, struThermometryDiffAlarm.dwThermalPicLen, struThermometryDiffAlarm.dwThermalInfoLen, struThermometryDiffAlarm.byThermometryUnit);
		}
		break;
	}

	default:
		UE_LOG(LogTemp, Log, TEXT("其他报警，报警信息类型: %d\n"), lCommand);
		//printf("其他报警，报警信息类型: %d\n", lCommand);
		break;
	}

	return true;
}

 
// Sets default values
USPCameraManager::USPCameraManager()
	:m_iCurChanIndex_Select(-1)
	,m_bIsLogin(false)
	,m_bIsPlaying(false)
	,m_bIsRecording(false)
	,m_nDevPort (8000)
	,m_struDeviceInfo(nullptr)
	,m_iCurChanIndex(-1)
	,m_lPlayHandle(-1)
{
	
}
 
USPCameraManager::~USPCameraManager()
{
	UnInit();
	if (m_struDeviceInfo)
	{
		delete m_struDeviceInfo;
		m_struDeviceInfo = nullptr;
	}
}
 
void USPCameraManager::Init()
{
	//Init SDK
	NET_DVR_Init();
 
	//Set reconnect time
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);
 
	//设置异常消息回调函数
	NET_DVR_SetExceptionCallBack_V30(0, NULL, g_ExceptionCallBack, NULL);

	updataActor = GetWorld()->SpawnActor<ALodeTextureActor>(ALodeTextureActor::StaticClass(),FVector::ZeroVector,FRotator::ZeroRotator);
}
 
void USPCameraManager::UnInit()
{
	NET_DVR_Cleanup();
}


void USPCameraManager::Tick(float DeltaTime)
{
	//解码回调 视频为YUV数据(YV12)，音频为PCM数据
	  if (GHardDiskVideoType.Num() <= 0)
	  	return;
	  long lFrameType = GHardDiskVideoType[0];
	  char* pBuf = GHardDiskVideoBuf[0];
	  long nSize = GHardDiskVideoSize[0];
	  long nWidth = GHardDiskVideoWidth[0];
	  long nHeight = GHardDiskVideoHeight[0];
	  if (lFrameType == T_YV12)
	  {
	  	//new function 1 无硬盘读取, 直接采用NV12转RGB32来解决
	  	int sizeRGB = nWidth * nHeight * 4;
	  	char* pBGR32 = new char[sizeRGB];
	  	memset(pBGR32, 0, sizeRGB);
	  	if(!YV12ToBGR32_FFmpeg((unsigned char*)pBuf, (unsigned char*)pBGR32, nWidth, nHeight))
	  	{
	  		return;
	  	}
	  	
	  	//UTexture2D* texture = UTexture2D::CreateTransient(nWidth, nHeight, PF_B8G8R8A8);
	  	//texture = UTexture2D::CreateTransient(nWidth, nHeight, PF_B8G8R8A8);
	  	
	  	//textureArr.Add(texture);
	  	// Fill in the source data from the file
	  	//void* TextureData = texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	  	//FMemory::Memcpy(TextureData, pBGR32, sizeRGB);
	  	//texture->PlatformData->Mips[0].BulkData.Unlock();
	  	// Update the rendering resource from data.
	  	//texture->UpdateResource();
	  	
	  	//updataActor->updateTexture2D(texture);

	  	if (!PlayM4_ConvertToJpegFile(pBuf, nSize, nWidth, nHeight, lFrameType, TCHAR_TO_UTF8(*m_ImageFilePath))) {
	  		return;
	  	}
	  	
	 	// //当前主UI上面的滑动CameraItem
	 	// if (GCameraItemIsPlayingStatus)
	 	// {
	 	// 	GetEditModeMainUI()->Image_CameraStream->SetBrushResourceObject(texture);
	 	// }
	
	 	// //当前是世界中播放
	 	// if (GDM_CameraStreamPlayerUIClassArray.Num() > 0)
	 	// {
	 	// 	for (auto widget : GDM_CameraStreamPlayerUIClassArray)
	 	// 	{
	 	// 		CONTINUE_IF_NULL(widget);
	 	// 		CONTINUE_IF_NULL(widget->Image_Movie);				
	 	// 		widget->Image_Movie->SetBrushResourceObject(texture);
	 	// 	}
	 	// }
 
 
	 	FMemory::Free(pBGR32);
	 	//FMemory::Free(TextureData);
	 	pBGR32 = nullptr;
 
	 	//new function 2, //有硬盘的读取
	 	//FString csDir = "D:\\qrcode\\SPProject\\Source\\1.jpg";
	 	//if (!PlayM4_ConvertToJpegFile(pBuf, nSize, nWidth, nHeight, lFrameType, TCHAR_TO_UTF8(*csDir))) {
	 	//	UUtilsLibrary::Log("Failed PlayM4_ConvertToJpegFile", true, 5.f, FColor::Red);
	 	//	return;
	 	//}
	 	//UTexture2D* t1 = UMedusaLibrary::LoadTexture(csDir);
	 	//if (ParentUI)
	 	//{
	 	//	ParentUI->Image_Streaming->SetBrushResourceObject(t1);
	 	//}
	 }
	 /*else if(lFrameType == T_AUDIO16)
	 {
	 	//处理声音部分
	 }*/
	 GHardDiskVideoBuf.Remove(pBuf);
	 GHardDiskVideoSize.Remove(nSize);
	 GHardDiskVideoWidth.Remove(nWidth);
	 GHardDiskVideoHeight.Remove(nHeight);
	 GHardDiskVideoType.Remove(lFrameType);
}
 
bool USPCameraManager::IsTickable() const
{
	return true;
}
 
TStatId USPCameraManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(USPCameraManager, STATGROUP_Tickables);
}
 
//获取登录硬盘录像机是否成功了
bool USPCameraManager::TrytoLoginDiskCamera(FString DeviceIp,int DevicePort,FString account,FString password)
{
	//如果已经登录成功了, 再改了参数又去Login的情况没有处理
	//todo...
 
	//try to login
	if (!m_bIsLogin)
	{
		if (!DoLogin(DeviceIp,DevicePort,account,password))
		//if (!DoLogin("192.168.1.64",8000,"admin","abcd1234"))
			return false;
		DoGetDeviceResoureCfg();	//获取设备资源信息
 
		m_bIsLogin = true;
 
		//广播硬盘录像机登录成功
		// FSPDelegates::DiskCameraLoginSuccessedDelegate.Broadcast();
	}
	return m_bIsLogin;
}
 
/*************************************************
函数名:    	DoLogin
函数描述:	向设备注册
输入参数:
输出参数:
返回值:
**************************************************/
bool USPCameraManager::DoLogin(FString DeviceIp,int DevicePort,FString account,FString password)
{
	// RETURN_FALSE_IF_NULL(GGameInstance);
	// RETURN_FALSE_IF_NULL(GGameInstance->GetLocalSave_CameraInfo());
 //
	// FString DeviceIp = GGameInstance->GetLocalSave_CameraInfo()->GetIP();
	// RETURN_FALSE_IF(DeviceIp.IsEmpty());
	// FString account = GGameInstance->GetLocalSave_CameraInfo()->GetAccount();
	// RETURN_FALSE_IF(account.IsEmpty());
	// FString password = GGameInstance->GetLocalSave_CameraInfo()->GetPassword();
	// RETURN_FALSE_IF(password.IsEmpty());


	char* ip = TCHAR_TO_ANSI(*DeviceIp);
	// m_nDevPort = GGameInstance->GetLocalSave_CameraInfo()->GetPort();
	m_nDevPort = DevicePort;
	char* accountstr = TCHAR_TO_ANSI(*account);
	char* passwordstr = TCHAR_TO_ANSI(*password);
 
 
	//register device
	LONG IUserID;
	NET_DVR_USER_LOGIN_INFO struLoginInfo = { 0 };
	NET_DVR_DEVICEINFO_V40 struDeviceInfo = { 0 };

	/*
	strcpy_s((char*)struLoginInfo.sDeviceAddress, sizeof(struLoginInfo.sDeviceAddress), ip);
	strcpy_s((char*)struLoginInfo.sUserName, sizeof(struLoginInfo.sUserName), accountstr);
	strcpy_s((char*)struLoginInfo.sPassword, sizeof(struLoginInfo.sPassword), passwordstr);
	struLoginInfo.wPort = m_nDevPort;
	*/
	strcpy_s((char*)struLoginInfo.sDeviceAddress, sizeof(struLoginInfo.sDeviceAddress), "192.168.1.64");
	strcpy_s((char*)struLoginInfo.sUserName, sizeof(struLoginInfo.sUserName), "admin");
	strcpy_s((char*)struLoginInfo.sPassword, sizeof(struLoginInfo.sPassword), "abcd1234");
	struLoginInfo.wPort = 8000;
	
	struLoginInfo.bUseAsynLogin = 0;
	
	
	IUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfo);
	if (IUserID == -1)
	{
		DWORD err = NET_DVR_GetLastError();
		FString error = "login faild errror, error_code:";
		error.Append(FString::FromInt(err));
		error.Append(".SDK Tips:");
		error.Append(NET_DVR_GetErrorMsg());
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(error));
		return false;
	}
	if (!m_struDeviceInfo)
	{
		m_struDeviceInfo = new STRU_DEVICE_INFO();
	}
 
	m_struDeviceInfo->lLoginID = IUserID;
	m_struDeviceInfo->iDeviceChanNum = struDeviceInfo.struDeviceV30.byChanNum;
	m_struDeviceInfo->iIPChanNum = struDeviceInfo.struDeviceV30.byIPChanNum;
	m_struDeviceInfo->iStartChan = struDeviceInfo.struDeviceV30.byStartChan;
	m_struDeviceInfo->iIPStartChan = struDeviceInfo.struDeviceV30.byStartDChan;
 
	return true;
}
 
/*************************************************
函数名:    	DoGetDeviceResoureCfg
函数描述:	获取设备的通道资源
输入参数:
输出参数:
返回值:
**************************************************/
void USPCameraManager::DoGetDeviceResoureCfg()
{
	NET_DVR_IPPARACFG_V40 IpAccessCfg;
	memset(&IpAccessCfg, 0, sizeof(IpAccessCfg));
	DWORD  dwReturned;
 
	int iGroupNO = 0;
	m_struDeviceInfo->bIPRet = NET_DVR_GetDVRConfig(m_struDeviceInfo->lLoginID, NET_DVR_GET_IPPARACFG_V40, iGroupNO, &IpAccessCfg, sizeof(NET_DVR_IPPARACFG_V40), &dwReturned);
 
	int i;
	if (!m_struDeviceInfo->bIPRet)   //不支持ip接入,9000以下设备不支持禁用模拟通道
	{
		for (i = 0; i < MAX_ANALOG_CHANNUM; i++)
		{
			if (i < m_struDeviceInfo->iDeviceChanNum)
			{
				sprintf_s(m_struDeviceInfo->struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo->iStartChan);
				m_struDeviceInfo->struChanInfo[i].iChanIndex = i + m_struDeviceInfo->iStartChan;  //通道号
				m_struDeviceInfo->struChanInfo[i].bEnable = true;
 
			}
			else
			{
				m_struDeviceInfo->struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo->struChanInfo[i].bEnable = false;
				sprintf_s(m_struDeviceInfo->struChanInfo[i].chChanName, "");
			}
		}
	}
	else        //支持IP接入，9000设备
	{
		for (i = 0; i < MAX_ANALOG_CHANNUM; i++)  //模拟通道
		{
			if (i < m_struDeviceInfo->iDeviceChanNum)
			{
				sprintf_s(m_struDeviceInfo->struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo->iStartChan);
				m_struDeviceInfo->struChanInfo[i].iChanIndex = i + m_struDeviceInfo->iStartChan;
				if (IpAccessCfg.byAnalogChanEnable[i])
				{
					m_struDeviceInfo->struChanInfo[i].bEnable = true;
				}
				else
				{
					m_struDeviceInfo->struChanInfo[i].bEnable = false;
				}
 
			}
			else//clear the state of other channel
			{
				m_struDeviceInfo->struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo->struChanInfo[i].bEnable = false;
				sprintf_s(m_struDeviceInfo->struChanInfo[i].chChanName, "");
			}
		}
 
		//数字通道
		for (i = 0; i < MAX_IP_CHANNEL; i++)
		{
			if (IpAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byEnable)  //ip通道在线
			{
				int byIPID = IpAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byIPID;
				int byIPIDHigh = IpAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byIPIDHigh;
				int iDevInfoIndex = byIPIDHigh * 256 + byIPID - 1 - iGroupNO * 64;
				//FString SIP(IpAccessCfg.struIPDevInfo[iDevInfoIndex].struIP.sIpV4);
				//printf("通道号%d 在线 摄像头取流, IP: %s\n", i + 1, IpAccessCfg.struIPDevInfo[iDevInfoIndex].struIP.sIpV4);
 
				int tempChanIndex = i + IpAccessCfg.dwStartDChan;
				m_struDeviceInfo->struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = true;
				m_struDeviceInfo->struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = tempChanIndex;
				sprintf_s(m_struDeviceInfo->struChanInfo[i + MAX_ANALOG_CHANNUM].chChanName, "IP Camera %d", i + 1);
				sprintf_s(m_struDeviceInfo->struChanInfo[i + MAX_ANALOG_CHANNUM].chAccessChanIP, IpAccessCfg.struIPDevInfo[iDevInfoIndex].struIP.sIpV4);
 
				int nDeviceIDLen = sizeof(IpAccessCfg.struIPDevInfo[iDevInfoIndex].szDeviceID);
				memcpy(m_struDeviceInfo->struChanInfo[i + MAX_ANALOG_CHANNUM].szDeviceID, IpAccessCfg.struIPDevInfo[iDevInfoIndex].szDeviceID, nDeviceIDLen);
 
				//视频上叠加的通道名称、OSD时间等显示使能、属性等
				NET_DVR_PICCFG_V40 net_dvr_piccfg_v40;
				memset(&net_dvr_piccfg_v40, 0, sizeof(net_dvr_piccfg_v40));
				DWORD dwPiccfg_Returned;
				if (NET_DVR_GetDVRConfig(m_struDeviceInfo->lLoginID, NET_DVR_GET_PICCFG_V40, tempChanIndex, &net_dvr_piccfg_v40, sizeof(NET_DVR_PICCFG_V40), &dwPiccfg_Returned))
				{
					int nLen = sizeof(net_dvr_piccfg_v40.sChanName);
					char* name = (char*)net_dvr_piccfg_v40.sChanName;
					memcpy(m_struDeviceInfo->struChanInfo[i + MAX_ANALOG_CHANNUM].chChanName, name, nLen);
					m_struDeviceInfo->struChanInfo[i + MAX_ANALOG_CHANNUM].chChanName[nLen] = '\0';
				}
				else
				{
					//get failed
				}
			}
			else
			{
				m_struDeviceInfo->struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = false;
				m_struDeviceInfo->struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = -1;
			}
		}
 
 
	}
}

void USPCameraManager::Up_Start()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,TILT_UP,0);
}

void USPCameraManager::Up_End()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,TILT_UP,1);
}

void USPCameraManager::Right_Start()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,PAN_RIGHT,0);
}

void USPCameraManager::Right_End()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,PAN_RIGHT,1);
}

void USPCameraManager::Left_Start()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,PAN_LEFT,0);
}

void USPCameraManager::Left_End()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,PAN_LEFT,1);
}

void USPCameraManager::Down_Start()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,TILT_DOWN,0);
}

void USPCameraManager::Down_End()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,TILT_DOWN,1);
}

void USPCameraManager::ZoomIN_Start()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,ZOOM_IN,0);
}

void USPCameraManager::ZoomIN_End()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,ZOOM_IN,1);
}

void USPCameraManager::ZoomOUT_Start()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,ZOOM_OUT,0);
}

void USPCameraManager::ZoomOUT_End()
{
	bool control = NET_DVR_PTZControl(m_lPlayHandle,ZOOM_OUT,0);
}

void USPCameraManager::AddPoint(int32 index)
{
	bool control = NET_DVR_PTZPreset(m_lPlayHandle,8,index);
}

void USPCameraManager::DeletePoint(int32 index)
{
	bool control = NET_DVR_PTZPreset(m_lPlayHandle,9,index);
}

void USPCameraManager::LookAtPoint(int32 index)
{
	bool control = NET_DVR_PTZPreset(m_lPlayHandle,39,index);
}
void USPCameraManager::TakePhoto(int iChanIndex, FString directoryPath, FString photoFileName)
{
	if (m_lPlayHandle == -1)
	{
		UE_LOG(LogTemp, Log, TEXT("请先选择一个通道播放"));
		return;
	}
	FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*directoryPath);

	char PicName[256] = { 0 };
	//FDateTime CurTime = FDateTime::Now();;
	//sprintf_s(PicName, "%s\\%04d%02d%02d%02d%02d%02d_ch%02d.jpg", TCHAR_TO_UTF8(*directoryPath), CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay(), 
	//	CurTime.GetHour(), CurTime.GetMinute(), CurTime.GetSecond(), iChanIndex);
	sprintf_s(PicName, "%s\\%s_ch%02d.jpg", TCHAR_TO_UTF8(*directoryPath), TCHAR_TO_UTF8(*photoFileName),iChanIndex);
	
	//组建jpg结构
	NET_DVR_JPEGPARA JpgPara = { 0 };
	JpgPara.wPicSize = static_cast<WORD>(0);
	JpgPara.wPicQuality = static_cast<WORD>(0);

	if (NET_DVR_CaptureJPEGPicture(m_struDeviceInfo->lLoginID, iChanIndex, &JpgPara, PicName))
	{
		std::string s(PicName);
		FString ass(s.c_str());
		UE_LOG(LogTemp, Log, TEXT("%s ,抓图成功"), *ass);
	}
}

FVector2D USPCameraManager::GetThermometerInfo()
{
	//抓热图
	NET_DVR_JPEGPICTURE_WITH_APPENDDATA m_struJpegWithAppendAata = { 0 };

	//自己分配内存，需要大于实际数据长度
	if (m_struJpegWithAppendAata.pP2PDataBuff == NULL)
	{
		m_struJpegWithAppendAata.pP2PDataBuff = new char[2 * 1024 * 1024];
		memset(m_struJpegWithAppendAata.pP2PDataBuff, 0, 2 * 1024 * 1024);
	}

	if (!NET_DVR_CaptureJPEGPicture_WithAppendData(m_struDeviceInfo->lLoginID, 2, &m_struJpegWithAppendAata))
	{
		//printf("NET_DVR_CaptureJPEGPicture_WithAppendData failed, error code: %d\n", NET_DVR_GetLastError());
		UE_LOG(LogTemp, Log, TEXT("NET_DVR_CaptureJPEGPicture_WithAppendData failed, error code: %d\n"), NET_DVR_GetLastError());
		return FVector2D::ZeroVector;
	}
	else
	{
		/*printf("NET_DVR_CaptureJPEGPicture_WithAppendData struThermalValidRect[X:%f Y:%f W:%f H:%f] struVisibleValidRect[X:%f Y:%f W:%f H:%f]",
			m_struJpegWithAppendAata.struThermalValidRect.fX, m_struJpegWithAppendAata.struThermalValidRect.fY,
			m_struJpegWithAppendAata.struThermalValidRect.fWidth, m_struJpegWithAppendAata.struThermalValidRect.fHeight,
			m_struJpegWithAppendAata.struVisibleValidRect.fX, m_struJpegWithAppendAata.struVisibleValidRect.fY,
			m_struJpegWithAppendAata.struVisibleValidRect.fWidth, m_struJpegWithAppendAata.struVisibleValidRect.fHeight);*/

		int iIndex = 0;
		float minTemp = 10000.0;
		float maxTemp = -10000.0;
		//int m_AnalysisHotPic_W = 384; //根据抓热图接口返回的图像宽dwJpegPicWidth进行赋值
		//int m_AnalysisHotPic_H = 288; //根据抓热图接口返回的图像高dwJpegPicHeight进行赋值
		int m_AnalysisHotPic_W = m_struJpegWithAppendAata.dwJpegPicWidth; //根据抓热图接口返回的图像宽dwJpegPicWidth进行赋值
		int m_AnalysisHotPic_H = m_struJpegWithAppendAata.dwJpegPicHeight; //根据抓热图接口返回的图像高dwJpegPicHeight进行赋值
		//int bufSize = m_AnalysisHotPic_H * m_AnalysisHotPic_W * 4;
		char* pDataBuf = m_struJpegWithAppendAata.pP2PDataBuff;

		for (int iWriteHeight = 0; iWriteHeight < m_AnalysisHotPic_H; ++iWriteHeight)
		{
			for (int iWriteWidth = 0; iWriteWidth < m_AnalysisHotPic_W; ++iWriteWidth)
			{
				float fTemp = *((float*)(pDataBuf + iIndex));

				//判断fTemp是否是一个正常值，不是则赋值最大或最小，防止设备崩溃
				fTemp = (9999 < fTemp) ? 9999 : ((-9999 > fTemp) ? -9999 : fTemp);

				minTemp = (minTemp > fTemp) ? fTemp : minTemp;
				maxTemp = (maxTemp > fTemp) ? maxTemp : fTemp;
				
				iIndex += 4;
			}
		}
		UE_LOG(LogTemp, Log, TEXT("minTemp: %f,maxTemp: %f"), minTemp, maxTemp);
		return FVector2D(minTemp, maxTemp);
	}

}


/*************************************************
函数名:    	GetDecoderCfg
函数描述:	获取云台解码器信息
输入参数:
输出参数:
返回值:
**************************************************/
void USPCameraManager::GetDecoderCfg()
{
	NET_DVR_DECODERCFG_V30 DecoderCfg;
	DWORD  dwReturned;
	bool bRet;
 
	//获取通道解码器信息
	for (int i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if (m_struDeviceInfo->struChanInfo[i].bEnable)
		{
			memset(&DecoderCfg, 0, sizeof(NET_DVR_DECODERCFG_V30));
			bRet = NET_DVR_GetDVRConfig(m_struDeviceInfo->lLoginID, NET_DVR_GET_DECODERCFG_V30, \
				m_struDeviceInfo->struChanInfo[i].iChanIndex, &DecoderCfg, sizeof(NET_DVR_DECODERCFG_V30), &dwReturned);
			if (!bRet)
			{
				auto str = FString::Printf(TEXT("Get DecderCfg failed,Chan:%d\n"), m_struDeviceInfo->struChanInfo[i].iChanIndex);
				UE_LOG(LogTemp,Log,TEXT("%s"),*str);
				//TRACE("Get DecderCfg failed,Chan:%d\n", m_struDeviceInfo->struChanInfo[i].iChanIndex);
				continue;
			}
 
			memcpy(&m_struDeviceInfo->struChanInfo[i].struDecodercfg, &DecoderCfg, sizeof(NET_DVR_DECODERCFG_V30));
		}
 
	}
 
}
 
/*************************************************
函数名:    	InitDecoderReferCtrl
函数描述:	初始化云台控制相关控件
输入参数:
输出参数:
返回值:
**************************************************/
void USPCameraManager::InitDecoderReferCtrl()
{
	int i = 0;
	FString tmp = "";
	//设置预置点
	for (i = 0; i < MAX_PRESET_V30; i++)
	{
		tmp = "";
		tmp.Append(FString::FromInt(i + 1));
//		ComboxPreset->AddOption(tmp);
	}
//	ComboxPreset->SetSelectedIndex(0);
 
	//巡航轨迹
	for (i = 0; i < MAX_CRUISE_SEQ; i++)
	{
		tmp = "";
		tmp.Append(FString::FromInt(i + 1));
//		ComboxSeq->AddOption(tmp);
	}
//	ComboxSeq->SetSelectedIndex(0);
}
 
/*************************************************
函数名:    	StartPlay
函数描述:	开始一路播放
输入参数:   ChanIndex-通道号
输出参数:
返回值:
**************************************************/
bool USPCameraManager::StartPlay(int iChanIndex)
{
	NET_DVR_SDKMEMPOOL_CFG struSDKMemPoolCfg = { 0 };
 
	if (!NET_DVR_ReleaseSDKMemPool(&struSDKMemPoolCfg))
	{
		UE_LOG(LogTemp,Warning,TEXT("Set Release Sdk MemPool fail"));
	}
	else
	{
		UE_LOG(LogTemp,Log,TEXT("Set Release Sdk MemPool successful"));
	}
 
	/*ClientInfo.hPlayWnd = NULL;
	ClientInfo.lChannel = m_iCurChanIndex + 1;
	ClientInfo.lLinkMode = 0;
	ClientInfo.sMultiCastIP = NULL;*/
 
	//display
	NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
	struPlayInfo.hPlayWnd = NULL;
	//struPlayInfo.lChannel = m_iCurChanIndex + 1;
	struPlayInfo.lChannel = iChanIndex;
	struPlayInfo.dwStreamType = 0;
	//0-TCP方式 1-UDP方式 2-多播方式 3-RTP方式 4-RTP/RSTP 5-RTP/HTTP 6-HRUDP（可靠传输) 7-RTSP/HTTPS 8-NPQ
	struPlayInfo.dwLinkMode = 0;
	struPlayInfo.bBlocked = 0;
	struPlayInfo.dwDisplayBufNum = 15;
 
	SetCurChanIndex_Select(iChanIndex);
 
	//m_lPlayHandle = NET_DVR_RealPlay_V30(m_struDeviceInfo->lLoginID, &ClientInfo, g_RealDataCallBack, NULL, true);
	m_lPlayHandle = NET_DVR_RealPlay_V40(m_struDeviceInfo->lLoginID, &struPlayInfo, g_RealDataCallBack, NULL);
	//m_lPlayHandle = NET_DVR_RealPlay_V40(m_struDeviceInfo->lLoginID, &struPlayInfo, NULL, NULL);
	
	if (m_lPlayHandle < 0)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(NET_DVR_GetErrorMsg()));
		UE_LOG(LogTemp,Warning,TEXT("play failed, error code:%d\n"), NET_DVR_GetLastError());
		NET_DVR_Logout(m_struDeviceInfo->lLoginID);
		return false;
	}

	/*
	if(!NET_DVR_SetRealDataCallBack(m_lPlayHandle,g_RealDataCallBack,0))
	{
		return  false;
	}
	*/
		
	m_bIsPlaying = true;
	//	TextBlock_PlayStatus->SetText(FText::FromString("StopPlay"));
	//FSPDelegates::DiskCameraStartPlayDelegate.Broadcast();
	return true;
}
 
/*************************************************
函数名:    	StopPlay
函数描述:	停止播放
输入参数:
输出参数:
返回值:
**************************************************/
bool USPCameraManager::StopPlay()
{
	if (m_lPlayHandle != -1)
	{
		if (m_bIsRecording)  //正在录像，先停止
		{
			StopRecord();
		}
		if (NET_DVR_StopRealPlay(m_lPlayHandle))
		{
			SetCurChanIndex_Select(-1);
 
			NET_DVR_SDKMEMPOOL_CFG struSDKMemPoolCfg = { 0 };
			if (!NET_DVR_ReleaseSDKMemPool(&struSDKMemPoolCfg))
			{
				UE_LOG(LogTemp,Warning,TEXT("Set Release Sdk MemPool fail"));
			}
			else
			{
				UE_LOG(LogTemp,Log,TEXT("Set Release Sdk MemPool successful"));
			}
 
			m_lPlayHandle = -1;
			m_bIsPlaying = false;
			//			TextBlock_PlayStatus->SetText(FText::FromString("Play"));
			// FSPDelegates::DiskCameraStopPlayDelegate.Broadcast();
		}
		else
		{
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("StopPlay failed"));
			return false;
		}
	}
	return true;
}
 
/*************************************************
函数名:    	StopRecord
函数描述:	停止录像
输入参数:
输出参数:
返回值:
**************************************************/
void USPCameraManager::StopRecord()
{
	if (!NET_DVR_StopSaveRealData(m_lPlayHandle))
	{
		//MessageBox("停止录像失败");
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("StopRecord failed"));
		return;
	}
	m_bIsRecording = false;
//	TextBlock_RecordStatus->SetText(FText::FromString("Record"));
}
 
/*************************************************
函数名:    	DbPlayChannel
函数描述:	双击播放
输入参数:   ChanIndex-通道号
输出参数:
返回值:
**************************************************/
bool USPCameraManager::DbPlayChannel(int ChanIndex)
{
	StopPlay();
	return StartPlay(ChanIndex);
}