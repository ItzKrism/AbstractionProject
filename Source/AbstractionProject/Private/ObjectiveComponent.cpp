// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveComponent.h"
#include "ObjectiveWorldSystem.h"

// Sets default values for this component's properties
UObjectiveComponent::UObjectiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	State = EObjectiveState::OS_Inactive;
	// ...
}

void UObjectiveComponent::SetState(EObjectiveState NewState)
{
	if(NewState != State)
	{
		State = NewState;
		StateChangedEvent.Broadcast(this, State);
	}
}

// Called when the game starts
void UObjectiveComponent::BeginPlay()
{
	Super::BeginPlay();

	//Register
	UObjectiveWorldSystem* ObjectiveWorldSystem = GetWorld()->GetSubsystem<UObjectiveWorldSystem>();
	if(ObjectiveWorldSystem)
	{
		ObjectiveWorldSystem->AddObjective(this);
	}
	
}


// Called every frame
void UObjectiveComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UObjectiveWorldSystem* ObjectiveWorldSystem = GetWorld()->GetSubsystem<UObjectiveWorldSystem>();
	if (ObjectiveWorldSystem)
	{
		ObjectiveWorldSystem->RemoveObjective(this);
	}
	Super::EndPlay(EndPlayReason);
}

