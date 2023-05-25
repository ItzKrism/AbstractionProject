// Copyright Epic Games, Inc. All Rights Reserved.


#include "AbstractionProjectGameModeBase.h"
#include "ObjectiveWorldSystem.h"

void AAbstractionProjectGameModeBase::StartPlay()
{
	Super::StartPlay();
	UObjectiveWorldSystem* ObjectiveWorldSystem = GetWorld()->GetSubsystem<UObjectiveWorldSystem>();
	if (ObjectiveWorldSystem)
	{
		ObjectiveWorldSystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveWorldSystem->DisplayObjectiveWidget();
	}
}

