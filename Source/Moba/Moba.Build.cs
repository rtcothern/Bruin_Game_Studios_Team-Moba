// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Moba : ModuleRules
{
	public Moba(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemUtils"});
		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });
	}
}
