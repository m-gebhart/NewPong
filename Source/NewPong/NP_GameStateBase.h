// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "NP_GameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class NEWPONG_API ANP_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int P1Score;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int P2Score;

	
};
