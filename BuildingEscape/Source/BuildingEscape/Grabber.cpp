// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	BindGrabActions();
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandleComp = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	ensure(PhysicsHandleComp);
}

void UGrabber::BindGrabActions()
{
	auto* InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (ensure(InputComponent))
	{
		InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
}


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbing!"));

	auto hit = GetFirstPhysicsBodyInReach();
	auto* hitComp = hit.GetComponent();
	if (hitComp)
	{
		PhysicsHandleComp->GrabComponentAtLocation(hitComp, NAME_None, hitComp->GetOwner()->GetActorLocation());
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult hit;

	FVector LineStart;
	FVector LineEnd;
	if (!GetGrabbingLine(OUT LineStart, OUT LineEnd))
		return hit;

	DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red, false, -1.f, 0, 5.f);


	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);

	FCollisionQueryParams QueryParam(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT hit, LineStart, LineEnd, ObjectQueryParams, QueryParam);

	return hit;
}

bool UGrabber::GetGrabbingLine(FVector& out_LineStart, FVector& out_LineEnd) const
{
	auto* ownerAsPawn = Cast<APawn>(GetOwner());
	ensure(ownerAsPawn);

	auto* playerController = Cast<APlayerController>(ownerAsPawn->GetController());
	if (playerController == nullptr)
	{
		return false;
	}

	FVector CameraLocation;
	FRotator CameraRotation;
	playerController->GetPlayerViewPoint(
		OUT CameraLocation,
		OUT CameraRotation
	);

	out_LineStart = CameraLocation;
	out_LineEnd = CameraLocation + CameraRotation.Vector() * Reach;
	return true;
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release!"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandleComp->GetGrabbedComponent())
	{
		FVector LineStart;
		FVector LineEnd;
		if (GetGrabbingLine(OUT LineStart, OUT LineEnd))
		{
			PhysicsHandleComp->SetTargetLocation(LineEnd);
		}

		UE_LOG(LogTemp, Warning, TEXT("Grabbing %s!"), *PhysicsHandleComp->GetGrabbedComponent()->GetOwner()->GetName());
	}
}

