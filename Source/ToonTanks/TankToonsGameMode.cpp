// Fill out your copyright notice in the Description page of Project Settings.


#include "TankToonsGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"
#include "ToonTanksPlayerController.h"
#include "TowerPawn.h"

#define OUT

void ATankToonsGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATankToonsGameMode::HandleGameStart()
{
	Tank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (PlayerController)
	{
		PlayerController->SetInputEnabledState(false);

		FTimerHandle Handle;

		//Delegate to call method in player controller that enables input
		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(
			PlayerController, 
			&AToonTanksPlayerController::SetInputEnabledState, 
			true
		);

		//Setting timer in Unreal Engine to have the delegate call the method after the amount of seconds defined in GameStartDelay
		GetWorldTimerManager().SetTimer(OUT Handle, Delegate, GameStartDelay, false);
	}
}

void ATankToonsGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (PlayerController)
			PlayerController->SetInputEnabledState(false);
	}
	else if (auto DestroyedTower = Cast<ATowerPawn>(DeadActor))
		DestroyedTower->HandleDestruction();
}