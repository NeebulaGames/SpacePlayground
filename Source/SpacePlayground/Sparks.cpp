// All rights Neebula Games

#include "SpacePlayground.h"
#include "Sparks.h"


// Sets default values
ASparks::ASparks()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	sparkAudioComponent->bOverrideAttenuation = true;
	FAttenuationSettings* fas = new FAttenuationSettings(sparkAudioComponent->AttenuationOverrides);
	fas->AttenuationShape = EAttenuationShape::Sphere;
	fas->AttenuationShapeExtents = FVector(200.0f);
	fas->FalloffDistance = 1500.0f;
	sparkAudioComponent->AdjustAttenuation(*fas);

	sparkPointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("Flash"));
	sparkPointLightComponent->SetupAttachment(sparkParticleSystemComponent);
	sparkPointLightComponent->SetIntensity(0.f);
	sparkPointLightComponent->SetAttenuationRadius(2048.f);
	sparkPointLightComponent->SetLightColor(FLinearColor(1.0f, 0.682f, 0.047f), false);
	sparkPointLightComponent->bUseInverseSquaredFalloff = false;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curvy(TEXT("CurveFloat'/Game/Miscellaneous/BrightnessControl.BrightnessControl'"));
	if (Curvy.Object)
		fCurve = Curvy.Object;

	BrightnessControl = CreateDefaultSubobject<UTimelineComponent>(TEXT("BrightnessControl"));
	
	//Bind the Callbackfuntion for the float return value
	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });
}

// Called when the game starts or when spawned
void ASparks::BeginPlay()
{
	Super::BeginPlay();

	delay = GetRandomDelay();

	//Add the float curve to the timeline and connect it to your timelines's interpolation function
	BrightnessControl->AddInterpFloat(fCurve, InterpFunction, FName{ TEXT("Floaty") });

	// Start your Timeline or PlayFromStart() etc, can be called anywhere in this class
	BrightnessControl->Play();
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
		BrightnessControl->PlayFromStart();
		sparkTime = 0.f;
		delay = GetRandomDelay();
	}
}

//Your Callback Function for the timeline float value
void ASparks::TimelineFloatReturn(float val) const
{
	sparkPointLightComponent->SetIntensity(val);
}

float ASparks::GetRandomDelay() const
{
	return FMath::FRandRange(minRand, maxRand);
}

