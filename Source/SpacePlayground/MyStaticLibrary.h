#pragma once

#include "MyStaticLibrary.generated.h"

UCLASS()
class UMyStaticLibrary : public UObject
{
	GENERATED_UCLASS_BODY()

		//FORCEINLNE function
		static FORCEINLINE bool Trace(
			UWorld* World,
			AActor* ActorToIgnore,
			const FVector& Start,
			const FVector& End,
			FHitResult& HitOut,
			ECollisionChannel CollisionChannel = ECC_Pawn,
			bool ReturnPhysMat = true
			) {
		if (!World)
		{
			return false;
		}

		FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, ActorToIgnore);
		TraceParams.bTraceComplex = true;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

		//Ignore Actors
		TraceParams.AddIgnoredActor(ActorToIgnore);

		//Re-initialize hit info
		HitOut = FHitResult(ForceInit);

		//Trace!
		World->LineTraceSingleByChannel(
			HitOut,		//result
			Start,	//start
			End, //end
			CollisionChannel, //collision channel
			TraceParams
			);

		//Hit any Actor?
		return (HitOut.GetActor() != NULL);
	}

	//cpp function
	static int32 ComplicatedGameDataAnalysis();
};