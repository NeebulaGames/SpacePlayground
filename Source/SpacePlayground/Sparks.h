// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "Sparks.generated.h"

UCLASS()
class SPACEPLAYGROUND_API ASparks : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASparks();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	//class UBillboardComponent* billboardComponent;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* sparkParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	class USoundCue* sparksSound;

	UPROPERTY(EditAnywhere)
	UAudioComponent* sparkAudioComponent;

	UPROPERTY(EditAnywhere)
	UPointLightComponent* sparkPointLightComponent;

	UPROPERTY()
	UTimelineComponent* BrightnessControl;

	UPROPERTY()
	UCurveFloat* fCurve;

	FOnTimelineFloat InterpFunction{};
	
private:
	UFUNCTION()
	float GetRandomDelay() const;

	UFUNCTION()
	void TimelineFloatReturn(float val) const;

	float delay = 0.f;
	float sparkTime = 0.f;

	const float minRand = 1.2f;
	const float maxRand = 4.0f;
};
