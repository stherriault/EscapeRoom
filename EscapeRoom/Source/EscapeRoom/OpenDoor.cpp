// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	actorToOpenDoor = GetWorld()->GetFirstPlayerController()->GetPawn();

	initialDoorRotation = GetOwner()->GetActorRotation();
}

void UOpenDoor::OpenDoor()
{
	AActor* owner = GetOwner();
	owner->SetActorRotation(initialDoorRotation - FRotator(0.0f, openAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	AActor* owner = GetOwner();
	owner->SetActorRotation(initialDoorRotation);
}

void UOpenDoor::VerifyActorPresence()
{
	if (actorToOpenDoor != nullptr)
	{
		if (pressurePlate != nullptr)
		{
			if (pressurePlate->IsOverlappingActor(actorToOpenDoor) == true)
			{
				OpenDoor();
			}
			else
			{
				CloseDoor();
			}
		}
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	VerifyActorPresence();
}

