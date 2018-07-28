// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

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


	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto* ownerAsPawn = Cast<APawn>(GetOwner());
	ensure(ownerAsPawn);

	auto* playerController = Cast<APlayerController>(ownerAsPawn->GetController());
	if (playerController == nullptr)
		return;

	FVector CameraLocation;
	FRotator CameraRotation;
	playerController->GetPlayerViewPoint(
		OUT CameraLocation, 
		OUT CameraRotation
	);

	FVector LineStart = CameraLocation;
	FVector LineEnd = CameraLocation + CameraRotation.Vector() * Reach;
	DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red, false, -1.f, 0, 5.f);

	//UE_LOG(LogTemp, Warning, TEXT("Grabber looking at %s with rotation %s."), *CameraLocation.ToString(), *CameraRotation.ToString());
}

