// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NP_LeftPaddlePlayerController.generated.h"

/**
 * 
 */
class ANP_Paddle;
UCLASS()
class NEWPONG_API ANP_LeftPaddlePlayerController : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION()
	virtual void SetupInputComponent() override;

	protected:
	virtual void BeginPlay() override;
	void MovementWASD(float f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ANP_Paddle> PaddleObj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LeftPaddleSpawnLocation;
	
	ANP_Paddle* LeftPaddle;
	
};
