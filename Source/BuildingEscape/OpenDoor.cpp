// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Gets a pointer to the object
	m_owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOnTrigger() > m_requiredMass) {
		OpenDoor();
		m_lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	/*
	if(m_presurePad->IsOverlappingActor(m_interactableActor)) {
		OpenDoor();
		m_lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	*/

	if (GetWorld()->GetTimeSeconds() - m_lastDoorOpenTime > m_doorCloseDelay) {
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	//Creates a new rotator
	FRotator newRotation = FRotator(0.0f, -m_openAngle, 0.0f);

	//Sets the objects rotation to the new rotator
	m_owner->SetActorRotation(newRotation);
}

void UOpenDoor::CloseDoor()
{
	//Creates a new rotator
	FRotator newRotation = FRotator(0.0f, 0.0f, 0.0f);

	//Sets the objects rotation to the new rotator
	m_owner->SetActorRotation(newRotation);
}

float UOpenDoor::GetTotalMassOnTrigger()
{
	float totalMass = 0.0f;

	///Find all overlapping actors
	TArray<AActor*> overlappingActors;
	m_presurePad->GetOverlappingActors(OUT overlappingActors);

	for (const auto* actor : overlappingActors) {
		UE_LOG(LogTemp, Warning, TEXT("%s is on the plate"), *actor->GetName());
		//Find UPrimitiveComponent
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("Total mass: %f"), *totalMass);
	}

	return totalMass;
}