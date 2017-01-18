// All rights Neebula Games

#include "SpacePlayground.h"
#include "PlaygroundPlayer.h"


// Sets default values
APlaygroundPlayer::APlaygroundPlayer()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlaygroundPlayer::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void APlaygroundPlayer::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

}

