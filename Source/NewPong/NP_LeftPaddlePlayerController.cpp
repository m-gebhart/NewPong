// Fill out your copyright notice in the Description page of Project Settings.


#include "NP_LeftPaddlePlayerController.h"
#include "NP_Paddle.h"

void ANP_LeftPaddlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAxis("MovementWASD", this, &ANP_LeftPaddlePlayerController::MovementWASD);
}

void ANP_LeftPaddlePlayerController::BeginPlay()
{
	UWorld* const World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		LeftPaddle = World->SpawnActor<ANP_Paddle>(PaddleObj, LeftPaddleSpawnLocation, FRotator(0,0,0), SpawnParams);
	}
	this->Possess(LeftPaddle);
}

void ANP_LeftPaddlePlayerController::MovementWASD(float f)
{
	if(LeftPaddle)
	{
		LeftPaddle->Movement((f));
	}
}
