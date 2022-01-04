// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// BaseMesh was moved to protected encapsulation to be accessible to the TankPawn, to attach the spring arm component to BaseMesh (for some reason, the camera was rotating based on the turret mesh and not the root component)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BaseMesh;

	void RotateTurret(FVector LookAtTarget);
	void Fire();
private:
	/* 
		forward declaring with class let's the compiler know UCapsuleComponent is
		an existing type without having to #include it (this avoids includes
		where they are not necessary, but we have to include in .cpp to access it's methodsU) 
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileObject;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;
};
