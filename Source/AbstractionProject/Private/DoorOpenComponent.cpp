// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpenComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDoorOpenComponent::UDoorOpenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UDoorOpenComponent::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	// ensure TimeToRotate is greater than EPSILON
	CurrentRotationTime = 0.0f;
	// ...
	
}


// Called every frame
void UDoorOpenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentRotationTime < TimeToRotate)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn)) 
			{
				CurrentRotationTime += DeltaTime;
				//const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				//const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FRotator(CurrentRoation) = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRoation);
			}
		}
	}
	// ...
}

