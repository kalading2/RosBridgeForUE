#pragma once


#include "Core.h"

#include "ROSBridgeSubscriber.h" //插件中的头文件

class ROSPoseSubscriber : public FROSBridgeSubscriber
{
public:
	ROSPoseSubscriber(const FString& InTopic);
	~ROSPoseSubscriber() override;
	
	TSharedPtr<FROSBridgeMsg>ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override;
	void Callback(TSharedPtr<FROSBridgeMsg> Msg) override;

	int32 RosMsg1;
	//机器人信息
	FString seq = "";
	FString secs = "";
	FString nsecs = "";
	FString frame_id = "";
	FString posx = "";
	FString posy = "";
	FString posZ = "";
	FString orix = "";
	FString oriy = "";
	FString oriz = "";
	FString oriw = "";
	
};
