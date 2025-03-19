// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UFFmpeg/Public/EncodeData.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEncodeData() {}
// Cross Module References
	UFFMPEG_API UClass* Z_Construct_UClass_UCircleQueue_NoRegister();
	UFFMPEG_API UClass* Z_Construct_UClass_UCircleQueue();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_UFFmpeg();
// End Cross Module References
	void UCircleQueue::StaticRegisterNativesUCircleQueue()
	{
	}
	UClass* Z_Construct_UClass_UCircleQueue_NoRegister()
	{
		return UCircleQueue::StaticClass();
	}
	struct Z_Construct_UClass_UCircleQueue_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCircleQueue_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_UFFmpeg,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCircleQueue_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "EncodeData.h" },
		{ "ModuleRelativePath", "Public/EncodeData.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCircleQueue_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCircleQueue>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCircleQueue_Statics::ClassParams = {
		&UCircleQueue::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCircleQueue_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCircleQueue_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCircleQueue()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCircleQueue_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCircleQueue, 3451845773);
	template<> UFFMPEG_API UClass* StaticClass<UCircleQueue>()
	{
		return UCircleQueue::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCircleQueue(Z_Construct_UClass_UCircleQueue, &UCircleQueue::StaticClass, TEXT("/Script/UFFmpeg"), TEXT("UCircleQueue"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCircleQueue);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
