// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TankPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankPawn : public ABasePawn
{
	GENERATED_BODY()
	

public:
	// Sets default values for this pawn's properties
	ATankPawn();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
	FVector GetCameraViewPoint();

	APlayerController* GetPlayerController() const {
		return PlayerController;
	};

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Components", meta = (AllowPrivateAccess = "true"))
	class ULevelSectionComponent* LevelSectionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TurnSpeed = 80.f;

	APlayerController* PlayerController;

	void Move(float Value);
	void Rotate(float Value);
};
