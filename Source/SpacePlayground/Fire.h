// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "Fire.generated.h"

UCLASS()
class SPACEPLAYGROUND_API AFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFire();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	class UBillboardComponent* billboardComponent;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* fireParticleSystemComponent;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* smokeParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	class USoundWave* fireSound;

	UPROPERTY(EditAnywhere)
	class USoundWave* fireSparksSound;

	UPROPERTY(EditAnywhere)
	class USoundWave* smokeSound;

	UPROPERTY(EditAnywhere)
	USoundAttenuation* soundAttenuation;

	UPROPERTY(EditAnywhere)
	UAudioComponent* fireAudioComponent;

	UPROPERTY(EditAnywhere, Category = "Triggerable")
	class AActor* InteractableActorExtinguish;

	UPROPERTY(EditAnywhere, Category = "Triggerable")
	class AActor* InteractableActorReset;

private:
	UFUNCTION()
	void ExtinguishFire();

	UFUNCTION()
	void RestartFire();

	bool extinguished = false;
};
