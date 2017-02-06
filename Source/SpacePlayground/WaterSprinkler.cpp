// All rights Neebula Games

#include "SpacePlayground.h"
#include "InteractableComponent.h"
#include "WaterSprinkler.h"


// Sets default values
AWaterSprinkler::AWaterSprinkler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	billboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	billboardComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> waterfallPS(TEXT("ParticleSystem'/Game/Particles/P_WaterFall.P_WaterFall'"));

	waterfallSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("waterfallSystemComponent"));
	waterfallSystemComponent->SetupAttachment(billboardComponent);
	waterfallSystemComponent->SetTemplate(waterfallPS.Object);
	waterfallSystemComponent->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundAttenuation> soundAttenuance(TEXT("SoundAttenuation'/Game/Effects/AttenuationDistanceEffect.AttenuationDistanceEffect'"));

	this->soundAttenuation = soundAttenuance.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> waterSound(TEXT("SoundWave'/Game/Sounds/Waterfall_Small02.Waterfall_Small02'"));
	this->waterSound = waterSound.Object;

	waterAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("waterAudioComponent"));
	waterAudioComponent->bAutoActivate = false;
	waterAudioComponent->SetupAttachment(billboardComponent);
	waterAudioComponent->AttenuationSettings = soundAttenuation;

}

// Called when the game starts or when spawned
void AWaterSprinkler::BeginPlay()
{
	Super::BeginPlay();

	//the Sprinkler will be OFF at start, we will have an Start function and a Stop function, to start the sprinklers and have them running over X time.

	/*FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(unusedHandle, this, &AWaterSprinkler::Start, 5.f);*/
	//GetWorldTimerManager().SetTimer(unusedHandle, this, &AWaterSprinkler::Stop, 10.f);


	if (InteractableActor != nullptr)
	{
		UInteractableComponent* InteractableComponent = InteractableActor->FindComponentByClass<UInteractableComponent>();
		if (ensureMsgf(InteractableComponent != nullptr, TEXT("The selected trigger is not ineractive!")))
			InteractableComponent->OnTriggerAction.AddDynamic(this, &AWaterSprinkler::StartStopsprinkler);
	}

	if (startActivated)
		StartStopsprinkler();
	
}

// Called every frame
void AWaterSprinkler::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWaterSprinkler::StartStopsprinkler()
{
	if(!isActive)
	{
		isActive = true;
		waterfallSystemComponent->Activate();

		waterAudioComponent->SetWorldLocation(GetActorLocation());

		if (waterAudioComponent->IsValidLowLevelFast()) {
			waterAudioComponent->SetSound(waterSound);
		}

		waterAudioComponent->Play();
	}
	else if (isActive)
	{
		isActive = false;
		waterfallSystemComponent->Deactivate();
		waterAudioComponent->Stop();
	}

}

