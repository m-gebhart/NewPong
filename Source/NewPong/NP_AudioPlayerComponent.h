// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FMODEvent.h"
#include "FMODAudioComponent.h"
#include "fmod_studio.hpp"
#include "NP_AudioPlayerComponent.generated.h"

UCLASS(ClassGroup = (NewPongComponents), meta = (BlueprintSpawnableComponent)) 
class NEWPONG_API UNP_AudioPlayerComponent : public UFMODAudioComponent
{
	GENERATED_BODY()
	
	public:
	UNP_AudioPlayerComponent();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void PlayAudio();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartEventAtGameTime = 2.0f;

	private:
	bool IsStudioValid();
};