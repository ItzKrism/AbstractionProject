// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWorldSystem.generated.h"


UCLASS()
class ABSTRACTIONPROJECT_API UObjectiveWorldSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass);
	void DisplayObjectiveWidget();

	void OnObjectiveCompleted();

private:
	UUserWidget* ObjectiveWidget = nullptr;
	
};
