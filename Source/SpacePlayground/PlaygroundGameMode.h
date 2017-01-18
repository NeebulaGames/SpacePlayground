// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "PlaygroundGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACEPLAYGROUND_API APlaygroundGameMode : public AGameMode
{
	GENERATED_BODY()

	APlaygroundGameMode(const FObjectInitializer& ObjectInitializer);
	
	void StartPlay() override;
};
