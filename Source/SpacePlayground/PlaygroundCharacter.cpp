// All rights Neebula Games

#include "SpacePlayground.h"
#include "PlaygroundCharacter.h"


// Sets default values
APlaygroundCharacter::APlaygroundCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlaygroundCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using Character!"));
}

// Called every frame
void APlaygroundCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APlaygroundCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputComponent->BindAxis("Forward", this, &APlaygroundCharacter::MoveForward);
	InputComponent->BindAxis("Horizontal", this, &APlaygroundCharacter::MoveHorizontal);
	InputComponent->BindAxis("Turn", this, &APlaygroundCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APlaygroundCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APlaygroundCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &APlaygroundCharacter::OnStopJump);
}

void APlaygroundCharacter::MoveForward(float Val)
{
	if ((Controller != nullptr) && (Val != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);
	}
}

void APlaygroundCharacter::MoveHorizontal(float Val)
{
	if ((Controller != nullptr) && (Val != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Val);
	}
}

void APlaygroundCharacter::OnStartJump()
{
	bPressedJump = true;
}

void APlaygroundCharacter::OnStopJump()
{
	bPressedJump = false;
}

