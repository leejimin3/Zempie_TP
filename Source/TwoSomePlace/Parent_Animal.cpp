// Fill out your copyright notice in the Description page of Project Settings.


#include "Parent_Animal.h"

// Sets default values
AParent_Animal::AParent_Animal()
{

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParent_Animal::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AParent_Animal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

