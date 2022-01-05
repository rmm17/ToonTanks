// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetInputEnabledState(bool bEnabled);

protected:
	virtual void BeginPlay() override;

private:
	void MoveCursorX(float Value);
	void MoveCursorY(float Value);

	float MouseOffset = 1000.f;
};
