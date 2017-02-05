// All rights Neebula Games

#include "SpacePlayground.h"
#include "Fire.h"


// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	billboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	billboardComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> firePS(TEXT("ParticleSystem'/Game/Particles/P_Fire.P_Fire'"));

	particleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	particleSystemComponent->SetupAttachment(billboardComponent);
	particleSystemComponent->SetTemplate(firePS.Object);
	particleSystemComponent->bAutoActivate = true;

	static ConstructorHelpers::FObjectFinder<USoundWave> fireSound(TEXT("SoundWave'/Game/Sounds/Fire01.Fire01'"));
	this->fireSound = fireSound.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> fireSparksSound(TEXT("SoundWave'/Game/Sounds/Fire_Sparks01.Fire_Sparks01'"));
	this->fireSparksSound = fireSparksSound.Object;
}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();

	//UGameplayStatics::PlaySoundAtLocation(GetWorld(), fireSound, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), fireSound, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), fireSparksSound, GetActorLocation());
	
}

// Called every frame
void AFire::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFire::ExtinguishFire()
{
	
}

