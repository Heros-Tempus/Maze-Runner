// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class guidedtutorial1_TMTarget : TargetRules
{
	public guidedtutorial1_TMTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "guidedtutorial1_TM" } );
	}
}
