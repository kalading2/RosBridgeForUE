// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class RosBridgeDemo : ModuleRules
{
	private string ModulePath
	{
		get
		{
			return ModuleDirectory;
		}
	}
	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../RosBridgeDemo/ThirdParty/HCNetSDK/")); }
	}
 
	public bool LoadHC(ReadOnlyTargetRules Target)
	{
		bool isLibrarySupported = false;
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			isLibrarySupported = true;
			string LibrariesPath = Path.Combine(ThirdPartyPath, "lib");
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "HCCore.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "HCNetSDK.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "PlayCtrl.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "GdiPlus.lib"));
		}
		if (isLibrarySupported)
		{
			//Include path
			PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include"));
		}
		return isLibrarySupported;
	}
 
	public RosBridgeDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "../../Config", "DefaultEngine.ini"));
		RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "../../Config", "DefaultGame.ini"));

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		CppStandard = CppStandardVersion.Cpp17;

		bEnableExceptions = true;

		// 添加职教版内容 后面再整理
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine",
			"InputCore", "ImageWrapper", "RenderCore", "RHI", "AssetRegistry",
			"Landscape","Json", "JsonUtilities",
			"Http","UMG","Slate", "SlateCore","UROSBridge","UFFmpeg"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "UMG", "Slate", "SlateCore" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		LoadHC(Target);
	}
}
