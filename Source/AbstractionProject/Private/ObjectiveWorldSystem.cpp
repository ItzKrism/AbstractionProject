// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSystem.h"
#include "Kismet/GameplayStatics.h"
#include "../AbstractionProjectGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ObjectivesHuds.h"

void UObjectiveWorldSystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass)
{
	if (ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}
}


void UObjectiveWorldSystem::DisplayObjectiveWidget()
{
	ensureMsgf(ObjectiveWidget, TEXT("UObjectiveWorldSystem::DisplayObjectiveWidget ObjectiveWidget is nullptr"));
	ObjectiveWidget->AddToViewport();
}

FString UObjectiveWorldSystem::GetCurrentObjectiveDescription()
{
	if(!Objectives.IsValidIndex(0) || Objectives[0]->GetState() == EObjectiveState::OS_Inactive)
	{
		return TEXT("N/A");
	}

	FString RetObjective = Objectives[0]->GetDescription();
	if (Objectives[0]->GetState() == EObjectiveState::OS_Completed)
	{
		RetObjective += TEXT(" Completed!");
	}

	return RetObjective;
}

void UObjectiveWorldSystem::AddObjective(UObjectiveComponent* ObjectiveComponent)
{
	check(ObjectiveComponent);
	size_t PrevSize = Objectives.Num();
	Objectives.AddUnique(ObjectiveComponent);
	if (Objectives.Num() > PrevSize)
	{
		ObjectiveComponent->OnStateChanged().AddUObject(this, &UObjectiveWorldSystem::OnObjectiveStateChanged);
	}
}

void UObjectiveWorldSystem::RemoveObjective(UObjectiveComponent* ObjectiveComponent)
{
	Objectives.Remove(ObjectiveComponent);
}

void UObjectiveWorldSystem::OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState)
{
	DisplayObjectiveWidget();
}