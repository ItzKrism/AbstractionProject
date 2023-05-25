// Copyright Epic Games, Inc. All Rights Reserved.


#include "AbstractionProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AAbstractionProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	if(ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}

	if (ObjectiveWidget)
	{
		ObjectiveWidget->AddToViewport();
	}
}

