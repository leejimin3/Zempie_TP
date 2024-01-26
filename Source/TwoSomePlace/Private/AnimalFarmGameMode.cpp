// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalFarmGameMode.h"

void AAnimalFarmGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	//Spawn animals
}

void AAnimalFarmGameMode::SpawnAnimals(int animalSpawnCount)
{
	FTransform animalDefaultTransform;
	animalDefaultTransform.SetScale3D({ 1.0f,1.0f,1.0f });

	FVector animalSpawnWorldLocation = MapCenterWorldLocation;
	animalSpawnWorldLocation.Y -= AnimalSpawnYDistance * animalSpawnCount;

}
