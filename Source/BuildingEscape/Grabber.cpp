
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

	GetPhysicsHandle();

	SetUpActions();
}

void UGrabber::SetUpActions()
{
	///Gets the input component on the object
	m_input = GetOwner()->FindComponentByClass<UInputComponent>();
	//Checks if the input component is found
	if (m_input)
	{
		m_input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		m_input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing input component"), *GetOwner()->GetName());
	}
}

void UGrabber::GetPhysicsHandle()
{
	///Gets the physics handle on the object
	m_physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//Checks if the physics handle is found
	if (m_physicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing physics handle component"), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_physicsHandle->GrabbedComponent) {
		///Creates storage for player view points
		FVector playerViewPointLocation;
		FRotator playerViewPointRotator;

		///Gets viewpoint values
		m_playerControler->GetPlayerViewPoint(OUT playerViewPointLocation, OUT playerViewPointRotator);

		///Creates a debug line from the player
		FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotator.Vector() * m_reach;

		m_physicsHandle->SetTargetLocation(lineTraceEnd);
	}
}

/*
Creates a ray cast from the defaut pawn to a point forward
*/
FHitResult UGrabber::RayCast(FVector &playerViewPointLocation, FVector &lineTraceEnd)
{
	///Set up query Parameters
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

	///Raycast
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		playerViewPointLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParameters
	);

	///Logs the raycasted actor
	AActor* hitActor = hit.GetActor();
	if (hitActor) {
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *hitActor->GetName());
	}

	return hit;
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///Creates storage for player view points
	FVector playerViewPointLocation;
	FRotator playerViewPointRotator;

	///Gets viewpoint values
	m_playerControler->GetPlayerViewPoint(OUT playerViewPointLocation, OUT playerViewPointRotator);

	///Creates a debug line from the player
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotator.Vector() * m_reach;
	//DrawDebugLine(GetWorld(), playerViewPointLocation, lineTraceEnd, FColor(225, 0, 0), false, 0.0f, 0, 10.0f);


	return RayCast(playerViewPointLocation, lineTraceEnd);
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbing"));

	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit) {
		//Attached a physics handle to the object
		m_physicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}	
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Releasing"));
	m_physicsHandle->ReleaseComponent();
}

