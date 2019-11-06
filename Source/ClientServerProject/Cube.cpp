
// Fill out your copyright notice in the Description page of Project Settings..
#include "Cube.h"

//No arguments in the constructor 
ACube::ACube()
{
	//Allow ticking....sort of...come back to
	PrimaryActorTick.bCanEverTick = true;

	//For no movment Error
	SetMobility(EComponentMobility::Movable);
}

void ACube::BeginPlay()
{
	Super::BeginPlay();
	//Setting replicates on the server so that inputs update on server and client and visa versa
	if (HasAuthority())
	{
		SetReplicates(true);        // Replicate cube mesh from server on client
		SetReplicateMovement(true); // Replicate cube mesh movment
	}

	//Start location of cube
	GlobalStartLocation = GetActorLocation();

	//Target location of cube
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //Super somthing?

	//Has Authority... Is the server, with replicates set, they will update on both, from the server
	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (Location - GlobalStartLocation).Size();

		if (JourneyTravelled >= JourneyLength)
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Speed * DeltaTime * Direction;
		SetActorLocation(Location);
	}
}