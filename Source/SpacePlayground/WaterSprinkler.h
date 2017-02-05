// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "WaterSprinkler.generated.h"

UCLASS()
class SPACEPLAYGROUND_API AWaterSprinkler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterSprinkler();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
protected:
	class UBillboardComponent* billboardComponent;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* waterfallSystemComponent;

	UPROPERTY(EditAnywhere)
	class USoundWave* waterSound;

	UPROPERTY(EditAnywhere)
		USoundAttenuation* soundAttenuation;

	UPROPERTY(EditAnywhere)
		UAudioComponent* waterAudioComponent;

public:
	void Start();
	void Stop();
	
	
};
