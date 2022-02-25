// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Winter2 : ModuleRules
{
	public Winter2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});
	}
}
