// Fill out your copyright notice in the Description page of Project Settings.


#include "TankToonsGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"
#include "TowerPawn.h"

void ATankToonsGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATankToonsGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (auto PlayerController = Tank->GetPlayerController())
		{
			Tank->DisableInput(PlayerController);
			PlayerController->bShowMouseCursor = false;
		}
	}
	else if (auto DestroyedTower = Cast<ATowerPawn>(DeadActor))
		DestroyedTower->HandleDestruction();
}