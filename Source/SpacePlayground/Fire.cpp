// All rights Neebula Games

#include "SpacePlayground.h"
#include "InteractableComponent.h"
#include "Fire.h"
#include "TeleporterComponent.h"


// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	billboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	billboardComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> firePS(TEXT("ParticleSystem'/Game/Particles/P_Fire.P_Fire'"));

	fireParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticleSystem"));
	fireParticleSystemComponent->SetupAttachment(billboardComponent);
	fireParticleSystemComponent->SetTemplate(firePS.Object);
	fireParticleSystemComponent->bAutoActivate = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> smokePS(TEXT("ParticleSystem'/Game/Particles/P_Smoke.P_Smoke'"));

	smokeParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokeParticleSystem"));
	smokeParticleSystemComponent->SetupAttachment(billboardComponent);
	smokeParticleSystemComponent->SetTemplate(smokePS.Object);
	smokeParticleSystemComponent->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundAttenuation> soundAttenuance(TEXT("SoundAttenuation'/Game/Effects/AttenuationDistanceEffect.AttenuationDistanceEffect'"));

	this->soundAttenuation = soundAttenuance.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> fireSound(TEXT("SoundWave'/Game/Sounds/Fire01.Fire01'"));
	this->fireSound = fireSound.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> fireSparksSound(TEXT("SoundWave'/Game/Sounds/Fire_Sparks01.Fire_Sparks01'"));
	this->fireSparksSound = fireSparksSound.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> smokeSound(TEXT("SoundWave'/Game/Sounds/Smoke01.Smoke01'"));
	this->smokeSound = smokeSound.Object;
	this->smokeSound->Volume = 0.3f;

	fireAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("fireAudioComponent"));
	fireAudioComponent->bAutoActivate = false;
	fireAudioComponent->SetupAttachment(billboardComponent);
	fireAudioComponent->AttenuationSettings = soundAttenuation;

}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();

	fireAudioComponent->SetWorldLocation(GetActorLocation());

	if (fireAudioComponent->IsValidLowLevelFast()) {
		fireAudioComponent->SetSound(fireSparksSound);
	}

	fireAudioComponent->Play();

	if (interactableActorExtinguish != nullptr)
	{
		UInteractableComponent* InteractableComponent = interactableActorExtinguish->FindComponentByClass<UInteractableComponent>();
		if (ensureMsgf(InteractableComponent != nullptr, TEXT("The selected trigger is not ineractive!")))
		{
			if (!extincWithSprinkler)
				InteractableComponent->OnTriggerAction.AddDynamic(this, &AFire::ExtinguishFire);
			else
				InteractableComponent->OnTriggerAction.AddDynamic(this, &AFire::DelayedExtinguishFire);
		}	
	}

	if (interactableActorReset != nullptr)
	{
		UInteractableComponent* InteractableComponent = interactableActorReset->FindComponentByClass<UInteractableComponent>();
		if (ensureMsgf(InteractableComponent != nullptr, TEXT("The selected trigger is not ineractive!")))
			InteractableComponent->OnTriggerAction.AddDynamic(this, &AFire::RestartFire);
			
	}

	/*FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &AFire::ExtinguishFire, 6.f);*/
	
}

// Called every frame
void AFire::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AFire::ExtinguishFire()
{
	if(!extinguished)
	{
		fireAudioComponent->Stop();
		if (fireAudioComponent->IsValidLowLevelFast()) {
			fireAudioComponent->SetSound(smokeSound);
		}
		fireAudioComponent->Play();

		extinguished = true;
		fireParticleSystemComponent->Deactivate();
		smokeParticleSystemComponent->Activate();
	}
}

void AFire::DelayedExtinguishFire()
{
	float delay = FMath::FRandRange(2.0f, 5.0f);
	FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &AFire::ExtinguishFire, delay);
}

void AFire::RestartFire()
{
	if(extinguished)
	{
		fireAudioComponent->Stop();
		if (fireAudioComponent->IsValidLowLevelFast()) {
			fireAudioComponent->SetSound(fireSparksSound);
		}
		fireAudioComponent->Play();
		extinguished = false;
		smokeParticleSystemComponent->Deactivate();
		fireParticleSystemComponent->Activate();
	}
	
}

