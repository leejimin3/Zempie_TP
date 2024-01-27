// Fill out your copyright notice in the Description page of Project Settings.


#include "CinematicCamera.h"

// Sets default values
ACinematicCamera::ACinematicCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACinematicCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACinematicCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}