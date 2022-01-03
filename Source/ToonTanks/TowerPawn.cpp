// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPawn.h"
#include "TankPawn.h"
#include "Kismet/GameplayStatics.h"


void ATowerPawn::BeginPlay() 
{
	Super::BeginPlay();

	TankPawn = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0)); // 0 is defined as the pawn number for the player (check auto possess player in the tank instance in the viewport)

	if (!TankPawn)
		UE_LOG(LogTemp, Error, TEXT("Object %s could not find a suitable player pawn."), *GetName());
}

void ATowerPawn::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	if (!TankPawn)
		return;

	// Find the distance to the tank
	float Distance = FVector::Dist(GetActorLocation(), TankPawn->GetActorLocation());

	// Check if the tank is in range
	if (Distance <= FireRange)
	{
		// If the tank is in range, rotate turret toward tank
		RotateTurret(TankPawn->GetActorLocation());
	}
}