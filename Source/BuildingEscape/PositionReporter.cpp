// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReporter.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	//Gets the objects name
	FString objectName = GetOwner()->GetName();
	
	//Gets the object position in the world
	FString objectPosition = GetOwner()->GetTransform().GetLocation().ToString();
	
	//Prints to the output console the name of the object and its position
	UE_LOG(LogTemp, Warning, TEXT("%s is at position: %s"), *objectName, *objectPosition);
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

