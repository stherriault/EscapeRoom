// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include <DrawDebugHelpers.h>


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

	UE_LOG(LogTemp, Warning, TEXT("Grabber ready to work."));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player viewpoint
	APlayerController* player = GetWorld()->GetFirstPlayerController();
	
	FVector pos;
	FRotator rot;
	player->GetPlayerViewPoint(pos, rot);
	
	//Ray cast for a specific distance
	FVector lineTraceEnd = pos + rot.Vector() * reach;
	DrawDebugLine(GetWorld(), pos, lineTraceEnd, { 255, 0, 0 }, false, 0.0f, 0, 10.0f);
	


	FHitResult outHit;
	GetWorld()->LineTraceSingleByObjectType(outHit, pos, lineTraceEnd, { ECollisionChannel::ECC_PhysicsBody }, { FName(TEXT("")), false, GetOwner() });
	
	///Verify what we hit
	AActor* actor = outHit.GetActor();
	if (actor!= nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit actor %s"), *actor->GetName());
	
		// Verify if what we hit is grabbable
	}



}

