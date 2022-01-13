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
	
	bGameStart = true;
	CurrentPart = 1;

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

	bool bPartOne = bGameStart || (PartOneTrigger && PartOneTrigger->IsOverlappingActor(PlayerPawn));
	bool bPartTwo = (PartTwoTrigger && PartTwoTrigger->IsOverlappingActor(PlayerPawn)) || 
					(PartTwoBackTrigger && PartTwoBackTrigger->IsOverlappingActor(PlayerPawn));
	bool bPartThree = (PartThreeTrigger && PartThreeTrigger->IsOverlappingActor(PlayerPawn)) || 
					(PartThreeBackTrigger && PartThreeBackTrigger->IsOverlappingActor(PlayerPawn));
	bool bPartFour = PartFourTrigger && PartFourTrigger->IsOverlappingActor(PlayerPawn);

	int32 PartNumber = bPartOne ? 1 : bPartTwo ? 2 : bPartThree ? 3 : bPartFour ? 4 : CurrentPart;

	switch (PartNumber)
	{
		case 1:
			PlayerPawn->ChangeCameraViewPoint(PartOneTargetArmLength, PartOneCameraRotation);
			CurrentPart = 1;
			bGameStart = false;
			break;
		case 2:
			PlayerPawn->ChangeCameraViewPoint(PartTwoTargetArmLength, PartTwoCameraRotation);
			CurrentPart = 2;
			break;
		case 3:
			PlayerPawn->ChangeCameraViewPoint(PartThreeTargetArmLength, PartThreeCameraRotation);
			CurrentPart = 3;
			break;
		case 4:
			PlayerPawn->ChangeCameraViewPoint(PartFourTargetArmLength, PartFourCameraRotation);
			CurrentPart = 4;
			break;
		default:
			break;
	}
}

// Ideally we should be able to use these overlap events with a callback, but for some reason the callback isn't being triggered.
/*void ULevelSectionComponent::OnPartTwoOverlap(class AActor* OverlappedActor, class AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Actor %s overlapped volume %s"), *OtherActor->GetName(), *OverlappedActor->GetName());
}*/

