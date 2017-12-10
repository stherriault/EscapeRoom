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

	owner = GetOwner();

	initialDoorRotation = GetOwner()->GetActorRotation();
}

void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(initialDoorRotation - FRotator(0.0f, openAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(initialDoorRotation);
}

void UOpenDoor::VerifyActorPresence()
{
	if (GetTotalMassOfActorsOnPlate() > 80.0f)
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	if (pressurePlate != nullptr)
	{
		TArray<AActor*> overlappingActors;
		pressurePlate->GetOverlappingActors(overlappingActors);
		for(const auto* actor : overlappingActors)
		{
			TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}

	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	VerifyActorPresence();

	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay)
	{
		CloseDoor();
	}
}

