// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "VlcMediaSettings.h"


UVlcMediaSettings::UVlcMediaSettings()
	: DiscCaching(FTimespan::FromMilliseconds(100.0))
	, FileCaching(FTimespan::FromMilliseconds(100.0))
	, LiveCaching(FTimespan::FromMilliseconds(100.0))
	, NetworkCaching(FTimespan::FromMilliseconds(100.0))
	, LogLevel(EVlcMediaLogLevel::Warning)
	, ShowLogContext(false)
{ }
