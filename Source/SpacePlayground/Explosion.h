// All rights Neebula Games

#pragma once

#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "Explosion.generated.h"

UCLASS()
class SPACEPLAYGROUND_API AExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosion();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	class UBillboardComponent* BillboardComponent;

	UPROPERTY(EditAnywhere)
	class URadialForceComponent* RadialForceComponent;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystemComponent;

	class USoundWave* explosionSound;

private:
	void DelayedExplosion();
};
