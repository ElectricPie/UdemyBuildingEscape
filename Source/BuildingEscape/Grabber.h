// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
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
	APlayerController* m_playerControler;
	UPROPERTY(EditAnywhere)
	float m_reach = 100.0f;

	UPhysicsHandleComponent* m_physicsHandle = nullptr;
	UInputComponent* m_input = nullptr;

	void SetUpActions();

	void GetPhysicsHandle();

	FHitResult RayCast(FVector &playerViewPointLocation, FVector &lineTraceEnd);

	const FHitResult GetFirstPhysicsBodyInReach();

	void Grab();

	void Release();
};
