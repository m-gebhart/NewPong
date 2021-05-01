// Fill out your copyright notice in the Description page of Project Settings.


#include "NP_Ball.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ANP_Ball::ANP_Ball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	RootComponent = SM_Ball;

	SM_Ball -> SetSimulatePhysics(true);
	SM_Ball -> SetEnableGravity(false);
    SM_Ball -> SetConstraintMode(EDOFMode::XYPlane);
	SM_Ball -> SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Ball -> SetCollisionProfileName(TEXT("PhysicsActor"));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 1.0f;
	ProjectileMovementComponent->Friction = 0.0f;
	ProjectileMovementComponent->Velocity.Z = 0.0f;
	
}



// Called when the game starts or when spawned
void ANP_Ball::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANP_Ball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANP_Ball::Launch()
{
	if(!BallLaunched)
	{
		SM_Ball->AddImpulse(FVector(0.0f,500.0f,0.0f), FName(), true);
		BallLaunched = true;
	}
	
}

UStaticMeshComponent* ANP_Ball::GetBall()
{
	return SM_Ball;
}

