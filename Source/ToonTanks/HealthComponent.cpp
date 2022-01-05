// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "HealthWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TankToonsGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	//Add method callback to OnTakeAnyDamage delegate (AddDynamic is a macro, not found by Intellisense autocomplete). Unreal Engine will call DamageTaken whenever a damage event is set
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	GameMode = Cast<ATankToonsGameMode>(UGameplayStatics::GetGameMode(this));

	UpdateProgressBar(1.0f);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/// <summary> 
/// Method to be passed as callback to OnTakeAnyDamage delegate that detects damage events
/// </summary>
/// <param name="DamagedActor">refers to the actor that was damaged</param>
/// <param name="Damage">refers to the amount of damage taken</param>
/// <param name="DamageType">refers to the kind of damage represented (e.g. fire damage, poison damage, ...). In Toon Tanks we are not discriminating types of damage</param>
/// <param name="Instigator">Controller responsible for causing this damage</param>
/// <param name="DamageCauser">refers to the actor that caused the damage</param>
void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f)
		return;

	Health -= Damage;

	if (GameMode && Health <= 0.f)
		GameMode->ActorDied(DamagedActor);

	UpdateProgressBar(Health / MaxHealth);
}

void UHealthComponent::UpdateProgressBar(float HealthPercentage)
{
	UHealthWidget *HealthWidget = Cast<UHealthWidget>(GetUserWidgetObject());

	if (HealthWidget) 
		HealthWidget->UpdateHealthPercent(HealthPercentage);
}

