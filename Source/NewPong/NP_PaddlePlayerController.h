// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NP_PaddlePlayerController.generated.h"

/**
 * 
 */

class ANP_Ball;

UCLASS()
class NEWPONG_API ANP_PaddlePlayerController : public APlayerController
{
	GENERATED_BODY()

	ANP_PaddlePlayerController();

	UFUNCTION()
		virtual void SetupInputComponent() override;

	protected:
	virtual void BeginPlay() override;
	void Movement(float f);
	
	void Launch();

	UPROPERTY(EditAnywhere)
		TSubclassOf<ANP_Ball> BallObj;

	ANP_Ball* MyBall;

	FVector SpawnLocation = FVector(0.0f,0.0f,0.0f);
	FRotator SpawnRotation = FRotator(0.0f,0.0f,0.0f);

	FActorSpawnParameters SpawnInfo;


	public:
		void SpawnBall();

	
};