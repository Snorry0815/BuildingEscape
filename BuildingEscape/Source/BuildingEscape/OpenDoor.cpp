#include "OpenDoor.h"

#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}

void UOpenDoor::OpenDoor()
{
	TimeToClose = GetWorld()->GetTimeSeconds() + DoorCloseDelay;

	if (bDoorIsOpen)
		return;

	bDoorIsOpen = true;
	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	if (!bDoorIsOpen)
		return;

	bDoorIsOpen = false;
	OnCloseRequest.Broadcast();
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OpenDoor();
		return;
	}

	if (!bDoorIsOpen)
		return;

	if (GetWorld()->GetTimeSeconds() > TimeToClose)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.f;

	if (PressurePlate == nullptr)
		return totalMass;

	TArray<AActor*> overlappingActors;
	PressurePlate->GetOverlappingActors(OUT overlappingActors);

	for (const auto* overlappingActor : overlappingActors)
	{
		auto* root = Cast<UPrimitiveComponent>(overlappingActor->GetRootComponent());
		if (root)
			totalMass += root->GetMass();

		UE_LOG(LogTemp, Warning, TEXT("OverlappingActor: %s"), *overlappingActor->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("Mass: %f"), totalMass);
	return totalMass;
}

