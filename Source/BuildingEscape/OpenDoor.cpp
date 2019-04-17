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
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOnTrigger() > m_requiredMass) {
		onOpen.Broadcast();
	}
	else {
		onClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOnTrigger()
{
	float totalMass = 0.0f;

	if (m_presurePad) {
		///Find all overlapping actors
		TArray<AActor*> overlappingActors;
		m_presurePad->GetOverlappingActors(OUT overlappingActors);

		for (const auto* actor : overlappingActors) {
			//UE_LOG(LogTemp, Warning, TEXT("%s is on the plate"), *actor->GetName());
			//Find UPrimitiveComponent
			totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}

	return totalMass;
}