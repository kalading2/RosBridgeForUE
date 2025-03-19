#pragma once


#include "Core.h"

#include "ROSBridgeSubscriber.h" //插件中的头文件

class ROSTwistSubscriber : public FROSBridgeSubscriber
{
public:
	ROSTwistSubscriber(const FString& InTopic);
	~ROSTwistSubscriber() override;
	
	TSharedPtr<FROSBridgeMsg>ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override;
	void Callback(TSharedPtr<FROSBridgeMsg> Msg) override;
	
	//机器人信息
	FString l1 = "";
	FString l2 = "";
	FString l3 = "";
	FString v1 = "";
	FString v2 = "";
	FString v3 = "";
	
};
