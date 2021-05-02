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
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	this->SM_Ball->SetStaticMesh(SphereMeshAsset.Object);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	
}



// Called when the game starts or when spawned
void ANP_Ball::BeginPlay()
{
	Super::BeginPlay();
	SM_Ball -> SetSimulatePhysics(true);
	SM_Ball -> SetEnableGravity(false);
	SM_Ball -> SetConstraintMode(EDOFMode::XYPlane);
	SM_Ball -> SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Ball -> SetCollisionProfileName(TEXT("PhysicsActor"));

	
	
	
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 1.0f;
	ProjectileMovementComponent->Friction = 0.0f;
	ProjectileMovementComponent->Velocity.Z = 0.0f;
	
	SM_Ball->OnComponentBeginOverlap.AddDynamic(this, &ANP_Ball::OnOverlapBegin);
	
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
		UE_LOG(LogTemp, Warning, TEXT("EK"));
	}
	
}

UStaticMeshComponent* ANP_Ball::GetBall()
{
	return SM_Ball;
}

void ANP_Ball::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("I just started runningKEK"));
	if(SweepResult.GetActor()->GetName()== "RightGoal")
	{
		UE_LOG(LogTemp, Warning, TEXT("I just started running"));
	}
	else if(SweepResult.GetActor()->GetName()== "LeftGoal"){
		UE_LOG(LogTemp, Warning, TEXT("I just started running2"));
	}
	
}

