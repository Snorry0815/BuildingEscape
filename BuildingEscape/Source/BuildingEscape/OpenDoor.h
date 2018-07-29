// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnCloseRequest;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetOpenAngleInDegree() const
	{
		return OpenAngleInDegree;
	}

private:
	float GetTotalMassOfActorsOnPlate();

	void OpenDoor();
	void CloseDoor();

	UPROPERTY(EditAnywhere)
	float OpenAngleInDegree = -90.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;
	float TimeToClose = 0.f;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 50.f;

	UPROPERTY(EditAnywhere)
	class ATriggerVolume* PressurePlate;

	bool bDoorIsOpen = false;
};
