// All rights Neebula Games

#pragma once

#include "Components/ActorComponent.h"
#include "TeleporterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEPLAYGROUND_API UTeleporterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeleporterComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere)
	FString NextLevel;

private:
	UFUNCTION()
	void OnOverlap(AActor* actor1, AActor* actor2);
};
