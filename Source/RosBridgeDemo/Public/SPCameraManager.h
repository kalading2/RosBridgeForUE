// Fill out your copyright notice in the Description page of Project Settings.
/*
*	Author:田华健 tianhj
*	Data:2020-11-23 13:57:26
*	摄像头布置数据管理器
*	Description: 摄像头布置数据管理器
*/
#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"
#include "LodeTextureActor.h"
#include "FFmpegDirector.h"
#include "RosBridgeDemo/ThirdParty/HCNetSDK/include/GeneralDef.h"

//extern "C" {
//#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
//#include <libavformat/avio.h>
//#include <libavutil/file.h>
//#include "libswresample/swresample.h"
//#include <libavutil/frame.h>
//#include <libavutil/mem.h>
//#include <libavutil/imgutils.h>
//#include <libavutil/samplefmt.h>
//#include <libavutil/timestamp.h>
//#include <libavformat/avformat.h>
//#include <libswscale/swscale.h>
//}
 
#include "SPCameraManager.generated.h"
 
UCLASS(Blueprintable)
class ROSBRIDGEDEMO_API USPCameraManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
 
public:
	// Sets default values for this character's properties
	USPCameraManager();
	virtual ~USPCameraManager();
 
	//从视频文件获取封面 sMovieFullPath:要解析的视频全路径, 直接在后面拼一个.jpg
	UFUNCTION(BlueprintCallable)
	void SaveJPEGFromMovie(const FString& sImageSavePath);
 
	UFUNCTION(BlueprintCallable)
	//初始化
	void Init();
	void UnInit();
 
	//Tick
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

	UFUNCTION(BlueprintCallable)
	//尝试登录硬盘录像机
	bool TrytoLoginDiskCamera(FString DeviceIp,int DevicePort,FString account,FString password);
 
	//获取DeviceInfo, 如果returnnull的话证明没有login硬盘录像机成功
	pLOCAL_DEVICE_INFO GetDeviceInfo()
	{ 
		return m_struDeviceInfo;
	}

	//获取登录硬盘录像机是否成功了
	bool GetLoginDiskCameraSusccessed() { return m_bIsLogin; }
	
	UFUNCTION(BlueprintCallable)
	void SetCurChanIndex(int val) { m_iCurChanIndex = val; }
	//int GetCurChanIndex() { return m_iCurChanIndex; }
 
	//当前选中的Index
	void SetCurChanIndex_Select(int val) { m_iCurChanIndex = val; }
	int GetCurChanIndex_Select() { return m_iCurChanIndex; }
	int m_iCurChanIndex_Select;
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* texture;
	UPROPERTY(BlueprintReadWrite)
	FString m_ImageFilePath;
	bool DbPlayChannel(int ChanIndex);
	bool StopPlay();
 
private:
 
	//对应SaveJPEGFromMovie()保存封面
	int saveMovieAsJPEG(AVFrame* pFrame, int width, int height, int index, FString sName);
 
	void InitDecoderReferCtrl();
	void GetDecoderCfg();
	void StopRecord();
	UFUNCTION(BlueprintCallable)
	bool StartPlay(int iChanIndex);
	bool DoLogin(FString DeviceIp,int DevicePort,FString account,FString password);
	void DoGetDeviceResoureCfg();

	//-----------控制移动-------------
	UFUNCTION(BlueprintCallable)
	void Up_Start();
	UFUNCTION(BlueprintCallable)
	void Up_End();
	UFUNCTION(BlueprintCallable)
	void Left_Start();
	UFUNCTION(BlueprintCallable)
	void Left_End();
	UFUNCTION(BlueprintCallable)
	void Down_Start();
	UFUNCTION(BlueprintCallable)
	void Down_End();
	UFUNCTION(BlueprintCallable)
	void Right_Start();
	UFUNCTION(BlueprintCallable)
	void Right_End();
	UFUNCTION(BlueprintCallable)
	void ZoomIN_Start();
	UFUNCTION(BlueprintCallable)
	void ZoomIN_End();
	UFUNCTION(BlueprintCallable)
	void ZoomOUT_Start();
	UFUNCTION(BlueprintCallable)
	void ZoomOUT_End();
	UFUNCTION(BlueprintCallable)
	void AddPoint(int32 index);
	UFUNCTION(BlueprintCallable)
	void DeletePoint(int32 index);
	UFUNCTION(BlueprintCallable)
	void LookAtPoint(int32 index);
	UFUNCTION(BlueprintCallable)
	void TakePhoto(int iChanIndex, FString directoryPath, FString photoFileName);
	UFUNCTION(BlueprintCallable)
	FVector2D GetThermometerInfo();
 
	bool m_bIsLogin;
	bool m_bIsPlaying;
	bool m_bIsRecording;
	UINT m_nDevPort;
	pLOCAL_DEVICE_INFO m_struDeviceInfo;	//如果returnnull的话证明没有login硬盘录像机成功
	int m_iCurChanIndex;               //当前通道在数组中索引
	LONG m_lPlayHandle;
	ALodeTextureActor* updataActor;
};