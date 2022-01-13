// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPawn.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "TankPawn.h"

#define OUT

void ATowerPawn::BeginPlay() 
{
	Super::BeginPlay();

	TankPawn = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0)); // 0 is defined as the pawn number for the player (check auto possess player in the tank instance in the viewport)

	if (!TankPawn)
		UE_LOG(LogTemp, Error, TEXT("Object %s could not find a suitable player pawn."), *GetName());

	// Sets a timed callback handled by Unreal Engine that calls ATowerPawn::CheckFireCondition, looping the callback every X seconds, in this case defined by FireRate.
	GetWorldTimerManager().SetTimer(OUT FireRateTimerHandle, this, &ATowerPawn::CheckFireCondition, FireRate, true);
}

void ATowerPawn::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	// Check if the tank is in range
	if (IsTankInRange())
	{
		// If the tank is in range, rotate turret toward tank
		RotateTurret(TankPawn->GetActorLocation());
	}
}

void ATowerPawn::CheckFireCondition()
{
	if (!TankPawn)
		return;

	// Check if the tank is in range
	if (IsTankInRange() && TankPawn->bAlive)
		Fire();
}

bool ATowerPawn::IsTankInRange()
{
	if (!TankPawn)
		return false;

	// Find the distance to the tank
	float Distance = FVector::Dist(GetActorLocation(), TankPawn->GetActorLocation());

	return Distance <= FireRange;
}

void ATowerPawn::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}