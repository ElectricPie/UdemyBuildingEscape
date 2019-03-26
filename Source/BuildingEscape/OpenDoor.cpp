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

	GetDefaultPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(m_presurePad->IsOverlappingActor(m_interactableActor)) {
		OpenDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	//Gets a pointer to the object
	AActor *owner = GetOwner();

	//Gets and prints the objects roation to the output log
	FString roation = owner->GetTransform().GetRotation().Euler().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Object roation is: %s"), *roation);

	//Creates a new rotator
	FRotator newRotation = FRotator(0.0f, -45.0f, 0.0f);

	//Sets the objects rotation to the new rotator
	owner->SetActorRotation(newRotation);
}

void UOpenDoor::GetDefaultPawn()
{
	//Gets the default pawn
	m_interactableActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}