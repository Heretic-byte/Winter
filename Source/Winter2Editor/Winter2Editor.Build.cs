// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;
using System.IO;

public class Winter2Editor : ModuleRules
{
	public Winter2Editor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] {
			"Winter2Editor/Public",
		});

		PrivateIncludePaths.AddRange(new string[] {
            "Winter2Editor/Private",
		});
			
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"UnrealEd",
				"Core",
				"Json",
				"Engine",
				"Slate",
				"SlateCore",
				"PropertyEditor",
				"UnrealEd",
				"DataTableEditor",
				"AssetTools",
				"InputCore",
				"EditorStyle",
                "Winter2"
            }
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"UnrealEd",
				"CoreUObject",
				"Json",
				"Engine",
				"Slate",
				"SlateCore",
				"PropertyEditor",
				"UnrealEd",
				"DataTableEditor",
				"AssetTools",
				"InputCore",
				"EditorStyle",
                "Winter2"
            }
		);
		

		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}
