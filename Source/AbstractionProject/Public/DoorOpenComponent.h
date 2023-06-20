// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "DoorOpenComponent.generated.h"

class ATriggerBox;
class IConsoleVariable;

UENUM()
enum class EDoorState
{
	//Displays a text prompt if the door is closed, open, or locked
	DS_Closed = 0	UMETA(DisplayName = "Closed"),
	DS_Opening = 1	UMETA(DisplayName = "Opening"),
	DS_Open = 2		UMETA(DisplayName = "Open"),
	DS_Closing = 3	UMETA(DisplayName = "Closing"),
	DS_Locked = 4	UMETA(DisplayName = "Locked"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTIONPROJECT_API UDoorOpenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpenComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	DECLARE_EVENT(FDoorOpenComponent, FOpened)
	FOpened& OnOpened() { return OpenedEvent; }

	FOpened OpenedEvent;

	void OnDoorOpen();

	void OnDoorClose();


	static void OnDebugToggled(IConsoleVariable* Var);
	void DebugDraw();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//binded to interaction imput from player
	void InteractionStart() override;

	//request to open the door
	UFUNCTION(BlueprinCallable)
	void OpenDoor();

	UFUNCTION(BlueprintCallable)
	bool IsOpen() { return DoorState == EDoorState::DS_Open; }

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator :: ZeroRotator;

	FRotator StartRotation = FRotator :: ZeroRotator;

	FRotator FinalRotation = FRotator :: ZeroRotator;

	UPROPERTY(EditAnywhere)
	float TimeToRotate = 1.0f;

	float CurrentRotationTime = 0.0f;

	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggerBox;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve OpenCurve;

	UPROPERTY(BlueprintReadOnly)
	EDoorState DoorState;

	UPROPERTY(EditAnywhere)
	ATriggerBox* ClosingTriggerBox;

	UPROPERTY(EditAnywhere)
	ATriggerBox* LockedTriggerBox;
};
