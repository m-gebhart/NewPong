// Fill out your copyright notice in the Description page of Project Settings.


#include "NP_PaddlePlayerController.h"

#include "NP_Ball.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

#include "NP_Paddle.h"

ANP_PaddlePlayerController::ANP_PaddlePlayerController()
{
}

void ANP_PaddlePlayerController::BeginPlay()
{

	Paddle = Cast<ANP_Paddle>(GetPawn());
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACameraActor::StaticClass(), CameraActors);

	FViewTargetTransitionParams Params;
	SetViewTarget(CameraActors[0], Params);
	//SpawnBall();
	
	UWorld* const World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		LeftPaddle = World->SpawnActor<ANP_Paddle>(PaddleObj, LeftPaddleSpawnLocation, FRotator(0,0,0), SpawnParams);
	}
}

void ANP_PaddlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAxis("MovementWASD", this, &ANP_PaddlePlayerController::MovementWASD);
	InputComponent->BindAxis("MovementArrowKeys", this, &ANP_PaddlePlayerController::Movement);
}



void ANP_PaddlePlayerController::Movement(float f)
{
	Paddle = Cast<ANP_Paddle>(GetPawn());
	Paddle->Movement(f);
}

void ANP_PaddlePlayerController::MovementWASD(float f)
{

	float MoveDistance = f * LeftPaddleSpeed * GetWorld()->GetDeltaSeconds();
	if(LeftPaddle->GetActorLocation().X + MoveDistance > 700)
	{
		LeftPaddle->SetActorLocation(FVector(700,LeftPaddle->GetActorLocation().Y, 0));
	}
	else if(LeftPaddle->GetActorLocation().X + MoveDistance < -700)
	{
		LeftPaddle->SetActorLocation(FVector(-700,LeftPaddle->GetActorLocation().Y, 0));
	}
	else
	{
		LeftPaddle->SetActorLocation(LeftPaddle->GetActorLocation()+ FVector(MoveDistance,0,0));
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

void ANP_PaddlePlayerController::StartGame()
{
	SpawnBall();
}
