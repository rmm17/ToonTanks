// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankPawn.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#define SpringArmSubobject TEXT("Spring Arm")
#define CameraSubobject TEXT("Camera")

#define MoveForwardBinding TEXT("MoveForward")
#define TurnBinding TEXT("Turn")
#define FireBinding TEXT("Fire")

#define OUT

ATankPawn::ATankPawn()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(SpringArmSubobject);
	if (SpringArmComp) SpringArmComp->SetupAttachment(BaseMesh);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(CameraSubobject);
	if (CameraComp) CameraComp->SetupAttachment(SpringArmComp);
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!PlayerInputComponent) {
		UE_LOG(LogTemp, Error, TEXT("Object %s has no PlayerInputComponent set"), *GetName());
		return;
	}

	PlayerInputComponent->BindAxis(MoveForwardBinding, this, &ATankPawn::Move);
	PlayerInputComponent->BindAxis(TurnBinding, this, &ATankPawn::Rotate);
	PlayerInputComponent->BindAction(FireBinding, IE_Pressed, this, &ATankPawn::Fire);
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());

	if (!PlayerController)
		UE_LOG(LogTemp, Error, TEXT("Object %s has no PlayerController set"), *GetName());
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerController)
		return;

	FHitResult Hit;
	PlayerController->GetHitResultUnderCursor(
		ECollisionChannel::ECC_Visibility, 
		false, 
		OUT Hit
	);

	/*DrawDebugSphere(
		GetWorld(),
		Hit.ImpactPoint,
		25.f,
		12,
		FColor::Red,
		false,
		-1.f
	);*/

	RotateTurret(Hit.ImpactPoint);
}

void ATankPawn::Move(float Value)
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	float MoveOffset = Value * DeltaTime * MoveSpeed;
	
	FVector DeltaLocation{ MoveOffset, 0.f, 0.f };
	AddActorLocalOffset(DeltaLocation, true); //bSweep = true passed as parameter will make the translation check for collisions, allowing the engine to correct the movement in case a collision happens.
}

void ATankPawn::Rotate(float Value)
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	float RotateValue = Value * DeltaTime * TurnSpeed;
	
	FRotator DeltaRotation{ 0.f, RotateValue, 0.f };
	AddActorLocalRotation(DeltaRotation, true); //bSweep = true passed as parameter will make the translation check for collisions, allowing the engine to correct the rotation in case a collision happens.
}

void ATankPawn::HandleDestruction()
{
	Super::HandleDestruction();
	
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	bAlive = false;
}