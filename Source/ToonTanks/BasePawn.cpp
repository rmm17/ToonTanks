// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Projectile.h"
#include "TankPawn.h"

#define CapsuleSubobject TEXT("Capsule Collider")
#define BaseMeshSubobject TEXT("Base Mesh")
#define TurretMeshSubobject TEXT("Turret Mesh")
#define ProjectileSpawnSubobject TEXT("Projectile Spawn Point")
#define WidgetSubobject TEXT("Health bar")

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(CapsuleSubobject);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(BaseMeshSubobject);
	if (BaseMesh) BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TurretMeshSubobject);
	if (TurretMesh) TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(ProjectileSpawnSubobject);
	if (ProjectileSpawnPoint) ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(WidgetSubobject);
	if (HealthComp) HealthComp->SetupAttachment(BaseMesh);

	RootComponent = CapsuleComp;
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	TankPawn = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0)); // 0 is defined as the pawn number for the player (check auto possess player in the tank instance in the viewport)
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateHealthBar();
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	if (!TurretMesh)
		return;

	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(LookAtRotation);
}

void ABasePawn::Fire()
{
	if (!ProjectileSpawnPoint)
		return;

	// auto allows the compiler to figure out the type to assign to a new variable
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileObject, 
		ProjectileSpawnPoint->GetComponentLocation(), 
		ProjectileSpawnPoint->GetComponentRotation()
	);

	// setting a owner to the projectile will allow us to determine the instigator of damage
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());

	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (DeathCameraShake && PlayerController)
		PlayerController->ClientStartCameraShake(DeathCameraShake);
}

void ABasePawn::RotateHealthBar()
{
	if (!TankPawn)
		return;

	if (!HealthComp)
		return;

	FVector ToTarget = TankPawn->GetCameraViewPoint() - HealthComp->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	HealthComp->SetWorldRotation(ToTarget.Rotation());
}

