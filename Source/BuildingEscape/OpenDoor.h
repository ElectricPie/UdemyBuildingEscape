// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* m_presurePad;

	AActor* m_owner;

	AActor* m_interactableActor;

	//How far the door opens
	UPROPERTY(EditAnywhere)
	float m_openAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	float m_doorCloseDelay;

	float m_lastDoorOpenTime;

	UPROPERTY(EditAnywhere)
	float m_requiredMass = 60.0f;

	float GetTotalMassOnTrigger();
};
