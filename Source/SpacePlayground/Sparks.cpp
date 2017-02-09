// All rights Neebula Games

#include "SpacePlayground.h"
#include "Sparks.h"


// Sets default values
ASparks::ASparks()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	billboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	billboardComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> sparksPS(TEXT("ParticleSystem'/Game/Particles/P_spark_burst.P_spark_burst'"));

	sparkParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SparkParticleSystem"));
	sparkParticleSystemComponent->SetupAttachment(billboardComponent);
	sparkParticleSystemComponent->SetTemplate(sparksPS.Object);
	sparkParticleSystemComponent->bAutoActivate = true;

	static ConstructorHelpers::FObjectFinder<USoundWave> sparkSound(TEXT("SoundWave'/Game/Sounds/sparks.sparks'"));
	this->sparkSound = sparkSound.Object;
}

// Called when the game starts or when spawned
void ASparks::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASparks::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

