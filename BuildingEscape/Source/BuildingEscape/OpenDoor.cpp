#include "OpenDoor.h"

#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	auto* PlayerController = GetWorld()->GetFirstPlayerController();
	ActorThatOpens = PlayerController->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	if (bDoorIsOpen)
		return;

	bDoorIsOpen = true;
	auto* owner = GetOwner();
	FRotator rot(0.f, -OpenAngleInDegree, 0.f);
	owner->AddActorWorldRotation(rot);
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((PressurePlate != nullptr) && PressurePlate->IsOverlappingActor(ActorThatOpens))
		OpenDoor();
}

