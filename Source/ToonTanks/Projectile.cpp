// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

#define ProjectileSubobject TEXT("Projectile")
#define ProjectileMovementSubobject TEXT("Projectile Movement")
#define ParticleSystemSubobject TEXT("Particle System")

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(ProjectileSubobject);
	RootComponent = ProjectileMesh;

	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(ParticleSystemSubobject);
	ParticleSystemComp->SetupAttachment(RootComponent);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(ProjectileMovementSubobject);

	if (!ProjectileMovementComp)
		return;

	ProjectileMovementComp->InitialSpeed = 1300.f;
	ProjectileMovementComp->MaxSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//Add method callback to component hit delegate (AddDynamic is a macro, not found by Intellisense autocomplete). Unreal Engine will call OnHit whenever a projectile collision happens.
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary> 
/// Method to be passed as callback to OnComponentHit delegate that detects collisions
/// </summary>
/// <param name="HitComp">refers to the component that made the hit, in this case it would be the Projectile</param>
/// <param name="OtherActor">refers to the Actor that was hit, e.g. can be used to identify if a TowerPawn was hit</param>
/// <param name="OtherComp">refers to the specific component that was hit (e.g. TurretMesh if we hit a TowerPawn in its turret, BaseMesh if we hit a TowerPawn in its base)</param>
/// <param name="NormalImpulse">is a vector that represents the impulse of the collision</param>
/// <param name="Hit">has additional information of the collision</param>
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	auto ProjectileOwner = GetOwner();

	if (!ProjectileOwner)
	{
		Destroy();
		return;
	}

	auto ProjectileInstigator = ProjectileOwner->GetInstigatorController();
	auto DamageType = UDamageType::StaticClass();

	// OtherActor: checks if it's not null
	// OtherActor != this: prevents damage from affecting this projectile (collision events from this instance to this instance are ignored)
	// OtherActor != ProjectileOwner: prevents damage of this projectile to affect it's owner (collision events that affect the owner of this projectile are ignored)
	if (OtherActor && OtherActor != this && OtherActor != ProjectileOwner)
	{
		// This will generate an event to by broadcast by Unreal Engine OnTakeAnyDamage delegate with the defined parameters
		UGameplayStatics::ApplyDamage(OtherActor, Damage, ProjectileInstigator, this, DamageType);

		if (HitParticles)
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());

		if (HitSound)
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, OtherActor->GetActorLocation());

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (HitCameraShake && PlayerController)
			PlayerController->ClientStartCameraShake(HitCameraShake);
	}

	Destroy();
}

