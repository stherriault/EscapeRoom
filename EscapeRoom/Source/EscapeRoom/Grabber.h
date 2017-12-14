// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

class UPhysicsHandleComponent;
class InputComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float reach = 100.0f;

	UPhysicsHandleComponent* physicsHandleComponent = nullptr;

	UInputComponent* inputComponent = nullptr;

	//Grab what's in view
	void Grab();

	//Release the grabbed object
	void Release();

	void FindPhysicsComponent();
	void SetupInputComponent();
	FHitResult GetFirstPhysicsBodyInReach();
};
