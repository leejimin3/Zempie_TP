// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalFarmGameMode.h"
#include "../Parent_Animal.h"

#include "Kismet/KismetMathLibrary.h"

void AAnimalFarmGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	//Spawn animals
}

void AAnimalFarmGameMode::SpawnAnimals(int animalSpawnCount)
{
	check(GetWorld() != nullptr);

	// upper player		
	for (int i = 0; i < animalSpawnCount; ++i)
	{
		AParent_Animal* animal = GetWorld()->SpawnActor<AParent_Animal>(AnimalClass, SpawnOrigin, { 0.0f,0.0f,0.0f });
		Animals.Push(animal);
	}

	// lower player
	for (int i = 0; i < animalSpawnCount; ++i)
	{
		AParent_Animal* animal = GetWorld()->SpawnActor<AParent_Animal>(AnimalClass, SpawnOrigin, { 0.0f,0.0f,0.0f });
		Animals.Push(animal);
	}
}
