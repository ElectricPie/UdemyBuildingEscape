// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

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

	GetDefaultPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(m_presurePad->IsOverlappingActor(m_interactableActor)) {
		OpenDoor();
		m_lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

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

void UOpenDoor::GetDefaultPawn()
{
	//Gets the default pawn
	m_interactableActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}