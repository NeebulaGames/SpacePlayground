// All rights Neebula Games

#include "SpacePlayground.h"
#include "InteractableComponent.h"
#include "Explosion.h"


// Sets default values
AExplosion::AExplosion()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	BillboardComponent->SetupAttachment(RootComponent);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForceComponent->SetupAttachment(BillboardComponent);
	RadialForceComponent->Radius = 1000.f;
	RadialForceComponent->ImpulseStrength = 500000.f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> explosionPS(TEXT("ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'"));

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystemComponent->SetupAttachment(BillboardComponent);
	ParticleSystemComponent->SetTemplate(explosionPS.Object);
	ParticleSystemComponent->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundWave> explosionSound(TEXT("SoundWave'/Game/Sounds/Explosion01.Explosion01'"));
	this->explosionSound = explosionSound.Object;
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle unusedHandle;
	//GetWorldTimerManager().SetTimer(unusedHandle, this, &AExplosion::DelayedExplosion, 2.f);

	if (InteractableActor != nullptr)
	{
		UInteractableComponent* InteractableComponent = InteractableActor->FindComponentByClass<UInteractableComponent>();
		if (ensure(InteractableComponent != nullptr))
			//verify(InteractableComponent != nullptr/*, TEXT("Actor %s is not interactable!"), InteractableActor->GetName()*/);
			InteractableComponent->OnTriggerAction.AddDynamic(this, &AExplosion::DelayedExplosion);
	}
}

// Called every frame
void AExplosion::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AExplosion::DelayedExplosion()
{
	RadialForceComponent->FireImpulse();

	ParticleSystemComponent->Activate();

	
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), explosionSound, FVector(0.f));
}

