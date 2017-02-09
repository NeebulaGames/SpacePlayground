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
	class UBillboardComponent* billboardComponent;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* sparkParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	class USoundWave* sparkSound;
	
private:
	
};
