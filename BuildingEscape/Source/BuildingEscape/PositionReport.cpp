#include "PositionReport.h"

#include "GameFramework/Actor.h"

UPositionReport::UPositionReport()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectPos = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Position report reporting for duty on %s at location %s!"), *GetOwner()->GetName(), *ObjectPos);

}

void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

