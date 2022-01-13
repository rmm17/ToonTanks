// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSectionComponent.h"
#include "Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"

// Sets default values for this component's properties
ULevelSectionComponent::ULevelSectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULevelSectionComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Ideally we should be able to use these overlap events with a callback, but for some reason the callback isn't being triggered.
	// if (PartTwoTrigger)
	//		PartTwoTrigger->OnActorBeginOverlap.AddDynamic(this, &ULevelSectionComponent::OnPartTwoOverlap);
}


// Called every frame
void ULevelSectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PlayerPawn)
		return;

	// Ideally we would use overlapping events instead of checking if it's overlapping on tick method
	if (PartTwoTrigger && PartTwoTrigger->IsOverlappingActor(PlayerPawn))
		PlayerPawn->ChangeCameraViewPoint(PartTwoTargetArmLength, PartTwoCameraRotation);

	if (PartThreeTrigger && PartThreeTrigger->IsOverlappingActor(PlayerPawn))
		PlayerPawn->ChangeCameraViewPoint(PartThreeTargetArmLength, PartThreeCameraRotation);

	if (PartFourTrigger && PartFourTrigger->IsOverlappingActor(PlayerPawn))
		PlayerPawn->ChangeCameraViewPoint(PartFourTargetArmLength, PartFourCameraRotation);
}

/*void ULevelSectionComponent::OnPartTwoOverlap(class AActor* OverlappedActor, class AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor %s overlapped volume %s"), *OtherActor->GetName(), *OverlappedActor->GetName());
}*/

