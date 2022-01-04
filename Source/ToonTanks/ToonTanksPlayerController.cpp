// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetInputEnabledState(bool bEnabled)
{
	bEnabled ? GetPawn()->EnableInput(this) : GetPawn()->DisableInput(this);
	bShowMouseCursor = bEnabled;
}