// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NP_Ball.generated.h"

class UProjectileMovementComponent;

UCLASS()
class NEWPONG_API ANP_Ball : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANP_Ball();

	virtual void Launch();

	bool BallLaunched;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		UStaticMeshComponent* SM_Ball;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UProjectileMovementComponent* ProjectileMovementComponent;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

UFUNCTION()
	UStaticMeshComponent* GetBall();
	
};