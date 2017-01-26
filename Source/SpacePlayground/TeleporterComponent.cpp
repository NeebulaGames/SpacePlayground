// All rights Neebula Games

#include "SpacePlayground.h"
#include "TeleporterComponent.h"


// Sets default values for this component's properties
UTeleporterComponent::UTeleporterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTeleporterComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UTeleporterComponent::OnOverlap);
}

void UTeleporterComponent::OnOverlap(AActor* actor1, AActor* actor2)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString("Teleporting to ").Append(NextLevel));
		UGameplayStatics::OpenLevel(GetWorld(), FName(*NextLevel));
	}
}