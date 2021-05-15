// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h" 
#include "NP_GameStateBase.h"
#include "NP_PaddlePlayerController.h"
#include "NP_Ball.generated.h"

//class USphereComponent;
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
	
private:
	UPROPERTY()
	USoundConcurrency* soundConcurreny;

	UPROPERTY()
	FVector2D MinMaxPitch = FVector2D(0.95f, 1.05f);

	UPROPERTY()
	FVector2D PitchCacheVector;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* SM_Ball;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	float XImpulse;
	float YImpulse;

	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TotalStartForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinYForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* PaddleCollisionSoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* WallCollisionSoundCue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D MinMaxVolumeMultiplier = FVector2D(0.4f, 0.5f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D MinMaxPitchIncreaseOnPaddle = FVector2D(0.005f, 0.05f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D MinMaxPitchDecreaseOnWall = FVector2D(0.01f, 0.017f);
	
	virtual void Tick(float DeltaTime) override;

	void ResetBall();
	
UFUNCTION()
	UStaticMeshComponent* GetBall();

	UFUNCTION(BlueprintCallable)
	void GoalScored(bool Side);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	ANP_PaddlePlayerController* Controller;
	
};
