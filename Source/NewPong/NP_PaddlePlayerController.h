// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NP_PaddlePlayerController.generated.h"

/**
 * 
 */

class ANP_Ball;
class ANP_Paddle;

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
	void MovementWASD(float f);
	
	void Launch();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool P1Selected;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool P2Selected;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int P1Soundtrack;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int P2Soundtrack;
	

	UPROPERTY(EditAnywhere)
		TSubclassOf<ANP_Ball> BallObj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ANP_Paddle> PaddleObj;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LeftPaddleSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LeftPaddleSpeed;
	
	ANP_Ball* MyBall;
	ANP_Paddle* LeftPaddle;
	ANP_Paddle* Paddle;
	
	
	FVector SpawnLocation = FVector(0.0f,0.0f,0.0f);
	FRotator SpawnRotation = FRotator(0.0f,0.0f,0.0f);

	FActorSpawnParameters SpawnInfo;


	public:
		void SpawnBall();

	UFUNCTION(BlueprintCallable)
		void StartGame();

	
	
};