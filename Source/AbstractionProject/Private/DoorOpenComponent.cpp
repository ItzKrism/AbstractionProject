// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpenComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "ObjectiveWorldSystem.h"
#include "DrawDebugHelpers.h"
#include "InteractionComponent.h"



using namespace std;



constexpr float FLT_METERS(float meters) { return meters * 100.0f; }

static TAutoConsoleVariable<bool> CVarToggleDebugDoor(TEXT("Abstraction.DoorOpenComponent.Debug"), false, TEXT("Toggle OpenDoorComponent debug display."), ECVF_Default);

// Sets default values for this component's properties
UDoorOpenComponent::UDoorOpenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	DoorState = EDoorState::DS_Locked;

	CVarToggleDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&UDoorOpenComponent::OnDebugToggled));
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
	if (DoorState == EDoorState::DS_Locked)
	{
		if (LockedTriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && LockedTriggerBox->IsOverlappingActor(PlayerPawn))
			{
				DoorState = EDoorState::DS_Closed;
				CurrentRotationTime = 0.0f;
			}
		}
	}
	else if (DoorState == EDoorState::DS_Closed)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn)) 
			{
				DoorState = EDoorState::DS_Opening;
				CurrentRotationTime = 0.0f;
			}
		}
	}
	else if (DoorState == EDoorState::DS_Opening)
	{
		CurrentRotationTime += DeltaTime;
		const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FRotator(CurrentRoation) = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRoation);
		if (TimeRatio >= 1.0f)
		{
			OnDoorOpen();
		}
	}
	else if (DoorState == EDoorState::DS_Open)
	{
		if (ClosingTriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && ClosingTriggerBox->IsOverlappingActor(PlayerPawn) == false)
			{
				DoorState = EDoorState::DS_Closing;
				CurrentRotationTime = 0.0f;
			}
		}
	}
	else if (DoorState == EDoorState::DS_Closing)
	{
		CurrentRotationTime += DeltaTime;
		const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FRotator(CurrentRoation) = FMath::Lerp(FinalRotation, StartRotation, RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRoation);
		if (TimeRatio >= 1.0f)
		{
			OnDoorClose();
		}
	}
	// ...

	DebugDraw();
}

void UDoorOpenComponent::OnDoorClose()
{
	DoorState = EDoorState::DS_Closed;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Door Closed"));
}


void UDoorOpenComponent::OnDoorOpen()
{
	DoorState = EDoorState::DS_Open;
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Door Opened"));
	//tell any listeners that the interaction is successful
	InteractionSuccess.Broadcast();
}

void UDoorOpenComponent::OnDebugToggled(IConsoleVariable* Var)
{
	UE_LOG(LogTemp, Warning, TEXT("OnDebugToggled"));
}

void UDoorOpenComponent::DebugDraw()
{
	if (CVarToggleDebugDoor->GetBool())
	{
		FVector Offset(FLT_METERS(-0.75f), 0.0f, FLT_METERS(2.5f));
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
		FString EnumAsString = TEXT("Door State: ") + UEnum::GetDisplayValueAsText(DoorState).ToString();
		DrawDebugString(GetWorld(), Offset, EnumAsString, GetOwner(), FColor::Blue, 0.0f);
	}
}

void UDoorOpenComponent::InteractionStart()
{
	Super::InteractionStart();
	if(InteractingActor)
	{
		OpenDoor();
	}
}

void UDoorOpenComponent::OpenDoor()
{
	if(IsOpen() || DoorState == EDoorState::DS_Opening)
	{
		return;
	}

	DoorState = EDoorState::DS_Opening;
	CurrentRotationTime = 0.0f;
}
