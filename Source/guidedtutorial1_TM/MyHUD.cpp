// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"

/*
Drawing to the screen with a HUD class is very simple. 
First, create a HUD class
Second, override the DrawHUD() function with whatever draw commands are required
Finally, change the world settings to use the custom HUD class

Changing the font requires a blueprint editable variable to be used in the DrawText command
Then, create a HUD blueprint which inherits from the custom class
The variable can then be set in the blueprint
and the world settings would need to be changed to use the blueprint
*/

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawLine(200, 300, 400, 500, FLinearColor::Blue);
	DrawText("Hello!", FLinearColor(254, 0, 0), 2, 2, hudFont, 2, true);
}
