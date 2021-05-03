#include "NewPong/NP_AudioPlayerComponent.h"
#include "Components/ActorComponent.h"
#include "FMODBlueprintStatics.h"
#include "Kismet/GameplayStatics.h"

UNP_AudioPlayerComponent::UNP_AudioPlayerComponent()
{
}

void UNP_AudioPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
	if (StartEventAtGameTime > 0.f)
		SetComponentTickEnabled(true);

	if (IsPlaying())
	{
		Stop();
	}
}

void UNP_AudioPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (UGameplayStatics::GetTimeSeconds(GetWorld()) > StartEventAtGameTime)
	{
		PlayAudio();
		SetComponentTickEnabled(false);
	}
}


void UNP_AudioPlayerComponent::PlayAudio()
{
	if (Event)
		Play();
}

bool UNP_AudioPlayerComponent::IsStudioValid()
{
	if (IFMODStudioModule::IsAvailable())
	{
		FMOD::Studio::System* StudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);
		if (StudioSystem)
		{
			return true;
		}
	}
	return false;
}