// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveComponent.h"
#include "ObjectiveWorldSystem.generated.h"


UCLASS()
class ABSTRACTIONPROJECT_API UObjectiveWorldSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass);
	void DisplayObjectiveWidget();

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDesctiption();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(Blueprintcallable)
	void RemoveObjective(UObjectiveComponent* ObjectiveComponent);

	void ObObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState);

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription() { return TEXT("Open Door"); }

private:
	UUserWidget* ObjectiveWidget = nullptr;
	

	//add or remove them
	//sign up for callback on changed
	TArray<UObjectiveComponent*> Objectives;
};
