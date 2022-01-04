// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankToonsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankToonsGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void ActorDied(AActor* DeadActor);

protected: 

	virtual void BeginPlay() override;

	//BlueprintImplementableEvent allows adding this method in the game mode blueprint, and implement logic to it in there (while being invoked on the C++ side)
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:

	class ATankPawn* Tank;
	class AToonTanksPlayerController* PlayerController;

	float GameStartDelay = 3.f;

	void HandleGameStart();
};
