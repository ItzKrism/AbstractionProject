// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"
#include "DoorOpenComponent.h"

AInteractableDoor::AInteractableDoor()
{
	DoorInteractionComponent = CreateDefaultSubobject<UDoorOpenComponent>(TEXT("DoorOpenComponent"));
}

