// Fill out your copyright notice in the Description page of Project Settings.

#include "NP_Paddle.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ANP_Paddle::ANP_Paddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Paddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
	RootComponent = SM_Paddle;

	SM_Paddle->SetSimulatePhysics(true);
	
	SM_Paddle->SetEnableGravity(false);
	SM_Paddle->SetConstraintMode(EDOFMode::XYPlane);
	SM_Paddle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Paddle->SetCollisionProfileName(TEXT("Pawn"));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));
}

// Called when the game starts or when spawned
void ANP_Paddle::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ANP_Paddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANP_Paddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANP_Paddle::Movement(float f)
{
	AddMovementInput(FVector(f,0.0f,0.0f), 1.0f, false);
}

void ANP_Paddle::MovementWASD(float f)
{
	AddMovementInput(FVector(f,0.0f,0.0f), 1.0f, false);
}

