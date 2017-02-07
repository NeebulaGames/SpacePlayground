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

	UPROPERTY(EditAnywhere, Category = "Triggerable")
		class AActor* interactableActor;

	UPROPERTY(EditAnywhere, Category = "Triggerable")
		bool startActivated = false;

public:
	UFUNCTION()
	void Start();

	UFUNCTION()
	void Stop();

	UFUNCTION()
	void StartWithTimer();

private:
	bool isActive = false;
	
	
};
