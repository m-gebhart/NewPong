// Fill out your copyright notice in the Description page of Project Settings.


#include "NP_PaddlePlayerController.h"

#include "NP_Ball.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

#include "NP_Paddle.h"
//#include Ball.h

ANP_PaddlePlayerController::ANP_PaddlePlayerController()
{
}

void ANP_PaddlePlayerController::BeginPlay()
{

	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACameraActor::StaticClass(), CameraActors);

	FViewTargetTransitionParams Params;
	SetViewTarget(CameraActors[0], Params);
	SpawnBall();
}

void ANP_PaddlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAxis("MovementWASD", this, &ANP_PaddlePlayerController::Movement);
	
}



void ANP_PaddlePlayerController::Movement(float f)
{
	
	auto MyPawn = Cast<ANP_Paddle>(GetPawn());

	if(MyPawn)
	{
		MyPawn->Movement((f));
	}
	
}

void ANP_PaddlePlayerController::Launch()
{
	MyBall->Launch();
	
}

void ANP_PaddlePlayerController::SpawnBall()
{
	if(!MyBall)
		MyBall = nullptr;

	if(BallObj)
	{
		MyBall = GetWorld()->SpawnActor<ANP_Ball>(BallObj, SpawnLocation, SpawnRotation, SpawnInfo);
	}

	Launch();
}
