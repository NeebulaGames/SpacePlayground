// Fill out your copyright notice in the Description page of Project Settings.

#include "SpacePlayground.h"
#include "PlaygroundGameMode.h"
#include "PlaygroundCharacter.h"

APlaygroundGameMode::APlaygroundGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultPawnClass = APlaygroundCharacter::StaticClass();
}

void APlaygroundGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("NEEBULAGAMES SPACE PLAYGROUND"));
	}
}
