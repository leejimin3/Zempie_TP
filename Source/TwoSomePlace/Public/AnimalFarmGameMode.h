// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"
#include "AnimalFarmGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TWOSOMEPLACE_API AAnimalFarmGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
public:

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FVector MapCenterWorldLocation;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float FarmSize = 512.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float AnimalSpawnYDistance = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Animal")
	void SpawnAnimals(int animalSpawnCount);

private:

	UPROPERTY()
	TArray<AActor*> UpperPlayerAnimals;

	UPROPERTY()
	TArray<AActor*> LowerPlayerAnimals;

};
