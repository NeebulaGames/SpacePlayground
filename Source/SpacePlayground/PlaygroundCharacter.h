// All rights Neebula Games

#pragma once

#include "GameFramework/Character.h"
#include "PlaygroundCharacter.generated.h"

UCLASS()
class SPACEPLAYGROUND_API APlaygroundCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlaygroundCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	AActor* pickedObject = nullptr;
	FHitResult LastHitted;
	FVector offset = FVector(0.f, 0.f, 50.f);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//handles moving forward/backward
	UFUNCTION()
	void MoveForward(float Val);
	//handles strafing
	UFUNCTION()
	void MoveHorizontal(float Val);

	UFUNCTION()
	void OnStartJump();

	UFUNCTION()
	void OnStopJump();

private:
	void Use();
	
};
