// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include <DrawDebugHelpers.h>
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
	FindPhysicsComponent();
	SetupInputComponent();
}

void UGrabber::FindPhysicsComponent()
{
	physicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandleComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s is missing its physics component."), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent != nullptr)
	{
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Release", IE_Pressed, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s is missing its input component."), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (physicsHandleComponent->GrabbedComponent != nullptr)
	{
		// Get player viewpoint
		auto* player = GetWorld()->GetFirstPlayerController();

		FVector pos;
		FRotator rot;
		player->GetPlayerViewPoint(pos, rot);
		FVector lineTraceEnd = pos + rot.Vector() * 200.0f;
		physicsHandleComponent->SetTargetLocation(lineTraceEnd);
	}
}

void UGrabber::Grab()
{
	auto hitResult = GetFirstPhysicsBodyInReach();
	auto componentToGrab = hitResult.GetComponent();
	auto actorHit = hitResult.GetActor();

	///Verify what we hit
	if (actorHit != nullptr)
	{
		physicsHandleComponent->GrabComponentAtLocation(componentToGrab
			, NAME_None
			, componentToGrab->GetOwner()->GetActorLocation());
	}
}

void UGrabber::Release()
{
	physicsHandleComponent->ReleaseComponent();
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get player viewpoint
	auto* player = GetWorld()->GetFirstPlayerController();

	FVector pos;
	FRotator rot;
	player->GetPlayerViewPoint(pos, rot);

	//Ray cast for a specific distance
	FVector lineTraceEnd = pos + rot.Vector() * reach;

	FHitResult outHit;
	GetWorld()->LineTraceSingleByObjectType(outHit, pos, lineTraceEnd, { ECollisionChannel::ECC_PhysicsBody }, { FName(TEXT("")), false, GetOwner() });

	return outHit;
}

