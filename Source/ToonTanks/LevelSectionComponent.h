// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LevelSectionComponent.generated.h"

class ATriggerVolume;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API ULevelSectionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelSectionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditInstanceOnly, Category = "Level Sections")
	ATriggerVolume* PartOneTrigger;

	UPROPERTY(EditInstanceOnly, Category = "Level Sections")
	ATriggerVolume* PartTwoTrigger;

	UPROPERTY(EditInstanceOnly, Category = "Level Sections")
	ATriggerVolume* PartTwoBackTrigger;

	UPROPERTY(EditInstanceOnly, Category = "Level Sections")
	ATriggerVolume* PartThreeTrigger;

	UPROPERTY(EditInstanceOnly, Category = "Level Sections")
	ATriggerVolume* PartThreeBackTrigger;

	UPROPERTY(EditInstanceOnly, Category = "Level Sections")
	ATriggerVolume* PartFourTrigger;

	UPROPERTY(EditAnywhere, Category = "Level Sections")
	float PartOneTargetArmLength = 600.f;

	UPROPERTY(EditAnywhere, Category = "Level Sections")
	FRotator PartOneCameraRotation = FRotator(-35.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Level Sections")
	float PartTwoTargetArmLength = 3000.f;

	UPROPERTY(EditAnywhere, Category = "Level Sections")
	FRotator PartTwoCameraRotation = FRotator(-90.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Level Sections")
	float PartThreeTargetArmLength = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Level Sections")
	FRotator PartThreeCameraRotation = FRotator(-15.f, 270.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Level Sections")
	float PartFourTargetArmLength = 600.f;

	UPROPERTY(EditAnywhere, Category = "Level Sections")
	FRotator PartFourCameraRotation = FRotator(-35.f, 0.f, 0.f);

	class ATankPawn* PlayerPawn;

	bool bGameStart = true;

	int32 CurrentPart = 1;

//	void OnPartTwoOverlap(class AActor* OverlappedActor, class AActor* OtherActor);
};
