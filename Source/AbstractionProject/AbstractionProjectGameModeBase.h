// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "AbstractionProjectGameModeBase.generated.h"


UCLASS()
class ABSTRACTIONPROJECT_API AAbstractionProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ObjectiveWidgetClass;
};
