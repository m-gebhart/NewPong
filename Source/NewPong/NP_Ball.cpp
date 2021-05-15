// Fill out your copyright notice in the Description page of Project Settings.
    
    
    #include "NP_Ball.h"

#include <PxBatchQueryDesc.h>

#include "Components/StaticMeshComponent.h"
    #include "GameFramework/ProjectileMovementComponent.h"
	#include "Kismet/GameplayStatics.h" 
    #include "Math/UnrealMathUtility.h"
    #include "Kismet/KismetMathLibrary.h"
    #include "Kismet/KismetSystemLibrary.h"
    
    ANP_Ball::ANP_Ball()
    {
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
	SM_Ball->OnComponentHit.AddDynamic(this, &ANP_Ball::OnHit);
	Controller = GetWorld()->GetFirstPlayerController<ANP_PaddlePlayerController>();
}

// Called every frame
void ANP_Ball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANP_Ball::ResetBall()
{
	this->SetActorLocation(FVector(0,0,0));
	
	this->Reset();
	BallLaunched = false;
	Launch();
}

void ANP_Ball::Launch()
{
	if(!BallLaunched)
	{
		YImpulse = FMath::RandRange(MinYForce, TotalStartForce);
		XImpulse = TotalStartForce - YImpulse;

		int i = FMath::RandRange(0,3);

		switch (i)
		{
			case 0:
				break;
			case 1:
				YImpulse = -YImpulse;
			break;
			case 2:
				XImpulse = -XImpulse;
			break;
			case 3:
				YImpulse = -YImpulse;
				XImpulse = -XImpulse;
			break;
		}
		
		
		SM_Ball->AddImpulse(FVector(XImpulse,YImpulse,0.0f), FName(), true);
		BallLaunched = true;
	}
	
}

UStaticMeshComponent* ANP_Ball::GetBall()
{
	return SM_Ball;
}

void ANP_Ball::GoalScored(bool Side)
{
	
	if(Side)
	{
		Controller->P1Score++;
		Controller->P1Scored();
		//GetWorld()->GetGameState<ANP_GameStateBase>()->P1Score++;
	}
	else
	{
		Controller->P2Score++;
		Controller->P2Scored();
		//GetWorld()->GetGameState<ANP_GameStateBase>()->P2Score++;
	}
	GetWorld()->GetFirstPlayerController<ANP_PaddlePlayerController>()->SpawnBall();
	Destroy();

	if(UKismetMathLibrary::Abs(Controller->P1Score - Controller->P2Score) >= 9)
	{
		//UKismetSystemLibrary::QuitGame(GetWorld(),Controller,,true);
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	}
}

void ANP_Ball::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(SweepResult.GetActor()->GetName()== "RightGoal")
		GoalScored((true));
	else if(SweepResult.GetActor()->GetName()== "LeftGoal")
		GoalScored(false);
}

void ANP_Ball::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (CollisionSoundCue)
	{
		if (!OtherActor->GetName().EndsWith("Wall"))
		{
			MinMaxPitch += FVector2D(FMath::RandRange(0.f, MinMaxPitch.X), FMath::RandRange(0.f, MinMaxPitch.Y));
			UE_LOG(LogTemp, Warning, TEXT("Pitch range changed to %f and %f!"), MinMaxPitch.X, MinMaxPitch.Y);
		}
		else
		{
			MinMaxPitch = FVector2D(0.95f, 1.05f);
			UE_LOG(LogTemp, Warning, TEXT("Pitch reset to 1.f and 1.f!"));
		}
		const float tempPitch = FMath::RandRange(MinMaxPitch.X, MinMaxPitch.Y);
		const float tempVolume = FMath::RandRange(MinMaxVolumeMultiplier.X, MinMaxVolumeMultiplier.Y);
		UE_LOG(LogTemp, Warning, TEXT("Pitch is %f with Volume at %f"), tempPitch, tempVolume);
		UGameplayStatics::PlaySound2D(GetWorld(), CollisionSoundCue, tempVolume, tempPitch, 0.0f, soundConcurreny, this, false);
	}
}