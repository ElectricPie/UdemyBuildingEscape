// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"

#define OUT

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

	UE_LOG(LogTemp, Warning, TEXT("Grabber started"));

	m_playerControler = GetWorld()->GetFirstPlayerController();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetViewPoint();
}

void UGrabber::GetViewPoint()
{
	//Creates storage for player view points
	FVector playerViewPointLocation;
	FRotator playerViewPointRotator;

	//Gets viewpoint values
	m_playerControler->GetPlayerViewPoint(OUT playerViewPointLocation, OUT playerViewPointRotator);

	//Post a message with the location and rotation of the viewpoints
	//UE_LOG(LogTemp, Warning, TEXT("Player Location: %s | Player Rotation: %s"), *playerViewPointLocation.ToString(), *playerViewPointRotator.ToString());

	//Creates a debug line from the player
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotator.Vector() * m_reach;
	DrawDebugLine(GetWorld(), playerViewPointLocation, lineTraceEnd, FColor(225, 0, 0), false, 0.0f, 0, 10.0f);
}

