// All rights Neebula Games

#include "SpacePlayground.h"
#include "Sparks.h"


// Sets default values
ASparks::ASparks()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//billboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	//billboardComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> sparksPS(TEXT("ParticleSystem'/Game/Particles/P_spark_burst.P_spark_burst'"));

	sparkParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));
	sparkParticleSystemComponent->SetupAttachment(RootComponent);
	sparkParticleSystemComponent->SetTemplate(sparksPS.Object);
	sparkParticleSystemComponent->bAutoActivate = true;

	static ConstructorHelpers::FObjectFinder<USoundCue> sparksSound(TEXT("SoundCue'/Game/Sounds/sparks.sparks'"));
	if(sparksSound.Object)
		this->sparksSound = sparksSound.Object;

	sparkAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	sparkAudioComponent->SetupAttachment(sparkParticleSystemComponent);
	sparkAudioComponent->bAutoActivate = true;
	sparkAudioComponent->SetSound(this->sparksSound);

	sparkPointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("Flash"));
	sparkPointLightComponent->SetupAttachment(sparkParticleSystemComponent);
	sparkPointLightComponent->SetIntensity(0.f);
	sparkPointLightComponent->SetAttenuationRadius(2048.f);
	sparkPointLightComponent->SetLightColor(FLinearColor(1.0f, 0.682f, 0.047f), false);


}

// Called when the game starts or when spawned
void ASparks::BeginPlay()
{
	Super::BeginPlay();

	delay = GetRandomDelay();
}

// Called every frame
void ASparks::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	sparkTime += DeltaTime;

	if (sparkTime > delay)
	{
		sparkParticleSystemComponent->Activate();
		sparkAudioComponent->Play();
		sparkTime = 0.f;
		delay = GetRandomDelay();
	}
}

float ASparks::GetRandomDelay() const
{
	return FMath::FRandRange(minRand, maxRand);
}

