// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InteractableDoor.generated.h"


class UDoorOpenComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpen);

UCLASS()
class ABSTRACTIONPROJECT_API AInteractableDoor : public AStaticMeshActor
{
	GENERATED_BODY()


public:
	AInteractableDoor();
	virtual void BeginPlay() override;

	float InterationTime = 5.0f;

	UPROPERTY(BluePrintAssignable, Category = "Door Interaction")
	FOnDoorOpen OnDoorOpen;

protected:
	UFUNCTION()
	void OnInteractionSuccess();
	UPROPERTY(EditAnywhere, NoClear)
	UDoorOpenComponent* DoorInteractionComponent;
};
