// Fill out your copyright notice in the Description page of Project Settings.

#include "SpacePlayground.h"
#include "PlaygroundGameMode.h"

APlaygroundGameMode::APlaygroundGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{}

void APlaygroundGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("NEEBULAGAMES SPACE PLAYGROUND"));
	}
}
