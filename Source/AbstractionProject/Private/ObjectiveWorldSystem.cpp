// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSystem.h"
#include "Kismet/GameplayStatics.h"

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

void UObjectiveWorldSystem::OnObjectiveCompleted()
{
	DisplayObjectiveWidget();
}