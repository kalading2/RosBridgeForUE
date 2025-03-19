#pragma once


#include "Core.h"

#include "ROSBridgeSubscriber.h" //插件中的头文件

class ROSStringSubscriber : public FROSBridgeSubscriber
{
public:
	ROSStringSubscriber(const FString& InTopic);
	~ROSStringSubscriber() override;
	
	TSharedPtr<FROSBridgeMsg>ParseMessage(TSharedPtr<FJsonObject> JsonObject) const override;
	void Callback(TSharedPtr<FROSBridgeMsg> Msg) override;
	
	int32 RosMsg1;
	FString rosMsg;
	
};

