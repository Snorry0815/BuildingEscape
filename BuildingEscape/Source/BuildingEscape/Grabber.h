// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGrabber();
	void BindGrabActions();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void FindPhysicsHandleComponent();
	FHitResult GetFirstPhysicsBodyInReach() const;
	bool GetGrabbingLine(FVector& out_LineStart, FVector& out_LineEnd) const;

	void Grab();
	void Release();

	UPROPERTY(EditDefaultsOnly)
	float Reach = 100.f;

	class UPhysicsHandleComponent* PhysicsHandleComp = nullptr;
};
