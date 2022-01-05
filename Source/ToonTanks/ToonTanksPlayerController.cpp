// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

#define OUT

#define MoveCursorXBinding TEXT("MoveCursorX")
#define MoveCursorYBinding TEXT("MoveCursorY")

void AToonTanksPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InputComponent->BindAxis(MoveCursorXBinding, this, &AToonTanksPlayerController::MoveCursorX);
	InputComponent->BindAxis(MoveCursorYBinding, this, &AToonTanksPlayerController::MoveCursorY);
}

void AToonTanksPlayerController::SetInputEnabledState(bool bEnabled)
{
	bEnabled ? GetPawn()->EnableInput(this) : GetPawn()->DisableInput(this);
	bShowMouseCursor = bEnabled;
}

void AToonTanksPlayerController::MoveCursorX(float Value) 
{
	if (!bShowMouseCursor)
		return;

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	float LocationX;
	float LocationY;
	
	GetMousePosition(OUT LocationX, OUT LocationY);

	SetMouseLocation(LocationX + Value * DeltaTime * MouseOffset, LocationY);
}

void AToonTanksPlayerController::MoveCursorY(float Value)
{
	if (!bShowMouseCursor)
		return;

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	float LocationX;
	float LocationY;

	GetMousePosition(OUT LocationX, OUT LocationY);

	SetMouseLocation(LocationX, LocationY + Value * DeltaTime * MouseOffset);
}
