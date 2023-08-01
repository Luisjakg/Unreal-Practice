// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class A01_BlockoutShooter : ModuleRules
{
	public A01_BlockoutShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
