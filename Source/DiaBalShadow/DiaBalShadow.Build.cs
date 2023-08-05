// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DiaBalShadow : ModuleRules
{
	public DiaBalShadow(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" , "GameFeatures" });

        PrivateDependencyModuleNames.AddRange(
                new string[] {
               // "LoadingScreen",
                "Slate",
                "SlateCore",
                "MoviePlayer",
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks",
                "AIModule"
                }
            );

    }
}
